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

#line 10 "z-closure.zco"

#include <assert.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-closure.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZClosure
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_closure_new(ctx)
#define INIT_EXISTS
#line 19 "z-closure.zco"
#define init z_closure_init
#line 62 "z-closure.zco"
#define new z_closure_new
#line 68 "z-closure.zco"
#define dup z_closure_dup
#line 76 "z-closure.zco"
#define get_handler z_closure_get_handler
#line 80 "z-closure.zco"
#define set_handler z_closure_set_handler
#line 88 "z-closure.zco"
#define get_userdata z_closure_get_userdata
#line 92 "z-closure.zco"
#define set_userdata z_closure_set_userdata
#line 100 "z-closure.zco"
#define set_marshal z_closure_set_marshal
#line 112 "z-closure.zco"
#define set_target z_closure_set_target
#line 122 "z-closure.zco"
#define invoke z_closure_invoke

int z_closure_type_id = -1;

static Self *__z_closure_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_closure_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_closure_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 19 "z-closure.zco"
static void z_closure_init(Self *self);
#line 27 "z-closure.zco"
static void  z_closure_reset(ZObject *object);
#line 45 "z-closure.zco"
static void  z_closure_dispose(ZObject *object);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZClosureGlobal * z_closure_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_closure_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_closure_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZClosureGlobal *global = (ZClosureGlobal *) malloc(sizeof(struct ZClosureGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZClosureClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZClosureClass));
		global->name = "ZClosure";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZClosure temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			if (p_class->id > class_off_size)
				class_off_size = p_class->id;
		}
		class_off_list = malloc(sizeof(unsigned long) * (class_off_size+1));
		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			memcpy((char *) CLASS_FROM_GLOBAL(global) + offset, CLASS_FROM_GLOBAL(p_class), sizeof(struct ZObjectClass));
			class_off_list[p_class->id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		((ZObjectClass *) CLASS_FROM_GLOBAL(global))->class_off_list = class_off_list;
		if (z_closure_type_id == -1)
			z_closure_type_id = zco_allocate_type_id();
		global->id = z_closure_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_closure_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_closure_type_id);
		*global_ptr = global;
		
#line 27 "z-closure.zco"
		{
#line 27 "z-closure.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 27 "z-closure.zco"
			global->__parent_reset = p_class->__reset;
#line 27 "z-closure.zco"
			p_class->__reset = z_closure_reset;
#line 27 "z-closure.zco"
		}
#line 45 "z-closure.zco"
		{
#line 45 "z-closure.zco"
			ZObjectClass *p_class = &CLASS_FROM_GLOBAL(global)->parent_z_object;
#line 45 "z-closure.zco"
			global->__parent_dispose = p_class->__dispose;
#line 45 "z-closure.zco"
			p_class->__dispose = z_closure_dispose;
#line 45 "z-closure.zco"
		}
		__z_closure_class_init(ctx, (ZClosureClass *) CLASS_FROM_GLOBAL(global));
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 62 "z-closure.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 68 "z-closure.zco"
		z_map_insert((ZMap *) global->method_map, strdup("dup"), (ZObjectSignalHandler) dup);
#line 122 "z-closure.zco"
		z_map_insert((ZMap *) global->method_map, strdup("invoke"), (ZObjectSignalHandler) invoke);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZClosureGlobal *) global);
		#endif
		return global;
	}
	return (ZClosureGlobal *) *global_ptr;
}

void __z_closure_class_init(struct zco_context_t *ctx, ZClosureClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_closure_init(struct zco_context_t *ctx, Self *self)
{
	struct ZClosureGlobal *_global = z_closure_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 19 "z-closure.zco"
static void z_closure_init(Self *self)
{
 selfp->marshal = 0;
 selfp->handler = 0;
 selfp->target = 0;
 selfp->userdata = 0;
 }
#line 27 "z-closure.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_closure_reset(ZObject *object)
{
 ZClosure *self = (ZClosure *) object;
 
 if (selfp->marshal)
 z_object_unref(Z_OBJECT(selfp->marshal));

 if (selfp->target)
 z_object_unref(Z_OBJECT(selfp->target));

 selfp->marshal = 0;
 selfp->handler = 0;
 selfp->target = 0;
 selfp->userdata = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 45 "z-closure.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_closure_dispose(ZObject *object)
{
 ZClosure *self = (ZClosure *) object;
 
 if (selfp->marshal) {
 z_object_unref(Z_OBJECT(selfp->marshal));
 selfp->marshal = 0;
 }

 if (selfp->target) {
 z_object_unref(Z_OBJECT(selfp->target));
 selfp->target = 0;
 }

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 62 "z-closure.zco"
Self * z_closure_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 68 "z-closure.zco"
Self * z_closure_dup(ZClosure *src)
{
 Self *self = GET_NEW(src->_global->ctx);
 return self;
 }
#line 76 "z-closure.zco"
ZObjectSignalHandler  z_closure_get_handler(Self *self)
{
 return selfp->handler;
 }
#line 80 "z-closure.zco"
void z_closure_set_handler(Self *self, ZObjectSignalHandler  value)
{
 selfp->handler = value;
 }
#line 88 "z-closure.zco"
void *  z_closure_get_userdata(Self *self)
{
 return selfp->userdata;
 }
#line 92 "z-closure.zco"
void z_closure_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
#line 100 "z-closure.zco"
void z_closure_set_marshal(Self *self, ZClosureMarshal *  value)
{
 if (selfp->marshal)
 z_object_unref(Z_OBJECT(selfp->marshal));

 selfp->marshal = value;
 z_object_ref(Z_OBJECT(selfp->marshal));
 }
#line 112 "z-closure.zco"
void z_closure_set_target(Self *self, ZObject *  value)
{
 if (selfp->target)
 z_object_unref(Z_OBJECT(selfp->target));

 selfp->target = value;
 z_object_ref(Z_OBJECT(selfp->target));
 }
#line 122 "z-closure.zco"
int  z_closure_invoke(Self *self,ZVector *args)
{
 return z_closure_marshal_invoke(selfp->marshal, selfp->target, selfp->handler, args, selfp->userdata);
 }

#line 126 "z-closure.zco"


