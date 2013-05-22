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



#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-value.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZValue
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_value_new(ctx,allocator)
#define INIT_EXISTS
#define init z_value_init
#define new z_value_new
#define dup z_value_dup
#define get_is_object z_value_get_is_object
#define get_as_object z_value_get_as_object
#define set_as_object z_value_set_as_object
#define get_is_boolean z_value_get_is_boolean
#define get_as_boolean z_value_get_as_boolean
#define set_as_boolean z_value_set_as_boolean
#define get_is_int8 z_value_get_is_int8
#define get_as_int8 z_value_get_as_int8
#define set_as_int8 z_value_set_as_int8
#define get_is_int16 z_value_get_is_int16
#define get_as_int16 z_value_get_as_int16
#define set_as_int16 z_value_set_as_int16
#define get_is_int32 z_value_get_is_int32
#define get_as_int32 z_value_get_as_int32
#define set_as_int32 z_value_set_as_int32
#define get_is_int64 z_value_get_is_int64
#define get_as_int64 z_value_get_as_int64
#define set_as_int64 z_value_set_as_int64
#define get_is_uint8 z_value_get_is_uint8
#define get_as_uint8 z_value_get_as_uint8
#define set_as_uint8 z_value_set_as_uint8
#define get_is_uint16 z_value_get_is_uint16
#define get_as_uint16 z_value_get_as_uint16
#define set_as_uint16 z_value_set_as_uint16
#define get_is_uint32 z_value_get_is_uint32
#define get_as_uint32 z_value_get_as_uint32
#define set_as_uint32 z_value_set_as_uint32
#define get_is_uint64 z_value_get_is_uint64
#define get_as_uint64 z_value_get_as_uint64
#define set_as_uint64 z_value_set_as_uint64
#define get_is_real32 z_value_get_is_real32
#define get_as_real32 z_value_get_as_real32
#define set_as_real32 z_value_set_as_real32
#define get_is_real64 z_value_get_is_real64
#define get_as_real64 z_value_get_as_real64
#define set_as_real64 z_value_set_as_real64

int z_value_type_id = -1;

