/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-string.c: Bootstrap file for z-string.zco
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

#line 28 "z-string.zco"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include <limits.h>


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-string.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZString
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_string_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 36 "z-string.zco"
#define init z_string_init
#line 73 "z-string.zco"
#define new z_string_new
#line 79 "z-string.zco"
#define dup z_string_dup
#line 86 "z-string.zco"
#define is_in_bound z_string_is_in_bound
#line 92 "z-string.zco"
#define validate z_string_validate
#line 124 "z-string.zco"
#define get_char_ref z_string_get_char_ref
#line 136 "z-string.zco"
#define get_char z_string_get_char
#line 145 "z-string.zco"
#define set_char z_string_set_char
#line 209 "z-string.zco"
#define set_cstring z_string_set_cstring
#line 247 "z-string.zco"
#define get_cstring z_string_get_cstring
#line 307 "z-string.zco"
#define append z_string_append
#line 314 "z-string.zco"
#define insert z_string_insert
#line 347 "z-string.zco"
#define erase z_string_erase
#line 372 "z-string.zco"
#define replace_with_chars z_string_replace_with_chars
#line 378 "z-string.zco"
#define replace z_string_replace
#line 384 "z-string.zco"
#define append_cstring z_string_append_cstring
#line 394 "z-string.zco"
#define get_char_size z_string_get_char_size
#line 424 "z-string.zco"
#define encode z_string_encode
#line 483 "z-string.zco"
#define get_next_byte z_string_get_next_byte
#line 495 "z-string.zco"
#define strict_decode z_string_strict_decode
#line 722 "z-string.zco"
#define move_next z_string_move_next
#line 801 "z-string.zco"
#define decode z_string_decode
#line 910 "z-string.zco"
#define push_back z_string_push_back
#line 929 "z-string.zco"
#define insert_char z_string_insert_char
#line 955 "z-string.zco"
#define to_lower z_string_to_lower
#line 963 "z-string.zco"
#define compare z_string_compare
#line 1016 "z-string.zco"
#define get_length z_string_get_length
#line 1024 "z-string.zco"
#define get_begin z_string_get_begin
#line 1033 "z-string.zco"
#define get_end z_string_get_end
#line 1041 "z-string.zco"
#define clear z_string_clear
#line 1049 "z-string.zco"
#define get_is_empty z_string_get_is_empty
#line 1055 "z-string.zco"
#define find z_string_find
#line 1101 "z-string.zco"
#define find_char z_string_find_char
#line 1155 "z-string.zco"
#define find_any_char z_string_find_any_char
#line 1202 "z-string.zco"
#define get_real64 z_string_get_real64
#line 1283 "z-string.zco"
#define get_int64 z_string_get_int64
#line 1383 "z-string.zco"
#define get_uint64 z_string_get_uint64
#line 1477 "z-string.zco"
#define append_int z_string_append_int
#line 1507 "z-string.zco"
#define append_hex z_string_append_hex
#line 1558 "z-string.zco"
#define append_ptr z_string_append_ptr
#line 1620 "z-string.zco"
#define append_vformat z_string_append_vformat
#line 1687 "z-string.zco"
#define vformat z_string_vformat
#line 1693 "z-string.zco"
#define append_format z_string_append_format
#line 1702 "z-string.zco"
#define format z_string_format
#line 1711 "z-string.zco"
#define token_start z_string_token_start
#line 1719 "z-string.zco"
#define token_next z_string_token_next

int z_string_type_id = -1;

static Self *__z_string_new(struct zco_context_t *ctx)
{
	Self *self = NULL;
	ZObjectTracker *object_tracker = (ZObjectTracker *) ctx->object_tracker;
	if (object_tracker)
		self = (Self *) z_object_tracker_create(object_tracker, z_string_type_id);
	if (!self)
		self = (Self *) malloc(sizeof(Self));
	__z_string_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 36 "z-string.zco"
static void z_string_init(Self *self);
#line 45 "z-string.zco"
static void  z_string_reset(ZObject *object);
#line 61 "z-string.zco"
static void  z_string_dispose(ZObject *object);
#line 124 "z-string.zco"
static ZVectorIter *  z_string_get_char_ref(Self *self,ZStringIter *it);
#line 394 "z-string.zco"
static unsigned int  z_string_get_char_size(uint32_t ch);
#line 424 "z-string.zco"
static unsigned int  z_string_encode(uint32_t ch,uint8_t *buffer);
#line 483 "z-string.zco"
static uint8_t  z_string_get_next_byte(Self *self,ZVectorIter *it);
#line 495 "z-string.zco"
static uint32_t  z_string_strict_decode(Self *self,ZVectorIter *it,int *status);
#line 722 "z-string.zco"
static void  z_string_move_next(Self *self,ZVectorIter *it);
#line 801 "z-string.zco"
static uint32_t  z_string_decode(Self *self,ZVectorIter *it);
#line 955 "z-string.zco"
static uint32_t  z_string_to_lower(uint32_t ch);
#line 1477 "z-string.zco"
static void  z_string_append_int(Self *self,int val);
#line 1507 "z-string.zco"
static void  z_string_append_hex(Self *self,unsigned int val,int uppercase);
#line 1558 "z-string.zco"
static void  z_string_append_ptr(Self *self,void *val,int uppercase);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZStringGlobal * z_string_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_string_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_string_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZStringGlobal *global = (ZStringGlobal *) malloc(sizeof(struct ZStringGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZStringClass));
		memset(global->_class, 0, sizeof(struct ZStringClass));
		global->name = "ZString";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;
		global->is_object = 1;

		struct ZString temp;
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
		if (z_string_type_id == -1)
			z_string_type_id = zco_allocate_type_id();
		global->id = z_string_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_string_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_string_type_id);
		*global_ptr = global;
		
#line 45 "z-string.zco"
		{
#line 45 "z-string.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 45 "z-string.zco"
			global->__parent_reset = p_class->__reset;
#line 45 "z-string.zco"
			p_class->__reset = z_string_reset;
#line 45 "z-string.zco"
		}
