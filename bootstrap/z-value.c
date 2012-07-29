/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-value.c: Bootstrap file for z-value.zco
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

#line 44 "z-value.zco"

#include <z-object.h>
#include <stdint.h>
#include <assert.h>

enum ZValueType {
 None,
 Boolean,
 Int8,
 Int16,
 Int32,
 Int64,
 UInt8,
 UInt16,
 UInt32,
 UInt64,
 Real32,
 Real64,
 Object
};



#include <z-map.h>
#include <string.h>
#include <z-value.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZValue
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_value_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 51 "z-value.zco"
#define init z_value_init
#line 56 "z-value.zco"
#define new z_value_new
#line 62 "z-value.zco"
#define dup z_value_dup
#line 89 "z-value.zco"
#define get_is_object z_value_get_is_object
#line 97 "z-value.zco"
#define get_as_object z_value_get_as_object
#line 103 "z-value.zco"
#define set_as_object z_value_set_as_object
#line 118 "z-value.zco"
#define get_is_boolean z_value_get_is_boolean
#line 126 "z-value.zco"
#define get_as_boolean z_value_get_as_boolean
#line 131 "z-value.zco"
#define set_as_boolean z_value_set_as_boolean
#line 144 "z-value.zco"
#define get_is_int8 z_value_get_is_int8
#line 152 "z-value.zco"
#define get_as_int8 z_value_get_as_int8
#line 157 "z-value.zco"
#define set_as_int8 z_value_set_as_int8
#line 169 "z-value.zco"
#define get_is_int16 z_value_get_is_int16
#line 177 "z-value.zco"
#define get_as_int16 z_value_get_as_int16
#line 182 "z-value.zco"
#define set_as_int16 z_value_set_as_int16
#line 194 "z-value.zco"
#define get_is_int32 z_value_get_is_int32
#line 202 "z-value.zco"
#define get_as_int32 z_value_get_as_int32
#line 207 "z-value.zco"
#define set_as_int32 z_value_set_as_int32
#line 219 "z-value.zco"
#define get_is_int64 z_value_get_is_int64
#line 227 "z-value.zco"
#define get_as_int64 z_value_get_as_int64
#line 232 "z-value.zco"
#define set_as_int64 z_value_set_as_int64
#line 245 "z-value.zco"
#define get_is_uint8 z_value_get_is_uint8
#line 253 "z-value.zco"
#define get_as_uint8 z_value_get_as_uint8
#line 258 "z-value.zco"
#define set_as_uint8 z_value_set_as_uint8
#line 270 "z-value.zco"
#define get_is_uint16 z_value_get_is_uint16
#line 278 "z-value.zco"
#define get_as_uint16 z_value_get_as_uint16
#line 283 "z-value.zco"
#define set_as_uint16 z_value_set_as_uint16
#line 295 "z-value.zco"
#define get_is_uint32 z_value_get_is_uint32
#line 303 "z-value.zco"
#define get_as_uint32 z_value_get_as_uint32
#line 308 "z-value.zco"
#define set_as_uint32 z_value_set_as_uint32
#line 320 "z-value.zco"
#define get_is_uint64 z_value_get_is_uint64
#line 328 "z-value.zco"
#define get_as_uint64 z_value_get_as_uint64
#line 333 "z-value.zco"
#define set_as_uint64 z_value_set_as_uint64
#line 346 "z-value.zco"
#define get_is_real32 z_value_get_is_real32
#line 354 "z-value.zco"
#define get_as_real32 z_value_get_as_real32
#line 359 "z-value.zco"
#define set_as_real32 z_value_set_as_real32
#line 371 "z-value.zco"
#define get_is_real64 z_value_get_is_real64
#line 379 "z-value.zco"
#define get_as_real64 z_value_get_as_real64
#line 384 "z-value.zco"
#define set_as_real64 z_value_set_as_real64

int z_value_type_id = -1;

