/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-framework-events.h: Bootstrap file for z-framework-events.zco
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

#ifndef _Z_FRAMEWORK_EVENTS_H_
#define _Z_FRAMEWORK_EVENTS_H_

#include <z-object.h>
#include <z-string.h>

#include <zco-type.h>
#define Self ZFrameworkEvents
#define Z_FRAMEWORK_EVENTS(s) ((ZFrameworkEvents *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_framework_events_type_id]))


struct ZFrameworkEventsPrivate;
struct ZFrameworkEventsProtected;
struct ZFrameworkEventsGlobal;
struct ZFrameworkEventsClass;
struct ZFrameworkEvents;

typedef struct ZFrameworkEventsPrivate ZFrameworkEventsPrivate;
typedef struct ZFrameworkEventsProtected ZFrameworkEventsProtected;
typedef struct ZFrameworkEventsGlobal ZFrameworkEventsGlobal;
typedef struct ZFrameworkEventsClass ZFrameworkEventsClass;
typedef struct ZFrameworkEvents ZFrameworkEvents;

struct ZFrameworkEventsPrivate {
};

struct ZFrameworkEventsProtected {
};

struct ZFrameworkEventsGlobal {
	struct ZCommonGlobal common;
	struct ZFrameworkEventsClass *_class;
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZFrameworkEventsClass {
	struct ZObjectClass parent_z_object;
};

struct ZFrameworkEvents {
	struct ZObject parent_z_object;
	struct ZFrameworkEventsGlobal *_global;
	struct ZFrameworkEventsPrivate _priv;
	struct ZFrameworkEventsProtected _prot;
};
extern int z_framework_events_type_id;
ZFrameworkEventsGlobal * z_framework_events_get_type(struct zco_context_t *ctx);
void __z_framework_events_init(struct zco_context_t *ctx, ZFrameworkEvents *self);
void __z_framework_events_class_init(struct zco_context_t *ctx, ZFrameworkEventsClass *_class);
Self * z_framework_events_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
void  z_framework_events_resize_event(Self *self,ZString *output);
void  z_framework_events_draw_event(Self *self,ZString *output);
void  z_framework_events_io_event(Self *self);

#undef Self


#endif
