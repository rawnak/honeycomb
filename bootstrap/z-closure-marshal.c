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



#include <string.h>
#include <z-closure-marshal.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZClosureMarshal
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_closure_marshal_new(ctx)
#define CTX self->_global->ctx
#define invoke z_closure_marshal_invoke

int z_closure_marshal_type_id = -1;
static ZClosureMarshalGlobal * z_closure_marshal_global;

static Self *__z_closure_marshal_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_closure_marshal_init(ctx, self);
	return self;
}
static int  z_closure_marshal_virtual_invoke(Self *self,ZObjectSignalHandler handler,ZVector *args,void *userdata);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZClosureMarshalGlobal * z_closure_marshal_get_type(struct zco_context_t *ctx)
{
	if (z_closure_marshal_type_id == -1)
		z_closure_marshal_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_closure_marshal_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZClosureMarshalGlobal));
		struct ZClosureMarshalGlobal *global = (ZClosureMarshalGlobal *) *global_ptr;
		z_closure_marshal_global = global;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZClosureMarshalClass));
		memset(global->_class, 0, sizeof(struct ZClosureMarshalClass));
		global->name = "ZClosureMarshal";
		global->id = z_closure_marshal_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZClosureMarshalClass temp;

		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_closure_marshal_type_id);		
		global->_class->__invoke = z_closure_marshal_virtual_invoke;
		#ifdef CLASS_INIT_EXISTS
			class_init((ZClosureMarshalGlobal *) global);
		#endif
	}
	return (ZClosureMarshalGlobal *) *global_ptr;
}

void __z_closure_marshal_init(struct zco_context_t *ctx, Self *self)
{
	struct ZClosureMarshalGlobal *_global = z_closure_marshal_get_type(ctx);
	self->_global = _global;
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
int  z_closure_marshal_invoke(Self *self,ZObjectSignalHandler handler,ZVector *args,void *userdata)
{
	ZObject *obj = (ZObject *) self;
	((ZClosureMarshalClass *) ((char *) obj->class_base + obj->vtable[z_closure_marshal_type_id]))->__invoke(self,handler,args,userdata);
}
static int  z_closure_marshal_virtual_invoke(Self *self,ZObjectSignalHandler handler,ZVector *args,void *userdata)
{
 return 0; /* not handled */
 }



