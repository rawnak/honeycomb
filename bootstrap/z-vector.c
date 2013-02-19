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

//#line 14 "z-vector.zco"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-vector.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVector
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_vector_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
//#line 29 "z-vector.zco"
#define init z_vector_init
//#line 86 "z-vector.zco"
#define new z_vector_new
//#line 94 "z-vector.zco"
#define set_item_size z_vector_set_item_size
//#line 108 "z-vector.zco"
#define set_is_insert_only_mode z_vector_set_is_insert_only_mode
//#line 119 "z-vector.zco"
#define set_item_construct z_vector_set_item_construct
//#line 130 "z-vector.zco"
#define set_item_copy_construct z_vector_set_item_copy_construct
//#line 142 "z-vector.zco"
#define set_item_destruct z_vector_set_item_destruct
//#line 152 "z-vector.zco"
#define set_userdata z_vector_set_userdata
//#line 161 "z-vector.zco"
#define get_begin z_vector_get_begin
//#line 175 "z-vector.zco"
#define get_end z_vector_get_end
//#line 193 "z-vector.zco"
#define get_size z_vector_get_size
//#line 197 "z-vector.zco"
#define set_size z_vector_set_size
//#line 264 "z-vector.zco"
#define get_is_empty z_vector_get_is_empty
//#line 272 "z-vector.zco"
#define get_item z_vector_get_item
//#line 283 "z-vector.zco"
#define set_item z_vector_set_item
//#line 295 "z-vector.zco"
#define get_front z_vector_get_front
//#line 303 "z-vector.zco"
#define set_front z_vector_set_front
//#line 315 "z-vector.zco"
#define get_back z_vector_get_back
//#line 324 "z-vector.zco"
#define set_back z_vector_set_back
//#line 335 "z-vector.zco"
#define push_back z_vector_push_back
//#line 348 "z-vector.zco"
#define pop_back z_vector_pop_back
//#line 366 "z-vector.zco"
#define split_segment z_vector_split_segment
//#line 391 "z-vector.zco"
#define insert z_vector_insert
//#line 473 "z-vector.zco"
#define insert_range z_vector_insert_range
//#line 708 "z-vector.zco"
#define insert_segment_after z_vector_insert_segment_after
//#line 734 "z-vector.zco"
#define insert_segment_before z_vector_insert_segment_before
//#line 760 "z-vector.zco"
#define remove_segment z_vector_remove_segment
//#line 813 "z-vector.zco"
#define erase z_vector_erase
//#line 893 "z-vector.zco"
#define erase1 z_vector_erase1
//#line 909 "z-vector.zco"
#define erase1_increment z_vector_erase1_increment
//#line 935 "z-vector.zco"
#define clear z_vector_clear

int z_vector_type_id = -1;

static Self *__z_vector_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_vector_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_vector_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
//#line 29 "z-vector.zco"
static void z_vector_init(Self *self);
//#line 43 "z-vector.zco"
static void  z_vector_reset(ZObject *object);
//#line 69 "z-vector.zco"
static void  z_vector_dispose(ZObject *object);
//#line 366 "z-vector.zco"
static void  z_vector_split_segment(Self *self,ZVectorSegment *segment,ZVectorIter *iter);
//#line 708 "z-vector.zco"
static void  z_vector_insert_segment_after(Self *self,ZVectorSegment *new_segment,ZVectorSegment *after);
//#line 734 "z-vector.zco"
static void  z_vector_insert_segment_before(Self *self,ZVectorSegment *new_segment,ZVectorSegment *before);
//#line 760 "z-vector.zco"
static void  z_vector_remove_segment(Self *self,ZVectorSegment *segment);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorGlobal * z_vector_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_vector_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_vector_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZVectorGlobal *global = (ZVectorGlobal *) malloc(sizeof(struct ZVectorGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorClass));
		memset(global->_class, 0, sizeof(struct ZVectorClass));
		global->name = "ZVector";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZVector temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			if (p_class->id > class_off_size)
				class_off_size = p_class->id;
		}
		class_off_list = malloc(sizeof(unsigned long) * (class_off_size+1));
		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
			class_off_list[p_class->id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		((ZObjectClass *) global->_class)->class_off_list = class_off_list;
		if (z_vector_type_id == -1)
			z_vector_type_id = zco_allocate_type_id();
		global->id = z_vector_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_vector_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_vector_type_id);
		*global_ptr = global;
		
//#line 43 "z-vector.zco"
		{
//#line 43 "z-vector.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
//#line 43 "z-vector.zco"
			global->__parent_reset = p_class->__reset;
//#line 43 "z-vector.zco"
			p_class->__reset = z_vector_reset;
//#line 43 "z-vector.zco"
		}
