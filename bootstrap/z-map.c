/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-map.c: Bootstrap file for z-map.zco
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

#line 21 "z-map.zco"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <math.h>


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-map.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZMap
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_map_new(ctx)
#define INIT_EXISTS
#line 31 "z-map.zco"
#define init z_map_init
#line 76 "z-map.zco"
#define new z_map_new
#line 84 "z-map.zco"
#define set_userdata z_map_set_userdata
#line 92 "z-map.zco"
#define set_key_destruct z_map_set_key_destruct
#line 100 "z-map.zco"
#define set_value_destruct z_map_set_value_destruct
#line 108 "z-map.zco"
#define get_begin z_map_get_begin
#line 122 "z-map.zco"
#define get_end z_map_get_end
#line 136 "z-map.zco"
#define get_is_empty z_map_get_is_empty
#line 144 "z-map.zco"
#define get_size z_map_get_size
#line 150 "z-map.zco"
#define clear z_map_clear
#line 155 "z-map.zco"
#define get_pivot z_map_get_pivot
#line 185 "z-map.zco"
#define find_item z_map_find_item
#line 268 "z-map.zco"
#define find z_map_find
#line 289 "z-map.zco"
#define get_key_internal z_map_get_key_internal
#line 294 "z-map.zco"
#define get_value_internal z_map_get_value_internal
#line 299 "z-map.zco"
#define set_key_internal z_map_set_key_internal
#line 304 "z-map.zco"
#define set_value_internal z_map_set_value_internal
#line 309 "z-map.zco"
#define get_key z_map_get_key
#line 320 "z-map.zco"
#define get_value z_map_get_value
#line 331 "z-map.zco"
#define set_value z_map_set_value
#line 342 "z-map.zco"
#define item_destroy z_map_item_destroy
#line 361 "z-map.zco"
#define add_item z_map_add_item
#line 419 "z-map.zco"
#define assign z_map_assign
#line 424 "z-map.zco"
#define insert z_map_insert
#line 429 "z-map.zco"
#define erase z_map_erase
#line 459 "z-map.zco"
#define erase1 z_map_erase1
#line 469 "z-map.zco"
#define erase1_inc z_map_erase1_inc
#line 489 "z-map.zco"
#define lower_bound z_map_lower_bound
#line 507 "z-map.zco"
#define upper_bound z_map_upper_bound
#line 545 "z-map.zco"
#define set_compare z_map_set_compare

int z_map_type_id = -1;

