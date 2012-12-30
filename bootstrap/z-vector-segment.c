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

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-vector-segment.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVectorSegment
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_vector_segment_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 25 "z-vector-segment.zco"
#define init z_vector_segment_init
#line 71 "z-vector-segment.zco"
#define new z_vector_segment_new
#line 82 "z-vector-segment.zco"
#define get_size z_vector_segment_get_size
#line 87 "z-vector-segment.zco"
#define set_size z_vector_segment_set_size
#line 142 "z-vector-segment.zco"
#define get_capacity z_vector_segment_get_capacity
#line 147 "z-vector-segment.zco"
#define set_capacity z_vector_segment_set_capacity
#line 176 "z-vector-segment.zco"
#define is_in_bound z_vector_segment_is_in_bound
#line 189 "z-vector-segment.zco"
#define get_item z_vector_segment_get_item
#line 209 "z-vector-segment.zco"
#define set_item z_vector_segment_set_item
#line 226 "z-vector-segment.zco"
#define insert_segment z_vector_segment_insert_segment
#line 247 "z-vector-segment.zco"
#define insert z_vector_segment_insert
#line 274 "z-vector-segment.zco"
#define get_begin z_vector_segment_get_begin
#line 286 "z-vector-segment.zco"
#define get_end z_vector_segment_get_end
#line 307 "z-vector-segment.zco"
#define insert_range z_vector_segment_insert_range
#line 363 "z-vector-segment.zco"
#define erase z_vector_segment_erase

int z_vector_segment_type_id = -1;

static Self *__z_vector_segment_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_vector_segment_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_vector_segment_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 25 "z-vector-segment.zco"
static void z_vector_segment_init(Self *self);
#line 34 "z-vector-segment.zco"
static void  z_vector_segment_reset(ZObject *object);
#line 55 "z-vector-segment.zco"
static void  z_vector_segment_dispose(ZObject *object);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorSegmentGlobal * z_vector_segment_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_vector_segment_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_vector_segment_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZVectorSegmentGlobal *global = (ZVectorSegmentGlobal *) malloc(sizeof(struct ZVectorSegmentGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorSegmentClass));
		memset(global->_class, 0, sizeof(struct ZVectorSegmentClass));
		global->name = "ZVectorSegment";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZVectorSegment temp;
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
		if (z_vector_segment_type_id == -1)
			z_vector_segment_type_id = zco_allocate_type_id();
		global->id = z_vector_segment_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_vector_segment_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_vector_segment_type_id);
		*global_ptr = global;
		
#line 34 "z-vector-segment.zco"
		{
#line 34 "z-vector-segment.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 34 "z-vector-segment.zco"
			global->__parent_reset = p_class->__reset;
#line 34 "z-vector-segment.zco"
			p_class->__reset = z_vector_segment_reset;
#line 34 "z-vector-segment.zco"
		}
