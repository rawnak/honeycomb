/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-closure-marshal.h: Bootstrap file for z-closure-marshal.zco
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

#ifndef _Z_CLOSURE_MARSHAL_H_
#define _Z_CLOSURE_MARSHAL_H_

#include <z-object.h>
#include <z-vector.h>

#include <zco-type.h>
#define Self ZClosureMarshal
#define Z_CLOSURE_MARSHAL(s) ((ZClosureMarshal *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_closure_marshal_type_id]))


struct ZClosureMarshalPrivate;
struct ZClosureMarshalProtected;
struct ZClosureMarshalGlobal;
struct ZClosureMarshalClass;
struct ZClosureMarshal;

typedef struct ZClosureMarshalPrivate ZClosureMarshalPrivate;
typedef struct ZClosureMarshalProtected ZClosureMarshalProtected;
typedef struct ZClosureMarshalGlobal ZClosureMarshalGlobal;
typedef struct ZClosureMarshalClass ZClosureMarshalClass;
typedef struct ZClosureMarshal ZClosureMarshal;

struct ZClosureMarshalPrivate {
};

struct ZClosureMarshalProtected {
};

struct ZClosureMarshalGlobal {
	struct ZCommonGlobal common;
	struct ZClosureMarshalClass *_class;
};

struct ZClosureMarshalClass {
	int  (*__invoke)(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,ZVector *vargs,void *userdata);
};

struct ZClosureMarshal {
	struct ZClosureMarshalGlobal *_global;
	struct ZClosureMarshalPrivate _priv;
	struct ZClosureMarshalProtected _prot;
};
extern int z_closure_marshal_type_id;
ZClosureMarshalGlobal * z_closure_marshal_get_type(struct zco_context_t *ctx);
void __z_closure_marshal_init(struct zco_context_t *ctx, ZClosureMarshal *self);
void __z_closure_marshal_class_init(struct zco_context_t *ctx, ZClosureMarshalClass *_class);
int  z_closure_marshal_invoke(Self *self,ZObject *target,ZObjectSignalHandler handler,ZVector *args,ZVector *vargs,void *userdata);

#undef Self


#endif
