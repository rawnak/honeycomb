/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-event-loop.c: Bootstrap file for z-event-loop.zco
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


#define _GNU_SOURCE

#include <z-value.h>
#include <z-bind.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* We require Linux kernel 2.6.37 or higher. The epoll_wait implementation for prior versions
   of the kernel assume an infinite wait time when the specified wait time is larger than
   LONG_MAX / HZ */
#define MAX_EVENTS 100


/* In an application, the first thread (main thread) will create a zco context. Lets call this
   the main context. The main thread can then create one or several zco contexts, each with an
   instance of ZEventLoop. Lets call these contexts the worker contexts. The ZEventLoop object
   will be under the worker context but, unlike other ZObject derived classes, some of its methods
   will be thread-safe.

   get_is_current() will return TRUE if the event loop is operating under the calling thread.

   run() will start the event loop in a new thread. This is not a blocking call since the loop
   will run on a new thread.

   post_task() will push a task described by a Bind object onto the context. The task will be
   scheduled to run after the specified timeout period. If a timeout of 0 is specified, it will
   run as soon as possible.

   quit() will push a QUIT task to the event loop. This task will set a flag so the event loop
   no longer waits for a new task. The event loop will still process any remaining tasks that
   are in the queue but it will not accept new tasks.
 */

#define INT_TO_PTR(x) ((void *) ((unsigned long) (x)))
#define PTR_TO_INT(x) ((int64_t) ((long) (x)))

struct ZTask {
 ZBindData request;
 ZBindData response;
 struct zco_context_t *origin_context;
 struct ZTask *next;
 uint64_t timeout;
 int has_request : 1;
 int has_response : 1;
 int no_wait : 1;
};


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-event-loop.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZEventLoop
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_event_loop_new(ctx,allocator)
#define map_compare z_event_loop_map_compare
#define runqueue_key_destroy z_event_loop_runqueue_key_destroy
#define runqueue_value_destroy z_event_loop_runqueue_value_destroy
#define INIT_EXISTS
#define init z_event_loop_init
#define set_fd_flags z_event_loop_set_fd_flags
#define delete_queue z_event_loop_delete_queue
#define new z_event_loop_new
#define get_is_current z_event_loop_get_is_current
#define all_tasks_are_nowait z_event_loop_all_tasks_are_nowait
#define run_tasks z_event_loop_run_tasks
#define reload_runqueue z_event_loop_reload_runqueue
#define get_ready_tasks z_event_loop_get_ready_tasks
#define wait_for_signal z_event_loop_wait_for_signal
#define get_next_task_time z_event_loop_get_next_task_time
#define reload_pending_queue z_event_loop_reload_pending_queue
#define thread_main z_event_loop_thread_main
#define run z_event_loop_run
#define get_name z_event_loop_get_name
#define set_name z_event_loop_set_name
#define is_active z_event_loop_is_active
#define convert_monotonic_to_realtime z_event_loop_convert_monotonic_to_realtime
#define get_monotonic_time z_event_loop_get_monotonic_time
#define add_to_task_queue z_event_loop_add_to_task_queue
#define post_task z_event_loop_post_task
#define zco_context_do_quit z_event_loop_zco_context_do_quit
#define quit z_event_loop_quit
#define join z_event_loop_join

int z_event_loop_type_id = -1;

static Self *__z_event_loop_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_event_loop_type_id);
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
		__z_event_loop_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static int  z_event_loop_map_compare(ZMap *map,const void *a,const void *b);
