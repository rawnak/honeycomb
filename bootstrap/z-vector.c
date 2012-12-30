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
#include <z-vector.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVector
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_vector_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 28 "z-vector.zco"
#define init z_vector_init
#line 87 "z-vector.zco"
#define new z_vector_new
#line 95 "z-vector.zco"
#define set_item_size z_vector_set_item_size
#line 109 "z-vector.zco"
#define set_is_insert_only_mode z_vector_set_is_insert_only_mode
#line 120 "z-vector.zco"
#define set_item_construct z_vector_set_item_construct
#line 132 "z-vector.zco"
#define set_item_destruct z_vector_set_item_destruct
#line 142 "z-vector.zco"
#define set_userdata z_vector_set_userdata
#line 151 "z-vector.zco"
#define get_begin z_vector_get_begin
#line 161 "z-vector.zco"
#define get_end z_vector_get_end
#line 173 "z-vector.zco"
#define get_size z_vector_get_size
#line 177 "z-vector.zco"
#define set_size z_vector_set_size
#line 266 "z-vector.zco"
#define get_is_empty z_vector_get_is_empty
#line 274 "z-vector.zco"
#define get_item z_vector_get_item
#line 282 "z-vector.zco"
#define set_item z_vector_set_item
#line 291 "z-vector.zco"
#define get_front z_vector_get_front
#line 299 "z-vector.zco"
#define set_front z_vector_set_front
#line 311 "z-vector.zco"
#define get_back z_vector_get_back
#line 320 "z-vector.zco"
#define set_back z_vector_set_back
#line 331 "z-vector.zco"
#define push_back z_vector_push_back
#line 344 "z-vector.zco"
#define pop_back z_vector_pop_back
#line 365 "z-vector.zco"
#define insert z_vector_insert
#line 391 "z-vector.zco"
#define insert_range z_vector_insert_range
#line 437 "z-vector.zco"
#define erase z_vector_erase
#line 488 "z-vector.zco"
#define erase1 z_vector_erase1
#line 504 "z-vector.zco"
#define erase1_increment z_vector_erase1_increment
#line 530 "z-vector.zco"
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
#line 28 "z-vector.zco"
static void z_vector_init(Self *self);
#line 44 "z-vector.zco"
static void  z_vector_reset(ZObject *object);
#line 72 "z-vector.zco"
static void  z_vector_dispose(ZObject *object);

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
		
#line 44 "z-vector.zco"
		{
#line 44 "z-vector.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 44 "z-vector.zco"
			global->__parent_reset = p_class->__reset;
#line 44 "z-vector.zco"
			p_class->__reset = z_vector_reset;
#line 44 "z-vector.zco"
		}
