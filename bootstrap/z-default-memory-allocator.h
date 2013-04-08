/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-default-memory-allocator.h: Bootstrap file for z-default-memory-allocator.zco
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

#ifndef _Z_DEFAULT_MEMORY_ALLOCATOR_H_
#define _Z_DEFAULT_MEMORY_ALLOCATOR_H_
#line 4 "z-default-memory-allocator.zco"

#include <z-memory-allocator.h>
#include <z-object.h>

#include <zco-type.h>
#define Self ZDefaultMemoryAllocator
#define Z_DEFAULT_MEMORY_ALLOCATOR(s) ((ZDefaultMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_default_memory_allocator_type_id]))


struct ZDefaultMemoryAllocatorPrivate;
struct ZDefaultMemoryAllocatorProtected;
struct ZDefaultMemoryAllocatorGlobal;
struct ZDefaultMemoryAllocatorClass;
struct ZDefaultMemoryAllocator;

typedef struct ZDefaultMemoryAllocatorPrivate ZDefaultMemoryAllocatorPrivate;
typedef struct ZDefaultMemoryAllocatorProtected ZDefaultMemoryAllocatorProtected;
typedef struct ZDefaultMemoryAllocatorGlobal ZDefaultMemoryAllocatorGlobal;
typedef struct ZDefaultMemoryAllocatorClass ZDefaultMemoryAllocatorClass;
typedef struct ZDefaultMemoryAllocator ZDefaultMemoryAllocator;

struct ZDefaultMemoryAllocatorPrivate {
};

struct ZDefaultMemoryAllocatorProtected {
};

struct ZDefaultMemoryAllocatorGlobal {
	struct ZCommonGlobal common;
	struct ZDefaultMemoryAllocatorClass *_class;
#line 24 "z-default-memory-allocator.zco"
	void  (*__parent_dispose)(ZObject *object);
#line 31 "z-default-memory-allocator.zco"
	void *  (*__parent_allocate)(ZMemoryAllocator *allocator,int size);
#line 37 "z-default-memory-allocator.zco"
	void *  (*__parent_allocate_aligned)(ZMemoryAllocator *allocator,int size,int alignment);
#line 43 "z-default-memory-allocator.zco"
	int  (*__parent_try_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
#line 49 "z-default-memory-allocator.zco"
	void *  (*__parent_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
#line 55 "z-default-memory-allocator.zco"
	void  (*__parent_deallocate)(ZMemoryAllocator *allocator,void *block);
#line 59 "z-default-memory-allocator.zco"
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZDefaultMemoryAllocatorClass {
	struct ZMemoryAllocatorClass parent_z_memory_allocator;
};

struct ZDefaultMemoryAllocator {
	struct ZMemoryAllocator parent_z_memory_allocator;
	struct ZDefaultMemoryAllocatorGlobal *_global;
	struct ZDefaultMemoryAllocatorPrivate _priv;
	struct ZDefaultMemoryAllocatorProtected _prot;
};
extern int z_default_memory_allocator_type_id;
ZDefaultMemoryAllocatorGlobal * z_default_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_default_memory_allocator_init(struct zco_context_t *ctx, ZDefaultMemoryAllocator *self);
void __z_default_memory_allocator_class_init(struct zco_context_t *ctx, ZDefaultMemoryAllocatorClass *_class);
#line 17 "z-default-memory-allocator.zco"
Self * z_default_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);

#undef Self


#endif