#line 61 "z-string.zco"
		{
#line 61 "z-string.zco"
			ZObjectClass *p_class = &global->_class->parent_z_object;
#line 61 "z-string.zco"
			global->__parent_dispose = p_class->__dispose;
#line 61 "z-string.zco"
			p_class->__dispose = z_string_dispose;
#line 61 "z-string.zco"
		}
		__z_string_class_init(ctx, (ZStringClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_userdata(global->method_map, global->method_map);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 73 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 79 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("dup"), (ZObjectSignalHandler) dup);
#line 86 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("is_in_bound"), (ZObjectSignalHandler) is_in_bound);
#line 92 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("validate"), (ZObjectSignalHandler) validate);
#line 136 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_char"), (ZObjectSignalHandler) get_char);
#line 145 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_char"), (ZObjectSignalHandler) set_char);
#line 209 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_cstring"), (ZObjectSignalHandler) set_cstring);
#line 247 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_cstring"), (ZObjectSignalHandler) get_cstring);
#line 307 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("append"), (ZObjectSignalHandler) append);
#line 314 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert"), (ZObjectSignalHandler) insert);
#line 347 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("erase"), (ZObjectSignalHandler) erase);
#line 372 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("replace_with_chars"), (ZObjectSignalHandler) replace_with_chars);
#line 378 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("replace"), (ZObjectSignalHandler) replace);
#line 384 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("append_cstring"), (ZObjectSignalHandler) append_cstring);
#line 910 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("push_back"), (ZObjectSignalHandler) push_back);
#line 929 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("insert_char"), (ZObjectSignalHandler) insert_char);
#line 963 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("compare"), (ZObjectSignalHandler) compare);
#line 1041 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("clear"), (ZObjectSignalHandler) clear);
#line 1055 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("find"), (ZObjectSignalHandler) find);
#line 1101 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("find_char"), (ZObjectSignalHandler) find_char);
#line 1155 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("find_any_char"), (ZObjectSignalHandler) find_any_char);
#line 1202 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_real64"), (ZObjectSignalHandler) get_real64);
#line 1283 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_int64"), (ZObjectSignalHandler) get_int64);
#line 1383 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("get_uint64"), (ZObjectSignalHandler) get_uint64);
#line 1620 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("append_vformat"), (ZObjectSignalHandler) append_vformat);
#line 1687 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("vformat"), (ZObjectSignalHandler) vformat);
#line 1693 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("append_format"), (ZObjectSignalHandler) append_format);
#line 1702 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("format"), (ZObjectSignalHandler) format);
#line 1711 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("token_start"), (ZObjectSignalHandler) token_start);
#line 1719 "z-string.zco"
		z_map_insert((ZMap *) global->method_map, strdup("token_next"), (ZObjectSignalHandler) token_next);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZStringGlobal *) global);
		#endif
		return global;
	}
	return (ZStringGlobal *) *global_ptr;
}

void __z_string_class_init(struct zco_context_t *ctx, ZStringClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_string_init(struct zco_context_t *ctx, Self *self)
{
	struct ZStringGlobal *_global = z_string_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObjectClass *) _global->_class)->real_global = (void *) _global;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 36 "z-string.zco"
static void z_string_init(Self *self)
{
 selfp->data = z_vector_new(CTX);
 z_vector_set_item_size(selfp->data, sizeof(char));

 selfp->length = 0;
 selfp->token_it = 0;
 }
#line 45 "z-string.zco"
#define PARENT_HANDLER self->_global->__parent_reset
static void  z_string_reset(ZObject *object)
{
 Self *self = (Self *) object;

 if (selfp->token_it)
 z_object_unref(Z_OBJECT(selfp->token_it));

 z_object_reset(Z_OBJECT(selfp->data));
 z_vector_set_item_size(selfp->data, sizeof(char));

 selfp->length = 0;
 selfp->token_it = 0;

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 61 "z-string.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_string_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 if (selfp->token_it)
 z_object_unref(Z_OBJECT(selfp->token_it));

 z_object_unref(Z_OBJECT(selfp->data));

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 73 "z-string.zco"
Self * z_string_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 79 "z-string.zco"
Self * z_string_dup(Self *src)
{
 Self *self = GET_NEW(src->_global->ctx);
 append(self, src, NULL, NULL);
 return self;
 }
#line 86 "z-string.zco"
int  z_string_is_in_bound(Self *self,ZStringIter *it)
{
 int index = z_string_iter_get_index(it);
 return (index >= 0 && index < selfp->length);
 }
#line 92 "z-string.zco"
int  z_string_validate(Self *self)
{
 int status = 0;
 ZVectorIter *it, *first, *last;

 first = z_vector_get_begin(selfp->data);
 last = z_vector_get_end(selfp->data);

 selfp->length = 0;
 it = z_vector_iter_dup(first);

 while (!z_vector_iter_is_gte(it, last)) {
 strict_decode(self, it, &status);
 
 if (status != 0) {
 int new_size = z_vector_iter_get_absolute_index(it) - z_vector_iter_get_absolute_index(first);
 z_vector_set_size(selfp->data, new_size);
 assert(z_vector_iter_is_lte(it, last));
 break;
 }

 ++selfp->length;
 assert(z_vector_iter_is_lte(it, last));
 }

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(first));
 z_object_unref(Z_OBJECT(last));

 return status;
 }
#line 124 "z-string.zco"
static ZVectorIter *  z_string_get_char_ref(Self *self,ZStringIter *it)
{
 ZVectorIter *ptr = z_vector_get_begin(selfp->data);
 int i, count = z_string_iter_get_index(it);

 for (i=0; i<count; ++i) {
 move_next(self, ptr);
 }

 return ptr;
 }
#line 136 "z-string.zco"
uint32_t  z_string_get_char(Self *self,ZStringIter *it)
{
 ZVectorIter *ptr = get_char_ref(self, it);
 uint32_t ch = decode(self, ptr);

 z_object_unref(Z_OBJECT(ptr));
 return ch;
 }
#line 145 "z-string.zco"
void  z_string_set_char(Self *self,ZStringIter *it,uint32_t ch)
{
 int i;

 /* encode the new unicode character as utf-8 and get its size in bytes */
 uint8_t buffer[6];
 int new_size = encode(ch, buffer);

 if (new_size == 0) {
 fputs("invalid unicode character\n", stderr);
 abort();
 }

 /* get a reference of the character that we want to replace */
 ZVectorIter *ptr = get_char_ref(self, it);

 /* get the size of the current unicode character */
 ZVectorIter *tmp_ptr = z_vector_iter_dup(ptr);
 int start_idx = z_vector_iter_get_absolute_index(tmp_ptr);
 move_next(self, tmp_ptr);
 int old_size = z_vector_iter_get_absolute_index(tmp_ptr) - start_idx;
 z_object_unref(Z_OBJECT(tmp_ptr));

 if (old_size == new_size) {
 /* the old character and the new character takes the same amount of
			   space */

 for (i=0; i<new_size; ++i) {
 z_vector_set_item(selfp->data, ptr, buffer+i);
 z_vector_iter_increment(ptr);
 }

 } else if (old_size < new_size) {
 /* the new character takes more space. we need to insert some elements
			   into the vector */

 uint8_t dummy = 0;
 z_vector_insert(selfp->data, ptr, new_size-old_size, &dummy);

 for (i=0; i<new_size; ++i) {
 z_vector_set_item(selfp->data, ptr, buffer+i);
 z_vector_iter_increment(ptr);
 }


 } else if (old_size > new_size) {
 /* the new character takes less space. we need to rmeove some elements
			   from the vector */

 ZVectorIter *the_end = z_vector_iter_dup(ptr);
 z_vector_iter_advance(the_end, old_size);

 for (i=0; i<new_size; ++i) {
 z_vector_set_item(selfp->data, ptr, buffer+i);
 z_vector_iter_increment(ptr);
 }

 z_vector_erase(selfp->data, ptr, the_end);
 z_object_unref(Z_OBJECT(the_end));
 }

 z_object_unref(Z_OBJECT(ptr));
 }
