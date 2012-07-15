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
#define Z_CLOSURE(s) ((ZClosure *) (s))


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
	void *userdata;
};

struct ZClosureProtected {
};

struct ZClosureGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	struct ZClosureClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void  (*__parent_dispose)(ZObject *object);
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
Self * z_closure_new(struct zco_context_t *ctx);
Self * z_closure_dup(ZClosure *src);
ZObjectSignalHandler  z_closure_get_handler(Self *self);
void z_closure_set_handler(Self *self, ZObjectSignalHandler  value);
void *  z_closure_get_userdata(Self *self);
void z_closure_set_userdata(Self *self, void *  value);
void z_closure_set_marshal(Self *self, ZClosureMarshal *  value);
int  z_closure_invoke(Self *self,ZVector *args);

#undef Self


#endif
