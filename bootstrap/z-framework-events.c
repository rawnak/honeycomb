/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-framework-events.c: Bootstrap file for z-framework-events.zco
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

#line 7 "z-framework-events.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-framework-events.h>
#include <zco-type.h>
#include <stdlib.h>
#include <z-vector.h>
#include <z-value.h>
#define Self ZFrameworkEvents
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_framework_events_new(ctx)
#define INIT_EXISTS
#line 11 "z-framework-events.zco"
#define init z_framework_events_init
#line 15 "z-framework-events.zco"
#define new z_framework_events_new
#line 22 "z-framework-events.zco"
#define resize_event z_framework_events_resize_event
#line 23 "z-framework-events.zco"
#define draw_event z_framework_events_draw_event
#line 24 "z-framework-events.zco"
#define io_event z_framework_events_io_event

int z_framework_events_type_id = -1;

static Self *__z_framework_events_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_framework_events_type_id);
	if (!self) {
		self = (Self *) malloc(sizeof(Self));
		__z_framework_events_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 11 "z-framework-events.zco"
static void z_framework_events_init(Self *self);
#line 25 "z-framework-events.zco"
static void z_framework_events_class_destroy(ZObjectGlobal *gbl);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZFrameworkEventsGlobal * z_framework_events_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_framework_events_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_framework_events_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZFrameworkEventsGlobal *global = (ZFrameworkEventsGlobal *) malloc(sizeof(struct ZFrameworkEventsGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZFrameworkEventsClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZFrameworkEventsClass));
		global->common.name = "ZFrameworkEvents";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZFrameworkEvents temp;
		struct ZFrameworkEventsClass temp_class;

		{
			struct ZObjectGlobal *p_global = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_global->common.vtable_off_list,
				p_global->common.vtable_off_size,
				&temp,
				&temp.parent_z_object);
			zco_inherit_vtable(
				&global->common.svtable_off_list,
				&global->common.svtable_off_size,
				p_global->common.svtable_off_list,
				p_global->common.svtable_off_size,
				&temp_class,
				&temp_class.parent_z_object);
			ZObjectClass *p1_class = CLASS_FROM_GLOBAL(p_global);
			ZObjectClass *p2_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			memcpy(p2_class, p1_class, sizeof(struct ZObjectClass));
		}
		if (z_framework_events_type_id == -1)
			z_framework_events_type_id = zco_allocate_type_id();
		global->common.id = z_framework_events_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_framework_events_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_framework_events_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_framework_events_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
#line 25 "z-framework-events.zco"
		{
#line 25 "z-framework-events.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
#line 25 "z-framework-events.zco"
			global->__parent_class_destroy = p_class->__class_destroy;
#line 25 "z-framework-events.zco"
			p_class->__class_destroy = z_framework_events_class_destroy;
#line 25 "z-framework-events.zco"
		}
		__z_framework_events_class_init(ctx, (ZFrameworkEventsClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
#line 15 "z-framework-events.zco"
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZFrameworkEventsGlobal *) global);
		#endif
		return global;
	}
	return (ZFrameworkEventsGlobal *) *global_ptr;
}

void __z_framework_events_class_init(struct zco_context_t *ctx, ZFrameworkEventsClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_framework_events_init(struct zco_context_t *ctx, Self *self)
{
	struct ZFrameworkEventsGlobal *_global = z_framework_events_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
#line 22 "z-framework-events.zco"
	z_object_register_signal(Z_OBJECT(self), "resize_event");
#line 23 "z-framework-events.zco"
	z_object_register_signal(Z_OBJECT(self), "draw_event");
#line 24 "z-framework-events.zco"
	z_object_register_signal(Z_OBJECT(self), "io_event");
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 11 "z-framework-events.zco"
static void z_framework_events_init(Self *self)
{
 }
#line 15 "z-framework-events.zco"
Self * z_framework_events_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 22 "z-framework-events.zco"
void  z_framework_events_resize_event(Self *self,ZString *output)
#line 22 "z-framework-events.zco"
{
#line 22 "z-framework-events.zco"
	ZVector *args = z_vector_new(CTX_FROM_OBJECT(self));
	z_vector_set_item_size(args, 0);
#line 22 "z-framework-events.zco"
	z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);
#line 22 "z-framework-events.zco"
	{
#line 22 "z-framework-events.zco"
		ZValue *value = z_value_new(CTX_FROM_OBJECT(self));
#line 22 "z-framework-events.zco"
		z_value_set_as_object(value, Z_OBJECT(output));
#line 22 "z-framework-events.zco"
		z_vector_push_back(args, value);
#line 22 "z-framework-events.zco"
	}
#line 22 "z-framework-events.zco"
	z_object_emit_signal(Z_OBJECT(self), "resize_event", args);
#line 22 "z-framework-events.zco"
	z_object_unref(Z_OBJECT(args));
#line 22 "z-framework-events.zco"
}
#line 23 "z-framework-events.zco"
void  z_framework_events_draw_event(Self *self,ZString *output)
#line 23 "z-framework-events.zco"
{
#line 23 "z-framework-events.zco"
	ZVector *args = z_vector_new(CTX_FROM_OBJECT(self));
	z_vector_set_item_size(args, 0);
#line 23 "z-framework-events.zco"
	z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);
#line 23 "z-framework-events.zco"
	{
#line 23 "z-framework-events.zco"
		ZValue *value = z_value_new(CTX_FROM_OBJECT(self));
#line 23 "z-framework-events.zco"
		z_value_set_as_object(value, Z_OBJECT(output));
#line 23 "z-framework-events.zco"
		z_vector_push_back(args, value);
#line 23 "z-framework-events.zco"
	}
#line 23 "z-framework-events.zco"
	z_object_emit_signal(Z_OBJECT(self), "draw_event", args);
#line 23 "z-framework-events.zco"
	z_object_unref(Z_OBJECT(args));
#line 23 "z-framework-events.zco"
}
#line 24 "z-framework-events.zco"
void  z_framework_events_io_event(Self *self)
#line 24 "z-framework-events.zco"
{
#line 24 "z-framework-events.zco"
	ZVector *args = z_vector_new(CTX_FROM_OBJECT(self));
	z_vector_set_item_size(args, 0);
#line 24 "z-framework-events.zco"
	z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);
#line 24 "z-framework-events.zco"
	z_object_emit_signal(Z_OBJECT(self), "io_event", args);
#line 24 "z-framework-events.zco"
	z_object_unref(Z_OBJECT(args));
#line 24 "z-framework-events.zco"
}
#line 25 "z-framework-events.zco"
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_framework_events_class_destroy(ZObjectGlobal *gbl)
{
	ZFrameworkEventsGlobal *_global = (ZFrameworkEventsGlobal *) gbl;

}

#undef PARENT_HANDLER

#line 25 "z-framework-events.zco"


