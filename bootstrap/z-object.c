/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-object.c: Bootstrap file for z-object.zco
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

#line 21 "z-object.zco"

#include <assert.h>
#include <z-map.h>
#include <z-vector.h>
#include <z-vector-iter.h>
#include <z-closure.h>
#include <z-closure-marshal.h>
#include <z-object-tracker.h>
#include <z-string.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-object.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZObject
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_object_new(ctx,allocator)
#define INIT_EXISTS
#define init z_object_init
#define class_destroy z_object_class_destroy
#define cleanup_attached_properties z_object_cleanup_attached_properties
#define reset z_object_reset
#define dispose z_object_dispose
#define ref z_object_ref
#define unref z_object_unref
#define lookup_method z_object_lookup_method
#define connect z_object_connect
#define disconnect z_object_disconnect
#define register_signal z_object_register_signal
#define emit_signal z_object_emit_signal
#define add_attached_property_map z_object_add_attached_property_map
#define map_compare z_object_map_compare
#define get_allocator_ptr z_object_get_allocator_ptr
#define set_allocator_ptr z_object_set_allocator_ptr

int z_object_type_id = -1;

static Self *__z_object_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_object_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		ZMemoryAllocator *obj_allocator = ctx->slab_allocator;
		if (obj_allocator)
			self = (Self *) z_memory_allocator_allocate(obj_allocator, sizeof(Self));
		else
			self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_object_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_object_init(Self *self);
static void  z_object_virtual_class_destroy(ZObjectGlobal *gbl);
static void  z_object_cleanup_attached_properties(Self *self);
static void  z_object_virtual_reset(Self *self);
static void  z_object_virtual_dispose(Self *self);
static ZObjectSignalHandler  z_object_lookup_method(Self *self,char *method_name);
static int  z_object_map_compare(ZMap *map,const void *a,const void *b);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_object_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_object_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZObjectGlobal *global = (ZObjectGlobal *) malloc(sizeof(struct ZObjectGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZObjectClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZObjectClass));
		global->common.name = "ZObject";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZObject temp;
		struct ZObjectClass temp_class;

		if (z_object_type_id == -1)
			z_object_type_id = zco_allocate_type_id();
		global->common.id = z_object_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_object_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_object_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_object_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		CLASS_FROM_GLOBAL(global)->__class_destroy = z_object_virtual_class_destroy;
		CLASS_FROM_GLOBAL(global)->__reset = z_object_virtual_reset;
		CLASS_FROM_GLOBAL(global)->__dispose = z_object_virtual_dispose;
		__z_object_class_init(ctx, (ZObjectClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("reset"), (ZObjectSignalHandler) reset);
		z_map_insert((ZMap *) global->common.method_map, strdup("dispose"), (ZObjectSignalHandler) dispose);
		z_map_insert((ZMap *) global->common.method_map, strdup("ref"), (ZObjectSignalHandler) ref);
		z_map_insert((ZMap *) global->common.method_map, strdup("unref"), (ZObjectSignalHandler) unref);
		z_map_insert((ZMap *) global->common.method_map, strdup("connect"), (ZObjectSignalHandler) connect);
		z_map_insert((ZMap *) global->common.method_map, strdup("disconnect"), (ZObjectSignalHandler) disconnect);
		z_map_insert((ZMap *) global->common.method_map, strdup("register_signal"), (ZObjectSignalHandler) register_signal);
		z_map_insert((ZMap *) global->common.method_map, strdup("emit_signal"), (ZObjectSignalHandler) emit_signal);
		z_map_insert((ZMap *) global->common.method_map, strdup("add_attached_property_map"), (ZObjectSignalHandler) add_attached_property_map);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZObjectGlobal *) global);
		#endif
		return global;
	}
	return (ZObjectGlobal *) *global_ptr;
}

