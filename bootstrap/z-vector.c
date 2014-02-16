/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector.c: Bootstrap file for z-vector.zco
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

#line 14 "z-vector.zco"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-vector-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZVector
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_vector_new(ctx,allocator)
#define INIT_EXISTS
#define init z_vector_init
#define new z_vector_new
#define get_item_size z_vector_get_item_size
#define set_item_size z_vector_set_item_size
#define set_is_insert_only_mode z_vector_set_is_insert_only_mode
#define set_item_construct z_vector_set_item_construct
#define set_item_copy_construct z_vector_set_item_copy_construct
#define set_item_destruct z_vector_set_item_destruct
#define set_userdata z_vector_set_userdata
#define get_begin z_vector_get_begin
#define get_end z_vector_get_end
#define create_segment z_vector_create_segment
#define get_size z_vector_get_size
#define set_size z_vector_set_size
#define get_is_empty z_vector_get_is_empty
#define get_item z_vector_get_item
#define set_item z_vector_set_item
#define get_front z_vector_get_front
#define set_front z_vector_set_front
#define get_back z_vector_get_back
#define set_back z_vector_set_back
#define push_back z_vector_push_back
#define pop_back z_vector_pop_back
#define split_segment z_vector_split_segment
#define insert z_vector_insert
#define insert_range z_vector_insert_range
#define insert_segment_after z_vector_insert_segment_after
#define insert_segment_before z_vector_insert_segment_before
#define remove_segment z_vector_remove_segment
#define erase z_vector_erase
#define erase1 z_vector_erase1
#define erase1_increment z_vector_erase1_increment
#define clear z_vector_clear

ZCO_DEFINE_CLASS_TYPE(z_vector);

static void z_vector_init(Self *self);
static void  z_vector_reset(ZObject *object);
static void  z_vector_dispose(ZObject *object);
static ZVectorSegment * z_vector_create_segment(Self *self);
static void  z_vector_split_segment(Self *self,ZVectorSegment *segment,ZVectorIter *iter);
static void  z_vector_insert_segment_after(Self *self,ZVectorSegment *new_segment,ZVectorSegment *after);
static void  z_vector_insert_segment_before(Self *self,ZVectorSegment *new_segment,ZVectorSegment *before);
static void  z_vector_remove_segment(Self *self,ZVectorSegment *segment);
static void z_vector_class_destroy(ZObjectGlobal *gbl);
static void z_vector___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorGlobal * z_vector_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZVector, z_vector, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZVector);
	ZCO_REGISTER_TYPE(z_vector);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector, reset);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector, dispose);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector, __delete);
	ZCO_CREATE_METHOD_MAP(ZVector, z_vector);
	ZCO_REGISTER_METHOD(new);
	ZCO_REGISTER_METHOD(get_item);
	ZCO_REGISTER_METHOD(set_item);
	ZCO_REGISTER_METHOD(push_back);
	ZCO_REGISTER_METHOD(pop_back);
	ZCO_REGISTER_METHOD(insert);
	ZCO_REGISTER_METHOD(insert_range);
	ZCO_REGISTER_METHOD(erase);
	ZCO_REGISTER_METHOD(erase1);
	ZCO_REGISTER_METHOD(erase1_increment);
	ZCO_REGISTER_METHOD(clear);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
}

