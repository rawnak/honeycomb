/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Rawnak Jahan Syeda
 *
 * z-bind.c: Bootstrap file for z-bind.zco
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


#include <z-value.h>
#include <stdint.h>
#include <assert.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-bind.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZBind
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_bind_new(ctx,allocator)
#define INIT_EXISTS
#define init z_bind_init
#define new z_bind_new
#define assign z_bind_assign
#define append_argument z_bind_append_argument
#define append_variable_argument z_bind_append_variable_argument
#define append_int8 z_bind_append_int8
#define append_int16 z_bind_append_int16
#define append_int32 z_bind_append_int32
#define append_int64 z_bind_append_int64
#define append_variable_int32 z_bind_append_variable_int32
#define append_variable_int64 z_bind_append_variable_int64
#define append_uint8 z_bind_append_uint8
#define append_uint16 z_bind_append_uint16
#define append_uint32 z_bind_append_uint32
#define append_uint64 z_bind_append_uint64
#define append_variable_uint32 z_bind_append_variable_uint32
#define append_variable_uint64 z_bind_append_variable_uint64
#define append_ptr z_bind_append_ptr
#define append_variable_ptr z_bind_append_variable_ptr
#define append_variable_buffer z_bind_append_variable_buffer
#define set_handler z_bind_set_handler
#define create_arglist z_bind_create_arglist
#define create_closure z_bind_create_closure
#define get_data_ptr z_bind_get_data_ptr
#define set_data_ptr z_bind_set_data_ptr
#define invoke z_bind_invoke
#define unpack_variable_buffer z_bind_unpack_variable_buffer

int z_bind_type_id = -1;

static Self *__z_bind_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_bind_type_id);
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
		__z_bind_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_bind_init(Self *self);
static void  z_bind_reset(ZObject *object);
static void  z_bind_append_argument(Self *self,void *value,int arg_size);
static void  z_bind_append_variable_argument(Self *self,void *value,int arg_size);
static ZVector *  z_bind_create_arglist(Self *self,uint8_t *args,int args_size,struct zco_context_t *ctx);
static ZClosure *  z_bind_create_closure(Self *self,ZBindData *data,struct zco_context_t *ctx);
static void z_bind_class_destroy(ZObjectGlobal *gbl);
static void z_bind___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZBindGlobal * z_bind_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_bind_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_bind_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZBindGlobal *global = (ZBindGlobal *) malloc(sizeof(struct ZBindGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZBindClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZBindClass));
		global->common.name = "ZBind";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZBind temp;
		struct ZBindClass temp_class;

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
		if (z_bind_type_id == -1)
			z_bind_type_id = zco_allocate_type_id();
		global->common.id = z_bind_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_bind_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_bind_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_bind_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_bind_reset;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_bind_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_bind___delete;
		}
		__z_bind_class_init(ctx, (ZBindClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		z_map_insert((ZMap *) global->common.method_map, strdup("assign"), (ZObjectSignalHandler) assign);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_int8"), (ZObjectSignalHandler) append_int8);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_int16"), (ZObjectSignalHandler) append_int16);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_int32"), (ZObjectSignalHandler) append_int32);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_int64"), (ZObjectSignalHandler) append_int64);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_variable_int32"), (ZObjectSignalHandler) append_variable_int32);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_variable_int64"), (ZObjectSignalHandler) append_variable_int64);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_uint8"), (ZObjectSignalHandler) append_uint8);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_uint16"), (ZObjectSignalHandler) append_uint16);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_uint32"), (ZObjectSignalHandler) append_uint32);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_uint64"), (ZObjectSignalHandler) append_uint64);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_variable_uint32"), (ZObjectSignalHandler) append_variable_uint32);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_variable_uint64"), (ZObjectSignalHandler) append_variable_uint64);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_ptr"), (ZObjectSignalHandler) append_ptr);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_variable_ptr"), (ZObjectSignalHandler) append_variable_ptr);
		z_map_insert((ZMap *) global->common.method_map, strdup("append_variable_buffer"), (ZObjectSignalHandler) append_variable_buffer);
		z_map_insert((ZMap *) global->common.method_map, strdup("invoke"), (ZObjectSignalHandler) invoke);
		z_map_insert((ZMap *) global->common.method_map, strdup("unpack_variable_buffer"), (ZObjectSignalHandler) unpack_variable_buffer);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZBindGlobal *) global);
		#endif
		return global;
	}
	return (ZBindGlobal *) *global_ptr;
}

