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
#define Z_VECTOR_SEGMENT(s) ((ZVectorSegment *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_vector_segment_type_id]))


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
	int start;
#line 20 "z-vector-segment.zco"
	int count;
#line 21 "z-vector-segment.zco"
	int capacity;
#line 22 "z-vector-segment.zco"
	void *data;
#line 23 "z-vector-segment.zco"
	Self *prev;
#line 24 "z-vector-segment.zco"
	Self *next;
};

struct ZVectorSegmentProtected {
};

struct ZVectorSegmentGlobal {
	struct ZCommonGlobal common;
	struct ZVectorSegmentClass *_class;
#line 36 "z-vector-segment.zco"
	void  (*__parent_reset)(ZObject *object);
#line 54 "z-vector-segment.zco"
	void  (*__parent_dispose)(ZObject *object);
#line 576 "z-vector-segment.zco"
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZVectorSegmentClass {
	struct ZObjectClass parent_z_object;
};

struct ZVectorSegment {
	struct ZObject parent_z_object;
	struct ZVectorSegmentGlobal *_global;
	struct ZVectorSegmentPrivate _priv;
	struct ZVectorSegmentProtected _prot;
};
extern int z_vector_segment_type_id;
ZVectorSegmentGlobal * z_vector_segment_get_type(struct zco_context_t *ctx);
void __z_vector_segment_init(struct zco_context_t *ctx, ZVectorSegment *self);
void __z_vector_segment_class_init(struct zco_context_t *ctx, ZVectorSegmentClass *_class);
#line 69 "z-vector-segment.zco"
Self * z_vector_segment_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
#line 77 "z-vector-segment.zco"
Self * z_vector_segment_get_prev(Self *self);
#line 84 "z-vector-segment.zco"
void z_vector_segment_set_prev(Self *self, Self * value);
#line 98 "z-vector-segment.zco"
Self * z_vector_segment_get_next(Self *self);
#line 105 "z-vector-segment.zco"
void z_vector_segment_set_next(Self *self, Self * value);
#line 122 "z-vector-segment.zco"
int  z_vector_segment_get_size(Self *self);
#line 127 "z-vector-segment.zco"
int  z_vector_segment_set_size(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct);
#line 185 "z-vector-segment.zco"
int  z_vector_segment_get_capacity(Self *self);
#line 230 "z-vector-segment.zco"
int  z_vector_segment_is_in_bound(Self *self,ZVectorIter *iter);
#line 243 "z-vector-segment.zco"
void *  z_vector_segment_get_item(Self *self,ZVectorIter *iter,int item_size,int storage_mode);
#line 263 "z-vector-segment.zco"
int  z_vector_segment_set_item(Self *self,ZVectorIter *iter,void *item,int item_size,int storage_mode);
#line 290 "z-vector-segment.zco"
int  z_vector_segment_insert(Self *self,ZVectorIter *iter,int n,void *item,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct);
#line 357 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_begin(Self *self);
#line 369 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_end(Self *self);
#line 398 "z-vector-segment.zco"
int  z_vector_segment_insert_range(Self *self,ZVectorIter *iter,ZVectorSegment *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct);
#line 502 "z-vector-segment.zco"
int  z_vector_segment_erase(Self *self,ZVectorIter *start,ZVectorIter *end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_destruct);

#undef Self


#endif