#line 55 "z-vector-segment.zco"
		{
#line 55 "z-vector-segment.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 55 "z-vector-segment.zco"
			global->__parent_dispose = p_class->__dispose;
#line 55 "z-vector-segment.zco"
			p_class->__dispose = z_vector_segment_dispose;
#line 55 "z-vector-segment.zco"
		}
		__z_vector_segment_class_init(ctx, (ZVectorSegmentClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 71 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 82 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_size"), (ZObjectSignalHandler) get_size);
#line 87 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_size"), (ZObjectSignalHandler) set_size);
#line 142 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_capacity"), (ZObjectSignalHandler) get_capacity);
#line 147 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_capacity"), (ZObjectSignalHandler) set_capacity);
#line 176 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_in_bound"), (ZObjectSignalHandler) is_in_bound);
#line 189 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_item"), (ZObjectSignalHandler) get_item);
#line 209 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_item"), (ZObjectSignalHandler) set_item);
#line 226 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert_segment"), (ZObjectSignalHandler) insert_segment);
#line 247 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert"), (ZObjectSignalHandler) insert);
#line 307 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert_range"), (ZObjectSignalHandler) insert_range);
#line 363 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase"), (ZObjectSignalHandler) erase);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZVectorSegmentGlobal *) global);
		#endif
		return global;
	}
	return (ZVectorSegmentGlobal *) *global_ptr;
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
	struct ZVectorSegmentGlobal *_global = z_vector_segment_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 25 "z-vector-segment.zco"
static void z_vector_segment_init(Self *self)
{
 selfp->count = 0;
 selfp->capacity = 0;
 selfp->data = 0;
 self->prev = NULL;
 self->next = NULL;
 }
#line 34 "z-vector-segment.zco"
#define PARENT_HANDLER self->_global->__parent_reset
static void  z_vector_segment_reset(ZObject *object)
{
 Self *self = (Self *) object;

 if (self->prev)
 z_object_unref(Z_OBJECT(self->prev));

 if (self->next)
 z_object_unref(Z_OBJECT(self->next));


 selfp->count = 0;
 selfp->capacity = 0;
 selfp->data = 0;

 self->prev = NULL;
 self->next = NULL;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 55 "z-vector-segment.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_vector_segment_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 if (self->prev)
 z_object_unref(Z_OBJECT(self->prev));

 if (self->next)
 z_object_unref(Z_OBJECT(self->next));

 self->prev = NULL;
 self->next = NULL;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 71 "z-vector-segment.zco"
Self * z_vector_segment_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 82 "z-vector-segment.zco"
int  z_vector_segment_get_size(Self *self)
{
 return selfp->count;
 }
#line 87 "z-vector-segment.zco"
int  z_vector_segment_set_size(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct)
{
 if (selfp->count < value) {
 /* grow the vector */
 if (selfp->capacity < value) {
 set_capacity(self, value * 2, item_size, storage_mode, userdata,
 item_construct, item_destruct);
 }

 if (item_construct) {
 int i;

 if (storage_mode == 0) {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * item_size;
 item_construct(selfp->data + offset, userdata);
 }
 } else {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * item_size;
 item_construct(*((void **)(selfp->data + offset)), userdata);
 }
 }
 }

 } else if (selfp->count > value) {
 /* shrink the vector */
 if (item_destruct) {
 int i;

 if (storage_mode == 0) {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * item_size;
 item_destruct(selfp->data + offset, userdata);
 }
 } else {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * item_size;
 item_destruct(*((void **)(selfp->data + offset)), userdata);
 }
 }
 }
 }

 selfp->count = value;

 /* FIXME: Always realloc the buffer for now. Once we have an allocator that is able to resize
                   a buffer and fail if it's not possible, we can return a different return code here to notify
                   the caller that the set_size operation wasn't successful */
 return 0;
 }
#line 142 "z-vector-segment.zco"
int  z_vector_segment_get_capacity(Self *self)
{
 return selfp->capacity;
 }
#line 147 "z-vector-segment.zco"
void  z_vector_segment_set_capacity(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct)
{
 if (value < selfp->count) {
 set_size(self, value, item_size, storage_mode, userdata, item_construct, item_destruct);
 selfp->count = value;
 }

 selfp->capacity = value;

 if (value) {
 if (selfp->data) {
 int copy_size = selfp->count * item_size;
 void *b = malloc(value * item_size);
 memcpy(b, selfp->data, copy_size);
 free(selfp->data);
 selfp->data = b;
 } else {
 selfp->data = malloc(value * item_size);
 }

 } else if (selfp->data) {
 free(selfp->data);
 selfp->data = NULL;
 }
 }
#line 176 "z-vector-segment.zco"
int  z_vector_segment_is_in_bound(Self *self,ZVectorIter *iter)
{
 int index = z_vector_iter_get_index(iter);

 if (index >= 0 && index < selfp->count)
 return 1;

 else
 return 0;
 }
#line 189 "z-vector-segment.zco"
void *  z_vector_segment_get_item(Self *self,ZVectorIter *iter,int item_size,int storage_mode)
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * item_size;

 if (is_in_bound(self, iter)) {
 if (storage_mode == 0)
 return selfp->data + offset;
 else
 return *((void **)(selfp->data + offset));

 } else {
 fprintf(stderr, "Index out of bound. max=%d, index=%d\n", selfp->count-1, index);
 }

 return NULL;
 }
#line 209 "z-vector-segment.zco"
int  z_vector_segment_set_item(Self *self,ZVectorIter *iter,void *item,int item_size,int storage_mode)
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * item_size;

 if (index >= 0 && index < selfp->count) {
 if (storage_mode == 0)
 memcpy(selfp->data + offset, item, item_size);
 else
 memcpy(selfp->data + offset, &item, item_size);

 return 0;
 }

 return ERANGE;
 }
