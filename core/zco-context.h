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


#ifndef _ZCO_CONTEXT_H_
#define _ZCO_CONTEXT_H_

#include <pthread.h>
#include <stdint.h>

#define GLOBAL_FROM_OBJECT(o)    ((o)->_global)
#define CLASS_FROM_OBJECT(o)     ((ZObjectClass *) (o)->class_base)
#define CLASS_FROM_GLOBAL(g)     ((g)->_class)
#define GLOBAL_FROM_CLASS(c)     ((ZCommonGlobal *) (c)->real_global)
#define CTX_FROM_GLOBAL(g)       ((g)->common.ctx)
#define CTX_FROM_OBJECT(o)       CTX_FROM_GLOBAL(GLOBAL_FROM_OBJECT(o))
#define ALLOCATOR_FROM_OBJECT(o) z_object_get_allocator_ptr(Z_OBJECT(o))

/* Forward declares structs for the class and also typedefs them so the
   'struct' keyword is not required */
#define ZCO_TYPEDEF_FWD_DECL_CLASS(c) \
        struct c##Private; typedef struct c##Private c##Private; \
        struct c##Protected; typedef struct c##Protected c##Protected; \
        struct c##Global; typedef struct c##Global c##Global; \
        struct c##Class; typedef struct c##Class c##Class; \
        struct c; typedef struct c c;

/* Required to be at the top of the global struct. It creates some struct
   fields that are expected to be there */
#define ZCO_CLASS_GLOBAL_HEAD(c) \
	struct ZCommonGlobal common; \
	struct c##Class *_class;

/* Required to be at the top of the instance struct. It creates some struct
   fields that are expected to be there */
#define ZCO_CLASS_PUBLIC_HEAD(c) \
        struct c##Global *_global; \
        struct c##Private _priv; \
        struct c##Protected _prot

