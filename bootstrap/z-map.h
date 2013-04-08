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
#define Z_MAP(s) ((ZMap *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_map_type_id]))


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
#line 68 "z-map.zco"
	void  (*__parent_dispose)(ZObject *object);
#line 553 "z-map.zco"
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
#line 83 "z-map.zco"
Self * z_map_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
#line 91 "z-map.zco"
void z_map_set_userdata(Self *self, void *  value);
#line 99 "z-map.zco"
void z_map_set_key_destruct(Self *self, ZMapItemCallback  value);
#line 107 "z-map.zco"
void z_map_set_value_destruct(Self *self, ZMapItemCallback  value);
#line 115 "z-map.zco"
ZMapIter * z_map_get_begin(Self *self);
#line 129 "z-map.zco"
ZMapIter * z_map_get_end(Self *self);
#line 143 "z-map.zco"
int  z_map_get_is_empty(Self *self);
#line 151 "z-map.zco"
int  z_map_get_size(Self *self);
#line 157 "z-map.zco"
void  z_map_clear(Self *self);
#line 275 "z-map.zco"
ZMapIter * z_map_find(Self *self,const void *key);
#line 316 "z-map.zco"
void * z_map_get_key(Self *self,ZMapIter *it);
#line 327 "z-map.zco"
void * z_map_get_value(Self *self,ZMapIter *it);
#line 338 "z-map.zco"
void  z_map_set_value(Self *self,ZMapIter *it,void *value);
#line 422 "z-map.zco"
int  z_map_assign(Self *self,void *key,void *value);
#line 427 "z-map.zco"
int  z_map_insert(Self *self,void *key,void *value);
#line 432 "z-map.zco"
void  z_map_erase(Self *self,ZMapIter *first,ZMapIter *last);
#line 462 "z-map.zco"
void  z_map_erase1(Self *self,ZMapIter *it);
#line 472 "z-map.zco"
void  z_map_erase1_inc(Self *self,ZMapIter **it);
#line 492 "z-map.zco"
ZMapIter * z_map_lower_bound(Self *self,void *key);
#line 510 "z-map.zco"
ZMapIter * z_map_upper_bound(Self *self,void *key);
#line 548 "z-map.zco"
void z_map_set_compare(Self *self, ZMapCompareFunc  value);

#undef Self


#endif
