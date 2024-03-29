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

#include <z-object.h>
#include <z-vector-iter.h>

struct ZVector;
typedef struct ZVector ZVector;
typedef void(*ZVectorItemCallback)(void *item, void *userdata);

struct ZSegmentData;
typedef struct ZSegmentData ZSegmentData;

#include <zco-context.h>
#define Self ZVectorSegment
#define Z_VECTOR_SEGMENT(s) ((ZVectorSegment *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_vector_segment_type_id]))


ZCO_TYPEDEF_FWD_DECL_CLASS(ZVectorSegment);

struct ZVectorSegmentPrivate {
	int start;
	int count;
	int capacity;
	ZSegmentData *data;
	Self *prev;
	Self *next;
};

struct ZVectorSegmentProtected {
};

struct ZVectorSegmentGlobal {
	ZCO_CLASS_GLOBAL_HEAD(ZVectorSegment);
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZVectorSegmentClass {
	struct ZObjectClass parent_z_object;
};

struct ZVectorSegment {
	struct ZObject parent_z_object;
	ZCO_CLASS_PUBLIC_HEAD(ZVectorSegment);
};
extern int z_vector_segment_type_id;
ZVectorSegmentGlobal * z_vector_segment_get_type(struct zco_context_t *ctx);
void __z_vector_segment_init(struct zco_context_t *ctx, ZVectorSegment *self);
void __z_vector_segment_class_init(struct zco_context_t *ctx, ZVectorSegmentClass *_class);
Self * z_vector_segment_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
Self * z_vector_segment_get_prev(Self *self);
void z_vector_segment_set_prev(Self *self, Self * value);
Self * z_vector_segment_get_next(Self *self);
void z_vector_segment_set_next(Self *self, Self * value);
int  z_vector_segment_get_size(Self *self);
int  z_vector_segment_set_size(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_copy_construct,ZVectorItemCallback item_destruct);
int  z_vector_segment_get_capacity(Self *self);
int  z_vector_segment_is_in_bound(Self *self,ZVectorIter *iter);
void *  z_vector_segment_get_item(Self *self,ZVectorIter *iter,int item_size,int storage_mode);
int  z_vector_segment_set_item(Self *self,ZVectorIter *iter,void *item,void *userdata,ZVectorItemCallback item_copy_construct,int item_size,int storage_mode);
int  z_vector_segment_insert(Self *self,ZVectorIter *iter,int n,void *item,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct);
ZVectorIter *  z_vector_segment_get_begin(Self *self);
ZVectorIter *  z_vector_segment_get_end(Self *self);
int  z_vector_segment_insert_range(Self *self,ZVectorIter *iter,ZVectorSegment *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct);
int  z_vector_segment_erase(Self *self,ZVectorIter *start,ZVectorIter *end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct,ZVectorItemCallback item_destruct);

#undef Self


#endif
