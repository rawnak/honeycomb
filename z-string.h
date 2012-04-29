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
#line 31 "z-string.zco"
	ZVector *data;
#line 32 "z-string.zco"
	int length;
#line 33 "z-string.zco"
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
#line 42 "z-string.zco"
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
#line 52 "z-string.zco"
Self * z_string_new(struct zco_context_t *ctx);
#line 58 "z-string.zco"
Self * z_string_dup(Self *src);
#line 65 "z-string.zco"
int  z_string_is_in_bound(Self *self,ZStringIter *it);
#line 71 "z-string.zco"
int  z_string_validate(Self *self);
#line 113 "z-string.zco"
uint32_t  z_string_get_char(Self *self,ZStringIter *it);
#line 122 "z-string.zco"
void  z_string_set_char(Self *self,ZStringIter *it,uint32_t ch);
#line 186 "z-string.zco"
void  z_string_set_cstring(Self *self,const char *s,int encoding);
#line 224 "z-string.zco"
char * z_string_get_cstring(Self *self,int encoding);
#line 277 "z-string.zco"
void  z_string_append(Self *self,ZString *src,ZStringIter *first,ZStringIter *last);
#line 284 "z-string.zco"
void  z_string_insert(Self *self,ZStringIter *it,ZString *src,ZStringIter *first,ZStringIter *last);
#line 315 "z-string.zco"
void  z_string_erase(Self *self,ZStringIter *first,ZStringIter *last);
#line 340 "z-string.zco"
void  z_string_replace_with_chars(Self *self,ZStringIter *first,ZStringIter *last,int count,uint32_t ch);
#line 346 "z-string.zco"
void  z_string_replace(Self *self,ZStringIter *first,ZStringIter *last,ZString *src,ZStringIter *src_first,ZStringIter *src_last);
#line 352 "z-string.zco"
void  z_string_append_cstring(Self *self,const char *s,int encoding);
#line 878 "z-string.zco"
void  z_string_push_back(Self *self,uint32_t ch);
#line 896 "z-string.zco"
void  z_string_insert_char(Self *self,ZStringIter *it,int count,uint32_t ch);
#line 929 "z-string.zco"
int  z_string_compare(Self *self,ZStringIter *it,ZString *other,ZStringIter *other_iter,int flags,unsigned int count);
#line 978 "z-string.zco"
int  z_string_get_length(Self *self);
#line 986 "z-string.zco"
ZStringIter *  z_string_get_begin(Self *self);
#line 995 "z-string.zco"
ZStringIter *  z_string_get_end(Self *self);
#line 1003 "z-string.zco"
void  z_string_clear(Self *self);
#line 1011 "z-string.zco"
int  z_string_get_is_empty(Self *self);
#line 1017 "z-string.zco"
int  z_string_find(Self *self,ZStringIter *it,ZString *needle,int flags);
#line 1063 "z-string.zco"
int  z_string_find_char(Self *self,ZStringIter *it,uint32_t ch,int flags);
#line 1117 "z-string.zco"
int  z_string_find_any_char(Self *self,ZStringIter *it,ZString *list,int flags);
#line 1164 "z-string.zco"
double  z_string_get_real64(Self *self,ZStringIter *first,ZStringIter *last);
#line 1245 "z-string.zco"
int64_t  z_string_get_int64(Self *self,ZStringIter *first,ZStringIter *last,int base);
#line 1345 "z-string.zco"
uint64_t  z_string_get_uint64(Self *self,ZStringIter *first,ZStringIter *last,int base);
#line 1581 "z-string.zco"
int  z_string_append_vformat(Self *self,const char *fmt,va_list ap);
#line 1649 "z-string.zco"
int  z_string_vformat(Self *self,const char *fmt,va_list ap);
#line 1655 "z-string.zco"
void  z_string_append_format(Self *self,const char *fmt,...);
#line 1664 "z-string.zco"
void  z_string_format(Self *self,const char *fmt,...);
#line 1673 "z-string.zco"
void  z_string_token_start(Self *self);
#line 1681 "z-string.zco"
int  z_string_token_next(Self *self,ZString *separator,ZStringIter *first,ZStringIter *last);

#undef Self


#endif
