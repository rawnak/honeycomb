/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector-iter.h: Bootstrap file for z-vector-iter.zco
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

#ifndef _Z_VECTOR_ITER_H_
#define _Z_VECTOR_ITER_H_

#include <z-object.h>

#include <zco-type.h>
#define Self ZVectorIter
#define Z_VECTOR_ITER(s) ((ZVectorIter *) (s))


struct ZVectorIterPrivate;
struct ZVectorIterProtected;
struct ZVectorIterGlobal;
struct ZVectorIterClass;
struct ZVectorIter;

typedef struct ZVectorIterPrivate ZVectorIterPrivate;
typedef struct ZVectorIterProtected ZVectorIterProtected;
typedef struct ZVectorIterGlobal ZVectorIterGlobal;
typedef struct ZVectorIterClass ZVectorIterClass;
typedef struct ZVectorIter ZVectorIter;

struct ZVectorIterPrivate {
	int index;
};

struct ZVectorIterProtected {
};

struct ZVectorIterGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZVectorIterClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
};

struct ZVectorIterClass {
	struct ZObjectClass parent_z_object;
};

struct ZVectorIter {
	struct ZObject parent_z_object;
	struct ZVectorIterGlobal *_global;
	struct ZVectorIterPrivate _priv;
	struct ZVectorIterProtected _prot;
};
extern int z_vector_iter_type_id;
ZVectorIterGlobal * z_vector_iter_get_type(struct zco_context_t *ctx);
void __z_vector_iter_init(struct zco_context_t *ctx, ZVectorIter *self);
Self * z_vector_iter_new(struct zco_context_t *ctx);
Self * z_vector_iter_dup(ZVectorIter *src);
int  z_vector_iter_get_index(Self *self);
void z_vector_iter_set_index(Self *self, int  value);
void  z_vector_iter_advance(Self *self,int steps);
void  z_vector_iter_increment(Self *self);
void  z_vector_iter_decrement(Self *self);
int  z_vector_iter_is_equal(Self *self,Self *other);
int  z_vector_iter_is_lte(Self *self,Self *other);
int  z_vector_iter_is_gte(Self *self,Self *other);

#undef Self


#endif
