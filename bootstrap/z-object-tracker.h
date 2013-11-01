/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-object-tracker.h: Bootstrap file for z-object-tracker.zco
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

#ifndef _Z_OBJECT_TRACKER_H_
#define _Z_OBJECT_TRACKER_H_

#include <z-object.h>

#include <zco-context.h>
#define Self ZObjectTracker
#define Z_OBJECT_TRACKER(s) ((ZObjectTracker *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_object_tracker_type_id]))


struct ZObjectTrackerPrivate;
struct ZObjectTrackerProtected;
struct ZObjectTrackerGlobal;
struct ZObjectTrackerClass;
struct ZObjectTracker;

typedef struct ZObjectTrackerPrivate ZObjectTrackerPrivate;
typedef struct ZObjectTrackerProtected ZObjectTrackerProtected;
typedef struct ZObjectTrackerGlobal ZObjectTrackerGlobal;
typedef struct ZObjectTrackerClass ZObjectTrackerClass;
typedef struct ZObjectTracker ZObjectTracker;

struct ZObjectTrackerPrivate {
};

struct ZObjectTrackerProtected {
};

struct ZObjectTrackerGlobal {
	struct ZCommonGlobal common;
	struct ZObjectTrackerClass *_class;
};

struct ZObjectTrackerClass {
	ZObject *  (*__create)(Self *self,int type_id);
	int  (*__destroy)(Self *self,ZObject *target);
	int  (*__garbage_collect)(Self *self);
};

struct ZObjectTracker {
	struct ZObjectTrackerGlobal *_global;
	struct ZObjectTrackerPrivate _priv;
	struct ZObjectTrackerProtected _prot;
};
extern int z_object_tracker_type_id;
ZObjectTrackerGlobal * z_object_tracker_get_type(struct zco_context_t *ctx);
void __z_object_tracker_init(struct zco_context_t *ctx, ZObjectTracker *self);
void __z_object_tracker_class_init(struct zco_context_t *ctx, ZObjectTrackerClass *_class);
ZObject *  z_object_tracker_create(Self *self,int type_id);
int  z_object_tracker_destroy(Self *self,ZObject *target);
int  z_object_tracker_garbage_collect(Self *self);

#undef Self


#endif
