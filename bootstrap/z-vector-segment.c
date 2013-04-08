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
#include <z-memory-allocator.h>
#include <z-vector-segment.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVectorSegment
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_vector_segment_new(ctx,allocator)
#define INIT_EXISTS
#line 26 "z-vector-segment.zco"
#define init z_vector_segment_init
#line 69 "z-vector-segment.zco"
#define new z_vector_segment_new
#line 77 "z-vector-segment.zco"
#define get_prev z_vector_segment_get_prev
#line 84 "z-vector-segment.zco"
#define set_prev z_vector_segment_set_prev
#line 98 "z-vector-segment.zco"
#define get_next z_vector_segment_get_next
#line 105 "z-vector-segment.zco"
#define set_next z_vector_segment_set_next
#line 122 "z-vector-segment.zco"
#define get_size z_vector_segment_get_size
#line 127 "z-vector-segment.zco"
#define set_size z_vector_segment_set_size
#line 185 "z-vector-segment.zco"
#define get_capacity z_vector_segment_get_capacity
#line 190 "z-vector-segment.zco"
#define set_capacity z_vector_segment_set_capacity
#line 230 "z-vector-segment.zco"
#define is_in_bound z_vector_segment_is_in_bound
#line 243 "z-vector-segment.zco"
#define get_item z_vector_segment_get_item
#line 263 "z-vector-segment.zco"
#define set_item z_vector_segment_set_item
#line 290 "z-vector-segment.zco"
#define insert z_vector_segment_insert
#line 357 "z-vector-segment.zco"
#define get_begin z_vector_segment_get_begin
#line 369 "z-vector-segment.zco"
#define get_end z_vector_segment_get_end
#line 398 "z-vector-segment.zco"
#define insert_range z_vector_segment_insert_range
#line 502 "z-vector-segment.zco"
#define erase z_vector_segment_erase

int z_vector_segment_type_id = -1;

static Self *__z_vector_segment_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_vector_segment_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_vector_segment_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 26 "z-vector-segment.zco"
static void z_vector_segment_init(Self *self);
#line 36 "z-vector-segment.zco"
static void  z_vector_segment_reset(ZObject *object);
#line 54 "z-vector-segment.zco"
static void  z_vector_segment_dispose(ZObject *object);
#line 190 "z-vector-segment.zco"
static int  z_vector_segment_set_capacity(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct);
#line 576 "z-vector-segment.zco"
static void z_vector_segment_class_destroy(ZObjectGlobal *gbl);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorSegmentGlobal * z_vector_segment_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_vector_segment_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_vector_segment_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZVectorSegmentGlobal *global = (ZVectorSegmentGlobal *) malloc(sizeof(struct ZVectorSegmentGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorSegmentClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZVectorSegmentClass));
		global->common.name = "ZVectorSegment";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZVectorSegment temp;
		struct ZVectorSegmentClass temp_class;

		{
			struct ZObjectGlobal *p_global = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_global->common.vtable_off_list,
				p_global->common.vtable_off_size,
				&temp,
				&temp.parent_z_object);
			zco_inherit_vtable(
				&global->common.svtable_off_list,
				&global->common.svtable_off_size,
				p_global->common.svtable_off_list,
				p_global->common.svtable_off_size,
				&temp_class,
				&temp_class.parent_z_object);
			ZObjectClass *p1_class = CLASS_FROM_GLOBAL(p_global);
			ZObjectClass *p2_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			memcpy(p2_class, p1_class, sizeof(struct ZObjectClass));
		}
		if (z_vector_segment_type_id == -1)
			z_vector_segment_type_id = zco_allocate_type_id();
		global->common.id = z_vector_segment_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_vector_segment_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_vector_segment_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_vector_segment_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
#line 36 "z-vector-segment.zco"
		{
#line 36 "z-vector-segment.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
#line 36 "z-vector-segment.zco"
			global->__parent_reset = p_class->__reset;
#line 36 "z-vector-segment.zco"
			p_class->__reset = z_vector_segment_reset;
#line 36 "z-vector-segment.zco"
		}
#line 54 "z-vector-segment.zco"
		{
#line 54 "z-vector-segment.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
#line 54 "z-vector-segment.zco"
			global->__parent_dispose = p_class->__dispose;
#line 54 "z-vector-segment.zco"
			p_class->__dispose = z_vector_segment_dispose;
#line 54 "z-vector-segment.zco"
		}
