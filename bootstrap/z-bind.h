/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-bind.h: Bootstrap file for z-bind.zco
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

#ifndef _Z_BIND_H_
#define _Z_BIND_H_

#include <zco-config.h>
#include <z-vector.h>
#include <z-closure.h>
#include <stdarg.h>

struct ZBind;
typedef void(*ZBindHandler)(struct ZBind *self, ...);

struct ZBindData
{
 ZBindHandler handler;
 int args_size;
 int vargs_size;
 uint8_t args[TASK_ARG_SIZE];
 uint8_t vargs[TASK_ARG_SIZE];
};

typedef struct ZBindData ZBindData;


#include <zco-type.h>
#define Self ZBind
#define Z_BIND(s) ((ZBind *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_bind_type_id]))


struct ZBindPrivate;
struct ZBindProtected;
struct ZBindGlobal;
struct ZBindClass;
struct ZBind;

typedef struct ZBindPrivate ZBindPrivate;
typedef struct ZBindProtected ZBindProtected;
typedef struct ZBindGlobal ZBindGlobal;
typedef struct ZBindClass ZBindClass;
typedef struct ZBind ZBind;

struct ZBindPrivate {
	ZBindData data;
	ZBindData *data_ptr;
};

struct ZBindProtected {
};

struct ZBindGlobal {
	struct ZCommonGlobal common;
	struct ZBindClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZBindClass {
	struct ZObjectClass parent_z_object;
};

struct ZBind {
	struct ZObject parent_z_object;
	struct ZBindGlobal *_global;
	struct ZBindPrivate _priv;
	struct ZBindProtected _prot;
};
extern int z_bind_type_id;
ZBindGlobal * z_bind_get_type(struct zco_context_t *ctx);
void __z_bind_init(struct zco_context_t *ctx, ZBind *self);
void __z_bind_class_init(struct zco_context_t *ctx, ZBindClass *_class);
Self * z_bind_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
void  z_bind_assign(Self *self,ZBind *other);
void  z_bind_append_int8(Self *self,int8_t value);
void  z_bind_append_int16(Self *self,int16_t value);
void  z_bind_append_int32(Self *self,int32_t value);
void  z_bind_append_int64(Self *self,int64_t value);
void  z_bind_append_variable_int32(Self *self,int32_t value);
void  z_bind_append_variable_int64(Self *self,int64_t value);
void  z_bind_append_uint8(Self *self,uint8_t value);
void  z_bind_append_uint16(Self *self,uint16_t value);
void  z_bind_append_uint32(Self *self,uint32_t value);
void  z_bind_append_uint64(Self *self,uint64_t value);
void  z_bind_append_variable_uint32(Self *self,uint32_t value);
void  z_bind_append_variable_uint64(Self *self,uint64_t value);
void  z_bind_append_ptr(Self *self,void *value);
void  z_bind_append_variable_ptr(Self *self,void *value);
void  z_bind_append_variable_buffer(Self *self,void *buffer,int size);
void z_bind_set_handler(Self *self, ZBindHandler  value);
ZBindData *  z_bind_get_data_ptr(Self *self);
void z_bind_set_data_ptr(Self *self, ZBindData *  value);
int  z_bind_invoke(Self *self);
void  z_bind_unpack_variable_buffer(va_list ap,void *buffer,int size);

#undef Self


#endif