static Self *__z_map_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_map_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_map_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 31 "z-map.zco"
static void z_map_init(Self *self);
#line 45 "z-map.zco"
static void  z_map_reset(ZObject *object);
#line 67 "z-map.zco"
static void  z_map_dispose(ZObject *object);
#line 155 "z-map.zco"
static void  z_map_get_pivot(Self *self,ZVectorIter *first,ZVectorIter *last,ZVectorIter *pivot);
#line 185 "z-map.zco"
static void * z_map_find_item(Self *self,const void *key,int *bound,ZMapIter *pivot);
#line 289 "z-map.zco"
static void * z_map_get_key_internal(void *item);
#line 294 "z-map.zco"
static void * z_map_get_value_internal(void *item);
#line 299 "z-map.zco"
static void  z_map_set_key_internal(void *item,void *key);
#line 304 "z-map.zco"
static void  z_map_set_value_internal(void *item,void *value);
#line 342 "z-map.zco"
static void  z_map_item_destroy(void *item,void *userdata);
#line 361 "z-map.zco"
static int  z_map_add_item(Self *self,void *key,void *value,int allow_replace);
#line 550 "z-map.zco"
static void z_map_class_destroy(ZObjectGlobal *gbl);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZMapGlobal * z_map_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_map_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_map_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZMapGlobal *global = (ZMapGlobal *) malloc(sizeof(struct ZMapGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZMapClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZMapClass));
		global->common.name = "ZMap";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.is_object = 1;

		struct ZMap temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			if (p_class->common.id > class_off_size)
				class_off_size = p_class->common.id;
		}
		class_off_list = malloc(sizeof(unsigned long) * (class_off_size+1));
		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_class->common.vtable_off_list,
				p_class->common.vtable_off_size,
				&temp,
				&temp.parent_z_object);
			memcpy((char *) CLASS_FROM_GLOBAL(global) + offset, CLASS_FROM_GLOBAL(p_class), sizeof(struct ZObjectClass));
			class_off_list[p_class->common.id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		((ZObjectClass *) CLASS_FROM_GLOBAL(global))->class_off_list = class_off_list;
		if (z_map_type_id == -1)
			z_map_type_id = zco_allocate_type_id();
		global->common.id = z_map_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_map_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_map_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
#line 45 "z-map.zco"
		{
#line 45 "z-map.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 45 "z-map.zco"
			global->__parent_reset = p_class->__reset;
#line 45 "z-map.zco"
			p_class->__reset = z_map_reset;
#line 45 "z-map.zco"
		}
#line 67 "z-map.zco"
		{
#line 67 "z-map.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 67 "z-map.zco"
			global->__parent_dispose = p_class->__dispose;
#line 67 "z-map.zco"
			p_class->__dispose = z_map_dispose;
#line 67 "z-map.zco"
		}
#line 550 "z-map.zco"
		{
#line 550 "z-map.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 550 "z-map.zco"
			global->__parent_class_destroy = p_class->__class_destroy;
#line 550 "z-map.zco"
			p_class->__class_destroy = z_map_class_destroy;
#line 550 "z-map.zco"
		}
		__z_map_class_init(ctx, (ZMapClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
#line 76 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 150 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("clear"), (ZObjectSignalHandler) clear);
#line 268 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("find"), (ZObjectSignalHandler) find);
#line 309 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("get_key"), (ZObjectSignalHandler) get_key);
#line 320 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("get_value"), (ZObjectSignalHandler) get_value);
#line 331 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("set_value"), (ZObjectSignalHandler) set_value);
#line 419 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("assign"), (ZObjectSignalHandler) assign);
#line 424 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("insert"), (ZObjectSignalHandler) insert);
#line 429 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("erase"), (ZObjectSignalHandler) erase);
#line 459 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("erase1"), (ZObjectSignalHandler) erase1);
#line 469 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("erase1_inc"), (ZObjectSignalHandler) erase1_inc);
#line 489 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("lower_bound"), (ZObjectSignalHandler) lower_bound);
#line 507 "z-map.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("upper_bound"), (ZObjectSignalHandler) upper_bound);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZMapGlobal *) global);
		#endif
		return global;
	}
	return (ZMapGlobal *) *global_ptr;
}

void __z_map_class_init(struct zco_context_t *ctx, ZMapClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_map_init(struct zco_context_t *ctx, Self *self)
{
	struct ZMapGlobal *_global = z_map_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 31 "z-map.zco"
static void z_map_init(Self *self)
{
 selfp->data = z_vector_new(CTX_FROM_OBJECT(self));
 z_vector_set_item_size(selfp->data, 2 * sizeof(void *));

 selfp->compare = NULL;
 selfp->key_destruct = NULL;
 selfp->value_destruct = NULL;
 selfp->userdata = NULL;

 z_vector_set_userdata(selfp->data, self);
 z_vector_set_item_destruct(selfp->data, item_destroy);
 }
#line 45 "z-map.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_map_reset(ZObject *object)
{
 Self *self = (Self *) object;

 z_object_unref(Z_OBJECT(selfp->data));
 selfp->data = z_vector_new(CTX_FROM_OBJECT(self));

 //z_object_reset(Z_OBJECT(selfp->data));

 z_vector_set_item_size(selfp->data, 2 * sizeof(void *));

 selfp->compare = NULL;
 selfp->key_destruct = NULL;
 selfp->value_destruct = NULL;
 selfp->userdata = NULL;

 z_vector_set_userdata(selfp->data, self);
 z_vector_set_item_destruct(selfp->data, item_destroy);

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 67 "z-map.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_map_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 z_object_unref(Z_OBJECT(selfp->data));

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 76 "z-map.zco"
Self * z_map_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 84 "z-map.zco"
void z_map_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
#line 92 "z-map.zco"
void z_map_set_key_destruct(Self *self, ZMapItemCallback  value)
{
 selfp->key_destruct = value;
 }
#line 100 "z-map.zco"
void z_map_set_value_destruct(Self *self, ZMapItemCallback  value)
{
 selfp->value_destruct = value;
 }
#line 108 "z-map.zco"
ZMapIter * z_map_get_begin(Self *self)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);
 ZMapIter *it = z_map_iter_new(CTX_FROM_OBJECT(self));

 z_map_iter_set_index(it, z_vector_iter_get_absolute_index(ptr));
 z_object_unref(Z_OBJECT(ptr));

 return it;
 }
#line 122 "z-map.zco"
ZMapIter * z_map_get_end(Self *self)
{
 ZVectorIter *ptr = z_vector_get_end(selfp->data);
 ZMapIter *it = z_map_iter_new(CTX_FROM_OBJECT(self));

 z_map_iter_set_index(it, z_vector_iter_get_absolute_index(ptr));
 z_object_unref(Z_OBJECT(ptr));

 return it;
 }
#line 136 "z-map.zco"
int  z_map_get_is_empty(Self *self)
{
 return get_size(self) == 0;
 }
#line 144 "z-map.zco"
int  z_map_get_size(Self *self)
{
 return z_vector_get_size(selfp->data);
 }
#line 150 "z-map.zco"
void  z_map_clear(Self *self)
{
 z_vector_clear(selfp->data);
 }
#line 155 "z-map.zco"
static void  z_map_get_pivot(Self *self,ZVectorIter *first,ZVectorIter *last,ZVectorIter *pivot)
{
 /* The pivot is the iterator that is exactly at the center of [first,last). 
		   In some cases, it is possible that there are two cneter iterators in a
		   range. It is important to always pick the higher of the two so that it
		   will not equal the 'first' iterator unless the range only consists of
		   one item. For example:

		   case #1: if first = 0, last = 3, the possible value for pivot is 1
		   case #2: if first = 0, last = 2, the possible values for pivot are 0,1
		   case #3: if first = 0, last = 1, the possible value for pivot is 0

		   If the lower of the two values were picked, the pivot value for cases 2
		   and 3 would be identical. This will not allow the caller to compare pivot
		   with another iterator to determine if any more iteration is possible.

		   If the higher of the two values were picked, the pivot value for case 2
		   and 3 would be different. This will allow the caller to compare the pivot
		   with 'first' to determine if any more iteration is possible. If the pivot
		   is equal to 'first' (which is no longer true for case 2), the range is
		   only composed of one element and no further iterations are needed.
		 */

 int begin_idx = z_vector_iter_get_absolute_index(first);
 int end_idx = z_vector_iter_get_absolute_index(last);
 int offset = (end_idx - begin_idx) >> 1;

 z_vector_iter_advance(pivot, begin_idx + offset);
 }
#line 185 "z-map.zco"
static void * z_map_find_item(Self *self,const void *key,int *bound,ZMapIter *pivot)
{
 ZVectorIter *first, *last, *pivot_ptr;

 first = z_vector_get_begin(selfp->data);
 last = z_vector_get_end(selfp->data);

 while (1) {
 void *pivot_key;
 void *item;

 pivot_ptr = z_vector_get_begin(selfp->data);
 get_pivot(self, first, last, pivot_ptr);
 item = z_vector_get_item(selfp->data, pivot_ptr);
 pivot_key = get_key_internal(item);
 int rc = selfp->compare(self, key, pivot_key);

 if (rc < 0) {
 /* keep the lower half. pivot is higher than target */
 if (z_vector_iter_is_equal(first, pivot_ptr)) {
 if (bound)
 *bound = 1;

 z_map_iter_set_index(pivot, z_vector_iter_get_absolute_index(pivot_ptr));
 z_object_unref(Z_OBJECT(pivot_ptr));
 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));
 return 0;
 }

 z_vector_iter_assign(last, pivot_ptr);

 } else if (rc > 0) {
 /* keep the upper half. pivot_ptr value is lower than target */
 if (z_vector_iter_is_equal(first, pivot_ptr)) {
 if (bound)
 *bound = -1;

 z_map_iter_set_index(pivot, z_vector_iter_get_absolute_index(pivot_ptr));
 z_object_unref(Z_OBJECT(pivot_ptr));
 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));
 return 0;
 }

 z_vector_iter_increment(pivot_ptr);

 if (!z_vector_iter_is_in_bound(pivot_ptr)) {
 /* revert to previous index (which is the highest valid index) */
 z_vector_iter_decrement(pivot_ptr);

 if (bound)
 *bound = -1;

 z_map_iter_set_index(pivot, z_vector_iter_get_absolute_index(pivot_ptr));
 z_object_unref(Z_OBJECT(pivot_ptr));
 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));
 return 0;
 }

 z_vector_iter_assign(first, pivot_ptr);

 } else {
 if (bound)
 *bound = 0;

 z_map_iter_set_index(pivot, z_vector_iter_get_absolute_index(pivot_ptr));
 z_object_unref(Z_OBJECT(pivot_ptr));
 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));
 return get_value_internal(item);
 }

 z_object_unref(Z_OBJECT(pivot_ptr));
 }

 z_map_iter_set_index(pivot, z_vector_iter_get_absolute_index(pivot_ptr));
 z_object_unref(Z_OBJECT(pivot_ptr));
 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));
 }
