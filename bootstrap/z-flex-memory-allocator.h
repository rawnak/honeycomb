/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-flex-memory-allocator.h: Bootstrap file for z-flex-memory-allocator.zco
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

#ifndef _Z_FLEX_MEMORY_ALLOCATOR_H_
#define _Z_FLEX_MEMORY_ALLOCATOR_H_

#include <z-memory-allocator.h>
#include <z-object.h>

#include <zco-type.h>
#define Self ZFlexMemoryAllocator
#define Z_FLEX_MEMORY_ALLOCATOR(s) ((ZFlexMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_flex_memory_allocator_type_id]))


struct ZFlexMemoryAllocatorPrivate;
struct ZFlexMemoryAllocatorProtected;
struct ZFlexMemoryAllocatorGlobal;
struct ZFlexMemoryAllocatorClass;
struct ZFlexMemoryAllocator;

typedef struct ZFlexMemoryAllocatorPrivate ZFlexMemoryAllocatorPrivate;
typedef struct ZFlexMemoryAllocatorProtected ZFlexMemoryAllocatorProtected;
typedef struct ZFlexMemoryAllocatorGlobal ZFlexMemoryAllocatorGlobal;
typedef struct ZFlexMemoryAllocatorClass ZFlexMemoryAllocatorClass;
typedef struct ZFlexMemoryAllocator ZFlexMemoryAllocator;

struct ZFlexMemoryAllocatorPrivate {
};

struct ZFlexMemoryAllocatorProtected {
};

struct ZFlexMemoryAllocatorGlobal {
	struct ZCommonGlobal common;
	struct ZFlexMemoryAllocatorClass *_class;
	void  (*__parent_dispose)(ZObject *object);
	void *  (*__parent_allocate)(ZMemoryAllocator *allocator,int size);
	void *  (*__parent_allocate_aligned)(ZMemoryAllocator *allocator,int size,int alignment);
	int  (*__parent_try_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
	void *  (*__parent_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
	void  (*__parent_deallocate)(ZMemoryAllocator *allocator,void *block);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZFlexMemoryAllocatorClass {
	struct ZMemoryAllocatorClass parent_z_memory_allocator;
};

struct ZFlexMemoryAllocator {
	struct ZMemoryAllocator parent_z_memory_allocator;
	struct ZFlexMemoryAllocatorGlobal *_global;
	struct ZFlexMemoryAllocatorPrivate _priv;
	struct ZFlexMemoryAllocatorProtected _prot;
};
extern int z_flex_memory_allocator_type_id;
ZFlexMemoryAllocatorGlobal * z_flex_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_flex_memory_allocator_init(struct zco_context_t *ctx, ZFlexMemoryAllocator *self);
void __z_flex_memory_allocator_class_init(struct zco_context_t *ctx, ZFlexMemoryAllocatorClass *_class);
Self * z_flex_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);

#undef Self


#endif
