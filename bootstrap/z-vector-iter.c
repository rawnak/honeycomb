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
#include <z-vector-iter.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVectorIter
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_vector_iter_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 18 "z-vector-iter.zco"
#define init z_vector_iter_init
#line 41 "z-vector-iter.zco"
#define new z_vector_iter_new
#line 47 "z-vector-iter.zco"
#define dup z_vector_iter_dup
#line 56 "z-vector-iter.zco"
#define get_segment z_vector_iter_get_segment
#line 63 "z-vector-iter.zco"
#define set_segment z_vector_iter_set_segment
#line 77 "z-vector-iter.zco"
#define get_absolute_index z_vector_iter_get_absolute_index
#line 81 "z-vector-iter.zco"
#define set_absolute_index z_vector_iter_set_absolute_index
#line 90 "z-vector-iter.zco"
#define get_index z_vector_iter_get_index
#line 94 "z-vector-iter.zco"
#define set_index z_vector_iter_set_index
#line 121 "z-vector-iter.zco"
#define assign z_vector_iter_assign
#line 132 "z-vector-iter.zco"
#define advance z_vector_iter_advance
#line 177 "z-vector-iter.zco"
#define increment z_vector_iter_increment
#line 212 "z-vector-iter.zco"
#define decrement z_vector_iter_decrement
#line 230 "z-vector-iter.zco"
#define is_equal z_vector_iter_is_equal
#line 235 "z-vector-iter.zco"
#define is_lte z_vector_iter_is_lte
#line 256 "z-vector-iter.zco"
#define is_gte z_vector_iter_is_gte
#line 279 "z-vector-iter.zco"
#define is_in_bound z_vector_iter_is_in_bound

int z_vector_iter_type_id = -1;

static Self *__z_vector_iter_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_vector_iter_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_vector_iter_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 18 "z-vector-iter.zco"
static void z_vector_iter_init(Self *self);
#line 25 "z-vector-iter.zco"
static void  z_vector_iter_reset(ZObject *object);
#line 34 "z-vector-iter.zco"
static void  z_vector_iter_dispose(ZObject *object);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorIterGlobal * z_vector_iter_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_vector_iter_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_vector_iter_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZVectorIterGlobal *global = (ZVectorIterGlobal *) malloc(sizeof(struct ZVectorIterGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorIterClass));
		memset(global->_class, 0, sizeof(struct ZVectorIterClass));
		global->name = "ZVectorIter";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZVectorIter temp;
		unsigned long offset = 0;

		unsigned long *class_off_list;
		unsigned long class_off_size = 0;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			if (p_class->id > class_off_size)
				class_off_size = p_class->id;
		}
		class_off_list = malloc(sizeof(unsigned long) * (class_off_size+1));
		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
			class_off_list[p_class->id] = offset;
			offset += sizeof(struct ZObjectClass);
		}
		((ZObjectClass *) global->_class)->class_off_list = class_off_list;
		if (z_vector_iter_type_id == -1)
			z_vector_iter_type_id = zco_allocate_type_id();
		global->id = z_vector_iter_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_vector_iter_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_vector_iter_type_id);
		*global_ptr = global;
		
#line 25 "z-vector-iter.zco"
		{
#line 25 "z-vector-iter.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 25 "z-vector-iter.zco"
			global->__parent_reset = p_class->__reset;
#line 25 "z-vector-iter.zco"
			p_class->__reset = z_vector_iter_reset;
#line 25 "z-vector-iter.zco"
		}
#line 34 "z-vector-iter.zco"
		{
#line 34 "z-vector-iter.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 34 "z-vector-iter.zco"
			global->__parent_dispose = p_class->__dispose;
#line 34 "z-vector-iter.zco"
			p_class->__dispose = z_vector_iter_dispose;
#line 34 "z-vector-iter.zco"
		}
		__z_vector_iter_class_init(ctx, (ZVectorIterClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_userdata(global->method_map, global->method_map);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 41 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 47 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("dup"), (ZObjectSignalHandler) dup);
#line 121 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("assign"), (ZObjectSignalHandler) assign);
#line 132 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("advance"), (ZObjectSignalHandler) advance);
#line 177 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("increment"), (ZObjectSignalHandler) increment);
#line 212 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("decrement"), (ZObjectSignalHandler) decrement);
#line 230 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_equal"), (ZObjectSignalHandler) is_equal);
#line 235 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_lte"), (ZObjectSignalHandler) is_lte);
#line 256 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_gte"), (ZObjectSignalHandler) is_gte);
#line 279 "z-vector-iter.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_in_bound"), (ZObjectSignalHandler) is_in_bound);
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
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 18 "z-vector-iter.zco"
static void z_vector_iter_init(Self *self)
{
 selfp->index = 0;
 selfp->absolute_index = 0;
 selfp->segment = 0;
 }
#line 25 "z-vector-iter.zco"
#define PARENT_HANDLER self->_global->__parent_reset
static void  z_vector_iter_reset(ZObject *object)
{
 Self *self = (Self *) object;
 selfp->index = 0;
 selfp->absolute_index = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 34 "z-vector-iter.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_vector_iter_dispose(ZObject *object)
{
 Self *self = (Self *) object;
 set_segment(self, NULL);
 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 41 "z-vector-iter.zco"
Self * z_vector_iter_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 47 "z-vector-iter.zco"
Self * z_vector_iter_dup(ZVectorIter *src)
{
 Self *self = GET_NEW(src->_global->ctx);
 assign(self, src);
 return self;
 }
#line 56 "z-vector-iter.zco"
ZVectorSegment * z_vector_iter_get_segment(Self *self)
{
 if (selfp->segment)
 z_object_ref(Z_OBJECT(selfp->segment));

 return selfp->segment;
 }
#line 63 "z-vector-iter.zco"
void z_vector_iter_set_segment(Self *self, ZVectorSegment * value)
{
 if (value)
 z_object_ref(Z_OBJECT(value));

 if (selfp->segment)
 z_object_unref(Z_OBJECT(selfp->segment));

 selfp->segment = value;
 }
#line 77 "z-vector-iter.zco"
int  z_vector_iter_get_absolute_index(Self *self)
{
 return selfp->absolute_index;
 }
#line 81 "z-vector-iter.zco"
void z_vector_iter_set_absolute_index(Self *self, int  value)
{
 if (selfp->absolute_index != value)
 advance(self, value - selfp->absolute_index);
 }
#line 90 "z-vector-iter.zco"
int  z_vector_iter_get_index(Self *self)
{
 return selfp->index;
 }
#line 94 "z-vector-iter.zco"
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
#line 121 "z-vector-iter.zco"
void  z_vector_iter_assign(Self *self,ZVectorIter *src)
{
 ZVectorSegment *segment = get_segment(src);
 set_segment(self, segment);

 if (segment)
 z_object_unref(Z_OBJECT(segment));

 set_index(self, get_index(src));
 }
#line 132 "z-vector-iter.zco"
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
#line 177 "z-vector-iter.zco"
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
#line 212 "z-vector-iter.zco"
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
#line 230 "z-vector-iter.zco"
int  z_vector_iter_is_equal(Self *self,Self *other)
{
 return selfp->segment == other->_priv.segment && selfp->index == get_index(other);
 }
#line 235 "z-vector-iter.zco"
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
#line 256 "z-vector-iter.zco"
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
#line 279 "z-vector-iter.zco"
int  z_vector_iter_is_in_bound(ZVectorIter *self)
{
 return z_vector_segment_is_in_bound(selfp->segment, self);
 }

#line 283 "z-vector-iter.zco"