/* Allocates space to store the class id */
#define ZCO_DEFINE_CLASS_TYPE(c) \
        int c##_type_id = -1; \
        static Self *__##c##_new(struct zco_context_t *ctx, ZMemoryAllocator *allocator) \
        { \
                Self *self = NULL; \
                if (allocator) { \
                        ZObjectTracker *object_tracker = z_memory_allocator_get_object_tracker(allocator); \
                        if (object_tracker) { \
                                self = (Self *) z_object_tracker_create(object_tracker, c##_type_id); \
                                z_object_unref(Z_OBJECT(object_tracker)); \
                        } \
                } \
                if (!self) { \
                        ZMemoryAllocator *obj_allocator = ctx->fixed_allocator; \
                        if (obj_allocator) \
                                self = (Self *) z_memory_allocator_allocate(obj_allocator, sizeof(Self)); \
                        else \
                                self = (Self *) malloc(sizeof(Self)); \
                        z_object_set_allocator_ptr((ZObject *) self, allocator); \
                        __##c##_init(ctx, self); \
                } \
                return self; \
        } \
        static int __map_compare(ZMap *map, const void *a, const void *b) \
        { \
                return strcmp(a, b); \
        } 

/* Defines the internal getter of the attached property */
#define ZCO_DEFINE_ATTACHED_PROP_GETTER(cu,c,p,t) \
        int  c##_get_attached_##p(ZObject *object) \
        { \
                struct cu##Global *_global = c##_get_type(GLOBAL_FROM_OBJECT(object)->common.ctx); \
                ZMap *map = (ZMap *) _global->_attached_##p; \
                ZMapIter *it = z_map_find(map, object); \
                void *value = z_map_get_value(map, it); \
                z_object_unref(Z_OBJECT(it)); \
                return (t) (unsigned long) value; \
        }

/* Defines the internal setter of the attached property */
#define ZCO_DEFINE_ATTACHED_PROP_SETTER(cu,c,p) \
        void c##_set_attached_##p(ZObject *object, int  value) \
        { \
                struct cu##Global *_global = c##_get_type(GLOBAL_FROM_OBJECT(object)->common.ctx); \
                ZMap *map = (ZMap *) _global->_attached_##p; \
                if (z_map_assign(map, object, (void *) (unsigned long) value) == 0) \
                        z_object_add_attached_property_map(object, map); \
        }

/* Allocate memory for class specific data */
#define ZCO_CREATE_CLASS(global,b,a,c) \
	ZCommonGlobal **global_ptr = (a##_type_id != -1)? zco_get_ctx_type(ctx, a##_type_id) : NULL; \
        if (global_ptr && *global_ptr) \
                return (b##Global *) *global_ptr; \
        struct b##Global *global = (b##Global *) malloc(sizeof(struct b##Global)); \
        global->common.ctx = ctx; \
        global->_class = malloc(sizeof(struct b##Class)); \
        memset(CLASS_FROM_GLOBAL(global), 0, sizeof(struct b##Class)); \
        global->common.name = #b; \
        global->common.vtable_off_list = NULL; \
        global->common.vtable_off_size = 0; \
        global->common.svtable_off_list = NULL; \
        global->common.svtable_off_size = 0; \
        global->common.is_object = c;

/* Clone the vtable of the parent class/interface */
#define ZCO_INHERIT_CLASS(b,a,c) \
        { \
                struct c temp; \
                struct c##Class temp_class; \
                struct b##Global *p_global = a##_get_type(ctx); \
                zco_inherit_vtable( \
                        &global->common.vtable_off_list, \
                        &global->common.vtable_off_size, \
                        p_global->common.vtable_off_list, \
                        p_global->common.vtable_off_size, \
                        &temp, \
                        &temp.parent_##a); \
                zco_inherit_vtable( \
                        &global->common.svtable_off_list, \
                        &global->common.svtable_off_size, \
                        p_global->common.svtable_off_list, \
                        p_global->common.svtable_off_size, \
                        &temp_class, \
                        &temp_class.parent_##a); \
                b##Class *p1_class = CLASS_FROM_GLOBAL(p_global); \
                b##Class *p2_class = (b##Class *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[a##_type_id]); \
                memcpy(p2_class, p1_class, sizeof(struct b##Class)); \
        }


/* Override a virtual method of a parent class */
#define ZCO_OVERRIDE_VIRTUAL_METHOD(a,b,d,c) \
        { \
                a##Class *p_class = (a##Class *) ((char *) CLASS_FROM_GLOBAL(global) + global->common.svtable_off_list[b##_type_id]); \
                global->__parent_##c = p_class->__##c; \
                p_class->__##c = d##_##c; \
        } 

/* Required to be called in the beginning of a signal method */
#define ZCO_SIGNAL_START(args) \
	ZVector *args = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self)); \
	z_vector_set_item_size(args, 0); \
	z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);

/* Required to be called in the end of a signal method */
#define ZCO_SIGNAL_END(args,a) \
	z_object_emit_signal(Z_OBJECT(self), #a, args); \
	z_object_unref(Z_OBJECT(args));


/* Register class with the type system */
#define ZCO_REGISTER_TYPE(a) \
        if (a##_type_id == -1) \
                a##_type_id = zco_allocate_type_id(); \
        global->common.id = a##_type_id; \
        zco_add_to_vtable(&global->common.vtable_off_list, &global->common.vtable_off_size, a##_type_id); \
        zco_add_to_vtable(&global->common.svtable_off_list, &global->common.svtable_off_size, a##_type_id); \
        global_ptr = zco_get_ctx_type(ctx, a##_type_id); \
        *global_ptr = (ZCommonGlobal *) global;

/* Register a method as a virtual method */
#define ZCO_CREATE_VIRTUAL_METHOD(b,a) CLASS_FROM_GLOBAL(global)->__##a = b##_virtual_##a

/* Create a method map so methods can be looked up by string */
#define ZCO_CREATE_METHOD_MAP(b,a) \
        __##a##_class_init(ctx, (b##Class *) CLASS_FROM_GLOBAL(global)); \
        global->common.method_map = z_map_new(ctx, NULL); \
        z_map_set_compare(global->common.method_map, __map_compare); \
        z_map_set_key_destruct(global->common.method_map, (ZMapItemCallback) free)

/* Register a method in the method map */
#define ZCO_REGISTER_METHOD(a) z_map_insert((ZMap *) global->common.method_map, strdup(#a), (ZObjectSignalHandler) a);

/* Required to be called in the beginning of the init method */
#define ZCO_INIT_START(a,b) \
	{ \
		struct a##Global *_global = b##_get_type(ctx); \
		self->_global = _global; \
	}

/* Seal this class as the final class in the inheritance. Any previous seals for the object will be replaced */
#define ZCO_SEAL_CLASS() \
        ((ZObject *) self)->class_base = (void *) CLASS_FROM_GLOBAL(self->_global); \
        ((ZObjectClass *) CLASS_FROM_GLOBAL(self->_global))->real_global = (ZCommonGlobal *) self->_global

#define ZCO_METHOD_HOOK_START(self,args) \
	{ \
		ZObjectMethodHookHandler _method_hook = Z_OBJECT(self)->_priv._method_hook; \
		if (_method_hook) { \
			ZVector *args = z_vector_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self)); \
			z_vector_set_item_size(args, 0); \
			z_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref) \

#define ZCO_METHOD_HOOK_END(self,args,symbol,ret_type) \
			ret_type dummy; \
			ret_type ret = (ret_type) _method_hook((ZObject *) self, #symbol, sizeof(*dummy), args); \
			z_object_unref(Z_OBJECT(args)); \
			return ret; \
		} \
	}


#define ZCO_ADD_ZVALUE_ARG(args,a) \
        { \
                ZValue *value = a; \
                z_object_ref(Z_OBJECT(value)); \
                z_vector_push_back(args, value); \
        }

#define ZCO_ADD_OBJECT_ARG(args,a) \
        { \
                ZValue *value = z_value_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self)); \
                z_value_set_as_object(value, Z_OBJECT(a)); \
                z_vector_push_back(args, value); \
        }


#define ZCO_ADD_STRING_ARG(args,a) \
        { \
                ZValue *value = z_value_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self)); \
                ZString *_temp = z_string_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self)); \
                z_string_set_cstring(_temp, a, Z_STRING_ENCODING_UTF8); \
                z_value_set_as_object(value, Z_OBJECT(_temp)); \
                z_object_unref(Z_OBJECT(_temp)); \
                z_vector_push_back(args, value); \
        }

#define A4(args,a,type) \
        { \
                ZValue *value = z_value_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self)); \
                z_value_set_as_##type(value, a); \
                z_vector_push_back(args, value); \
        }


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

struct ZMemoryAllocator;
struct ZClosureMarshal;
struct ZEventLoop;
struct ZBind;
struct ZObject;

typedef struct ZCommonGlobal ZCommonGlobal;
typedef struct ZEventLoop ZEventLoop;
typedef struct ZBind ZBind;

struct zco_context_t {
        struct ZCommonGlobal **types;
        int type_count;

        /* Minimum vector segment capacity */
        int min_segment_cap_by_size;
        int min_segment_cap_by_count;

        /* The fixed_allocator is used when we need to allocate fixed sized
           block. The allocator will assume that the block will not be resized
           after allocation */
        struct ZMemoryAllocator *fixed_allocator; 

        /* The flex_allocator is used when we need to allocate a block
           of a certain size that may (or may not) be increased in size
           depending on how it is allocated. This allocator may be less
           efficient compared to fixed_allocator but it will reduce the
           overhead of reallocating a new block of memory by resizing
           the existing block. */
        struct ZMemoryAllocator *flex_allocator;

        /* The ts_fixed_allocator is a thread-safe version of the fixed_allocator */
        struct ZMemoryAllocator *ts_fixed_allocator;
};

void    zco_context_init(struct zco_context_t *ctx);
void    zco_context_destroy(struct zco_context_t *ctx);
void *  zco_context_set_object_tracker(struct zco_context_t *ctx, void *object_tracker);
int     zco_context_get_min_segment_capacity_by_size(struct zco_context_t *ctx);
void    zco_context_set_min_segment_capacity_by_size(struct zco_context_t *ctx, int value);
int     zco_context_get_min_segment_capacity_by_count(struct zco_context_t *ctx);
void    zco_context_set_min_segment_capacity_by_count(struct zco_context_t *ctx, int value);
void    zco_context_full_garbage_collect(struct zco_context_t *ctx);

ZCommonGlobal ** zco_get_ctx_type(struct zco_context_t *ctx, int type_id);
int              zco_allocate_type_id();
int              zco_get_type_count();
void             zco_inherit_vtable(int **list, int *size, int *src_list, int src_size, void *base, void *target);
void             zco_add_to_vtable(int **list, int *size, int type_id);

#endif

