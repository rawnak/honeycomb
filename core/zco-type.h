/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco-type.h: Context management
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


#ifndef _ZCO_H_
#define _ZCO_H_

#define GLOBAL_FROM_OBJECT(o) ((o)->_global)
#define CLASS_FROM_OBJECT(o)  ((ZObjectClass *) (o)->class_base)
#define CLASS_FROM_GLOBAL(g)  ((g)->_class)
#define GLOBAL_FROM_CLASS(c)  ((ZCommonGlobal *) (c)->real_global)
#define CTX_FROM_GLOBAL(g)    ((g)->common.ctx)
#define CTX_FROM_OBJECT(o)    CTX_FROM_GLOBAL(GLOBAL_FROM_OBJECT(o))

struct ZCommonGlobal {
        /* vtable for object instance.
           This table maps type id to an offset. Given a type id of a parent
           object or interface, we get an offset from the base address of the
           object. Since we use single inheritance only, the offset will always
           be 0 when the requested type id belongs to an object and will almost
           always be non-zero when the requested type id belongs to an
           interface.

           Since interfaces do not contain any data members, the only purpose
           of this table is to verify if a certain object implements an
           interface. In a language that support multiple inheritance, this
           table would allow for a way to get the data members of the
           first and non-first parent classes of the object.

           Since this table is the same for all objects of the same type, it is
           stored in the Global struct. It is not stored in the Class struct
           because the mapping does not depend on whether another class
           inherits this class.  */
	int *vtable_off_list;
	int vtable_off_size;

        /* vtable for static class
           This table maps type id to an offset. Given a type id of a parent
           object or interface, we get an offset from the base address of the
           Class struct. Since we use single inheritance only, the offset will
           always be 0 when the requested type belongs to an object and will
           almost always be non-zero when the requested type id belongs to an
           interface.

           Unlike the vtable for object instance (above), this vtable operates
           on the Class struct. Since the virtual function pointer of
           interfaces are stored in the Class struct, this offset can be used
           to retrieve the virtual function pointers for non-first parent
           classes (which would have to be interfaces).

           Since this table is the same for all object of the same type, it is
           stored in the Global struct. It is not stored in the Class struct
           because the mapping does not depend on whether another class
           inherits this class.  */
	int *svtable_off_list;
	int svtable_off_size;

	int is_object;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
};
typedef struct ZCommonGlobal ZCommonGlobal;

struct zco_context_t {
        ZCommonGlobal **types;
        int type_count;
        void *marshal;                  /* ZClosureMarshal object */
        void *framework_events;         /* ZFrameworkEvents object */
        void *object_tracker;           /* ZObjectTracker object */
        int min_segment_cap_by_size;    /* Minimum vector segment capacity */
        int min_segment_cap_by_count;   /* Minimum vector segment capacity */
};

void    zco_context_init(struct zco_context_t *ctx);
void    zco_context_destroy(struct zco_context_t *ctx);
void    zco_context_set_marshal(struct zco_context_t *ctx, void *marshal);
void *  zco_context_get_framework_events(struct zco_context_t *ctx);
void *  zco_context_set_object_tracker(struct zco_context_t *ctx, void *object_tracker);
int     zco_context_get_min_segment_capacity_by_size(struct zco_context_t *ctx);
void    zco_context_set_min_segment_capacity_by_size(struct zco_context_t *ctx, int value);
int     zco_context_get_min_segment_capacity_by_count(struct zco_context_t *ctx);
void    zco_context_set_min_segment_capacity_by_count(struct zco_context_t *ctx, int value);


ZCommonGlobal ** zco_get_ctx_type(struct zco_context_t *ctx, int type_id);
int              zco_allocate_type_id();
int              zco_get_type_count();
void             zco_inherit_vtable(int **list, int *size, int *src_list, int src_size, void *base, void *target);
void             zco_add_to_vtable(int **list, int *size, int type_id);

#endif

