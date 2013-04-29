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
#include <z-memory-allocator.h>
#include <z-map.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZMap
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_map_new(ctx,allocator)
#define INIT_EXISTS
#define init z_map_init
#define new z_map_new
#define set_userdata z_map_set_userdata
#define set_key_destruct z_map_set_key_destruct
#define set_value_destruct z_map_set_value_destruct
#define get_begin z_map_get_begin
#define get_end z_map_get_end
#define get_is_empty z_map_get_is_empty
#define get_size z_map_get_size
#define clear z_map_clear
#define get_pivot z_map_get_pivot
#define find_item z_map_find_item
#define find z_map_find
#define get_key_internal z_map_get_key_internal
#define get_value_internal z_map_get_value_internal
#define set_key_internal z_map_set_key_internal
#define set_value_internal z_map_set_value_internal
#define get_key z_map_get_key
#define get_value z_map_get_value
#define set_value z_map_set_value
#define item_destroy z_map_item_destroy
#define add_item z_map_add_item
#define assign z_map_assign
#define insert z_map_insert
#define erase z_map_erase
#define erase1 z_map_erase1
#define erase1_inc z_map_erase1_inc
#define lower_bound z_map_lower_bound
#define upper_bound z_map_upper_bound
#define set_compare z_map_set_compare

int z_map_type_id = -1;

static Self *__z_map_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_map_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		ZMemoryAllocator *obj_allocator = ctx->fixed_allocator;
		if (obj_allocator)
			self = (Self *) z_memory_allocator_allocate(obj_allocator, sizeof(Self));
		else
			self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_map_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_map_init(Self *self);
static void  z_map_reset(ZObject *object);
static void  z_map_dispose(ZObject *object);
static void  z_map_get_pivot(Self *self,ZVectorIter *first,ZVectorIter *last,ZVectorIter *pivot);
static void * z_map_find_item(Self *self,const void *key,int *bound,ZMapIter *pivot);
static void * z_map_get_key_internal(void *item);
static void * z_map_get_value_internal(void *item);
static void  z_map_set_key_internal(void *item,void *key);
static void  z_map_set_value_internal(void *item,void *value);
static void  z_map_item_destroy(void *item,void *userdata);
static int  z_map_add_item(Self *self,void *key,void *value,int allow_replace);
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
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZMap temp;
		struct ZMapClass temp_class;

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
		if (z_map_type_id == -1)
			z_map_type_id = zco_allocate_type_id();
		global->common.id = z_map_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_map_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_map_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_map_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_map_reset;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_map_dispose;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_map_class_destroy;
		}
		__z_map_class_init(ctx, (ZMapClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		z_map_insert((ZMap *) global->common.method_map, strdup("clear"), (ZObjectSignalHandler) clear);
		z_map_insert((ZMap *) global->common.method_map, strdup("find"), (ZObjectSignalHandler) find);
		z_map_insert((ZMap *) global->common.method_map, strdup("get_key"), (ZObjectSignalHandler) get_key);
		z_map_insert((ZMap *) global->common.method_map, strdup("get_value"), (ZObjectSignalHandler) get_value);
		z_map_insert((ZMap *) global->common.method_map, strdup("set_value"), (ZObjectSignalHandler) set_value);
		z_map_insert((ZMap *) global->common.method_map, strdup("assign"), (ZObjectSignalHandler) assign);
		z_map_insert((ZMap *) global->common.method_map, strdup("insert"), (ZObjectSignalHandler) insert);
		z_map_insert((ZMap *) global->common.method_map, strdup("erase"), (ZObjectSignalHandler) erase);
		z_map_insert((ZMap *) global->common.method_map, strdup("erase1"), (ZObjectSignalHandler) erase1);
		z_map_insert((ZMap *) global->common.method_map, strdup("erase1_inc"), (ZObjectSignalHandler) erase1_inc);
		z_map_insert((ZMap *) global->common.method_map, strdup("lower_bound"), (ZObjectSignalHandler) lower_bound);
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
static void z_map_init(Self *self)
{
 selfp->data = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_set_item_size(selfp->data, 2 * sizeof(void *));

 selfp->compare = NULL;
 selfp->key_destruct = NULL;
 selfp->value_destruct = NULL;
 selfp->userdata = NULL;

 z_vector_set_userdata(selfp->data, self);
 z_vector_set_item_destruct(selfp->data, item_destroy);
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_map_reset(ZObject *object)
{
 Self *self = (Self *) object;

 z_vector_clear(selfp->data);

 selfp->compare = NULL;
 selfp->key_destruct = NULL;
 selfp->value_destruct = NULL;
 selfp->userdata = NULL;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_map_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 /* Make sure internal vector is clear. We don't want to rely
                   on the garbage collector to lazily destroy the items whose
                   destructor depends on this map to be available. Making the
                   items hold a reference to self will result in a circular
                   reference so it's not a feasible approach */
 z_vector_clear(selfp->data);
 z_object_unref(Z_OBJECT(selfp->data));

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_map_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 if (!allocator)
 allocator = ctx->flex_allocator;

 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
void z_map_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
void z_map_set_key_destruct(Self *self, ZMapItemCallback  value)
{
 selfp->key_destruct = value;
 }
void z_map_set_value_destruct(Self *self, ZMapItemCallback  value)
{
 selfp->value_destruct = value;
 }
ZMapIter * z_map_get_begin(Self *self)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);
 ZMapIter *it = z_map_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));

 z_map_iter_set_index(it, z_vector_iter_get_absolute_index(ptr));
 z_object_unref(Z_OBJECT(ptr));

 return it;
 }