static Self *__z_value_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_value_type_id);
			z_object_unref(Z_OBJECT(object_tracker));
		}
	}
	if (!self) {
		ZMemoryAllocator *obj_allocator = ctx->fixed_allocator;
		if (obj_allocator)
			self = (Self *) z_memory_allocator_allocate(obj_allocator, sizeof(Self));
		else
			self = (Self *) malloc(sizeof(Self));
		z_object_set_allocator_ptr((ZObject *) self, allocator);
		__z_value_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_value_init(Self *self);
static void  z_value_reset(ZObject *object);
static void  z_value_dispose(ZObject *object);
static void z_value_class_destroy(ZObjectGlobal *gbl);
static void z_value___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZValueGlobal * z_value_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_value_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_value_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZValueGlobal *global = (ZValueGlobal *) malloc(sizeof(struct ZValueGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZValueClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZValueClass));
		global->common.name = "ZValue";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZValue temp;
		struct ZValueClass temp_class;

		{
			struct ZObjectGlobal *p_global = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->common.vtable_off_list,
				&global->common.vtable_off_size,
				p_global->common.vtable_off_list,
				p_global->common.vtable_off_size,
				&temp,
				&temp.parent_z_object);
			zco_inherit_vtable(
				&global->common.svtable_off_list,
				&global->common.svtable_off_size,
				p_global->common.svtable_off_list,
				p_global->common.svtable_off_size,
				&temp_class,
				&temp_class.parent_z_object);
			ZObjectClass *p1_class = CLASS_FROM_GLOBAL(p_global);
			ZObjectClass *p2_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			memcpy(p2_class, p1_class, sizeof(struct ZObjectClass));
		}
		if (z_value_type_id == -1)
			z_value_type_id = zco_allocate_type_id();
		global->common.id = z_value_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_value_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_value_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_value_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_value_reset;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_value_dispose;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_value_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_value___delete;
		}
		__z_value_class_init(ctx, (ZValueClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		z_map_insert((ZMap *) global->common.method_map, strdup("dup"), (ZObjectSignalHandler) dup);
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
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_value_init(Self *self)
{
 selfp->tag = None;
 }
Self * z_value_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
Self * z_value_dup(ZValue *src)
{
 Self *self = GET_NEW(CTX_FROM_OBJECT(src), ALLOCATOR_FROM_OBJECT(src));

 selfp->data = src->_priv.data;
 selfp->tag = src->_priv.tag;

 if (selfp->tag == Object)
 z_object_ref(Z_OBJECT(selfp->data._object));

 return self;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_value_reset(ZObject *object)
{
 Self *self = (Self *) object;

 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = None;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_value_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
int  z_value_get_is_object(Self *self)
{
 return selfp->tag == Object;
 }
ZObject *  z_value_get_as_object(Self *self)
{
 assert(selfp->tag == Object);
 z_object_ref(selfp->data._object);
 return selfp->data._object;
 }
void z_value_set_as_object(Self *self, ZObject *  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);
 else
 selfp->tag = Object;

 selfp->data._object = value;
 z_object_ref(value);
 }
int  z_value_get_is_boolean(Self *self)
{
 return selfp->tag == Boolean;
 }
int  z_value_get_as_boolean(Self *self)
{
 assert(selfp->tag == Boolean);
 return selfp->data._boolean;
 }
void z_value_set_as_boolean(Self *self, int  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Boolean;
 selfp->data._boolean = value;
 }
int  z_value_get_is_int8(Self *self)
{
 return selfp->tag == Int8;
 }
int8_t  z_value_get_as_int8(Self *self)
{
 assert(selfp->tag == Int8);
 return selfp->data._int8;
 }
void z_value_set_as_int8(Self *self, int8_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int8;
 selfp->data._int8 = value;
 }
int  z_value_get_is_int16(Self *self)
{
 return selfp->tag == Int16;
 }
int16_t  z_value_get_as_int16(Self *self)
{
 assert(selfp->tag == Int16);
 return selfp->data._int16;
 }
void z_value_set_as_int16(Self *self, int16_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int16;
 selfp->data._int16 = value;
 }
int  z_value_get_is_int32(Self *self)
{
 return selfp->tag == Int32;
 }
int32_t  z_value_get_as_int32(Self *self)
{
 assert(selfp->tag == Int32);
 return selfp->data._int32;
 }
void z_value_set_as_int32(Self *self, int32_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int32;
 selfp->data._int32 = value;
 }
int  z_value_get_is_int64(Self *self)
{
 return selfp->tag == Int64;
 }
int64_t  z_value_get_as_int64(Self *self)
{
 assert(selfp->tag == Int64);
 return selfp->data._int64;
 }
void z_value_set_as_int64(Self *self, int64_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Int64;
 selfp->data._int64 = value;
 }
int  z_value_get_is_uint8(Self *self)
{
 return selfp->tag == UInt8;
 }
uint8_t  z_value_get_as_uint8(Self *self)
{
 assert(selfp->tag == UInt8);
 return selfp->data._uint8;
 }
void z_value_set_as_uint8(Self *self, uint8_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt8;
 selfp->data._uint8 = value;
 }
int  z_value_get_is_uint16(Self *self)
{
 return selfp->tag == UInt16;
 }
uint16_t  z_value_get_as_uint16(Self *self)
{
 assert(selfp->tag == UInt16);
 return selfp->data._uint16;
 }
void z_value_set_as_uint16(Self *self, uint16_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt16;
 selfp->data._uint16 = value;
 }
int  z_value_get_is_uint32(Self *self)
{
 return selfp->tag == UInt32;
 }
uint32_t  z_value_get_as_uint32(Self *self)
{
 assert(selfp->tag == UInt32);
 return selfp->data._uint32;
 }
void z_value_set_as_uint32(Self *self, uint32_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt32;
 selfp->data._uint32 = value;
 }
int  z_value_get_is_uint64(Self *self)
{
 return selfp->tag == UInt64;
 }
uint64_t  z_value_get_as_uint64(Self *self)
{
 assert(selfp->tag == UInt64);
 return selfp->data._uint64;
 }
void z_value_set_as_uint64(Self *self, uint64_t  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = UInt64;
 selfp->data._uint64 = value;
 }
int  z_value_get_is_real32(Self *self)
{
 return selfp->tag == Real32;
 }
float  z_value_get_as_real32(Self *self)
{
 assert(selfp->tag == Real32);
 return selfp->data._real32;
 }
void z_value_set_as_real32(Self *self, float  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Real32;
 selfp->data._real32 = value;
 }
int  z_value_get_is_real64(Self *self)
{
 return selfp->tag == Real64;
 }
double  z_value_get_as_real64(Self *self)
{
 assert(selfp->tag == Real64);
 return selfp->data._real64;
 }
void z_value_set_as_real64(Self *self, double  value)
{
 if (selfp->tag == Object)
 z_object_unref(selfp->data._object);

 selfp->tag = Real64;
 selfp->data._real64 = value;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_value_class_destroy(ZObjectGlobal *gbl)
{
	ZValueGlobal *_global = (ZValueGlobal *) gbl;

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_value___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



