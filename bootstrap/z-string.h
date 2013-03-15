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
#line 18 "z-string.zco"

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
#define Z_STRING(s) ((ZString *) ((char *) (s) + GLOBAL_FROM_OBJECT(s)->common.vtable_off_list[z_string_type_id]))


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
#line 32 "z-string.zco"
	ZVector *data;
#line 33 "z-string.zco"
	int length;
#line 34 "z-string.zco"
	ZStringIter *token_it;
};

struct ZStringProtected {
};

struct ZStringGlobal {
	struct ZCommonGlobal common;
	struct ZStringClass *_class;
#line 45 "z-string.zco"
	void  (*__parent_reset)(ZObject *object);
#line 63 "z-string.zco"
	void  (*__parent_dispose)(ZObject *object);
#line 1741 "z-string.zco"
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
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
void __z_string_class_init(struct zco_context_t *ctx, ZStringClass *_class);
#line 75 "z-string.zco"
Self * z_string_new(struct zco_context_t *ctx);
#line 81 "z-string.zco"
Self * z_string_dup(Self *src);
#line 88 "z-string.zco"
int  z_string_is_in_bound(Self *self,ZStringIter *it);
#line 94 "z-string.zco"
int  z_string_validate(Self *self);
#line 138 "z-string.zco"
uint32_t  z_string_get_char(Self *self,ZStringIter *it);
#line 147 "z-string.zco"
void  z_string_set_char(Self *self,ZStringIter *it,uint32_t ch);
#line 211 "z-string.zco"
void  z_string_set_cstring(Self *self,const char *s,int encoding);
#line 249 "z-string.zco"
char * z_string_get_cstring(Self *self,int encoding);
#line 309 "z-string.zco"
void  z_string_append(Self *self,ZString *src,ZStringIter *first,ZStringIter *last);
#line 316 "z-string.zco"
void  z_string_insert(Self *self,ZStringIter *it,ZString *src,ZStringIter *first,ZStringIter *last);
#line 349 "z-string.zco"
void  z_string_erase(Self *self,ZStringIter *first,ZStringIter *last);
#line 374 "z-string.zco"
void  z_string_replace_with_chars(Self *self,ZStringIter *first,ZStringIter *last,int count,uint32_t ch);
#line 380 "z-string.zco"
void  z_string_replace(Self *self,ZStringIter *first,ZStringIter *last,ZString *src,ZStringIter *src_first,ZStringIter *src_last);
#line 386 "z-string.zco"
void  z_string_append_cstring(Self *self,const char *s,int encoding);
#line 912 "z-string.zco"
void  z_string_push_back(Self *self,uint32_t ch);
#line 931 "z-string.zco"
void  z_string_insert_char(Self *self,ZStringIter *it,int count,uint32_t ch);
#line 965 "z-string.zco"
int  z_string_compare(Self *self,ZStringIter *it,ZString *other,ZStringIter *other_iter,int flags,int64_t count);
#line 1018 "z-string.zco"
int  z_string_get_length(Self *self);
#line 1026 "z-string.zco"
ZStringIter *  z_string_get_begin(Self *self);
#line 1035 "z-string.zco"
ZStringIter *  z_string_get_end(Self *self);
#line 1043 "z-string.zco"
void  z_string_clear(Self *self);
#line 1051 "z-string.zco"
int  z_string_get_is_empty(Self *self);
#line 1057 "z-string.zco"
int  z_string_find(Self *self,ZStringIter *it,ZString *needle,int flags);
#line 1103 "z-string.zco"
int  z_string_find_char(Self *self,ZStringIter *it,uint32_t ch,int flags);
#line 1157 "z-string.zco"
int  z_string_find_any_char(Self *self,ZStringIter *it,ZString *list,int flags);
#line 1204 "z-string.zco"
double  z_string_get_real64(Self *self,ZStringIter *first,ZStringIter *last);
#line 1285 "z-string.zco"
int64_t  z_string_get_int64(Self *self,ZStringIter *first,ZStringIter *last,int base);
#line 1385 "z-string.zco"
uint64_t  z_string_get_uint64(Self *self,ZStringIter *first,ZStringIter *last,int base);
#line 1622 "z-string.zco"
int  z_string_append_vformat(Self *self,const char *fmt,va_list ap);
#line 1689 "z-string.zco"
int  z_string_vformat(Self *self,const char *fmt,va_list ap);
#line 1695 "z-string.zco"
void  z_string_append_format(Self *self,const char *fmt,...);
#line 1704 "z-string.zco"
void  z_string_format(Self *self,const char *fmt,...);
#line 1713 "z-string.zco"
void  z_string_token_start(Self *self);
#line 1721 "z-string.zco"
int  z_string_token_next(Self *self,ZString *separator,ZStringIter *first,ZStringIter *last);

#undef Self


#endif
