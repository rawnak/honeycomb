/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector-segment.c: Bootstrap file for z-vector-segment.zco
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

#line 15 "z-vector-segment.zco"

#include <zco-config.h>

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <malloc.h>


struct ZSegmentData {
 int ref_count;
 unsigned char buffer[1];
};

#define DATA_OVERHEAD sizeof(int)


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-vector-segment-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZVectorSegment
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_vector_segment_new(ctx,allocator)
#define INIT_EXISTS
#define init z_vector_segment_init
#define new z_vector_segment_new
#define get_prev z_vector_segment_get_prev
#define set_prev z_vector_segment_set_prev
#define get_next z_vector_segment_get_next
#define set_next z_vector_segment_set_next
#define release_data z_vector_segment_release_data
#define prepare_for_writing z_vector_segment_prepare_for_writing
#define get_size z_vector_segment_get_size
#define set_size z_vector_segment_set_size
#define get_capacity z_vector_segment_get_capacity
#define deallocate z_vector_segment_deallocate
#define set_capacity z_vector_segment_set_capacity
#define is_in_bound z_vector_segment_is_in_bound
#define get_item z_vector_segment_get_item
#define set_item z_vector_segment_set_item
#define insert z_vector_segment_insert
#define get_begin z_vector_segment_get_begin
#define get_end z_vector_segment_get_end
#define clone z_vector_segment_clone
#define insert_range z_vector_segment_insert_range
#define erase z_vector_segment_erase

ZCO_DEFINE_CLASS_TYPE(z_vector_segment);

static void z_vector_segment_init(Self *self);
static void  z_vector_segment_reset(ZObject *object);
static void  z_vector_segment_dispose(ZObject *object);
static void  z_vector_segment_release_data(Self *self);
static void  z_vector_segment_prepare_for_writing(Self *self,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct);
static void  z_vector_segment_deallocate(Self *self);
static int  z_vector_segment_set_capacity(Self *self,int min_value,int max_value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_copy_construct,ZVectorItemCallback item_destruct);
static int  z_vector_segment_clone(Self *self,ZVectorSegment *src);
static void z_vector_segment_class_destroy(ZObjectGlobal *gbl);
static void z_vector_segment___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorSegmentGlobal * z_vector_segment_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZVectorSegment, z_vector_segment, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZVectorSegment);
	ZCO_REGISTER_TYPE(z_vector_segment);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_segment, reset);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_segment, dispose);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_segment, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_segment, __delete);
	ZCO_CREATE_METHOD_MAP(ZVectorSegment, z_vector_segment);
	ZCO_REGISTER_METHOD(new);
	ZCO_REGISTER_METHOD(get_size);
	ZCO_REGISTER_METHOD(set_size);
	ZCO_REGISTER_METHOD(get_capacity);
	ZCO_REGISTER_METHOD(is_in_bound);
	ZCO_REGISTER_METHOD(get_item);
	ZCO_REGISTER_METHOD(set_item);
	ZCO_REGISTER_METHOD(insert);
	ZCO_REGISTER_METHOD(insert_range);
	ZCO_REGISTER_METHOD(erase);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
}