void __z_object_class_init(struct zco_context_t *ctx, ZObjectClass *_class)
{
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_object_init(struct zco_context_t *ctx, Self *self)
{
	struct ZObjectGlobal *_global = z_object_get_type(ctx);
	self->_global = _global;
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_object_init(Self *self)
{
 selfp->ref_count = 1;
 selfp->attached_properties = 0;
 selfp->signal_map = 0;
 }
void  z_object_class_destroy(ZObjectGlobal *gbl)
{
	ZObjectClass *class_base = CLASS_FROM_GLOBAL(gbl);
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) class_base + offset))->__class_destroy(gbl);
}
static void  z_object_virtual_class_destroy(ZObjectGlobal *gbl)
{
 }
static void  z_object_cleanup_attached_properties(Self *self)
{
 ZVector *attached_properties = selfp->attached_properties;

 if (attached_properties) {
 ZVectorIter *it, *end;

 /* iterate through all attached properties */
 it = z_vector_get_begin(attached_properties);
 end = z_vector_get_end(attached_properties);

 for (; !z_vector_iter_is_equal(it, end); z_vector_iter_increment(it)) {
 /* the vector contains a list of maps that has a pointer to 'self'.
				   our goal is to remove 'self' from the map */
 ZMap *map = (ZMap *) z_vector_get_item(attached_properties, it);

 /* remove the pointer */
 ZMapIter *x = z_map_find(map, self);
 z_map_erase1(map, x);
 unref(Z_OBJECT(x));
 }

 unref(Z_OBJECT(end));
 unref(Z_OBJECT(it));
 unref(Z_OBJECT(attached_properties));

 selfp->attached_properties = NULL;
 }

 }
void  z_object_reset(Self *self)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) class_base + offset))->__reset(self);
}
static void  z_object_virtual_reset(Self *self)
{
 /* This ensures that reset() is not called by someone other
                   than the object tracker */
 assert(selfp->ref_count == 0);
 selfp->ref_count = 1;

 cleanup_attached_properties(self);

 /* No need to worry about signal_map. Since we ref(self) when
                   a signal is connected and unref(self) when it is
                   disconnected, all closure lists must be empty before self
                   can have a reference count of 0 */
 }
void  z_object_dispose(Self *self)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) class_base + offset))->__dispose(self);
}
static void  z_object_virtual_dispose(Self *self)
{
 cleanup_attached_properties(self);

 ZMap *signal_map = selfp->signal_map;
 if (signal_map) {
 unref(Z_OBJECT(signal_map));
 selfp->signal_map = NULL;
 }

 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->slab_allocator;
 if (allocator)
 z_memory_allocator_deallocate(allocator, self);
 else
 free(self);
 }
void  z_object_ref(Self *self)
{
 ++selfp->ref_count;
 }
void  z_object_unref(Self *self)
{
 assert(selfp->ref_count > 0);
 if (--selfp->ref_count == 0) {
 if (selfp->allocator) {
 ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(selfp->allocator);
 if (object_tracker) {
 z_object_tracker_destroy(object_tracker, self);
 unref(Z_OBJECT(object_tracker));
 return;
 } 
 } 

 dispose(self);
 }
 }
static ZObjectSignalHandler  z_object_lookup_method(Self *self,char *method_name)
{
 /* This reinterpret cast is only valid for the fields that
		   are common between the source (unknown) *Global type and
		   ZObjectGlobal. Since we are interested in the vtable information,
		   we can perform the cast */
 ZCommonGlobal *gbl = ((ZObjectClass *) self->class_base)->real_global;


 int *vtable_off_list = gbl->vtable_off_list;
 int vtable_off_size = gbl->vtable_off_size;
 int i;

 for (i=vtable_off_size-1; i>=0; --i) {
 int offset = vtable_off_list[i];

 /* -1 indicates that this object is not derived from
			   a parent class with the type id 'i' */
 if (offset == -1)
 continue;

 gbl = *((ZCommonGlobal **) zco_get_ctx_type(CTX_FROM_OBJECT(self), i));
 ZMap *method_map = (ZMap *) gbl->method_map;
 ZMapIter *it = z_map_find(method_map, method_name);

 if (it) {
 ZObjectSignalHandler handler = z_map_get_value(method_map, it);
 unref(Z_OBJECT(it));
 return handler;
 }
 }

 return NULL;
 }