#line 209 "z-string.zco"
void  z_string_set_cstring(Self *self,const char *s,int encoding)
{
 const uint8_t *ch;

 assert(s != NULL);
 clear(self);

 switch(encoding)
 {
 case Z_STRING_ENCODING_UTF8:
 ch = (uint8_t *) s;

 while (*ch) {
 int i, char_size = get_char_size(*ch);

 /* bad encoding */
 if (char_size == 0)
 break;

 for (i=0; i<char_size; ++i) {
 z_vector_push_back(selfp->data, (void *) (ch+i));
 }

 ch = ch + char_size;
 ++selfp->length;
 }
 break;

 case Z_STRING_ENCODING_ASCII:
 for (ch = (uint8_t *) s; *ch; ++ch) {
 push_back(self, *ch);
 }
 break;
 default:
 fputs("Invalid encoding\n", stderr);
 }
 }
#line 247 "z-string.zco"
char * z_string_get_cstring(Self *self,int encoding)
{
 ZVectorIter *it, *last;
 char *buffer;
 int i, size;

 if (get_length(self) == 0) {
 buffer = malloc(1);
 buffer[0] = 0;
 return buffer;
 }

 it = z_vector_get_begin(selfp->data);
 last = z_vector_get_end(selfp->data);
 i = 0;

 switch(encoding)
 {
 case Z_STRING_ENCODING_UTF8:
 size = z_vector_get_size(selfp->data);
 buffer = malloc(size + 1);

 while (!z_vector_iter_is_gte(it, last)) {
 void *p = z_vector_get_item(selfp->data, it);

 buffer[i] = *((char *) p);
 assert(i <= size);
 ++i;

 z_vector_iter_increment(it);
 assert(z_vector_iter_is_lte(it, last));
 }

 buffer[i] = 0;
 break;

 case Z_STRING_ENCODING_ASCII:
 size = selfp->length;
 buffer = malloc(size + 1);

 while (!z_vector_iter_is_gte(it, last)) {
 /* reinterpret cast from unsigned char to signed char */
 uint8_t ch = (uint8_t) decode(self, it);
 buffer[i] = *((char *) &ch);
 assert(i <= size);
 assert(z_vector_iter_is_lte(it, last));
 ++i;
 }

 buffer[i] = 0;
 break;
 default:
 fputs("Invalid encoding\n", stderr);
 }

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(last));
 return buffer;
 }
#line 307 "z-string.zco"
void  z_string_append(Self *self,ZString *src,ZStringIter *first,ZStringIter *last)
{
 ZStringIter *it = get_end(self);
 insert(self, it, src, first, last);
 z_object_unref(Z_OBJECT(it));
 }
#line 314 "z-string.zco"
void  z_string_insert(Self *self,ZStringIter *it,ZString *src,ZStringIter *first,ZStringIter *last)
{
 ZVectorIter *it1, *it2, *tmp, *pos;

 /* compute it1 */
 if (first)
 it1 = get_char_ref(src, first);
 else
 it1 = z_vector_get_begin(src->_priv.data);

 /* compute it2 */
 if (last)
 it2 = get_char_ref(src, last);
 else
 it2 = z_vector_get_end(src->_priv.data);

 /* compute new string length */
 tmp = z_vector_iter_dup(it1);
 while (!z_vector_iter_is_gte(tmp, it2)) {
 move_next(src, tmp);
 ++selfp->length;
 assert(z_vector_iter_is_lte(tmp, it2));
 }
 z_object_unref(Z_OBJECT(tmp));

 /* copy data */
 pos = get_char_ref(self, it);
 z_vector_insert_range(selfp->data, pos, src->_priv.data, it1, it2);
 z_object_unref(Z_OBJECT(pos));
 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));
 }
#line 347 "z-string.zco"
void  z_string_erase(Self *self,ZStringIter *first,ZStringIter *last)
{
 ZVectorIter *it1 = get_char_ref(self, first);
 ZVectorIter *it2 = get_char_ref(self, last);

 /* compute the size of the string that is to be removed */
 int diff = 0;
 ZVectorIter *tmp = z_vector_iter_dup(it1);
 while (!z_vector_iter_is_gte(tmp, it2)) {
 move_next(self, tmp);
 --diff;
 assert(z_vector_iter_is_lte(tmp, it2));
 }
 z_object_unref(Z_OBJECT(tmp));

 /* reduce the size of the string */
 selfp->length += diff;

 /* erase the characters */
 z_vector_erase(selfp->data, it1, it2);

 z_object_unref(Z_OBJECT(it1));
 z_object_unref(Z_OBJECT(it2));
 }
#line 372 "z-string.zco"
void  z_string_replace_with_chars(Self *self,ZStringIter *first,ZStringIter *last,int count,uint32_t ch)
{
 erase(self, first, last);
 insert_char(self, first, count, ch);
 }
#line 378 "z-string.zco"
void  z_string_replace(Self *self,ZStringIter *first,ZStringIter *last,ZString *src,ZStringIter *src_first,ZStringIter *src_last)
{
 erase(self, first, last);
 insert(self, first, src, src_first, src_last);
 }
#line 384 "z-string.zco"
void  z_string_append_cstring(Self *self,const char *s,int encoding)
{
 Self *tmp = new(CTX);

 set_cstring(tmp, s, encoding);
 append(self, tmp, NULL, NULL);

 z_object_unref(Z_OBJECT(tmp));
 }
#line 394 "z-string.zco"
static unsigned int  z_string_get_char_size(uint32_t ch)
{
 if (ch < 0x80) {
 /* 1 byte - 0aaaaaaa */
 return 1;

 } else if (ch < 0xe0) {
 /* 2 bytes - 00000bbb aaaaaaaa */
 return 2;

 } else if (ch < 0xf0) {
 /* 3 bytes - bbbbbbbb aaaaaaaa */
 return 3;

 } else if (ch < 0xf8) {
 /* 4 bytes - 000ccccc bbbbbbbb aaaaaaaa */
 return 4;

 } else if (ch < 0xfc) {
 /* 5 bytes - 000000dd cccccccc bbbbbbbb aaaaaaaa */
 return 5;
 } else if (ch < 0xfe) {
 /* 6 bytes - 0ddddddd cccccccc bbbbbbbb aaaaaaaa */
 return 6;
 } 

 return 0;
 }
