/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector.h: Bootstrap file for z-vector.zco
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

#ifndef _Z_VECTOR_H_
#define _Z_VECTOR_H_
#line 7 "z-vector.zco"

#include <z-object.h>
#include <z-vector-iter.h>
#include <z-vector-segment.h>

typedef void(*ZVectorItemCallback)(void *item, void *userdata);

#include <zco-type.h>
#define Self ZVector
#define Z_VECTOR(s) ((ZVector *) ((char *) (s) + (s)->_global->vtable_off_list[z_vector_type_id]))


struct ZVectorPrivate;
struct ZVectorProtected;
struct ZVectorGlobal;
struct ZVectorClass;
struct ZVector;

typedef struct ZVectorPrivate ZVectorPrivate;
typedef struct ZVectorProtected ZVectorProtected;
typedef struct ZVectorGlobal ZVectorGlobal;
typedef struct ZVectorClass ZVectorClass;
typedef struct ZVector ZVector;

struct ZVectorPrivate {
#line 18 "z-vector.zco"
	int item_size;
#line 19 "z-vector.zco"
	int count;
#line 20 "z-vector.zco"
	int storage_mode;
#line 21 "z-vector.zco"
	int is_insert_only_mode;
#line 22 "z-vector.zco"
	ZVectorSegment *head;
#line 23 "z-vector.zco"
	ZVectorSegment *tail;
#line 24 "z-vector.zco"
	void *userdata;
#line 25 "z-vector.zco"
	ZVectorItemCallback item_construct;
#line 26 "z-vector.zco"
	ZVectorItemCallback item_copy_construct;
#line 27 "z-vector.zco"
	ZVectorItemCallback item_destruct;
};

struct ZVectorProtected {
};

struct ZVectorGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	int is_object;
	struct ZVectorClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
#line 43 "z-vector.zco"
	void  (*__parent_reset)(ZObject *object);
#line 69 "z-vector.zco"
	void  (*__parent_dispose)(ZObject *object);
};

struct ZVectorClass {
	struct ZObjectClass parent_z_object;
};

struct ZVector {
	struct ZObject parent_z_object;
	struct ZVectorGlobal *_global;
	struct ZVectorPrivate _priv;
	struct ZVectorProtected _prot;
};
extern int z_vector_type_id;
ZVectorGlobal * z_vector_get_type(struct zco_context_t *ctx);
void __z_vector_init(struct zco_context_t *ctx, ZVector *self);
void __z_vector_class_init(struct zco_context_t *ctx, ZVectorClass *_class);
#line 86 "z-vector.zco"
Self * z_vector_new(struct zco_context_t *ctx);
#line 94 "z-vector.zco"
void z_vector_set_item_size(Self *self, int  value);
#line 108 "z-vector.zco"
void z_vector_set_is_insert_only_mode(Self *self, int  value);
#line 119 "z-vector.zco"
void z_vector_set_item_construct(Self *self, ZVectorItemCallback  value);
#line 130 "z-vector.zco"
void z_vector_set_item_copy_construct(Self *self, ZVectorItemCallback  value);
#line 142 "z-vector.zco"
void z_vector_set_item_destruct(Self *self, ZVectorItemCallback  value);
#line 152 "z-vector.zco"
void z_vector_set_userdata(Self *self, void *  value);
#line 161 "z-vector.zco"
ZVectorIter *  z_vector_get_begin(Self *self);
#line 175 "z-vector.zco"
ZVectorIter *  z_vector_get_end(Self *self);
#line 193 "z-vector.zco"
int  z_vector_get_size(Self *self);
#line 197 "z-vector.zco"
void z_vector_set_size(Self *self, int  value);
#line 264 "z-vector.zco"
int  z_vector_get_is_empty(Self *self);
#line 272 "z-vector.zco"
void *  z_vector_get_item(Self *self,ZVectorIter *iter);
#line 283 "z-vector.zco"
int  z_vector_set_item(Self *self,ZVectorIter *iter,void *item);
#line 295 "z-vector.zco"
void *  z_vector_get_front(Self *self);
#line 303 "z-vector.zco"
void z_vector_set_front(Self *self, void *  value);
#line 315 "z-vector.zco"
void *  z_vector_get_back(Self *self);
#line 324 "z-vector.zco"
void z_vector_set_back(Self *self, void *  value);
#line 335 "z-vector.zco"
void  z_vector_push_back(Self *self,void *item);
#line 348 "z-vector.zco"
int  z_vector_pop_back(Self *self,void *item);
#line 391 "z-vector.zco"
int  z_vector_insert(Self *self,ZVectorIter *iter,int n,void *item);
#line 473 "z-vector.zco"
int  z_vector_insert_range(Self *self,ZVectorIter *iter,ZVector *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end);
#line 813 "z-vector.zco"
int  z_vector_erase(Self *self,ZVectorIter *start,ZVectorIter *end);
#line 893 "z-vector.zco"
int  z_vector_erase1(Self *self,ZVectorIter *iter);
#line 909 "z-vector.zco"
int  z_vector_erase1_increment(Self *self,ZVectorIter *iter);
#line 935 "z-vector.zco"
int  z_vector_clear(Self *self);

#undef Self


#endif
