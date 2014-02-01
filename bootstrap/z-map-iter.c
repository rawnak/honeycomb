/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-map-iter.c: Bootstrap file for z-map-iter.zco
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

#line 6 "z-map-iter.zco"


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-map-iter-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZMapIter
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_map_iter_new(ctx,allocator)
#define INIT_EXISTS
#define init z_map_iter_init
#define new z_map_iter_new
#define dup z_map_iter_dup
#define assign z_map_iter_assign
#define get_index z_map_iter_get_index
#define set_index z_map_iter_set_index
#define advance z_map_iter_advance
#define increment z_map_iter_increment
#define decrement z_map_iter_decrement
#define is_equal z_map_iter_is_equal
#define is_lte z_map_iter_is_lte
#define is_gte z_map_iter_is_gte

ZCO_DEFINE_CLASS_TYPE(z_map_iter);

static void z_map_iter_init(Self *self);
static void  z_map_iter_reset(ZObject *object);
static void z_map_iter_class_destroy(ZObjectGlobal *gbl);
static void z_map_iter___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZMapIterGlobal * z_map_iter_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZMapIter, z_map_iter, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZMapIter);
	ZCO_REGISTER_TYPE(z_map_iter);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_map_iter, reset);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_map_iter, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_map_iter, __delete);
	ZCO_CREATE_METHOD_MAP(ZMapIter, z_map_iter);
	ZCO_REGISTER_METHOD(new);
	ZCO_REGISTER_METHOD(dup);
	ZCO_REGISTER_METHOD(assign);
	ZCO_REGISTER_METHOD(advance);
	ZCO_REGISTER_METHOD(increment);
	ZCO_REGISTER_METHOD(decrement);
	ZCO_REGISTER_METHOD(is_equal);
	ZCO_REGISTER_METHOD(is_lte);
	ZCO_REGISTER_METHOD(is_gte);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
}

void __z_map_iter_class_init(struct zco_context_t *ctx, ZMapIterClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_map_iter_init(struct zco_context_t *ctx, Self *self)
{
	ZCO_INIT_START(ZMapIter, z_map_iter);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_map_iter_init(Self *self)
{
 selfp->index = 0;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_map_iter_reset(ZObject *object)
{
 Self *self = (Self *) object;
 selfp->index = 0;
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_map_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
Self * z_map_iter_dup(ZMapIter *src)
{
{
 Self *self = GET_NEW(CTX_FROM_OBJECT(src), ALLOCATOR_FROM_OBJECT(src));

 set_index(self, get_index(src));
 return self;
 }
}
void  z_map_iter_assign(Self *self,ZMapIter *src)
{
{
 set_index(self, get_index(src)); 
 }
}
int  z_map_iter_get_index(Self *self)
{
{
 return selfp->index;
 }
}
void z_map_iter_set_index(Self *self, int  value)
{
{
 selfp->index = value;
 }
}
void  z_map_iter_advance(Self *self,int steps)
{
{
 selfp->index += steps;
 }
}
void  z_map_iter_increment(Self *self)
{
{
 ++selfp->index;
 }
}
void  z_map_iter_decrement(Self *self)
{
{
 --selfp->index;
 }
}
int  z_map_iter_is_equal(Self *self,Self *other)
{
{
 return selfp->index == get_index(other);
 }
}
int  z_map_iter_is_lte(Self *self,Self *other)
{
{
 return selfp->index <= get_index(other);
 }
}
int  z_map_iter_is_gte(Self *self,Self *other)
{
{
 return selfp->index >= get_index(other);
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_map_iter_class_destroy(ZObjectGlobal *gbl)
{
	ZMapIterGlobal *_global = (ZMapIterGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_map_iter___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



