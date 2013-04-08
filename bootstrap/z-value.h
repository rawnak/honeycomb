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
#define Z_VALUE(s) ((ZValue *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_value_type_id]))


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
	union ZValueDataType data;
	int tag;
};

struct ZValueProtected {
};

struct ZValueGlobal {
	struct ZCommonGlobal common;
	struct ZValueClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
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
Self * z_value_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
Self * z_value_dup(ZValue *src);
int  z_value_get_is_object(Self *self);
ZObject *  z_value_get_as_object(Self *self);
void z_value_set_as_object(Self *self, ZObject *  value);
int  z_value_get_is_boolean(Self *self);
int  z_value_get_as_boolean(Self *self);
void z_value_set_as_boolean(Self *self, int  value);
int  z_value_get_is_int8(Self *self);
int8_t  z_value_get_as_int8(Self *self);
void z_value_set_as_int8(Self *self, int8_t  value);
int  z_value_get_is_int16(Self *self);
int16_t  z_value_get_as_int16(Self *self);
void z_value_set_as_int16(Self *self, int16_t  value);
int  z_value_get_is_int32(Self *self);
int32_t  z_value_get_as_int32(Self *self);
void z_value_set_as_int32(Self *self, int32_t  value);
int  z_value_get_is_int64(Self *self);
int64_t  z_value_get_as_int64(Self *self);
void z_value_set_as_int64(Self *self, int64_t  value);
int  z_value_get_is_uint8(Self *self);
uint8_t  z_value_get_as_uint8(Self *self);
void z_value_set_as_uint8(Self *self, uint8_t  value);
int  z_value_get_is_uint16(Self *self);
uint16_t  z_value_get_as_uint16(Self *self);
void z_value_set_as_uint16(Self *self, uint16_t  value);
int  z_value_get_is_uint32(Self *self);
uint32_t  z_value_get_as_uint32(Self *self);
void z_value_set_as_uint32(Self *self, uint32_t  value);
int  z_value_get_is_uint64(Self *self);
uint64_t  z_value_get_as_uint64(Self *self);
void z_value_set_as_uint64(Self *self, uint64_t  value);
int  z_value_get_is_real32(Self *self);
float  z_value_get_as_real32(Self *self);
void z_value_set_as_real32(Self *self, float  value);
int  z_value_get_is_real64(Self *self);
double  z_value_get_as_real64(Self *self);
void z_value_set_as_real64(Self *self, double  value);

#undef Self


#endif
