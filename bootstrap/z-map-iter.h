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
#define Z_MAP_ITER(s) ((ZMapIter *) (s))


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
	int *vtable_off_list;
	int vtable_off_size;
	struct ZMapIterClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
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
Self * z_map_iter_new(struct zco_context_t *ctx);
Self * z_map_iter_dup(ZMapIter *src);
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
