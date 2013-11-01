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

struct ZVectorSegment;
typedef struct ZVectorSegment ZVectorSegment;

#include <zco-context.h>
#define Self ZVectorIter
#define Z_VECTOR_ITER(s) ((ZVectorIter *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_vector_iter_type_id]))


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
	int absolute_index;
	ZVectorSegment *segment;
};

struct ZVectorIterProtected {
};

struct ZVectorIterGlobal {
	struct ZCommonGlobal common;
	struct ZVectorIterClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
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
Self * z_vector_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
Self * z_vector_iter_dup(ZVectorIter *src);
ZVectorSegment * z_vector_iter_get_segment(Self *self);
void z_vector_iter_set_segment(Self *self, ZVectorSegment * value);
int  z_vector_iter_get_absolute_index(Self *self);
void z_vector_iter_set_absolute_index(Self *self, int  value);
int  z_vector_iter_get_index(Self *self);
void z_vector_iter_set_index(Self *self, int  value);
void  z_vector_iter_assign(Self *self,ZVectorIter *src);
void  z_vector_iter_advance(Self *self,int steps);
void  z_vector_iter_increment(Self *self);
void  z_vector_iter_decrement(Self *self);
int  z_vector_iter_is_equal(Self *self,Self *other);
int  z_vector_iter_is_lte(Self *self,Self *other);
int  z_vector_iter_is_gte(Self *self,Self *other);
int  z_vector_iter_is_in_bound(ZVectorIter *self);

#undef Self


#endif
