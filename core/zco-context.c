/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco-type.c: Context management
 * This file is part of ZCO.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ZCO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ZCO.  If not, see <http://www.gnu.org/licenses/>.
 */

#define _GNU_SOURCE

#include <zco-context.h>
#include <zco-config.h>

#include <z-object.h>
#include <z-sys-memory-allocator.h>
#include <z-vector-segment.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#if !defined(BOOTSTRAP)
#include <z-simple-memory-allocator.h>
#include <z-buddy-memory-allocator.h>
#include <z-thread-simple-memory-allocator.h>
#include <z-default-object-tracker.h>
#endif

static int next_id = -1;
static int last_allocator_id = -1;

void zco_context_init(struct zco_context_t *ctx)
{
	ctx->type_count = 0;
	ctx->types = 0;
        ctx->fixed_allocator = NULL;
        ctx->flex_allocator = NULL;

        /* Set the default minimum segment capacity to be 3 times the overhead
           incurred by each segment. This means that there can be at most 40%
           wasted space that is not used by the actual data */
        zco_context_set_min_segment_capacity_by_size(ctx, 3 * sizeof(ZVectorSegment));

        /* Set the default minimum segment capacity to hold 2 items. If each
           segment holds a single item, it is nothing more than a linked list. */
        zco_context_set_min_segment_capacity_by_count(ctx, 2);

        /* Create the allocators */
#if !defined(BOOTSTRAP) && defined(USE_CUSTOM_ALLOCATORS)
        ZSimpleMemoryAllocator *fixed_allocator = z_simple_memory_allocator_new(ctx, NULL);
        ZBuddyMemoryAllocator *flex_allocator = z_buddy_memory_allocator_new(ctx, NULL);
        ZThreadSimpleMemoryAllocator *ts_fixed_allocator = z_thread_simple_memory_allocator_new(ctx, NULL);
#else
        ZSysMemoryAllocator *fixed_allocator = z_sys_memory_allocator_new(ctx, NULL);
        ZSysMemoryAllocator *flex_allocator = z_sys_memory_allocator_new(ctx, NULL);
        ZSysMemoryAllocator *ts_fixed_allocator = z_sys_memory_allocator_new(ctx, NULL);
#endif

        ctx->fixed_allocator = (ZMemoryAllocator *) fixed_allocator;
        ctx->flex_allocator = (ZMemoryAllocator *) flex_allocator;
        ctx->ts_fixed_allocator = (ZMemoryAllocator *) ts_fixed_allocator;

        /* Keep note of the last type id for which the object buffer was not
           allocated using the allocators. */
        if (last_allocator_id == -1)
                last_allocator_id = next_id;

#if !defined(BOOTSTRAP) && defined(USE_GARBAGE_COLLECTION)
        /* Create an object tracker for each allocator */
        ZDefaultObjectTracker *fixed_tracker = z_default_object_tracker_new(ctx, NULL);
        ZDefaultObjectTracker *flex_tracker = z_default_object_tracker_new(ctx, NULL);
        ZDefaultObjectTracker *ts_fixed_tracker = z_default_object_tracker_new(ctx, NULL);

        /* Assign the object tracker to the allocator */
        z_memory_allocator_set_object_tracker((ZMemoryAllocator *) fixed_allocator, (ZObjectTracker *) fixed_tracker);
        z_memory_allocator_set_object_tracker((ZMemoryAllocator *) flex_allocator, (ZObjectTracker *) flex_tracker);
        z_memory_allocator_set_object_tracker((ZMemoryAllocator *) ts_fixed_allocator, (ZObjectTracker *) ts_fixed_tracker);

        z_object_unref(Z_OBJECT(fixed_tracker));
        z_object_unref(Z_OBJECT(flex_tracker));
        z_object_unref(Z_OBJECT(ts_fixed_tracker));
#endif
}

