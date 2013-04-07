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

#include <zco-type.h>
#include <z-object.h>
#include <z-framework-events.h>
#include <z-default-object-tracker.h>
#include <z-vector-segment.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int next_id = -1;

void zco_context_init(struct zco_context_t *ctx)
{
	ctx->type_count = 0;
	ctx->types = 0;
	ctx->marshal = NULL;
        ctx->object_tracker = NULL;

        /* Set the default minimum segment capacity to be 3 times the overhead
           incurred by each segment. This means that there can be at most 40%
           wasted space that is not used by the actual data */
        zco_context_set_min_segment_capacity_by_size(ctx, 3 * sizeof(ZVectorSegment));

        /* Set the default minimum segment capacity to hold 2 items. If each
           segment holds a single item, it is nothing more than a linked list. */
        zco_context_set_min_segment_capacity_by_count(ctx, 2);

	ctx->framework_events = z_framework_events_new(ctx, NULL);

        /* Load the default object tracker
           This must be the very last step in the context initialization process
           (by convention). Loading the object tracker at the end of the context
           initialization and unloading it at the start of the context destruction
           ensures that we consistently use the correct tracker for every object. */
        ZObjectTracker *tracker = (ZObjectTracker *) z_default_object_tracker_new(ctx, NULL);
        zco_context_set_object_tracker(ctx, (void *) tracker);
}

void zco_context_destroy(struct zco_context_t *ctx)
{
	int i;
        ZObjectTracker *tracker = (ZObjectTracker *) ctx->object_tracker;

        if (tracker) {
                /* Full garbage collection */
                while (z_object_tracker_garbage_collect((ZObjectTracker *) tracker));

                /* Unload the object tracker
                   This must be the very first step in the context destruction process
                   (by convention). Loading the object tracker at the end of the context
                   initialization and unloading it at the start of the context destruction
                   ensures that we consistently use the correct tracker for every object.
                   
                   When we created the object tracker, we didn't have any trackers loaded.
                   When we are unloading the object tracker, we must ensure that no trackers
                   (itself) isn't loaded. To do this, we keep a reference to the pointer
                   and set the pointer to NULL. */
                ctx->object_tracker = NULL;
                z_object_unref(Z_OBJECT(tracker));
        }

	z_object_unref((ZObject *) ctx->framework_events);

	if (ctx->marshal) {
		z_object_unref((ZObject *) ctx->marshal);
		ctx->marshal = NULL;
	}

	for (i=0; i < ctx->type_count; ++i) {
		struct ZCommonGlobal *global = ctx->types[i];

		if (global)
			z_object_unref((ZObject *) global->method_map);
	}

	for (i=ctx->type_count - 1; i >= 0; --i) {
		struct ZCommonGlobal *global = ctx->types[i];

		if (global) {
                        struct ZObjectGlobal *obj_global = ((ZObjectGlobal *) global);

			if (global->is_object) {
				z_object_class_destroy(obj_global);
			}
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

void zco_context_set_marshal(struct zco_context_t *ctx, void *marshal)
{
	if (ctx->marshal)
		z_object_unref((ZObject *) ctx->marshal);

	ctx->marshal = marshal;
	z_object_ref((ZObject *) marshal);
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

void * zco_context_get_framework_events(struct zco_context_t *ctx)
{
	return ctx->framework_events;
}

void * zco_context_set_object_tracker(struct zco_context_t *ctx, void *object_tracker)
{
        ctx->object_tracker = object_tracker;
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