void __z_vector_segment_class_init(struct zco_context_t *ctx, ZVectorSegmentClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_vector_segment_init(struct zco_context_t *ctx, Self *self)
{
	ZCO_INIT_START(ZVectorSegment, z_vector_segment);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_vector_segment_init(Self *self)
{
 selfp->start = 0;
 selfp->count = 0;
 selfp->capacity = 0;
 selfp->data = 0;
 selfp->prev = NULL;
 selfp->next = NULL;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_vector_segment_reset(ZObject *object)
{
 Self *self = (Self *) object;

 set_prev(self, NULL);
 set_next(self, NULL);

 deallocate(self);

 selfp->start = 0;
 selfp->count = 0;
 selfp->capacity = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_vector_segment_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 set_prev(self, NULL);
 set_next(self, NULL);

 deallocate(self);

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_vector_segment_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 if (!allocator)
 allocator = ctx->flex_allocator;

 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
Self * z_vector_segment_get_prev(Self *self)
{
{
 if (selfp->prev)
 z_object_ref(Z_OBJECT(selfp->prev));

 return selfp->prev;
 }
}
void z_vector_segment_set_prev(Self *self, Self * value)
{
{
 if (selfp->prev)
 z_object_unref(Z_OBJECT(selfp->prev));

 selfp->prev = value;

 if (value)
 z_object_ref(Z_OBJECT(value));
 }
}
Self * z_vector_segment_get_next(Self *self)
{
{
 if (selfp->next)
 z_object_ref(Z_OBJECT(selfp->next));

 return selfp->next;
 }
}
void z_vector_segment_set_next(Self *self, Self * value)
{
{
 if (selfp->next)
 z_object_unref(Z_OBJECT(selfp->next));

 selfp->next = value;

 if (value)
 z_object_ref(Z_OBJECT(value));
 }
}
static void  z_vector_segment_release_data(Self *self)
{
{
 assert(selfp->data->ref_count > 1);
 --selfp->data->ref_count;

 selfp->data = NULL;
 }
}
static void  z_vector_segment_prepare_for_writing(Self *self,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct)
{
{
 /* If the segment data has a ref-count of 1, we are allowed to
                   write on it because it's not being shared by any other
                   segments */
 if (!selfp->data || selfp->data->ref_count == 1)
 return;

 /* Allocating space for a new segment data */
 ZMemoryAllocator *alloc = z_object_get_allocator_ptr(Z_OBJECT(self));
 ZSegmentData *original = selfp->data;

 if (alloc)
 selfp->data = z_memory_allocator_allocate(alloc, selfp->capacity * item_size + DATA_OVERHEAD);
 else
 selfp->data = malloc(selfp->capacity * item_size + DATA_OVERHEAD);

 /* Copying over contents from the original segment */
 selfp->data->ref_count = 1;
 memcpy(selfp->data->buffer, original->buffer, selfp->capacity * item_size);

 /* Call copy constructor for each copied element */
 if (item_copy_construct) {
 int i;
 int n = selfp->count;

 if (storage_mode == 0) {
 for (i=0; i<n; ++i) {
 int offset = i * item_size;
 item_copy_construct(selfp->data->buffer + selfp->start + offset, userdata);
 }

 } else {
 for (i=0; i<n; ++i) {
 int offset = i * item_size;
 item_copy_construct(*((void **)(selfp->data->buffer + selfp->start + offset)), userdata);
 }
 }
 } 

 /* This segment no longer needs to reference the original
                   segment data */
 --original->ref_count;
 }
}
int  z_vector_segment_get_size(Self *self)
{
{
 return selfp->count;
 }
}
int  z_vector_segment_set_size(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_copy_construct,ZVectorItemCallback item_destruct)
{
{
 int rc = 0;

 if (selfp->count < value) {
 /* grow the vector */
 prepare_for_writing(self, item_size, storage_mode, userdata, item_copy_construct);

 if (selfp->capacity < value) {
 rc = set_capacity(self, value, value * 2, item_size, storage_mode, userdata,
 item_construct, item_copy_construct, item_destruct);
 
 if (rc)
 goto done;
 }

 if (item_construct) {
 int i;

 if (storage_mode == 0) {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * item_size;
 item_construct(selfp->data->buffer + selfp->start + offset, userdata);
 }
 } else {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * item_size;
 item_construct(*((void **)(selfp->data->buffer + selfp->start + offset)), userdata);
 }
 }
 }

 } else if (selfp->count > value) {
 /* shrink the vector */
 if (value == 0 && selfp->data->ref_count > 1) {
 release_data(self);

 } else {
 prepare_for_writing(self, item_size, storage_mode, userdata, item_copy_construct);

 if (item_destruct) {
 int i;

 if (storage_mode == 0) {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * item_size;
 item_destruct(selfp->data->buffer + selfp->start + offset, userdata);
 }
 } else {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * item_size;
 item_destruct(*((void **)(selfp->data->buffer + selfp->start + offset)), userdata);
 }
 }
 } 
 }
 }

 selfp->count = value;

done:
 return rc;
 }
}
int  z_vector_segment_get_capacity(Self *self)
{
{
 return selfp->capacity;
 }
}
static void  z_vector_segment_deallocate(Self *self)
{
{
 ZSegmentData *data = selfp->data;

 if (!data) {
 return;

 } else if (data->ref_count > 1) {
 --data->ref_count;

 } else {
 ZMemoryAllocator *alloc = z_object_get_allocator_ptr(Z_OBJECT(self));

 if (alloc)
 z_memory_allocator_deallocate(alloc, selfp->data);
 else
 free(selfp->data);
 }

 selfp->data = NULL;
 }
}
static int  z_vector_segment_set_capacity(Self *self,int min_value,int max_value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_copy_construct,ZVectorItemCallback item_destruct)
{
{
 if (max_value < selfp->count) {
 set_size(self, max_value, item_size, storage_mode, userdata, item_construct, item_copy_construct, item_destruct);
 selfp->count = max_value;
 }

 if (max_value) {
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 int min_segment_capacity_by_size = zco_context_get_min_segment_capacity_by_size(ctx);
 int min_segment_capacity_by_count = zco_context_get_min_segment_capacity_by_count(ctx);

 /* restrict minimum segment size by count */
 if (min_value < min_segment_capacity_by_count)
 min_value = min_segment_capacity_by_count;

 if (max_value < min_segment_capacity_by_count)
 max_value = min_segment_capacity_by_count;

 /* restrict minimum segment size by size in bytes */
 if (min_value * item_size < min_segment_capacity_by_size)
 min_value = (min_segment_capacity_by_size + item_size - 1) / item_size;

 if (max_value * item_size < min_segment_capacity_by_size)
 max_value = (min_segment_capacity_by_size + item_size - 1) / item_size;

 ZMemoryAllocator *alloc = z_object_get_allocator_ptr(Z_OBJECT(self));
 int new_capacity = 0;

 if (alloc) {
 if (selfp->data) {
 #ifdef FILL_USABLE_SPACE
 int available_capacity = (z_memory_allocator_get_usable_size(alloc, selfp->data) - DATA_OVERHEAD) / item_size;
 #else
 int available_capacity = 0;
 #endif

 if (selfp->data->ref_count == 1 && available_capacity >= min_value) {
 new_capacity = (available_capacity < max_value)? available_capacity : max_value;
 void *new_p = z_memory_allocator_resize(alloc, selfp->data, new_capacity * item_size + DATA_OVERHEAD);
 assert(new_p == selfp->data);
 } else {
 /* couldn't resize the block */
 return -1;
 }
 } else {
 new_capacity = max_value;
 selfp->data = z_memory_allocator_allocate(alloc, new_capacity * item_size + DATA_OVERHEAD);
 }
 } else {
 if (selfp->data) {
 #ifdef FILL_USABLE_SPACE
 int available_capacity = (malloc_usable_size(selfp->data) - DATA_OVERHEAD) / item_size;
 #else
 int available_capacity = 0;
 #endif

 if (selfp->data->ref_count == 1 && available_capacity >= min_value) {
 new_capacity = (available_capacity < max_value)? available_capacity : max_value;
 void *new_p = realloc(selfp->data, new_capacity * item_size + DATA_OVERHEAD);
 assert(new_p == selfp->data);
 } else {
 /* couldn't resize the block */
 return -1;
 }
 } else {
 new_capacity = max_value;
 selfp->data = malloc(new_capacity * item_size + DATA_OVERHEAD);
 }
 }

 selfp->data->ref_count = 1;
 selfp->capacity = new_capacity;

 } else if (selfp->data) {
 selfp->capacity = 0;
 deallocate(self);
 }

 return 0;
 }
}
int  z_vector_segment_is_in_bound(Self *self,ZVectorIter *iter)
{
{
 int index = z_vector_iter_get_index(iter);

 if (index >= 0 && index < selfp->count)
 return 1;

 else
 return 0;
 }
}
void *  z_vector_segment_get_item(Self *self,ZVectorIter *iter,int item_size,int storage_mode)
{
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * item_size;

 if (is_in_bound(self, iter)) {
 if (storage_mode == 0)
 return selfp->data->buffer + selfp->start + offset;
 else
 return *((void **)(selfp->data->buffer + selfp->start + offset));

 } else {
 fprintf(stderr, "Index out of bound. max=%d, index=%d\n", selfp->count-1, index);
 abort();
 }

 return NULL;
 }
}
int  z_vector_segment_set_item(Self *self,ZVectorIter *iter,void *item,void *userdata,ZVectorItemCallback item_copy_construct,int item_size,int storage_mode)
{
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * item_size;

 prepare_for_writing(self, item_size, storage_mode, userdata, item_copy_construct);

 if (index >= 0 && index < selfp->count) {
 if (storage_mode == 0)
 memcpy(selfp->data->buffer + selfp->start + offset, item, item_size);
 else
 memcpy(selfp->data->buffer + selfp->start + offset, &item, item_size);

 return 0;
 }

 return ERANGE;
 }
}
int  z_vector_segment_insert(Self *self,ZVectorIter *iter,int n,void *item,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct)
{
{
 /* increase the size of the vector */

 int size = get_size(self);
 int rc = set_size(self, size + n, item_size, storage_mode, userdata, NULL, item_copy_construct, NULL);

 if (rc)
 return rc;

 assert(size + n == get_size(self));
 //assert(self == z_vector_iter_get_segment(iter));

 /* make a copy of the iterator */
 ZVectorIter *it = z_vector_iter_dup(iter);

 /* shift all elements in [it,inf) forward */
 int index = z_vector_iter_get_index(it);
 assert(size >= index);

 prepare_for_writing(self, item_size, storage_mode, userdata, item_copy_construct);

 if (size > index) {
 void *base = selfp->data->buffer + selfp->start;
 memmove(base + (index + n) * item_size,
 base + index * item_size,
 (size - index) * item_size);
 }

 int i;

 if (item_copy_construct) {
 int i;

 if (storage_mode == 0) {
 for (i=0; i<n; ++i) {
 set_item(self, it, item, userdata, item_copy_construct, item_size, storage_mode);
 z_vector_iter_increment(it);

 int offset = (index + i) * item_size;
 item_copy_construct(selfp->data->buffer + selfp->start + offset, userdata);
 }

 } else {
 for (i=0; i<n; ++i) {
 set_item(self, it, item, userdata, item_copy_construct, item_size, storage_mode);
 z_vector_iter_increment(it);

 int offset = (index + i) * item_size;
 item_copy_construct(*((void **)(selfp->data->buffer + selfp->start + offset)), userdata);
 }
 }
 } else {
 for (i=0; i<n; ++i) {
 set_item(self, it, item, userdata, item_copy_construct, item_size, storage_mode);
 z_vector_iter_increment(it);
 }
 }


 z_object_unref(Z_OBJECT(it));

 return 0;
 }
}
ZVectorIter *  z_vector_segment_get_begin(Self *self)
{
{
 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_segment(iter, self);
 return iter;
 }
}
ZVectorIter *  z_vector_segment_get_end(Self *self)
{
{
 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_segment(iter, self);
 z_vector_iter_set_index(iter, get_size(self)-1);
 z_vector_iter_increment(iter);
 return iter;
 }
}
static int  z_vector_segment_clone(Self *self,ZVectorSegment *src)
{
{
 selfp->data = src->_priv.data;
 ++selfp->data->ref_count;

 selfp->count = get_size(src);
 selfp->capacity = get_capacity(src);

 return selfp->count;
 }
}
int  z_vector_segment_insert_range(Self *self,ZVectorIter *iter,ZVectorSegment *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct)
{
{
 ZVectorIter *src_begin_it, *src_end_it;
 ZVectorIter *it1, *it2;
 ZVectorIter *dest_it;

 /* make a copy of the iterators */
 src_begin_it = get_begin(src);
 src_end_it = get_end(src);

 if (src_iter_start == NULL) {
 it1 = src_begin_it;
 z_object_ref(Z_OBJECT(it1));
 } else {
 it1 = z_vector_iter_dup(src_iter_start);
 }

 if (src_iter_end == NULL) {
 it2 = src_end_it;
 z_object_ref(Z_OBJECT(it2));
 } else {
 it2 = z_vector_iter_dup(src_iter_end);
 }

 #ifdef USE_COPY_ON_WRITE
 if (selfp->count == 0 &&
 z_vector_iter_is_equal(it1, src_begin_it) &&
 z_vector_iter_is_equal(it2, src_end_it)) {

 z_object_unref(Z_OBJECT(src_end_it));
 z_object_unref(Z_OBJECT(src_begin_it));
 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));
 return clone(self, src);
 }
 #endif

 z_object_unref(Z_OBJECT(src_end_it));
 z_object_unref(Z_OBJECT(src_begin_it));

 if (iter == NULL)
 dest_it = get_end(self);
 else
 dest_it = z_vector_iter_dup(iter);

 /* compute the item count */
 ZVectorSegment *it2_segment = z_vector_iter_get_segment(it2);

 int n;
 if (src == it2_segment) {
 n = z_vector_iter_get_index(it2) - z_vector_iter_get_index(it1);
 } else {
 assert(it2_segment == src->_priv.next);
 assert(z_vector_iter_get_index(it2) == 0);
 n = z_vector_segment_get_size(src) - z_vector_iter_get_index(it1);
 }
 z_object_unref(Z_OBJECT(it2_segment));
 assert(n >= 0);

 /* increase the size of the vector */
 int size = get_size(self);
 int rc = set_size(self, size + n, item_size, storage_mode, userdata, NULL, item_copy_construct, NULL);

 if (rc) {
 /* all return codes must be non-positive */
 assert(rc < 0);
 n = rc;
 goto done;
 }

 int index = z_vector_iter_get_index(dest_it);

 prepare_for_writing(self, item_size, storage_mode, userdata, item_copy_construct);

 /* shift all elements in [dest_it,inf) forward */
 void *base = selfp->data->buffer + selfp->start;
 memmove(base + (index + n) * item_size,
 base + index * item_size,
 (size - index) * item_size);

 /* insert the new item(s) */
 int i;
 if (item_copy_construct) {
 int i;

 if (storage_mode == 0) {
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1, item_size, storage_mode);
 set_item(self, dest_it, data, userdata, item_copy_construct, item_size, storage_mode);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);

 int offset = (index + i) * item_size;
 item_copy_construct(selfp->data->buffer + selfp->start + offset, userdata);
 }

 } else {
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1, item_size, storage_mode);
 set_item(self, dest_it, data, userdata, item_copy_construct, item_size, storage_mode);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);

 int offset = (index + i) * item_size;
 item_copy_construct(*((void **)(selfp->data->buffer + selfp->start + offset)), userdata);
 }
 }
 } else {
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1, item_size, storage_mode);
 set_item(self, dest_it, data, userdata, item_copy_construct, item_size, storage_mode);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);
 }
 }