static Self *__z_value_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_value_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 51 "z-value.zco"
static void z_value_init(Self *self);
#line 75 "z-value.zco"
static void  z_value_dispose(ZObject *object);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZValueGlobal * z_value_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_value_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_value_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZValueGlobal *global = (ZValueGlobal *) malloc(sizeof(struct ZValueGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZValueClass));
		memset(global->_class, 0, sizeof(struct ZValueClass));
		global->name = "ZValue";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZValue temp;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			unsigned long offset = global->vtable_off_list[z_object_type_id];
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
		}
		if (z_value_type_id == -1)
			z_value_type_id = zco_allocate_type_id();
		global->id = z_value_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_value_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_value_type_id);
		*global_ptr = global;
		
#line 75 "z-value.zco"
		{
#line 75 "z-value.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) global->_class + global->vtable_off_list[z_object_type_id]);
#line 75 "z-value.zco"
			global->__parent_dispose = p_class->__dispose;
#line 75 "z-value.zco"
			p_class->__dispose = z_value_dispose;
#line 75 "z-value.zco"
		}
		__z_value_class_init(ctx, (ZValueClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 56 "z-value.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 62 "z-value.zco"
		z_map_insert((ZMap *) global->method_map, strdup("dup"), (ZObjectSignalHandler) dup);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZValueGlobal *) global);
		#endif
		return global;
	}
	return (ZValueGlobal *) *global_ptr;
}

