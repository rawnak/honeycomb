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
#line 3 "z-vector-iter.zco"

#include <z-object.h>

#include <zco-type.h>
#define Self ZVectorIter
#define Z_VECTOR_ITER(s) ((ZVectorIter *) ((char *) (s) + (s)->_global->vtable_off_list[z_vector_iter_type_id]))


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
#line 10 "z-vector-iter.zco"
	int index;
};

struct ZVectorIterProtected {
};

struct ZVectorIterGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	int is_object;
	struct ZVectorIterClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
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
void __z_vector_iter_class_init(struct zco_context_t *ctx, ZVectorIterClass *_class);
#line 17 "z-vector-iter.zco"
Self * z_vector_iter_new(struct zco_context_t *ctx);
#line 23 "z-vector-iter.zco"
Self * z_vector_iter_dup(ZVectorIter *src);
#line 33 "z-vector-iter.zco"
int  z_vector_iter_get_index(Self *self);
#line 37 "z-vector-iter.zco"
void z_vector_iter_set_index(Self *self, int  value);
#line 43 "z-vector-iter.zco"
void  z_vector_iter_advance(Self *self,int steps);
#line 48 "z-vector-iter.zco"
void  z_vector_iter_increment(Self *self);
#line 53 "z-vector-iter.zco"
void  z_vector_iter_decrement(Self *self);
#line 58 "z-vector-iter.zco"
int  z_vector_iter_is_equal(Self *self,Self *other);
#line 63 "z-vector-iter.zco"
int  z_vector_iter_is_lte(Self *self,Self *other);
#line 68 "z-vector-iter.zco"
int  z_vector_iter_is_gte(Self *self,Self *other);

#undef Self


#endif