void zco_context_destroy(struct zco_context_t *ctx)
{
	int i;

        /* Release method maps used for signals that use the fixed allocator
           to allocate space for the object buffer */
	for (i=ctx->type_count-1; i>last_allocator_id ; --i) {
		struct ZCommonGlobal *global = ctx->types[i];

		if (global)
			z_object_unref((ZObject *) global->method_map);
	}

        /* Perform full garbage collection */
        zco_context_full_garbage_collect(ctx);

        /* Release the object trackers */
        z_memory_allocator_set_object_tracker(ctx->ts_fixed_allocator, NULL);
        z_memory_allocator_set_object_tracker(ctx->flex_allocator, NULL);
        z_memory_allocator_set_object_tracker(ctx->fixed_allocator, NULL);

        /* Destroy objects for class static */
	for (i=ctx->type_count-1; i >= 0; --i) {
		struct ZCommonGlobal *global = ctx->types[i];

		if (global) {
                        struct ZObjectGlobal *obj_global = ((ZObjectGlobal *) global);

			if (global->is_object) {
				z_object_class_destroy(obj_global);
			}
		}
	}

        /* Release memory allocators */
        ZMemoryAllocator *ts_fixed_allocator = ctx->ts_fixed_allocator;
        ZMemoryAllocator *flex_allocator = ctx->flex_allocator;
        ZMemoryAllocator *fixed_allocator = ctx->fixed_allocator;

        ctx->ts_fixed_allocator = NULL;
        ctx->flex_allocator = NULL;
        ctx->fixed_allocator = NULL;

        z_object_unref(Z_OBJECT(ts_fixed_allocator));
        z_object_unref(Z_OBJECT(flex_allocator));
        z_object_unref(Z_OBJECT(fixed_allocator));

        /* Release the remaining  method maps used for signals. This includes
           the maps that were included before the fixed allocator was available
           for use. This is why it has to be deallocated after the allocators
           have been uninstalled. */
	for (i=last_allocator_id; i>=0; --i) {
		struct ZCommonGlobal *global = ctx->types[i];

		if (global)
			z_object_unref((ZObject *) global->method_map);
	}

        /* Free class static */
	for (i=ctx->type_count - 1; i >= 0; --i) {
		struct ZCommonGlobal *global = ctx->types[i];

		if (global) {
                        struct ZObjectGlobal *obj_global = ((ZObjectGlobal *) global);

			free(obj_global->_class);
			free(global->vtable_off_list);
                        free(global->svtable_off_list);
			free(global);
		}
	}

	free(ctx->types);
	ctx->types = NULL;
	ctx->type_count = 0;
}

ZCommonGlobal **zco_get_ctx_type(struct zco_context_t *ctx, int type_id)
{
	if (ctx->type_count <= type_id) {
		int new_size = type_id + 1;

		ctx->types = (ZCommonGlobal **) realloc(ctx->types, new_size * sizeof(void *));
		memset(ctx->types + ctx->type_count, 0, (new_size - ctx->type_count) * sizeof(void *));
		ctx->type_count = new_size;
	}

	return ctx->types + type_id;
}

int zco_allocate_type_id()
{
	return ++next_id;
}

int zco_get_type_count()
{
	return next_id+1;
}

void zco_inherit_vtable(int **list, int *size, int *src_list, int src_size, void *base, void *target)
{
	int i;

	/* compute the difference between the two address and store the offset into this element */
	int offset = (unsigned long) target - (unsigned long) base;

	/* if the source table is larger than the target table, increase the size of the target table
	   to match that of the source table */
	if (*size < src_size) {
		int old_size = *size;
		*size = src_size;

		*list = (int *) realloc(*list, src_size * sizeof(int));

		/* fill the uninitialized elements with -1 */
		memset(*list + old_size, 0xff, (src_size - old_size) * sizeof(int));
	} 

	/* copy the valid elements from the source table to the target table */
	for (i=0; i<src_size; ++i) {
		int src = src_list[i];

		if (src != -1)
			(*list)[i] = src_list[i] + offset;
	}
}

void zco_add_to_vtable(int **list, int *size, int type_id)
{
	/* if the type_id that we want to add is too high for the current size of the table, increase
	   the size of the table so that we are able to add this new type_id */
	if (*size <= type_id) {
		/* current vtable_off_table isn't large enough to hold specified type. we need to
		   resize the table and set the uninitialized data to -1 */
		int old_size = *size;
		int new_size = type_id + 1;
		*size = new_size;

		*list = (int *) realloc(*list, new_size * sizeof(int));

		/* fill the uninitialized elements (all new elements except for the last one, which we want
		   to fill with useful information) with -1 */
		memset(*list + old_size, 0xff, (new_size - old_size - 1) * sizeof(int));
	}

	/* set the offset of the type 'type_id' to 0 */
	(*list)[type_id] = 0;
}

int zco_context_get_min_segment_capacity_by_size(struct zco_context_t *ctx)
{
        return ctx->min_segment_cap_by_size;
}

void zco_context_set_min_segment_capacity_by_size(struct zco_context_t *ctx, int value)
{
        ctx->min_segment_cap_by_size = value;
}

int zco_context_get_min_segment_capacity_by_count(struct zco_context_t *ctx)
{
        return ctx->min_segment_cap_by_count;
}

void zco_context_set_min_segment_capacity_by_count(struct zco_context_t *ctx, int value)
{
        ctx->min_segment_cap_by_count = value;
}

void zco_context_full_garbage_collect(struct zco_context_t *ctx)
{
        /* Full garbage collection on all allocators.
           Since running GC in one object tracker may push items into the pool
           of another object tracker, we cannot assume one tracker's pool is
           clear until all the trackers' pool have been cleared */

        int objects_released;

        do {
                objects_released = 0;

                objects_released += z_memory_allocator_garbage_collect(ctx->ts_fixed_allocator);
                objects_released += z_memory_allocator_garbage_collect(ctx->flex_allocator);
                objects_released += z_memory_allocator_garbage_collect(ctx->fixed_allocator);

        } while (objects_released);
}


