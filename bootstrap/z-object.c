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


#include <assert.h>
#include <z-map.h>
#include <z-vector.h>
#include <z-vector-iter.h>
#include <z-closure.h>
#include <z-closure-marshal.h>
#include <z-string.h>

#include <string.h>
#include <z-object.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZObject
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_object_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#define init z_object_init
#define CLASS_INIT_EXISTS
#define class_init z_object_class_init
#define dispose z_object_dispose
#define ref z_object_ref
#define unref z_object_unref
#define connect z_object_connect
#define disconnect z_object_disconnect
#define register_method z_object_register_method
#define register_signal z_object_register_signal
#define emit_signal z_object_emit_signal
#define add_attached_property_map z_object_add_attached_property_map
#define map_compare z_object_map_compare

int z_object_type_id = -1;

static Self *__z_object_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_object_init(ctx, self);
	return self;
}
static void z_object_init(Self *self);
static void z_object_class_init(struct zco_context_t *ctx,ZObjectClass *_class);
static void  z_object_virtual_dispose(Self *self);
static int  z_object_map_compare(ZMap *map,const void *a,const void *b);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx)
{
	if (z_object_type_id == -1)
		z_object_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_object_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZObjectGlobal));
		struct ZObjectGlobal *global = (ZObjectGlobal *) *global_ptr;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZObjectClass));
		memset(global->_class, 0, sizeof(struct ZObjectClass));
		global->name = "ZObject";
		global->id = z_object_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZObjectClass temp;

		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_object_type_id);		
		global->_class->__dispose = z_object_virtual_dispose;
		__z_object_class_init(ctx, (ZObjectClass *) &temp);
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
	z_object_register_method(ctx, (ZObjectClass *) _class, "dispose", (ZObjectSignalHandler) dispose);
	z_object_register_method(ctx, (ZObjectClass *) _class, "ref", (ZObjectSignalHandler) ref);
	z_object_register_method(ctx, (ZObjectClass *) _class, "unref", (ZObjectSignalHandler) unref);
	z_object_register_method(ctx, (ZObjectClass *) _class, "connect", (ZObjectSignalHandler) connect);
	z_object_register_method(ctx, (ZObjectClass *) _class, "disconnect", (ZObjectSignalHandler) disconnect);
	z_object_register_method(ctx, (ZObjectClass *) _class, "register_method", (ZObjectSignalHandler) register_method);
	z_object_register_method(ctx, (ZObjectClass *) _class, "register_signal", (ZObjectSignalHandler) register_signal);
	z_object_register_method(ctx, (ZObjectClass *) _class, "emit_signal", (ZObjectSignalHandler) emit_signal);
	z_object_register_method(ctx, (ZObjectClass *) _class, "add_attached_property_map", (ZObjectSignalHandler) add_attached_property_map);
}
void __z_object_init(struct zco_context_t *ctx, Self *self)
{
	struct ZObjectGlobal *_global = z_object_get_type(ctx);
	self->_global = _global;
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
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
static void z_object_class_init(struct zco_context_t *ctx,ZObjectClass *_class)
{
 _class->method_map = NULL;
 }
void  z_object_dispose(Self *self)
{
	ZObject *obj = (ZObject *) self;
	((ZObjectClass *) ((char *) obj->class_base + obj->vtable[z_object_type_id]))->__dispose(self);
}
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
void  z_object_ref(Self *self)
{
 ++selfp->ref_count;
 }
void  z_object_unref(Self *self)
{
 assert(selfp->ref_count > 0);
 if (--selfp->ref_count == 0)
 dispose(self);
 }
void *  z_object_connect(Self *self,char *name,ZObject *target,char *method_name,void *userdata)
{
 ZClosure *closure;
 ZObjectSignalHandler handler;

 assert(selfp->signal_map != NULL);

 /* lookup handler from method_name */
 handler = NULL;

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
 }
void  z_object_register_method(struct zco_context_t *ctx,ZObjectClass *_class,char *name,ZObjectSignalHandler method)
{
 if (!_class->method_map) {
 _class->method_map = z_map_new(ctx);
 z_map_set_compare(_class->method_map, map_compare);
 z_map_set_key_destruct(_class->method_map, (ZMapItemCallback) free);
 }

 z_map_insert((ZMap *) _class->method_map, strdup(name), method);
 }
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
 ZVector *closure_list = z_vector_new(CTX, 0);
 z_vector_set_item_destruct(closure_list, (ZVectorItemCallback) z_object_unref);
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

 return rc;
 }
void  z_object_add_attached_property_map(Self *self,void *map)
{
 if (selfp->attached_properties == 0)
 selfp->attached_properties = z_vector_new(CTX, sizeof(void *));

 /* keep note of the maps that has a pointer to 'self' */
 z_vector_push_back((ZVector *) selfp->attached_properties, map);
 }
static int  z_object_map_compare(ZMap *map,const void *a,const void *b)
{
 return strcmp(a, b);
 }



