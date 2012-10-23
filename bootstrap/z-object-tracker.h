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
#line 3 "z-object-tracker.zco"

#include <z-object.h>

#include <zco-type.h>
#define Self ZObjectTracker
#define Z_OBJECT_TRACKER(s) ((ZObjectTracker *) ((char *) (s) + (s)->_global->vtable_off_list[z_object_tracker_type_id]))


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
	int *vtable_off_list;
	int vtable_off_size;
	int is_object;
	struct ZObjectTrackerClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
};

struct ZObjectTrackerClass {
#line 10 "z-object-tracker.zco"
	ZObject *  (*__create)(Self *self,int type_id);
#line 15 "z-object-tracker.zco"
	int  (*__destroy)(Self *self,ZObject *target);
#line 20 "z-object-tracker.zco"
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
#line 10 "z-object-tracker.zco"
ZObject *  z_object_tracker_create(Self *self,int type_id);
#line 15 "z-object-tracker.zco"
int  z_object_tracker_destroy(Self *self,ZObject *target);
#line 20 "z-object-tracker.zco"
int  z_object_tracker_garbage_collect(Self *self);

#undef Self


#endif
