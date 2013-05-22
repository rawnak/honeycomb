/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-default-object-tracker.h: Bootstrap file for z-default-object-tracker.zco
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

#ifndef _Z_DEFAULT_OBJECT_TRACKER_H_
#define _Z_DEFAULT_OBJECT_TRACKER_H_

#include <z-object-tracker.h>
#include <z-map.h>
#include <z-vector.h>
#include <z-object.h>

#include <zco-type.h>
#define Self ZDefaultObjectTracker
#define Z_DEFAULT_OBJECT_TRACKER(s) ((ZDefaultObjectTracker *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_default_object_tracker_type_id]))


struct ZDefaultObjectTrackerPrivate;
struct ZDefaultObjectTrackerProtected;
struct ZDefaultObjectTrackerGlobal;
struct ZDefaultObjectTrackerClass;
struct ZDefaultObjectTracker;

typedef struct ZDefaultObjectTrackerPrivate ZDefaultObjectTrackerPrivate;
typedef struct ZDefaultObjectTrackerProtected ZDefaultObjectTrackerProtected;
typedef struct ZDefaultObjectTrackerGlobal ZDefaultObjectTrackerGlobal;
typedef struct ZDefaultObjectTrackerClass ZDefaultObjectTrackerClass;
typedef struct ZDefaultObjectTracker ZDefaultObjectTracker;

struct ZDefaultObjectTrackerPrivate {
	ZMap *pools;
	int suspended;
	int is_destroying;
};

struct ZDefaultObjectTrackerProtected {
};

struct ZDefaultObjectTrackerGlobal {
	struct ZCommonGlobal common;
	struct ZDefaultObjectTrackerClass *_class;
	void  (*__parent_dispose)(ZObject *object);
	ZObject *  (*__parent_create)(ZObjectTracker *tracker,int type_id);
	int  (*__parent_destroy)(ZObjectTracker *tracker,ZObject *target);
	int  (*__parent_garbage_collect)(ZObjectTracker *tracker);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZDefaultObjectTrackerClass {
	struct ZObjectClass parent_z_object;
	struct ZObjectTrackerClass parent_z_object_tracker;
};

struct ZDefaultObjectTracker {
	struct ZObject parent_z_object;
	struct ZObjectTracker parent_z_object_tracker;
	struct ZDefaultObjectTrackerGlobal *_global;
	struct ZDefaultObjectTrackerPrivate _priv;
	struct ZDefaultObjectTrackerProtected _prot;
};
extern int z_default_object_tracker_type_id;
ZDefaultObjectTrackerGlobal * z_default_object_tracker_get_type(struct zco_context_t *ctx);
void __z_default_object_tracker_init(struct zco_context_t *ctx, ZDefaultObjectTracker *self);
void __z_default_object_tracker_class_init(struct zco_context_t *ctx, ZDefaultObjectTrackerClass *_class);
Self * z_default_object_tracker_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);

#undef Self


#endif
