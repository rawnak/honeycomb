/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-string-iter.c: Bootstrap file for z-string-iter.zco
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
#include <z-string-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZStringIter
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_string_iter_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#define init z_string_iter_init
#define new z_string_iter_new
#define dup z_string_iter_dup
#define get_index z_string_iter_get_index
#define set_index z_string_iter_set_index
#define advance z_string_iter_advance
#define increment z_string_iter_increment
#define decrement z_string_iter_decrement
#define is_equal z_string_iter_is_equal
#define is_lte z_string_iter_is_lte
#define is_gte z_string_iter_is_gte

int z_string_iter_type_id = -1;
static ZStringIterGlobal * z_string_iter_global;

static Self *__z_string_iter_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_string_iter_init(ctx, self);
	return self;
}
static void z_string_iter_init(Self *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZStringIterGlobal * z_string_iter_get_type(struct zco_context_t *ctx)
{
	if (z_string_iter_type_id == -1)
		z_string_iter_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_string_iter_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZStringIterGlobal));
		struct ZStringIterGlobal *global = (ZStringIterGlobal *) *global_ptr;
		z_string_iter_global = global;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZStringIterClass));
		memset(global->_class, 0, sizeof(struct ZStringIterClass));
		global->name = "ZStringIter";
		global->id = z_string_iter_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZStringIterClass temp;

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
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_string_iter_type_id);		
		#ifdef CLASS_INIT_EXISTS
			class_init((ZStringIterGlobal *) global);
		#endif
	}
	return (ZStringIterGlobal *) *global_ptr;
}

void __z_string_iter_init(struct zco_context_t *ctx, Self *self)
{
	struct ZStringIterGlobal *_global = z_string_iter_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, Z_OBJECT(self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_string_iter_init(Self *self)
{
 selfp->index = 0;
 }
Self * z_string_iter_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
Self * z_string_iter_dup(ZStringIter *src)
{
 Self *self = GET_NEW(src->_global->ctx);
 
 set_index(self, get_index(src));
 return self;
 }
int  z_string_iter_get_index(Self *self)
{
 return selfp->index;
 }
void z_string_iter_set_index(Self *self, int  value)
{
 selfp->index = value;
 }
void  z_string_iter_advance(Self *self,int steps)
{
 selfp->index += steps;
 }
void  z_string_iter_increment(Self *self)
{
 ++selfp->index;
 }
void  z_string_iter_decrement(Self *self)
{
 --selfp->index;
 }
int  z_string_iter_is_equal(Self *self,Self *other)
{
 return selfp->index == get_index(other);
 }
int  z_string_iter_is_lte(Self *self,Self *other)
{
 return selfp->index <= get_index(other);
 }
int  z_string_iter_is_gte(Self *self,Self *other)
{
 return selfp->index >= get_index(other);
 }



