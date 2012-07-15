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

struct ZObject;
typedef void(*ZObjectSignalHandler)(struct ZObject *self, ...);

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
#line 22 "z-object.zco"
	unsigned int ref_count;
#line 23 "z-object.zco"
	void *attached_properties;
#line 24 "z-object.zco"
	void *signal_map;
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
#line 33 "z-object.zco"
	void  (*__dispose)(Self *self);
};

struct ZObject {
	struct ZObjectGlobal *_global;
	struct ZObjectPrivate _priv;
	struct ZObjectProtected _prot;
#line 20 "z-object.zco"
	void *class_base;
#line 21 "z-object.zco"
	int *vtable;
};
extern int z_object_type_id;
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx);
void __z_object_init(struct zco_context_t *ctx, ZObject *self);
#line 33 "z-object.zco"
void  z_object_dispose(Self *self);
#line 70 "z-object.zco"
void  z_object_ref(Self *self);
#line 75 "z-object.zco"
void  z_object_unref(Self *self);
#line 82 "z-object.zco"
void *  z_object_connect(Self *self,char *name,ZObjectSignalHandler handler,void *userdata);
#line 104 "z-object.zco"
void  z_object_disconnect(Self *self,char *name,void *key);
#line 129 "z-object.zco"
void  z_object_register_signal(Self *self,char *name);
#line 152 "z-object.zco"
int  z_object_emit_signal(Self *self,char *name,void *argv);
#line 177 "z-object.zco"
void  z_object_add_attached_property_map(Self *self,void *map);

#undef Self


#endif
