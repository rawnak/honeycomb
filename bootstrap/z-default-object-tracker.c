/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-default-object-tracker.c: Bootstrap file for z-default-object-tracker.zco
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

#line 11 "z-default-object-tracker.zco"

#include <z-value.h>
#include <assert.h>
#include <stdio.h>

#include <z-map.h>
#include <string.h>
#include <z-default-object-tracker.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZDefaultObjectTracker
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_default_object_tracker_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 15 "z-default-object-tracker.zco"
#define init z_default_object_tracker_init
#line 19 "z-default-object-tracker.zco"
#define new z_default_object_tracker_new

int z_default_object_tracker_type_id = -1;

static Self *__z_default_object_tracker_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_default_object_tracker_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 15 "z-default-object-tracker.zco"
static void z_default_object_tracker_init(Self *self);
#line 26 "z-default-object-tracker.zco"
static ZObject *  z_default_object_tracker_create(ZObjectTracker *self,int type_id);
#line 32 "z-default-object-tracker.zco"
static int  z_default_object_tracker_destroy(ZObjectTracker *self,ZObject *target);
#line 38 "z-default-object-tracker.zco"
static void  z_default_object_tracker_garbage_collect(ZObjectTracker *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZDefaultObjectTrackerGlobal * z_default_object_tracker_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_default_object_tracker_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_default_object_tracker_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZDefaultObjectTrackerGlobal *global = (ZDefaultObjectTrackerGlobal *) malloc(sizeof(struct ZDefaultObjectTrackerGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZDefaultObjectTrackerClass));
		memset(global->_class, 0, sizeof(struct ZDefaultObjectTrackerClass));
		global->name = "ZDefaultObjectTracker";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZDefaultObjectTracker temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			if (p_class->id > class_off_size)
				class_off_size = p_class->id;
		}
		{
			struct ZObjectTrackerGlobal *p_class = z_object_tracker_get_type(ctx);
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
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
			class_off_list[p_class->id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		{
			struct ZObjectTrackerGlobal *p_class = z_object_tracker_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object_tracker);
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectTrackerClass));
			class_off_list[p_class->id] = offset;
			offset += sizeof(struct ZObjectTrackerClass);
		}
		((ZObjectClass *) global->_class)->class_off_list = class_off_list;
		if (z_default_object_tracker_type_id == -1)
			z_default_object_tracker_type_id = zco_allocate_type_id();
		global->id = z_default_object_tracker_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_default_object_tracker_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_default_object_tracker_type_id);
		*global_ptr = global;
		
#line 26 "z-default-object-tracker.zco"
		{
#line 26 "z-default-object-tracker.zco"
			ZObjectTrackerClass *p_class = &global->_class->parent_z_object_tracker;
#line 26 "z-default-object-tracker.zco"
			global->__parent_create = p_class->__create;
#line 26 "z-default-object-tracker.zco"
			p_class->__create = z_default_object_tracker_create;
#line 26 "z-default-object-tracker.zco"
		}
#line 32 "z-default-object-tracker.zco"
		{
#line 32 "z-default-object-tracker.zco"
			ZObjectTrackerClass *p_class = &global->_class->parent_z_object_tracker;
#line 32 "z-default-object-tracker.zco"
			global->__parent_destroy = p_class->__destroy;
#line 32 "z-default-object-tracker.zco"
			p_class->__destroy = z_default_object_tracker_destroy;
#line 32 "z-default-object-tracker.zco"
		}
#line 38 "z-default-object-tracker.zco"
		{
#line 38 "z-default-object-tracker.zco"
			ZObjectTrackerClass *p_class = &global->_class->parent_z_object_tracker;
#line 38 "z-default-object-tracker.zco"
			global->__parent_garbage_collect = p_class->__garbage_collect;
#line 38 "z-default-object-tracker.zco"
			p_class->__garbage_collect = z_default_object_tracker_garbage_collect;
#line 38 "z-default-object-tracker.zco"
		}
		__z_default_object_tracker_class_init(ctx, (ZDefaultObjectTrackerClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 19 "z-default-object-tracker.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZDefaultObjectTrackerGlobal *) global);
		#endif
		return global;
	}
	return (ZDefaultObjectTrackerGlobal *) *global_ptr;
}

void __z_default_object_tracker_class_init(struct zco_context_t *ctx, ZDefaultObjectTrackerClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	__z_object_tracker_class_init(ctx, (ZObjectTrackerClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_default_object_tracker_init(struct zco_context_t *ctx, Self *self)
{
	struct ZDefaultObjectTrackerGlobal *_global = z_default_object_tracker_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, Z_OBJECT(self));
	__z_object_tracker_init(ctx, Z_OBJECT_TRACKER(self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 15 "z-default-object-tracker.zco"
static void z_default_object_tracker_init(Self *self)
{
 }
#line 19 "z-default-object-tracker.zco"
Self * z_default_object_tracker_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 26 "z-default-object-tracker.zco"
#define PARENT_HANDLER self->_global->__parent_create
static ZObject *  z_default_object_tracker_create(ZObjectTracker *self,int type_id)
{

 }
#undef PARENT_HANDLER
#line 32 "z-default-object-tracker.zco"
#define PARENT_HANDLER self->_global->__parent_destroy
static int  z_default_object_tracker_destroy(ZObjectTracker *self,ZObject *target)
{
 z_object_dispose(target);
 }
#undef PARENT_HANDLER
#line 38 "z-default-object-tracker.zco"
#define PARENT_HANDLER self->_global->__parent_garbage_collect
static void  z_default_object_tracker_garbage_collect(ZObjectTracker *self)
{

 }
#undef PARENT_HANDLER

#line 42 "z-default-object-tracker.zco"


