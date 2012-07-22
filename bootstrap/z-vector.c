/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-vector.c: Bootstrap file for z-vector.zco
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


#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include <z-map.h>
#include <string.h>
#include <z-vector.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZVector
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_vector_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 26 "z-vector.zco"
#define init z_vector_init
#line 47 "z-vector.zco"
#define new z_vector_new
#line 67 "z-vector.zco"
#define set_item_construct z_vector_set_item_construct
#line 79 "z-vector.zco"
#define set_item_destruct z_vector_set_item_destruct
#line 89 "z-vector.zco"
#define set_userdata z_vector_set_userdata
#line 98 "z-vector.zco"
#define get_begin z_vector_get_begin
#line 109 "z-vector.zco"
#define get_end z_vector_get_end
#line 123 "z-vector.zco"
#define get_size z_vector_get_size
#line 127 "z-vector.zco"
#define set_size z_vector_set_size
#line 177 "z-vector.zco"
#define get_is_empty z_vector_get_is_empty
#line 187 "z-vector.zco"
#define get_capacity z_vector_get_capacity
#line 191 "z-vector.zco"
#define set_capacity z_vector_set_capacity
#line 220 "z-vector.zco"
#define is_in_bound z_vector_is_in_bound
#line 233 "z-vector.zco"
#define get_item z_vector_get_item
#line 253 "z-vector.zco"
#define set_item z_vector_set_item
#line 273 "z-vector.zco"
#define get_front z_vector_get_front
#line 280 "z-vector.zco"
#define set_front z_vector_set_front
#line 291 "z-vector.zco"
#define get_back z_vector_get_back
#line 300 "z-vector.zco"
#define set_back z_vector_set_back
#line 311 "z-vector.zco"
#define push_back z_vector_push_back
#line 324 "z-vector.zco"
#define pop_back z_vector_pop_back
#line 340 "z-vector.zco"
#define insert z_vector_insert
#line 375 "z-vector.zco"
#define insert_range z_vector_insert_range
#line 427 "z-vector.zco"
#define erase z_vector_erase
#line 471 "z-vector.zco"
#define erase1 z_vector_erase1
#line 484 "z-vector.zco"
#define erase1_increment z_vector_erase1_increment
#line 507 "z-vector.zco"
#define clear z_vector_clear

int z_vector_type_id = -1;

static Self *__z_vector_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_vector_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 26 "z-vector.zco"
static void z_vector_init(Self *self);
#line 37 "z-vector.zco"
static void  z_vector_dispose(ZObject *object);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZVectorGlobal * z_vector_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_vector_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_vector_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZVectorGlobal *global = (ZVectorGlobal *) malloc(sizeof(struct ZVectorGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZVectorClass));
		memset(global->_class, 0, sizeof(struct ZVectorClass));
		global->name = "ZVector";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZVector temp;

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
		if (z_vector_type_id == -1)
			z_vector_type_id = zco_allocate_type_id();
		global->id = z_vector_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_vector_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_vector_type_id);
		*global_ptr = global;
		
#line 37 "z-vector.zco"
		{
#line 37 "z-vector.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) global->_class + global->vtable_off_list[z_object_type_id]);
#line 37 "z-vector.zco"
			global->__parent_dispose = p_class->__dispose;
#line 37 "z-vector.zco"
			p_class->__dispose = z_vector_dispose;
#line 37 "z-vector.zco"
		}
		__z_vector_class_init(ctx, (ZVectorClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 47 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 220 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_in_bound"), (ZObjectSignalHandler) is_in_bound);
#line 233 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_item"), (ZObjectSignalHandler) get_item);
#line 253 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_item"), (ZObjectSignalHandler) set_item);
#line 311 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("push_back"), (ZObjectSignalHandler) push_back);
#line 324 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("pop_back"), (ZObjectSignalHandler) pop_back);
#line 340 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert"), (ZObjectSignalHandler) insert);
#line 375 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert_range"), (ZObjectSignalHandler) insert_range);
#line 427 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase"), (ZObjectSignalHandler) erase);
#line 471 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase1"), (ZObjectSignalHandler) erase1);
#line 484 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase1_increment"), (ZObjectSignalHandler) erase1_increment);
#line 507 "z-vector.zco"
		z_map_insert((ZMap *) global->method_map, strdup("clear"), (ZObjectSignalHandler) clear);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZVectorGlobal *) global);
		#endif
		return global;
	}
	return (ZVectorGlobal *) *global_ptr;
}

