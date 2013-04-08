/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-default-object-tracker.c: Bootstrap file for z-default-object-tracker.zco
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

#line 16 "z-default-object-tracker.zco"

#include <z-value.h>
#include <assert.h>
#include <stdio.h>

#define INT_TO_PTR(x) ((void *) ((unsigned long) (x)))
#define PTR_TO_INT(x) ((int64_t) ((long) (x)))


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-default-object-tracker.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZDefaultObjectTracker
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_default_object_tracker_new(ctx,allocator)
#define INIT_EXISTS
#line 23 "z-default-object-tracker.zco"
#define init z_default_object_tracker_init
#line 31 "z-default-object-tracker.zco"
#define new z_default_object_tracker_new
#line 37 "z-default-object-tracker.zco"
#define map_compare z_default_object_tracker_map_compare
#line 172 "z-default-object-tracker.zco"
#define garbage_collect_pool z_default_object_tracker_garbage_collect_pool

int z_default_object_tracker_type_id = -1;

static Self *__z_default_object_tracker_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_default_object_tracker_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		self = (Self *) malloc(sizeof(Self));
		__z_default_object_tracker_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 23 "z-default-object-tracker.zco"
static void z_default_object_tracker_init(Self *self);
#line 37 "z-default-object-tracker.zco"
static int  z_default_object_tracker_map_compare(ZMap *map,const void *a,const void *b);
#line 43 "z-default-object-tracker.zco"
static void  z_default_object_tracker_dispose(ZObject *object);
#line 73 "z-default-object-tracker.zco"
static ZObject *  z_default_object_tracker_create(ZObjectTracker *tracker,int type_id);
#line 131 "z-default-object-tracker.zco"
static int  z_default_object_tracker_destroy(ZObjectTracker *tracker,ZObject *target);
#line 172 "z-default-object-tracker.zco"
static int  z_default_object_tracker_garbage_collect_pool(Self *self,ZVector *pool);
#line 224 "z-default-object-tracker.zco"
static int  z_default_object_tracker_garbage_collect(ZObjectTracker *tracker);
#line 256 "z-default-object-tracker.zco"
static void z_default_object_tracker_class_destroy(ZObjectGlobal *gbl);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZDefaultObjectTrackerGlobal * z_default_object_tracker_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_default_object_tracker_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_default_object_tracker_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZDefaultObjectTrackerGlobal *global = (ZDefaultObjectTrackerGlobal *) malloc(sizeof(struct ZDefaultObjectTrackerGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZDefaultObjectTrackerClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZDefaultObjectTrackerClass));
		global->common.name = "ZDefaultObjectTracker";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZDefaultObjectTracker temp;
		struct ZDefaultObjectTrackerClass temp_class;

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
		{
			struct ZObjectTrackerGlobal *p_global = z_object_tracker_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_global->common.vtable_off_list,
				p_global->common.vtable_off_size,
				&temp,
				&temp.parent_z_object_tracker);
			zco_inherit_vtable(
				&global->common.svtable_off_list,
				&global->common.svtable_off_size,
				p_global->common.svtable_off_list,
				p_global->common.svtable_off_size,
				&temp_class,
				&temp_class.parent_z_object_tracker);
			ZObjectTrackerClass *p1_class = CLASS_FROM_GLOBAL(p_global);
			ZObjectTrackerClass *p2_class = (ZObjectTrackerClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_tracker_type_id]);
			memcpy(p2_class, p1_class, sizeof(struct ZObjectTrackerClass));
		}
		if (z_default_object_tracker_type_id == -1)
			z_default_object_tracker_type_id = zco_allocate_type_id();
		global->common.id = z_default_object_tracker_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_default_object_tracker_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_default_object_tracker_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_default_object_tracker_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
#line 43 "z-default-object-tracker.zco"
		{
#line 43 "z-default-object-tracker.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
#line 43 "z-default-object-tracker.zco"
			global->__parent_dispose = p_class->__dispose;
#line 43 "z-default-object-tracker.zco"
			p_class->__dispose = z_default_object_tracker_dispose;
#line 43 "z-default-object-tracker.zco"
		}
#line 73 "z-default-object-tracker.zco"
		{
#line 73 "z-default-object-tracker.zco"
			ZObjectTrackerClass *p_class = (ZObjectTrackerClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_tracker_type_id]);
#line 73 "z-default-object-tracker.zco"
			global->__parent_create = p_class->__create;
#line 73 "z-default-object-tracker.zco"
			p_class->__create = z_default_object_tracker_create;
#line 73 "z-default-object-tracker.zco"
		}
#line 131 "z-default-object-tracker.zco"
		{
#line 131 "z-default-object-tracker.zco"
			ZObjectTrackerClass *p_class = (ZObjectTrackerClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_tracker_type_id]);
