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

#include <z-object.h>
#include <z-vector-iter.h>
#include <z-vector-segment.h>

typedef void(*ZVectorItemCallback)(void *item, void *userdata);

#include <zco-type.h>
#define Self ZVector
#define Z_VECTOR(s) ((ZVector *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_vector_type_id]))


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
	int item_size;
	int count;
	int storage_mode;
	int is_insert_only_mode;
	ZVectorSegment *head;
	ZVectorSegment *tail;
	void *userdata;
	ZVectorItemCallback item_construct;
	ZVectorItemCallback item_copy_construct;
	ZVectorItemCallback item_destruct;
};

struct ZVectorProtected {
};

struct ZVectorGlobal {
	struct ZCommonGlobal common;
	struct ZVectorClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
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
Self * z_vector_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
int  z_vector_get_item_size(Self *self);
void z_vector_set_item_size(Self *self, int  value);
void z_vector_set_is_insert_only_mode(Self *self, int  value);
void z_vector_set_item_construct(Self *self, ZVectorItemCallback  value);
void z_vector_set_item_copy_construct(Self *self, ZVectorItemCallback  value);
void z_vector_set_item_destruct(Self *self, ZVectorItemCallback  value);
void z_vector_set_userdata(Self *self, void *  value);
ZVectorIter *  z_vector_get_begin(Self *self);
ZVectorIter *  z_vector_get_end(Self *self);
int  z_vector_get_size(Self *self);
void z_vector_set_size(Self *self, int  value);
int  z_vector_get_is_empty(Self *self);
void *  z_vector_get_item(Self *self,ZVectorIter *iter);
int  z_vector_set_item(Self *self,ZVectorIter *iter,void *item);
void *  z_vector_get_front(Self *self);
void z_vector_set_front(Self *self, void *  value);
void *  z_vector_get_back(Self *self);
void z_vector_set_back(Self *self, void *  value);
void  z_vector_push_back(Self *self,void *item);
int  z_vector_pop_back(Self *self,void *item);
int  z_vector_insert(Self *self,ZVectorIter *iter,int n,void *item);
int  z_vector_insert_range(Self *self,ZVectorIter *iter,ZVector *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end);
int  z_vector_erase(Self *self,ZVectorIter *start,ZVectorIter *end);
int  z_vector_erase1(Self *self,ZVectorIter *iter);
int  z_vector_erase1_increment(Self *self,ZVectorIter *iter);
int  z_vector_clear(Self *self);

#undef Self


#endif
