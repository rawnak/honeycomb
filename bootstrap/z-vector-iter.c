/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector-iter.c: Bootstrap file for z-vector-iter.zco
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

#line 10 "z-vector-iter.zco"

#include <z-vector-segment.h>

#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-vector-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVectorIter
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_vector_iter_new(ctx,allocator)
#define INIT_EXISTS
#define init z_vector_iter_init
#define validate z_vector_iter_validate
#define new z_vector_iter_new
#define dup z_vector_iter_dup
#define get_segment z_vector_iter_get_segment
#define set_segment z_vector_iter_set_segment
#define get_absolute_index z_vector_iter_get_absolute_index
#define set_absolute_index z_vector_iter_set_absolute_index
#define get_index z_vector_iter_get_index
#define set_index z_vector_iter_set_index
#define assign z_vector_iter_assign
#define advance z_vector_iter_advance
#define increment z_vector_iter_increment
#define decrement z_vector_iter_decrement
#define is_equal z_vector_iter_is_equal
#define is_lte z_vector_iter_is_lte
#define is_gte z_vector_iter_is_gte
#define is_in_bound z_vector_iter_is_in_bound

int z_vector_iter_type_id = -1;

static Self *__z_vector_iter_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator)
{
	Self *self = NULL;
	if (allocator) {
		ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator);
		if (object_tracker) {
			self = (Self *) z_object_tracker_create(object_tracker, z_vector_iter_type_id);
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
		__z_vector_iter_init(ctx, self);
	}
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
static void z_vector_iter_init(Self *self);
static void  z_vector_iter_reset(ZObject *object);
static void  z_vector_iter_dispose(ZObject *object);
static void  z_vector_iter_validate(Self *self);
static void z_vector_iter_class_destroy(ZObjectGlobal *gbl);
static void z_vector_iter___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorIterGlobal * z_vector_iter_get_type(struct zco_context_t *ctx)
{
	ZCommonGlobal **global_ptr = NULL;
	if (z_vector_iter_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_vector_iter_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZVectorIterGlobal *global = (ZVectorIterGlobal *) malloc(sizeof(struct ZVectorIterGlobal));
		global->common.ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorIterClass));
		memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct ZVectorIterClass));
		global->common.name = "ZVectorIter";
		global->common.vtable_off_list = NULL;
		global->common.vtable_off_size = 0;
		global->common.svtable_off_list = NULL;
		global->common.svtable_off_size = 0;
		global->common.is_object = 1;

		struct ZVectorIter temp;
		struct ZVectorIterClass temp_class;

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
		if (z_vector_iter_type_id == -1)
			z_vector_iter_type_id = zco_allocate_type_id();
		global->common.id = z_vector_iter_type_id;
		zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, z_vector_iter_type_id);
		zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, z_vector_iter_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_vector_iter_type_id);
		*global_ptr = (ZCommonGlobal *) global;
		
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_reset = p_class->__reset;
			p_class->__reset = z_vector_iter_reset;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_dispose = p_class->__dispose;
			p_class->__dispose = z_vector_iter_dispose;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent_class_destroy = p_class->__class_destroy;
			p_class->__class_destroy = z_vector_iter_class_destroy;
		}
		{
			ZObjectClass *p_class = (ZObjectClass *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[z_object_type_id]);
			global->__parent___delete = p_class->____delete;
			p_class->____delete = z_vector_iter___delete;
		}
		__z_vector_iter_class_init(ctx, (ZVectorIterClass *) CLASS_FROM_GLOBAL(global));
		global->common.method_map = z_map_new(ctx, NULL);
		z_map_set_compare(global->common.method_map, __map_compare);
		z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free);
		z_map_insert((ZMap *) global->common.method_map, strdup("new"), (ZObjectSignalHandler) new);
		z_map_insert((ZMap *) global->common.method_map, strdup("dup"), (ZObjectSignalHandler) dup);
		z_map_insert((ZMap *) global->common.method_map, strdup("assign"), (ZObjectSignalHandler) assign);
		z_map_insert((ZMap *) global->common.method_map, strdup("advance"), (ZObjectSignalHandler) advance);
		z_map_insert((ZMap *) global->common.method_map, strdup("increment"), (ZObjectSignalHandler) increment);
		z_map_insert((ZMap *) global->common.method_map, strdup("decrement"), (ZObjectSignalHandler) decrement);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_equal"), (ZObjectSignalHandler) is_equal);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_lte"), (ZObjectSignalHandler) is_lte);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_gte"), (ZObjectSignalHandler) is_gte);
		z_map_insert((ZMap *) global->common.method_map, strdup("is_in_bound"), (ZObjectSignalHandler) is_in_bound);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZVectorIterGlobal *) global);
		#endif
		return global;
	}
	return (ZVectorIterGlobal *) *global_ptr;
}