#line 576 "z-vector-segment.zco"
		{
#line 576 "z-vector-segment.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
#line 576 "z-vector-segment.zco"
			global->__parent_class_destroy = p_class->__class_destroy;
#line 576 "z-vector-segment.zco"
			p_class->__class_destroy = z_vector_segment_class_destroy;
#line 576 "z-vector-segment.zco"
		}
		__z_vector_segment_class_init(ctx, (ZVectorSegmentClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
#line 69 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 122 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("get_size"), (ZObjectSignalHandler) get_size);
#line 127 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("set_size"), (ZObjectSignalHandler) set_size);
#line 185 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("get_capacity"), (ZObjectSignalHandler) get_capacity);
#line 230 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("is_in_bound"), (ZObjectSignalHandler) is_in_bound);
#line 243 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("get_item"), (ZObjectSignalHandler) get_item);
#line 263 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("set_item"), (ZObjectSignalHandler) set_item);
#line 290 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("insert"), (ZObjectSignalHandler) insert);
#line 398 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("insert_range"), (ZObjectSignalHandler) insert_range);
#line 502 "z-vector-segment.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("erase"), (ZObjectSignalHandler) erase);
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
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 26 "z-vector-segment.zco"
static void z_vector_segment_init(Self *self)
{
 selfp->start = 0;
 selfp->count = 0;
 selfp->capacity = 0;
 selfp->data = 0;
 selfp->prev = NULL;
 selfp->next = NULL;
 }
#line 36 "z-vector-segment.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_vector_segment_reset(ZObject *object)
{
 Self *self = (Self *) object;

 set_prev(self, NULL);
 set_next(self, NULL);

 if (selfp->data)
 free(selfp->data);
 
 selfp->data = 0;
 selfp->start = 0;
 selfp->count = 0;
 selfp->capacity = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 54 "z-vector-segment.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_vector_segment_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 set_prev(self, NULL);
 set_next(self, NULL);

 if (selfp->data)
 free(selfp->data);
 
 selfp->data = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 69 "z-vector-segment.zco"
Self * z_vector_segment_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
#line 77 "z-vector-segment.zco"
Self * z_vector_segment_get_prev(Self *self)
{
 if (selfp->prev)
 z_object_ref(Z_OBJECT(selfp->prev));

 return selfp->prev;
 }
#line 84 "z-vector-segment.zco"
void z_vector_segment_set_prev(Self *self, Self * value)
{
 if (selfp->prev)
 z_object_unref(Z_OBJECT(selfp->prev));

 selfp->prev = value;

 if (value)
 z_object_ref(Z_OBJECT(value));
 }
#line 98 "z-vector-segment.zco"
Self * z_vector_segment_get_next(Self *self)
{
 if (selfp->next)
 z_object_ref(Z_OBJECT(selfp->next));

 return selfp->next;
 }
#line 105 "z-vector-segment.zco"
void z_vector_segment_set_next(Self *self, Self * value)
{
 if (selfp->next)
 z_object_unref(Z_OBJECT(selfp->next));

 selfp->next = value;

 if (value)
 z_object_ref(Z_OBJECT(value));
 }
#line 122 "z-vector-segment.zco"
int  z_vector_segment_get_size(Self *self)
{
 return selfp->count;
 }
#line 127 "z-vector-segment.zco"
int  z_vector_segment_set_size(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct)
{
 int rc = 0;

 if (selfp->count < value) {
 /* grow the vector */
 if (selfp->capacity < value) {
 rc = set_capacity(self, value * 2, item_size, storage_mode, userdata,
 item_construct, item_destruct);
 
 if (rc)
 goto done;
 }

 if (item_construct) {
 int i;

 if (storage_mode == 0) {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * item_size;
 item_construct(selfp->data + selfp->start + offset, userdata);
 }
 } else {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * item_size;
 item_construct(*((void **)(selfp->data + selfp->start + offset)), userdata);
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
 item_destruct(selfp->data + selfp->start + offset, userdata);
 }
 } else {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * item_size;
 item_destruct(*((void **)(selfp->data + selfp->start + offset)), userdata);
 }
 }
 } 
 }

 selfp->count = value;

done:
 return rc;
 }
#line 185 "z-vector-segment.zco"
int  z_vector_segment_get_capacity(Self *self)
{
 return selfp->capacity;
 }
#line 190 "z-vector-segment.zco"
static int  z_vector_segment_set_capacity(Self *self,int value,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_construct,ZVectorItemCallback item_destruct)
{
 if (value < selfp->count) {
 set_size(self, value, item_size, storage_mode, userdata, item_construct, item_destruct);
 selfp->count = value;
 }

 if (value) {
 int min_segment_capacity_by_size = zco_context_get_min_segment_capacity_by_size(CTX_FROM_OBJECT(self));
 int min_segment_capacity_by_count = zco_context_get_min_segment_capacity_by_count(CTX_FROM_OBJECT(self));

 /* restrict minimum segment size by count */
 if (value < min_segment_capacity_by_count)
 value = min_segment_capacity_by_count;

 /* restrict minimum segment size by size in bytes */
 if (value * item_size < min_segment_capacity_by_size)
 value = (min_segment_capacity_by_size + item_size - 1) / item_size;

 if (selfp->data) {
 /* FIXME: We cannot resize the buffer until we have an allocator to do so */
 return -1;
 } else {
 selfp->capacity = value;
 selfp->data = malloc(value * item_size);
 }

 } else if (selfp->data) {
 selfp->capacity = 0;

 free(selfp->data);
 selfp->data = NULL;
 }

 return 0;
 }
#line 230 "z-vector-segment.zco"
int  z_vector_segment_is_in_bound(Self *self,ZVectorIter *iter)
{
 int index = z_vector_iter_get_index(iter);

 if (index >= 0 && index < selfp->count)
 return 1;

 else
 return 0;
 }
