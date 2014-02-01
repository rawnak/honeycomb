/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-memory-allocator.h: Bootstrap file for z-memory-allocator.zco
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

#ifndef _Z_MEMORY_ALLOCATOR_H_
#define _Z_MEMORY_ALLOCATOR_H_

#include <z-object.h>
#include <z-object-tracker.h>
#include <assert.h>

#include <zco-context.h>
#define Self ZMemoryAllocator
#define Z_MEMORY_ALLOCATOR(s) ((ZMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_memory_allocator_type_id]))


ZCO_TYPEDEF_FWD_DECL_CLASS(ZMemoryAllocator);

struct ZMemoryAllocatorPrivate {
	ZObjectTracker *object_tracker;
};

struct ZMemoryAllocatorProtected {
};

struct ZMemoryAllocatorGlobal {
	ZCO_CLASS_GLOBAL_HEAD(ZMemoryAllocator);
	void  (*__parent_dispose)(ZObject *object);
	void  (*__parent_reset)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZMemoryAllocatorClass {
	struct ZObjectClass parent_z_object;
	void *  (*__allocate)(Self *self,int size);
	void *  (*__allocate_aligned)(Self *self,int size,int alignment);
	int  (*__get_usable_size)(Self *self,void *block);
	void *  (*__resize)(Self *self,void *block,int new_size);
	void  (*__deallocate)(Self *self,void *block);
	void  (*__deallocate_by_size)(Self *self,void *block,int size);
	int  (*__garbage_collect)(Self *self);
};

struct ZMemoryAllocator {
	struct ZObject parent_z_object;
	ZCO_CLASS_PUBLIC_HEAD(ZMemoryAllocator);
};
extern int z_memory_allocator_type_id;
ZMemoryAllocatorGlobal * z_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_memory_allocator_init(struct zco_context_t *ctx, ZMemoryAllocator *self);
void __z_memory_allocator_class_init(struct zco_context_t *ctx, ZMemoryAllocatorClass *_class);
ZObjectTracker * z_memory_allocator_get_object_tracker(Self *self);
void z_memory_allocator_set_object_tracker(Self *self, ZObjectTracker * value);
void *  z_memory_allocator_allocate(Self *self,int size);
void *  z_memory_allocator_allocate_aligned(Self *self,int size,int alignment);
int  z_memory_allocator_get_usable_size(Self *self,void *block);
void *  z_memory_allocator_resize(Self *self,void *block,int new_size);
void  z_memory_allocator_deallocate(Self *self,void *block);
void  z_memory_allocator_deallocate_by_size(Self *self,void *block,int size);
int  z_memory_allocator_garbage_collect(Self *self);

#undef Self


#endif
