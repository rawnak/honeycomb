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

int z_object_tracker_type_id = -1;

static Self *__z_object_tracker_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_object_tracker_type_id);
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
		__z_object_tracker_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
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
	ZCommonGlobal **global_ptr = NULL;
	if (z_object_tracker_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_object_tracker_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZObjectTrackerGlobal *global = (ZObjectTrackerGlobal *) malloc(sizeof(struct ZObjectTrackerGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZObjectTrackerClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZObjectTrackerClass));
		global->common.name = "ZObjectTracker";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 0;

		struct ZObjectTracker temp;
		struct ZObjectTrackerClass temp_class;

		if (z_object_tracker_type_id == -1)
			z_object_tracker_type_id = zco_allocate_type_id();
		global->common.id = z_object_tracker_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_object_tracker_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_object_tracker_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_object_tracker_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		CLASS_FROM_GLOBAL(global)->__create = z_object_tracker_virtual_create;
		CLASS_FROM_GLOBAL(global)->__destroy = z_object_tracker_virtual_destroy;
		CLASS_FROM_GLOBAL(global)->__garbage_collect = z_object_tracker_virtual_garbage_collect;
		__z_object_tracker_class_init(ctx, (ZObjectTrackerClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("create"), (ZObjectSignalHandler) create);
		z_map_insert((ZMap *) global->common.method_map, strdup("destroy"), (ZObjectSignalHandler) destroy);
		z_map_insert((ZMap *) global->common.method_map, strdup("garbage_collect"), (ZObjectSignalHandler) garbage_collect);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZObjectTrackerGlobal *) global);
		#endif
		return global;
	}
	return (ZObjectTrackerGlobal *) *global_ptr;
}

void __z_object_tracker_class_init(struct zco_context_t *ctx, ZObjectTrackerClass *_class)
{
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_object_tracker_init(struct zco_context_t *ctx, Self *self)
{
	struct ZObjectTrackerGlobal *_global = z_object_tracker_get_type(ctx);
	self->_global = _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
ZObject *  z_object_tracker_create(Self *self,int type_id)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_tracker_type_id];
	((ZObjectTrackerClass *) ((char *) class_base + offset))->__create(self,type_id);
}
static ZObject *  z_object_tracker_virtual_create(Self *self,int type_id)
{
 return 0; /* not handled */
 }
int  z_object_tracker_destroy(Self *self,ZObject *target)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_tracker_type_id];
	((ZObjectTrackerClass *) ((char *) class_base + offset))->__destroy(self,target);
}
static int  z_object_tracker_virtual_destroy(Self *self,ZObject *target)
{
 return -1; /* not handled */
 }
int  z_object_tracker_garbage_collect(Self *self)
{
	ZObject *obj = (ZObject *) self;
	ZObjectClass *class_base = (ZObjectClass *) obj->class_base;
	ZCommonGlobal *common_global = class_base->real_global;
	unsigned long offset = common_global->svtable_off_list[z_object_tracker_type_id];
	((ZObjectTrackerClass *) ((char *) class_base + offset))->__garbage_collect(self);
}
static int  z_object_tracker_virtual_garbage_collect(Self *self)
{
 return 0; /* no objects collected */
 }