void __z_vector_class_init(struct zco_context_t *ctx, ZVectorClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_vector_init(struct zco_context_t *ctx, Self *self)
{
	ZCO_INIT_START(ZVector, z_vector);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_vector_init(Self *self)
{
 selfp->tail = selfp->head = NULL;

 selfp->item_size = 0;
 selfp->storage_mode = 0;
 selfp->is_insert_only_mode = 0;
 selfp->count = 0;
 selfp->userdata = 0;
 selfp->item_construct = 0;
 selfp->item_copy_construct = 0;
 selfp->item_destruct = 0;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_vector_reset(ZObject *object)
{
 Self *self = (Self *) object;

 clear(self);

 if (selfp->head)
 z_object_unref(Z_OBJECT(selfp->head));

 if (selfp->tail)
 z_object_unref(Z_OBJECT(selfp->tail));

 selfp->tail = selfp->head = NULL;

 selfp->item_size = 0;
 selfp->storage_mode = 0;
 selfp->is_insert_only_mode = 0;
 selfp->count = 0;
 selfp->userdata = 0;
 selfp->item_construct = 0;
 selfp->item_copy_construct = 0;
 selfp->item_destruct = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_vector_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 clear(self);

 if (selfp->head)
 z_object_unref(Z_OBJECT(selfp->head));

 if (selfp->tail)
 z_object_unref(Z_OBJECT(selfp->tail));

 selfp->tail = selfp->head = NULL;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_vector_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 if (!allocator) {
 allocator = ctx->flex_allocator;
 }

 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
int  z_vector_get_item_size(Self *self)
{
{
 if (selfp->storage_mode == 1)
 return 0;
 else
 return selfp->item_size;
 }
}
void z_vector_set_item_size(Self *self, int  value)
{
{
 if (value == 0) {
 selfp->storage_mode = 1;
 selfp->item_size = sizeof(void*);
 } else {
 selfp->storage_mode = 0;
 selfp->item_size = value;
 }
 }
}
void z_vector_set_is_insert_only_mode(Self *self, int  value)
{
{
 selfp->is_insert_only_mode = value;
 }
}
void z_vector_set_item_construct(Self *self, ZVectorItemCallback  value)
{
{
 selfp->item_construct = value;
 }
}
void z_vector_set_item_copy_construct(Self *self, ZVectorItemCallback  value)
{
{
 selfp->item_copy_construct = value;
 }
}
void z_vector_set_item_destruct(Self *self, ZVectorItemCallback  value)
{
{
 selfp->item_destruct = value;
 }
}
void z_vector_set_userdata(Self *self, void *  value)
{
{
 selfp->userdata = value;
 }
}
ZVectorIter *  z_vector_get_begin(Self *self)
{
{
 if (selfp->head)
 return z_vector_segment_get_begin(selfp->head);

 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 return iter;
 }
}
ZVectorIter *  z_vector_get_end(Self *self)
{
{
 if (selfp->tail)
 return z_vector_segment_get_end(selfp->tail);

 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_index(iter, get_size(self)-1);
 z_vector_iter_increment(iter);
 return iter;
 }
}
static ZVectorSegment * z_vector_create_segment(Self *self)
{
{
 return z_vector_segment_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 }
}
int  z_vector_get_size(Self *self)
{
{
 return selfp->count;
 }
}
void z_vector_set_size(Self *self, int  value)
{
{
 if (selfp->count < value) {
 /* Grow vector */
 int tail_size = 0;
 
 if (selfp->tail)
 tail_size = z_vector_segment_get_size(selfp->tail);

 if (!selfp->tail || z_vector_segment_set_size(selfp->tail, tail_size + value - selfp->count,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_copy_construct, selfp->item_destruct) != 0) {

 /* Failed to resize the tail. We need a new segment */
 ZVectorSegment *new_tail = create_segment(self);
 z_vector_segment_set_size(new_tail, value - selfp->count,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_copy_construct, selfp->item_destruct);

 if (selfp->tail)
 z_vector_segment_set_next(selfp->tail, new_tail);

 z_vector_segment_set_prev(new_tail, selfp->tail);
 z_vector_segment_set_next(new_tail, NULL);

 if (!selfp->head) {
 selfp->head = new_tail;
 z_object_ref(Z_OBJECT(new_tail));
 }

 if (selfp->tail)
 z_object_unref(Z_OBJECT(selfp->tail));

 /* giving ownership of new_tail to selfp->tail */
 selfp->tail = new_tail;
 }

 selfp->count = value;

 } else if (selfp->count > value && !selfp->is_insert_only_mode) {
 /* Shrink vector */
 
 int difference = selfp->count - value;

 while (difference) {
 int tail_size = z_vector_segment_get_size(selfp->tail);
 if (tail_size <= difference) {
 remove_segment(self, selfp->tail);
 difference -= tail_size;

 } else {
 z_vector_segment_set_size(selfp->tail, tail_size - difference,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_copy_construct, selfp->item_destruct);

 difference = 0;
 }
 }

 selfp->count = value;
 }
 }
}
int  z_vector_get_is_empty(Self *self)
{
{
 return get_size(self) == 0;
 }
}
void *  z_vector_get_item(Self *self,ZVectorIter *iter)
{
{
 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 void *item = z_vector_segment_get_item(segment, iter, selfp->item_size, selfp->storage_mode);
 z_object_unref(Z_OBJECT(segment));

 return item;
 }
}
int  z_vector_set_item(Self *self,ZVectorIter *iter,void *item)
{
{
 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 int rc = z_vector_segment_set_item(segment, iter, item, selfp->userdata,
 selfp->item_copy_construct, selfp->item_size, selfp->storage_mode);
 z_object_unref(Z_OBJECT(segment));

 return rc;
 }
}
void *  z_vector_get_front(Self *self)
{
{
 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_segment(iter, selfp->head);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;
 }
}
void z_vector_set_front(Self *self, void *  value)
{
{
 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_segment(iter, selfp->head);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
}
void *  z_vector_get_back(Self *self)
{
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;

 }
}
void z_vector_set_back(Self *self, void *  value)
{
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
}
void  z_vector_push_back(Self *self,void *item)
{
{
 /*  increase the size of the vector by 1 */
 int size = get_size(self);
 set_size(self, size + 1);

 /* set the last item of the vector */
 set_back(self, item);
 }
}
int  z_vector_pop_back(Self *self,void *item)
{
{
 if (selfp->is_insert_only_mode)
 return -1;

 if (item) {
 /* get the last item of the vector */
 void *d = get_back(self);
 memcpy(item, &d, selfp->item_size);
 }

 /* decrease the size of the vector by 1 */
 int size = get_size(self);
 set_size(self, size - 1);

 return 0;
 }
}
static void  z_vector_split_segment(Self *self,ZVectorSegment *segment,ZVectorIter *iter)
{
{
 /* split the segment so that the 'iter' will be pointing to the first element
                   in the second segment */

 /* create the new 2nd segment.
                   our intention is to move the later parts of the 1st segment into
                   the 2nd segment. we don't want to call the item copy
                   constructor because ware are not really copying the elements. */
 ZVectorSegment *new_segment = create_segment(self);
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 int rc = z_vector_segment_insert_range(new_segment, new_iter, segment, iter,
 NULL, selfp->item_size, selfp->storage_mode, selfp->userdata,
 NULL);
 assert(rc >= 0);
 z_object_unref(Z_OBJECT(new_iter));

 /* shrink the current segment. it will be the 1st segment after the split.
                   since we are not adding new elements to the segment, we don't expect the constructor
                   to be called, so we don't pass the item_construct.

                   since we "moved" the elements from the first segment into the second segment,
                   we shouldn't call the destructor on the original item. the user of the vector
                   should not be notified that an item was copied and deleted because of the move
                   operation.

                   we are passing the item_copy_constructor because reducing the size of the segment
                   may trigger a copy-on-write, for which we would need to run the copy constructor
                   on each element.
                 */
 z_vector_segment_set_size(segment, z_vector_iter_get_index(iter), selfp->item_size,
 selfp->storage_mode, selfp->userdata, NULL, selfp->item_copy_construct, NULL);

 /* insert the 2nd segment after the 1st */
 insert_segment_after(self, new_segment, segment);
 z_object_unref(Z_OBJECT(new_segment));
 }
}
int  z_vector_insert(Self *self,ZVectorIter *iter,int n,void *item)
{
{
 /* We not be inserting the new elements at the back of the vector
                   so we also reject this operation in insert only mode */
 if (selfp->is_insert_only_mode)
 return -1;

 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 int rc = z_vector_segment_insert(segment, iter, n, item, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_copy_construct);

 if (rc < 0) {
 int index = z_vector_iter_get_index(iter);
 int segment_size = z_vector_segment_get_size(segment);

 if (index == 0) {
 /* Iterator is at the beginning of the segment. We needn't split the segment */
 ZVectorSegment *new_segment = create_segment(self);

 /* build the new segment */
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert(new_segment, new_iter, n, item, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_copy_construct);

 assert(rc >= 0);
 z_object_unref(Z_OBJECT(new_iter));
 
 /* insert the new segment before 'segment' */
 insert_segment_before(self, new_segment, segment);
 z_object_unref(Z_OBJECT(new_segment));

 } else if (index == segment_size) {
 /* Iterator is at the end of the segment. We needn't split the segment */
 ZVectorSegment *new_segment = create_segment(self);
 
 /* build the new segment */
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert(new_segment, new_iter, n, item, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_copy_construct);
 assert(rc >= 0);
 z_object_unref(Z_OBJECT(new_iter));

 /* insert the new segment after 'segment' */
 insert_segment_after(self, new_segment, segment);
 z_object_unref(Z_OBJECT(new_segment));

 } else {
 /* Iterator is in the middle of the segment. We have to split the segment */
 split_segment(self, segment, iter);

 /* build the new segment */
 ZVectorSegment *new_segment = create_segment(self);
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert(new_segment, new_iter, n, item, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_copy_construct);
 assert(rc >= 0);
 z_object_unref(Z_OBJECT(new_iter));

 /* insert the new segment after 'segement' */
 insert_segment_after(self, new_segment, segment);
 z_object_unref(Z_OBJECT(new_segment));
 }
 }

 z_object_unref(Z_OBJECT(segment));
 selfp->count += n;

 return 0;
 }
}
int  z_vector_insert_range(Self *self,ZVectorIter *iter,ZVector *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end)
{
{
 /* We may not be inserting the new elements at the back of the vector
                   so we also reject this operation in insert only mode */
 if (selfp->is_insert_only_mode)
 return -1;

 ZVectorSegment *source_start_segment = z_vector_iter_get_segment(src_iter_start);

 if (!source_start_segment) {
 /* The iterator doesn't point to any segment. The vector that the iterator is meant
			   to point to must be empty */
 return 0;
 }

 ZVectorSegment *source_end_segment = z_vector_iter_get_segment(src_iter_end);

 /* The end segment cannot be NULL if the start segment is non-NULL. If the vector that the
		   two iterators are meant to point to is the same vector, it cannot be both empty and
		   non-empty */
 assert(source_end_segment != NULL);

 ZVectorIter *temp_iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_assign(temp_iter, iter);

 ZVectorSegment *target_segment = z_vector_iter_get_segment(temp_iter);

 ZVectorSegment *source_segment = source_end_segment;
 z_object_ref(Z_OBJECT(source_segment));

 int count = 0;

 ZVectorIter *begin_of_start_segment = z_vector_segment_get_begin(source_start_segment);
 ZVectorIter *end_of_end_segment = z_vector_segment_get_end(source_end_segment);

 while (1) {
 int rc;

 /* Note that we are inserting in reverse, from the end to the start.
                           The first insertion (from the end segment) may not be the entire
                           segment. For that reason, we need to do an insert_range instead
                           of just copying the segment.

                           If the copy is successful, the target pointer (temp_iter) may still
                           be pointing to a middle part of a segment. In that case, we have
                           to insert_range for the next round. Once we get to a point where
                           the insertion failed and we needed to insert a new segment, we
                           can start inserting whole segments.

                           Because the last insertion (from the start segment) may not be
                           the complete segment, we need to do something similar to what
                           we did with the first insertion except we should try to create a
                           new segment. This will ensure that the segment from the second-last
                           insertion is not modified, since modifying it may cause a copy on
                           write.

                           For the final insertion, we should create a new segment as long as
                           it isn't the first insertion as well. If the last insertion and the
                           first insertion are the same then we really have only one insertion
                           taking place.
                         */
 ZVectorIter *t1,*t2;

 if (source_segment == source_start_segment) {
 t1 = src_iter_start;

 if (source_segment == source_end_segment)
 t2 = src_iter_end;
 else
 t2 = NULL;

 } else if (source_segment == source_end_segment) {
 t1 = NULL;
 t2 = src_iter_end;
 } else {
 t1 = NULL;
 t2 = NULL;
 }

 if (t1 == NULL && t2 == NULL && z_vector_iter_get_index(temp_iter) == 0) {
 /* we can copy the whole segment */
 ZVectorSegment *new_segment = create_segment(self);

 /* build the new segment */
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert_range(new_segment, NULL, source_segment, NULL,
 NULL, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_copy_construct);
 assert(rc > 0);

 /* change iterator so that it points to the beginning of the new segment */
 z_object_unref(Z_OBJECT(temp_iter));
 temp_iter = new_iter;

 /* insert the new segment before target_segment */
 insert_segment_before(self, new_segment, target_segment);

 /* make the current segment the newly created segment (passing ownership) */
 z_object_unref(Z_OBJECT(target_segment));
 target_segment = new_segment;

 rc = z_vector_segment_get_size(new_segment);

 } else {
 if (!target_segment) {
 /* If this target iterator has an NULL segment, it must mean that this
                                           vector (that the iterator is associated with) is empty. Let's assert it */
 assert(!selfp->head);
 assert(!selfp->tail);

 target_segment = create_segment(self);
 
 selfp->head = target_segment;
 z_object_ref(Z_OBJECT(target_segment));

 selfp->tail = target_segment;
 z_object_ref(Z_OBJECT(target_segment));

 z_vector_iter_set_segment(temp_iter, target_segment);
 z_vector_iter_set_segment(iter, target_segment);
 }


 rc = z_vector_segment_insert_range(target_segment, temp_iter, source_segment, t1, t2,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_copy_construct);
 }

 if (rc < 0) {
 /* z_vector_segment_insert_range failed. We need to create a new segment and link it to the
                                   existing segment */

 int new_index = z_vector_iter_get_index(temp_iter);
 int segment_size = z_vector_segment_get_size(target_segment);

 if (new_index == 0) {
 /* Iterator is at the beginning of the segment. We needn't split the segment */
 ZVectorSegment *new_segment = create_segment(self);
 
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert_range(new_segment, new_iter, source_segment, t1,
 t2, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_copy_construct);

 assert(rc > 0);

 z_object_unref(Z_OBJECT(temp_iter));
 temp_iter = new_iter;
 
 insert_segment_before(self, new_segment, target_segment);

 /* the new target segment is the newly created segment. this ensures
                                           that the next insert_range happens before the newly created segment.
                                           (passing ownership) */
 z_object_unref(Z_OBJECT(target_segment));
 target_segment = new_segment;


 } else if (new_index == segment_size) {
 /* Iterator is at the end of the segment. We needn't split the segment */
 ZVectorSegment *new_segment = create_segment(self);
 
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert_range(new_segment, new_iter, source_segment, t1,
 t2, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_copy_construct);


 assert(rc > 0);

 z_object_unref(Z_OBJECT(temp_iter));
 temp_iter = new_iter;

 insert_segment_after(self, new_segment, target_segment);

 /* the new target segment is the newly created segment. this ensures
                                           that the next insert_range happens before the newly created segment.
                                           (passing ownership) */
 z_object_unref(Z_OBJECT(target_segment));
 target_segment = new_segment;

 } else {
 split_segment(self, target_segment, temp_iter);

 /* Iterator is in the middle of the segment. We have to split the segment */
 ZVectorSegment *new_segment = create_segment(self);
 
 /* build the new segment */
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert_range(new_segment, new_iter, source_segment, t1,
 t2, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_copy_construct);
 assert(rc > 0);
 z_object_unref(Z_OBJECT(new_iter));
 
 /* insert the new segment after target_segment */
 insert_segment_after(self, new_segment, target_segment);

 /* the new target segment is the newly created segment. this ensures
                                           that the next insert_range happens before the newly created segment.
                                           (passing ownership) */
 z_object_unref(Z_OBJECT(target_segment));
 target_segment = new_segment;

 z_object_unref(Z_OBJECT(temp_iter));
 temp_iter = z_vector_segment_get_begin(target_segment);

 }
 } 

 count += rc;

 if (source_segment == source_start_segment)
 break;

 /* move to the previous segment */
 ZVectorSegment *source_segment_prev = z_vector_segment_get_prev(source_segment);
 z_object_unref(Z_OBJECT(source_segment));
 source_segment = source_segment_prev;
 }

 z_object_unref(Z_OBJECT(source_segment));
 z_object_unref(Z_OBJECT(source_start_segment));
 z_object_unref(Z_OBJECT(source_end_segment));
 z_object_unref(Z_OBJECT(target_segment));

 z_object_unref(Z_OBJECT(begin_of_start_segment));
 z_object_unref(Z_OBJECT(end_of_end_segment));
 z_object_unref(Z_OBJECT(temp_iter));

 selfp->count += count;
 }
}
static void  z_vector_insert_segment_after(Self *self,ZVectorSegment *new_segment,ZVectorSegment *after)
{
{
 /* new segment points back to the existing segment */
 z_vector_segment_set_prev(new_segment, after);

 /* new segment points forward to the existing segment's next segment */
 ZVectorSegment *after_next = z_vector_segment_get_next(after);
 z_vector_segment_set_next(new_segment, after_next);

 /* if the existing segment had a next, it should point back to the new segment */
 if (after_next) {
 z_vector_segment_set_prev(after_next, new_segment);
 z_object_unref(Z_OBJECT(after_next));
 }

 /* the existing segment points forward to the new segment */
 z_vector_segment_set_next(after, new_segment);

 /* if after was the tail of the vector, the new segment should be the new tail */
 if (after == selfp->tail) {
 z_object_unref(Z_OBJECT(selfp->tail));
 selfp->tail = new_segment;
 z_object_ref(Z_OBJECT(new_segment));
 }
 }
}
static void  z_vector_insert_segment_before(Self *self,ZVectorSegment *new_segment,ZVectorSegment *before)
{
{
 /* new segment points back to the existing segment's previous segment */
 ZVectorSegment *before_prev = z_vector_segment_get_prev(before);
 z_vector_segment_set_prev(new_segment, before_prev);

 /* new segment points forward to the existing segment */
 z_vector_segment_set_next(new_segment, before);

 /* if the existing segment had a previous, it should point forward to the new segment */
 if (before_prev) {
 z_vector_segment_set_next(before_prev, new_segment);
 z_object_unref(Z_OBJECT(before_prev));
 }

 /* the existing segment points back to the new segment */
 z_vector_segment_set_prev(before, new_segment);

 /* if before was the head of the vector, the new segment should be the new head */
 if (before == selfp->head) {
 z_object_unref(Z_OBJECT(selfp->head));
 selfp->head = new_segment;
 z_object_ref(Z_OBJECT(new_segment));
 }
 }
}
static void  z_vector_remove_segment(Self *self,ZVectorSegment *segment)
{
{
 /* Empty the segment so the destructor is called for each item removed */
 z_vector_segment_set_size(segment, 0,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_copy_construct, selfp->item_destruct);

 ZVectorSegment *segment_prev = z_vector_segment_get_prev(segment);
 ZVectorSegment *segment_next = z_vector_segment_get_next(segment);

 if (segment_prev) {
 /* the previous segment point forward to the next segment */
 z_vector_segment_set_next(segment_prev, segment_next);
 } else {
 assert(segment == selfp->head);

 /* if the segment was the head of the vector, make the next
			   segment the new head */
 if (selfp->head)
 z_object_unref(Z_OBJECT(selfp->head));

 selfp->head = segment_next;

 if (segment_next)
 z_object_ref(Z_OBJECT(segment_next));
 }

 if (segment_next) {
 /* the next segment points back to the previous segment */
 z_vector_segment_set_prev(segment_next, segment_prev);
 } else {
 assert(segment == selfp->tail);

 /* if the segment was the tail of the vector, make the previous
			   segment the new tail */
 if (selfp->tail)
 z_object_unref(Z_OBJECT(selfp->tail));

 selfp->tail = segment_prev;

 if (segment_prev)
 z_object_ref(Z_OBJECT(segment_prev));
 }

 if (segment_prev)
 z_object_unref(Z_OBJECT(segment_prev));

 if (segment_next)
 z_object_unref(Z_OBJECT(segment_next));

 }
}
int  z_vector_erase(Self *self,ZVectorIter *start,ZVectorIter *end)
{
{
 if (selfp->is_insert_only_mode)
 return -1;

 if (get_is_empty(self))
 return 0;

 if (start)
 z_object_ref(Z_OBJECT(start));
 else
 start = get_begin(self);

 if (end)
 z_object_ref(Z_OBJECT(end));
 else
 end = get_end(self);

 ZVectorSegment *start_segment = z_vector_iter_get_segment(start);
 ZVectorSegment *end_segment = z_vector_iter_get_segment(end);
 ZVectorSegment *segment = start_segment;
 int count = 0;
 
 z_object_ref(Z_OBJECT(segment)); 

 while (1) {
 ZVectorIter *t1,*t2;
 if (segment == start_segment) {
 t1 = start;

 if (segment == end_segment)
 t2 = end;
 else
 t2 = NULL;
 } else if (segment == end_segment) {
 t1 = NULL;
 t2 = end;
 } else {
 t1 = NULL;
 t2 = NULL;
 }

 if (t2) {
 int t2_index = z_vector_iter_get_index(t2);

 if (t2_index == 0) {
 /* The t2 iterator points to the first element in
                                           end_segment but it is really meant to point to the one
                                           past the last element of the previous segment. In another
                                           words, we already processed the final segment (the
                                           prevoius segment) so we can break out of the loop here. */
 break;

 } else if (t2_index == z_vector_segment_get_size(end_segment)) {
 t2 = NULL;
 }
 }

 if (t1 && z_vector_iter_get_index(t1) == 0)
 t1 = NULL;

 if (t1 == NULL && t2 == NULL) {
 count += z_vector_segment_get_size(segment);
 remove_segment(self, segment);
 } else {
 count += z_vector_segment_erase(segment, t1, t2, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_copy_construct, selfp->item_destruct);
 }

 if (segment == end_segment)
 break;

 /* set segment to point to the next segment */
 ZVectorSegment *segment_next = z_vector_segment_get_next(segment);
 z_object_unref(Z_OBJECT(segment));
 segment = segment_next;
 }

 selfp->count -= count;

 z_object_unref(Z_OBJECT(segment)); 
 z_object_unref(Z_OBJECT(end_segment));
 z_object_unref(Z_OBJECT(start_segment)); 

 z_object_unref(Z_OBJECT(end));
 z_object_unref(Z_OBJECT(start));

 return 0;
 }
}
int  z_vector_erase1(Self *self,ZVectorIter *iter)
{
{
 int rc;
 ZVectorIter *next = z_vector_iter_dup(iter);

 z_vector_iter_increment(next);
 rc = erase(self, iter, next);

 z_object_unref(Z_OBJECT(next));

 return rc;
 }
}
int  z_vector_erase1_increment(Self *self,ZVectorIter *iter)
{
{
 int rc;
 ZVectorIter *temp = get_begin(self);
 
 if (z_vector_iter_is_equal(iter, temp)) {
 /* iterator is pointing to the first element of the vector */
 rc = erase1(self, iter);

 z_object_unref(Z_OBJECT(temp));
 temp = get_begin(self);
 z_vector_iter_assign(iter, temp);

 } else {
 z_vector_iter_assign(temp, iter);
 z_vector_iter_decrement(iter);
 rc = erase1(self, temp);
 z_vector_iter_increment(iter);
 }

 z_object_unref(Z_OBJECT(temp));

 return rc;
 }
}
int  z_vector_clear(Self *self)
{
{
 if (selfp->count == 0)
 return 0;

 if (selfp->is_insert_only_mode)
 return -1;

 set_size(self, 0);

 return 0;
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_vector_class_destroy(ZObjectGlobal *gbl)
{
	ZVectorGlobal *_global = (ZVectorGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_vector___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



