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

#include <zco-type.h>
#define Self ZStringIter
#define Z_STRING_ITER(s) ((ZStringIter *) (s))


struct ZStringIterPrivate;
struct ZStringIterProtected;
struct ZStringIterGlobal;
struct ZStringIterClass;
struct ZStringIter;

typedef struct ZStringIterPrivate ZStringIterPrivate;
typedef struct ZStringIterProtected ZStringIterProtected;
typedef struct ZStringIterGlobal ZStringIterGlobal;
typedef struct ZStringIterClass ZStringIterClass;
typedef struct ZStringIter ZStringIter;

struct ZStringIterPrivate {
	int index;
};

struct ZStringIterProtected {
};

struct ZStringIterGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZStringIterClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
};

struct ZStringIterClass {
	struct ZObjectClass parent_z_object;
};

struct ZStringIter {
	struct ZObject parent_z_object;
	struct ZStringIterGlobal *_global;
	struct ZStringIterPrivate _priv;
	struct ZStringIterProtected _prot;
};
extern int z_string_iter_type_id;
ZStringIterGlobal * z_string_iter_get_type(struct zco_context_t *ctx);
void __z_string_iter_init(struct zco_context_t *ctx, ZStringIter *self);
Self * z_string_iter_new(struct zco_context_t *ctx);
Self * z_string_iter_dup(ZStringIter *src);
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
