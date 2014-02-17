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
#include <z-object-tracker.h>
#include <z-string.h>

#if !defined(BOOTSTRAP)
#include <z-closure.h>
#include <z-closure-marshal.h>
#endif

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-object-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZObject
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_object_new(ctx,allocator)
#define INIT_EXISTS
#define init z_object_init
#define class_destroy z_object_class_destroy
#define cleanup_attached_properties z_object_cleanup_attached_properties
#define reset z_object_reset
#define __delete z_object___delete
#define dispose z_object_dispose
#define ref z_object_ref
#define unref z_object_unref
#define set_method_hook z_object_set_method_hook
#define lookup_method z_object_lookup_method
#define connect z_object_connect
#define disconnect z_object_disconnect
#define register_signal z_object_register_signal
#define emit_signal z_object_emit_signal
#define add_attached_property_map z_object_add_attached_property_map
#define map_compare z_object_map_compare
#define get_allocator_ptr z_object_get_allocator_ptr
#define set_allocator_ptr z_object_set_allocator_ptr
#define get_closure_marshal z_object_get_closure_marshal
#define set_closure_marshal z_object_set_closure_marshal

ZCO_DEFINE_CLASS_TYPE(z_object);

static void z_object_init(Self *self);
static void  z_object_virtual_class_destroy(ZObjectGlobal *gbl);
static void  z_object_cleanup_attached_properties(Self *self);
static void  z_object_virtual_reset(Self *self);
static void  z_object_virtual___delete(Self *self);
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
	ZCO_CREATE_CLASS(global, ZObject, z_object, 1);
	ZCO_REGISTER_TYPE(z_object);
	ZCO_CREATE_VIRTUAL_METHOD(z_object, class_destroy);
	ZCO_CREATE_VIRTUAL_METHOD(z_object, reset);
	ZCO_CREATE_VIRTUAL_METHOD(z_object, __delete);
	ZCO_CREATE_VIRTUAL_METHOD(z_object, dispose);
	ZCO_CREATE_METHOD_MAP(ZObject, z_object);
	ZCO_REGISTER_METHOD(reset);
	ZCO_REGISTER_METHOD(__delete);
	ZCO_REGISTER_METHOD(dispose);
	ZCO_REGISTER_METHOD(ref);
	ZCO_REGISTER_METHOD(unref);
	ZCO_REGISTER_METHOD(set_method_hook);
	ZCO_REGISTER_METHOD(connect);
	ZCO_REGISTER_METHOD(disconnect);
	ZCO_REGISTER_METHOD(register_signal);
	ZCO_REGISTER_METHOD(emit_signal);
	ZCO_REGISTER_METHOD(add_attached_property_map);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
}

void __z_object_class_init(struct zco_context_t *ctx, ZObjectClass *_class)
{
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_object_init(struct zco_context_t *ctx, Self *self)
{
	ZCO_INIT_START(ZObject, z_object);
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_object_init(Self *self)
{
 selfp->ref_count = 1;
 selfp->attached_properties = NULL;
 selfp->signal_map = NULL;
 selfp->closure_marshal = NULL;
 selfp->_method_hook = NULL;
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
{
 ZVector *attached_properties = (ZVector *) selfp->attached_properties;

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
}
void  z_object_reset(Self *self)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) class_base + offset))->__reset(self);
}
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
void  z_object___delete(Self *self)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) class_base + offset))->____delete(self);
}
}
static void  z_object_virtual___delete(Self *self)
{
 /* This method must be overridden by derived classes. The
                   derived classes must NOT call PARENT_HANDLER */
 abort();
 }
void  z_object_dispose(Self *self)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) class_base + offset))->__dispose(self);
}
}
static void  z_object_virtual_dispose(Self *self)
{
 set_closure_marshal(self, NULL);
 cleanup_attached_properties(self);

 ZMap *signal_map = (ZMap *) selfp->signal_map;
 if (signal_map) {
 unref(Z_OBJECT(signal_map));
 selfp->signal_map = NULL;
 }

 __delete(self);
 }