#line 424 "z-string.zco"
static unsigned int  z_string_encode(uint32_t ch,uint8_t *buffer)
{
 switch (get_char_size(ch))
 {
 case 1:
 /* 1 byte - 0aaaaaaa => 0aaaaaaa */
 buffer[0] = ch;
 return 1;

 case 2:
 /* 2 bytes - 00000bbb aaaaaaaa => 110bbbaa 10aaaaaa */
 buffer[0] = 0xc0 | (ch >> 6);
 buffer[1] = 0x80 | (ch & 0x3f);
 return 2;

 case 3:
 /* 3 bytes - bbbbbbbb aaaaaaaa =>
				   1110bbbb 10bbbbaa 10aaaaaa */
 buffer[0] = 0xe0 | (ch >> 12);
 buffer[1] = 0x80 | ((ch >> 6) & 0x3f);
 buffer[2] = 0x80 | (ch & 0x3f);
 return 3;

 case 4:
 /* 4 bytes - 000ccccc bbbbbbbb aaaaaaaa =>
				   11110ccc 10ccbbbb 10bbbbaa 10aaaaaa */
 buffer[0] = 0xf0 | (ch >> 18);
 buffer[1] = 0x80 | ((ch >> 12) & 0x3f);
 buffer[2] = 0x80 | ((ch >> 6) & 0x3f);
 buffer[3] = 0x80 | (ch & 0x3f);
 return 4;

 case 5:
 /* 5 bytes - 000000dd cccccccc bbbbbbbb aaaaaaaa =>
				   111110dd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa */

 buffer[0] = 0xf8 | (ch >> 24); 
 buffer[1] = 0x80 | ((ch >> 18) & 0x3f);
 buffer[2] = 0x80 | ((ch >> 12) & 0x3f);
 buffer[3] = 0x80 | ((ch >> 6) & 0x3f);
 buffer[4] = 0x80 | (ch & 0x3f);
 return 5;

 case 6:
 /* 6 bytes - 0ddddddd cccccccc bbbbbbbb aaaaaaaa =>
				   1111110d 10dddddd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa */
 buffer[0] = 0xfc | (ch >> 30);
 buffer[1] = 0x80 | ((ch >> 24) & 0x3f);
 buffer[2] = 0x80 | ((ch >> 18) & 0x3f);
 buffer[3] = 0x80 | ((ch >> 12) & 0x3f);
 buffer[4] = 0x80 | ((ch >> 6) & 0x3f);
 buffer[5] = 0x80 | (ch & 0x3f);
 return 6;

 default:
 return 0;
 }
 }
#line 483 "z-string.zco"
static uint8_t  z_string_get_next_byte(Self *self,ZVectorIter *it)
{
 uint8_t byte = 0;

 if (z_vector_iter_is_in_bound(it)) {
 byte = *((uint8_t *) z_vector_get_item(selfp->data, it));
 z_vector_iter_increment(it);
 }

 return byte;
 }
#line 495 "z-string.zco"
static uint32_t  z_string_strict_decode(Self *self,ZVectorIter *it,int *status)
{
 uint32_t ch = 0;
 uint32_t b[6];

 b[0] = get_next_byte(self, it);

 if (*b < 0x80) {
 /* 1 byte - 0aaaaaaa => 0aaaaaaa */
 ch = *b;

 } else if (*b < 0xe0) {
 /* 2 bytes - 110bbbaa 10aaaaaa =>
			   00000bbb aaaaaaaa
			 
			   b0 << 6 = 00110bbb aa000000 
			   b1      = 00000000 10aaaaaa
			 */

 if ((b[0] & 0xe0) != 0xc0) {
 *status = -1;
 z_vector_iter_advance(it, -1);
 return 0;
 }

 b[1] = get_next_byte(self, it);
 if ((b[1] & 0xc0) != 0x80) {

 *status = -1;
 z_vector_iter_advance(it, -2);
 return 0;
 }

 ch = ((b[0] << 6) & 0x7c0) | (b[1] & 0x3f);

 } else if (*b < 0xf0) {
 /* 3 bytes - 1110bbbb 10bbbbaa 10aaaaaa =>
			   bbbbbbbb aaaaaaaa
			 
			   b0 << 12 = 00001110 bbbb0000 00000000
			   b1 << 6  = 00000000 0010bbbb aa000000
			   b2       = 00000000 00000000 10aaaaaa
			 */

 if ((b[0] & 0xf0) != 0xe0) {
 *status = -1;
 z_vector_iter_advance(it, -1);
 return 0;
 }

 b[1] = get_next_byte(self, it);
 if ((b[1] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -2);
 return 0;
 }

 b[2] = get_next_byte(self, it);
 if ((b[2] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -3);
 return 0;
 }

 ch = ((b[0] << 12) & 0xf000) |
 ((b[1] << 6) & 0xfc0) |
 (b[2] & 0x3f);

 } else if (*b < 0xf8) {
 /* 4 bytes - 11110ccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   000ccccc bbbbbbbb aaaaaaaa
			 
			   b0 << 18 = 00000011 110ccc00 00000000 00000000 
			   b1 << 12 = 00000000 000010cc bbbb0000 00000000
			   b2 << 6  = 00000000 00000000 0010bbbb aa000000
			   b3       = 00000000 00000000 00000000 10aaaaaa
			 */

 if ((b[0] & 0xf8) != 0xf0) {
 *status = -1;
 z_vector_iter_advance(it, -1);
 return 0;
 }

 b[1] = get_next_byte(self, it);
 if ((b[1] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -2);
 return 0;
 }

 b[2] = get_next_byte(self, it);
 if ((b[2] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -3);
 return 0;
 }

 b[3] = get_next_byte(self, it);
 if ((b[3] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -4);
 return 0;
 }

 ch = ((b[0] << 18) & 0x1c0000) |
 ((b[1] << 12) & 0x3f000) |
 ((b[2] << 6) & 0xfc0) |
 (b[3] & 0x3f);

 } else if (*b < 0xfc) { 
 /* 5 bytes - 111110dd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   000000dd cccccccc bbbbbbbb aaaaaaaa
			 
			   b0 << 24 = 111110dd 00000000 00000000 00000000
			   b1 << 18 = 00000010 cccccc00 00000000 00000000 
			   b2 << 12 = 00000000 000010cc bbbb0000 00000000
			   b3 << 6  = 00000000 00000000 0010bbbb aa000000
			   b4       = 00000000 00000000 00000000 10aaaaaa
			 */

 if ((b[0] & 0xfc) != 0xf8) {
 *status = -1;
 z_vector_iter_advance(it, -1);
 return 0;
 }

 b[1] = get_next_byte(self, it);
 if ((b[1] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -2);
 return 0;
 }

 b[2] = get_next_byte(self, it);
 if ((b[2] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -3);
 return 0;
 }

 b[3] = get_next_byte(self, it);
 if ((b[3] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -4);
 return 0;
 }

 b[4] = get_next_byte(self, it);
 if ((b[4] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -5);
 return 0;
 }

 ch = ((b[0] << 24) & 0x3000000) |
 ((b[1] << 18) & 0xfc0000) |
 ((b[2] << 12) & 0x3f000) |
 ((b[3] << 6) & 0xfc0) |
 (b[4] & 0x3f);

 } else if (*b < 0xfe) { 
 /* 6 bytes - 1111110d 10dddddd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   0ddddddd cccccccc bbbbbbbb aaaaaaaa 
			 
			   b0 << 30 = 00111111 0d000000 00000000 00000000 00000000 
			   b1 << 24 = 00000000 10dddddd 00000000 00000000 00000000
			   b2 << 18 = 00000000 00000010 cccccc00 00000000 00000000
			   b3 << 12 = 00000000 00000000 000010cc bbbb0000 00000000
			   b4 << 6  = 00000000 00000000 00000000 0010bbbb aa000000
			   b5       = 00000000 00000000 00000000 00000000 10aaaaaa
			 */

 if ((b[0] & 0xfe) != 0x8c) {
 *status = -1;
 z_vector_iter_advance(it, -1);
 return 0;
 }

 b[1] = get_next_byte(self, it);
 if ((b[1] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -2);
 return 0;
 }

 b[2] = get_next_byte(self, it);
 if ((b[2] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -3);
 return 0;
 }

 b[3] = get_next_byte(self, it);
 if ((b[3] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -4);
 return 0;
 }

 b[4] = get_next_byte(self, it);
 if ((b[4] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -5);
 return 0;
 }

 b[5] = get_next_byte(self, it);
 if ((b[5] & 0xc0) != 0x80) {
 *status = -1;
 z_vector_iter_advance(it, -6);
 return 0;
 }

 ch = ((b[0] << 30) & 0x40000000) |
 ((b[1] << 24) & 0x3f000000) |
 ((b[2] << 18) & 0xfc0000) |
 ((b[3] << 12) & 0x3f000) |
 ((b[4] << 6) & 0xfc0) |
 (b[5] & 0x3f);
 } 

 *status = 0;
 return ch;

 }
