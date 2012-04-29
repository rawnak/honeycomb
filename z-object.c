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

#include <string.h>
#include <z-object.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZObject
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_object_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 14 "z-object.zco"
#define init z_object_init
#line 19 "z-object.zco"
#define dispose z_object_dispose
#line 24 "z-object.zco"
#define ref z_object_ref
#line 29 "z-object.zco"
#define unref z_object_unref

int z_object_type_id = -1;

static Self *__z_object_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_object_init(ctx, self);
	return self;
}
#line 14 "z-object.zco"
static void z_object_init(Self *self);
#line 19 "z-object.zco"
static void  z_object_virtual_dispose(Self *self);

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
#line 19 "z-object.zco"
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
#line 14 "z-object.zco"
static void z_object_init(Self *self)
{
 selfp->ref_count = 1;
 }
#line 19 "z-object.zco"
void  z_object_dispose(Self *self)
{
	ZObject *obj = (ZObject *) self;
	((ZObjectClass *) ((char *) obj->class_base + obj->vtable[z_object_type_id]))->__dispose(self);
}
#line 19 "z-object.zco"
static void  z_object_virtual_dispose(Self *self)
{
 free(self);
 }
#line 24 "z-object.zco"
void  z_object_ref(Self *self)
{
 ++selfp->ref_count;
 }
#line 29 "z-object.zco"
void  z_object_unref(Self *self)
{
 assert(selfp->ref_count > 0);
 if (--selfp->ref_count == 0)
 dispose(self);
 }



