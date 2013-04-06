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

#line 6 "z-memory-allocator.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZMemoryAllocator
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_memory_allocator_new(ctx,allocator)
#line 10 "z-memory-allocator.zco"
#define allocate z_memory_allocator_allocate
#line 15 "z-memory-allocator.zco"
#define allocate_aligned z_memory_allocator_allocate_aligned
#line 20 "z-memory-allocator.zco"
#define try_resize z_memory_allocator_try_resize
#line 25 "z-memory-allocator.zco"
#define resize z_memory_allocator_resize
#line 30 "z-memory-allocator.zco"
#define deallocate z_memory_allocator_deallocate

int z_memory_allocator_type_id = -1;

static Self *__z_memory_allocator_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_memory_allocator_type_id);
	if (!self) {
		self = (Self *) malloc(sizeof(Self));
		__z_memory_allocator_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 10 "z-memory-allocator.zco"
static void *  z_memory_allocator_virtual_allocate(Self *self,int size);
#line 15 "z-memory-allocator.zco"
static void *  z_memory_allocator_virtual_allocate_aligned(Self *self,int size,int alignment);
#line 20 "z-memory-allocator.zco"
static int  z_memory_allocator_virtual_try_resize(Self *self,void *block,int new_size);
#line 25 "z-memory-allocator.zco"
static void *  z_memory_allocator_virtual_resize(Self *self,void *block,int new_size);
#line 30 "z-memory-allocator.zco"
static void  z_memory_allocator_virtual_deallocate(Self *self,void *block);

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
		global->common.is_object = 0;

		struct ZMemoryAllocator temp;
		unsigned long offset = 0;

		if (z_memory_allocator_type_id == -1)
			z_memory_allocator_type_id = zco_allocate_type_id();
		global->common.id = z_memory_allocator_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_memory_allocator_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_memory_allocator_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
#line 10 "z-memory-allocator.zco"
		CLASS_FROM_GLOBAL(global)->__allocate = z_memory_allocator_virtual_allocate;
#line 15 "z-memory-allocator.zco"
		CLASS_FROM_GLOBAL(global)->__allocate_aligned = z_memory_allocator_virtual_allocate_aligned;
#line 20 "z-memory-allocator.zco"
		CLASS_FROM_GLOBAL(global)->__try_resize = z_memory_allocator_virtual_try_resize;
#line 25 "z-memory-allocator.zco"
		CLASS_FROM_GLOBAL(global)->__resize = z_memory_allocator_virtual_resize;
#line 30 "z-memory-allocator.zco"
		CLASS_FROM_GLOBAL(global)->__deallocate = z_memory_allocator_virtual_deallocate;
		__z_memory_allocator_class_init(ctx, (ZMemoryAllocatorClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
#line 10 "z-memory-allocator.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("allocate"), (ZObjectSignalHandler) allocate);
#line 15 "z-memory-allocator.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("allocate_aligned"), (ZObjectSignalHandler) allocate_aligned);
#line 20 "z-memory-allocator.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("try_resize"), (ZObjectSignalHandler) try_resize);
#line 25 "z-memory-allocator.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("resize"), (ZObjectSignalHandler) resize);
#line 30 "z-memory-allocator.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("deallocate"), (ZObjectSignalHandler) deallocate);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZMemoryAllocatorGlobal *) global);
		#endif
		return global;
	}
	return (ZMemoryAllocatorGlobal *) *global_ptr;
}

void __z_memory_allocator_class_init(struct zco_context_t *ctx, ZMemoryAllocatorClass *_class)
{
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_memory_allocator_init(struct zco_context_t *ctx, Self *self)
{
	struct ZMemoryAllocatorGlobal *_global = z_memory_allocator_get_type(ctx);
	self->_global = _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 10 "z-memory-allocator.zco"
void *  z_memory_allocator_allocate(Self *self,int size)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	unsigned long offset = class_base->class_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__allocate(self,size);
}
#line 10 "z-memory-allocator.zco"
static void *  z_memory_allocator_virtual_allocate(Self *self,int size)
{
 return 0; /* not handled */
 }
#line 15 "z-memory-allocator.zco"
void *  z_memory_allocator_allocate_aligned(Self *self,int size,int alignment)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	unsigned long offset = class_base->class_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__allocate_aligned(self,size,alignment);
}
#line 15 "z-memory-allocator.zco"
static void *  z_memory_allocator_virtual_allocate_aligned(Self *self,int size,int alignment)
{
 return 0; /* not handled */
 }
#line 20 "z-memory-allocator.zco"
int  z_memory_allocator_try_resize(Self *self,void *block,int new_size)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	unsigned long offset = class_base->class_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__try_resize(self,block,new_size);
}
#line 20 "z-memory-allocator.zco"
static int  z_memory_allocator_virtual_try_resize(Self *self,void *block,int new_size)
{
 return 0; /* not handled */
 }
#line 25 "z-memory-allocator.zco"
void *  z_memory_allocator_resize(Self *self,void *block,int new_size)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	unsigned long offset = class_base->class_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__resize(self,block,new_size);
}
#line 25 "z-memory-allocator.zco"
static void *  z_memory_allocator_virtual_resize(Self *self,void *block,int new_size)
{
 return 0; /* not handled */
 }
#line 30 "z-memory-allocator.zco"
void  z_memory_allocator_deallocate(Self *self,void *block)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	unsigned long offset = class_base->class_off_list[z_memory_allocator_type_id];
	((ZMemoryAllocatorClass *) ((char *) class_base + offset))->__deallocate(self,block);
}
#line 30 "z-memory-allocator.zco"
static void  z_memory_allocator_virtual_deallocate(Self *self,void *block)
{
 return 0; /* not handled */
 }

#line 34 "z-memory-allocator.zco"


