/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-sys-memory-allocator.h: Bootstrap file for z-sys-memory-allocator.zco
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

#ifndef _Z_SYS_MEMORY_ALLOCATOR_H_
#define _Z_SYS_MEMORY_ALLOCATOR_H_

#include <z-memory-allocator.h>
#include <z-object.h>

#include <zco-context.h>
#define Self ZSysMemoryAllocator
#define Z_SYS_MEMORY_ALLOCATOR(s) ((ZSysMemoryAllocator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_sys_memory_allocator_type_id]))


ZCO_TYPEDEF_FWD_DECL_CLASS(ZSysMemoryAllocator);

struct ZSysMemoryAllocatorPrivate {
};

struct ZSysMemoryAllocatorProtected {
};

struct ZSysMemoryAllocatorGlobal {
	ZCO_CLASS_GLOBAL_HEAD(ZSysMemoryAllocator);
	void  (*__parent_dispose)(ZObject *object);
	void *  (*__parent_allocate)(ZMemoryAllocator *allocator,int size);
	void *  (*__parent_allocate_aligned)(ZMemoryAllocator *allocator,int size,int alignment);
	int  (*__parent_get_usable_size)(ZMemoryAllocator *allocator,void *block);
	void *  (*__parent_resize)(ZMemoryAllocator *allocator,void *block,int new_size);
	void  (*__parent_deallocate)(ZMemoryAllocator *allocator,void *block);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZSysMemoryAllocatorClass {
	struct ZMemoryAllocatorClass parent_z_memory_allocator;
};

struct ZSysMemoryAllocator {
	struct ZMemoryAllocator parent_z_memory_allocator;
	ZCO_CLASS_PUBLIC_HEAD(ZSysMemoryAllocator);
};
extern int z_sys_memory_allocator_type_id;
ZSysMemoryAllocatorGlobal * z_sys_memory_allocator_get_type(struct zco_context_t *ctx);
void __z_sys_memory_allocator_init(struct zco_context_t *ctx, ZSysMemoryAllocator *self);
void __z_sys_memory_allocator_class_init(struct zco_context_t *ctx, ZSysMemoryAllocatorClass *_class);
Self * z_sys_memory_allocator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);

#undef Self


#endif