void __z_bind_class_init(struct zco_context_t *ctx, ZBindClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_bind_init(struct zco_context_t *ctx, Self *self)
{
	struct ZBindGlobal *_global = z_bind_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_bind_init(Self *self)
{
 selfp->data_ptr = &selfp->data;
 selfp->data.handler = NULL;
 selfp->data.args_size = 0;
 selfp->data.vargs_size = 0;
 memset(selfp->data.args, 0, sizeof(selfp->data.args));
 memset(selfp->data.args, 0, sizeof(selfp->data.vargs));
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_bind_reset(ZObject *object)
{
 Self *self = (Self *) object;

 selfp->data_ptr = &selfp->data;
 selfp->data.handler = NULL;
 selfp->data.args_size = 0;
 selfp->data.vargs_size = 0;
 memset(selfp->data.args, 0, sizeof(selfp->data.args));
 memset(selfp->data.args, 0, sizeof(selfp->data.vargs));

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_bind_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
void  z_bind_assign(Self *self,ZBind *other)
{
 ZBindData *to = &selfp->data;
 ZBindData *from = &other->_priv.data;

 to->handler = from->handler;

 to->args_size = from->args_size;
 memcpy(to->args, from->args, from->args_size);

 to->vargs_size = from->vargs_size;
 memcpy(to->vargs, from->vargs, from->vargs_size);
 }
static void  z_bind_append_argument(Self *self,void *value,int arg_size)
{
 uint8_t *args = selfp->data.args;
 int args_size = selfp->data.args_size;

 *(args + args_size) = arg_size;
 memcpy(args + args_size + 1, value, arg_size);

 selfp->data.args_size = args_size + arg_size + 1;
 }
static void  z_bind_append_variable_argument(Self *self,void *value,int arg_size)
{
 uint8_t *vargs = selfp->data.vargs;
 int vargs_size = selfp->data.vargs_size;

 *(vargs + vargs_size) = arg_size;
 memcpy(vargs + vargs_size + 1, value, arg_size);

 selfp->data.vargs_size = vargs_size + arg_size + 1;
 }
void  z_bind_append_int8(Self *self,int8_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_int16(Self *self,int16_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_int32(Self *self,int32_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_int64(Self *self,int64_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_variable_int32(Self *self,int32_t value)
{
 append_variable_argument(self, &value, sizeof(value));
 }
void  z_bind_append_variable_int64(Self *self,int64_t value)
{
 append_variable_argument(self, &value, sizeof(value));
 }
void  z_bind_append_uint8(Self *self,uint8_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_uint16(Self *self,uint16_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_uint32(Self *self,uint32_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_uint64(Self *self,uint64_t value)
{
 append_argument(self, &value, sizeof(value));
 }
void  z_bind_append_variable_uint32(Self *self,uint32_t value)
{
 append_variable_argument(self, &value, sizeof(value));
 }
void  z_bind_append_variable_uint64(Self *self,uint64_t value)
{
 append_variable_argument(self, &value, sizeof(value));
 }
void  z_bind_append_ptr(Self *self,void *value)
{
 append_argument(self, &value, sizeof(void*));
 }
void  z_bind_append_variable_ptr(Self *self,void *value)
{
 append_variable_argument(self, &value, sizeof(void*));
 }
void  z_bind_append_variable_buffer(Self *self,void *buffer,int size)
{
 uint8_t *b8 = (uint8_t *) buffer;

 while (size > 0) {
 if (size >= 8) {
 append_variable_uint64(self, *((uint64_t *) b8));
 size -= 8;
 b8 += 8;
 } else if (size >= 4) {
 append_variable_uint32(self, *((uint32_t *) b8));
 size -= 4;
 b8 += 4;
 } else if (size == 3) {
 uint32_t val = 0;
 memcpy(&val, b8, 3);
 append_variable_uint32(self, val);
 size -= 3;
 b8 += 3;
 } else if (size == 2) {
 append_variable_uint32(self, (uint32_t) *((uint16_t *) b8));
 size -= 2;
 b8 += 2;
 } else if (size == 1) {
 append_variable_uint32(self, (uint32_t) *b8);
 --size;
 ++b8;
 }
 }
 }
void z_bind_set_handler(Self *self, ZBindHandler  value)
{
 selfp->data_ptr->handler = value;
 }
static ZVector *  z_bind_create_arglist(Self *self,uint8_t *args,int args_size,struct zco_context_t *ctx)
{
 ZVector *arglist = z_vector_new(ctx, ctx->flex_allocator);
 z_vector_set_item_size(arglist, 0);
 z_vector_set_item_destruct(arglist, (ZVectorItemCallback) z_object_unref);
 int i;

 for (i=0; i<args_size; ++i) {
 ZValue *zval = z_value_new(ctx, ctx->flex_allocator);
 int arg_size = args[i];

 assert(arg_size == 1 || arg_size == 2 || arg_size == 4 || arg_size == 8);

 switch (arg_size)
 {
 case 1:
 {
 uint8_t value = *(args + i + 1);
 ++i;
 z_value_set_as_uint8(zval, value);
 }
 break;
 case 2:
 {
 uint16_t value = *((uint16_t *) (args + i + 1));
 i+=2;
 z_value_set_as_uint16(zval, value);
 }
 break;
 case 4:
 {
 uint32_t value = *((uint32_t *) (args + i + 1));
 i+=4;
 z_value_set_as_uint32(zval, value);
 }
 break;
 case 8:
 {
 uint64_t value = *((uint64_t *) (args + i + 1));
 i+=8;
 z_value_set_as_uint64(zval, value);
 }
 break;

 default:
 abort();
 }

 z_vector_push_back(arglist, zval);
 }

 return arglist;
 }
static ZClosure *  z_bind_create_closure(Self *self,ZBindData *data,struct zco_context_t *ctx)
{
 ZClosure *closure = z_closure_new(ctx, ctx->flex_allocator);
 z_closure_set_marshal(closure, ctx->marshal);
 z_closure_set_target(closure, Z_OBJECT(self));
 z_closure_set_handler(closure, (ZObjectSignalHandler) data->handler);

 return closure;
 }
ZBindData *  z_bind_get_data_ptr(Self *self)
{
 return selfp->data_ptr;
 }
void z_bind_set_data_ptr(Self *self, ZBindData *  value)
{
 selfp->data_ptr = value;
 }
int  z_bind_invoke(Self *self)
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZClosure *closure;
 ZVector *args, *vargs;

 closure = create_closure(self, selfp->data_ptr, ctx);
 args = create_arglist(self, selfp->data_ptr->args, selfp->data_ptr->args_size, ctx);
 vargs = create_arglist(self, selfp->data_ptr->vargs, selfp->data_ptr->vargs_size, ctx);

 int rc = z_closure_invoke(closure, args, vargs);

 z_object_unref(Z_OBJECT(vargs));
 z_object_unref(Z_OBJECT(args));
 z_object_unref(Z_OBJECT(closure));

 return rc;
 }
void  z_bind_unpack_variable_buffer(va_list ap,void *buffer,int size)
{
 uint8_t *b8 = (uint8_t *) buffer;

 while (size > 0) {
 if (size >= 8) {
 *((uint64_t *) b8) = va_arg(ap, uint64_t);
 size -= 8;
 b8 += 8;
 } else if (size >= 4) {
 *((uint32_t *) b8) = va_arg(ap, uint32_t);
 size -= 4;
 b8 += 4;
 } else if (size == 3) {
 uint32_t val = va_arg(ap, uint32_t);
 memcpy(b8, &val, 3);
 size -= 3;
 b8 += 3;
 } else if (size == 2) {
 *((uint16_t *) b8) = va_arg(ap, uint32_t);
 size -= 2;
 b8 += 2;
 } else if (size == 1) {
 *((uint8_t *) b8) = va_arg(ap, uint32_t);
 --size;
 ++b8;
 }
 }
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_bind_class_destroy(ZObjectGlobal *gbl)
{
	ZBindGlobal *_global = (ZBindGlobal *) gbl;

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_bind___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



