/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-object.h: Bootstrap file for z-object.zco
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

#ifndef _Z_OBJECT_H_
#define _Z_OBJECT_H_

#define likely(x) __builtin_expect((x),1)
#define unlikely(x) __builtin_expect((x),0)

#include <zco-type.h>
#define Self ZObject
#define Z_OBJECT(s) ((ZObject *) (s))


struct ZObjectPrivate;
struct ZObjectProtected;
struct ZObjectGlobal;
struct ZObjectClass;
struct ZObject;

typedef struct ZObjectPrivate ZObjectPrivate;
typedef struct ZObjectProtected ZObjectProtected;
typedef struct ZObjectGlobal ZObjectGlobal;
typedef struct ZObjectClass ZObjectClass;
typedef struct ZObject ZObject;

struct ZObjectPrivate {
#line 15 "z-object.zco"
	unsigned int ref_count;
};

struct ZObjectProtected {
};

struct ZObjectGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZObjectClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
};

struct ZObjectClass {
#line 22 "z-object.zco"
	void  (*__dispose)(Self *self);
};

struct ZObject {
	struct ZObjectGlobal *_global;
	struct ZObjectPrivate _priv;
	struct ZObjectProtected _prot;
#line 13 "z-object.zco"
	void *class_base;
#line 14 "z-object.zco"
	int *vtable;
};
extern int z_object_type_id;
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx);
void __z_object_init(struct zco_context_t *ctx, ZObject *self);
#line 22 "z-object.zco"
void  z_object_dispose(Self *self);
#line 27 "z-object.zco"
void  z_object_ref(Self *self);
#line 32 "z-object.zco"
void  z_object_unref(Self *self);

#undef Self


#endif
