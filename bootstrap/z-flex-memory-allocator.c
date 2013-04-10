/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-flex-memory-allocator.c: Bootstrap file for z-flex-memory-allocator.zco
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



#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-flex-memory-allocator.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZFlexMemoryAllocator
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_flex_memory_allocator_new(ctx,allocator)
#define INIT_EXISTS
#define init z_flex_memory_allocator_init
#define new z_flex_memory_allocator_new

int z_flex_memory_allocator_type_id = -1;

static Self *__z_flex_memory_allocator_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_flex_memory_allocator_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_flex_memory_allocator_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_flex_memory_allocator_init(Self *self);
static void  z_flex_memory_allocator_dispose(ZObject *object);
static void *  z_flex_memory_allocator_allocate(ZMemoryAllocator *allocator,int size);
static void *  z_flex_memory_allocator_allocate_aligned(ZMemoryAllocator *allocator,int size,int alignment);
static int  z_flex_memory_allocator_try_resize(ZMemoryAllocator *allocator,void *block,int new_size);
static void *  z_flex_memory_allocator_resize(ZMemoryAllocator *allocator,void *block,int new_size);
static void  z_flex_memory_allocator_deallocate(ZMemoryAllocator *allocator,void *block);
static void z_flex_memory_allocator_class_destroy(ZObjectGlobal *gbl);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZFlexMemoryAllocatorGlobal * z_flex_memory_allocator_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_flex_memory_allocator_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_flex_memory_allocator_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZFlexMemoryAllocatorGlobal *global = (ZFlexMemoryAllocatorGlobal *) malloc(sizeof(struct ZFlexMemoryAllocatorGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZFlexMemoryAllocatorClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZFlexMemoryAllocatorClass));
		global->common.name = "ZFlexMemoryAllocator";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZFlexMemoryAllocator temp;
		struct ZFlexMemoryAllocatorClass temp_class;

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
		if (z_flex_memory_allocator_type_id == -1)
			z_flex_memory_allocator_type_id = zco_allocate_type_id();
		global->common.id = z_flex_memory_allocator_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_flex_memory_allocator_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_flex_memory_allocator_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_flex_memory_allocator_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_flex_memory_allocator_dispose;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_allocate = p_class->__allocate;
			p_class->__allocate = z_flex_memory_allocator_allocate;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_allocate_aligned = p_class->__allocate_aligned;
			p_class->__allocate_aligned = z_flex_memory_allocator_allocate_aligned;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_try_resize = p_class->__try_resize;
			p_class->__try_resize = z_flex_memory_allocator_try_resize;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_resize = p_class->__resize;
			p_class->__resize = z_flex_memory_allocator_resize;
		}
		{
			ZMemoryAllocatorClass *p_class = (ZMemoryAllocatorClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_memory_allocator_type_id]);
			global->__parent_deallocate = p_class->__deallocate;
			p_class->__deallocate = z_flex_memory_allocator_deallocate;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_flex_memory_allocator_class_destroy;
		}
		__z_flex_memory_allocator_class_init(ctx, (ZFlexMemoryAllocatorClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZFlexMemoryAllocatorGlobal *) global);
		#endif
		return global;
	}
	return (ZFlexMemoryAllocatorGlobal *) *global_ptr;
}

void __z_flex_memory_allocator_class_init(struct zco_context_t *ctx, ZFlexMemoryAllocatorClass *_class)
{
	__z_memory_allocator_class_init(ctx, (ZMemoryAllocatorClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_flex_memory_allocator_init(struct zco_context_t *ctx, Self *self)
{
	struct ZFlexMemoryAllocatorGlobal *_global = z_flex_memory_allocator_get_type(ctx);
	self->_global = _global;
	__z_memory_allocator_init(ctx, (ZMemoryAllocator *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_flex_memory_allocator_init(Self *self)
{
 }
Self * z_flex_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_flex_memory_allocator_dispose(ZObject *object)
{
 Self *self = (Self *) object;
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_allocate
static void *  z_flex_memory_allocator_allocate(ZMemoryAllocator *allocator,int size)
{
 return malloc(size);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_allocate_aligned
static void *  z_flex_memory_allocator_allocate_aligned(ZMemoryAllocator *allocator,int size,int alignment)
{
 return NULL;
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_try_resize
static int  z_flex_memory_allocator_try_resize(ZMemoryAllocator *allocator,void *block,int new_size)
{
 return -1;
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_resize
static void *  z_flex_memory_allocator_resize(ZMemoryAllocator *allocator,void *block,int new_size)
{
 return realloc(block, new_size);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_deallocate
static void  z_flex_memory_allocator_deallocate(ZMemoryAllocator *allocator,void *block)
{
 free(block);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_flex_memory_allocator_class_destroy(ZObjectGlobal *gbl)
{
	ZFlexMemoryAllocatorGlobal *_global = (ZFlexMemoryAllocatorGlobal *) gbl;

}

#undef PARENT_HANDLER



