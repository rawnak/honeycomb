/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-closure.c: Bootstrap file for z-closure.zco
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

#include <string.h>
#include <z-closure.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZClosure
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_closure_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 18 "z-closure.zco"
#define init z_closure_init
#line 35 "z-closure.zco"
#define new z_closure_new
#line 41 "z-closure.zco"
#define dup z_closure_dup
#line 49 "z-closure.zco"
#define get_handler z_closure_get_handler
#line 53 "z-closure.zco"
#define set_handler z_closure_set_handler
#line 61 "z-closure.zco"
#define get_userdata z_closure_get_userdata
#line 65 "z-closure.zco"
#define set_userdata z_closure_set_userdata
#line 73 "z-closure.zco"
#define set_marshal z_closure_set_marshal
#line 83 "z-closure.zco"
#define invoke z_closure_invoke

int z_closure_type_id = -1;
static ZClosureGlobal * z_closure_global;

static Self *__z_closure_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_closure_init(ctx, self);
	return self;
}
#line 18 "z-closure.zco"
static void z_closure_init(Self *self);
#line 25 "z-closure.zco"
static void  z_closure_dispose(ZObject *object);

ZClosureGlobal * z_closure_get_type(struct zco_context_t *ctx)
{
	if (z_closure_type_id == -1)
		z_closure_type_id = zco_allocate_type_id();

	void **global_ptr = zco_get_ctx_type(ctx, z_closure_type_id);
	if (*global_ptr == 0) {
		*global_ptr = malloc(sizeof(struct ZClosureGlobal));
		struct ZClosureGlobal *global = (ZClosureGlobal *) *global_ptr;
		z_closure_global = global;
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZClosureClass));
		memset(global->_class, 0, sizeof(struct ZClosureClass));
		global->name = "ZClosure";
		global->id = z_closure_type_id;
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZClosureClass temp;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			unsigned long offset = global->vtable_off_list[z_object_type_id];
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
		}
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_closure_type_id);		
#line 25 "z-closure.zco"
		{
#line 25 "z-closure.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) global->_class + global->vtable_off_list[z_object_type_id]);
#line 25 "z-closure.zco"
			global->__parent_dispose = p_class->__dispose;
#line 25 "z-closure.zco"
			p_class->__dispose = z_closure_dispose;
#line 25 "z-closure.zco"
		}
		#ifdef CLASS_INIT_EXISTS
			class_init((ZClosureGlobal *) global);
		#endif
	}
	return (ZClosureGlobal *) *global_ptr;
}

void __z_closure_init(struct zco_context_t *ctx, Self *self)
{
	struct ZClosureGlobal *_global = z_closure_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, Z_OBJECT(self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 18 "z-closure.zco"
static void z_closure_init(Self *self)
{
 selfp->marshal = 0;
 selfp->handler = 0;
 selfp->userdata = 0;
 }
#line 25 "z-closure.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_closure_dispose(ZObject *object)
{
 ZClosure *self = (ZClosure *) object;
 
 if (selfp->marshal) {
 z_object_unref(Z_OBJECT(selfp->marshal));
 selfp->marshal = 0;
 }
 }
#undef PARENT_HANDLER
#line 35 "z-closure.zco"
Self * z_closure_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 41 "z-closure.zco"
Self * z_closure_dup(ZClosure *src)
{
 Self *self = GET_NEW(src->_global->ctx);
 return self;
 }
#line 49 "z-closure.zco"
ZObjectSignalHandler  z_closure_get_handler(Self *self)
{
 return selfp->handler;
 }
#line 53 "z-closure.zco"
void z_closure_set_handler(Self *self, ZObjectSignalHandler  value)
{
 selfp->handler = value;
 }
#line 61 "z-closure.zco"
void *  z_closure_get_userdata(Self *self)
{
 return selfp->userdata;
 }
#line 65 "z-closure.zco"
void z_closure_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
#line 73 "z-closure.zco"
void z_closure_set_marshal(Self *self, ZClosureMarshal *  value)
{
 if (selfp->marshal)
 z_object_unref(Z_OBJECT(selfp->marshal));

 selfp->marshal = value;
 z_object_ref(Z_OBJECT(selfp->marshal));
 }
#line 83 "z-closure.zco"
int  z_closure_invoke(Self *self,ZVector *args)
{
 return z_closure_marshal_invoke(selfp->marshal, selfp->handler, args);
 }



