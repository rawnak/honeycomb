/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-memory-allocator.c: Bootstrap file for z-memory-allocator.zco
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

#line 7 "z-memory-allocator.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-memory-allocator.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZMemoryAllocator
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_memory_allocator_new(ctx,allocator)
#define INIT_EXISTS
#define init z_memory_allocator_init
#define get_object_tracker z_memory_allocator_get_object_tracker
#define set_object_tracker z_memory_allocator_set_object_tracker
#define allocate z_memory_allocator_allocate
#define allocate_aligned z_memory_allocator_allocate_aligned
#define get_usable_size z_memory_allocator_get_usable_size
#define resize z_memory_allocator_resize
#define deallocate z_memory_allocator_deallocate
#define deallocate_by_size z_memory_allocator_deallocate_by_size
#define garbage_collect z_memory_allocator_garbage_collect

int z_memory_allocator_type_id = -1;

static Self *__z_memory_allocator_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_memory_allocator_type_id);
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
		__z_memory_allocator_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_memory_allocator_init(Self *self);
static void  z_memory_allocator_dispose(ZObject *object);
static void  z_memory_allocator_reset(ZObject *object);
static void *  z_memory_allocator_virtual_allocate(Self *self,int size);
static void *  z_memory_allocator_virtual_allocate_aligned(Self *self,int size,int alignment);
static int  z_memory_allocator_virtual_get_usable_size(Self *self,void *block);
static void *  z_memory_allocator_virtual_resize(Self *self,void *block,int new_size);
static void  z_memory_allocator_virtual_deallocate(Self *self,void *block);
static void  z_memory_allocator_virtual_deallocate_by_size(Self *self,void *block,int size);
static int  z_memory_allocator_virtual_garbage_collect(Self *self);
static void z_memory_allocator_class_destroy(ZObjectGlobal *gbl);
static void z_memory_allocator___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZMemoryAllocatorGlobal * z_memory_allocator_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_memory_allocator_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_memory_allocator_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZMemoryAllocatorGlobal *global = (ZMemoryAllocatorGlobal *) malloc(sizeof(struct ZMemoryAllocatorGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZMemoryAllocatorClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZMemoryAllocatorClass));
		global->common.name = "ZMemoryAllocator";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZMemoryAllocator temp;
		struct ZMemoryAllocatorClass temp_class;

		{
			struct ZObjectGlobal *p_global = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_global->common.vtable_off_list,
				p_global->common.vtable_off_size,
				&temp,
				&temp.parent_z_object);
			zco_inherit_vtable(
				&global->common.svtable_off_list,
				&global->common.svtable_off_size,
				p_global->common.svtable_off_list,
				p_global->common.svtable_off_size,
				&temp_class,
				&temp_class.parent_z_object);
			ZObjectClass *p1_class = CLASS_FROM_GLOBAL(p_global);
			ZObjectClass *p2_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			memcpy(p2_class, p1_class, sizeof(struct ZObjectClass));
		}
		if (z_memory_allocator_type_id == -1)
			z_memory_allocator_type_id = zco_allocate_type_id();
		global->common.id = z_memory_allocator_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_memory_allocator_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_memory_allocator_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_memory_allocator_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_memory_allocator_dispose;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_memory_allocator_reset;
		}
		CLASS_FROM_GLOBAL(global)->__allocate = z_memory_allocator_virtual_allocate;
		CLASS_FROM_GLOBAL(global)->__allocate_aligned = z_memory_allocator_virtual_allocate_aligned;
		CLASS_FROM_GLOBAL(global)->__get_usable_size = z_memory_allocator_virtual_get_usable_size;
		CLASS_FROM_GLOBAL(global)->__resize = z_memory_allocator_virtual_resize;
		CLASS_FROM_GLOBAL(global)->__deallocate = z_memory_allocator_virtual_deallocate;
		CLASS_FROM_GLOBAL(global)->__deallocate_by_size = z_memory_allocator_virtual_deallocate_by_size;
		CLASS_FROM_GLOBAL(global)->__garbage_collect = z_memory_allocator_virtual_garbage_collect;
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_memory_allocator_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_memory_allocator___delete;
		}
		__z_memory_allocator_class_init(ctx, (ZMemoryAllocatorClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("allocate"), (ZObjectSignalHandler) allocate);
		z_map_insert((ZMap *) global->common.method_map, strdup("allocate_aligned"), (ZObjectSignalHandler) allocate_aligned);
		z_map_insert((ZMap *) global->common.method_map, strdup("get_usable_size"), (ZObjectSignalHandler) get_usable_size);
		z_map_insert((ZMap *) global->common.method_map, strdup("resize"), (ZObjectSignalHandler) resize);
		z_map_insert((ZMap *) global->common.method_map, strdup("deallocate"), (ZObjectSignalHandler) deallocate);
		z_map_insert((ZMap *) global->common.method_map, strdup("deallocate_by_size"), (ZObjectSignalHandler) deallocate_by_size);
		z_map_insert((ZMap *) global->common.method_map, strdup("garbage_collect"), (ZObjectSignalHandler) garbage_collect);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZMemoryAllocatorGlobal *) global);
		#endif
		return global;
	}
	return (ZMemoryAllocatorGlobal *) *global_ptr;
}