#line 722 "z-string.zco"
static void  z_string_move_next(Self *self,ZVectorIter *it)
{
 uint32_t b0 = get_next_byte(self, it);

 if (b0 < 0x80) {
 /* 1 byte - 0aaaaaaa => 0aaaaaaa */

 } else if (b0 < 0xe0) {
 /* 2 bytes - 110bbbaa 10aaaaaa =>
			   00000bbb aaaaaaaa
			 
			   b1 << 6 = 00110bbb aa000000 
			   b0      = 00000000 10aaaaaa
			 */

 get_next_byte(self, it);

 } else if (b0 < 0xf0) {
 /* 3 bytes - 1110bbbb 10bbbbaa 10aaaaaa =>
			   bbbbbbbb aaaaaaaa
			 
			   b0 << 12 = 00001110 bbbb0000 00000000
			   b1 << 6  = 00000000 0010bbbb aa000000
			   b2       = 00000000 00000000 10aaaaaa
			 */

 get_next_byte(self, it);
 get_next_byte(self, it);

 } else if (b0 < 0xf8) {
 /* 4 bytes - 11110ccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   000ccccc bbbbbbbb aaaaaaaa
			 
			   b0 << 18 = 00000011 110ccc00 00000000 00000000 
			   b1 << 12 = 00000000 000010cc bbbb0000 00000000
			   b2 << 6  = 00000000 00000000 0010bbbb aa000000
			   b3       = 00000000 00000000 00000000 10aaaaaa
			 */

 get_next_byte(self, it);
 get_next_byte(self, it);
 get_next_byte(self, it);

 } else if (b0 < 0xfc) { 
 /* 5 bytes - 111110dd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   000000dd cccccccc bbbbbbbb aaaaaaaa
			 
			   b0 << 24 = 111110dd 00000000 00000000 00000000
			   b1 << 18 = 00000010 cccccc00 00000000 00000000 
			   b2 << 12 = 00000000 000010cc bbbb0000 00000000
			   b3 << 6  = 00000000 00000000 0010bbbb aa000000
			   b4       = 00000000 00000000 00000000 10aaaaaa
			 */

 get_next_byte(self, it);
 get_next_byte(self, it);
 get_next_byte(self, it);
 get_next_byte(self, it);

 } else if (b0 < 0xfe) { 
 /* 6 bytes - 1111110d 10dddddd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   0ddddddd cccccccc bbbbbbbb aaaaaaaa 
			 
			   b0 << 30 = 00111111 0d000000 00000000 00000000 00000000 
			   b1 << 24 = 00000000 10dddddd 00000000 00000000 00000000
			   b2 << 18 = 00000000 00000010 cccccc00 00000000 00000000
			   b3 << 12 = 00000000 00000000 000010cc bbbb0000 00000000
			   b4 << 6  = 00000000 00000000 00000000 0010bbbb aa000000
			   b5       = 00000000 00000000 00000000 00000000 10aaaaaa
			 */

 get_next_byte(self, it);
 get_next_byte(self, it);
 get_next_byte(self, it);
 get_next_byte(self, it);
 get_next_byte(self, it);
 } 
 }
#line 801 "z-string.zco"
static uint32_t  z_string_decode(Self *self,ZVectorIter *it)
{
 uint32_t ch = 0;
 uint32_t b[6];

 b[0] = get_next_byte(self, it);

 if (*b < 0x80) {
 /* 1 byte - 0aaaaaaa => 0aaaaaaa */
 ch = *b;

 } else if (*b < 0xe0) {
 /* 2 bytes - 110bbbaa 10aaaaaa =>
			   00000bbb aaaaaaaa
			 
			   b1 << 6 = 00110bbb aa000000 
			   b0      = 00000000 10aaaaaa
			 */

 b[1] = get_next_byte(self, it);

 ch = ((b[0] << 6) & 0x7c0) | (b[1] & 0x3f);

 } else if (*b < 0xf0) {
 /* 3 bytes - 1110bbbb 10bbbbaa 10aaaaaa =>
			   bbbbbbbb aaaaaaaa
			 
			   b0 << 12 = 00001110 bbbb0000 00000000
			   b1 << 6  = 00000000 0010bbbb aa000000
			   b2       = 00000000 00000000 10aaaaaa
			 */

 b[1] = get_next_byte(self, it);
 b[2] = get_next_byte(self, it);

 ch = ((b[0] << 12) & 0xf000) |
 ((b[1] << 6) & 0xfc0) |
 (b[2] & 0x3f);

 } else if (*b < 0xf8) {
 /* 4 bytes - 11110ccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   000ccccc bbbbbbbb aaaaaaaa
			 
			   b0 << 18 = 00000011 110ccc00 00000000 00000000 
			   b1 << 12 = 00000000 000010cc bbbb0000 00000000
			   b2 << 6  = 00000000 00000000 0010bbbb aa000000
			   b3       = 00000000 00000000 00000000 10aaaaaa
			 */

 b[1] = get_next_byte(self, it);
 b[2] = get_next_byte(self, it);
 b[3] = get_next_byte(self, it);

 ch = ((b[0] << 18) & 0x1c0000) |
 ((b[1] << 12) & 0x3f000) |
 ((b[2] << 6) & 0xfc0) |
 (b[3] & 0x3f);

 } else if (*b < 0xfc) { 
 /* 5 bytes - 111110dd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   000000dd cccccccc bbbbbbbb aaaaaaaa
			 
			   b0 << 24 = 111110dd 00000000 00000000 00000000
			   b1 << 18 = 00000010 cccccc00 00000000 00000000 
			   b2 << 12 = 00000000 000010cc bbbb0000 00000000
			   b3 << 6  = 00000000 00000000 0010bbbb aa000000
			   b4       = 00000000 00000000 00000000 10aaaaaa
			 */

 b[1] = get_next_byte(self, it);
 b[2] = get_next_byte(self, it);
 b[3] = get_next_byte(self, it);
 b[4] = get_next_byte(self, it);

 ch = ((b[0] << 24) & 0x3000000) |
 ((b[1] << 18) & 0xfc0000) |
 ((b[2] << 12) & 0x3f000) |
 ((b[3] << 6) & 0xfc0) |
 (b[4] & 0x3f);

 } else if (*b < 0xfe) { 
 /* 6 bytes - 1111110d 10dddddd 10cccccc 10ccbbbb 10bbbbaa 10aaaaaa =>
			   0ddddddd cccccccc bbbbbbbb aaaaaaaa 
			 
			   b0 << 30 = 00111111 0d000000 00000000 00000000 00000000 
			   b1 << 24 = 00000000 10dddddd 00000000 00000000 00000000
			   b2 << 18 = 00000000 00000010 cccccc00 00000000 00000000
			   b3 << 12 = 00000000 00000000 000010cc bbbb0000 00000000
			   b4 << 6  = 00000000 00000000 00000000 0010bbbb aa000000
			   b5       = 00000000 00000000 00000000 00000000 10aaaaaa
			 */

 b[1] = get_next_byte(self, it);
 b[2] = get_next_byte(self, it);
 b[3] = get_next_byte(self, it);
 b[4] = get_next_byte(self, it);
 b[5] = get_next_byte(self, it);

 ch = ((b[0] << 30) & 0x40000000) |
 ((b[1] << 24) & 0x3f000000) |
 ((b[2] << 18) & 0xfc0000) |
 ((b[3] << 12) & 0x3f000) |
 ((b[4] << 6) & 0xfc0) |
 (b[5] & 0x3f);
 } 

 return ch;
 }
