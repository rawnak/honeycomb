/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-slab-memory-allocator.h: Bootstrap file for z-slab-memory-allocator.zco
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

#ifndef _Z_SLAB_MEMORY_ALLOCATOR_H_
#define _Z_SLAB_MEMORY_ALLOCATOR_H_

#include <z-memory-allocator.h>
#include <z-object.h>

#include <zco-type.h>
#define Self ZSlabMemoryAllocator
#define Z_SLAB_MEMORY_ALLOCATOR(s) ((ZSlabMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_slab_memory_allocator_type_id]))


struct ZSlabMemoryAllocatorPrivate;
struct ZSlabMemoryAllocatorProtected;
struct ZSlabMemoryAllocatorGlobal;
struct ZSlabMemoryAllocatorClass;
struct ZSlabMemoryAllocator;

typedef struct ZSlabMemoryAllocatorPrivate ZSlabMemoryAllocatorPrivate;
typedef struct ZSlabMemoryAllocatorProtected ZSlabMemoryAllocatorProtected;
typedef struct ZSlabMemoryAllocatorGlobal ZSlabMemoryAllocatorGlobal;
typedef struct ZSlabMemoryAllocatorClass ZSlabMemoryAllocatorClass;
typedef struct ZSlabMemoryAllocator ZSlabMemoryAllocator;

struct ZSlabMemoryAllocatorPrivate {
};

struct ZSlabMemoryAllocatorProtected {
};

struct ZSlabMemoryAllocatorGlobal {
	struct ZCommonGlobal common;
	struct ZSlabMemoryAllocatorClass *_class;
	void  (*__parent_dispose)(ZObject *object);
	void *  (*__parent_allocate)(ZMemoryAllocator *allocator,int size);
	void *  (*__parent_allocate_aligned)(ZMemoryAllocator *allocator,int size,int alignment);
	int  (*__parent_try_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
	void *  (*__parent_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
	void  (*__parent_deallocate)(ZMemoryAllocator *allocator,void *block);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZSlabMemoryAllocatorClass {
	struct ZMemoryAllocatorClass parent_z_memory_allocator;
};

struct ZSlabMemoryAllocator {
	struct ZMemoryAllocator parent_z_memory_allocator;
	struct ZSlabMemoryAllocatorGlobal *_global;
	struct ZSlabMemoryAllocatorPrivate _priv;
	struct ZSlabMemoryAllocatorProtected _prot;
};
extern int z_slab_memory_allocator_type_id;
ZSlabMemoryAllocatorGlobal * z_slab_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_slab_memory_allocator_init(struct zco_context_t *ctx, ZSlabMemoryAllocator *self);
void __z_slab_memory_allocator_class_init(struct zco_context_t *ctx, ZSlabMemoryAllocatorClass *_class);
Self * z_slab_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);

#undef Self


#endif
