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
#include <z-vector-iter-protected.h>
#include <zco-context.h>
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

ZCO_DEFINE_CLASS_TYPE(z_vector_iter);

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
	ZCO_CREATE_CLASS(global, ZVectorIter, z_vector_iter, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZVectorIter);
	ZCO_REGISTER_TYPE(z_vector_iter);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_iter, reset);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_iter, dispose);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_iter, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_vector_iter, __delete);
	ZCO_CREATE_METHOD_MAP(ZVectorIter, z_vector_iter);
	ZCO_REGISTER_METHOD(new);
	ZCO_REGISTER_METHOD(dup);
	ZCO_REGISTER_METHOD(assign);
	ZCO_REGISTER_METHOD(advance);
	ZCO_REGISTER_METHOD(increment);
	ZCO_REGISTER_METHOD(decrement);
	ZCO_REGISTER_METHOD(is_equal);
	ZCO_REGISTER_METHOD(is_lte);
	ZCO_REGISTER_METHOD(is_gte);
	ZCO_REGISTER_METHOD(is_in_bound);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
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
	ZCO_INIT_START(ZVectorIter, z_vector_iter);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
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
{
 ZVectorSegment *segment = selfp->segment;

 if (!segment) {
 selfp->index = 0;
 selfp->absolute_index = 0;
 return;
 }

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
}
Self * z_vector_iter_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
Self * z_vector_iter_dup(ZVectorIter *src)
{
{
 Self *self = GET_NEW(CTX_FROM_OBJECT(src), ALLOCATOR_FROM_OBJECT(src));
 assign(self, src);
 return self;
 }
}
ZVectorSegment * z_vector_iter_get_segment(Self *self)
{
{
 if (selfp->segment)
 z_object_ref(Z_OBJECT(selfp->segment));

 return selfp->segment;
 }
}
void z_vector_iter_set_segment(Self *self, ZVectorSegment * value)
{
{
 if (value)
 z_object_ref(Z_OBJECT(value));

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 selfp->segment = value;
 }
}
int  z_vector_iter_get_absolute_index(Self *self)
{
{
 return selfp->absolute_index;
 }
}
void z_vector_iter_set_absolute_index(Self *self, int  value)
{
{
 if (selfp->absolute_index != value)
 advance(self, value - selfp->absolute_index);
 }
}
int  z_vector_iter_get_index(Self *self)
{
{
 return selfp->index;
 }
}
void z_vector_iter_set_index(Self *self, int  value)
{
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
}
void  z_vector_iter_assign(Self *self,ZVectorIter *src)
{
{
 ZVectorSegment *segment = get_segment(src);
 set_segment(self, segment);

 if (segment)
 z_object_unref(Z_OBJECT(segment));

 set_index(self, get_index(src));
 }
}
void  z_vector_iter_advance(Self *self,int steps)
{
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
}
void  z_vector_iter_increment(Self *self)
{
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
}
void  z_vector_iter_decrement(Self *self)
{
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
}
int  z_vector_iter_is_equal(Self *self,Self *other)
{
{
 if (self == other)
 return 1;

 validate(self);
 validate(other);
 return selfp->segment == other->_priv.segment && selfp->index == get_index(other);
 }
}
int  z_vector_iter_is_lte(Self *self,Self *other)
{
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
}
int  z_vector_iter_is_gte(Self *self,Self *other)
{
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
}
int  z_vector_iter_is_in_bound(ZVectorIter *self)
{
{
 return z_vector_segment_is_in_bound(selfp->segment, self);
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_vector_iter_class_destroy(ZObjectGlobal *gbl)
{
	ZVectorIterGlobal *_global = (ZVectorIterGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

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



