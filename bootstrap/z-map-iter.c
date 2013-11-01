/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-map-iter.c: Bootstrap file for z-map-iter.zco
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

#line 6 "z-map-iter.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-map-iter-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZMapIter
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_map_iter_new(ctx,allocator)
#define INIT_EXISTS
#define init z_map_iter_init
#define new z_map_iter_new
#define dup z_map_iter_dup
#define assign z_map_iter_assign
#define get_index z_map_iter_get_index
#define set_index z_map_iter_set_index
#define advance z_map_iter_advance
#define increment z_map_iter_increment
#define decrement z_map_iter_decrement
#define is_equal z_map_iter_is_equal
#define is_lte z_map_iter_is_lte
#define is_gte z_map_iter_is_gte

int z_map_iter_type_id = -1;

static Self *__z_map_iter_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_map_iter_type_id);
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
		__z_map_iter_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_map_iter_init(Self *self);
static void  z_map_iter_reset(ZObject *object);
static void z_map_iter_class_destroy(ZObjectGlobal *gbl);
static void z_map_iter___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZMapIterGlobal * z_map_iter_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_map_iter_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_map_iter_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZMapIterGlobal *global = (ZMapIterGlobal *) malloc(sizeof(struct ZMapIterGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZMapIterClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZMapIterClass));
		global->common.name = "ZMapIter";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZMapIter temp;
		struct ZMapIterClass temp_class;

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
		if (z_map_iter_type_id == -1)
			z_map_iter_type_id = zco_allocate_type_id();
		global->common.id = z_map_iter_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_map_iter_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_map_iter_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_map_iter_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_map_iter_reset;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_map_iter_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_map_iter___delete;
		}
		__z_map_iter_class_init(ctx, (ZMapIterClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		z_map_insert((ZMap *) global->common.method_map, strdup("dup"), (ZObjectSignalHandler) dup);
		z_map_insert((ZMap *) global->common.method_map, strdup("assign"), (ZObjectSignalHandler) assign);
		z_map_insert((ZMap *) global->common.method_map, strdup("advance"), (ZObjectSignalHandler) advance);
		z_map_insert((ZMap *) global->common.method_map, strdup("increment"), (ZObjectSignalHandler) increment);
		z_map_insert((ZMap *) global->common.method_map, strdup("decrement"), (ZObjectSignalHandler) decrement);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_equal"), (ZObjectSignalHandler) is_equal);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_lte"), (ZObjectSignalHandler) is_lte);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_gte"), (ZObjectSignalHandler) is_gte);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZMapIterGlobal *) global);
		#endif
		return global;
	}
	return (ZMapIterGlobal *) *global_ptr;
}

void __z_map_iter_class_init(struct zco_context_t *ctx, ZMapIterClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_map_iter_init(struct zco_context_t *ctx, Self *self)
{
	struct ZMapIterGlobal *_global = z_map_iter_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_map_iter_init(Self *self)
{
 selfp->index = 0;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_map_iter_reset(ZObject *object)
{
 Self *self = (Self *) object;
 selfp->index = 0;
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_map_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
Self * z_map_iter_dup(ZMapIter *src)
{
 Self *self = GET_NEW(CTX_FROM_OBJECT(src), ALLOCATOR_FROM_OBJECT(src));

 set_index(self, get_index(src));
 return self;
 }
void  z_map_iter_assign(Self *self,ZMapIter *src)
{
 set_index(self, get_index(src)); 
 }
int  z_map_iter_get_index(Self *self)
{
 return selfp->index;
 }
void z_map_iter_set_index(Self *self, int  value)
{
 selfp->index = value;
 }
void  z_map_iter_advance(Self *self,int steps)
{
 selfp->index += steps;
 }
void  z_map_iter_increment(Self *self)
{
 ++selfp->index;
 }
void  z_map_iter_decrement(Self *self)
{
 --selfp->index;
 }
int  z_map_iter_is_equal(Self *self,Self *other)
{
 return selfp->index == get_index(other);
 }
int  z_map_iter_is_lte(Self *self,Self *other)
{
 return selfp->index <= get_index(other);
 }
int  z_map_iter_is_gte(Self *self,Self *other)
{
 return selfp->index >= get_index(other);
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_map_iter_class_destroy(ZObjectGlobal *gbl)
{
	ZMapIterGlobal *_global = (ZMapIterGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_map_iter___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



