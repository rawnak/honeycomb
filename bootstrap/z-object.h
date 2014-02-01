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

struct ZVector;
typedef void*(*ZObjectMethodHookHandler)(struct ZObject *self, const char *symbol, int return_value_size, struct ZVector *args);

struct ZMemoryAllocator;
typedef struct ZMemoryAllocator ZMemoryAllocator;

struct ZClosureMarshal;
typedef struct ZClosureMarshal ZClosureMarshal;


#include <zco-context.h>
#define Self ZObject
#define Z_OBJECT(s) ((ZObject *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_object_type_id]))


ZCO_TYPEDEF_FWD_DECL_CLASS(ZObject);

struct ZObjectPrivate {
	unsigned int ref_count;
	ZObject *attached_properties;
	ZObject *signal_map;
	ZObject *closure_marshal;
	ZMemoryAllocator *allocator;
	ZObjectMethodHookHandler _method_hook;
};

struct ZObjectProtected {
};

struct ZObjectGlobal {
	ZCO_CLASS_GLOBAL_HEAD(ZObject);
};

struct ZObjectClass {
	ZCommonGlobal * real_global;
	void  (*__class_destroy)(ZObjectGlobal *gbl);
	void  (*__reset)(Self *self);
	void  (*____delete)(Self *self);
	void  (*__dispose)(Self *self);
};

struct ZObject {
	ZCO_CLASS_PUBLIC_HEAD(ZObject);
	void *class_base;
};
extern int z_object_type_id;
ZObjectGlobal * z_object_get_type(struct zco_context_t *ctx);
void __z_object_init(struct zco_context_t *ctx, ZObject *self);
void __z_object_class_init(struct zco_context_t *ctx, ZObjectClass *_class);
void  z_object_class_destroy(ZObjectGlobal *gbl);
void  z_object_reset(Self *self);
void  z_object___delete(Self *self);
void  z_object_dispose(Self *self);
void  z_object_ref(Self *self);
void  z_object_unref(Self *self);
void *  z_object_connect(Self *self,char *name,ZObject *target,char *method_name,void *userdata);
void  z_object_disconnect(Self *self,char *name,void *key);
void  z_object_register_signal(Self *self,char *name);
int  z_object_emit_signal(Self *self,char *name,void *argv);
void  z_object_add_attached_property_map(Self *self,void *map);
ZMemoryAllocator *  z_object_get_allocator_ptr(Self *self);
void z_object_set_allocator_ptr(Self *self, ZMemoryAllocator *  value);
ZObject *  z_object_get_closure_marshal(Self *self);
void z_object_set_closure_marshal(Self *self, ZObject *  value);

#undef Self


#endif
