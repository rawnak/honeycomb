/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-thread-simple-memory-allocator.c: Bootstrap file for z-thread-simple-memory-allocator.zco
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


/* The simple allocator stores a list of bins containing a list of free blocks.
   The blocks are chained with a single linked list, where the 'next' pointer
   is stored within the free space. This means that the smallest block size
   is that of a pointer:
     bin 0:  8-byte blocks
     bin 1:  16-byte blocks
     bin 2:  24-byte blocks
     bin 3:  32-byte blocks
     ...

   The block sizes are always 64-bit aligned

 */

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-thread-simple-memory-allocator.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZThreadSimpleMemoryAllocator
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_thread_simple_memory_allocator_new(ctx,allocator)
#define INIT_EXISTS
#define init z_thread_simple_memory_allocator_init
#define new z_thread_simple_memory_allocator_new
#define get_padded_size z_thread_simple_memory_allocator_get_padded_size
#define get_bin_index z_thread_simple_memory_allocator_get_bin_index
#define get_block_size z_thread_simple_memory_allocator_get_block_size

int z_thread_simple_memory_allocator_type_id = -1;

static Self *__z_thread_simple_memory_allocator_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_thread_simple_memory_allocator_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		ZMemoryAllocator *obj_allocator = ctx->fixed_allocator;
		if (obj_allocator)
			self = (Self *) z_memory_allocator_allocate(obj_allocator, sizeof(Self));
		else
			self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_thread_simple_memory_allocator_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_thread_simple_memory_allocator_init(Self *self);
static void  z_thread_simple_memory_allocator_dispose(ZObject *object);
static int  z_thread_simple_memory_allocator_get_padded_size(int size);
static int  z_thread_simple_memory_allocator_get_bin_index(Self *self,int padded_size);
static void *  z_thread_simple_memory_allocator_allocate(ZMemoryAllocator *allocator,int size);
static void *  z_thread_simple_memory_allocator_allocate_aligned(ZMemoryAllocator *allocator,int size,int alignment);
static int  z_thread_simple_memory_allocator_get_usable_size(ZMemoryAllocator *allocator,void *block);
static void *  z_thread_simple_memory_allocator_resize(ZMemoryAllocator *allocator,void *block,int new_size);
static int  z_thread_simple_memory_allocator_get_block_size(void *block);
static void  z_thread_simple_memory_allocator_deallocate_by_size(ZMemoryAllocator *allocator,void *block,int size);
static int  z_thread_simple_memory_allocator_garbage_collect(ZMemoryAllocator *allocator);
static void z_thread_simple_memory_allocator_class_destroy(ZObjectGlobal *gbl);
static void z_thread_simple_memory_allocator___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZThreadSimpleMemoryAllocatorGlobal * z_thread_simple_memory_allocator_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_thread_simple_memory_allocator_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_thread_simple_memory_allocator_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZThreadSimpleMemoryAllocatorGlobal *global = (ZThreadSimpleMemoryAllocatorGlobal *) malloc(sizeof(struct ZThreadSimpleMemoryAllocatorGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZThreadSimpleMemoryAllocatorClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZThreadSimpleMemoryAllocatorClass));
		global->common.name = "ZThreadSimpleMemoryAllocator";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZThreadSimpleMemoryAllocator temp;
		struct ZThreadSimpleMemoryAllocatorClass temp_class;

		{
			struct ZMemoryAllocatorGlobal *p_global = z_memory_allocator_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_global->common.vtable_off_list,
				p_global->common.vtable_off_size,
				&temp,
				&temp.parent_z_memory_allocator);
			zco_inherit_vtable(
				&global->common.svtable_off_list,
				&global->common.svtable_off_size,
				p_global->common.svtable_off_list,
				p_global->common.svtable_off_size,
				&temp_class,
				&temp_class.parent_z_memory_allocator);
			ZMemoryAllocatorClass *p1_class = CLASS_FROM_GLOBAL(p_global);
			ZMemoryAllocatorClass *p2_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			memcpy(p2_class, p1_class, sizeof(struct ZMemoryAllocatorClass));
		}
		if (z_thread_simple_memory_allocator_type_id == -1)
			z_thread_simple_memory_allocator_type_id = zco_allocate_type_id();
		global->common.id = z_thread_simple_memory_allocator_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_thread_simple_memory_allocator_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_thread_simple_memory_allocator_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_thread_simple_memory_allocator_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_thread_simple_memory_allocator_dispose;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_allocate = p_class->__allocate;
			p_class->__allocate = z_thread_simple_memory_allocator_allocate;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_allocate_aligned = p_class->__allocate_aligned;
			p_class->__allocate_aligned = z_thread_simple_memory_allocator_allocate_aligned;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_get_usable_size = p_class->__get_usable_size;
			p_class->__get_usable_size = z_thread_simple_memory_allocator_get_usable_size;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_resize = p_class->__resize;
			p_class->__resize = z_thread_simple_memory_allocator_resize;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_deallocate_by_size = p_class->__deallocate_by_size;
			p_class->__deallocate_by_size = z_thread_simple_memory_allocator_deallocate_by_size;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_garbage_collect = p_class->__garbage_collect;
			p_class->__garbage_collect = z_thread_simple_memory_allocator_garbage_collect;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_thread_simple_memory_allocator_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_thread_simple_memory_allocator___delete;
		}
		__z_thread_simple_memory_allocator_class_init(ctx, (ZThreadSimpleMemoryAllocatorClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZThreadSimpleMemoryAllocatorGlobal *) global);
		#endif
		return global;
	}
	return (ZThreadSimpleMemoryAllocatorGlobal *) *global_ptr;
}

