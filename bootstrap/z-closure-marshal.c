/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-closure-marshal.c: Bootstrap file for z-closure-marshal.zco
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

#line 7 "z-closure-marshal.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-closure-marshal.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZClosureMarshal
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_closure_marshal_new(ctx)
#define CTX self->_global->ctx
#line 11 "z-closure-marshal.zco"
#define invoke z_closure_marshal_invoke

int z_closure_marshal_type_id = -1;

static Self *__z_closure_marshal_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_closure_marshal_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_closure_marshal_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 11 "z-closure-marshal.zco"
static int  z_closure_marshal_virtual_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,void *userdata);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZClosureMarshalGlobal * z_closure_marshal_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_closure_marshal_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_closure_marshal_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZClosureMarshalGlobal *global = (ZClosureMarshalGlobal *) malloc(sizeof(struct ZClosureMarshalGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZClosureMarshalClass));
		memset(global->_class, 0, sizeof(struct ZClosureMarshalClass));
		global->name = "ZClosureMarshal";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 0;

		struct ZClosureMarshal temp;
		unsigned long offset = 0;

		if (z_closure_marshal_type_id == -1)
			z_closure_marshal_type_id = zco_allocate_type_id();
		global->id = z_closure_marshal_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_closure_marshal_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_closure_marshal_type_id);
		*global_ptr = global;
		
#line 11 "z-closure-marshal.zco"
		global->_class->__invoke = z_closure_marshal_virtual_invoke;
		__z_closure_marshal_class_init(ctx, (ZClosureMarshalClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_userdata(global->method_map, global->method_map);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 11 "z-closure-marshal.zco"
		z_map_insert((ZMap *) global->method_map, strdup("invoke"), (ZObjectSignalHandler) invoke);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZClosureMarshalGlobal *) global);
		#endif
		return global;
	}
	return (ZClosureMarshalGlobal *) *global_ptr;
}

void __z_closure_marshal_class_init(struct zco_context_t *ctx, ZClosureMarshalClass *_class)
{
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_closure_marshal_init(struct zco_context_t *ctx, Self *self)
{
	struct ZClosureMarshalGlobal *_global = z_closure_marshal_get_type(ctx);
	self->_global = _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 11 "z-closure-marshal.zco"
int  z_closure_marshal_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,void *userdata)
{
	ZObject *obj = (ZObject *) self;
	unsigned long offset = ((ZObjectClass *) obj->class_base)->class_off_list[z_closure_marshal_type_id];
	((ZClosureMarshalClass *) ((char *) obj->class_base + offset))->__invoke(self,target,handler,args,userdata);
}
#line 11 "z-closure-marshal.zco"
static int  z_closure_marshal_virtual_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,void *userdata)
{
 return 0; /* not handled */
 }

#line 15 "z-closure-marshal.zco"


