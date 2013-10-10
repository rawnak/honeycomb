/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-map-iter.h: Bootstrap file for z-map-iter.zco
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

#ifndef _Z_MAP_ITER_H_
#define _Z_MAP_ITER_H_

#include <z-object.h>

#include <zco-type.h>
#define Self ZMapIter
#define Z_MAP_ITER(s) ((ZMapIter *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_map_iter_type_id]))


struct ZMapIterPrivate;
struct ZMapIterProtected;
struct ZMapIterGlobal;
struct ZMapIterClass;
struct ZMapIter;

typedef struct ZMapIterPrivate ZMapIterPrivate;
typedef struct ZMapIterProtected ZMapIterProtected;
typedef struct ZMapIterGlobal ZMapIterGlobal;
typedef struct ZMapIterClass ZMapIterClass;
typedef struct ZMapIter ZMapIter;

struct ZMapIterPrivate {
	int index;
};

struct ZMapIterProtected {
};

struct ZMapIterGlobal {
	struct ZCommonGlobal common;
	struct ZMapIterClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZMapIterClass {
	struct ZObjectClass parent_z_object;
};

struct ZMapIter {
	struct ZObject parent_z_object;
	struct ZMapIterGlobal *_global;
	struct ZMapIterPrivate _priv;
	struct ZMapIterProtected _prot;
};
extern int z_map_iter_type_id;
ZMapIterGlobal * z_map_iter_get_type(struct zco_context_t *ctx);
void __z_map_iter_init(struct zco_context_t *ctx, ZMapIter *self);
void __z_map_iter_class_init(struct zco_context_t *ctx, ZMapIterClass *_class);
Self * z_map_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
Self * z_map_iter_dup(ZMapIter *src);
void  z_map_iter_assign(Self *self,ZMapIter *src);
int  z_map_iter_get_index(Self *self);
void z_map_iter_set_index(Self *self, int  value);
void  z_map_iter_advance(Self *self,int steps);
void  z_map_iter_increment(Self *self);
void  z_map_iter_decrement(Self *self);
int  z_map_iter_is_equal(Self *self,Self *other);
int  z_map_iter_is_lte(Self *self,Self *other);
int  z_map_iter_is_gte(Self *self,Self *other);

#undef Self


#endif