void __z_vector_class_init(struct zco_context_t *ctx, ZVectorClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_vector_init(struct zco_context_t *ctx, Self *self)
{
	struct ZVectorGlobal *_global = z_vector_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->global_base = (void *) _global;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 26 "z-vector.zco"
static void z_vector_init(Self *self)
{
 selfp->item_size = 0;
 selfp->count = 0;
 selfp->capacity = 0;
 selfp->data = 0;
 selfp->userdata = 0;
 selfp->item_construct = 0;
 selfp->item_destruct = 0;
 }
#line 37 "z-vector.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_vector_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 clear(self);
 set_capacity(self, 0);

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 47 "z-vector.zco"
Self * z_vector_new(struct zco_context_t *ctx,int item_size)
{
 Self *self = GET_NEW(ctx);

 if (item_size == 0) {
 selfp->storage_mode = 1;
 selfp->item_size = sizeof(void*);
 } else {
 selfp->storage_mode = 0;
 selfp->item_size = item_size;
 }

 return self;
 }
#line 67 "z-vector.zco"
void z_vector_set_item_construct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_construct = value;
 }
#line 79 "z-vector.zco"
void z_vector_set_item_destruct(Self *self, ZVectorItemCallback  value)
{
 selfp->item_destruct = value;
 }
#line 89 "z-vector.zco"
void z_vector_set_userdata(Self *self, void *  value)
{
 selfp->userdata = value;
 }
#line 98 "z-vector.zco"
ZVectorIter *  z_vector_get_begin(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 return iter;
 }
#line 109 "z-vector.zco"
ZVectorIter *  z_vector_get_end(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 z_vector_iter_set_index(iter, get_size(self));
 return iter;
 }
#line 123 "z-vector.zco"
int  z_vector_get_size(Self *self)
{
 return selfp->count;
 }
#line 127 "z-vector.zco"
void z_vector_set_size(Self *self, int  value)
{
 if (selfp->count < value) {
 /* grow the vector */
 if (selfp->capacity < value) {
 set_capacity(self, value);
 }

 if (selfp->item_construct) {
 int i;

 if (selfp->storage_mode == 0) {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * selfp->item_size;
 selfp->item_construct(selfp->data + offset, selfp->userdata);
 }
 } else {
 for (i = selfp->count; i < value; ++i) {
 int offset = i * selfp->item_size;
 selfp->item_construct(*((void **)(selfp->data + offset)), selfp->userdata);
 }
 }
 }

 } else if (selfp->count > value) {
 /* shrink the vector */
 if (selfp->item_destruct) {
 int i;

 if (selfp->storage_mode == 0) {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * selfp->item_size;
 selfp->item_destruct(selfp->data + offset, selfp->userdata);
 }
 } else {
 for (i = value; i < selfp->count; ++i) {
 int offset = i * selfp->item_size;
 selfp->item_destruct(*((void **)(selfp->data + offset)), selfp->userdata);
 }
 }
 }
 }

 selfp->count = value;
 }
#line 177 "z-vector.zco"
int  z_vector_get_is_empty(Self *self)
{
 return get_size(self) == 0;
 }
#line 187 "z-vector.zco"
int  z_vector_get_capacity(Self *self)
{
 return selfp->capacity;
 }