#line 268 "z-map.zco"
ZMapIter * z_map_find(Self *self,const void *key)
{
 ZMapIter *it;
 int bound;

 if (get_is_empty(self)) {
 return NULL;

 } else {
 it = z_map_iter_new(CTX_FROM_OBJECT(self));
 find_item(self, key, &bound, it);

 if (bound == 0) {
 return it;
 } else {
 z_object_unref(Z_OBJECT(it));
 return NULL;
 }
 }
 }
#line 289 "z-map.zco"
static void * z_map_get_key_internal(void *item)
{
 return (void *)((unsigned long *)item)[0];
 }
#line 294 "z-map.zco"
static void * z_map_get_value_internal(void *item)
{
 return (void *)((unsigned long *)item)[1];
 }
#line 299 "z-map.zco"
static void  z_map_set_key_internal(void *item,void *key)
{
 ((unsigned long *)item)[0] = (unsigned long)key;
 }
#line 304 "z-map.zco"
static void  z_map_set_value_internal(void *item,void *value)
{
 ((unsigned long *)item)[1] = (unsigned long)value;
 }
#line 309 "z-map.zco"
void * z_map_get_key(Self *self,ZMapIter *it)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(ptr, z_map_iter_get_index(it));
 void *item = z_vector_get_item(selfp->data, ptr);
 z_object_unref(Z_OBJECT(ptr));

 return get_key_internal(item);
 }