void  z_object_ref(Self *self)
{
{
 ++selfp->ref_count;
 }
}
void  z_object_unref(Self *self)
{
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
}
void  z_object_set_method_hook(Self *self,ZObjectMethodHookHandler handler)
{
{
 selfp->_method_hook = handler;
 }
}
static ZObjectSignalHandler  z_object_lookup_method(Self *self,char *method_name)
{
{
 /* This reinterpret cast is only valid for the fields that
		   are common between the source (unknown) *Global type and
		   ZObjectGlobal. Since we are interested in the vtable information,
		   we can perform the cast */
 ZCommonGlobal *gbl = ((ZObjectClass *) self->class_base)->real_global;
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);

 int *vtable_off_list = gbl->vtable_off_list;
 int vtable_off_size = gbl->vtable_off_size;
 int i;

 for (i=vtable_off_size-1; i>=0; --i) {
 int offset = vtable_off_list[i];

 /* -1 indicates that this object is not derived from
			   a parent class with the type id 'i' */
 if (offset == -1)
 continue;

 gbl = *((ZCommonGlobal **) zco_get_ctx_type(ctx, i));
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
}
void *  z_object_connect(Self *self,char *name,ZObject *target,char *method_name,void *userdata)
{
{
#if !defined(BOOTSTRAP)
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

 z_closure_set_target(closure, target);
 z_closure_set_handler(closure, handler);
 z_closure_set_userdata(closure, userdata);

 /* locate signal's closure list by name */
 ZMap *signal_map = (ZMap *) selfp->signal_map;
 ZMapIter *it = z_map_find(signal_map, name);
 assert(it != NULL);
 ZVector *closure_list = z_map_get_value(signal_map, it);
 unref(Z_OBJECT(it));

 /* add new closure into the signal */
 z_vector_push_back(closure_list, closure);

 return closure;
#else
 return NULL;
#endif
 }
}
void  z_object_disconnect(Self *self,char *name,void *key)
{
{
 assert(selfp->signal_map != NULL);

 /* locate signal's closure list by name */
 ZMap *signal_map = (ZMap *) selfp->signal_map;
 ZMapIter *map_iter = z_map_find(signal_map, name);
 assert(map_iter != NULL);
 ZVector *closure_list = z_map_get_value(signal_map, map_iter);
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
}
void  z_object_register_signal(Self *self,char *name)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 /* create signal map (if necessary) */
 if (!selfp->signal_map) {
 ZMap *signal_map = z_map_new(ctx, allocator);
 z_map_set_compare(signal_map, map_compare);
 z_map_set_key_destruct(signal_map, (ZMapItemCallback) free);
 z_map_set_value_destruct(signal_map, (ZMapItemCallback) unref);

 selfp->signal_map = (ZObject *) signal_map;
 }

 /* locate signal's closure list by name */
 ZMap *signal_map = (ZMap *) selfp->signal_map;
 ZMapIter *it = z_map_find(signal_map, name);

 if (!it) {
 ZVector *closure_list = z_vector_new(ctx, allocator);
 z_vector_set_item_size(closure_list, 0);
 z_vector_set_item_destruct(closure_list, (ZVectorItemCallback) unref);
 z_map_insert(signal_map, strdup(name), closure_list);
 } else {
 z_object_unref(Z_OBJECT(it));
 }
 }
}
int  z_object_emit_signal(Self *self,char *name,void *argv)
{
{
#if !defined(BOOTSTRAP)
 assert(selfp->signal_map != NULL);

 /* locate signal's closure list by name */
 ZMap *signal_map = (ZMap *) selfp->signal_map;
 ZMapIter *map_iter = z_map_find(signal_map, name);
 assert(map_iter != NULL);
 ZVector *closure_list = z_map_get_value(signal_map, map_iter);
 unref(Z_OBJECT(map_iter));

 /* remove the closure from the list */
 ZVectorIter *it = z_vector_get_begin(closure_list);
 ZVectorIter *end = z_vector_get_end(closure_list);
 int rc = 0;

 while (!z_vector_iter_is_equal(it, end)) {
 ZClosure *closure = ((ZClosure *) z_vector_get_item(closure_list, it));
 rc = z_closure_invoke(closure, (ZVector *) argv, NULL);

 if (rc == 1)
 break;

 z_vector_iter_increment(it);
 }

 unref(Z_OBJECT(end));
 unref(Z_OBJECT(it));
 return rc;
#else
 return -1;
#endif
 }
}
void  z_object_add_attached_property_map(Self *self,void *map)
{
{
 if (selfp->attached_properties == 0) {
 ZVector *attached_properties = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 z_vector_set_item_size(attached_properties, sizeof(void *));

 selfp->attached_properties = (ZObject *) attached_properties;
 }

 /* keep note of the maps that has a pointer to 'self' */
 z_vector_push_back((ZVector *) selfp->attached_properties, map);
 }
}
static int  z_object_map_compare(ZMap *map,const void *a,const void *b)
{
{
 return strcmp(a, b);
 }
}
ZMemoryAllocator *  z_object_get_allocator_ptr(Self *self)
{
{
 return selfp->allocator;
 }
}
void z_object_set_allocator_ptr(Self *self, ZMemoryAllocator *  value)
{
{
 selfp->allocator = value;
 }
}
ZObject *  z_object_get_closure_marshal(Self *self)
{
{
 if (selfp->closure_marshal)
 z_object_ref(selfp->closure_marshal);

 return selfp->closure_marshal;
 }
}
void z_object_set_closure_marshal(Self *self, ZObject *  value)
{
{
 if (selfp->closure_marshal)
 z_object_unref(selfp->closure_marshal);

 selfp->closure_marshal = value;

 if (selfp->closure_marshal)
 z_object_ref(selfp->closure_marshal);
 }
}



