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
#line 10 "z-object.zco"

#define likely(x) __builtin_expect((x),1)
#define unlikely(x) __builtin_expect((x),0)

struct ZObject;
typedef void(*ZObjectSignalHandler)(struct ZObject *self, ...);

struct ZMemoryAllocator;
typedef struct ZMemoryAllocator ZMemoryAllocator;

#include <zco-type.h>
#define Self ZObject
#define Z_OBJECT(s) ((ZObject *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_object_type_id]))


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
#line 27 "z-object.zco"
	unsigned int ref_count;
#line 28 "z-object.zco"
	void *attached_properties;
#line 29 "z-object.zco"
	void *signal_map;
#line 30 "z-object.zco"
	ZMemoryAllocator *allocator;
};

struct ZObjectProtected {
};

struct ZObjectGlobal {
	struct ZCommonGlobal common;
	struct ZObjectClass *_class;
};

struct ZObjectClass {
	ZCommonGlobal * real_global;
#line 40 "z-object.zco"
	void  (*__class_destroy)(ZObjectGlobal *gbl);
#line 75 "z-object.zco"
	void  (*__reset)(Self *self);
#line 90 "z-object.zco"
	void  (*__dispose)(Self *self);
};

struct ZObject {
	struct ZObjectGlobal *_global;
	struct ZObjectPrivate _priv;
	struct ZObjectProtected _prot;
#line 25 "z-object.zco"
	void *class_base;
#line 26 "z-object.zco"
};
extern int z_object_type_id;
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx);
void __z_object_init(struct zco_context_t *ctx, ZObject *self);
void __z_object_class_init(struct zco_context_t *ctx, ZObjectClass *_class);
#line 40 "z-object.zco"
void  z_object_class_destroy(ZObjectGlobal *gbl);
#line 75 "z-object.zco"
void  z_object_reset(Self *self);
#line 90 "z-object.zco"
void  z_object_dispose(Self *self);
#line 103 "z-object.zco"
void  z_object_ref(Self *self);
#line 108 "z-object.zco"
void  z_object_unref(Self *self);
#line 157 "z-object.zco"
void *  z_object_connect(Self *self,char *name,ZObject *target,char *method_name,void *userdata);
#line 192 "z-object.zco"
void  z_object_disconnect(Self *self,char *name,void *key);
#line 223 "z-object.zco"
void  z_object_register_signal(Self *self,char *name);
#line 247 "z-object.zco"
int  z_object_emit_signal(Self *self,char *name,void *argv);
#line 277 "z-object.zco"
void  z_object_add_attached_property_map(Self *self,void *map);
#line 293 "z-object.zco"
ZMemoryAllocator *  z_object_get_allocator_ptr(Self *self);

#undef Self


#endif