#line 320 "z-map.zco"
void * z_map_get_value(Self *self,ZMapIter *it)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(ptr, z_map_iter_get_index(it));
 void *item = z_vector_get_item(selfp->data, ptr);
 z_object_unref(Z_OBJECT(ptr));

 return get_value_internal(item);
 }
#line 331 "z-map.zco"
void  z_map_set_value(Self *self,ZMapIter *it,void *value)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(ptr, z_map_iter_get_index(it));
 void *item = z_vector_get_item(selfp->data, ptr);
 z_object_unref(Z_OBJECT(ptr));

 set_value_internal(item, value);
 }
#line 342 "z-map.zco"
static void  z_map_item_destroy(void *item,void *userdata)
{
 ZMap *self = (ZMap *) userdata;
 void *key, *value;

 key = get_key_internal(item);
 value = get_value_internal(item);

 // FIXME
 //if (selfp->key_destruct == free)
 //abort();

 if (selfp->key_destruct)
 selfp->key_destruct(key, selfp->userdata);

 if (selfp->value_destruct) 
 selfp->value_destruct(value, selfp->userdata);
 }
#line 361 "z-map.zco"
static int  z_map_add_item(Self *self,void *key,void *value,int allow_replace)
{
 ZMapIter *it, *prev;
 unsigned long key_value[2];
 void *item;

 if (!get_is_empty(self) && (it = upper_bound(self, key))) {

 prev = z_map_iter_dup(it);
 z_map_iter_decrement(prev);

 ZVectorIter *prev_ptr = z_vector_get_begin(selfp->data);
 z_vector_iter_advance(prev_ptr, z_map_iter_get_index(prev));
 z_object_unref(Z_OBJECT(prev));

 if (z_vector_iter_is_in_bound(prev_ptr)) {
 item = z_vector_get_item(selfp->data, prev_ptr);

 if (selfp->compare(self, get_key_internal(item), key) == 0) {
 /* key already exists */

 if (allow_replace) {
 /* destroy the current item */
 item_destroy(item, self);

 /* add the new item */
 set_key_internal(item, key);
 set_value_internal(item, value);
 }

 z_object_unref(Z_OBJECT(prev_ptr));
 z_object_unref(Z_OBJECT(it));
 return -1;
 }
 }
 z_object_unref(Z_OBJECT(prev_ptr));

 key_value[0] = (unsigned long)key;
 key_value[1] = (unsigned long)value;

 ZVectorIter *it_ptr = z_vector_get_begin(selfp->data);
 z_vector_iter_advance(it_ptr, z_map_iter_get_index(it));
 z_vector_insert(selfp->data, it_ptr, 1, key_value);
 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(it_ptr));


 } else {

 key_value[0] = (unsigned long)key;
 key_value[1] = (unsigned long)value;

 z_vector_push_back(selfp->data, key_value);
 }

 return 0;
 }
