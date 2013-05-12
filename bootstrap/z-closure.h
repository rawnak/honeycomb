/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-closure.h: Bootstrap file for z-closure.zco
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

#ifndef _Z_CLOSURE_H_
#define _Z_CLOSURE_H_

#include <z-object.h>
#include <z-vector.h>
#include <stdint.h>
#include <z-closure-marshal.h>

#include <zco-type.h>
#define Self ZClosure
#define Z_CLOSURE(s) ((ZClosure *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_closure_type_id]))


struct ZClosurePrivate;
struct ZClosureProtected;
struct ZClosureGlobal;
struct ZClosureClass;
struct ZClosure;

typedef struct ZClosurePrivate ZClosurePrivate;
typedef struct ZClosureProtected ZClosureProtected;
typedef struct ZClosureGlobal ZClosureGlobal;
typedef struct ZClosureClass ZClosureClass;
typedef struct ZClosure ZClosure;

struct ZClosurePrivate {
	ZClosureMarshal *marshal;
	ZObjectSignalHandler handler;
	ZObject *target;
	void *userdata;
};

struct ZClosureProtected {
};

struct ZClosureGlobal {
	struct ZCommonGlobal common;
	struct ZClosureClass *_class;
	void  (*__parent_reset)(ZObject *object);
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZClosureClass {
	struct ZObjectClass parent_z_object;
};

struct ZClosure {
	struct ZObject parent_z_object;
	struct ZClosureGlobal *_global;
	struct ZClosurePrivate _priv;
	struct ZClosureProtected _prot;
};
extern int z_closure_type_id;
ZClosureGlobal * z_closure_get_type(struct zco_context_t *ctx);
void __z_closure_init(struct zco_context_t *ctx, ZClosure *self);
void __z_closure_class_init(struct zco_context_t *ctx, ZClosureClass *_class);
Self * z_closure_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
Self * z_closure_dup(ZClosure *src);
ZObjectSignalHandler  z_closure_get_handler(Self *self);
void z_closure_set_handler(Self *self, ZObjectSignalHandler  value);
void *  z_closure_get_userdata(Self *self);
void z_closure_set_userdata(Self *self, void *  value);
void z_closure_set_marshal(Self *self, ZClosureMarshal *  value);
void z_closure_set_target(Self *self, ZObject *  value);
int  z_closure_invoke(Self *self,ZVector *args);

#undef Self


#endif