#line 131 "z-default-object-tracker.zco"
			global->__parent_destroy = p_class->__destroy;
#line 131 "z-default-object-tracker.zco"
			p_class->__destroy = z_default_object_tracker_destroy;
#line 131 "z-default-object-tracker.zco"
		}
#line 224 "z-default-object-tracker.zco"
		{
#line 224 "z-default-object-tracker.zco"
			ZObjectTrackerClass *p_class = (ZObjectTrackerClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_tracker_type_id]);
#line 224 "z-default-object-tracker.zco"
			global->__parent_garbage_collect = p_class->__garbage_collect;
#line 224 "z-default-object-tracker.zco"
			p_class->__garbage_collect = z_default_object_tracker_garbage_collect;
#line 224 "z-default-object-tracker.zco"
		}
#line 256 "z-default-object-tracker.zco"
		{
#line 256 "z-default-object-tracker.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
#line 256 "z-default-object-tracker.zco"
			global->__parent_class_destroy = p_class->__class_destroy;
#line 256 "z-default-object-tracker.zco"
			p_class->__class_destroy = z_default_object_tracker_class_destroy;
#line 256 "z-default-object-tracker.zco"
		}
		__z_default_object_tracker_class_init(ctx, (ZDefaultObjectTrackerClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
#line 31 "z-default-object-tracker.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZDefaultObjectTrackerGlobal *) global);
		#endif
		return global;
	}
	return (ZDefaultObjectTrackerGlobal *) *global_ptr;
}