#line 419 "z-map.zco"
int  z_map_assign(Self *self,void *key,void *value)
{
 return add_item(self, key, value, 1);
 }
#line 424 "z-map.zco"
int  z_map_insert(Self *self,void *key,void *value)
{
 return add_item(self, key, value, 0);
 }
#line 429 "z-map.zco"
void  z_map_erase(Self *self,ZMapIter *first,ZMapIter *last)
{
 ZVectorIter *p1, *p2;

 if (first == NULL)
 first = get_begin(self);
 else
 z_object_ref(Z_OBJECT(first));

 if (last == NULL)
 last = get_end(self);
 else
 z_object_ref(Z_OBJECT(last));


 p1 = z_vector_get_begin(selfp->data);
 p2 = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(p1, z_map_iter_get_index(first));
 z_vector_iter_advance(p2, z_map_iter_get_index(last));

 z_vector_erase(selfp->data, p1, p2);

 z_object_unref(Z_OBJECT(p1));
 z_object_unref(Z_OBJECT(p2));

 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));
 }
#line 459 "z-map.zco"
void  z_map_erase1(Self *self,ZMapIter *it)
{
 ZMapIter *end;

 end = z_map_iter_dup(it);
 z_map_iter_increment(end);
 erase(self, it, end);
 z_object_unref(Z_OBJECT(end));
 }
#line 469 "z-map.zco"
void  z_map_erase1_inc(Self *self,ZMapIter **it)
{
 ZMapIter *temp;

 temp = get_begin(self);

 if (z_map_iter_is_equal(*it, temp)) {
 /* iterator is pointing to the first element in the map */
 erase1(self, *it);
 z_object_unref(Z_OBJECT(*it));
 *it = get_begin(self);
 } else {
 z_object_unref(Z_OBJECT(temp));
 temp = z_map_iter_dup(*it);
 z_map_iter_decrement(*it);
 erase1(self, temp);
 z_map_iter_increment(*it);
 }
 }
#line 489 "z-map.zco"
ZMapIter * z_map_lower_bound(Self *self,void *key)
{
 ZMapIter *it;
 int bound;

 if (get_is_empty(self))
 return NULL;

 it = get_begin(self);
 find_item(self, key, &bound, it);

 if (bound > 0)
 /* 'it' is the upper bound, move one step back */
 z_map_iter_decrement(it);

 return it;
 }
#line 507 "z-map.zco"
ZMapIter * z_map_upper_bound(Self *self,void *key)
{
 ZMapIter *it;
 int bound;

 if (get_is_empty(self))
 return NULL;

 it = get_begin(self);
 find_item(self, key, &bound, it);

 /* Given that find_item() returns a bound value that is -1,0,+1 ,
		   we can perform some calculation on this number to determine how
		   many steps we need to move forward.

		   If bound == +1, the iterator points to an element whose key is
		   higher than the target key. Since the upper_bound is defined to
		   be an element with the lowest key value that is strictly higher
		   than the target, the iterator does not need to be changed.

		   If bound == 0, the iterator points to an element whose key is
		   same as the target key. We need to increment the iterator by 1 so
		   that it points to an element whose key is higher.

		   If bound == -1, the iterator points to an element whose key is
		   less than the target key. Since find_item() would return the
		   target element if it did exist, we can assume that the element after
		   the one return is higher than the target key; We need to increment
		   the iterator only by 1.  */

 if (bound <= 0)
 z_map_iter_increment(it);

 return it;
 }
#line 545 "z-map.zco"
void z_map_set_compare(Self *self, ZMapCompareFunc  value)
{
 selfp->compare = value;
 }
#line 550 "z-map.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_map_class_destroy(ZObjectGlobal *gbl)
{
	ZMapGlobal *_global = (ZMapGlobal *) gbl;

}

#undef PARENT_HANDLER

#line 550 "z-map.zco"


