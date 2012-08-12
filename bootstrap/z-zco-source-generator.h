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
#line 44 "z-zco-source-generator.zco"
	ZFile *source_file;
#line 45 "z-zco-source-generator.zco"
	ZFile *header_file;
#line 47 "z-zco-source-generator.zco"
	ZString *type_name;
#line 48 "z-zco-source-generator.zco"
	ZString *symbol_name;
#line 49 "z-zco-source-generator.zco"
	ZString *virtual_base_name;
#line 50 "z-zco-source-generator.zco"
	char *header_filename;
#line 51 "z-zco-source-generator.zco"
	char *zco_filename;
#line 54 "z-zco-source-generator.zco"
	ZString *current_class_name_lowercase;
#line 57 "z-zco-source-generator.zco"
	ZString *current_class_name_pascal;
#line 60 "z-zco-source-generator.zco"
	int parent_class_count;
#line 61 "z-zco-source-generator.zco"
	ZString **parent_class_name_lowercase;
#line 62 "z-zco-source-generator.zco"
	ZString **parent_class_name_uppercase;
#line 63 "z-zco-source-generator.zco"
	ZString **parent_class_name_pascal;
#line 64 "z-zco-source-generator.zco"
	int is_interface;
#line 65 "z-zco-source-generator.zco"
	int is_attached_property;
#line 66 "z-zco-source-generator.zco"
	int class_needs_zvalue;
#line 67 "z-zco-source-generator.zco"
	int class_needs_vector;
#line 68 "z-zco-source-generator.zco"
	int class_needs_map;
#line 69 "z-zco-source-generator.zco"
	int class_needs_string;
#line 70 "z-zco-source-generator.zco"
	int real_lineno;
#line 72 "z-zco-source-generator.zco"
	ZString *global_data;
#line 73 "z-zco-source-generator.zco"
	ZString *class_data;
#line 74 "z-zco-source-generator.zco"
	ZString *private_data;
#line 75 "z-zco-source-generator.zco"
	ZString *protected_data;
#line 76 "z-zco-source-generator.zco"
	ZString *public_data;
#line 77 "z-zco-source-generator.zco"
	ZString *function_prototypes_c;
#line 78 "z-zco-source-generator.zco"
	ZString *function_definitions;
#line 79 "z-zco-source-generator.zco"
	ZString *virtual_function_ptr_inits;
#line 80 "z-zco-source-generator.zco"
	ZString *h_macros_head;
#line 81 "z-zco-source-generator.zco"
	ZString *h_macros_tail;
#line 82 "z-zco-source-generator.zco"
	ZString *c_macros;
#line 83 "z-zco-source-generator.zco"
	ZString *function_prototypes_h;
#line 84 "z-zco-source-generator.zco"
	ZString *function_registrations;
#line 85 "z-zco-source-generator.zco"
	ZString *signal_registrations;
#line 87 "z-zco-source-generator.zco"
	access_mode_t access_mode;
#line 88 "z-zco-source-generator.zco"
	modifier_mode_t modifier_mode;
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
#line 96 "z-zco-source-generator.zco"
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
#line 131 "z-zco-source-generator.zco"
Self * z_zco_source_generator_new(struct zco_context_t *ctx);
#line 137 "z-zco-source-generator.zco"
ZString *  z_zco_source_generator_new_string(Self *self,const char *s1);
#line 165 "z-zco-source-generator.zco"
void  z_zco_source_generator_special_member_function_decl(Self *self,ZString *symbol,ZString *arglist,ZString *code);
#line 613 "z-zco-source-generator.zco"
void  z_zco_source_generator_property_decl(Self *self,ZString *get_or_set,ZString *code);
#line 733 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_parent(Self *self,ZString *name_in_pascal);
#line 832 "z-zco-source-generator.zco"
void  z_zco_source_generator_record_line_number(Self *self);
#line 881 "z-zco-source-generator.zco"
void  z_zco_source_generator_prepare_class(Self *self,ZString *class_name);
#line 981 "z-zco-source-generator.zco"
void  z_zco_source_generator_prepare_interface(Self *self,ZString *interface_name);
#line 1129 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_class_definition(Self *self);
#line 1134 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_interface_definition(Self *self);
#line 1546 "z-zco-source-generator.zco"
void  z_zco_source_generator_write_header_block(Self *self,ZString *s);
#line 1554 "z-zco-source-generator.zco"
void  z_zco_source_generator_write_source_block(Self *self,ZString *s);
#line 1562 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_declaration(Self *self);
#line 1571 "z-zco-source-generator.zco"
void  z_zco_source_generator_interface_declaration(Self *self);
#line 1580 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_virtual_mode(Self *self);
#line 1589 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_override_mode(Self *self,ZString *s);
#line 1602 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_access_mode(Self *self,int mode);
#line 1607 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_type_name(Self *self,ZString *s);
#line 1616 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_symbol_name(Self *self,ZString *s);
#line 1629 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_class_data_member(Self *self);
#line 1634 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_class_virtual_data_member(Self *self);
#line 1639 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_virtual_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
#line 1644 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_override_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
#line 1649 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3);
#line 1654 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_signal_decl(Self *self,ZString *s1,ZString *s2);
#line 1659 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_property(Self *self);
#line 1673 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_attached_property(Self *self);
#line 1678 "z-zco-source-generator.zco"
int  z_zco_source_generator_setup(Self *self,int argc,char **argv);

#undef Self


#endif
