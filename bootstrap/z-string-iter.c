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

#line 6 "z-string-iter.zco"


#include <z-map.h>
#include <string.h>
#include <z-string-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZStringIter
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_string_iter_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 12 "z-string-iter.zco"
#define init z_string_iter_init
#line 17 "z-string-iter.zco"
#define new z_string_iter_new
#line 23 "z-string-iter.zco"
#define dup z_string_iter_dup
#line 33 "z-string-iter.zco"
#define get_index z_string_iter_get_index
#line 37 "z-string-iter.zco"
#define set_index z_string_iter_set_index
#line 43 "z-string-iter.zco"
#define advance z_string_iter_advance
#line 48 "z-string-iter.zco"
#define increment z_string_iter_increment
#line 53 "z-string-iter.zco"
#define decrement z_string_iter_decrement
#line 58 "z-string-iter.zco"
#define is_equal z_string_iter_is_equal
#line 63 "z-string-iter.zco"
#define is_lte z_string_iter_is_lte
#line 68 "z-string-iter.zco"
#define is_gte z_string_iter_is_gte

int z_string_iter_type_id = -1;

static Self *__z_string_iter_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_string_iter_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 12 "z-string-iter.zco"
static void z_string_iter_init(Self *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZStringIterGlobal * z_string_iter_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_string_iter_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_string_iter_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZStringIterGlobal *global = (ZStringIterGlobal *) malloc(sizeof(struct ZStringIterGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZStringIterClass));
		memset(global->_class, 0, sizeof(struct ZStringIterClass));
		global->name = "ZStringIter";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZStringIter temp;
		unsigned long offset = 0;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
			if (0 == class_off_size) {
				class_off_size = p_class->id + 1;
				((ZObjectClass *) global->_class)->class_off_list = malloc(sizeof(unsigned long) * class_off_size);
			} else if (p_class->id >= class_off_size) {
				class_off_size = p_class->id + 1;
				((ZObjectClass *) global->_class)->class_off_list = realloc(((ZObjectClass *) global->_class)->class_off_list, sizeof(unsigned long) * class_off_size);
			}
			((ZObjectClass *) global->_class)->class_off_list[p_class->id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		if (z_string_iter_type_id == -1)
			z_string_iter_type_id = zco_allocate_type_id();
		global->id = z_string_iter_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_string_iter_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_string_iter_type_id);
		*global_ptr = global;
		
		__z_string_iter_class_init(ctx, (ZStringIterClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 17 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 23 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("dup"), (ZObjectSignalHandler) dup);
#line 43 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("advance"), (ZObjectSignalHandler) advance);
#line 48 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("increment"), (ZObjectSignalHandler) increment);
#line 53 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("decrement"), (ZObjectSignalHandler) decrement);
#line 58 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_equal"), (ZObjectSignalHandler) is_equal);
#line 63 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_lte"), (ZObjectSignalHandler) is_lte);
#line 68 "z-string-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_gte"), (ZObjectSignalHandler) is_gte);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZStringIterGlobal *) global);
		#endif
		return global;
	}
	return (ZStringIterGlobal *) *global_ptr;
}

void __z_string_iter_class_init(struct zco_context_t *ctx, ZStringIterClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_string_iter_init(struct zco_context_t *ctx, Self *self)
{
	struct ZStringIterGlobal *_global = z_string_iter_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 12 "z-string-iter.zco"
static void z_string_iter_init(Self *self)
{
 selfp->index = 0;
 }
#line 17 "z-string-iter.zco"
Self * z_string_iter_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 23 "z-string-iter.zco"
Self * z_string_iter_dup(ZStringIter *src)
{
 Self *self = GET_NEW(src->_global->ctx);
 
 set_index(self, get_index(src));
 return self;
 }
#line 33 "z-string-iter.zco"
int  z_string_iter_get_index(Self *self)
{
 return selfp->index;
 }
#line 37 "z-string-iter.zco"
void z_string_iter_set_index(Self *self, int  value)
{
 selfp->index = value;
 }
#line 43 "z-string-iter.zco"
void  z_string_iter_advance(Self *self,int steps)
{
 selfp->index += steps;
 }
#line 48 "z-string-iter.zco"
void  z_string_iter_increment(Self *self)
{
 ++selfp->index;
 }
#line 53 "z-string-iter.zco"
void  z_string_iter_decrement(Self *self)
{
 --selfp->index;
 }
#line 58 "z-string-iter.zco"
int  z_string_iter_is_equal(Self *self,Self *other)
{
 return selfp->index == get_index(other);
 }
#line 63 "z-string-iter.zco"
int  z_string_iter_is_lte(Self *self,Self *other)
{
 return selfp->index <= get_index(other);
 }
#line 68 "z-string-iter.zco"
int  z_string_iter_is_gte(Self *self,Self *other)
{
 return selfp->index >= get_index(other);
 }

#line 72 "z-string-iter.zco"