//#line 69 "z-vector.zco"
		{
//#line 69 "z-vector.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
//#line 69 "z-vector.zco"
			global->__parent_dispose = p_class->__dispose;
//#line 69 "z-vector.zco"
			p_class->__dispose = z_vector_dispose;
//#line 69 "z-vector.zco"
		}
		__z_vector_class_init(ctx, (ZVectorClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_userdata(global->method_map, global->method_map);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
//#line 86 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
//#line 272 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_item"), (ZObjectSignalHandler) get_item);
//#line 283 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_item"), (ZObjectSignalHandler) set_item);
//#line 335 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("push_back"), (ZObjectSignalHandler) push_back);
//#line 348 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("pop_back"), (ZObjectSignalHandler) pop_back);
//#line 391 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert"), (ZObjectSignalHandler) insert);
//#line 473 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert_range"), (ZObjectSignalHandler) insert_range);
//#line 813 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase"), (ZObjectSignalHandler) erase);
//#line 893 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase1"), (ZObjectSignalHandler) erase1);
//#line 909 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase1_increment"), (ZObjectSignalHandler) erase1_increment);
//#line 935 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("clear"), (ZObjectSignalHandler) clear);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZVectorGlobal *) global);
		#endif
		return global;
	}
	return (ZVectorGlobal *) *global_ptr;
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
	struct ZVectorGlobal *_global = z_vector_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
//#line 29 "z-vector.zco"
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
//#line 43 "z-vector.zco"
#define PARENT_HANDLER self->_global->__parent_reset
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
//#line 69 "z-vector.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
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
//#line 86 "z-vector.zco"
Self * z_vector_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
//#line 94 "z-vector.zco"
void z_vector_set_item_size(Self *self, int  value)
{
 if (value == 0) {
 selfp->storage_mode = 1;
 selfp->item_size = sizeof(void*);
 } else {
 selfp->storage_mode = 0;
 selfp->item_size = value;
 }
 }
//#line 108 "z-vector.zco"
void z_vector_set_is_insert_only_mode(Self *self, int  value)
{
 selfp->is_insert_only_mode = value;
 }
//#line 119 "z-vector.zco"
void z_vector_set_item_construct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_construct = value;
 }
//#line 130 "z-vector.zco"
void z_vector_set_item_copy_construct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_copy_construct = value;
 }
//#line 142 "z-vector.zco"
void z_vector_set_item_destruct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_destruct = value;
 }
//#line 152 "z-vector.zco"
void z_vector_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
//#line 161 "z-vector.zco"
ZVectorIter *  z_vector_get_begin(Self *self)
{
 if (selfp->head)
 return z_vector_segment_get_begin(selfp->head);

 ZVectorIter *iter = z_vector_iter_new(CTX);
 return iter;
 }
//#line 175 "z-vector.zco"
ZVectorIter *  z_vector_get_end(Self *self)
{
 if (selfp->tail)
 return z_vector_segment_get_end(selfp->tail);

 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_index(iter, get_size(self)-1);
 z_vector_iter_increment(iter);
 return iter;
 }
//#line 193 "z-vector.zco"
int  z_vector_get_size(Self *self)
{
 return selfp->count;
 }
//#line 197 "z-vector.zco"
void z_vector_set_size(Self *self, int  value)
{
 if (selfp->count < value) {
 /* Grow vector */
 int tail_size = 0;
 
 if (selfp->tail)
 tail_size = z_vector_segment_get_size(selfp->tail);

 if (!selfp->tail || z_vector_segment_set_size(selfp->tail, tail_size + value - selfp->count,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_destruct) != 0) {

 /* Failed to resize the tail. We need a new segment */
 ZVectorSegment *new_tail = z_vector_segment_new(CTX);
 z_vector_segment_set_size(new_tail, value - selfp->count,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_destruct);

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
 selfp->item_construct, selfp->item_destruct);

 difference = 0;
 }
 }

 selfp->count = value;
 }
 }
//#line 264 "z-vector.zco"
int  z_vector_get_is_empty(Self *self)
{
 return get_size(self) == 0;
 }
//#line 272 "z-vector.zco"
void *  z_vector_get_item(Self *self,ZVectorIter *iter)
{
 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 void *item = z_vector_segment_get_item(segment, iter, selfp->item_size, selfp->storage_mode);
 z_object_unref(Z_OBJECT(segment));

 return item;
 }