void __z_value_class_init(struct zco_context_t *ctx, ZValueClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_value_init(struct zco_context_t *ctx, Self *self)
{
	struct ZValueGlobal *_global = z_value_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->global_base = (void *) _global;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 51 "z-value.zco"
static void z_value_init(Self *self)
{
 selfp->tag = None;
 }
#line 56 "z-value.zco"
Self * z_value_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 62 "z-value.zco"
Self * z_value_dup(ZValue *src)
{
 Self *self = GET_NEW(src->_global->ctx);

 selfp->data = src->_priv.data;
 selfp->tag = src->_priv.tag;

 if (selfp->tag == Object)
 z_object_ref(Z_OBJECT(selfp->data._object));

 return self;
 }
#line 75 "z-value.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_value_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 89 "z-value.zco"
int  z_value_get_is_object(Self *self)
{
 return selfp->tag == Object;
 }
#line 97 "z-value.zco"
ZObject *  z_value_get_as_object(Self *self)
{
 assert(selfp->tag == Object);
 z_object_ref(selfp->data._object);
 return selfp->data._object;
 }
#line 103 "z-value.zco"
void z_value_set_as_object(Self *self, ZObject *  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);
 else
 selfp->tag = Object;

 selfp->data._object = value;
 z_object_ref(value);
 }
#line 118 "z-value.zco"
int  z_value_get_is_boolean(Self *self)
{
 return selfp->tag == Boolean;
 }
#line 126 "z-value.zco"
int  z_value_get_as_boolean(Self *self)
{
 assert(selfp->tag == Boolean);
 return selfp->data._boolean;
 }
#line 131 "z-value.zco"
void z_value_set_as_boolean(Self *self, int  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Boolean;
 selfp->data._boolean = value;
 }
#line 144 "z-value.zco"
int  z_value_get_is_int8(Self *self)
{
 return selfp->tag == Int8;
 }
#line 152 "z-value.zco"
int8_t  z_value_get_as_int8(Self *self)
{
 assert(selfp->tag == Int8);
 return selfp->data._int8;
 }
#line 157 "z-value.zco"
void z_value_set_as_int8(Self *self, int8_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int8;
 selfp->data._int8 = value;
 }
#line 169 "z-value.zco"
int  z_value_get_is_int16(Self *self)
{
 return selfp->tag == Int16;
 }
#line 177 "z-value.zco"
int16_t  z_value_get_as_int16(Self *self)
{
 assert(selfp->tag == Int16);
 return selfp->data._int16;
 }
#line 182 "z-value.zco"
void z_value_set_as_int16(Self *self, int16_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int16;
 selfp->data._int16 = value;
 }
#line 194 "z-value.zco"
int  z_value_get_is_int32(Self *self)
{
 return selfp->tag == Int32;
 }
#line 202 "z-value.zco"
int32_t  z_value_get_as_int32(Self *self)
{
 assert(selfp->tag == Int32);
 return selfp->data._int32;
 }
#line 207 "z-value.zco"
void z_value_set_as_int32(Self *self, int32_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int32;
 selfp->data._int32 = value;
 }
#line 219 "z-value.zco"
int  z_value_get_is_int64(Self *self)
{
 return selfp->tag == Int64;
 }
#line 227 "z-value.zco"
int64_t  z_value_get_as_int64(Self *self)
{
 assert(selfp->tag == Int64);
 return selfp->data._int64;
 }
#line 232 "z-value.zco"
void z_value_set_as_int64(Self *self, int64_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int64;
 selfp->data._int64 = value;
 }
#line 245 "z-value.zco"
int  z_value_get_is_uint8(Self *self)
{
 return selfp->tag == UInt8;
 }
#line 253 "z-value.zco"
uint8_t  z_value_get_as_uint8(Self *self)
{
 assert(selfp->tag == UInt8);
 return selfp->data._uint8;
 }
#line 258 "z-value.zco"
void z_value_set_as_uint8(Self *self, uint8_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt8;
 selfp->data._uint8 = value;
 }
#line 270 "z-value.zco"
int  z_value_get_is_uint16(Self *self)
{
 return selfp->tag == UInt16;
 }
#line 278 "z-value.zco"
uint16_t  z_value_get_as_uint16(Self *self)
{
 assert(selfp->tag == UInt16);
 return selfp->data._uint16;
 }
#line 283 "z-value.zco"
void z_value_set_as_uint16(Self *self, uint16_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt16;
 selfp->data._uint16 = value;
 }
#line 295 "z-value.zco"
int  z_value_get_is_uint32(Self *self)
{
 return selfp->tag == UInt32;
 }
#line 303 "z-value.zco"
uint32_t  z_value_get_as_uint32(Self *self)
{
 assert(selfp->tag == UInt32);
 return selfp->data._uint32;
 }
#line 308 "z-value.zco"
void z_value_set_as_uint32(Self *self, uint32_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt32;
 selfp->data._uint32 = value;
 }
#line 320 "z-value.zco"
int  z_value_get_is_uint64(Self *self)
{
 return selfp->tag == UInt64;
 }
#line 328 "z-value.zco"
uint64_t  z_value_get_as_uint64(Self *self)
{
 assert(selfp->tag == UInt64);
 return selfp->data._uint64;
 }
#line 333 "z-value.zco"
void z_value_set_as_uint64(Self *self, uint64_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt64;
 selfp->data._uint64 = value;
 }
#line 346 "z-value.zco"
int  z_value_get_is_real32(Self *self)
{
 return selfp->tag == Real32;
 }
#line 354 "z-value.zco"
float  z_value_get_as_real32(Self *self)
{
 assert(selfp->tag == Real32);
 return selfp->data._real32;
 }
#line 359 "z-value.zco"
void z_value_set_as_real32(Self *self, float  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Real32;
 selfp->data._real32 = value;
 }
#line 371 "z-value.zco"
int  z_value_get_is_real64(Self *self)
{
 return selfp->tag == Real64;
 }
#line 379 "z-value.zco"
double  z_value_get_as_real64(Self *self)
{
 assert(selfp->tag == Real64);
 return selfp->data._real64;
 }
#line 384 "z-value.zco"
void z_value_set_as_real64(Self *self, double  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Real64;
 selfp->data._real64 = value;
 }

#line 395 "z-value.zco"


