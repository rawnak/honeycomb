/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector-segment.h: Bootstrap file for z-vector-segment.zco
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

#ifndef _Z_VECTOR_SEGMENT_H_
#define _Z_VECTOR_SEGMENT_H_
#line 8 "z-vector-segment.zco"

#include <z-object.h>
#include <z-vector-iter.h>

struct ZVector;
typedef struct ZVector ZVector;
typedef void(*ZVectorItemCallback)(void *item, void *userdata);

#include <zco-type.h>
#define Self ZVectorSegment
#define Z_VECTOR_SEGMENT(s) ((ZVectorSegment *) ((char *) (s) + (s)->_global->vtable_off_list[z_vector_segment_type_id]))


struct ZVectorSegmentPrivate;
struct ZVectorSegmentProtected;
struct ZVectorSegmentGlobal;
struct ZVectorSegmentClass;
struct ZVectorSegment;

typedef struct ZVectorSegmentPrivate ZVectorSegmentPrivate;
typedef struct ZVectorSegmentProtected ZVectorSegmentProtected;
typedef struct ZVectorSegmentGlobal ZVectorSegmentGlobal;
typedef struct ZVectorSegmentClass ZVectorSegmentClass;
typedef struct ZVectorSegment ZVectorSegment;

struct ZVectorSegmentPrivate {
#line 19 "z-vector-segment.zco"
	int count;
#line 20 "z-vector-segment.zco"
	int capacity;
#line 21 "z-vector-segment.zco"
	void *data;
};

struct ZVectorSegmentProtected {
};

struct ZVectorSegmentGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	int is_object;
	struct ZVectorSegmentClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
#line 34 "z-vector-segment.zco"
	void  (*__parent_reset)(ZObject *object);
#line 55 "z-vector-segment.zco"
	void  (*__parent_dispose)(ZObject *object);
};

struct ZVectorSegmentClass {
	struct ZObjectClass parent_z_object;
};

struct ZVectorSegment {
	struct ZObject parent_z_object;
	struct ZVectorSegmentGlobal *_global;
	struct ZVectorSegmentPrivate _priv;
	struct ZVectorSegmentProtected _prot;
#line 22 "z-vector-segment.zco"
	Self *prev;
#line 23 "z-vector-segment.zco"
	Self *next;
};
extern int z_vector_segment_type_id;
ZVectorSegmentGlobal * z_vector_segment_get_type(struct zco_context_t *ctx);
void __z_vector_segment_init(struct zco_context_t *ctx, ZVectorSegment *self);
void __z_vector_segment_class_init(struct zco_context_t *ctx, ZVectorSegmentClass *_class);
#line 71 "z-vector-segment.zco"
Self * z_vector_segment_new(struct zco_context_t *ctx);
#line 82 "z-vector-segment.zco"
int  z_vector_segment_get_size(Self *self);
#line 87 "z-vector-segment.zco"
int  z_vector_segment_set_size(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct);
#line 142 "z-vector-segment.zco"
int  z_vector_segment_get_capacity(Self *self);
#line 147 "z-vector-segment.zco"
void  z_vector_segment_set_capacity(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct);
#line 176 "z-vector-segment.zco"
int  z_vector_segment_is_in_bound(Self *self,ZVectorIter *iter);
#line 189 "z-vector-segment.zco"
void *  z_vector_segment_get_item(Self *self,ZVectorIter *iter,int item_size,int storage_mode);
#line 209 "z-vector-segment.zco"
int  z_vector_segment_set_item(Self *self,ZVectorIter *iter,void *item,int item_size,int storage_mode);
#line 226 "z-vector-segment.zco"
int  z_vector_segment_insert_segment(Self *self,ZVectorSegment *src,int item_size);
#line 247 "z-vector-segment.zco"
void  z_vector_segment_insert(Self *self,ZVectorIter *iter,int n,void *item,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct);
#line 274 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_begin(Self *self);
#line 286 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_end(Self *self);
#line 307 "z-vector-segment.zco"
int  z_vector_segment_insert_range(Self *self,ZVectorIter *iter,ZVectorSegment *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct);
#line 363 "z-vector-segment.zco"
int  z_vector_segment_erase(Self *self,ZVectorIter *start,ZVectorIter *end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_destruct);

#undef Self


#endif