#line 226 "z-vector-segment.zco"
int  z_vector_segment_insert_segment(Self *self,ZVectorSegment *src,int item_size)
{
 ZVectorSegment *obj;

 obj = z_vector_segment_new(CTX);
 obj->_priv.count = src->_priv.count;
 obj->_priv.capacity = src->_priv.count;
 obj->next = self;
 obj->prev = self->prev;
 self->prev->next = obj;
 self->prev = obj;

 obj->_priv.data = malloc(src->_priv.capacity * item_size);
 memcpy(obj->_priv.data, src->_priv.data, src->_priv.count * item_size);

 return obj->_priv.count;
 }
#line 247 "z-vector-segment.zco"
void  z_vector_segment_insert(Self *self,ZVectorIter *iter,int n,void *item,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct)
{
 /* make a copy of the iterator */
 ZVectorIter *it = z_vector_iter_dup(iter);

 /* increase the size of the vector */
 int size = get_size(self);
 set_size(self, size + n, item_size, storage_mode, userdata, item_construct, item_destruct);

 /* shift all elements in [it,inf) forward */
 memmove(selfp->data + (z_vector_iter_get_index(it) + n) * item_size,
 selfp->data + z_vector_iter_get_index(it) * item_size,
 (size - z_vector_iter_get_index(it)) * item_size);

 int i;
 for (i=0; i<n; ++i) {
 set_item(self, it, item, item_size, storage_mode);
 z_vector_iter_increment(it);
 }

 z_object_unref(Z_OBJECT(it));
 }
#line 274 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_begin(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_segment(iter, self);
 return iter;
 }
#line 286 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_end(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_segment(iter, self);
 z_vector_iter_set_index(iter, get_size(self));
 return iter;
 }
#line 307 "z-vector-segment.zco"
int  z_vector_segment_insert_range(Self *self,ZVectorIter *iter,ZVectorSegment *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct)
{
 ZVectorIter *it1, *it2;
 ZVectorIter *dest_it;

 /* make a copy of the iterators */
 if (iter == NULL)
 dest_it = get_end(self);
 else
 dest_it = z_vector_iter_dup(iter);

 if (src_iter_start == NULL)
 it1 = get_begin(src);
 else
 it1 = z_vector_iter_dup(src_iter_start);

 if (src_iter_end == NULL)
 it2 = get_end(src);
 else
 it2 = z_vector_iter_dup(src_iter_end);
 
 /* compute the item count */
 int n = z_vector_iter_get_index(it2) - z_vector_iter_get_index(it1);

 assert(n >= 0);

 /* increase the size of the vector */
 int size = get_size(self);
 set_size(self, size + n, item_size, storage_mode, userdata, item_construct, item_destruct);

 /* shift all elements in [dest_it,inf) forward */
 memmove(selfp->data +
 (z_vector_iter_get_index(dest_it) + n) * item_size,
 selfp->data + z_vector_iter_get_index(dest_it) * item_size,
 (size - z_vector_iter_get_index(dest_it)) * item_size);

 /* insert the new item(s) */
 int i;
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1, item_size, storage_mode);
 set_item(self, dest_it, data, item_size, storage_mode);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);
 }

 z_object_unref(Z_OBJECT(it1));
 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(dest_it));

 return n;
 }
#line 363 "z-vector-segment.zco"
int  z_vector_segment_erase(Self *self,ZVectorIter *start,ZVectorIter *end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_destruct)
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
 int n = z_vector_iter_get_index(end) - z_vector_iter_get_index(start);

 if (n >= 0) {
 it1 = z_vector_iter_dup(start);
 it2 = z_vector_iter_dup(end);
 } else {
 it1 = z_vector_iter_dup(end);
 it2 = z_vector_iter_dup(start);
 n = -n;
 }

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
 int size = get_size(self);

 memmove(selfp->data + (z_vector_iter_get_index(it1)) * item_size,
 selfp->data + (z_vector_iter_get_index(it1) + n) * item_size,
 (size - z_vector_iter_get_index(it2)) * item_size);

 /* decrease the size of the vector */
 selfp->count = size - n;

 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));

 return n;
 }

#line 418 "z-vector-segment.zco"