static void  z_event_loop_runqueue_key_destroy(void *item,Self *self);
static void  z_event_loop_runqueue_value_destroy(ZTask *bind_data,Self *self);
static void z_event_loop_init(Self *self);
static void  z_event_loop_set_fd_flags(int fd,int flags);
static void  z_event_loop_delete_queue(Self *self,ZTask **queue);
static void  z_event_loop_reset(ZObject *object);
static void  z_event_loop_dispose(ZObject *object);
static int  z_event_loop_all_tasks_are_nowait(Self *self);
static void  z_event_loop_run_tasks(Self *self,ZMapIter *it,ZMapIter *end);
static void  z_event_loop_reload_runqueue(Self *self);
static void  z_event_loop_get_ready_tasks(Self *self,ZMapIter **it,ZMapIter **end);
static void  z_event_loop_wait_for_signal(Self *self,struct timespec timeout);
static uint64_t  z_event_loop_get_next_task_time(Self *self);
static void  z_event_loop_reload_pending_queue(Self *self);
static void  z_event_loop_thread_main(Self *self);
static int  z_event_loop_is_active(Self *self);
static uint64_t  z_event_loop_convert_monotonic_to_realtime(Self *self,uint64_t monotonic);
static uint64_t  z_event_loop_get_monotonic_time();
static int  z_event_loop_add_to_task_queue(Self *self,ZTask *task);
static void  z_event_loop_zco_context_do_quit(ZBind *bind,Self *self);
static void z_event_loop_class_destroy(ZObjectGlobal *gbl);
static void z_event_loop___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZEventLoopGlobal * z_event_loop_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_event_loop_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_event_loop_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZEventLoopGlobal *global = (ZEventLoopGlobal *) malloc(sizeof(struct ZEventLoopGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZEventLoopClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZEventLoopClass));
		global->common.name = "ZEventLoop";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZEventLoop temp;
		struct ZEventLoopClass temp_class;

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
		if (z_event_loop_type_id == -1)
			z_event_loop_type_id = zco_allocate_type_id();
		global->common.id = z_event_loop_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_event_loop_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_event_loop_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_event_loop_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_event_loop_reset;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_event_loop_dispose;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_event_loop_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_event_loop___delete;
		}
		__z_event_loop_class_init(ctx, (ZEventLoopClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		z_map_insert((ZMap *) global->common.method_map, strdup("run"), (ZObjectSignalHandler) run);
		z_map_insert((ZMap *) global->common.method_map, strdup("post_task"), (ZObjectSignalHandler) post_task);
		z_map_insert((ZMap *) global->common.method_map, strdup("quit"), (ZObjectSignalHandler) quit);
		z_map_insert((ZMap *) global->common.method_map, strdup("join"), (ZObjectSignalHandler) join);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZEventLoopGlobal *) global);
		#endif
		return global;
	}
	return (ZEventLoopGlobal *) *global_ptr;
}

