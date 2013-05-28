/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-thread-simple-memory-allocator.h: Bootstrap file for z-thread-simple-memory-allocator.zco
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

#ifndef _Z_THREAD_SIMPLE_MEMORY_ALLOCATOR_H_
#define _Z_THREAD_SIMPLE_MEMORY_ALLOCATOR_H_

#include <z-memory-allocator.h>
#include <z-object.h>
#include <malloc.h>

#include <zco-type.h>
#define Self ZThreadSimpleMemoryAllocator
#define Z_THREAD_SIMPLE_MEMORY_ALLOCATOR(s) ((ZThreadSimpleMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_thread_simple_memory_allocator_type_id]))


struct ZThreadSimpleMemoryAllocatorPrivate;
struct ZThreadSimpleMemoryAllocatorProtected;
struct ZThreadSimpleMemoryAllocatorGlobal;
struct ZThreadSimpleMemoryAllocatorClass;
struct ZThreadSimpleMemoryAllocator;

typedef struct ZThreadSimpleMemoryAllocatorPrivate ZThreadSimpleMemoryAllocatorPrivate;
typedef struct ZThreadSimpleMemoryAllocatorProtected ZThreadSimpleMemoryAllocatorProtected;
typedef struct ZThreadSimpleMemoryAllocatorGlobal ZThreadSimpleMemoryAllocatorGlobal;
typedef struct ZThreadSimpleMemoryAllocatorClass ZThreadSimpleMemoryAllocatorClass;
typedef struct ZThreadSimpleMemoryAllocator ZThreadSimpleMemoryAllocator;

struct ZThreadSimpleMemoryAllocatorPrivate {
	pthread_mutex_t lock;
	void *bins;
	int nbins;
};

struct ZThreadSimpleMemoryAllocatorProtected {
};

struct ZThreadSimpleMemoryAllocatorGlobal {
	struct ZCommonGlobal common;
	struct ZThreadSimpleMemoryAllocatorClass *_class;
	void  (*__parent_dispose)(ZObject *object);
	void *  (*__parent_allocate)(ZMemoryAllocator *allocator,int size);
	void *  (*__parent_allocate_aligned)(ZMemoryAllocator *allocator,int size,int alignment);
	int  (*__parent_get_usable_size)(ZMemoryAllocator *allocator,void *block);
	void *  (*__parent_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
	void  (*__parent_deallocate_by_size)(ZMemoryAllocator *allocator,void *block,int size);
	int  (*__parent_garbage_collect)(ZMemoryAllocator *allocator);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZThreadSimpleMemoryAllocatorClass {
	struct ZMemoryAllocatorClass parent_z_memory_allocator;
};

struct ZThreadSimpleMemoryAllocator {
	struct ZMemoryAllocator parent_z_memory_allocator;
	struct ZThreadSimpleMemoryAllocatorGlobal *_global;
	struct ZThreadSimpleMemoryAllocatorPrivate _priv;
	struct ZThreadSimpleMemoryAllocatorProtected _prot;
};
extern int z_thread_simple_memory_allocator_type_id;
ZThreadSimpleMemoryAllocatorGlobal * z_thread_simple_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_thread_simple_memory_allocator_init(struct zco_context_t *ctx, ZThreadSimpleMemoryAllocator *self);
void __z_thread_simple_memory_allocator_class_init(struct zco_context_t *ctx, ZThreadSimpleMemoryAllocatorClass *_class);
Self * z_thread_simple_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);

#undef Self


#endif
