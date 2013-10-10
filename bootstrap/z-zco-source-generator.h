/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-zco-source-generator.h: Bootstrap file for z-zco-source-generator.zco
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

#ifndef _Z_ZCO_SOURCE_GENERATOR_H_
#define _Z_ZCO_SOURCE_GENERATOR_H_

#include <z-object.h>

#include <z-string.h>
#include <z-file.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//extern ZString* yytext[];
extern int column;
extern int yylineno;
extern void yyerror(const char *s);

//int yydebug=1;

enum access_mode_t
{
 ACCESS_PRIVATE,
 ACCESS_PROTECTED,
 ACCESS_PUBLIC,
 ACCESS_GLOBAL
};

enum modifier_mode_t
{
 MODIFIER_NONE,
 MODIFIER_VIRTUAL,
 MODIFIER_OVERRIDE
};

typedef enum access_mode_t access_mode_t;
typedef enum modifier_mode_t modifier_mode_t;


#include <zco-type.h>
#define Self ZZcoSourceGenerator
#define Z_ZCO_SOURCE_GENERATOR(s) ((ZZcoSourceGenerator *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[z_zco_source_generator_type_id]))


struct ZZcoSourceGeneratorPrivate;
struct ZZcoSourceGeneratorProtected;
struct ZZcoSourceGeneratorGlobal;
struct ZZcoSourceGeneratorClass;
struct ZZcoSourceGenerator;

typedef struct ZZcoSourceGeneratorPrivate ZZcoSourceGeneratorPrivate;
typedef struct ZZcoSourceGeneratorProtected ZZcoSourceGeneratorProtected;
typedef struct ZZcoSourceGeneratorGlobal ZZcoSourceGeneratorGlobal;
typedef struct ZZcoSourceGeneratorClass ZZcoSourceGeneratorClass;
typedef struct ZZcoSourceGenerator ZZcoSourceGenerator;

struct ZZcoSourceGeneratorPrivate {
	ZFile *source_file;
	ZFile *header_file;
	ZString *type_name;
	ZString *symbol_name;
	ZString *virtual_base_name;
	char *header_filename;
	char *zco_filename;
	ZString *current_class_name_lowercase;
	ZString *current_class_name_pascal;
	int parent_class_count;
	ZString **parent_class_name_lowercase;
	ZString **parent_class_name_uppercase;
	ZString **parent_class_name_pascal;
	int is_interface;
	int is_attached_property;
	int class_needs_zvalue;
	int class_needs_vector;
	int class_needs_map;
	int class_needs_string;
	int real_lineno;
	ZString *global_data;
	ZString *class_data;
	ZString *private_data;
	ZString *protected_data;
	ZString *public_data;
	ZString *function_prototypes_c;
	ZString *function_definitions;
	ZString *virtual_function_ptr_inits;
	ZString *h_macros_head;
	ZString *h_macros_tail;
	ZString *c_macros;
	ZString *function_prototypes_h;
	ZString *function_registrations;
	ZString *signal_registrations;
	ZString *attached_prop_registrations;
	ZString *class_destroy_code;
	access_mode_t access_mode;
	modifier_mode_t modifier_mode;
	ZString *str_class_init;
	ZString *str_global_init;
	ZString *str_init;
	ZString *str_global_destroy;
	ZString *str_get;
	ZString *str_set;
	ZString *str_comma;
	ZString *str_zvalue;
	ZString *str_self;
	ZString *str_z;
	ZString *str_char;
	ZString *str_int8_t;
	ZString *str_unsigned_char;
	ZString *str_uint8_t;
	ZString *str_short;
	ZString *str_int16_t;
	ZString *str_int;
	ZString *str_int32_t;
	ZString *str_long;
	ZString *str_long_long;
	ZString *str_int64_t;
	ZString *str_unsigned_short;
	ZString *str_uint16_t;
	ZString *str_unsigned_int;
	ZString *str_uint32_t;
	ZString *str_unsigned_long;
	ZString *str_unsigned_long_long;
	ZString *str_uint64_t;
	ZString *str_float;
	ZString *str_double;
	ZString *str_void;
	ZString *str_class_destroy;
	ZString *z_object_class_name_pascal;
};

struct ZZcoSourceGeneratorProtected {
};

struct ZZcoSourceGeneratorGlobal {
	struct ZCommonGlobal common;
	struct ZZcoSourceGeneratorClass *_class;
	void  (*__parent_dispose)(ZObject *object);
	void (*__parent_class_destroy)(ZObjectGlobal *gbl);
	void (*__parent___delete)(ZObject *self);
};

struct ZZcoSourceGeneratorClass {
	struct ZObjectClass parent_z_object;
};

struct ZZcoSourceGenerator {
	struct ZObject parent_z_object;
	struct ZZcoSourceGeneratorGlobal *_global;
	struct ZZcoSourceGeneratorPrivate _priv;
	struct ZZcoSourceGeneratorProtected _prot;
};
extern int z_zco_source_generator_type_id;
ZZcoSourceGeneratorGlobal * z_zco_source_generator_get_type(struct zco_context_t *ctx);
void __z_zco_source_generator_init(struct zco_context_t *ctx, ZZcoSourceGenerator *self);
void __z_zco_source_generator_class_init(struct zco_context_t *ctx, ZZcoSourceGeneratorClass *_class);
void  z_zco_source_generator_shutdown(Self *self);
Self * z_zco_source_generator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator);
ZString *  z_zco_source_generator_new_string(Self *self,const char *s1);
void  z_zco_source_generator_special_member_function_decl(Self *self,ZString *symbol,ZString *arglist,ZString *code);
void  z_zco_source_generator_property_decl(Self *self,ZString *get_or_set,ZString *code);
void  z_zco_source_generator_add_parent(Self *self,ZString *name_in_pascal);
void  z_zco_source_generator_record_line_number(Self *self);
void  z_zco_source_generator_prepare_class(Self *self,ZString *class_name);
void  z_zco_source_generator_prepare_interface(Self *self,ZString *interface_name);
void  z_zco_source_generator_finalize_class_definition(Self *self);
void  z_zco_source_generator_finalize_interface_definition(Self *self);
void  z_zco_source_generator_write_header_block(Self *self,ZString *s);
void  z_zco_source_generator_write_source_block(Self *self,ZString *s);
void  z_zco_source_generator_class_declaration(Self *self);
void  z_zco_source_generator_interface_declaration(Self *self);
void  z_zco_source_generator_enable_virtual_mode(Self *self);
void  z_zco_source_generator_enable_override_mode(Self *self,ZString *s);
void  z_zco_source_generator_set_access_mode(Self *self,int mode);
void  z_zco_source_generator_set_type_name(Self *self,ZString *s);
void  z_zco_source_generator_set_symbol_name(Self *self,ZString *s);
void  z_zco_source_generator_add_class_data_member(Self *self);
void  z_zco_source_generator_add_class_virtual_data_member(Self *self);
void  z_zco_source_generator_class_virtual_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
void  z_zco_source_generator_class_override_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
void  z_zco_source_generator_class_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
void  z_zco_source_generator_class_signal_decl(Self *self,ZString *s1,ZString *s2);
void  z_zco_source_generator_finalize_property(Self *self);
void  z_zco_source_generator_enable_attached_property(Self *self);
int  z_zco_source_generator_setup(Self *self,int argc,char **argv);

#undef Self


#endif