#line 910 "z-string.zco"
void  z_string_push_back(Self *self,uint32_t ch)
{
 uint8_t buffer[6];
 unsigned int i, length;

 assert(ch != 0);
 length = encode(ch, buffer);

 if (length == 0) {
 fputs("invalid unicode character\n", stderr);
 abort();
 }

 for (i=0; i<length; ++i)
 z_vector_push_back(selfp->data, buffer+i);

 ++selfp->length;
 }
#line 929 "z-string.zco"
void  z_string_insert_char(Self *self,ZStringIter *it,int count,uint32_t ch)
{
 ZVectorIter *pos;
 int size, i, j;
 uint8_t b[6];

 assert(ch != 0);
 size = encode(ch, b);
 pos = get_char_ref(self, it);

 if (size == 1) {
 z_vector_insert(selfp->data, pos, count, b);

 } else {
 for (i = 0; i < count; ++i) {
 for (j = 0; j < size; ++j) {
 z_vector_insert(selfp->data, pos, 1, b + j);
 z_vector_iter_increment(pos);
 }
 }
 }

 selfp->length += count;
 z_object_unref(Z_OBJECT(pos));
 }
#line 955 "z-string.zco"
static uint32_t  z_string_to_lower(uint32_t ch)
{
 if (ch >= 'A' && ch <= 'Z')
 return ch + ('a' - 'A');

 return ch;
 }
#line 963 "z-string.zco"
int  z_string_compare(Self *self,ZStringIter *it,ZString *other,ZStringIter *other_iter,int flags,int64_t count)
{
 ZVectorIter *it1, *it2;
 uint32_t x1, x2;
 int64_t i;

 if (count == 0)
 /* special case that is not covered in the do-while loop below */
 return 0;

 if (count == -1)
 count = LONG_MAX;

 /* get the vector iterators that point to the characters we want to compare */
 if (it)
 it1 = get_char_ref(self, it);
 else
 it1 = z_vector_get_begin(selfp->data);

 if (other_iter)
 it2 = get_char_ref(other, other_iter);
 else
 it2 = z_vector_get_begin(other->_priv.data);

 if (flags & Z_STRING_FLAG_CASE_INSENSITIVE) {
 /* perform case insensitive search */
 for (i=0; i<count; ++i) {
 x1 = to_lower(decode(self, it1));
 x2 = to_lower(decode(other, it2));

 if (!x1 || x1 != x2)
 break;
 }

 } else {
 /* perform standard search */
 for (i=0; i<count; ++i) {
 x1 = decode(self, it1);
 x2 = decode(other, it2);

 if (!x1 || x1 != x2)
 break;
 }
 }

 z_object_unref(Z_OBJECT(it1));
 z_object_unref(Z_OBJECT(it2));

 return (int32_t) x1 - (int32_t) x2;
 }
#line 1016 "z-string.zco"
int  z_string_get_length(Self *self)
{
 return selfp->length;
 }
#line 1024 "z-string.zco"
ZStringIter *  z_string_get_begin(Self *self)
{
 ZStringIter *it = z_string_iter_new(CTX);
 return it;
 }
#line 1033 "z-string.zco"
ZStringIter *  z_string_get_end(Self *self)
{
 ZStringIter *it = z_string_iter_new(CTX);
 z_string_iter_set_index(it, selfp->length);
 return it;
 }
#line 1041 "z-string.zco"
void  z_string_clear(Self *self)
{
 z_vector_clear(selfp->data);
 selfp->length = 0;
 }
#line 1049 "z-string.zco"
int  z_string_get_is_empty(Self *self)
{
 return selfp->length == 0;
 }
#line 1055 "z-string.zco"
int  z_string_find(Self *self,ZStringIter *it,ZString *needle,int flags)
{
 ZStringIter *temp;
 int needlelen;
 uint32_t first_ch;

 needlelen = get_length(needle);

 /* always return TRUE for an empty needle */
 if (needlelen == 0)
 return 1;

 /* always return FALSE for an empty hay */
 if (selfp->length == 0)
 return 0;

 /* get the first character of the needle */
 temp = get_begin(needle);
 first_ch = get_char(needle, temp);
 z_object_unref(Z_OBJECT(temp));

 /* if the 'it' iterator was specified, start the search from that point. if it
		   was not specified, start from the beginning of the hay string */
 if (it)
 temp = z_string_iter_dup(it);
 else
 temp = get_begin(self);

 /* repeatedly locate the first character of the needle in the hay and then
		   do a string compare */
 do {
 if (compare(self, temp, needle, NULL, flags, needlelen) == 0) {
 if (it)
 z_string_iter_set_index(it, z_string_iter_get_index(temp));

 z_object_unref(Z_OBJECT(temp));
 return 1;
 }

 z_string_iter_increment(temp);
 } while (find_char(self, temp, first_ch, flags) != 0);

 z_object_unref(Z_OBJECT(temp));
 return 0;
 }
#line 1101 "z-string.zco"
int  z_string_find_char(Self *self,ZStringIter *it,uint32_t ch,int flags)
{
 ZStringIter *temp;
 uint32_t x;

 /* if the 'it' iterator was specified, start the search from that point. if it
		   was not specified, start from the beginning of the hay string */
 if (it)
 temp = z_string_iter_dup(it);
 else 
 temp = get_begin(self);

 /* iterate through the string to locate the character */
 ZVectorIter *ptr = get_char_ref(self, temp);

 if (flags & Z_STRING_FLAG_CASE_INSENSITIVE) {
 /* perform case insensitive search */
 uint32_t temp_ch = to_lower(ch);

 while(1) {
 x = decode(self, ptr);

 if (x && to_lower(x) != temp_ch)
 z_string_iter_increment(temp);
 else
 break;
 }
 } else {
 /* perform standard search */
 while(1) {
 x = decode(self, ptr);

 if (x && x != ch)
 z_string_iter_increment(temp);
 else
 break;
 }
 }

 z_object_unref(Z_OBJECT(ptr));

 if (x) {
 if (it)
 z_string_iter_set_index(it, z_string_iter_get_index(temp));

 z_object_unref(Z_OBJECT(temp));
 return 1;
 }

 /* no match found */
 z_object_unref(Z_OBJECT(temp));
 return 0;
 }