void __z_event_loop_class_init(struct zco_context_t *ctx, ZEventLoopClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_event_loop_init(struct zco_context_t *ctx, Self *self)
{
	struct ZEventLoopGlobal *_global = z_event_loop_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static int  z_event_loop_map_compare(ZMap *map,const void *a,const void *b)
{
#if __WORDSIZE >= 64
 return PTR_TO_INT(a) - PTR_TO_INT(b);
#else
 return *((uint64_t *) a) - *((uint64_t *) b);
#endif
 }
static void  z_event_loop_runqueue_key_destroy(void *item,Self *self)
{
 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
 z_memory_allocator_deallocate_by_size(allocator, item, sizeof(uint64_t));
 }
static void  z_event_loop_runqueue_value_destroy(ZTask *bind_data,Self *self)
{
 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->ts_fixed_allocator;
 z_memory_allocator_deallocate_by_size(allocator, bind_data, sizeof(ZTask));
 }
static void z_event_loop_init(Self *self)
{
 selfp->is_done = 0;
 selfp->is_running = 0;
 selfp->name = NULL;

 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 /* Create a bind closure for the quit task */
 selfp->quit_task = z_bind_new(ctx, allocator);
 z_bind_set_handler(selfp->quit_task, (ZBindHandler) zco_context_do_quit);
 z_bind_append_ptr(selfp->quit_task, self);

 /* Initialize task queues */
 selfp->run_queue = z_map_new(ctx, allocator);
 z_map_set_compare(selfp->run_queue, map_compare);
 z_map_set_userdata(selfp->run_queue, self);

#if __WORDSIZE < 64
 z_map_set_key_destruct(selfp->run_queue, (ZMapItemCallback) runqueue_key_destroy);
#endif
 z_map_set_value_destruct(selfp->run_queue, (ZMapItemCallback) runqueue_value_destroy);

#ifdef USE_IO_EVENT_LOOP
 /* Create an epoll file descriptor */
 assert((selfp->ep_fd = epoll_create1(0)) >= 0);

 /* Allocate space to hold epoll events */
 selfp->ep_events = z_memory_allocator_allocate(
 ctx->fixed_allocator,
 sizeof(struct epoll_event) * MAX_EVENTS);

 /* Create a pipe to send tasks into guest thread */
 int pipe_fds[2];
 assert(pipe(pipe_fds) == 0);

 selfp->pipe_out = pipe_fds[0];
 selfp->pipe_in = pipe_fds[1];

 /* Set file descriptors to non-blocking mode */
 set_fd_flags(selfp->pipe_in, O_NONBLOCK);
 set_fd_flags(selfp->pipe_out, O_NONBLOCK);

 /* Subscribe the output of the pipe to epoll */
 struct epoll_event event;
 event.data.ptr = NULL;
 event.events = EPOLLIN | EPOLLRDHUP | EPOLLPRI | EPOLLET;
 assert(epoll_ctl(selfp->ep_fd, EPOLL_CTL_ADD, selfp->pipe_out, &event) == 0);
#else
 selfp->pending_queue = NULL;
 selfp->incoming_queue = NULL;

 /* Initialize locks */
 pthread_mutex_init(&selfp->queue_lock, NULL);

 /* Initialize condition variables */
 pthread_cond_init(&selfp->schedule_cond, NULL);
#endif
 }
static void  z_event_loop_set_fd_flags(int fd,int flags)
{
 int old_flags = fcntl(fd, F_GETFL, 0);
 fcntl(fd, F_SETFL, old_flags | flags);
 }
static void  z_event_loop_delete_queue(Self *self,ZTask **queue)
{
 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->ts_fixed_allocator;
 ZTask *p = *queue;

 while (p) {
 ZTask *next = p->next;
 z_memory_allocator_deallocate_by_size(allocator, p, sizeof(ZTask));
 p = next;
 }

 *queue = NULL;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_event_loop_reset(ZObject *object)
{
 /* We never anticipate reusing a ZEventLoop object */
 abort();
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_event_loop_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 quit(self);
 z_object_unref(Z_OBJECT(selfp->quit_task));

 /* Wait for thread to complete */
 pthread_join(selfp->thread, NULL);
 selfp->is_done = 0;

#ifdef USE_IO_EVENT_LOOP
 close(selfp->pipe_in);
 close(selfp->pipe_out);
 close(selfp->ep_fd);
#else
 delete_queue(self, &selfp->incoming_queue);
 delete_queue(self, &selfp->pending_queue);

 pthread_mutex_destroy(&selfp->queue_lock);
#endif

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_event_loop_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
int  z_event_loop_get_is_current(Self *self)
{
 return pthread_equal(pthread_self(), selfp->thread);
 }
static int  z_event_loop_all_tasks_are_nowait(Self *self)
{
 /* The worst case time complexity of this function is O(n) because, in the
                   worst case, it will have to iterate through the entire map. The average
                   case is actually close to O(1) because the loop starts from the first
                   element in the map and iterates forward. It's very likely that the
                   application scheduled a NO_WAIT task far into the future and so it's
                   less likely that the lower elements in the map is marked with NO_WAIT.
                   This loop may very well exit with 1 iteration in most cases */

 ZMapIter *it, *end;
 it = z_map_get_begin(selfp->run_queue);
 end = z_map_get_end(selfp->run_queue);
 int value = 1;

 while (!z_map_iter_is_equal(it, end)) {
 ZTask *task = (ZTask *) z_map_get_value(selfp->run_queue, it);
 if (!task->no_wait) {
 value = 0; 
 break;
 }

 z_map_iter_increment(it);
 }

 z_object_unref(Z_OBJECT(end));
 z_object_unref(Z_OBJECT(it));

 return value;
 }
static void  z_event_loop_run_tasks(Self *self,ZMapIter *it,ZMapIter *end)
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 /* Iterate through the run queue and execute the tasks that
                   are scheduled to run now */
 while (!z_map_iter_is_equal(it, end)) {
 ZTask *task = (ZTask *) z_map_get_value(selfp->run_queue, it);

 if (task->has_request) {
 ZBind *request = z_bind_new(ctx, allocator);
 z_bind_set_data_ptr(request, &task->request);
 z_bind_invoke(request);
 z_object_unref(Z_OBJECT(request));
 }

 if (task->has_response) {
 ZBind *response_bind = z_bind_new(ctx, allocator);
 z_bind_set_data_ptr(response_bind, &task->response);

 /* TODO: This assertion needs to be handled gracefully */
 assert(zco_context_post_task(task->origin_context, response_bind, NULL, 0, 0) == 0);

 z_object_unref(Z_OBJECT(response_bind));
 }

 z_map_iter_increment(it);
 }
 }
static void  z_event_loop_reload_runqueue(Self *self)
{
#ifdef USE_IO_EVENT_LOOP
 ZTask *tasks[MAX_EVENTS];
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ssize_t nbytes;

 while(1) {
 nbytes = read(selfp->pipe_out, &tasks[0], sizeof(tasks));

 if (nbytes == -1) {
 if (errno == EAGAIN)
 break;

 perror("read");
 continue;
 }

 int i;
 int count = nbytes / sizeof(ZTask *);

 for (i=0; i<count; ++i) {
 ZTask *task = tasks[i];

#if __WORDSIZE >= 64
 /* For 64-bit systems, we store the time inforation inside the pointer value. This allows
                                   us to eliminate an allocation */

 while (z_map_insert(selfp->run_queue, INT_TO_PTR(task->timeout), task) == -1) {
 /* In the rare case when two tasks where scheduled to run at the same time,
                                           we delay one of the tasks by 1ns to ensure all keys in the map are unique */
 ++task->timeout;
 }
#else
 /* For 32-bit systems (or less), we allocate an 8-byte buffer to store the time information
                                   and stor ethe address to this buffer in the pointer value. */

 uint64_t *task_time = z_memory_allocator_allocate(ctx->fixed_allocator, sizeof(uint64_t));
 *task_time = task->timeout;

 while (z_map_insert(selfp->run_queue, task_time, task) == -1) {
 /* In the rare case when two tasks where scheduled to run at the same time,
                                           we delay one of the tasks by 1ns to ensure all keys in the map are unique */
 ++(*task_time);
 }
#endif
 }

 };
#else
 /* Move tasks from the pending queue into the run queue */
 ZTask *bind_data = selfp->pending_queue; 
 while (bind_data) {
#if __WORDSIZE >= 64
 /* For 64-bit systems, we store the time inforation inside the pointer value. This allows
                           us to eliminate an allocation */

 while (z_map_insert(selfp->run_queue, INT_TO_PTR(bind_data->timeout), bind_data) == -1) {
 /* In the rare case when two tasks where scheduled to run at the same time,
                                   we delay one of the tasks by 1ns to ensure all keys in the map are unique */
 ++bind_data->timeout;
 }
#else
 /* For 32-bit systems (or less), we allocate an 8-byte buffer to store the time information
                           and stor ethe address to this buffer in the pointer value. */

 uint64_t *task_time = z_memory_allocator_allocate(ctx->fixed_allocator, sizeof(uint64_t));
 *task_time = bind_data->timeout;

 while (z_map_insert(selfp->run_queue, task_time, bind_data) == -1) {
 /* In the rare case when two tasks where scheduled to run at the same time,
                                   we delay one of the tasks by 1ns to ensure all keys in the map are unique */
 ++(*task_time);
 }
#endif

 bind_data = bind_data->next;
 }
#endif
 }
static void  z_event_loop_get_ready_tasks(Self *self,ZMapIter **it,ZMapIter **end)
{
 uint64_t monotonic_time = get_monotonic_time();

 /* Compute the range of tasks that should be executed now */
 *it = z_map_get_begin(selfp->run_queue);

#if __WORDSIZE >= 64
 *end = z_map_upper_bound(selfp->run_queue, INT_TO_PTR(monotonic_time));
#else
 *end = z_map_upper_bound(selfp->run_queue, &monotonic_time);
#endif
 }
static void  z_event_loop_wait_for_signal(Self *self,struct timespec timeout)
{
#ifdef USE_IO_EVENT_LOOP
 int64_t timeout_ms = timeout.tv_sec * 1000 + timeout.tv_nsec / 1000000;

 /* A wait time of 0 ns indicates that there is no task that has a scheduled time
                   to run in the future. We set the timeout_ms = -1 so epoll_pwait waits indefinitely
                   until there is an event */
 if (timeout_ms == 0)
 timeout_ms = -1;

 /* epoll_pwait first calls sigprocmask to set the signal mask to the
                   specified 'sigmask', calls the standard epoll_wait() function and
                   then resets the signal mask with another call to sigprocmask, all
                   atomically. although we are not supposed to use sigprocmask in a
                   multi-threaded application, we can still get away with it as long
                   as we don't block the SIGCANCEL and SIGSETXID signals. */
 sigset_t sigmask;
 sigemptyset(&sigmask);
 selfp->ep_nfds = epoll_pwait(selfp->ep_fd, selfp->ep_events, MAX_EVENTS, (int) timeout_ms, &sigmask);

#else
 pthread_mutex_lock(&selfp->queue_lock);

 if (timeout.tv_sec == 0 && timeout.tv_nsec == 0)
 pthread_cond_wait(&selfp->schedule_cond, &selfp->queue_lock);
 else
 pthread_cond_timedwait(&selfp->schedule_cond, &selfp->queue_lock, &timeout);

 pthread_mutex_unlock(&selfp->queue_lock);
#endif
 }
static uint64_t  z_event_loop_get_next_task_time(Self *self)
{
 uint64_t next_task_time;

 /* Check the time of the next scheduled task in the run queue */
 ZMapIter *it = z_map_get_begin(selfp->run_queue);
#if __WORDSIZE >= 64
 next_task_time = PTR_TO_INT(z_map_get_key(selfp->run_queue, it));
#else
 next_task_time = *((uint64_t *) z_map_get_key(selfp->run_queue, it));
#endif
 z_object_unref(Z_OBJECT(it));

 return next_task_time;
 }
static void  z_event_loop_reload_pending_queue(Self *self)
{
#ifdef USE_IO_EVENT_LOOP
 /* No pending queues required for IO based event loop. */
 abort();
#else
 /* All tasks in the pending queue has been moved over to the run queue. Lets
                   swap the pending queue and incoming queue so we can execute newly added tasks
                   that exists in the incoming queue.

                   We should do this as late as possible so that the incoming queue has a better
                   chance of having some tasks */
 selfp->pending_queue = NULL;

 /* Hold the queue lock */
 pthread_mutex_lock(&selfp->queue_lock);

 /* Swap the pending queue and incoming queue */
 ZTask *temp = selfp->pending_queue;
 selfp->pending_queue = selfp->incoming_queue;
 selfp->incoming_queue = temp;

 pthread_mutex_unlock(&selfp->queue_lock);
#endif
 }
static void  z_event_loop_thread_main(Self *self)
{
 int is_running = 1;
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 while (is_running) {
 /* Reload new tasks into the run queue */
 reload_runqueue(self);

 /* Compute the range of tasks that should be executed now */
 ZMapIter *it, *end;
 get_ready_tasks(self, &it, &end);

 /* Run the tasks */
 run_tasks(self, it, end);

 /* Remove the tasks from the queue that have been executed */
 z_map_erase(selfp->run_queue, NULL, end);

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(end));

#ifndef USE_IO_EVENT_LOOP
 reload_pending_queue(self);

 if (selfp->pending_queue) {
 continue;
 }
#endif

 uint64_t next_task_time;

 if (z_map_get_is_empty(selfp->run_queue)) {
 /* If no tasks are scheduled to run, we don't know how long we should
                                   wait for a signal. We denote a non-timed wait with next_task_time=0 */
 next_task_time = 0;

 /* If the is_done flag is also set, we release the locks and exit the loop */
 if (selfp->is_done) {
 is_running = 0;
 continue;
 }

 } else if (selfp->is_done && all_tasks_are_nowait(self)) {
 /* Invoke all tasks in the queue */
 ZMapIter *it, *end;

 it = z_map_get_begin(selfp->run_queue);
 end = z_map_get_end(selfp->run_queue);

 run_tasks(self, it, end);

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(end));

 z_map_clear(selfp->run_queue);

 /* Release the locks and exit the loop */
 is_running = 0;
 continue;

 } else {
 next_task_time = get_next_task_time(self);
 }

 struct timespec timeout;

 if (next_task_time) {
 next_task_time = convert_monotonic_to_realtime(self, next_task_time);
 timeout.tv_sec = next_task_time / 1000000000ul;
 timeout.tv_nsec = next_task_time % 1000000000ul;
 } else {
 timeout.tv_sec = 0;
 timeout.tv_nsec = 0;
 }

 wait_for_signal(self, timeout);

#ifndef USE_IO_EVENT_LOOP
 reload_pending_queue(self);
#endif
 }

 selfp->is_running = 0;
 z_object_unref(Z_OBJECT(selfp->run_queue));

 pthread_exit(0);
 }
void  z_event_loop_run(Self *self)
{
 if (selfp->is_running)
 return;

 selfp->is_running = 1;
 memset(&selfp->thread, 0, sizeof(pthread_t));
 pthread_create(&selfp->thread, NULL, (void * (*)(void*)) &thread_main, self);

 if (selfp->name) {
 pthread_setname_np(selfp->thread, selfp->name);
 }
 }
char *  z_event_loop_get_name(Self *self)
{
 char *name = selfp->name;
 if (name)
 return strdup(name);
 else
 return NULL;
 }
void z_event_loop_set_name(Self *self, char *  value)
{
 if (selfp->name)
 free(selfp->name);

 selfp->name = value;
 }
static int  z_event_loop_is_active(Self *self)
{
 /* It's optimal to check the is_done flag over is_running. The is_running flag
                   can be modified by the thread_main() function so there is a greater chance
                   of a cache miss if we read from it */
 if (selfp->is_done || !selfp->is_running)
 return 0;

 return 1;
 }
static uint64_t  z_event_loop_convert_monotonic_to_realtime(Self *self,uint64_t monotonic)
{
 struct timespec realtime_tp;
 clock_gettime(CLOCK_REALTIME, &realtime_tp);
 uint64_t realtime_ns = ((uint64_t) realtime_tp.tv_sec) * 1000000000ul + realtime_tp.tv_nsec;

 uint64_t monotonic_ns = get_monotonic_time(); 

 return (uint64_t) ((int64_t) monotonic - (int64_t) monotonic_ns + (int64_t) realtime_ns);
 }
static uint64_t  z_event_loop_get_monotonic_time()
{
 struct timespec tp;
 clock_gettime(CLOCK_BOOTTIME, &tp);
 return ((uint64_t) tp.tv_sec) * 1000000000ul + tp.tv_nsec;
 }
static int  z_event_loop_add_to_task_queue(Self *self,ZTask *task)
{
#ifdef USE_IO_EVENT_LOOP
 /* Send the address of the task to the guest thread through the pipe */
 int rc = write(selfp->pipe_in, &task, sizeof(ZTask *));
 if (rc < 0)
 return -errno;

 return 0;
#else
 /* Hold the incoming_queue lock */
 assert(pthread_mutex_lock(&selfp->queue_lock) == 0);


 /* Prepend it into the incoming queue. We don't care
                   about the order of insertion into the incoming queue; The order of execution
                   is preserved because each task knows what time it should be executed. As
                   long as the tasks that are scheduled the earliest are executed first, the
                   order will be maintained */
 task->next = selfp->incoming_queue;
 selfp->incoming_queue = task;

 /* Send a signal that new work has been scheduled */
 assert(pthread_cond_signal(&selfp->schedule_cond) == 0);

 /* Release the incoming_queue lock */
 assert(pthread_mutex_unlock(&selfp->queue_lock) == 0);

 return 0;
#endif
 }
int  z_event_loop_post_task(Self *self,ZBind *request,ZBind *response,uint64_t timeout,int flags)
{
 if (!is_active(self))
 return -EPERM;

 /* Use the thread-safe allocator to allocate memory for the raw closure */
 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->ts_fixed_allocator;
 ZTask *task = z_memory_allocator_allocate(allocator, sizeof(ZTask));

 task->origin_context = CTX_FROM_OBJECT(request);

 if (request) {
 task->origin_context = CTX_FROM_OBJECT(request);
 task->has_request = 1;
 memcpy(&task->request, z_bind_get_data_ptr(request), sizeof(ZBindData));
 } else {
 task->origin_context = CTX_FROM_OBJECT(response);
 task->has_request = 0;
 }

 if (response) {
 task->has_response = 1;
 memcpy(&task->response, z_bind_get_data_ptr(response), sizeof(ZBindData));
 } else {
 task->has_response = 0;
 }

 task->no_wait = (flags & Z_EVENT_LOOP_NO_WAIT)? 1 : 0;

 /* Normalize the timeout with a monotonic clock - Instead of
                   it being the time between now and the time the task is
                   scheduled to run, it will become the time between a
                   monotonic time and the time the task is scheduled to run */
 task->timeout = timeout + get_monotonic_time();

 return add_to_task_queue(self, task);
 }
static void  z_event_loop_zco_context_do_quit(ZBind *bind,Self *self)
{
 selfp->is_done = 1;
 }
int  z_event_loop_quit(Self *self)
{
 if (!is_active(self))
 return -EPERM;

 /* Send a QUIT signal to the thread */
 return post_task(self, selfp->quit_task, NULL, 0, 0);
 }
void  z_event_loop_join(Self *self)
{
 pthread_join(selfp->thread, NULL);
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_event_loop_class_destroy(ZObjectGlobal *gbl)
{
	ZEventLoopGlobal *_global = (ZEventLoopGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_event_loop___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



