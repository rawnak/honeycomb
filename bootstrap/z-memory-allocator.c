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
#include <z-memory-allocator-protected.h>
#include <zco-context.h>
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

ZCO_DEFINE_CLASS_TYPE(z_memory_allocator);

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
	ZCO_CREATE_CLASS(global, ZMemoryAllocator, z_memory_allocator, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZMemoryAllocator);
	ZCO_REGISTER_TYPE(z_memory_allocator);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_memory_allocator, dispose);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_memory_allocator, reset);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, allocate);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, allocate_aligned);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, get_usable_size);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, resize);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, deallocate);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, deallocate_by_size);
	ZCO_CREATE_VIRTUAL_METHOD(z_memory_allocator, garbage_collect);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_memory_allocator, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_memory_allocator, __delete);
	ZCO_CREATE_METHOD_MAP(ZMemoryAllocator, z_memory_allocator);
	ZCO_REGISTER_METHOD(allocate);
	ZCO_REGISTER_METHOD(allocate_aligned);
	ZCO_REGISTER_METHOD(get_usable_size);
	ZCO_REGISTER_METHOD(resize);
	ZCO_REGISTER_METHOD(deallocate);
	ZCO_REGISTER_METHOD(deallocate_by_size);
	ZCO_REGISTER_METHOD(garbage_collect);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
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
	ZCO_INIT_START(ZMemoryAllocator, z_memory_allocator);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
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
{
 if (selfp->object_tracker)
 z_object_ref(Z_OBJECT(selfp->object_tracker));

 return selfp->object_tracker;
 }
}
void z_memory_allocator_set_object_tracker(Self *self, ZObjectTracker * value)
{
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
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__allocate(self,size);
}
}
static void *  z_memory_allocator_virtual_allocate(Self *self,int size)
{
 return 0; /* not handled */
 }
void *  z_memory_allocator_allocate_aligned(Self *self,int size,int alignment)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__allocate_aligned(self,size,alignment);
}
}
static void *  z_memory_allocator_virtual_allocate_aligned(Self *self,int size,int alignment)
{
 return 0; /* not handled */
 }
int  z_memory_allocator_get_usable_size(Self *self,void *block)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__get_usable_size(self,block);
}
}
static int  z_memory_allocator_virtual_get_usable_size(Self *self,void *block)
{
 return -1; /* not handled */
 }
void *  z_memory_allocator_resize(Self *self,void *block,int new_size)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__resize(self,block,new_size);
}
}
static void *  z_memory_allocator_virtual_resize(Self *self,void *block,int new_size)
{
 return 0; /* not handled */
 }
void  z_memory_allocator_deallocate(Self *self,void *block)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__deallocate(self,block);
}
}
static void  z_memory_allocator_virtual_deallocate(Self *self,void *block)
{
 return; /* not handled */
 }
void  z_memory_allocator_deallocate_by_size(Self *self,void *block,int size)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__deallocate_by_size(self,block,size);
}
}
static void  z_memory_allocator_virtual_deallocate_by_size(Self *self,void *block,int size)
{
 deallocate(self, block);
 }
int  z_memory_allocator_garbage_collect(Self *self)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__garbage_collect(self);
}
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
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

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