#line 1155 "z-string.zco"
int  z_string_find_any_char(Self *self,ZStringIter *it,ZString *list,int flags)
{
 ZStringIter *temp;
 ZVectorIter *ptr;
 uint32_t ch;

 temp = z_string_iter_dup(it);
 
 /* get the vector iterator from the string iterator */
 ptr = get_char_ref(self, temp);

 /* iterate over each character in the hay string */
 if (flags & Z_STRING_FLAG_NEGATIVE) {
 /* perform negative search */
 while ((ch = decode(self, ptr))) {
 /* break out of the loop if the character is not in the needle list */
 if (!find_char(list, NULL, ch, flags))
 break;

 z_string_iter_increment(temp);
 }
 } else {
 /* perform standard search */
 while ((ch = decode(self, ptr))) {
 /* break out of the loop if the character is in the needle list */
 if (find_char(list, NULL, ch, flags))
 break;

 z_string_iter_increment(temp);
 }
 }
 z_object_unref(Z_OBJECT(ptr));

 if (ch) {
 /* match found */
 if (it)
 z_string_iter_set_index(it, z_string_iter_get_index(temp));

 z_object_unref(Z_OBJECT(temp));
 return 1;
 }

 /* no match found */
 z_object_unref(Z_OBJECT(temp));
 return 0;
 }
#line 1202 "z-string.zco"
double  z_string_get_real64(Self *self,ZStringIter *first,ZStringIter *last)
{
 ZStringIter *it, *it2;
 ZVectorIter *ptr;
 double result;
 int64_t part = 0, whole = 0, fraction = 0;
 int i, radix_idx = -1, exp_idx = -1, sign = 1;

 if (first)
 it = z_string_iter_dup(first);
 else
 it = get_begin(self);

 if (last)
 it2 = z_string_iter_dup(last);
 else
 it2 = get_end(self);

 ptr = get_char_ref(self, it);

 for (i = 0; !z_string_iter_is_gte(it, it2); ++i) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x39) {
 part = part * 10 + (ch - 0x30);

 } else if (ch == 0x2d && i == 0) {
 sign = -1;

 } else if (ch == 0x2e && radix_idx == -1 && exp_idx == -1) {
 whole = part;
 part = 0;
 radix_idx = i;

 } else if ((ch & 0xffffffdf) == 0x45 && exp_idx == -1) {
 if (radix_idx != -1) {
 fraction = part;
 part = 0;
 exp_idx = i;

 } else {
 whole = part;
 part = 0;
 exp_idx = i;
 }

 } else {
 break;
 }
 }

 z_object_unref(Z_OBJECT(ptr));
 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(it2));

 if (exp_idx != -1) {
 if (radix_idx != -1)
 /* whole.fraction * 10 ^ part */
 result =
 (double)(whole * sign) * pow(10, (double)part) +
 ((double)fraction) * pow(10, (double)(radix_idx - i + 1 + part));

 else
 /* whole.0 * 10 ^ part */
 result = (double)(whole * sign) * pow(10, (double)part);

 } else {
 if (radix_idx != -1)
 /* whole.part */
 result = (double)(whole * sign) + ((double)part) * pow(10, (double)(radix_idx - i + 1));

 else
 /* part.0 */
 result = (double)(part * sign);
 }

 return result;
 }
#line 1283 "z-string.zco"
int64_t  z_string_get_int64(Self *self,ZStringIter *first,ZStringIter *last,int base)
{
 ZStringIter *it, *it2;
 ZVectorIter *ptr;
 int64_t result = 0;
 int i, sign = 1;

 if (first)
 it = z_string_iter_dup(first);
 else
 it = get_begin(self);

 if (last)
 it2 = z_string_iter_dup(last);
 else
 it2 = get_end(self);

 ptr = get_char_ref(self, it);

 switch (base) {
 case 2:
 for (; !z_string_iter_is_gte(it, it2);) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch == 0x30 && ch == 0x31)
 result = result * 2 + (ch - 0x30);
 else
 break;
 }
 break;

 case 8:
 for (; !z_string_iter_is_gte(it, it2);) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x38)
 result = result * 8 + (ch - 0x30);
 else
 break;
 }
 break;

 case 10:
 for (i = 0; !z_string_iter_is_gte(it, it2); ++i) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x39)
 result = result * 10 + (ch - 0x30);

 else if (ch == 0x2d && i == 0)
 sign = -1;

 else
 break;
 }

 result *= sign;
 break;

 case 16:
 for (; !z_string_iter_is_gte(it, it2);) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x39) {
 result = result * 16 + (ch - 0x30);

 } else {
 /* force character to be uppercase */
 ch = ch & 0xffffffdf;

 if (ch >= 0x41 && ch <= 0x46)
 result = result * 16 + (ch - 0x37);

 else
 break;
 }
 }
 break;

 default:
 fprintf(stderr, "Base %d not supported\n", base);
 abort();
 break;
 }
 
 z_object_unref(Z_OBJECT(ptr));
 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(it2));

 return result;
 }
#line 1383 "z-string.zco"
uint64_t  z_string_get_uint64(Self *self,ZStringIter *first,ZStringIter *last,int base)
{
 ZStringIter *it, *it2;
 ZVectorIter *ptr;
 int64_t result = 0;
 int i;

 if (first)
 it = z_string_iter_dup(first);
 else
 it = get_begin(self);

 if (last)
 it2 = z_string_iter_dup(last);
 else
 it2 = get_end(self);

 ptr = get_char_ref(self, it);

 switch (base) {
 case 2:
 for (; !z_string_iter_is_gte(it, it2);) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch == 0x30 && ch == 0x31)
 result = result * 2 + (ch - 0x30);
 else
 break;
 }
 break;

 case 8:
 for (; !z_string_iter_is_gte(it, it2);) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x38)
 result = result * 8 + (ch - 0x30);
 else
 break;
 }
 break;

 case 10:
 for (i = 0; !z_string_iter_is_gte(it, it2); ++i) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x39)
 result = result * 10 + (ch - 0x30);
 else
 break;
 }
 break;

 case 16:
 for (; !z_string_iter_is_gte(it, it2);) {
 uint32_t ch = decode(self, ptr);
 z_string_iter_increment(it);
 assert(z_string_iter_is_lte(it, it2));

 if (ch >= 0x30 && ch <= 0x39) {
 result = result * 16 + (ch - 0x30);

 } else {
 /* force character to be uppercase */
 ch = ch & 0xffffffdf;

 if (ch >= 0x41 && ch <= 0x46)
 result = result * 16 + (ch - 0x37);

 else
 break;
 }
 }
 break;

 default:
 fprintf(stderr, "Base %d not supported\n", base);
 abort();
 break;
 }
 
 z_object_unref(Z_OBJECT(ptr));
 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(it2));

 return result;
 }
