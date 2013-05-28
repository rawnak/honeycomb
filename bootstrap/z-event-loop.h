/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-event-loop.h: Bootstrap file for z-event-loop.zco
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

#ifndef _Z_EVENT_LOOP_H_
#define _Z_EVENT_LOOP_H_

#include <z-vector.h>
#include <z-closure.h>
#include <z-bind.h>
#include <signal.h>


#include <zco-type.h>
#define Self ZEventLoop
#define Z_EVENT_LOOP(s) ((ZEventLoop *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_event_loop_type_id]))


struct ZEventLoopPrivate;
struct ZEventLoopProtected;
struct ZEventLoopGlobal;
struct ZEventLoopClass;
struct ZEventLoop;

typedef struct ZEventLoopPrivate ZEventLoopPrivate;
typedef struct ZEventLoopProtected ZEventLoopProtected;
typedef struct ZEventLoopGlobal ZEventLoopGlobal;
typedef struct ZEventLoopClass ZEventLoopClass;
typedef struct ZEventLoop ZEventLoop;

struct ZEventLoopPrivate {
	ZBind *quit_task;
	pthread_t thread;
	ZBindData *read_queue;
	ZBindData *write_queue;
	pthread_cond_t schedule_cond;
	pthread_mutex_t read_queue_lock;
	pthread_mutex_t write_queue_lock;
	volatile sig_atomic_t is_done;
	volatile sig_atomic_t is_running;
};

struct ZEventLoopProtected {
};

struct ZEventLoopGlobal {
	struct ZCommonGlobal common;
	struct ZEventLoopClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZEventLoopClass {
	struct ZObjectClass parent_z_object;
};

struct ZEventLoop {
	struct ZObject parent_z_object;
	struct ZEventLoopGlobal *_global;
	struct ZEventLoopPrivate _priv;
	struct ZEventLoopProtected _prot;
};
extern int z_event_loop_type_id;
ZEventLoopGlobal * z_event_loop_get_type(struct zco_context_t *ctx);
void __z_event_loop_init(struct zco_context_t *ctx, ZEventLoop *self);
void __z_event_loop_class_init(struct zco_context_t *ctx, ZEventLoopClass *_class);
Self * z_event_loop_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
int  z_event_loop_get_is_current(Self *self);
void  z_event_loop_run(Self *self);
void  z_event_loop_post_task(Self *self,ZBind *bind,uint64_t ns);
void  z_event_loop_quit(Self *self);

#undef Self


#endif
