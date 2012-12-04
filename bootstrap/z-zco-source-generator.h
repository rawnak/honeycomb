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
#line 37 "z-zco-source-generator.zco"

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
#define Z_ZCO_SOURCE_GENERATOR(s) ((ZZcoSourceGenerator *) ((char *) (s) + (s)->_global->vtable_off_list[z_zco_source_generator_type_id]))


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
#line 50 "z-zco-source-generator.zco"
	ZFile *source_file;
#line 51 "z-zco-source-generator.zco"
	ZFile *header_file;
#line 53 "z-zco-source-generator.zco"
	ZString *type_name;
#line 54 "z-zco-source-generator.zco"
	ZString *symbol_name;
#line 55 "z-zco-source-generator.zco"
	ZString *virtual_base_name;
#line 56 "z-zco-source-generator.zco"
	char *header_filename;
#line 57 "z-zco-source-generator.zco"
	char *zco_filename;
#line 60 "z-zco-source-generator.zco"
	ZString *current_class_name_lowercase;
#line 63 "z-zco-source-generator.zco"
	ZString *current_class_name_pascal;
#line 66 "z-zco-source-generator.zco"
	int parent_class_count;
#line 67 "z-zco-source-generator.zco"
	ZString **parent_class_name_lowercase;
#line 68 "z-zco-source-generator.zco"
	ZString **parent_class_name_uppercase;
#line 69 "z-zco-source-generator.zco"
	ZString **parent_class_name_pascal;
#line 70 "z-zco-source-generator.zco"
	int is_interface;
#line 71 "z-zco-source-generator.zco"
	int is_attached_property;
#line 72 "z-zco-source-generator.zco"
	int class_needs_zvalue;
#line 73 "z-zco-source-generator.zco"
	int class_needs_vector;
#line 74 "z-zco-source-generator.zco"
	int class_needs_map;
#line 75 "z-zco-source-generator.zco"
	int class_needs_string;
#line 76 "z-zco-source-generator.zco"
	int real_lineno;
#line 78 "z-zco-source-generator.zco"
	ZString *global_data;
#line 79 "z-zco-source-generator.zco"
	ZString *class_data;
#line 80 "z-zco-source-generator.zco"
	ZString *private_data;
#line 81 "z-zco-source-generator.zco"
	ZString *protected_data;
#line 82 "z-zco-source-generator.zco"
	ZString *public_data;
#line 83 "z-zco-source-generator.zco"
	ZString *function_prototypes_c;
#line 84 "z-zco-source-generator.zco"
	ZString *function_definitions;
#line 85 "z-zco-source-generator.zco"
	ZString *virtual_function_ptr_inits;
#line 86 "z-zco-source-generator.zco"
	ZString *h_macros_head;
#line 87 "z-zco-source-generator.zco"
	ZString *h_macros_tail;
#line 88 "z-zco-source-generator.zco"
	ZString *c_macros;
#line 89 "z-zco-source-generator.zco"
	ZString *function_prototypes_h;
#line 90 "z-zco-source-generator.zco"
	ZString *function_registrations;
#line 91 "z-zco-source-generator.zco"
	ZString *signal_registrations;
#line 93 "z-zco-source-generator.zco"
	access_mode_t access_mode;
#line 94 "z-zco-source-generator.zco"
	modifier_mode_t modifier_mode;
#line 96 "z-zco-source-generator.zco"
	ZString *str_class_init;
#line 97 "z-zco-source-generator.zco"
	ZString *str_global_init;
#line 98 "z-zco-source-generator.zco"
	ZString *str_init;
#line 99 "z-zco-source-generator.zco"
	ZString *str_get;
#line 100 "z-zco-source-generator.zco"
	ZString *str_set;
#line 101 "z-zco-source-generator.zco"
	ZString *str_comma;
#line 102 "z-zco-source-generator.zco"
	ZString *str_zvalue;
#line 103 "z-zco-source-generator.zco"
	ZString *str_self;
#line 104 "z-zco-source-generator.zco"
	ZString *str_z;
#line 105 "z-zco-source-generator.zco"
	ZString *str_char;
#line 106 "z-zco-source-generator.zco"
	ZString *str_int8_t;
#line 107 "z-zco-source-generator.zco"
	ZString *str_unsigned_char;