#line 243 "z-vector-segment.zco"
void *  z_vector_segment_get_item(Self *self,ZVectorIter *iter,int item_size,int storage_mode)
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * item_size;

 if (is_in_bound(self, iter)) {
 if (storage_mode == 0)
 return selfp->data + selfp->start + offset;
 else
 return *((void **)(selfp->data + selfp->start + offset));

 } else {
 fprintf(stderr, "Index out of bound. max=%d, index=%d\n", selfp->count-1, index);
 }

 return NULL;
 }
#line 263 "z-vector-segment.zco"
int  z_vector_segment_set_item(Self *self,ZVectorIter *iter,void *item,int item_size,int storage_mode)
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * item_size;

 if (index >= 0 && index < selfp->count) {
 if (storage_mode == 0)
 memcpy(selfp->data + selfp->start + offset, item, item_size);
 else
 memcpy(selfp->data + selfp->start + offset, &item, item_size);

 return 0;
 }

 return ERANGE;
 }
#line 290 "z-vector-segment.zco"
int  z_vector_segment_insert(Self *self,ZVectorIter *iter,int n,void *item,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct)
{
 /* increase the size of the vector */

 int size = get_size(self);
 int rc = set_size(self, size + n, item_size, storage_mode, NULL, NULL, NULL);

 if (rc)
 return rc;

 assert(size + n == get_size(self));
 //assert(self == z_vector_iter_get_segment(iter));

 /* make a copy of the iterator */
 ZVectorIter *it = z_vector_iter_dup(iter);

 /* shift all elements in [it,inf) forward */
 int index = z_vector_iter_get_index(it);
 assert(size >= index);

 if (size > index) {
 void *base = selfp->data + selfp->start;
 memmove(base + (index + n) * item_size,
 base + index * item_size,
 (size - index) * item_size);
 }

 int i;

 if (item_copy_construct) {
 int i;

 if (storage_mode == 0) {
 for (i=0; i<n; ++i) {
 set_item(self, it, item, item_size, storage_mode);
 z_vector_iter_increment(it);

 int offset = (index + i) * item_size;
 item_copy_construct(selfp->data + selfp->start + offset, userdata);
 }

 } else {
 for (i=0; i<n; ++i) {
 set_item(self, it, item, item_size, storage_mode);
 z_vector_iter_increment(it);

 int offset = (index + i) * item_size;
 item_copy_construct(*((void **)(selfp->data + selfp->start + offset)), userdata);
 }
 }
 } else {
 for (i=0; i<n; ++i) {
 set_item(self, it, item, item_size, storage_mode);
 z_vector_iter_increment(it);
 }
 }


 z_object_unref(Z_OBJECT(it));

 return 0;
 }
#line 357 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_begin(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_segment(iter, self);
 return iter;
 }
#line 369 "z-vector-segment.zco"
ZVectorIter *  z_vector_segment_get_end(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_iter_set_segment(iter, self);
 z_vector_iter_set_index(iter, get_size(self)-1);
 z_vector_iter_increment(iter);
 return iter;
 }
#line 398 "z-vector-segment.zco"
int  z_vector_segment_insert_range(Self *self,ZVectorIter *iter,ZVectorSegment *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end,int item_size,int storage_mode,void *userdata,ZVectorItemCallback item_copy_construct)
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
 int rc = set_size(self, size + n, item_size, storage_mode, NULL, NULL, NULL);

 if (rc) {
 /* all return codes must be non-positive */
 assert(rc < 0);
 n = rc;
 goto done;
 }

 int index = z_vector_iter_get_index(dest_it);

 /* shift all elements in [dest_it,inf) forward */
 void *base = selfp->data + selfp->start;
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
 set_item(self, dest_it, data, item_size, storage_mode);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);

 int offset = (index + i) * item_size;
 item_copy_construct(selfp->data + selfp->start + offset, userdata);
 }

 } else {
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1, item_size, storage_mode);
 set_item(self, dest_it, data, item_size, storage_mode);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);

 int offset = (index + i) * item_size;
 item_copy_construct(*((void **)(selfp->data + selfp->start + offset)), userdata);
 }
 }
 } else {
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1, item_size, storage_mode);
 set_item(self, dest_it, data, item_size, storage_mode);

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
#line 502 "z-vector-segment.zco"
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
 int it1_index = z_vector_iter_get_index(it1);
 int it2_index = z_vector_iter_get_index(it2);
 void *base = selfp->data + selfp->start;

 if (self == it2_segment) {
 memmove(base + (it1_index) * item_size,
 base + (it1_index + n) * item_size,
 (size - it2_index) * item_size);
 } 

 z_object_unref(Z_OBJECT(it2_segment));

 /* decrease the size of the vector */
 selfp->count = size - n;

 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));

 return n;
 }
#line 576 "z-vector-segment.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_vector_segment_class_destroy(ZObjectGlobal *gbl)
{
	ZVectorSegmentGlobal *_global = (ZVectorSegmentGlobal *) gbl;

}

#undef PARENT_HANDLER

#line 576 "z-vector-segment.zco"


