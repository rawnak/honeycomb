/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-string.h: Bootstrap file for z-string.zco
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

#ifndef _Z_STRING_H_
#define _Z_STRING_H_

#include <stdint.h>
#include <stdarg.h>
#include <z-object.h>
#include <z-vector.h>
#include <z-string-iter.h>


#define Z_STRING_FLAG_CASE_INSENSITIVE 0x1
#define Z_STRING_FLAG_NEGATIVE 0x2

enum ZStringEncoding
{
 Z_STRING_ENCODING_UTF8 = 1,
 Z_STRING_ENCODING_ASCII,
};


#include <zco-type.h>
#define Self ZString
#define Z_STRING(s) ((ZString *) (s))


struct ZStringPrivate;
struct ZStringProtected;
struct ZStringGlobal;
struct ZStringClass;
struct ZString;

typedef struct ZStringPrivate ZStringPrivate;
typedef struct ZStringProtected ZStringProtected;
typedef struct ZStringGlobal ZStringGlobal;
typedef struct ZStringClass ZStringClass;
typedef struct ZString ZString;

struct ZStringPrivate {
	ZVector *data;
	int length;
	ZStringIter *token_it;
};

struct ZStringProtected {
};

struct ZStringGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZStringClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void  (*__parent_dispose)(ZObject *object);
};

struct ZStringClass {
	struct ZObjectClass parent_z_object;
};

struct ZString {
	struct ZObject parent_z_object;
	struct ZStringGlobal *_global;
	struct ZStringPrivate _priv;
	struct ZStringProtected _prot;
};
extern int z_string_type_id;
ZStringGlobal * z_string_get_type(struct zco_context_t *ctx);
void __z_string_init(struct zco_context_t *ctx, ZString *self);
Self * z_string_new(struct zco_context_t *ctx);
Self * z_string_dup(Self *src);
int  z_string_is_in_bound(Self *self,ZStringIter *it);
int  z_string_validate(Self *self);
uint32_t  z_string_get_char(Self *self,ZStringIter *it);
void  z_string_set_char(Self *self,ZStringIter *it,uint32_t ch);
void  z_string_set_cstring(Self *self,const char *s,int encoding);
char * z_string_get_cstring(Self *self,int encoding);
void  z_string_append(Self *self,ZString *src,ZStringIter *first,ZStringIter *last);
void  z_string_insert(Self *self,ZStringIter *it,ZString *src,ZStringIter *first,ZStringIter *last);
void  z_string_erase(Self *self,ZStringIter *first,ZStringIter *last);
void  z_string_replace_with_chars(Self *self,ZStringIter *first,ZStringIter *last,int count,uint32_t ch);
void  z_string_replace(Self *self,ZStringIter *first,ZStringIter *last,ZString *src,ZStringIter *src_first,ZStringIter *src_last);
void  z_string_append_cstring(Self *self,const char *s,int encoding);
void  z_string_push_back(Self *self,uint32_t ch);
void  z_string_insert_char(Self *self,ZStringIter *it,int count,uint32_t ch);
int  z_string_compare(Self *self,ZStringIter *it,ZString *other,ZStringIter *other_iter,int flags,unsigned int count);
int  z_string_get_length(Self *self);
ZStringIter *  z_string_get_begin(Self *self);
ZStringIter *  z_string_get_end(Self *self);
void  z_string_clear(Self *self);
int  z_string_get_is_empty(Self *self);
int  z_string_find(Self *self,ZStringIter *it,ZString *needle,int flags);
int  z_string_find_char(Self *self,ZStringIter *it,uint32_t ch,int flags);
int  z_string_find_any_char(Self *self,ZStringIter *it,ZString *list,int flags);
double  z_string_get_real64(Self *self,ZStringIter *first,ZStringIter *last);
int64_t  z_string_get_int64(Self *self,ZStringIter *first,ZStringIter *last,int base);
uint64_t  z_string_get_uint64(Self *self,ZStringIter *first,ZStringIter *last,int base);
int  z_string_append_vformat(Self *self,const char *fmt,va_list ap);
int  z_string_vformat(Self *self,const char *fmt,va_list ap);
void  z_string_append_format(Self *self,const char *fmt,...);
void  z_string_format(Self *self,const char *fmt,...);
void  z_string_token_start(Self *self);
int  z_string_token_next(Self *self,ZString *separator,ZStringIter *first,ZStringIter *last);

#undef Self


#endif