#line 108 "z-zco-source-generator.zco"
	ZString *str_uint8_t;
#line 109 "z-zco-source-generator.zco"
	ZString *str_short;
#line 110 "z-zco-source-generator.zco"
	ZString *str_int16_t;
#line 111 "z-zco-source-generator.zco"
	ZString *str_int;
#line 112 "z-zco-source-generator.zco"
	ZString *str_int32_t;
#line 113 "z-zco-source-generator.zco"
	ZString *str_long;
#line 114 "z-zco-source-generator.zco"
	ZString *str_long_long;
#line 115 "z-zco-source-generator.zco"
	ZString *str_int64_t;
#line 116 "z-zco-source-generator.zco"
	ZString *str_unsigned_short;
#line 117 "z-zco-source-generator.zco"
	ZString *str_uint16_t;
#line 118 "z-zco-source-generator.zco"
	ZString *str_unsigned_int;
#line 119 "z-zco-source-generator.zco"
	ZString *str_uint32_t;
#line 120 "z-zco-source-generator.zco"
	ZString *str_unsigned_long;
#line 121 "z-zco-source-generator.zco"
	ZString *str_unsigned_long_long;
#line 122 "z-zco-source-generator.zco"
	ZString *str_uint64_t;
#line 123 "z-zco-source-generator.zco"
	ZString *str_float;
#line 124 "z-zco-source-generator.zco"
	ZString *str_double;
};

struct ZZcoSourceGeneratorProtected {
};

struct ZZcoSourceGeneratorGlobal {
	int *vtable_off_list;
	int vtable_off_size;
	int is_object;
	struct ZZcoSourceGeneratorClass *_class;
	struct zco_context_t *ctx;
	const char *name;
	int id;
	void *method_map;
#line 190 "z-zco-source-generator.zco"
	void  (*__parent_dispose)(ZObject *object);
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
#line 255 "z-zco-source-generator.zco"
Self * z_zco_source_generator_new(struct zco_context_t *ctx);
#line 261 "z-zco-source-generator.zco"
ZString *  z_zco_source_generator_new_string(Self *self,const char *s1);
#line 279 "z-zco-source-generator.zco"
void  z_zco_source_generator_special_member_function_decl(Self *self,ZString *symbol,ZString *arglist,ZString *code);
#line 767 "z-zco-source-generator.zco"
void  z_zco_source_generator_property_decl(Self *self,ZString *get_or_set,ZString *code);
#line 879 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_parent(Self *self,ZString *name_in_pascal);
#line 1032 "z-zco-source-generator.zco"
void  z_zco_source_generator_record_line_number(Self *self);
#line 1081 "z-zco-source-generator.zco"
void  z_zco_source_generator_prepare_class(Self *self,ZString *class_name);
#line 1181 "z-zco-source-generator.zco"
void  z_zco_source_generator_prepare_interface(Self *self,ZString *interface_name);
#line 1329 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_class_definition(Self *self);
#line 1334 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_interface_definition(Self *self);
#line 1753 "z-zco-source-generator.zco"
void  z_zco_source_generator_write_header_block(Self *self,ZString *s);
#line 1761 "z-zco-source-generator.zco"
void  z_zco_source_generator_write_source_block(Self *self,ZString *s);
#line 1769 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_declaration(Self *self);
#line 1778 "z-zco-source-generator.zco"
void  z_zco_source_generator_interface_declaration(Self *self);
#line 1787 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_virtual_mode(Self *self);
#line 1796 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_override_mode(Self *self,ZString *s);
#line 1809 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_access_mode(Self *self,int mode);
#line 1814 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_type_name(Self *self,ZString *s);
#line 1823 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_symbol_name(Self *self,ZString *s);
#line 1836 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_class_data_member(Self *self);
#line 1841 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_class_virtual_data_member(Self *self);
#line 1846 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_virtual_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
#line 1851 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_override_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
#line 1856 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
#line 1861 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_signal_decl(Self *self,ZString *s1,ZString *s2);
#line 1866 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_property(Self *self);
#line 1880 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_attached_property(Self *self);
#line 1885 "z-zco-source-generator.zco"
int  z_zco_source_generator_setup(Self *self,int argc,char **argv);

#undef Self


#endif