void __z_memory_allocator_class_init(struct zco_context_t *ctx, ZMemoryAllocatorClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_memory_allocator_init(struct zco_context_t *ctx, Self *self)
{
	struct ZMemoryAllocatorGlobal *_global = z_memory_allocator_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_memory_allocator_init(Self *self)
{
 selfp->object_tracker = NULL;
 }
ZObjectTracker * z_memory_allocator_get_object_tracker(Self *self)
{
 if (selfp->object_tracker)
 z_object_ref(Z_OBJECT(selfp->object_tracker));

 return selfp->object_tracker;
 }
void z_memory_allocator_set_object_tracker(Self *self, ZObjectTracker * value)
{
 if (selfp->object_tracker) {
 ZObjectTracker *tracker = selfp->object_tracker;
 ZObjectTracker *tracker_interface = Z_OBJECT_TRACKER((ZObject *) tracker);

 /* Full garbage collection */
 while (z_object_tracker_garbage_collect(tracker));

 /* Unload the object tracker */
 selfp->object_tracker = NULL;
 z_object_unref(Z_OBJECT(tracker));
 }

 selfp->object_tracker = value;

 if (value)
 z_object_ref(Z_OBJECT(value));
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_memory_allocator_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 /* The object tracker must be reset by the caller. Resetting
                   object trackers for all memory allocators before resetting
                   any allocator ensures that the allocators are present during
                   the destruction of the objects. */
 assert(selfp->object_tracker == NULL);

 /* Notify allocators to start cleaning up */
 garbage_collect(self);

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_memory_allocator_reset(ZObject *object)
{
 Self *self = (Self *) object;
 set_object_tracker(self, NULL);
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
void *  z_memory_allocator_allocate(Self *self,int size)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__allocate(self,size);
}
static void *  z_memory_allocator_virtual_allocate(Self *self,int size)
{
 return 0; /* not handled */
 }
void *  z_memory_allocator_allocate_aligned(Self *self,int size,int alignment)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__allocate_aligned(self,size,alignment);
}
static void *  z_memory_allocator_virtual_allocate_aligned(Self *self,int size,int alignment)
{
 return 0; /* not handled */
 }
int  z_memory_allocator_get_usable_size(Self *self,void *block)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__get_usable_size(self,block);
}
static int  z_memory_allocator_virtual_get_usable_size(Self *self,void *block)
{
 return -1; /* not handled */
 }
void *  z_memory_allocator_resize(Self *self,void *block,int new_size)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__resize(self,block,new_size);
}
static void *  z_memory_allocator_virtual_resize(Self *self,void *block,int new_size)
{
 return 0; /* not handled */
 }
void  z_memory_allocator_deallocate(Self *self,void *block)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__deallocate(self,block);
}
static void  z_memory_allocator_virtual_deallocate(Self *self,void *block)
{
 return; /* not handled */
 }
void  z_memory_allocator_deallocate_by_size(Self *self,void *block,int size)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__deallocate_by_size(self,block,size);
}
static void  z_memory_allocator_virtual_deallocate_by_size(Self *self,void *block,int size)
{
 deallocate(self, block);
 }
int  z_memory_allocator_garbage_collect(Self *self)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__garbage_collect(self);
}
static int  z_memory_allocator_virtual_garbage_collect(Self *self)
{
 if (selfp->object_tracker)
 return z_object_tracker_garbage_collect(selfp->object_tracker);

 return 0;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_memory_allocator_class_destroy(ZObjectGlobal *gbl)
{
	ZMemoryAllocatorGlobal *_global = (ZMemoryAllocatorGlobal *) gbl;

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_memory_allocator___delete(ZObject *self)
{
ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
if (allocator)
	z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
else
	free(self);
}

#undef PARENT_HANDLER



