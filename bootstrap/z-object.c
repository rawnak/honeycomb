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

#line 18 "z-object.zco"

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
#include <z-object.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZObject
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_object_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 29 "z-object.zco"
#define init z_object_init
#line 36 "z-object.zco"
#define reset z_object_reset
#line 43 "z-object.zco"
#define dispose z_object_dispose
#line 80 "z-object.zco"
#define ref z_object_ref
#line 85 "z-object.zco"
#define unref z_object_unref
#line 98 "z-object.zco"
#define lookup_method z_object_lookup_method
#line 133 "z-object.zco"
#define connect z_object_connect
#line 164 "z-object.zco"
#define disconnect z_object_disconnect
#line 193 "z-object.zco"
#define register_signal z_object_register_signal
#line 216 "z-object.zco"
#define emit_signal z_object_emit_signal
#line 246 "z-object.zco"
#define add_attached_property_map z_object_add_attached_property_map
#line 257 "z-object.zco"
#define map_compare z_object_map_compare

int z_object_type_id = -1;

static Self *__z_object_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_object_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_object_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 29 "z-object.zco"
static void z_object_init(Self *self);
#line 36 "z-object.zco"
static void  z_object_virtual_reset(Self *self);
#line 43 "z-object.zco"
static void  z_object_virtual_dispose(Self *self);
#line 98 "z-object.zco"
static ZObjectSignalHandler  z_object_lookup_method(Self *self,char *method_name);
#line 257 "z-object.zco"
static int  z_object_map_compare(ZMap *map,const void *a,const void *b);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_object_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_object_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZObjectGlobal *global = (ZObjectGlobal *) malloc(sizeof(struct ZObjectGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZObjectClass));
		memset(global->_class, 0, sizeof(struct ZObjectClass));
		global->name = "ZObject";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZObject temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		class_off_list = malloc(sizeof(unsigned long) * (class_off_size+1));
		((ZObjectClass *) global->_class)->class_off_list = class_off_list;
		if (z_object_type_id == -1)
			z_object_type_id = zco_allocate_type_id();
		global->id = z_object_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_object_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_object_type_id);
		*global_ptr = global;
		
#line 36 "z-object.zco"
		global->_class->__reset = z_object_virtual_reset;
#line 43 "z-object.zco"
		global->_class->__dispose = z_object_virtual_dispose;
		__z_object_class_init(ctx, (ZObjectClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 36 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("reset"), (ZObjectSignalHandler) reset);
#line 43 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("dispose"), (ZObjectSignalHandler) dispose);
#line 80 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("ref"), (ZObjectSignalHandler) ref);
#line 85 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("unref"), (ZObjectSignalHandler) unref);
#line 133 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("connect"), (ZObjectSignalHandler) connect);
#line 164 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("disconnect"), (ZObjectSignalHandler) disconnect);
#line 193 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("register_signal"), (ZObjectSignalHandler) register_signal);
#line 216 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("emit_signal"), (ZObjectSignalHandler) emit_signal);
#line 246 "z-object.zco"
		z_map_insert((ZMap *) global->method_map, strdup("add_attached_property_map"), (ZObjectSignalHandler) add_attached_property_map);
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
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 29 "z-object.zco"
static void z_object_init(Self *self)
{
 selfp->ref_count = 1;
 selfp->attached_properties = 0;
 selfp->signal_map = 0;
 }
#line 36 "z-object.zco"
void  z_object_reset(Self *self)
{
	ZObject *obj = (ZObject *) self;
	unsigned long offset = ((ZObjectClass *) obj->class_base)->class_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) obj->class_base + offset))->__reset(self);
}
#line 36 "z-object.zco"
static void  z_object_virtual_reset(Self *self)
{
 selfp->ref_count = 1;
 selfp->attached_properties = 0;
 selfp->signal_map = 0;
 }
#line 43 "z-object.zco"
void  z_object_dispose(Self *self)
{
	ZObject *obj = (ZObject *) self;
	unsigned long offset = ((ZObjectClass *) obj->class_base)->class_off_list[z_object_type_id];
	((ZObjectClass *) ((char *) obj->class_base + offset))->__dispose(self);
}
#line 43 "z-object.zco"
static void  z_object_virtual_dispose(Self *self)
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
 z_object_unref(Z_OBJECT(x));
 }

 z_object_unref(Z_OBJECT(end));
 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(attached_properties));

 selfp->attached_properties = NULL;
 }

 ZMap *signal_map = selfp->signal_map;
 if (signal_map) {
 z_object_unref(Z_OBJECT(signal_map));
 selfp->signal_map = NULL;
 }

 free(self);
 }
#line 80 "z-object.zco"
void  z_object_ref(Self *self)
{
 ++selfp->ref_count;
 }