void __z_thread_simple_memory_allocator_class_init(struct zco_context_t *ctx, ZThreadSimpleMemoryAllocatorClass *_class)
{
	__z_memory_allocator_class_init(ctx, (ZMemoryAllocatorClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_thread_simple_memory_allocator_init(struct zco_context_t *ctx, Self *self)
{
	struct ZThreadSimpleMemoryAllocatorGlobal *_global = z_thread_simple_memory_allocator_get_type(ctx);
	self->_global = _global;
	__z_memory_allocator_init(ctx, (ZMemoryAllocator *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_thread_simple_memory_allocator_init(Self *self)
{
 pthread_mutex_init(&selfp->lock, NULL);

 selfp->bins = NULL;
 selfp->nbins = 0;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_thread_simple_memory_allocator_dispose(ZObject *object)
{
 Self *self = (Self *) object;
 pthread_mutex_destroy(&selfp->lock);
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_thread_simple_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
static int  z_thread_simple_memory_allocator_get_padded_size(int size)
{
 return (size + 7) & ~7;
 }
static int  z_thread_simple_memory_allocator_get_bin_index(Self *self,int padded_size)
{
 int bin_index = padded_size >> 3 - 1;

 if (selfp->nbins <= bin_index) {
 selfp->bins = realloc(selfp->bins, sizeof(void*) * (bin_index+1));
 memset(selfp->bins + (sizeof(void*) * selfp->nbins), 0, sizeof(void*) * ((bin_index+1) - selfp->nbins));
 selfp->nbins = bin_index+1;
 }

 return bin_index;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_allocate
static void *  z_thread_simple_memory_allocator_allocate(ZMemoryAllocator *allocator,int size)
{
 Self *self = (Self *) allocator;
 int padded_size = get_padded_size(size);

 pthread_mutex_lock(&selfp->lock);

 int bin_index = get_bin_index(self, padded_size);
 void **bins = (void **) selfp->bins;
 void *p;

 if (selfp->nbins <= bin_index || bins[bin_index] == 0) {
 p = malloc(padded_size);
 goto done;
 }

 /* dereference 'bin' to get the head node of the free list */
 p = bins[bin_index];

 /* dereference the head node to get the next node. assign
                   this pointer value to the 'bin' */
 bins[bin_index] = *((void **) p);

done:
 pthread_mutex_unlock(&selfp->lock);
 return (unsigned char *) p;
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_allocate_aligned
static void *  z_thread_simple_memory_allocator_allocate_aligned(ZMemoryAllocator *allocator,int size,int alignment)
{
 return NULL;
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_get_usable_size
static int  z_thread_simple_memory_allocator_get_usable_size(ZMemoryAllocator *allocator,void *block)
{
 return malloc_usable_size(block);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_resize
static void *  z_thread_simple_memory_allocator_resize(ZMemoryAllocator *allocator,void *block,int new_size)
{
 return NULL;
 }
#undef PARENT_HANDLER
static int  z_thread_simple_memory_allocator_get_block_size(void *block)
{
 return *((unsigned long *) block);
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_deallocate_by_size
static void  z_thread_simple_memory_allocator_deallocate_by_size(ZMemoryAllocator *allocator,void *block,int size)
{
 Self *self = (Self *) allocator;

 pthread_mutex_lock(&selfp->lock);

 int bin_index = get_bin_index(self, get_padded_size(size));
 void **bins = (void **) selfp->bins;

 /* store pointer to old head in the memory block being freed */
 *((void **) block) = bins[bin_index];

 /* make the new block the head node */
 bins[bin_index] = block;

 pthread_mutex_unlock(&selfp->lock);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_garbage_collect
static int  z_thread_simple_memory_allocator_garbage_collect(ZMemoryAllocator *allocator)
{
 Self *self = (Self *) allocator;

 pthread_mutex_lock(&selfp->lock);

 void **bins = (void **) selfp->bins;
 int i;

 for (i=0; i<selfp->nbins; ++i) {
 void *p;
 
 while ((p = bins[i])) {
 bins[i] = *((void **) p);
 free(p);
 }
 }

 if (selfp->bins)
 free(selfp->bins);

 selfp->bins = NULL;
 selfp->nbins = 0;

 int rc = PARENT_HANDLER(allocator);
 pthread_mutex_unlock(&selfp->lock);

 return rc;
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_thread_simple_memory_allocator_class_destroy(ZObjectGlobal *gbl)
{
	ZThreadSimpleMemoryAllocatorGlobal *_global = (ZThreadSimpleMemoryAllocatorGlobal *) gbl;

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_thread_simple_memory_allocator___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



