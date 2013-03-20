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
#include <z-map-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZMapIter
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_map_iter_new(ctx)
#define INIT_EXISTS
#line 12 "z-map-iter.zco"
#define init z_map_iter_init
#line 24 "z-map-iter.zco"
#define new z_map_iter_new
#line 30 "z-map-iter.zco"
#define dup z_map_iter_dup
#line 40 "z-map-iter.zco"
#define get_index z_map_iter_get_index
#line 44 "z-map-iter.zco"
#define set_index z_map_iter_set_index
#line 50 "z-map-iter.zco"
#define advance z_map_iter_advance
#line 55 "z-map-iter.zco"
#define increment z_map_iter_increment
#line 60 "z-map-iter.zco"
#define decrement z_map_iter_decrement
#line 65 "z-map-iter.zco"
#define is_equal z_map_iter_is_equal
#line 70 "z-map-iter.zco"
#define is_lte z_map_iter_is_lte
#line 75 "z-map-iter.zco"
#define is_gte z_map_iter_is_gte

int z_map_iter_type_id = -1;

static Self *__z_map_iter_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_map_iter_type_id);
	if (!self) {
		self = (Self *) malloc(sizeof(Self));
		__z_map_iter_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 12 "z-map-iter.zco"
static void z_map_iter_init(Self *self);
#line 17 "z-map-iter.zco"
static void  z_map_iter_reset(ZObject *object);
#line 79 "z-map-iter.zco"
static void z_map_iter_class_destroy(ZObjectGlobal *gbl);

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
		global->common.is_object = 1;

		struct ZMapIter temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			if (p_class->common.id > class_off_size)
				class_off_size = p_class->common.id;
		}
		class_off_list = malloc(sizeof(unsigned long) * (zco_get_type_count()+1));
		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_class->common.vtable_off_list,
				p_class->common.vtable_off_size,
				&temp,
				&temp.parent_z_object);
			memcpy((char *) CLASS_FROM_GLOBAL(global) + offset, CLASS_FROM_GLOBAL(p_class), sizeof(struct ZObjectClass));
			class_off_list[p_class->common.id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		((ZObjectClass *) CLASS_FROM_GLOBAL(global))->class_off_list = class_off_list;
		if (z_map_iter_type_id == -1)
			z_map_iter_type_id = zco_allocate_type_id();
		global->common.id = z_map_iter_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_map_iter_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_map_iter_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		class_off_list[global->common.id] = offset;
#line 17 "z-map-iter.zco"
		{
#line 17 "z-map-iter.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 17 "z-map-iter.zco"
			global->__parent_reset = p_class->__reset;
#line 17 "z-map-iter.zco"
			p_class->__reset = z_map_iter_reset;
#line 17 "z-map-iter.zco"
		}
#line 79 "z-map-iter.zco"
		{
#line 79 "z-map-iter.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 79 "z-map-iter.zco"
			global->__parent_class_destroy = p_class->__class_destroy;
#line 79 "z-map-iter.zco"
			p_class->__class_destroy = z_map_iter_class_destroy;
#line 79 "z-map-iter.zco"
		}
		__z_map_iter_class_init(ctx, (ZMapIterClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
#line 24 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 30 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("dup"), (ZObjectSignalHandler) dup);
#line 50 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("advance"), (ZObjectSignalHandler) advance);
#line 55 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("increment"), (ZObjectSignalHandler) increment);
#line 60 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("decrement"), (ZObjectSignalHandler) decrement);
#line 65 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("is_equal"), (ZObjectSignalHandler) is_equal);
#line 70 "z-map-iter.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("is_lte"), (ZObjectSignalHandler) is_lte);
#line 75 "z-map-iter.zco"
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
#line 12 "z-map-iter.zco"
static void z_map_iter_init(Self *self)
{
 selfp->index = 0;
 }
#line 17 "z-map-iter.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_map_iter_reset(ZObject *object)
{
 Self *self = (Self *) object;
 selfp->index = 0;
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 24 "z-map-iter.zco"
Self * z_map_iter_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 30 "z-map-iter.zco"
Self * z_map_iter_dup(ZMapIter *src)
{
 Self *self = GET_NEW(CTX_FROM_OBJECT(src));

 set_index(self, get_index(src));
 return self;
 }
#line 40 "z-map-iter.zco"
int  z_map_iter_get_index(Self *self)
{
 return selfp->index;
 }
#line 44 "z-map-iter.zco"
void z_map_iter_set_index(Self *self, int  value)
{
 selfp->index = value;
 }
#line 50 "z-map-iter.zco"
void  z_map_iter_advance(Self *self,int steps)
{
 selfp->index += steps;
 }
#line 55 "z-map-iter.zco"
void  z_map_iter_increment(Self *self)
{
 ++selfp->index;
 }
#line 60 "z-map-iter.zco"
void  z_map_iter_decrement(Self *self)
{
 --selfp->index;
 }
#line 65 "z-map-iter.zco"
int  z_map_iter_is_equal(Self *self,Self *other)
{
 return selfp->index == get_index(other);
 }
#line 70 "z-map-iter.zco"
int  z_map_iter_is_lte(Self *self,Self *other)
{
 return selfp->index <= get_index(other);
 }
#line 75 "z-map-iter.zco"
int  z_map_iter_is_gte(Self *self,Self *other)
{
 return selfp->index >= get_index(other);
 }
#line 79 "z-map-iter.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_map_iter_class_destroy(ZObjectGlobal *gbl)
{
	ZMapIterGlobal *_global = (ZMapIterGlobal *) gbl;

}

#undef PARENT_HANDLER

#line 79 "z-map-iter.zco"


