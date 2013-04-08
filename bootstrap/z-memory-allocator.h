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
#line 4 "z-memory-allocator.zco"

#include <z-object.h>
#include <z-object-tracker.h>

#include <zco-type.h>
#define Self ZMemoryAllocator
#define Z_MEMORY_ALLOCATOR(s) ((ZMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_memory_allocator_type_id]))


struct ZMemoryAllocatorPrivate;
struct ZMemoryAllocatorProtected;
struct ZMemoryAllocatorGlobal;
struct ZMemoryAllocatorClass;
struct ZMemoryAllocator;

typedef struct ZMemoryAllocatorPrivate ZMemoryAllocatorPrivate;
typedef struct ZMemoryAllocatorProtected ZMemoryAllocatorProtected;
typedef struct ZMemoryAllocatorGlobal ZMemoryAllocatorGlobal;
typedef struct ZMemoryAllocatorClass ZMemoryAllocatorClass;
typedef struct ZMemoryAllocator ZMemoryAllocator;

struct ZMemoryAllocatorPrivate {
#line 11 "z-memory-allocator.zco"
	ZObjectTracker *object_tracker;
};

struct ZMemoryAllocatorProtected {
};

struct ZMemoryAllocatorGlobal {
	struct ZCommonGlobal common;
	struct ZMemoryAllocatorClass *_class;
#line 46 "z-memory-allocator.zco"
	void  (*__parent_dispose)(ZObject *object);
#line 53 "z-memory-allocator.zco"
	void  (*__parent_reset)(ZObject *object);
#line 84 "z-memory-allocator.zco"
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZMemoryAllocatorClass {
	struct ZObjectClass parent_z_object;
#line 60 "z-memory-allocator.zco"
	void *  (*__allocate)(Self *self,int size);
#line 65 "z-memory-allocator.zco"
	void *  (*__allocate_aligned)(Self *self,int size,int alignment);
#line 70 "z-memory-allocator.zco"
	int  (*__try_resize)(Self *self,void *block,int new_size);
#line 75 "z-memory-allocator.zco"
	void *  (*__resize)(Self *self,void *block,int new_size);
#line 80 "z-memory-allocator.zco"
	void  (*__deallocate)(Self *self,void *block);
};

struct ZMemoryAllocator {
	struct ZObject parent_z_object;
	struct ZMemoryAllocatorGlobal *_global;
	struct ZMemoryAllocatorPrivate _priv;
	struct ZMemoryAllocatorProtected _prot;
};
extern int z_memory_allocator_type_id;
ZMemoryAllocatorGlobal * z_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_memory_allocator_init(struct zco_context_t *ctx, ZMemoryAllocator *self);
void __z_memory_allocator_class_init(struct zco_context_t *ctx, ZMemoryAllocatorClass *_class);
#line 20 "z-memory-allocator.zco"
ZObjectTracker * z_memory_allocator_get_object_tracker(Self *self);
#line 25 "z-memory-allocator.zco"
void z_memory_allocator_set_object_tracker(Self *self, ZObjectTracker * value);
#line 60 "z-memory-allocator.zco"
void *  z_memory_allocator_allocate(Self *self,int size);
#line 65 "z-memory-allocator.zco"
void *  z_memory_allocator_allocate_aligned(Self *self,int size,int alignment);
#line 70 "z-memory-allocator.zco"
int  z_memory_allocator_try_resize(Self *self,void *block,int new_size);
#line 75 "z-memory-allocator.zco"
void *  z_memory_allocator_resize(Self *self,void *block,int new_size);
#line 80 "z-memory-allocator.zco"
void  z_memory_allocator_deallocate(Self *self,void *block);

#undef Self


#endif