#line 191 "z-vector.zco"
void z_vector_set_capacity(Self *self, int  value)
{
 if (value < selfp->count) {
 set_size(self, value);
 selfp->count = value;
 }

 selfp->capacity = value;

 if (value) {
 if (selfp->data) {
 int copy_size = selfp->count * selfp->item_size;
 void *b = malloc(value * selfp->item_size);
 memcpy(b, selfp->data, copy_size);
 free(selfp->data);
 selfp->data = b;
 } else {
 selfp->data = malloc(value * selfp->item_size);
 }

 } else if (selfp->data) {
 free(selfp->data);
 selfp->data = NULL;
 }
 }
#line 220 "z-vector.zco"
int  z_vector_is_in_bound(Self *self,ZVectorIter *iter)
{
 int index = z_vector_iter_get_index(iter);

 if (index >= 0 && index < selfp->count)
 return 1;

 else
 return 0;
 }
#line 233 "z-vector.zco"
void *  z_vector_get_item(Self *self,ZVectorIter *iter)
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * selfp->item_size;

 if (is_in_bound(self, iter)) {
 if (selfp->storage_mode == 0)
 return selfp->data + offset;
 else
 return *((void **)(selfp->data + offset));

 } else {
 fprintf(stderr, "Index out of bound. max=%d, index=%d\n", selfp->count-1, index);
 }

 return NULL;
 }
#line 253 "z-vector.zco"
int  z_vector_set_item(Self *self,ZVectorIter *iter,void *item)
{
 int index = z_vector_iter_get_index(iter);
 int offset = index * selfp->item_size;

 if (index >= 0 && index < selfp->count) {
 if (selfp->storage_mode == 0)
 memcpy(selfp->data + offset, item, selfp->item_size);
 else
 memcpy(selfp->data + offset, &item, selfp->item_size);

 return 0;
 }

 return ERANGE;
 }
#line 273 "z-vector.zco"
void *  z_vector_get_front(Self *self)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;
 }
#line 280 "z-vector.zco"
void z_vector_set_front(Self *self, void *  value)
{
 ZVectorIter *iter = z_vector_iter_new(CTX);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
#line 291 "z-vector.zco"
void *  z_vector_get_back(Self *self)
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 void *item = get_item(self, iter);
 z_object_unref(Z_OBJECT(iter));
 return item;

 }
#line 300 "z-vector.zco"
void z_vector_set_back(Self *self, void *  value)
{
 ZVectorIter *iter = get_end(self);
 z_vector_iter_decrement(iter);
 set_item(self, iter, value);
 z_object_unref(Z_OBJECT(iter));
 }
#line 311 "z-vector.zco"
void  z_vector_push_back(Self *self,void *item)
{
 /*  increase the size of the vector by 1 */
 int size = get_size(self);
 set_size(self, size + 1);

 /* set the last item of the vector */
 set_back(self, item);
 }
#line 324 "z-vector.zco"
void  z_vector_pop_back(Self *self,void *item)
{
 if (item) {
 /* get the last item of the vector */
 void *d = get_back(self);
 memcpy(item, d, selfp->item_size);
 }

 /* decrease the size of the vector by 1 */
 int size = get_size(self);
 set_size(self, size - 1);
 }
#line 340 "z-vector.zco"
void  z_vector_insert(Self *self,ZVectorIter *iter,int n,void *item)
{
 /* make a copy of the iterator */
 ZVectorIter *it = z_vector_iter_dup(iter);

 /* increase the size of the vector */
 int size = get_size(self);
 set_size(self, size + n);

 /* shift all elements in [it,inf) forward */
 memmove(selfp->data + (z_vector_iter_get_index(it) + n) * selfp->item_size,
 selfp->data + z_vector_iter_get_index(it) * selfp->item_size,
 (size - z_vector_iter_get_index(it)) * selfp->item_size);

 int i;
 for (i=0; i<n; ++i) {
 set_item(self, it, item);
 z_vector_iter_increment(it);
 }

 z_object_unref(Z_OBJECT(it));
 }