void __z_vector_iter_class_init(struct zco_context_t *ctx, ZVectorIterClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_vector_iter_init(struct zco_context_t *ctx, Self *self)
{
	struct ZVectorIterGlobal *_global = z_vector_iter_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(_global);
	((ZObjectClass *) CLASS_FROM_GLOBAL(_global))->real_global = (ZCommonGlobal *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_vector_iter_init(Self *self)
{
 selfp->index = 0;
 selfp->absolute_index = 0;
 selfp->segment = 0;
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_reset
static void  z_vector_iter_reset(ZObject *object)
{
 Self *self = (Self *) object;

 set_segment(self, NULL);

 selfp->index = 0;
 selfp->absolute_index = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_vector_iter_dispose(ZObject *object)
{
 Self *self = (Self *) object;
 set_segment(self, NULL);
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
static void  z_vector_iter_validate(Self *self)
{
 ZVectorSegment *segment = selfp->segment;
 int segment_size = z_vector_segment_get_size(segment);

 if (segment_size != selfp->index)
 return;

 /* This iterator is pointing to the 'one past the last'
                   element in the segment */
 ZVectorSegment *next = z_vector_segment_get_next(segment);
 if (!next)
 return;


 ZVectorIter *begin = z_vector_segment_get_begin(next);
 assign(self, begin);
 
 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(next));
 }
Self * z_vector_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
Self * z_vector_iter_dup(ZVectorIter *src)
{
 Self *self = GET_NEW(CTX_FROM_OBJECT(src), ALLOCATOR_FROM_OBJECT(src));
 assign(self, src);
 return self;
 }
ZVectorSegment * z_vector_iter_get_segment(Self *self)
{
 if (selfp->segment)
 z_object_ref(Z_OBJECT(selfp->segment));

 return selfp->segment;
 }
void z_vector_iter_set_segment(Self *self, ZVectorSegment * value)
{
 if (value)
 z_object_ref(Z_OBJECT(value));

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 selfp->segment = value;
 }
int  z_vector_iter_get_absolute_index(Self *self)
{
 return selfp->absolute_index;
 }
void z_vector_iter_set_absolute_index(Self *self, int  value)
{
 if (selfp->absolute_index != value)
 advance(self, value - selfp->absolute_index);
 }
int  z_vector_iter_get_index(Self *self)
{
 return selfp->index;
 }
void z_vector_iter_set_index(Self *self, int  value)
{
 ZVectorSegment *seg = selfp->segment;

 selfp->index = value;
 selfp->absolute_index = 0;

 if (seg) {
 z_object_ref(Z_OBJECT(seg));

 while (1) {
 ZVectorSegment *new_seg = z_vector_segment_get_prev(seg);
 z_object_unref(Z_OBJECT(seg));
 seg = new_seg;

 if (!seg)
 break;

 selfp->absolute_index += z_vector_segment_get_size(seg);
 }
 }

 selfp->absolute_index += value;
 }
void  z_vector_iter_assign(Self *self,ZVectorIter *src)
{
 ZVectorSegment *segment = get_segment(src);
 set_segment(self, segment);

 if (segment)
 z_object_unref(Z_OBJECT(segment));

 set_index(self, get_index(src));
 }
void  z_vector_iter_advance(Self *self,int steps)
{
 int segment_size;

 selfp->index += steps;
 selfp->absolute_index += steps;

 if (steps > 0) {
 while (1) {
 ZVectorSegment *next = z_vector_segment_get_next(selfp->segment);

 if (!next)
 break;

 if (selfp->index >= (segment_size = z_vector_segment_get_size(selfp->segment))) {
 selfp->index -= segment_size;

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 /* give ownership of next to selfp->segment */
 selfp->segment = next;
 continue;
 }

 z_object_unref(Z_OBJECT(next));
 break;
 }

 } else if (steps < 0) {
 while (selfp->index < 0) {
 ZVectorSegment *prev = z_vector_segment_get_prev(selfp->segment);
 if (!prev)
 break;

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 selfp->segment = prev;
 selfp->index += z_vector_segment_get_size(selfp->segment);
 }

 }
 }
void  z_vector_iter_increment(Self *self)
{
 int segment_size;

 ++selfp->index;
 ++selfp->absolute_index;

 /* If there is no associated segment with this iterator (which may happen if it's
		   referencing an empty vector), we just increment the index without touching
		   the segment */
 if (!selfp->segment)
 return;

 while (1) {
 ZVectorSegment *next = z_vector_segment_get_next(selfp->segment);

 if (!next)
 break;

 if (selfp->index >= (segment_size = z_vector_segment_get_size(selfp->segment))) {
 selfp->index -= segment_size;

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 /* give ownership of next to selfp->segment */
 selfp->segment = next;
 continue;
 }

 z_object_unref(Z_OBJECT(next));
 break;
 }
 }
void  z_vector_iter_decrement(Self *self)
{
 --selfp->index;
 --selfp->absolute_index;

 while (selfp->index < 0) {
 ZVectorSegment *prev = z_vector_segment_get_prev(selfp->segment);
 if (!prev)
 break;

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 selfp->segment = prev;
 selfp->index += z_vector_segment_get_size(selfp->segment);
 }
 }
int  z_vector_iter_is_equal(Self *self,Self *other)
{
 if (self == other)
 return 1;

 validate(self);
 validate(other);
 return selfp->segment == other->_priv.segment && selfp->index == get_index(other);
 }
int  z_vector_iter_is_lte(Self *self,Self *other)
{
 if (selfp->segment == other->_priv.segment) {
 return selfp->index <= get_index(other);
 } else {
 ZVectorSegment *segment = z_vector_segment_get_next(selfp->segment);

 while (segment && segment != other->_priv.segment) {
 ZVectorSegment *next = z_vector_segment_get_next(segment);
 z_object_unref(Z_OBJECT(segment));
 segment = next;
 }

 int rc = segment == other->_priv.segment;
 if (segment)
 z_object_unref(Z_OBJECT(segment));

 return rc;
 }
 }
int  z_vector_iter_is_gte(Self *self,Self *other)
{
 if (selfp->segment == other->_priv.segment) {
 return selfp->index >= get_index(other);
 } else {
 ZVectorSegment *segment = z_vector_segment_get_prev(selfp->segment);

 while (segment && segment != other->_priv.segment) {
 ZVectorSegment *prev = z_vector_segment_get_prev(segment);
 z_object_unref(Z_OBJECT(segment));
 segment = prev;
 }

 int rc = segment == other->_priv.segment;
 if (segment)
 z_object_unref(Z_OBJECT(segment));

 return rc;
 }
 }
int  z_vector_iter_is_in_bound(ZVectorIter *self)
{
 return z_vector_segment_is_in_bound(selfp->segment, self);
 }
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_vector_iter_class_destroy(ZObjectGlobal *gbl)
{
	ZVectorIterGlobal *_global = (ZVectorIterGlobal *) gbl;

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_vector_iter___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



