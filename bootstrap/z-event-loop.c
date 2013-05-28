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


#include <z-value.h>
#include <stdint.h>
#include <assert.h>
 
#include <stdio.h>

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
#define INIT_EXISTS
#define init z_event_loop_init
#define delete_queue z_event_loop_delete_queue
#define new z_event_loop_new
#define get_is_current z_event_loop_get_is_current
#define swap_queues z_event_loop_swap_queues
#define thread_main z_event_loop_thread_main
#define run z_event_loop_run
#define is_active z_event_loop_is_active
#define post_task z_event_loop_post_task
#define zco_context_do_quit z_event_loop_zco_context_do_quit
#define quit z_event_loop_quit

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
static void z_event_loop_init(Self *self);
static void  z_event_loop_delete_queue(Self *self,ZBindData *queue);
static void  z_event_loop_reset(ZObject *object);
static void  z_event_loop_dispose(ZObject *object);
static void  z_event_loop_swap_queues(Self *self);
static void  z_event_loop_thread_main(Self *self);
static int  z_event_loop_is_active(Self *self);
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
static void z_event_loop_init(Self *self)
{
 selfp->is_done = 0;
 selfp->is_running = 0;

 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 /* Create a bind closure for the quit task */
 selfp->quit_task = z_bind_new(ctx, allocator);
 z_bind_set_handler(selfp->quit_task, (ZBindHandler) zco_context_do_quit);
 z_bind_append_ptr(selfp->quit_task, self);

 /* Initialize task queues */
 selfp->read_queue = NULL;
 selfp->write_queue = NULL;

 /* Initialize locks */
 pthread_mutex_init(&selfp->read_queue_lock, NULL);
 pthread_mutex_init(&selfp->write_queue_lock, NULL);

 /* Initialize condition variables */
 pthread_cond_init(&selfp->schedule_cond, NULL);
 }
static void  z_event_loop_delete_queue(Self *self,ZBindData *queue)
{
 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->ts_fixed_allocator;

 while (queue) {
 ZBindData *next = queue->next;
 z_memory_allocator_deallocate_by_size(allocator, queue, sizeof(ZBindData));
 queue = next;
 }
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_event_loop_reset(ZObject *object)
{
 Self *self = (Self *) object;
 quit(self);

 /* Wait for thread to complete */
 pthread_join(selfp->thread, NULL);
 selfp->is_done = 0;

 delete_queue(self, selfp->write_queue);
 delete_queue(self, selfp->read_queue);

 selfp->write_queue = NULL;
 selfp->read_queue = NULL;

 PARENT_HANDLER(object);
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

 delete_queue(self, selfp->write_queue);
 delete_queue(self, selfp->read_queue);

 selfp->write_queue = NULL;
 selfp->read_queue = NULL;

 pthread_mutex_destroy(&selfp->write_queue_lock);
 pthread_mutex_destroy(&selfp->read_queue_lock);

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
static void  z_event_loop_swap_queues(Self *self)
{
 /* Swap the read_queue and write_queue */
 pthread_mutex_lock(&selfp->read_queue_lock);
 pthread_mutex_lock(&selfp->write_queue_lock);

 ZBindData *temp = selfp->read_queue;
 selfp->read_queue = selfp->write_queue;
 selfp->write_queue = temp;

 pthread_mutex_unlock(&selfp->write_queue_lock);
 pthread_mutex_unlock(&selfp->read_queue_lock);
 }
static void  z_event_loop_thread_main(Self *self)
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);
 ZMemoryAllocator *data_allocator = ctx->ts_fixed_allocator;

 while (1) {
 /* Execute all tasks in the read_queue. The read_queue is not touched
                           by the post_task operation so we needn't hold onto a lock to access it */
 ZBindData *queue = selfp->read_queue;
 selfp->read_queue = NULL;

 while (queue) {
 ZBindData *next = queue->next;

 /* Create a new bind object under the worker context and set it to point
                                   to the data that was copied in post_task(). */
 ZBind *task = z_bind_new(ctx, allocator);
 z_bind_set_data_ptr(task, queue);
 
 /* Execute the task */
 z_bind_invoke(task);

 /* Release the closure data and the task object */
 z_memory_allocator_deallocate_by_size(data_allocator, queue, sizeof(ZBindData));
 z_object_unref(Z_OBJECT(task));

 queue = next;
 }

 /* All tasks in the read_queue has been executed. Lets swap the read_queue
                           and write_queue so we can execute newly added tasks that exists in the
                           write_queue. */
 swap_queues(self);

 /* If the new read_queue is not empty, repeat the loop and run all tasks
                           in the queue */
 if (selfp->read_queue)
 continue;

 /* If the new read_queue is empty and the is_done flag is set, we exit
                           the loop */
 if (selfp->is_done)
 break;

 /* Wait for a schedule work signal */
 pthread_mutex_lock(&selfp->write_queue_lock);

 if (!selfp->write_queue)
 pthread_cond_wait(&selfp->schedule_cond, &selfp->write_queue_lock);

 pthread_mutex_unlock(&selfp->write_queue_lock);

 /* New tasks have been added to the write_queue. Lets swap the read_queue
                           and write_queue so we can execute the tasks in the read_queue */
 swap_queues(self);
 }

 selfp->is_running = 0;
 pthread_exit(0);
 }
void  z_event_loop_run(Self *self)
{
 if (selfp->is_running)
 return;

 selfp->is_running = 1;
 memset(&selfp->thread, 0, sizeof(pthread_t));
 pthread_create(&selfp->thread, NULL, (void * (*)(void*)) &thread_main, self);
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
void  z_event_loop_post_task(Self *self,ZBind *bind,uint64_t ns)
{
 if (!is_active(self))
 return;

 /* Use the thread-safe allocator to allocate memory for the raw closure */
 ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->ts_fixed_allocator;
 ZBindData *data = z_memory_allocator_allocate(allocator, sizeof(ZBindData));

 /* Hold the write_queue lock */
 pthread_mutex_lock(&selfp->write_queue_lock);

 /* Get the closure data and insert it into the write queue */
 z_bind_get_data(bind, data);
 data->next = selfp->write_queue;
 selfp->write_queue = data;

 /* Send a signal that new work has been scheduled */
 pthread_cond_signal(&selfp->schedule_cond);

 /* Release the write_queue lock */
 pthread_mutex_unlock(&selfp->write_queue_lock);
 }
static void  z_event_loop_zco_context_do_quit(ZBind *bind,Self *self)
{
 selfp->is_done = 1;
 }
void  z_event_loop_quit(Self *self)
{
 if (!is_active(self))
 return;

 /* Send a QUIT signal to the thread */
 post_task(self, selfp->quit_task, 0);
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_event_loop_class_destroy(ZObjectGlobal *gbl)
{
	ZEventLoopGlobal *_global = (ZEventLoopGlobal *) gbl;

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