ZMapIter * z_map_get_end(Self *self)
{
 ZVectorIter *ptr = z_vector_get_end(selfp->data);
 ZMapIter *it = z_map_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));

 z_map_iter_set_index(it, z_vector_iter_get_absolute_index(ptr));
 z_object_unref(Z_OBJECT(ptr));

 return it;
 }
int  z_map_get_is_empty(Self *self)
{
 return get_size(self) == 0;
 }
int  z_map_get_size(Self *self)
{
 return z_vector_get_size(selfp->data);
 }
void  z_map_clear(Self *self)
{
 z_vector_clear(selfp->data);
 }
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
ZMapIter * z_map_find(Self *self,const void *key)
{
 ZMapIter *it;
 int bound;

 if (get_is_empty(self)) {
 return NULL;

 } else {
 it = z_map_iter_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 find_item(self, key, &bound, it);

 if (bound == 0) {
 return it;
 } else {
 z_object_unref(Z_OBJECT(it));
 return NULL;
 }
 }
 }
static void * z_map_get_key_internal(void *item)
{
 return (void *)((unsigned long *)item)[0];
 }
static void * z_map_get_value_internal(void *item)
{
 return (void *)((unsigned long *)item)[1];
 }
static void  z_map_set_key_internal(void *item,void *key)
{
 ((unsigned long *)item)[0] = (unsigned long)key;
 }
static void  z_map_set_value_internal(void *item,void *value)
{
 ((unsigned long *)item)[1] = (unsigned long)value;
 }
void * z_map_get_key(Self *self,ZMapIter *it)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(ptr, z_map_iter_get_index(it));
 void *item = z_vector_get_item(selfp->data, ptr);
 z_object_unref(Z_OBJECT(ptr));

 return get_key_internal(item);
 }
void * z_map_get_value(Self *self,ZMapIter *it)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(ptr, z_map_iter_get_index(it));
 void *item = z_vector_get_item(selfp->data, ptr);
 z_object_unref(Z_OBJECT(ptr));

 return get_value_internal(item);
 }
void  z_map_set_value(Self *self,ZMapIter *it,void *value)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);

 z_vector_iter_advance(ptr, z_map_iter_get_index(it));
 void *item = z_vector_get_item(selfp->data, ptr);
 z_object_unref(Z_OBJECT(ptr));

 set_value_internal(item, value);
 }
static void  z_map_item_destroy(void *item,void *userdata)
{
 ZMap *self = (ZMap *) userdata;
 void *key, *value;

 key = get_key_internal(item);
 value = get_value_internal(item);

 if (selfp->key_destruct)
 selfp->key_destruct(key, selfp->userdata);

 if (selfp->value_destruct) 
 selfp->value_destruct(value, selfp->userdata);
 }
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
int  z_map_assign(Self *self,void *key,void *value)
{
 return add_item(self, key, value, 1);
 }
int  z_map_insert(Self *self,void *key,void *value)
{
 return add_item(self, key, value, 0);
 }
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
void  z_map_erase1(Self *self,ZMapIter *it)
{
 ZMapIter *end;

 end = z_map_iter_dup(it);
 z_map_iter_increment(end);
 erase(self, it, end);
 z_object_unref(Z_OBJECT(end));
 }
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
void z_map_set_compare(Self *self, ZMapCompareFunc  value)
{
 selfp->compare = value;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_map_class_destroy(ZObjectGlobal *gbl)
{
	ZMapGlobal *_global = (ZMapGlobal *) gbl;

}

#undef PARENT_HANDLER