void __z_default_object_tracker_class_init(struct zco_context_t *ctx, ZDefaultObjectTrackerClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	__z_object_tracker_class_init(ctx, (ZObjectTrackerClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_default_object_tracker_init(struct zco_context_t *ctx, Self *self)
{
	struct ZDefaultObjectTrackerGlobal *_global = z_default_object_tracker_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, ((ZObject *) ((char *) self + GLOBAL_FROM_OBJECT(self)->common.vtable_off_list[z_object_type_id])));
	__z_object_tracker_init(ctx, ((ZObjectTracker *) ((char *) self + GLOBAL_FROM_OBJECT(self)->common.vtable_off_list[z_object_tracker_type_id])));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 23 "z-default-object-tracker.zco"
static void z_default_object_tracker_init(Self *self)
{
 selfp->pools = z_map_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_map_set_compare(selfp->pools, map_compare);
 z_map_set_value_destruct(selfp->pools, (ZMapItemCallback) z_object_unref);
 selfp->suspended = 0;
 }
#line 31 "z-default-object-tracker.zco"
Self * z_default_object_tracker_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
#line 37 "z-default-object-tracker.zco"
static int  z_default_object_tracker_map_compare(ZMap *map,const void *a,const void *b)
{
 return PTR_TO_INT(a) - PTR_TO_INT(b);
 }
#line 43 "z-default-object-tracker.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_default_object_tracker_dispose(ZObject *object)
{
 Self *self = (Self *) object;
 ZMapIter *begin, *it, *end;

 /* suspend garbage collector */
 selfp->suspended = 1;

 /* set a item destructor for each pool */
 begin = z_map_get_begin(selfp->pools);
 it = z_map_iter_dup(begin);
 end = z_map_get_end(selfp->pools);

 while (!z_map_iter_is_equal(it, end)) {
 ZVector *pool = (ZVector *) z_map_get_value(selfp->pools, it);
 z_vector_set_item_destruct(pool, (ZVectorItemCallback) z_object_dispose);
 z_map_iter_increment(it);
 }

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(end));

 /* unref the pools map */
 z_object_unref(Z_OBJECT(selfp->pools));

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 73 "z-default-object-tracker.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_create
static ZObject *  z_default_object_tracker_create(ZObjectTracker *tracker,int type_id)
{
 Self *self = (ZDefaultObjectTracker *) tracker;
 ZMapIter *pos;
 ZVector *pool;
 ZObject *object;

 if (selfp->suspended)
 return NULL;

 selfp->suspended = 1;

 /* look for an object pool of the target type id */
 pos = z_map_find(selfp->pools, INT_TO_PTR(type_id));
 if (!pos) {
 /* nothing to reclaim */
 object = NULL;
 goto done;
 }

 pool = z_map_get_value(selfp->pools, pos);
 z_object_unref(Z_OBJECT(pos));

 /* nothing to do if pool is empty */
 if (z_vector_get_is_empty(pool)) {
 /* nothing to reclaim */
 object = NULL;
 goto done;
 }
 
 /* pop last item from the pool */
 if (z_vector_pop_back(pool, &object) != 0) {
 /* pool is in insert-only mode */
 object = NULL;
 goto done;
 }

 /* reset the object state */
 if (type_id == 1) { // map
 //z_object_dispose(object);
 //object = NULL;
 z_object_reset(object);

 } else if (type_id == 9) { // string
 //z_object_dispose(object);
 //object = NULL;
 z_object_reset(object);

 } else {
 z_object_reset(object);
 }

done:
 selfp->suspended = 0;
 return object;
 }
#undef PARENT_HANDLER
#line 131 "z-default-object-tracker.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_destroy
static int  z_default_object_tracker_destroy(ZObjectTracker *tracker,ZObject *target)
{
 Self *self = (Self *) tracker;

 if (selfp->suspended) {
 z_object_dispose(target);
 } else {
 selfp->suspended = 1;

 /* We can't use GLOBAL_FROM_OBJECT() here because we are interested in the Global struct of
                           the derived class, not ZObject. CLASS_FROM_OBJECT() returns the Class struct for the
                           derived class and GLOBAL_FROM_CLASS() returns the Global struct of the derived class.
                           GLOBAL_FROM_OBJECT() treats the input as a ZObject so it always returns the Global struct
                           of the ZObject part */
 int id = GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT(target))->id;

 ZMapIter *pos;
 ZVector *pool;

 pos = z_map_find(selfp->pools, INT_TO_PTR(id));

 if (pos) {
 pool = z_map_get_value(selfp->pools, pos);
 z_object_unref(Z_OBJECT(pos));

 } else {
 /* create the pool for the type */
 pool = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_set_item_size(pool, 0);

 /* insert the pool into the list of pools */
 z_map_assign(selfp->pools, INT_TO_PTR(id), pool);
 } 

 /* insert the object into the pool */
 z_vector_push_back(pool, target);

 selfp->suspended = 0;
 }
 }
#undef PARENT_HANDLER
#line 172 "z-default-object-tracker.zco"
static int  z_default_object_tracker_garbage_collect_pool(Self *self,ZVector *pool)
{
 ZVectorIter *begin, *it, *end;

 if (z_vector_get_is_empty(pool))
 return 0;

 /* Temporarily enable insert-only mode on the pool. This will
                   ensure that the size of the vector will not decrease and so
                   the iterators will remain valid */
 z_vector_set_is_insert_only_mode(pool, 1);

 begin = z_vector_get_begin(pool);
 it = z_vector_iter_dup(begin);
 end = z_vector_get_end(pool);

 /* Iterate through the vector in the range of [begin,end). Note that
                   during this loop iteration, more items may be pushed into the vector.
                   we will only GC the items that were present at the start of the loop.
                   Subsequent calls to garbage_collect() will pick up the remaining
                   garbage objects */
 while (!z_vector_iter_is_equal(it, end)) {
 ZObject *obj = (ZObject *) z_vector_get_item(pool, it);
 z_object_dispose(obj);
 z_vector_iter_increment(it);
 }

 /* Disable insert-only mode since we are now ready to erase part or all
                   of the pool */
 z_vector_set_is_insert_only_mode(pool, 0);

 /* Temporarily suspend the garbage collector. We are suspending it since
                   z_vector_erase internally creates and destroys objects.  

                   If we don't suspend it, this call will push more items into the vector,
                   thus making it impossible for the vector size to ever be 0. It can also
                   decrease the size of the vector making the iterators invalid. */

 selfp->suspended = 1;

 z_vector_erase(pool, begin, end);

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(end));

 selfp->suspended = 0;

 return z_vector_get_size(pool);
 }
#line 224 "z-default-object-tracker.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_garbage_collect
static int  z_default_object_tracker_garbage_collect(ZObjectTracker *tracker)
{
 Self *self = (Self *) tracker;
 ZMapIter *begin, *it, *end;
 int count = 0;

 begin = z_map_get_begin(selfp->pools);
 it = z_map_iter_dup(begin);
 end = z_map_get_end(selfp->pools);

 /* Iterate through the vector in the range of [begin,end). Note that
                   during this loop iteration, more items may be pushed into the vector.
                   we will only GC the items that were present at the start of the loop.
                   Subsequent calls to garbage_collect() will pick up the remaining
                   garbage objects */
 while (!z_map_iter_is_equal(it, end)) {
 ZVector *pool = (ZVector *) z_map_get_value(selfp->pools, it);
 count += garbage_collect_pool(self, pool);
 z_map_iter_increment(it);
 }

 /* Temporarily suspend the garbage collector. */
 selfp->suspended = 1;

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(end));

 selfp->suspended = 0;

 return count;
 }
#undef PARENT_HANDLER
#line 256 "z-default-object-tracker.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_default_object_tracker_class_destroy(ZObjectGlobal *gbl)
{
	ZDefaultObjectTrackerGlobal *_global = (ZDefaultObjectTrackerGlobal *) gbl;

}

#undef PARENT_HANDLER

#line 256 "z-default-object-tracker.zco"


