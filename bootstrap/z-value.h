/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-value.h: Bootstrap file for z-value.zco
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

#ifndef _Z_VALUE_H_
#define _Z_VALUE_H_
#line 20 "z-value.zco"

#include <z-object.h>
#include <stdint.h>

union ZValueDataType {
 uint8_t _boolean;
 int8_t _int8;
 int16_t _int16;
 int32_t _int32;
 int64_t _int64;
 uint8_t _uint8;
 uint16_t _uint16;
 uint32_t _uint32;
 uint64_t _uint64;
 float _real32;
 double _real64;
 ZObject * _object;
};


#include <zco-type.h>
#define Self ZValue
#define Z_VALUE(s) ((ZValue *) ((char *) (s) + GLOBAL_FROM_OBJECT(s)->common.vtable_off_list[z_value_type_id]))


struct ZValuePrivate;
struct ZValueProtected;
struct ZValueGlobal;
struct ZValueClass;
struct ZValue;

typedef struct ZValuePrivate ZValuePrivate;
typedef struct ZValueProtected ZValueProtected;
typedef struct ZValueGlobal ZValueGlobal;
typedef struct ZValueClass ZValueClass;
typedef struct ZValue ZValue;

struct ZValuePrivate {
#line 48 "z-value.zco"
	union ZValueDataType data;
#line 49 "z-value.zco"
	int tag;
};

struct ZValueProtected {
};

struct ZValueGlobal {
	struct ZCommonGlobal common;
	struct ZValueClass *_class;
#line 75 "z-value.zco"
	void  (*__parent_reset)(ZObject *object);
#line 87 "z-value.zco"
	void  (*__parent_dispose)(ZObject *object);
};

struct ZValueClass {
	struct ZObjectClass parent_z_object;
};

struct ZValue {
	struct ZObject parent_z_object;
	struct ZValueGlobal *_global;
	struct ZValuePrivate _priv;
	struct ZValueProtected _prot;
};
extern int z_value_type_id;
ZValueGlobal * z_value_get_type(struct zco_context_t *ctx);
void __z_value_init(struct zco_context_t *ctx, ZValue *self);
void __z_value_class_init(struct zco_context_t *ctx, ZValueClass *_class);
#line 56 "z-value.zco"
Self * z_value_new(struct zco_context_t *ctx);
#line 62 "z-value.zco"
Self * z_value_dup(ZValue *src);
#line 101 "z-value.zco"
int  z_value_get_is_object(Self *self);
#line 109 "z-value.zco"
ZObject *  z_value_get_as_object(Self *self);
#line 115 "z-value.zco"
void z_value_set_as_object(Self *self, ZObject *  value);
#line 130 "z-value.zco"
int  z_value_get_is_boolean(Self *self);
#line 138 "z-value.zco"
int  z_value_get_as_boolean(Self *self);
#line 143 "z-value.zco"
void z_value_set_as_boolean(Self *self, int  value);
#line 156 "z-value.zco"
int  z_value_get_is_int8(Self *self);
#line 164 "z-value.zco"
int8_t  z_value_get_as_int8(Self *self);
#line 169 "z-value.zco"
void z_value_set_as_int8(Self *self, int8_t  value);
#line 181 "z-value.zco"
int  z_value_get_is_int16(Self *self);
#line 189 "z-value.zco"
int16_t  z_value_get_as_int16(Self *self);
#line 194 "z-value.zco"
void z_value_set_as_int16(Self *self, int16_t  value);
#line 206 "z-value.zco"
int  z_value_get_is_int32(Self *self);
#line 214 "z-value.zco"
int32_t  z_value_get_as_int32(Self *self);
#line 219 "z-value.zco"
void z_value_set_as_int32(Self *self, int32_t  value);
#line 231 "z-value.zco"
int  z_value_get_is_int64(Self *self);
#line 239 "z-value.zco"
int64_t  z_value_get_as_int64(Self *self);
#line 244 "z-value.zco"
void z_value_set_as_int64(Self *self, int64_t  value);
#line 257 "z-value.zco"
int  z_value_get_is_uint8(Self *self);
#line 265 "z-value.zco"
uint8_t  z_value_get_as_uint8(Self *self);
#line 270 "z-value.zco"
void z_value_set_as_uint8(Self *self, uint8_t  value);
#line 282 "z-value.zco"
int  z_value_get_is_uint16(Self *self);
#line 290 "z-value.zco"
uint16_t  z_value_get_as_uint16(Self *self);
#line 295 "z-value.zco"
void z_value_set_as_uint16(Self *self, uint16_t  value);
#line 307 "z-value.zco"
int  z_value_get_is_uint32(Self *self);
#line 315 "z-value.zco"
uint32_t  z_value_get_as_uint32(Self *self);
#line 320 "z-value.zco"
void z_value_set_as_uint32(Self *self, uint32_t  value);
#line 332 "z-value.zco"
int  z_value_get_is_uint64(Self *self);
#line 340 "z-value.zco"
uint64_t  z_value_get_as_uint64(Self *self);
#line 345 "z-value.zco"
void z_value_set_as_uint64(Self *self, uint64_t  value);
#line 358 "z-value.zco"
int  z_value_get_is_real32(Self *self);
#line 366 "z-value.zco"
float  z_value_get_as_real32(Self *self);
#line 371 "z-value.zco"
void z_value_set_as_real32(Self *self, float  value);
#line 383 "z-value.zco"
int  z_value_get_is_real64(Self *self);
#line 391 "z-value.zco"
double  z_value_get_as_real64(Self *self);
#line 396 "z-value.zco"
void z_value_set_as_real64(Self *self, double  value);

#undef Self


#endif