done:
 z_object_unref(Z_OBJECT(it1));
 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(dest_it));

 return n;
 }
}
int  z_vector_segment_erase(Self *self,ZVectorIter *start,ZVectorIter *end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct,ZVectorItemCallback item_destruct)
{
{
 ZVectorIter *it1;
 ZVectorIter *it2;

 if (start == NULL)
 start = get_begin(self);
 else
 z_object_ref(Z_OBJECT(start));

 if (end == NULL)
 end = get_end(self);
 else
 z_object_ref(Z_OBJECT(end));
 
 /* compute the item count */
 ZVectorSegment *it2_segment = z_vector_iter_get_segment(end);

 int n;
 if (self == it2_segment) {
 n = z_vector_iter_get_index(end) - z_vector_iter_get_index(start);
 } else {
 assert(it2_segment == selfp->next);
 assert(z_vector_iter_get_index(end) == 0);
 n = z_vector_segment_get_size(self) - z_vector_iter_get_index(start);
 }

 if (n >= 0) {
 it1 = z_vector_iter_dup(start);
 it2 = z_vector_iter_dup(end);
 } else {
 it1 = z_vector_iter_dup(end);
 it2 = z_vector_iter_dup(start);
 n = -n;
 }

 z_object_unref(Z_OBJECT(end));
 z_object_unref(Z_OBJECT(start));

 int size = get_size(self);
 if (selfp->data->ref_count > 1 && n == size) {
 release_data(self);

 } else {
 prepare_for_writing(self, item_size, storage_mode, userdata, item_copy_construct);

 /* call the item destructor on the items that is being removed */
 if (item_destruct) {
 ZVectorIter *temp = z_vector_iter_dup(it1);

 for (; !z_vector_iter_is_equal(temp, it2); z_vector_iter_increment(temp)) {
 void *item = get_item(self, temp, item_size, storage_mode);
 item_destruct(item, userdata);
 }

 z_object_unref(Z_OBJECT(temp));
 }

 /* shift all elements in [it1,inf) backward */
 int it1_index = z_vector_iter_get_index(it1);
 int it2_index = z_vector_iter_get_index(it2);
 void *base = selfp->data->buffer + selfp->start;

 if (self == it2_segment) {
 memmove(base + (it1_index) * item_size,
 base + (it1_index + n) * item_size,
 (size - it2_index) * item_size);
 } 
 }

 z_object_unref(Z_OBJECT(it2_segment));

 /* decrease the size of the vector */
 selfp->count = size - n;

 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));

 return n;
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_vector_segment_class_destroy(ZObjectGlobal *gbl)
{
	ZVectorSegmentGlobal *_global = (ZVectorSegmentGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_vector_segment___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



