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
#line 11 "z-map.zco"

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
#line 25 "z-map.zco"
	ZVector *data;
#line 26 "z-map.zco"
	ZMapCompareFunc compare;
#line 27 "z-map.zco"
	ZMapItemCallback key_destruct;
#line 28 "z-map.zco"
	ZMapItemCallback value_destruct;
#line 29 "z-map.zco"
	void *userdata;
};

struct ZMapProtected {
};

struct ZMapGlobal {
	struct ZCommonGlobal common;
	struct ZMapClass *_class;
#line 45 "z-map.zco"
	void  (*__parent_reset)(ZObject *object);
#line 67 "z-map.zco"
	void  (*__parent_dispose)(ZObject *object);
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
#line 76 "z-map.zco"
Self * z_map_new(struct zco_context_t *ctx);
#line 84 "z-map.zco"
void z_map_set_userdata(Self *self, void *  value);
#line 92 "z-map.zco"
void z_map_set_key_destruct(Self *self, ZMapItemCallback  value);
#line 100 "z-map.zco"
void z_map_set_value_destruct(Self *self, ZMapItemCallback  value);
#line 108 "z-map.zco"
ZMapIter * z_map_get_begin(Self *self);
#line 122 "z-map.zco"
ZMapIter * z_map_get_end(Self *self);
#line 136 "z-map.zco"
int  z_map_get_is_empty(Self *self);
#line 144 "z-map.zco"
int  z_map_get_size(Self *self);
#line 150 "z-map.zco"
void  z_map_clear(Self *self);
#line 268 "z-map.zco"
ZMapIter * z_map_find(Self *self,const void *key);
#line 309 "z-map.zco"
void * z_map_get_key(Self *self,ZMapIter *it);
#line 320 "z-map.zco"
void * z_map_get_value(Self *self,ZMapIter *it);
#line 331 "z-map.zco"
void  z_map_set_value(Self *self,ZMapIter *it,void *value);
#line 419 "z-map.zco"
int  z_map_assign(Self *self,void *key,void *value);
#line 424 "z-map.zco"
int  z_map_insert(Self *self,void *key,void *value);
#line 429 "z-map.zco"
void  z_map_erase(Self *self,ZMapIter *first,ZMapIter *last);
#line 459 "z-map.zco"
void  z_map_erase1(Self *self,ZMapIter *it);
#line 469 "z-map.zco"
void  z_map_erase1_inc(Self *self,ZMapIter **it);
#line 489 "z-map.zco"
ZMapIter * z_map_lower_bound(Self *self,void *key);
#line 507 "z-map.zco"
ZMapIter * z_map_upper_bound(Self *self,void *key);
#line 545 "z-map.zco"
void z_map_set_compare(Self *self, ZMapCompareFunc  value);

#undef Self


#endif