#line 375 "z-vector.zco"
void  z_vector_insert_range(Self *self,ZVectorIter *iter,ZVector *src,ZVectorIter *src_iter_start,ZVectorIter *src_iter_end)
{
 ZVectorIter *it1, *it2;
 ZVectorIter *dest_it;

 /* make a copy of the iterators */
 if (iter == NULL)
 dest_it = get_end(self);
 else
 dest_it = z_vector_iter_dup(iter);

 if (src_iter_start == NULL)
 it1 = get_begin(src);
 else
 it1 = z_vector_iter_dup(src_iter_start);

 if (src_iter_end == NULL)
 it2 = get_end(src);
 else
 it2 = z_vector_iter_dup(src_iter_end);
 
 /* compute the item count */
 int n = z_vector_iter_get_index(it2) - z_vector_iter_get_index(it1);

 assert(n >= 0);

 /* increase the size of the vector */
 int size = get_size(self);
 set_size(self, size + n);

 /* shift all elements in [dest_it,inf) forward */
 memmove(selfp->data +
 (z_vector_iter_get_index(dest_it) + n) * selfp->item_size,
 selfp->data + z_vector_iter_get_index(dest_it) * selfp->item_size,
 (size - z_vector_iter_get_index(dest_it)) * selfp->item_size);

 /* insert the new item(s) */
 int i;
 for (i=0; i<n; ++i) {
 void *data = get_item(src, it1);
 set_item(self, dest_it, data);

 z_vector_iter_increment(dest_it);
 z_vector_iter_increment(it1);
 }

 z_object_unref(Z_OBJECT(it1));
 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(dest_it));
 }
#line 427 "z-vector.zco"
void  z_vector_erase(Self *self,ZVectorIter *start,ZVectorIter *end)
{
 ZVectorIter *it1;
 ZVectorIter *it2;
 
 /* compute the item count */
 int n = z_vector_iter_get_index(end) - z_vector_iter_get_index(start);

 if (n >= 0) {
 it1 = z_vector_iter_dup(start);
 it2 = z_vector_iter_dup(end);
 } else {
 it1 = z_vector_iter_dup(end);
 it2 = z_vector_iter_dup(start);
 n = -n;
 }

 /* call the item destructor on the items that is being removed */
 if (selfp->item_destruct) {
 ZVectorIter *temp = z_vector_iter_dup(it1);

 for (; !z_vector_iter_is_equal(temp, it2); z_vector_iter_increment(temp)) {
 void *item = get_item(self, temp);
 selfp->item_destruct(item, selfp->userdata);
 }

 z_object_unref(Z_OBJECT(temp));
 }

 /* shift all elements in [it1,inf) backward */
 int size = get_size(self);

 memmove(selfp->data + (z_vector_iter_get_index(it1)) * selfp->item_size,
 selfp->data + (z_vector_iter_get_index(it1) + n) * selfp->item_size,
 (size - z_vector_iter_get_index(it2)) * selfp->item_size);

 /* decrease the size of the vector */
 selfp->count = size - n;

 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));
 }
#line 471 "z-vector.zco"
void  z_vector_erase1(Self *self,ZVectorIter *iter)
{
 ZVectorIter *next = z_vector_iter_dup(iter);

 z_vector_iter_increment(next);
 erase(self, iter, next);

 z_object_unref(Z_OBJECT(next));
 }
#line 484 "z-vector.zco"
void  z_vector_erase1_increment(Self *self,ZVectorIter *iter)
{
 ZVectorIter *temp = z_vector_iter_new(CTX);

 if (z_vector_iter_is_equal(iter, temp)) {
 /* iterator is pointing to the first element of the vector */
 erase1(self, iter);

 z_object_unref(Z_OBJECT(temp));
 temp = get_begin(self);
 z_vector_iter_set_index(iter, z_vector_iter_get_index(temp));

 } else {
 z_vector_iter_set_index(temp, z_vector_iter_get_index(iter));
 z_vector_iter_decrement(iter);
 erase1(self, temp);
 z_vector_iter_increment(iter);
 }

 z_object_unref(Z_OBJECT(temp));
 }
#line 507 "z-vector.zco"
void  z_vector_clear(Self *self)
{
 set_size(self, 0);
 }


