/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-object-tracker.c: Bootstrap file for z-object-tracker.zco
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

#line 6 "z-object-tracker.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-object-tracker-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZObjectTracker
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_object_tracker_new(ctx,allocator)
#define create z_object_tracker_create
#define destroy z_object_tracker_destroy
#define garbage_collect z_object_tracker_garbage_collect

ZCO_DEFINE_CLASS_TYPE(z_object_tracker);

static ZObject *  z_object_tracker_virtual_create(Self *self,int type_id);
static int  z_object_tracker_virtual_destroy(Self *self,ZObject *target);
static int  z_object_tracker_virtual_garbage_collect(Self *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZObjectTrackerGlobal * z_object_tracker_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZObjectTracker, z_object_tracker, 0);
	ZCO_REGISTER_TYPE(z_object_tracker);
	ZCO_CREATE_VIRTUAL_METHOD(z_object_tracker, create);
	ZCO_CREATE_VIRTUAL_METHOD(z_object_tracker, destroy);
	ZCO_CREATE_VIRTUAL_METHOD(z_object_tracker, garbage_collect);
	ZCO_CREATE_METHOD_MAP(ZObjectTracker, z_object_tracker);
	ZCO_REGISTER_METHOD(create);
	ZCO_REGISTER_METHOD(destroy);
	ZCO_REGISTER_METHOD(garbage_collect);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
}

void __z_object_tracker_class_init(struct zco_context_t *ctx, ZObjectTrackerClass *_class)
{
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_object_tracker_init(struct zco_context_t *ctx, Self *self)
{
	ZCO_INIT_START(ZObjectTracker, z_object_tracker);
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
ZObject *  z_object_tracker_create(Self *self,int type_id)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_tracker_type_id];
	((ZObjectTrackerClass *) ((char *) class_base + offset))->__create(self,type_id);
}
}
static ZObject *  z_object_tracker_virtual_create(Self *self,int type_id)
{
 return 0; /* not handled */
 }
int  z_object_tracker_destroy(Self *self,ZObject *target)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_tracker_type_id];
	((ZObjectTrackerClass *) ((char *) class_base + offset))->__destroy(self,target);
}
}
static int  z_object_tracker_virtual_destroy(Self *self,ZObject *target)
{
 return -1; /* not handled */
 }
int  z_object_tracker_garbage_collect(Self *self)
{
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_tracker_type_id];
	((ZObjectTrackerClass *) ((char *) class_base + offset))->__garbage_collect(self);
}
}
static int  z_object_tracker_virtual_garbage_collect(Self *self)
{
 return 0; /* no objects collected */
 }



