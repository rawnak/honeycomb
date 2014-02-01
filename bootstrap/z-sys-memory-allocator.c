/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-sys-memory-allocator.c: Bootstrap file for z-sys-memory-allocator.zco
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


#include <malloc.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-sys-memory-allocator-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZSysMemoryAllocator
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_sys_memory_allocator_new(ctx,allocator)
#define INIT_EXISTS
#define init z_sys_memory_allocator_init
#define new z_sys_memory_allocator_new

ZCO_DEFINE_CLASS_TYPE(z_sys_memory_allocator);

static void z_sys_memory_allocator_init(Self *self);
static void  z_sys_memory_allocator_dispose(ZObject *object);
static void *  z_sys_memory_allocator_allocate(ZMemoryAllocator *allocator,int size);
static void *  z_sys_memory_allocator_allocate_aligned(ZMemoryAllocator *allocator,int size,int alignment);
static int  z_sys_memory_allocator_get_usable_size(ZMemoryAllocator *allocator,void *block);
static void *  z_sys_memory_allocator_resize(ZMemoryAllocator *allocator,void *block,int new_size);
static void  z_sys_memory_allocator_deallocate(ZMemoryAllocator *allocator,void *block);
static void z_sys_memory_allocator_class_destroy(ZObjectGlobal *gbl);
static void z_sys_memory_allocator___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZSysMemoryAllocatorGlobal * z_sys_memory_allocator_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZSysMemoryAllocator, z_sys_memory_allocator, 1);
	ZCO_INHERIT_CLASS(ZMemoryAllocator, z_memory_allocator, ZSysMemoryAllocator);
	ZCO_REGISTER_TYPE(z_sys_memory_allocator);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_sys_memory_allocator, dispose);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZMemoryAllocator, z_memory_allocator, z_sys_memory_allocator, allocate);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZMemoryAllocator, z_memory_allocator, z_sys_memory_allocator, allocate_aligned);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZMemoryAllocator, z_memory_allocator, z_sys_memory_allocator, get_usable_size);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZMemoryAllocator, z_memory_allocator, z_sys_memory_allocator, resize);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZMemoryAllocator, z_memory_allocator, z_sys_memory_allocator, deallocate);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_sys_memory_allocator, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_sys_memory_allocator, __delete);
	ZCO_CREATE_METHOD_MAP(ZSysMemoryAllocator, z_sys_memory_allocator);
	ZCO_REGISTER_METHOD(new);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
}

void __z_sys_memory_allocator_class_init(struct zco_context_t *ctx, ZSysMemoryAllocatorClass *_class)
{
	__z_memory_allocator_class_init(ctx, (ZMemoryAllocatorClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_sys_memory_allocator_init(struct zco_context_t *ctx, Self *self)
{
	ZCO_INIT_START(ZSysMemoryAllocator, z_sys_memory_allocator);
	__z_memory_allocator_init(ctx, (ZMemoryAllocator *) (self));
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_sys_memory_allocator_init(Self *self)
{
 }
Self * z_sys_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_sys_memory_allocator_dispose(ZObject *object)
{
 Self *self = (Self *) object;
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_allocate
static void *  z_sys_memory_allocator_allocate(ZMemoryAllocator *allocator,int size)
{
 return malloc(size);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_allocate_aligned
static void *  z_sys_memory_allocator_allocate_aligned(ZMemoryAllocator *allocator,int size,int alignment)
{
 return NULL;
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_get_usable_size
static int  z_sys_memory_allocator_get_usable_size(ZMemoryAllocator *allocator,void *block)
{
 return malloc_usable_size(block);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_resize
static void *  z_sys_memory_allocator_resize(ZMemoryAllocator *allocator,void *block,int new_size)
{
 return realloc(block, new_size);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_deallocate
static void  z_sys_memory_allocator_deallocate(ZMemoryAllocator *allocator,void *block)
{
 free(block);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_sys_memory_allocator_class_destroy(ZObjectGlobal *gbl)
{
	ZSysMemoryAllocatorGlobal *_global = (ZSysMemoryAllocatorGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_sys_memory_allocator___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