#line 85 "z-object.zco"
void  z_object_unref(Self *self)
{
 assert(selfp->ref_count > 0);
 if (--selfp->ref_count == 0) {
 if (CTX->object_tracker) {
 ZObjectTracker *object_tracker = (ZObjectTracker *) CTX->object_tracker;
 z_object_tracker_destroy(object_tracker, self);
 } else {
 dispose(self);
 }
 }
 }
#line 98 "z-object.zco"
static ZObjectSignalHandler  z_object_lookup_method(Self *self,char *method_name)
{
 /* This reinterpret cast is only valid for the fields that
		   are common between the source (unknown) *Global type and
		   ZObjectGlobal. Since we are interested in the vtable information,
		   we can perform the cast */
 ZObjectGlobal *gbl = ((ZObjectClass *) self->class_base)->real_global;


 int *vtable_off_list = gbl->vtable_off_list;
 int vtable_off_size = gbl->vtable_off_size;
 int i;

 for (i=vtable_off_size-1; i>=0; --i) {
 int offset = vtable_off_list[i];

 /* -1 indicates that this object is not derived from
			   a parent class with the type id 'i' */
 if (offset == -1)
 continue;

 gbl = *((void **) zco_get_ctx_type(CTX, i));
 ZMap *method_map = (ZMap *) gbl->method_map;
 ZMapIter *it = z_map_find(method_map, method_name);

 if (it) {
 ZObjectSignalHandler handler = z_map_get_value(method_map, it);
 z_object_unref(Z_OBJECT(it));
 return handler;
 }
 }

 return NULL;
 }
#line 133 "z-object.zco"
void *  z_object_connect(Self *self,char *name,ZObject *target,char *method_name,void *userdata)
{
 ZClosure *closure;
 ZObjectSignalHandler handler;

 assert(selfp->signal_map != NULL);

 /* lookup handler from method_name */
 handler = lookup_method(target, method_name);
 assert(handler != NULL);

 /* create a closure */
 closure = z_closure_new(CTX);

 z_closure_set_marshal(closure, (ZClosureMarshal *) CTX->marshal);
 z_closure_set_target(closure, target);
 z_closure_set_handler(closure, handler);
 z_closure_set_userdata(closure, userdata);

 /* locate signal's closure list by name */
 ZMapIter *it = z_map_find(selfp->signal_map, name);
 assert(it != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, it);
 z_object_unref(Z_OBJECT(it));

 /* add new closure into the signal */
 z_vector_push_back(closure_list, closure);

 return closure;
 }
#line 164 "z-object.zco"
void  z_object_disconnect(Self *self,char *name,void *key)
{
 assert(selfp->signal_map != NULL);

 /* locate signal's closure list by name */
 ZMapIter *map_iter = z_map_find(selfp->signal_map, name);
 assert(map_iter != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, map_iter);
 z_object_unref(Z_OBJECT(map_iter));

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

 z_object_unref(Z_OBJECT(end));
 z_object_unref(Z_OBJECT(it));
 }
#line 193 "z-object.zco"
void  z_object_register_signal(Self *self,char *name)
{
 /* create signal map (if necessary) */
 if (!selfp->signal_map) {
 selfp->signal_map = z_map_new(CTX);
 z_map_set_compare(selfp->signal_map, map_compare);
 z_map_set_key_destruct(selfp->signal_map, (ZMapItemCallback) free);
 z_map_set_value_destruct(selfp->signal_map, (ZMapItemCallback) z_object_unref);
 }

 /* locate signal's closure list by name */
 ZMapIter *it = z_map_find(selfp->signal_map, name);

 if (!it) {
 ZVector *closure_list = z_vector_new(CTX);
 z_vector_set_item_size(closure_list, 0);
 z_vector_set_item_destruct(closure_list, (ZVectorItemCallback) z_object_unref);
 z_map_insert(selfp->signal_map, strdup(name), closure_list);
 }
 }
#line 216 "z-object.zco"
int  z_object_emit_signal(Self *self,char *name,void *argv)
{
 assert(selfp->signal_map != NULL);

 /* locate signal's closure list by name */
 ZMapIter *map_iter = z_map_find(selfp->signal_map, name);
 assert(map_iter != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, map_iter);
 z_object_unref(Z_OBJECT(map_iter));

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

 z_object_unref(Z_OBJECT(end));
 z_object_unref(Z_OBJECT(it));
 return rc;
 }
#line 246 "z-object.zco"
void  z_object_add_attached_property_map(Self *self,void *map)
{
 if (selfp->attached_properties == 0) {
 selfp->attached_properties = z_vector_new(CTX);
 z_vector_set_item_size(selfp->attached_properties, sizeof(void *));
 }

 /* keep note of the maps that has a pointer to 'self' */
 z_vector_push_back((ZVector *) selfp->attached_properties, map);
 }
#line 257 "z-object.zco"
static int  z_object_map_compare(ZMap *map,const void *a,const void *b)
{
 return strcmp(a, b);
 }

#line 261 "z-object.zco"


