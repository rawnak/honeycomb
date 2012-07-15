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
#line 26 "z-object.zco"
#define init z_object_init
#line 33 "z-object.zco"
#define dispose z_object_dispose
#line 70 "z-object.zco"
#define ref z_object_ref
#line 75 "z-object.zco"
#define unref z_object_unref
#line 82 "z-object.zco"
#define connect z_object_connect
#line 110 "z-object.zco"
#define disconnect z_object_disconnect
#line 133 "z-object.zco"
#define register_signal z_object_register_signal
#line 148 "z-object.zco"
#define emit_signal z_object_emit_signal
#line 171 "z-object.zco"
#define add_attached_property_map z_object_add_attached_property_map
#line 180 "z-object.zco"
#define map_compare z_object_map_compare

int z_object_type_id = -1;
static ZObjectGlobal * z_object_global;

static Self *__z_object_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_object_init(ctx, self);
	return self;
}
#line 26 "z-object.zco"
static void z_object_init(Self *self);
#line 33 "z-object.zco"
static void  z_object_virtual_dispose(Self *self);
#line 180 "z-object.zco"
static int  z_object_map_compare(ZMap *map,const void *a,const void *b);

ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx)
{
	if (z_object_type_id == -1)
		z_object_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_object_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZObjectGlobal));
		struct ZObjectGlobal *global = (ZObjectGlobal *) *global_ptr;
		z_object_global = global;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZObjectClass));
		memset(global->_class, 0, sizeof(struct ZObjectClass));
		global->name = "ZObject";
		global->id = z_object_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZObjectClass temp;

		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_object_type_id);		
#line 33 "z-object.zco"
		global->_class->__dispose = z_object_virtual_dispose;
		#ifdef CLASS_INIT_EXISTS
			class_init((ZObjectGlobal *) global);
		#endif
	}
	return (ZObjectGlobal *) *global_ptr;
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
#line 26 "z-object.zco"
static void z_object_init(Self *self)
{
 selfp->ref_count = 1;
 selfp->attached_properties = 0;
 selfp->signal_map = 0;
 }
#line 33 "z-object.zco"
void  z_object_dispose(Self *self)
{
	ZObject *obj = (ZObject *) self;
	((ZObjectClass *) ((char *) obj->class_base + obj->vtable[z_object_type_id]))->__dispose(self);
}
#line 33 "z-object.zco"
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
#line 70 "z-object.zco"
void  z_object_ref(Self *self)
{
 ++selfp->ref_count;
 }
#line 75 "z-object.zco"
void  z_object_unref(Self *self)
{
 assert(selfp->ref_count > 0);
 if (--selfp->ref_count == 0)
 dispose(self);
 }
#line 82 "z-object.zco"
void *  z_object_connect(Self *self,char *name,ZObjectSignalHandler handler,void *userdata)
{
 ZClosure *closure;

 /* create a closure */
 closure = z_closure_new(CTX);
 z_closure_set_handler(closure, handler);
 z_closure_set_userdata(closure, userdata);

 /* create signal map (if necessary) */
 if (!selfp->signal_map) {
 selfp->signal_map = z_map_new(CTX);
 z_map_set_compare(selfp->signal_map, map_compare);
 z_map_set_key_destruct(selfp->signal_map, (ZMapItemCallback) free);
 z_map_set_value_destruct(selfp->signal_map, (ZMapItemCallback) z_object_unref);
 }

 /* locate signal's closure list by name */
 ZMapIter *it = z_map_find(selfp->signal_map, name);
 assert(it != NULL);
 ZVector *closure_list = z_map_get_value(selfp->signal_map, it);

 /* add new closure into the signal */
 z_vector_push_back(closure_list, closure);

 return closure;
 }
#line 110 "z-object.zco"
void  z_object_disconnect(Self *self,char *name,void *key)
{
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
#line 133 "z-object.zco"
void  z_object_register_signal(Self *self,char *name)
{
 /* locate signal's closure list by name */
 ZMapIter *it = z_map_find(selfp->signal_map, name);

 if (!it) {
 ZVector *closure_list = z_vector_new(CTX, sizeof(void *));
 z_vector_set_item_destruct(closure_list, (ZVectorItemCallback) z_object_unref);
 z_map_insert(selfp->signal_map, strdup(name), closure_list);
 }
 }
#line 148 "z-object.zco"
int  z_object_emit_signal(Self *self,char *name,void *argv)
{
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
 }

 return rc;
 }
#line 171 "z-object.zco"
void  z_object_add_attached_property_map(Self *self,void *map)
{
 if (selfp->attached_properties == 0)
 selfp->attached_properties = z_vector_new(CTX, sizeof(void *));

 /* keep note of the maps that has a pointer to 'self' */
 z_vector_push_back((ZVector *) selfp->attached_properties, map);
 }
#line 180 "z-object.zco"
static int  z_object_map_compare(ZMap *map,const void *a,const void *b)
{
 return strcmp(a, b);
 }



