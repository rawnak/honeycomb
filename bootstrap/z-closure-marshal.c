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
#include <z-memory-allocator.h>
#include <z-closure-marshal-protected.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZClosureMarshal
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_closure_marshal_new(ctx,allocator)
#define invoke z_closure_marshal_invoke

int z_closure_marshal_type_id = -1;

static Self *__z_closure_marshal_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_closure_marshal_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		ZMemoryAllocator *obj_allocator = ctx->fixed_allocator;
		if (obj_allocator)
			self = (Self *) z_memory_allocator_allocate(obj_allocator, sizeof(Self));
		else
			self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_closure_marshal_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static int  z_closure_marshal_virtual_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,ZVector *vargs,void *userdata);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZClosureMarshalGlobal * z_closure_marshal_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_closure_marshal_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_closure_marshal_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZClosureMarshalGlobal *global = (ZClosureMarshalGlobal *) malloc(sizeof(struct ZClosureMarshalGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZClosureMarshalClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZClosureMarshalClass));
		global->common.name = "ZClosureMarshal";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 0;

		struct ZClosureMarshal temp;
		struct ZClosureMarshalClass temp_class;

		if (z_closure_marshal_type_id == -1)
			z_closure_marshal_type_id = zco_allocate_type_id();
		global->common.id = z_closure_marshal_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_closure_marshal_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_closure_marshal_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_closure_marshal_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		CLASS_FROM_GLOBAL(global)->__invoke = z_closure_marshal_virtual_invoke;
		__z_closure_marshal_class_init(ctx, (ZClosureMarshalClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("invoke"), (ZObjectSignalHandler) invoke);
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
int  z_closure_marshal_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,ZVector *vargs,void *userdata)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_closure_marshal_type_id];
	((ZClosureMarshalClass *) ((char *) class_base + offset))->__invoke(self,target,handler,args,vargs,userdata);
}
static int  z_closure_marshal_virtual_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,ZVector *vargs,void *userdata)
{
 return 0; /* not handled */
 }



