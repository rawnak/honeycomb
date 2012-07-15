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



#include <string.h>
#include <z-map-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZMapIter
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_map_iter_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#define init z_map_iter_init
#define new z_map_iter_new
#define dup z_map_iter_dup
#define get_index z_map_iter_get_index
#define set_index z_map_iter_set_index
#define advance z_map_iter_advance
#define increment z_map_iter_increment
#define decrement z_map_iter_decrement
#define is_equal z_map_iter_is_equal
#define is_lte z_map_iter_is_lte
#define is_gte z_map_iter_is_gte

int z_map_iter_type_id = -1;

static Self *__z_map_iter_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_map_iter_init(ctx, self);
	return self;
}
static void z_map_iter_init(Self *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZMapIterGlobal * z_map_iter_get_type(struct zco_context_t *ctx)
{
	if (z_map_iter_type_id == -1)
		z_map_iter_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_map_iter_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZMapIterGlobal));
		struct ZMapIterGlobal *global = (ZMapIterGlobal *) *global_ptr;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZMapIterClass));
		memset(global->_class, 0, sizeof(struct ZMapIterClass));
		global->name = "ZMapIter";
		global->id = z_map_iter_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZMapIterClass temp;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			unsigned long offset = global->vtable_off_list[z_object_type_id];
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
		}
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_map_iter_type_id);		
		__z_map_iter_class_init(ctx, (ZMapIterClass *) &temp);
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
	z_object_register_method(ctx, (ZObjectClass *) _class, "new", (ZObjectSignalHandler) new);
	z_object_register_method(ctx, (ZObjectClass *) _class, "dup", (ZObjectSignalHandler) dup);
	z_object_register_method(ctx, (ZObjectClass *) _class, "advance", (ZObjectSignalHandler) advance);
	z_object_register_method(ctx, (ZObjectClass *) _class, "increment", (ZObjectSignalHandler) increment);
	z_object_register_method(ctx, (ZObjectClass *) _class, "decrement", (ZObjectSignalHandler) decrement);
	z_object_register_method(ctx, (ZObjectClass *) _class, "is_equal", (ZObjectSignalHandler) is_equal);
	z_object_register_method(ctx, (ZObjectClass *) _class, "is_lte", (ZObjectSignalHandler) is_lte);
	z_object_register_method(ctx, (ZObjectClass *) _class, "is_gte", (ZObjectSignalHandler) is_gte);
}
void __z_map_iter_init(struct zco_context_t *ctx, Self *self)
{
	struct ZMapIterGlobal *_global = z_map_iter_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, Z_OBJECT(self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_map_iter_init(Self *self)
{
 selfp->index = 0;
 }
Self * z_map_iter_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
Self * z_map_iter_dup(ZMapIter *src)
{
 Self *self = GET_NEW(src->_global->ctx);

 set_index(self, get_index(src));
 return self;
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