//#line 283 "z-vector.zco"
int  z_vector_set_item(Self *self,ZVectorIter *iter,void *item)
{
 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 int rc = z_vector_segment_set_item(segment, iter, item, selfp->item_size, selfp->storage_mode);
 z_object_unref(Z_OBJECT(segment));

 return rc;
 }
//#line 295 "z-vector.zco"
void *  z_vector_get_front(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_segment(iter, selfp->head);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;
 }
//#line 303 "z-vector.zco"
void z_vector_set_front(Self *self, void *  value)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_segment(iter, selfp->head);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
//#line 315 "z-vector.zco"
void *  z_vector_get_back(Self *self)
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;

 }
//#line 324 "z-vector.zco"
void z_vector_set_back(Self *self, void *  value)
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
//#line 335 "z-vector.zco"
void  z_vector_push_back(Self *self,void *item)
{
 /*  increase the size of the vector by 1 */
 int size = get_size(self);
 set_size(self, size + 1);

 /* set the last item of the vector */
 set_back(self, item);
 }
//#line 348 "z-vector.zco"
int  z_vector_pop_back(Self *self,void *item)
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
//#line 366 "z-vector.zco"
static void  z_vector_split_segment(Self *self,ZVectorSegment *segment,ZVectorIter *iter)
{
 /* split the segment so that the 'iter' will be pointing to the first element
                   in the second segment */

 /* create the new 2nd segment. */
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 int rc = z_vector_segment_insert_range(new_segment, new_iter, segment, iter,
 NULL, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_copy_construct);
 assert(rc >= 0);

 /* shrink the current segment. it will be the 1st segment after the split. */
 z_vector_segment_set_size(segment, z_vector_iter_get_index(iter), 
 selfp->item_size, selfp->storage_mode, NULL, NULL, NULL);

 /* insert the 2nd segment after the 1st */
 insert_segment_after(self, new_segment, segment);
 z_object_unref(Z_OBJECT(new_segment));
 }
//#line 391 "z-vector.zco"
int  z_vector_insert(Self *self,ZVectorIter *iter,int n,void *item)
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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);

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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);
 
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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);
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
//#line 473 "z-vector.zco"
int  z_vector_insert_range(Self *self,ZVectorIter *iter,ZVector *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end)
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


 ZVectorIter *temp_iter = z_vector_iter_new(CTX);
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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);

 /* build the new segment */
 ZVectorIter *new_iter = z_vector_segment_get_begin(new_segment);
 rc = z_vector_segment_insert_range(new_segment, new_iter, source_segment, NULL,
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

 target_segment = z_vector_segment_new(CTX);
 
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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);
 
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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);
 
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
 ZVectorSegment *new_segment = z_vector_segment_new(CTX);
 
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
//#line 708 "z-vector.zco"
static void  z_vector_insert_segment_after(Self *self,ZVectorSegment *new_segment,ZVectorSegment *after)
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
//#line 734 "z-vector.zco"
static void  z_vector_insert_segment_before(Self *self,ZVectorSegment *new_segment,ZVectorSegment *before)
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
//#line 760 "z-vector.zco"
static void  z_vector_remove_segment(Self *self,ZVectorSegment *segment)
{
 /* Empty the segment so the destructor is called for each item removed */
 z_vector_segment_set_size(segment, 0,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_destruct);

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
//#line 813 "z-vector.zco"
int  z_vector_erase(Self *self,ZVectorIter *start,ZVectorIter *end)
{
 if (selfp->is_insert_only_mode)
 return -1;

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

 /* 2 unrefs since it lost two references. one from the previous node
                                   and one from the next node */
 //z_object_unref(Z_OBJECT(segment)); 
 //z_object_unref(Z_OBJECT(segment)); 
 } else {
 count += z_vector_segment_erase(segment, t1, t2, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_destruct);
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

 return 0;
 }
//#line 893 "z-vector.zco"
int  z_vector_erase1(Self *self,ZVectorIter *iter)
{
 int rc;
 ZVectorIter *next = z_vector_iter_dup(iter);

 z_vector_iter_increment(next);
 rc = erase(self, iter, next);

 z_object_unref(Z_OBJECT(next));

 return rc;
 }
//#line 909 "z-vector.zco"
int  z_vector_erase1_increment(Self *self,ZVectorIter *iter)
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
//#line 935 "z-vector.zco"
int  z_vector_clear(Self *self)
{
 if (selfp->count == 0)
 return 0;

 if (selfp->is_insert_only_mode)
 return -1;

 set_size(self, 0);

 return 0;
 }

//#line 947 "z-vector.zco"


