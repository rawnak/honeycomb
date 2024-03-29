/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-string-iter.h: Bootstrap file for z-string-iter.zco
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

#ifndef _Z_STRING_ITER_H_
#define _Z_STRING_ITER_H_

#include <z-object.h>

#include <zco-context.h>
#define Self ZStringIter
#define Z_STRING_ITER(s) ((ZStringIter *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_string_iter_type_id]))


ZCO_TYPEDEF_FWD_DECL_CLASS(ZStringIter);

struct ZStringIterPrivate {
	int index;
};

struct ZStringIterProtected {
};

struct ZStringIterGlobal {
	ZCO_CLASS_GLOBAL_HEAD(ZStringIter);
	void  (*__parent_reset)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZStringIterClass {
	struct ZObjectClass parent_z_object;
};

struct ZStringIter {
	struct ZObject parent_z_object;
	ZCO_CLASS_PUBLIC_HEAD(ZStringIter);
};
extern int z_string_iter_type_id;
ZStringIterGlobal * z_string_iter_get_type(struct zco_context_t *ctx);
void __z_string_iter_init(struct zco_context_t *ctx, ZStringIter *self);
void __z_string_iter_class_init(struct zco_context_t *ctx, ZStringIterClass *_class);
Self * z_string_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
Self * z_string_iter_dup(ZStringIter *src);
void  z_string_iter_assign(Self *self,ZStringIter *src);
int  z_string_iter_get_index(Self *self);
void z_string_iter_set_index(Self *self, int  value);
void  z_string_iter_advance(Self *self,int steps);
void  z_string_iter_increment(Self *self);
void  z_string_iter_decrement(Self *self);
int  z_string_iter_is_equal(Self *self,Self *other);
int  z_string_iter_is_lte(Self *self,Self *other);
int  z_string_iter_is_gte(Self *self,Self *other);

#undef Self


#endif