void *  z_object_connect(Self *self,char *name,ZObject *target,char *method_name,void *userdata)
{
 ZClosure *closure;
 ZObjectSignalHandler handler;

 assert(selfp->signal_map != NULL);

 /* Increase the reference count of self so it stays alive for
                   the disconnect() call. */
 ref(self);

 /* lookup handler from method_name */
 handler = lookup_method(target, method_name);
 assert(handler != NULL);

 /* create a closure */
 closure = z_closure_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));

 z_closure_set_marshal(closure, (ZClosureMarshal *) CTX_FROM_OBJECT(self)->marshal);
 z_closure_set_target(closure, target);
 z_closure_set_handler(closure, handler);
 z_closure_set_userdata(closure, userdata);

 /* locate signal's closure list by name */
 ZMapIter *it = z_map_find(selfp->signal_map, name);
 assert(it != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, it);
 unref(Z_OBJECT(it));

 /* add new closure into the signal */
 z_vector_push_back(closure_list, closure);

 return closure;
 }
void  z_object_disconnect(Self *self,char *name,void *key)
{
 assert(selfp->signal_map != NULL);

 /* locate signal's closure list by name */
 ZMapIter *map_iter = z_map_find(selfp->signal_map, name);
 assert(map_iter != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, map_iter);
 unref(Z_OBJECT(map_iter));

 /* remove the closure from the list */
 ZVectorIter *it = z_vector_get_begin(closure_list);
 ZVectorIter *end = z_vector_get_end(closure_list);

 while (!z_vector_iter_is_equal(it, end)) {
 void *current_key = z_vector_get_item(closure_list, it);

 if (current_key == key) {
 z_vector_erase1(closure_list, it);
 break;
 } else {
 z_vector_iter_increment(it);
 }
 }

 unref(Z_OBJECT(end));
 unref(Z_OBJECT(it));

 unref(self);
 }
void  z_object_register_signal(Self *self,char *name)
{
 /* create signal map (if necessary) */
 if (!selfp->signal_map) {
 selfp->signal_map = z_map_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_map_set_compare(selfp->signal_map, map_compare);
 z_map_set_key_destruct(selfp->signal_map, (ZMapItemCallback) free);
 z_map_set_value_destruct(selfp->signal_map, (ZMapItemCallback) unref);
 }

 /* locate signal's closure list by name */
 ZMapIter *it = z_map_find(selfp->signal_map, name);

 if (!it) {
 ZVector *closure_list = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_set_item_size(closure_list, 0);
 z_vector_set_item_destruct(closure_list, (ZVectorItemCallback) unref);
 z_map_insert(selfp->signal_map, strdup(name), closure_list);
 }
 }
int  z_object_emit_signal(Self *self,char *name,void *argv)
{
 assert(selfp->signal_map != NULL);

 /* locate signal's closure list by name */
 ZMapIter *map_iter = z_map_find(selfp->signal_map, name);
 assert(map_iter != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, map_iter);
 unref(Z_OBJECT(map_iter));

 /* remove the closure from the list */
 ZVectorIter *it = z_vector_get_begin(closure_list);
 ZVectorIter *end = z_vector_get_end(closure_list);
 int rc = 0;

 while (!z_vector_iter_is_equal(it, end)) {
 ZClosure *closure = ((ZClosure *) z_vector_get_item(closure_list, it));
 rc = z_closure_invoke(closure, (ZVector *) argv);

 if (rc == 1)
 break;

 z_vector_iter_increment(it);
 }

 unref(Z_OBJECT(end));
 unref(Z_OBJECT(it));
 return rc;
 }
void  z_object_add_attached_property_map(Self *self,void *map)
{
 if (selfp->attached_properties == 0) {
 selfp->attached_properties = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_set_item_size(selfp->attached_properties, sizeof(void *));
 }

 /* keep note of the maps that has a pointer to 'self' */
 z_vector_push_back((ZVector *) selfp->attached_properties, map);
 }
static int  z_object_map_compare(ZMap *map,const void *a,const void *b)
{
 return strcmp(a, b);
 }
ZMemoryAllocator *  z_object_get_allocator_ptr(Self *self)
{
 return selfp->allocator;
 }
void z_object_set_allocator_ptr(Self *self, ZMemoryAllocator *  value)
{
 selfp->allocator = value;
 }