#line 1477 "z-string.zco"
static void  z_string_append_int(Self *self,int val)
{
 int temp = 1000000000;
 int sum_of_digits = 0;

 /* for negative numbers */
 if (val < 0) {
 push_back(self, '-');
 val = -val;
 }

 while (temp > 0) {
 /* digit = floor(val / temp) */
 int digit = val / temp;

 /* sum_of_digits == 0 if all we encountered so far is '0' characters. this
			   allows us to omit the leading 0 digits */
 sum_of_digits += digit;
 if (sum_of_digits > 0)
 push_back(self, digit + '0');

 /* val' = val - floor(val / temp) * temp */
 val -= digit * temp;
 temp /= 10;
 }

 if (sum_of_digits == 0)
 push_back(self, '0');
 }
#line 1507 "z-string.zco"
static void  z_string_append_hex(Self *self,unsigned int val,int uppercase)
{
 int temp = 0x10000000;
 int sum_of_digits = 0;
 int a_minus_10 = 'a' - 10;
 int A_minus_10 = 'A' - 10;

 if (uppercase) {
 while (temp > 0) {
 /* digit = floor(val / temp) */
 int digit = val / temp;

 /* sum_of_digits == 0 if all we encountered so far is '0' characters. this
				   allows us to omit the leading 0 digits */
 sum_of_digits += digit;
 if (sum_of_digits > 0) {
 if (digit < 10)
 push_back(self, digit + '0');
 else
 push_back(self, digit + A_minus_10);
 }

 /* val' = val - floor(val / temp) * temp */
 val -= digit * temp;
 temp /= 16;
 }
 } else {
 while (temp > 0) {
 /* digit = floor(val / temp) */
 int digit = val / temp;

 /* sum_of_digits == 0 if all we encountered so far is '0' characters. this
				   allows us to omit the leading 0 digits */
 sum_of_digits += digit;
 if (sum_of_digits > 0) {
 if (digit < 10)
 push_back(self, digit + '0');
 else
 push_back(self, digit + a_minus_10);
 }

 /* val' = val - floor(val / temp) * temp */
 val -= digit * temp;
 temp /= 16;
 }
 }

 if (sum_of_digits == 0)
 push_back(self, '0');
 }
#line 1558 "z-string.zco"
static void  z_string_append_ptr(Self *self,void *val,int uppercase)
{
 long input;
 long temp;
 int sum_of_digits = 0;
 int a_minus_10 = 'a' - 10;
 int A_minus_10 = 'A' - 10;

 /* reinterpret cast the pointer into a 'long' type */
 input = *((long *) &val);

#if __WORDSIZE == 64
 temp = 0x1000000000000000L; /* 64-bit pointer */
#else
 temp = 0x10000000L; /* 32-bit pointer */
#endif

 if (uppercase) {
 while (temp > 0) {
 /* digit = floor(input / temp) */
 int digit = input / temp;

 /* sum_of_digits == 0 if all we encountered so far is '0' characters. this
				   allows us to omit the leading 0 digits */
 sum_of_digits += digit;
 if (sum_of_digits > 0) {
 if (digit < 10)
 push_back(self, digit + '0');
 else
 push_back(self, digit + A_minus_10);
 }

 /* input' = input - floor(input / temp) * temp */
 input -= digit * temp;
 temp /= 16;
 }
 } else {
 while (temp > 0) {
 /* digit = floor(input / temp) */
 int digit = input / temp;

 /* sum_of_digits == 0 if all we encountered so far is '0' characters. this
				   allows us to omit the leading 0 digits */
 sum_of_digits += digit;
 if (sum_of_digits > 0) {
 if (digit < 10)
 push_back(self, digit + '0');
 else
 push_back(self, digit + a_minus_10);
 }

 /* input' = input - floor(input / temp) * temp */
 input -= digit * temp;
 temp /= 16;
 }
 }

 if (sum_of_digits == 0)
 push_back(self, '0');

 }
#line 1620 "z-string.zco"
int  z_string_append_vformat(Self *self,const char *fmt,va_list ap)
{
 const char *p;
 int i;

 /* FIXME: add support for more format specifiers */

 p = fmt;
 while (*p) {
 if (p[0] == '%') {
 ++p;

 if (p[0] == '%') {
 z_vector_push_back(selfp->data, (void *) p);

 } else if (p[0] == 'd' || p[0] == 'i') {
 int val = va_arg(ap, int);
 append_int(self, val);

 } else if (p[0] == 'x') {
 int val = va_arg(ap, int);
 append_hex(self, val, 0);

 } else if (p[0] == 'X') {
 int val = va_arg(ap, int);
 append_hex(self, val, 1);

 } else if (p[0] == 'p') {
 void *val = va_arg(ap, void *);
 append_ptr(self, val, 0);

 } else if (p[0] == 'P') {
 void *val = va_arg(ap, void *);
 append_ptr(self, val, 1);

 } else if (p[0] == 'c') {
 int32_t val = va_arg(ap, int32_t);
 push_back(self, val);

 } else if (p[0] == 's') {
 char *val = va_arg(ap, char *);
 append_cstring(self, val, Z_STRING_ENCODING_ASCII);

 } else if (p[0] == 'S') {
 ZString *val = va_arg(ap, ZString *);
 append(self, val, NULL, NULL);
 }
 ++p;

 } else {
 int char_size = get_char_size(*p);

 /* bad encoding */
 if (char_size == 0)
 return -1;

 for (i=0; i<char_size; ++i)
 z_vector_push_back(selfp->data, (void *) (p+i));

 p += char_size;
 ++selfp->length;
 }
 }

 return 0;
 }
#line 1687 "z-string.zco"
int  z_string_vformat(Self *self,const char *fmt,va_list ap)
{
 clear(self);
 append_vformat(self, fmt, ap);
 }
#line 1693 "z-string.zco"
void  z_string_append_format(Self *self,const char *fmt,...)
{
 va_list ap;

 va_start(ap, fmt);
 append_vformat(self, fmt, ap);
 va_end(ap);
 }
#line 1702 "z-string.zco"
void  z_string_format(Self *self,const char *fmt,...)
{
 va_list ap;

 va_start(ap, fmt);
 vformat(self, fmt, ap);
 va_end(ap);
 }
#line 1711 "z-string.zco"
void  z_string_token_start(Self *self)
{
 if (selfp->token_it)
 z_object_unref(Z_OBJECT(selfp->token_it));

 selfp->token_it = get_begin(self);
 }
#line 1719 "z-string.zco"
int  z_string_token_next(Self *self,ZString *separator,ZStringIter *first,ZStringIter *last)
{
 z_string_iter_set_index(first, z_string_iter_get_index(selfp->token_it));

 if (separator && find(self, selfp->token_it, separator, 0) != 0) {
 /* match found */
 z_string_iter_set_index(last, z_string_iter_get_index(selfp->token_it));
 z_string_iter_advance(selfp->token_it, get_length(separator));

 return is_in_bound(self, selfp->token_it);
 }

 /* no matches found */
 ZStringIter *temp = get_end(self);
 z_string_iter_set_index(last, z_string_iter_get_index(temp));
 z_object_unref(Z_OBJECT(temp));

 return 0;

 }

#line 1739 "z-string.zco"


