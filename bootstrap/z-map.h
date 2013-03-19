/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-map.h: Bootstrap file for z-map.zco
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

#ifndef _Z_MAP_H_
#define _Z_MAP_H_

#include <stdint.h>
#include <z-object.h>
#include <z-vector.h>
#include <z-map-iter.h>

struct ZMap;
typedef int(*ZMapCompareFunc)(struct ZMap *, const void *, const void *);
typedef void(*ZMapItemCallback)(void *item, void *userdata);


#include <zco-type.h>
#define Self ZMap
#define Z_MAP(s) ((ZMap *) ((char *) (s) + GLOBAL_FROM_OBJECT(s)->common.vtable_off_list[z_map_type_id]))


struct ZMapPrivate;
struct ZMapProtected;
struct ZMapGlobal;
struct ZMapClass;
struct ZMap;

typedef struct ZMapPrivate ZMapPrivate;
typedef struct ZMapProtected ZMapProtected;
typedef struct ZMapGlobal ZMapGlobal;
typedef struct ZMapClass ZMapClass;
typedef struct ZMap ZMap;

struct ZMapPrivate {
	ZVector *data;
	ZMapCompareFunc compare;
	ZMapItemCallback key_destruct;
	ZMapItemCallback value_destruct;
	void *userdata;
};

struct ZMapProtected {
};

struct ZMapGlobal {
	struct ZCommonGlobal common;
	struct ZMapClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
};

struct ZMapClass {
	struct ZObjectClass parent_z_object;
};

struct ZMap {
	struct ZObject parent_z_object;
	struct ZMapGlobal *_global;
	struct ZMapPrivate _priv;
	struct ZMapProtected _prot;
};
extern int z_map_type_id;
ZMapGlobal * z_map_get_type(struct zco_context_t *ctx);
void __z_map_init(struct zco_context_t *ctx, ZMap *self);
void __z_map_class_init(struct zco_context_t *ctx, ZMapClass *_class);
Self * z_map_new(struct zco_context_t *ctx);
void z_map_set_userdata(Self *self, void *  value);
void z_map_set_key_destruct(Self *self, ZMapItemCallback  value);
void z_map_set_value_destruct(Self *self, ZMapItemCallback  value);
ZMapIter * z_map_get_begin(Self *self);
ZMapIter * z_map_get_end(Self *self);
int  z_map_get_is_empty(Self *self);
int  z_map_get_size(Self *self);
void  z_map_clear(Self *self);
ZMapIter * z_map_find(Self *self,const void *key);
void * z_map_get_key(Self *self,ZMapIter *it);
void * z_map_get_value(Self *self,ZMapIter *it);
void  z_map_set_value(Self *self,ZMapIter *it,void *value);
int  z_map_assign(Self *self,void *key,void *value);
int  z_map_insert(Self *self,void *key,void *value);
void  z_map_erase(Self *self,ZMapIter *first,ZMapIter *last);
void  z_map_erase1(Self *self,ZMapIter *it);
void  z_map_erase1_inc(Self *self,ZMapIter **it);
ZMapIter * z_map_lower_bound(Self *self,void *key);
ZMapIter * z_map_upper_bound(Self *self,void *key);
void z_map_set_compare(Self *self, ZMapCompareFunc  value);

#undef Self


#endif
