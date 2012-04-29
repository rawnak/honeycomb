/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector-iter.c: Bootstrap file for z-vector-iter.zco
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
#include <z-vector-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVectorIter
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_vector_iter_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 12 "z-vector-iter.zco"
#define init z_vector_iter_init
#line 17 "z-vector-iter.zco"
#define new z_vector_iter_new
#line 23 "z-vector-iter.zco"
#define dup z_vector_iter_dup
#line 33 "z-vector-iter.zco"
#define get_index z_vector_iter_get_index
#line 37 "z-vector-iter.zco"
#define set_index z_vector_iter_set_index
#line 43 "z-vector-iter.zco"
#define advance z_vector_iter_advance
#line 48 "z-vector-iter.zco"
#define increment z_vector_iter_increment
#line 53 "z-vector-iter.zco"
#define decrement z_vector_iter_decrement
#line 58 "z-vector-iter.zco"
#define is_equal z_vector_iter_is_equal
#line 63 "z-vector-iter.zco"
#define is_lte z_vector_iter_is_lte
#line 68 "z-vector-iter.zco"
#define is_gte z_vector_iter_is_gte

int z_vector_iter_type_id = -1;

static Self *__z_vector_iter_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_vector_iter_init(ctx, self);
	return self;
}
#line 12 "z-vector-iter.zco"
static void z_vector_iter_init(Self *self);

ZVectorIterGlobal * z_vector_iter_get_type(struct zco_context_t *ctx)
{
	if (z_vector_iter_type_id == -1)
		z_vector_iter_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_vector_iter_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZVectorIterGlobal));
		struct ZVectorIterGlobal *global = (ZVectorIterGlobal *) *global_ptr;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorIterClass));
		memset(global->_class, 0, sizeof(struct ZVectorIterClass));
		global->name = "ZVectorIter";
		global->id = z_vector_iter_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZVectorIterClass temp;

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
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_vector_iter_type_id);		
		#ifdef CLASS_INIT_EXISTS
			class_init((ZVectorIterGlobal *) global);
		#endif
	}
	return (ZVectorIterGlobal *) *global_ptr;
}

void __z_vector_iter_init(struct zco_context_t *ctx, Self *self)
{
	struct ZVectorIterGlobal *_global = z_vector_iter_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, Z_OBJECT(self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 12 "z-vector-iter.zco"
static void z_vector_iter_init(Self *self)
{
 selfp->index = 0;
 }
#line 17 "z-vector-iter.zco"
Self * z_vector_iter_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 23 "z-vector-iter.zco"
Self * z_vector_iter_dup(ZVectorIter *src)
{
 Self *self = GET_NEW(src->_global->ctx);

 set_index(self, get_index(src));
 return self;
 }
#line 33 "z-vector-iter.zco"
int  z_vector_iter_get_index(Self *self)
{
 return selfp->index;
 }
#line 37 "z-vector-iter.zco"
void z_vector_iter_set_index(Self *self, int  value)
{
 selfp->index = value;
 }
#line 43 "z-vector-iter.zco"
void  z_vector_iter_advance(Self *self,int steps)
{
 selfp->index += steps;
 }
#line 48 "z-vector-iter.zco"
void  z_vector_iter_increment(Self *self)
{
 ++selfp->index;
 }
#line 53 "z-vector-iter.zco"
void  z_vector_iter_decrement(Self *self)
{
 --selfp->index;
 }
#line 58 "z-vector-iter.zco"
int  z_vector_iter_is_equal(Self *self,Self *other)
{
 return selfp->index == get_index(other);
 }
#line 63 "z-vector-iter.zco"
int  z_vector_iter_is_lte(Self *self,Self *other)
{
 return selfp->index <= get_index(other);
 }
#line 68 "z-vector-iter.zco"
int  z_vector_iter_is_gte(Self *self,Self *other)
{
 return selfp->index >= get_index(other);
 }