#line 72 "z-vector.zco"
		{
#line 72 "z-vector.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 72 "z-vector.zco"
			global->__parent_dispose = p_class->__dispose;
#line 72 "z-vector.zco"
			p_class->__dispose = z_vector_dispose;
#line 72 "z-vector.zco"
		}
		__z_vector_class_init(ctx, (ZVectorClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 87 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 274 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_item"), (ZObjectSignalHandler) get_item);
#line 282 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_item"), (ZObjectSignalHandler) set_item);
#line 331 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("push_back"), (ZObjectSignalHandler) push_back);
#line 344 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("pop_back"), (ZObjectSignalHandler) pop_back);
#line 365 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert"), (ZObjectSignalHandler) insert);
#line 391 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert_range"), (ZObjectSignalHandler) insert_range);
#line 437 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase"), (ZObjectSignalHandler) erase);
#line 488 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase1"), (ZObjectSignalHandler) erase1);
#line 504 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase1_increment"), (ZObjectSignalHandler) erase1_increment);
#line 530 "z-vector.zco"
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
#line 28 "z-vector.zco"
static void z_vector_init(Self *self)
{
 selfp->head = z_vector_segment_new(CTX);

 selfp->tail = selfp->head;
 z_object_ref(Z_OBJECT(selfp->tail));

 selfp->item_size = 0;
 selfp->storage_mode = 0;
 selfp->is_insert_only_mode = 0;
 selfp->count = 0;
 selfp->userdata = 0;
 selfp->item_construct = 0;
 selfp->item_destruct = 0;
 }
#line 44 "z-vector.zco"
#define PARENT_HANDLER self->_global->__parent_reset
static void  z_vector_reset(ZObject *object)
{
 Self *self = (Self *) object;

 clear(self);

 if (selfp->head)
 z_object_unref(Z_OBJECT(selfp->head));

 if (selfp->tail)
 z_object_unref(Z_OBJECT(selfp->tail));

 selfp->head = z_vector_segment_new(CTX);

 selfp->tail = selfp->head;
 z_object_ref(Z_OBJECT(selfp->tail));

 selfp->item_size = 0;
 selfp->storage_mode = 0;
 selfp->is_insert_only_mode = 0;
 selfp->count = 0;
 selfp->userdata = 0;
 selfp->item_construct = 0;
 selfp->item_destruct = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 72 "z-vector.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_vector_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 clear(self);

 if (selfp->head)
 z_object_unref(Z_OBJECT(selfp->head));

 if (selfp->tail)
 z_object_unref(Z_OBJECT(selfp->tail));

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 87 "z-vector.zco"
Self * z_vector_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 95 "z-vector.zco"
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
#line 109 "z-vector.zco"
void z_vector_set_is_insert_only_mode(Self *self, int  value)
{
 selfp->is_insert_only_mode = value;
 }
#line 120 "z-vector.zco"
void z_vector_set_item_construct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_construct = value;
 }
#line 132 "z-vector.zco"
void z_vector_set_item_destruct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_destruct = value;
 }
#line 142 "z-vector.zco"
void z_vector_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
#line 151 "z-vector.zco"
ZVectorIter *  z_vector_get_begin(Self *self)
{
 return z_vector_segment_get_begin(selfp->head);
 }
#line 161 "z-vector.zco"
ZVectorIter *  z_vector_get_end(Self *self)
{
 return z_vector_segment_get_end(selfp->tail);
 }
#line 173 "z-vector.zco"
int  z_vector_get_size(Self *self)
{
 return selfp->count;
 }
#line 177 "z-vector.zco"
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
 selfp->tail->next = new_tail;

 z_object_ref(Z_OBJECT(new_tail));

 /* No need to unref the old tail. We'll just assume that the reference
                                           is now owned by the new tail. */
 new_tail->prev = selfp->tail;
 new_tail->next = NULL;

 if (!selfp->tail)
 selfp->head = new_tail;

 selfp->tail = new_tail;
 }

 selfp->count = value;

 } else if (selfp->count > value && !selfp->is_insert_only_mode) {
 /* Shrink vector */
 
 int difference = selfp->count - value;

 while (difference) {
 int tail_size = z_vector_segment_get_size(selfp->tail);
 if (tail_size <= difference) {
 /* The current tail has a reference from its previous node (+1)
                                                   and from the vector itself (+1) for a total ref-count of 2.

                                                   The new tail has a reference from its previous node (+1)
                                                   and from its next node (the current tail) (+1) for a total
                                                   ref-count of 2.

                                                   For the new tail, the ref-count remains unchanged so we needn't
                                                   call ref/unref on it. For the old tail, it loses a reference
                                                   from its previous node (-1) and from the vector itself (-1).
                                                 */

 ZVectorSegment *old_tail = selfp->tail;
 selfp->tail = old_tail->prev;
 old_tail->prev = NULL;

 if (selfp->tail) {
 selfp->tail->next = NULL;
 z_object_unref(Z_OBJECT(old_tail));
 } else {
 selfp->head = NULL;
 }

 z_object_unref(Z_OBJECT(old_tail));

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
#line 266 "z-vector.zco"
int  z_vector_get_is_empty(Self *self)
{
 return get_size(self) == 0;
 }
#line 274 "z-vector.zco"
void *  z_vector_get_item(Self *self,ZVectorIter *iter)
{
 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 return z_vector_segment_get_item(segment, iter, selfp->item_size, selfp->storage_mode);
 }
#line 282 "z-vector.zco"
int  z_vector_set_item(Self *self,ZVectorIter *iter,void *item)
{
 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 return z_vector_segment_set_item(segment, iter, item, selfp->item_size, selfp->storage_mode);
 }
#line 291 "z-vector.zco"
void *  z_vector_get_front(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_segment(iter, selfp->head);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;
 }
#line 299 "z-vector.zco"
void z_vector_set_front(Self *self, void *  value)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_segment(iter, selfp->head);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
#line 311 "z-vector.zco"
void *  z_vector_get_back(Self *self)
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;

 }
#line 320 "z-vector.zco"
void z_vector_set_back(Self *self, void *  value)
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
#line 331 "z-vector.zco"
void  z_vector_push_back(Self *self,void *item)
{
 /*  increase the size of the vector by 1 */
 int size = get_size(self);
 set_size(self, size + 1);

 /* set the last item of the vector */
 set_back(self, item);
 }
#line 344 "z-vector.zco"
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
#line 365 "z-vector.zco"
int  z_vector_insert(Self *self,ZVectorIter *iter,int n,void *item)
{
 /* We not be inserting the new elements at the back of the vector
                   so we also reject this operation in insert only mode */
 if (selfp->is_insert_only_mode)
 return -1;

 ZVectorSegment *segment = z_vector_iter_get_segment(iter);
 z_vector_segment_insert(segment, iter, n, item, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_construct, selfp->item_destruct);

 selfp->count += n;
 }
#line 391 "z-vector.zco"
int  z_vector_insert_range(Self *self,ZVectorIter *iter,ZVector *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end)
{
 /* We not be inserting the new elements at the back of the vector
                   so we also reject this operation in insert only mode */
 if (selfp->is_insert_only_mode)
 return -1;

 ZVectorSegment *target_segment = z_vector_iter_get_segment(iter);
 ZVectorSegment *source_start_segment = z_vector_iter_get_segment(src_iter_start);
 ZVectorSegment *source_end_segment = z_vector_iter_get_segment(src_iter_end);

 ZVectorSegment *source_segment = source_start_segment;
 int count = 0;

 while (1) {
 if (source_segment == source_start_segment) {
 if (source_segment == source_end_segment)
 count += z_vector_segment_insert_range(target_segment, iter, source_start_segment, src_iter_start,
 src_iter_end, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_destruct);

 else
 count += z_vector_segment_insert_range(target_segment, iter, source_start_segment, src_iter_start,
 NULL, selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_destruct);

 } else if (source_segment == source_end_segment) {
 count += z_vector_segment_insert_range(target_segment, iter, source_end_segment, NULL, src_iter_end,
 selfp->item_size, selfp->storage_mode, selfp->userdata,
 selfp->item_construct, selfp->item_destruct);

 } else {
 count += z_vector_segment_insert_segment(target_segment, source_segment, selfp->item_size);
 }

 if (source_segment == source_end_segment)
 break;

 source_segment = source_segment->next;
 }


 selfp->count += count;
 }
#line 437 "z-vector.zco"
int  z_vector_erase(Self *self,ZVectorIter *start,ZVectorIter *end)
{
 if (selfp->is_insert_only_mode)
 return -1;

 ZVectorSegment *start_segment = z_vector_iter_get_segment(start);
 ZVectorSegment *end_segment = z_vector_iter_get_segment(end);
 ZVectorSegment *segment = start_segment;
 int count = 0;
 
 while (1) {
 if (segment == start_segment) {
 if (segment == end_segment)
 count += z_vector_segment_erase(start_segment, start, end, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_destruct);

 else
 count += z_vector_segment_erase(start_segment, start, NULL, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_destruct);

 } else if (segment == end_segment) {
 count += z_vector_segment_erase(end_segment, NULL, end, selfp->item_size, selfp->storage_mode,
 selfp->userdata, selfp->item_destruct);

 } else {
 segment->prev->next = segment->next;
 segment->next->prev = segment->prev;

 /* 2 unrefs since it lost two references. one from the previous node
                                   and one from the next node */
 z_object_unref(Z_OBJECT(segment));
 z_object_unref(Z_OBJECT(segment));
 }

 if (segment == end_segment)
 break;

 segment = segment->next;
 }

 if (start_segment != end_segment) {
 start_segment->next = end_segment;
 end_segment->prev = start_segment;
 }

 selfp->count -= count;

 return 0;
 }
#line 488 "z-vector.zco"
int  z_vector_erase1(Self *self,ZVectorIter *iter)
{
 int rc;
 ZVectorIter *next = z_vector_iter_dup(iter);

 z_vector_iter_increment(next);
 rc = erase(self, iter, next);

 z_object_unref(Z_OBJECT(next));

 return rc;
 }
#line 504 "z-vector.zco"
int  z_vector_erase1_increment(Self *self,ZVectorIter *iter)
{
 int rc;
 ZVectorIter *temp = get_begin(self);
 
 if (z_vector_iter_is_equal(iter, temp)) {
 /* iterator is pointing to the first element of the vector */
 rc = erase1(self, iter);

 z_object_unref(Z_OBJECT(temp));
 temp = get_begin(self);
 z_vector_iter_set_index(iter, z_vector_iter_get_index(temp));

 } else {
 z_vector_iter_set_index(temp, z_vector_iter_get_index(iter));
 z_vector_iter_decrement(iter);
 rc = erase1(self, temp);
 z_vector_iter_increment(iter);
 }

 z_object_unref(Z_OBJECT(temp));

 return rc;
 }
#line 530 "z-vector.zco"
int  z_vector_clear(Self *self)
{
 if (selfp->count == 0)
 return 0;

 if (selfp->is_insert_only_mode)
 return -1;

 set_size(self, 0);

 return 0;
 }

#line 542 "z-vector.zco"


