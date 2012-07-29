/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * z-zco-source-generator.c: Bootstrap file for z-zco-source-generator.zco
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

#line 40 "z-zco-source-generator.zco"


#include <z-map.h>
#include <string.h>
#include <z-zco-source-generator.h>
#include <zco-type.h>
#include <stdlib.h>
#define Self ZZcoSourceGenerator
#define selfp (&self->_priv)
#define GET_NEW(ctx) __z_zco_source_generator_new(ctx)
#define CTX self->_global->ctx
#define INIT_EXISTS
#line 92 "z-zco-source-generator.zco"
#define init z_zco_source_generator_init
#line 131 "z-zco-source-generator.zco"
#define new z_zco_source_generator_new
#line 137 "z-zco-source-generator.zco"
#define strdup2 z_zco_source_generator_strdup2
#line 148 "z-zco-source-generator.zco"
#define strdup3 z_zco_source_generator_strdup3
#line 159 "z-zco-source-generator.zco"
#define strdup4 z_zco_source_generator_strdup4
#line 170 "z-zco-source-generator.zco"
#define strdup5 z_zco_source_generator_strdup5
#line 181 "z-zco-source-generator.zco"
#define strdup6 z_zco_source_generator_strdup6
#line 192 "z-zco-source-generator.zco"
#define strdup7 z_zco_source_generator_strdup7
#line 204 "z-zco-source-generator.zco"
#define dump_string z_zco_source_generator_dump_string
#line 214 "z-zco-source-generator.zco"
#define print_line_number z_zco_source_generator_print_line_number
#line 219 "z-zco-source-generator.zco"
#define print_line_number_on_file z_zco_source_generator_print_line_number_on_file
#line 224 "z-zco-source-generator.zco"
#define special_member_function_decl z_zco_source_generator_special_member_function_decl
#line 247 "z-zco-source-generator.zco"
#define self_strndup z_zco_source_generator_self_strndup
#line 261 "z-zco-source-generator.zco"
#define extract_argument z_zco_source_generator_extract_argument
#line 283 "z-zco-source-generator.zco"
#define signal_decl z_zco_source_generator_signal_decl
#line 502 "z-zco-source-generator.zco"
#define member_function_decl z_zco_source_generator_member_function_decl
#line 545 "z-zco-source-generator.zco"
#define add_data_member z_zco_source_generator_add_data_member
#line 574 "z-zco-source-generator.zco"
#define add_virtual_data_member z_zco_source_generator_add_virtual_data_member
#line 588 "z-zco-source-generator.zco"
#define define_attached_property_getter z_zco_source_generator_define_attached_property_getter
#line 629 "z-zco-source-generator.zco"
#define define_attached_property_setter z_zco_source_generator_define_attached_property_setter
#line 670 "z-zco-source-generator.zco"
#define property_decl z_zco_source_generator_property_decl
#line 701 "z-zco-source-generator.zco"
#define pascal_to_uppercase z_zco_source_generator_pascal_to_uppercase
#line 734 "z-zco-source-generator.zco"
#define pascal_to_lowercase z_zco_source_generator_pascal_to_lowercase
#line 763 "z-zco-source-generator.zco"
#define add_parent z_zco_source_generator_add_parent
#line 778 "z-zco-source-generator.zco"
#define add_function_pointer z_zco_source_generator_add_function_pointer
#line 784 "z-zco-source-generator.zco"
#define strip_out_type z_zco_source_generator_strip_out_type
#line 796 "z-zco-source-generator.zco"
#define strip_out_types z_zco_source_generator_strip_out_types
#line 822 "z-zco-source-generator.zco"
#define virtual_member_function_decl z_zco_source_generator_virtual_member_function_decl
#line 863 "z-zco-source-generator.zco"
#define record_line_number z_zco_source_generator_record_line_number
#line 868 "z-zco-source-generator.zco"
#define override_member_function_decl z_zco_source_generator_override_member_function_decl
#line 915 "z-zco-source-generator.zco"
#define prepare_class z_zco_source_generator_prepare_class
#line 1013 "z-zco-source-generator.zco"
#define prepare_interface z_zco_source_generator_prepare_interface
#line 1111 "z-zco-source-generator.zco"
#define get_base_filename z_zco_source_generator_get_base_filename
#line 1135 "z-zco-source-generator.zco"
#define macro_safe z_zco_source_generator_macro_safe
#line 1160 "z-zco-source-generator.zco"
#define external_declaration z_zco_source_generator_external_declaration
#line 1532 "z-zco-source-generator.zco"
#define write_header_block z_zco_source_generator_write_header_block
#line 1540 "z-zco-source-generator.zco"
#define write_source_block z_zco_source_generator_write_source_block
#line 1548 "z-zco-source-generator.zco"
#define class_declaration z_zco_source_generator_class_declaration
#line 1557 "z-zco-source-generator.zco"
#define interface_declaration z_zco_source_generator_interface_declaration
#line 1566 "z-zco-source-generator.zco"
#define enable_virtual_mode z_zco_source_generator_enable_virtual_mode
#line 1572 "z-zco-source-generator.zco"
#define enable_override_mode z_zco_source_generator_enable_override_mode
#line 1579 "z-zco-source-generator.zco"
#define set_access_mode z_zco_source_generator_set_access_mode
#line 1584 "z-zco-source-generator.zco"
#define set_type_name z_zco_source_generator_set_type_name
#line 1592 "z-zco-source-generator.zco"
#define set_symbol_name z_zco_source_generator_set_symbol_name
#line 1604 "z-zco-source-generator.zco"
#define add_class_data_member z_zco_source_generator_add_class_data_member
#line 1609 "z-zco-source-generator.zco"
#define add_class_virtual_data_member z_zco_source_generator_add_class_virtual_data_member
#line 1614 "z-zco-source-generator.zco"
#define class_virtual_member_function_decl z_zco_source_generator_class_virtual_member_function_decl
#line 1619 "z-zco-source-generator.zco"
#define class_override_member_function_decl z_zco_source_generator_class_override_member_function_decl
#line 1624 "z-zco-source-generator.zco"
#define class_member_function_decl z_zco_source_generator_class_member_function_decl
#line 1629 "z-zco-source-generator.zco"
#define class_signal_decl z_zco_source_generator_class_signal_decl
#line 1634 "z-zco-source-generator.zco"
#define finalize_property z_zco_source_generator_finalize_property
#line 1644 "z-zco-source-generator.zco"
#define enable_attached_property z_zco_source_generator_enable_attached_property
#line 1649 "z-zco-source-generator.zco"
#define setup z_zco_source_generator_setup

int z_zco_source_generator_type_id = -1;

static Self *__z_zco_source_generator_new(struct zco_context_t *ctx)
{
	Self *self = (Self *) malloc(sizeof(Self));
	__z_zco_source_generator_init(ctx, self);
	return self;
}

static int __map_compare(ZMap *map, const void *a, const void *b)
{
	return strcmp(a, b);
}
#line 92 "z-zco-source-generator.zco"
static void z_zco_source_generator_init(Self *self);
#line 96 "z-zco-source-generator.zco"
static void  z_zco_source_generator_dispose(ZObject *object);
#line 204 "z-zco-source-generator.zco"
static void  z_zco_source_generator_dump_string(ZString *str,FILE *file);
#line 214 "z-zco-source-generator.zco"
static void  z_zco_source_generator_print_line_number(Self *self,ZString *str);
#line 219 "z-zco-source-generator.zco"
static void  z_zco_source_generator_print_line_number_on_file(Self *self,ZFile *file);
#line 247 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_self_strndup(const char *s,int max_len);
#line 261 "z-zco-source-generator.zco"
static void  z_zco_source_generator_extract_argument(char *arg,char **arg_type,char **arg_name);
#line 283 "z-zco-source-generator.zco"
static void  z_zco_source_generator_signal_decl(Self *self,const char *type,const char *symbol,const char *arglist);
#line 502 "z-zco-source-generator.zco"
static void  z_zco_source_generator_member_function_decl(Self *self,const char *type,const char *symbol,const char *arglist,const char *code,int should_register_method);
#line 545 "z-zco-source-generator.zco"
static void  z_zco_source_generator_add_data_member(Self *self,int mode,const char *_type_name,const char *_symbol_name);
#line 574 "z-zco-source-generator.zco"
static void  z_zco_source_generator_add_virtual_data_member(Self *self,int mode,const char *_type_name,const char *_symbol_name);
#line 588 "z-zco-source-generator.zco"
static void  z_zco_source_generator_define_attached_property_getter(Self *self,char *symbol_name,const char *app_code);
#line 629 "z-zco-source-generator.zco"
static void  z_zco_source_generator_define_attached_property_setter(Self *self,const char *symbol_name,const char *app_code);
#line 701 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_pascal_to_uppercase(const char *s,char delimiter);
#line 734 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_pascal_to_lowercase(const char *s,char delimiter);
#line 778 "z-zco-source-generator.zco"
static void  z_zco_source_generator_add_function_pointer(Self *self,ZString *output,const char *_type_name,const char *_symbol_name_prefix,const char *_symbol_name,const char *_arglist);
#line 784 "z-zco-source-generator.zco"
static char * z_zco_source_generator_strip_out_type(char *arg);
#line 796 "z-zco-source-generator.zco"
static void  z_zco_source_generator_strip_out_types(ZString *str,const char *arglist);
#line 822 "z-zco-source-generator.zco"
static void  z_zco_source_generator_virtual_member_function_decl(Self *self,const char *type,const char *symbol,const char *arglist,const char *code);
#line 868 "z-zco-source-generator.zco"
static void  z_zco_source_generator_override_member_function_decl(Self *self,const char *type,const char *symbol,const char *arglist,const char *code);
#line 1111 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_get_base_filename(const char *full_filename,int *base_length);
#line 1135 "z-zco-source-generator.zco"
static char * z_zco_source_generator_macro_safe(const char *s);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZZcoSourceGeneratorGlobal * z_zco_source_generator_get_type(struct zco_context_t *ctx)
{
	void **global_ptr = NULL;
	if (z_zco_source_generator_type_id != -1) {
		global_ptr = zco_get_ctx_type(ctx, z_zco_source_generator_type_id);
	}
	if (!global_ptr || !*global_ptr) {
		struct ZZcoSourceGeneratorGlobal *global = (ZZcoSourceGeneratorGlobal *) malloc(sizeof(struct ZZcoSourceGeneratorGlobal));
		global->ctx = ctx;
		global->_class = malloc(sizeof(struct ZZcoSourceGeneratorClass));
		memset(global->_class, 0, sizeof(struct ZZcoSourceGeneratorClass));
		global->name = "ZZcoSourceGenerator";
		global->vtable_off_list = NULL;
		global->vtable_off_size = 0;

		struct ZZcoSourceGenerator temp;

		{
			struct ZObjectGlobal *p_class = z_object_get_type(ctx);
			zco_inherit_vtable(
				&global->vtable_off_list,
				&global->vtable_off_size,
				p_class->vtable_off_list,
				p_class->vtable_off_size,
				&temp,
				&temp.parent_z_object);
			unsigned long offset = global->vtable_off_list[z_object_type_id];
			memcpy((char *) global->_class + offset, p_class->_class, sizeof(struct ZObjectClass));
		}
		if (z_zco_source_generator_type_id == -1)
			z_zco_source_generator_type_id = zco_allocate_type_id();
		global->id = z_zco_source_generator_type_id;
		zco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, z_zco_source_generator_type_id);
		global_ptr = zco_get_ctx_type(ctx, z_zco_source_generator_type_id);
		*global_ptr = global;
		
#line 96 "z-zco-source-generator.zco"
		{
#line 96 "z-zco-source-generator.zco"
			ZObjectClass *p_class = (ZObjectClass *) ((char *) global->_class + global->vtable_off_list[z_object_type_id]);
#line 96 "z-zco-source-generator.zco"
			global->__parent_dispose = p_class->__dispose;
#line 96 "z-zco-source-generator.zco"
			p_class->__dispose = z_zco_source_generator_dispose;
#line 96 "z-zco-source-generator.zco"
		}
		__z_zco_source_generator_class_init(ctx, (ZZcoSourceGeneratorClass *) global->_class);
		global->method_map = z_map_new(ctx);
		z_map_set_compare(global->method_map, __map_compare);
		z_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);
#line 131 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("new"), (ZObjectSignalHandler) new);
#line 137 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("strdup2"), (ZObjectSignalHandler) strdup2);
#line 148 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("strdup3"), (ZObjectSignalHandler) strdup3);
#line 159 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("strdup4"), (ZObjectSignalHandler) strdup4);
#line 170 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("strdup5"), (ZObjectSignalHandler) strdup5);
#line 181 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("strdup6"), (ZObjectSignalHandler) strdup6);
#line 192 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("strdup7"), (ZObjectSignalHandler) strdup7);
#line 224 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("special_member_function_decl"), (ZObjectSignalHandler) special_member_function_decl);
#line 670 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("property_decl"), (ZObjectSignalHandler) property_decl);
#line 763 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("add_parent"), (ZObjectSignalHandler) add_parent);
#line 863 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("record_line_number"), (ZObjectSignalHandler) record_line_number);
#line 915 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("prepare_class"), (ZObjectSignalHandler) prepare_class);
#line 1013 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("prepare_interface"), (ZObjectSignalHandler) prepare_interface);
#line 1160 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("external_declaration"), (ZObjectSignalHandler) external_declaration);
#line 1532 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("write_header_block"), (ZObjectSignalHandler) write_header_block);
#line 1540 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("write_source_block"), (ZObjectSignalHandler) write_source_block);
#line 1548 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("class_declaration"), (ZObjectSignalHandler) class_declaration);
#line 1557 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("interface_declaration"), (ZObjectSignalHandler) interface_declaration);
#line 1566 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("enable_virtual_mode"), (ZObjectSignalHandler) enable_virtual_mode);
#line 1572 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("enable_override_mode"), (ZObjectSignalHandler) enable_override_mode);
#line 1579 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_access_mode"), (ZObjectSignalHandler) set_access_mode);
#line 1584 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_type_name"), (ZObjectSignalHandler) set_type_name);
#line 1592 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("set_symbol_name"), (ZObjectSignalHandler) set_symbol_name);
#line 1604 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("add_class_data_member"), (ZObjectSignalHandler) add_class_data_member);
#line 1609 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("add_class_virtual_data_member"), (ZObjectSignalHandler) add_class_virtual_data_member);
#line 1614 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("class_virtual_member_function_decl"), (ZObjectSignalHandler) class_virtual_member_function_decl);
#line 1619 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("class_override_member_function_decl"), (ZObjectSignalHandler) class_override_member_function_decl);
#line 1624 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("class_member_function_decl"), (ZObjectSignalHandler) class_member_function_decl);
#line 1629 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("class_signal_decl"), (ZObjectSignalHandler) class_signal_decl);
#line 1634 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("finalize_property"), (ZObjectSignalHandler) finalize_property);
#line 1644 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("enable_attached_property"), (ZObjectSignalHandler) enable_attached_property);
#line 1649 "z-zco-source-generator.zco"
		z_map_insert((ZMap *) global->method_map, strdup("setup"), (ZObjectSignalHandler) setup);
		#ifdef GLOBAL_INIT_EXISTS
			global_init((ZZcoSourceGeneratorGlobal *) global);
		#endif
		return global;
	}
	return (ZZcoSourceGeneratorGlobal *) *global_ptr;
}

void __z_zco_source_generator_class_init(struct zco_context_t *ctx, ZZcoSourceGeneratorClass *_class)
{
	__z_object_class_init(ctx, (ZObjectClass *) _class);
	#ifdef CLASS_INIT_EXISTS
		class_init(ctx, _class);
	#endif
}
void __z_zco_source_generator_init(struct zco_context_t *ctx, Self *self)
{
	struct ZZcoSourceGeneratorGlobal *_global = z_zco_source_generator_get_type(ctx);
	self->_global = _global;
	__z_object_init(ctx, (ZObject *) (self));
	((ZObject *) self)->class_base = (void *) _global->_class;
	((ZObject *) self)->global_base = (void *) _global;
	((ZObject *) self)->vtable = _global->vtable_off_list;
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
#line 92 "z-zco-source-generator.zco"
static void z_zco_source_generator_init(Self *self)
{
 }
#line 96 "z-zco-source-generator.zco"
#define PARENT_HANDLER self->_global->__parent_dispose
static void  z_zco_source_generator_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 free(selfp->header_filename);

 z_file_write(selfp->header_file, "\n#endif\n");
 z_file_write(selfp->source_file, "\n\n");

 z_file_close(selfp->header_file);
 z_file_close(selfp->source_file);

 z_object_unref(Z_OBJECT(selfp->header_file));
 z_object_unref(Z_OBJECT(selfp->source_file));

 if (selfp->type_name) {
 free(selfp->type_name);
 }

 if (selfp->current_class_name_pascal) {
 free(selfp->current_class_name_pascal);
 }

 if (selfp->symbol_name) {
 free(selfp->symbol_name);
 }

 if (selfp->virtual_base_name) {
 free(selfp->virtual_base_name);
 }

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
#line 131 "z-zco-source-generator.zco"
Self * z_zco_source_generator_new(struct zco_context_t *ctx)
{
 Self *self = GET_NEW(ctx);
 return self;
 }
#line 137 "z-zco-source-generator.zco"
char *  z_zco_source_generator_strdup2(Self *self,const char *s1,const char *s2)
{
 ZString *str = z_string_new(CTX);
 z_string_append_format(str, "%s%s", s1, s2);

 char *res = z_string_get_cstring(str, Z_STRING_ENCODING_ASCII);
 z_object_unref(Z_OBJECT(str));

 return res;
 }
#line 148 "z-zco-source-generator.zco"
char *  z_zco_source_generator_strdup3(Self *self,const char *s1,const char *s2,const char *s3)
{
 ZString *str = z_string_new(CTX);
 z_string_append_format(str, "%s%s%s", s1, s2, s3);

 char *res = z_string_get_cstring(str, Z_STRING_ENCODING_ASCII);
 z_object_unref(Z_OBJECT(str));

 return res;
 }
#line 159 "z-zco-source-generator.zco"
char *  z_zco_source_generator_strdup4(Self *self,const char *s1,const char *s2,const char *s3,const char *s4)
{
 ZString *str = z_string_new(CTX);
 z_string_append_format(str, "%s%s%s%s", s1, s2, s3, s4);

 char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
 z_object_unref(Z_OBJECT(str));

 return res;
 }
#line 170 "z-zco-source-generator.zco"
char *  z_zco_source_generator_strdup5(Self *self,const char *s1,const char *s2,const char *s3,const char *s4,const char *s5)
{
 ZString *str = z_string_new(CTX);
 z_string_append_format(str, "%s%s%s%s%s", s1, s2, s3, s4, s5);

 char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
 z_object_unref(Z_OBJECT(str));

 return res;
 }
#line 181 "z-zco-source-generator.zco"
char *  z_zco_source_generator_strdup6(Self *self,const char *s1,const char *s2,const char *s3,const char *s4,const char *s5,const char *s6)
{
 ZString *str = z_string_new(CTX);
 z_string_append_format(str, "%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6);

 char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
 z_object_unref(Z_OBJECT(str));

 return res;
 }
#line 192 "z-zco-source-generator.zco"
char *  z_zco_source_generator_strdup7(Self *self,const char *s1,const char *s2,const char *s3,const char *s4,const char *s5,const char *s6,const char *s7)
{
 ZString *str = z_string_new(CTX);
 z_string_append_format(str, "%s%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6, s7);

 char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
 z_object_unref(Z_OBJECT(str));

 return res;
 }
#line 204 "z-zco-source-generator.zco"
static void  z_zco_source_generator_dump_string(ZString *str,FILE *file)
{
 z_string_validate(str);
 char *s = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
 fputs(s, file);
 free(s);
 z_string_clear(str);
 }
#line 214 "z-zco-source-generator.zco"
static void  z_zco_source_generator_print_line_number(Self *self,ZString *str)
{
 z_string_append_format(str, "#line %d \"%s\"\n", selfp->real_lineno, selfp->zco_filename);
 }
#line 219 "z-zco-source-generator.zco"
static void  z_zco_source_generator_print_line_number_on_file(Self *self,ZFile *file)
{
 z_file_write_format(file, "#line %d \"%s\"\n", selfp->real_lineno, selfp->zco_filename);
 }
#line 224 "z-zco-source-generator.zco"
void  z_zco_source_generator_special_member_function_decl(Self *self,const char *symbol,const char *arglist,const char *code)
{
 if (!strcmp(symbol, "class_init"))
 z_string_append_cstring(selfp->c_macros, "#define CLASS_INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

 else if (!strcmp(symbol, "global_init"))
 z_string_append_cstring(selfp->c_macros, "#define GLOBAL_INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

 else if (!strcmp(symbol, "init"))
 z_string_append_cstring(selfp->c_macros, "#define INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

 print_line_number(self, selfp->c_macros);
 z_string_append_format(selfp->c_macros, "#define %s %s_%s\n", symbol, selfp->current_class_name_lowercase, symbol);

 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static void %s_%s%s;\n", selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static void %s_%s%s\n%s\n", selfp->current_class_name_lowercase, symbol, arglist, code);
 }
#line 247 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_self_strndup(const char *s,int max_len)
{
 int length = strlen(s);

 if (length > max_len)
 length = max_len;

 char *str = malloc(length + 1);
 memcpy(str, s, length);
 str[length] = 0;

 return str;
 }
#line 261 "z-zco-source-generator.zco"
static void  z_zco_source_generator_extract_argument(char *arg,char **arg_type,char **arg_name)
{
 int i, length = strlen(arg);
 int j;

 for (i=length-1; i>=0; --i) {
 if (arg[i] == ' ' || arg[i] == '*') {
 /* trim the spaces from the arg_type string and copy it */
 for (j=i; arg[j] == ' '; --j);
 *arg_type = self_strndup(arg, j+1);

 /* copy the argument name */
 *arg_name = strdup(arg + (i+1));
 return;
 }
 }

 *arg_type = strdup("");
 *arg_name = strdup(arg);
 }
#line 283 "z-zco-source-generator.zco"
static void  z_zco_source_generator_signal_decl(Self *self,const char *type,const char *symbol,const char *arglist)
{
 print_line_number(self, selfp->c_macros);
 z_string_append_format(selfp->c_macros, "#define %s %s_%s\n", symbol, selfp->current_class_name_lowercase, symbol);

 switch (selfp->access_mode)
 {
 case ACCESS_PRIVATE:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %s %s_%s%s;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static %s %s_%s%s\n", type, selfp->current_class_name_lowercase, symbol, arglist);
 break;

 case ACCESS_PUBLIC:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_h);
 z_string_append_format(selfp->function_prototypes_h, "%s %s_%s%s;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "%s %s_%s%s\n", type, selfp->current_class_name_lowercase, symbol, arglist);
 break;

 default:
 abort();
 }

 selfp->class_needs_vector = 1;
 selfp->class_needs_zvalue = 1;

 /* start of function body */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\x7b\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\tZVector *args = z_vector_new(CTX, 0);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\tz_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);\n");

 char *arglist_no_paren = strdup(arglist+1);
 char *p;

 arglist_no_paren[strlen(arglist_no_paren)-1] = 0;

 p = strtok(arglist_no_paren, ",");

 /* always skip the first argument */
 p = strtok(NULL, ",");

 while (p)
 {
 char *arg_type, *arg_name, *temp;
 int is_pointer, length;

 extract_argument(p, &arg_type, &arg_name);
 p = strtok(NULL, ",");

 /* create the ZValue object */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\x7b\n");

 /* check if the parameter has pointers */
 length = strlen(arg_type);
 temp = strchr(arg_type, '*');
 is_pointer = temp != NULL;

 /* set the value into the ZValue */
 if (is_pointer) {
 /* make sure there is at most one '*' character */
 if (temp != arg_type + (length-1)) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\t#error \"Invalid signal parameter type %s - cannot have multipointer types\"\n", arg_type);

 /* if the value is already a ZValue, use it directly */
 } else if (!strncmp(arg_type, "ZValue", 6)) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = %s;\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_object_ref(Z_OBJECT(value));\n", arg_name);

 /* if the value is derived from ZObject, treat it as an object type */
 } else if (!strncmp(arg_type, "Self", 4) || arg_type[0] == 'Z') {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_object(value, Z_OBJECT(%s));\n", arg_name);

 } else if (!strncmp(arg_type, "char", 4) || !strncmp(arg_type, "int8_t", 6) ||
 !strncmp(arg_type, "unsigned char", 13) || !strncmp(arg_type, "uint8_t", 7)) {
 selfp->class_needs_string = 1;

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZString *_temp = z_string_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_string_set_cstring(_temp, %s, Z_STRING_ENCODING_UTF8);\n", arg_name);

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_object(value, Z_OBJECT(_temp));\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_object_unref(Z_OBJECT(_temp));\n");
 }

 } else if (!strcmp(arg_type, "char") || !strcmp(arg_type, "int8_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_int8(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "short") || !strcmp(arg_type, "int16_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_int16(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "int") || !strcmp(arg_type, "int32_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_int32(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "long") || !strcmp(arg_type, "long long") || !strcmp(arg_type, "int64_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");
 
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_int64(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "unsigned char") || !strcmp(arg_type, "uint8_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_uint8(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "unsigned short") || !strcmp(arg_type, "uint16_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_uint16(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "unsigned int") || !strcmp(arg_type, "uint32_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_uint32(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "unsigned long") ||
 !strcmp(arg_type, "unsigned long long") ||
 !strcmp(arg_type, "uint64_t")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_uint64(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "float")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_real32(value, %s);\n", arg_name);

 } else if (!strcmp(arg_type, "double")) {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tZValue *value = z_value_new(CTX);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_value_set_as_real64(value, %s);\n", arg_name);

 } else {
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\t#error \"Invalid signal parameter type %s\"\n", arg_type);
 }

 /* add the ZValue into the vector */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\tz_vector_push_back(args, value);\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\t\x7d\n");

 free(arg_type);
 free(arg_name);
 }

 free(arglist_no_paren);

 /* end of function body */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\tz_object_emit_signal(Z_OBJECT(self), \"%s\", args);\n", symbol);

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\tz_object_unref(Z_OBJECT(args));\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\x7d\n");

 print_line_number(self, selfp->signal_registrations);
 z_string_append_format(selfp->signal_registrations, "\tz_object_register_signal(Z_OBJECT(self), \"%s\");\n", symbol);
 }
#line 502 "z-zco-source-generator.zco"
static void  z_zco_source_generator_member_function_decl(Self *self,const char *type,const char *symbol,const char *arglist,const char *code,int should_register_method)
{
 print_line_number(self, selfp->c_macros);
 z_string_append_format(selfp->c_macros, "#define %s %s_%s\n", symbol, selfp->current_class_name_lowercase, symbol);

 switch (selfp->access_mode)
 {
 case ACCESS_PRIVATE:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %s %s_%s%s;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static %s %s_%s%s\n%s\n", type, selfp->current_class_name_lowercase, symbol, arglist, code);
 break;

 case ACCESS_PUBLIC:
 if (should_register_method) {
 /* register method in look up table */
 print_line_number(self, selfp->function_registrations);
 // FIXME: _class cannot be casted to ZObjectClass* if it's originally an interface, like ZClosureMarshalClass
 //z_string_append_format(selfp->function_registrations,
 //     "\tz_object_register_method(ctx, (ZObjectClass *) _class, \"%s\", (ZObjectSignalHandler) %s);\n", symbol, symbol);

 z_string_append_format(selfp->function_registrations,
 "\t\tz_map_insert((ZMap *) global->method_map, strdup(\"%s\"), (ZObjectSignalHandler) %s);\n",
 symbol, symbol);
 }

 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_h);
 z_string_append_format(selfp->function_prototypes_h, "%s %s_%s%s;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "%s %s_%s%s\n%s\n", type, selfp->current_class_name_lowercase, symbol, arglist, code);
 break;
 default:
 abort();
 }
 }
#line 545 "z-zco-source-generator.zco"
static void  z_zco_source_generator_add_data_member(Self *self,int mode,const char *_type_name,const char *_symbol_name)
{
 switch (mode)
 {
 case ACCESS_PRIVATE:
 print_line_number(self, selfp->private_data);
 z_string_append_format(selfp->private_data, "\t%s%s;\n", _type_name, _symbol_name);
 break;

 case ACCESS_PROTECTED:
 print_line_number(self, selfp->protected_data);
 z_string_append_format(selfp->protected_data, "\t%s%s;\n", _type_name, _symbol_name);
 break;

 case ACCESS_PUBLIC:
 print_line_number(self, selfp->public_data);
 z_string_append_format(selfp->public_data, "\t%s%s;\n", _type_name, _symbol_name);
 break;

 case ACCESS_GLOBAL:
 print_line_number(self, selfp->global_data);
 z_string_append_format(selfp->global_data, "\t%s%s;\n", _type_name, _symbol_name);
 z_string_append_format(selfp->c_macros, "#define %s (self->_global->%s)\n", _symbol_name, selfp->symbol_name);
 break;
 default:
 abort();
 }
 }
#line 574 "z-zco-source-generator.zco"
static void  z_zco_source_generator_add_virtual_data_member(Self *self,int mode,const char *_type_name,const char *_symbol_name)
{
 switch (mode)
 {
 case ACCESS_PUBLIC:
 print_line_number(self, selfp->public_data);
 z_string_append_format(selfp->class_data, "\t%s %s;\n", _type_name, _symbol_name);
 break;

 default:
 abort();
 }
 }
#line 588 "z-zco-source-generator.zco"
static void  z_zco_source_generator_define_attached_property_getter(Self *self,char *symbol_name,const char *app_code)
{
 ZString *code;
 const char *arglist = "(ZObject *object)";
 char *symbol, *temp;

 /* define the helper macro to get the current value of the attached property */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions,
 "#define get_current_value() get_attached_%s(object)\n", symbol_name);

 /* define the exposed getter of the attached property */
 symbol = strdup2(self, "get_", symbol_name);
 member_function_decl(self, selfp->type_name, symbol, arglist, app_code, 0);
 free(symbol);

 /* undefine the helper macro previously defined before the exposed getter */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "#undef get_current_value\n");

 /* define the method to get the value of the attached property */
 selfp->class_needs_map = 1;
 code = z_string_new(CTX);
 z_string_format(code,
 "\x7b\n"
 "\tZMap *map = (ZMap *) attached_%s;\n"
 "\tZMapIter *it = z_map_find(map, object);\n"
 "\tvoid *value = z_map_get_value(map, it);\n"
 "\tz_object_unref(Z_OBJECT(it));\n"
 "\treturn (%s) (unsigned long) value;\n"
 "\x7d", symbol_name, selfp->type_name);

 symbol = strdup2(self, "get_attached_", symbol_name);
 temp = z_string_get_cstring(code, Z_STRING_ENCODING_UTF8);
 member_function_decl(self, selfp->type_name, symbol, arglist, temp, 0);
 free(temp);
 free(symbol);

 z_object_unref(Z_OBJECT(code));
 }
#line 629 "z-zco-source-generator.zco"
static void  z_zco_source_generator_define_attached_property_setter(Self *self,const char *symbol_name,const char *app_code)
{
 ZString *code;
 char *arglist = strdup3(self, "(ZObject *object, ", selfp->type_name, " value)");
 char *symbol, *temp;

 /* define the helper macro to get the current value of the attached property */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions,
 "#define set_current_value(val) set_attached_%s(object,value)\n", symbol_name);

 /* define the exposed setter of the attached property */
 symbol = strdup2(self, "set_", symbol_name);
 member_function_decl(self, selfp->type_name, symbol, arglist, app_code, 0);
 free(symbol);

 /* undefine the helper macro previously defined before the exposed setter */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "#undef set_current_value\n");

 /* define the method to set the value of the attached property */
 selfp->class_needs_map = 1;
 code = z_string_new(CTX);
 z_string_format(code,
 "\x7b\n"
 "\tZMap *map = (ZMap *) attached_%s;\n"
 "\tif (z_map_assign(map, object, (void *) (unsigned long) value) == 0)\n"
 "\t\tz_object_add_attached_property_map(object, map);\n"
 "\x7d", symbol_name);

 symbol = strdup2(self, "set_attached_", symbol_name);
 temp = z_string_get_cstring(code, Z_STRING_ENCODING_UTF8);
 member_function_decl(self, "void", symbol, arglist, temp, 0);
 free(temp);
 free(symbol);
 free(arglist);

 z_object_unref(Z_OBJECT(code));
 }
#line 670 "z-zco-source-generator.zco"
void  z_zco_source_generator_property_decl(Self *self,const char *get_or_set,const char *code)
{
 char *arglist, *symbol;

 if (selfp->is_attached_property) {
 /* attached property */
 if (!strcmp(get_or_set, "get"))
 define_attached_property_getter(self, selfp->symbol_name, code);

 else if (!strcmp(get_or_set, "set"))
 define_attached_property_setter(self, selfp->symbol_name, code);

 } else {
 /* regular property */

 if (!strcmp(get_or_set, "get")) {
 arglist = "(Self *self)";
 symbol = strdup2(self, "get_", selfp->symbol_name);
 member_function_decl(self, selfp->type_name, symbol, arglist, code, 0);
 free(symbol);

 } else if (!strcmp(get_or_set, "set")) {
 arglist = strdup3(self, "(Self *self, ", selfp->type_name, " value)");
 symbol = strdup2(self, "set_", selfp->symbol_name);
 member_function_decl(self, "void", symbol, arglist, code, 0);
 free(arglist);
 free(symbol);
 }
 }
 }
#line 701 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_pascal_to_uppercase(const char *s,char delimiter)
{
 int first = 1;
 char *res = malloc(strlen(s) * 2 + 1);
 char *p = res;

 for (; *s; ++s)
 {
 if (*s >= 'A' && *s <= 'Z') {
 if (!first) {
 *p = delimiter;
 ++p;
 }

 *p = *s;
 ++p;
 } else if (*s >= 'a' && *s <= 'z') {
 *p = *s + ('A' - 'a');
 ++p;

 } else {
 *p = *s;
 ++p;
 }

 first = 0;
 }

 *p = 0;

 return res;
 }
#line 734 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_pascal_to_lowercase(const char *s,char delimiter)
{
 int first = 1;
 char *res = malloc(strlen(s) * 2 + 1);
 char *p = res;

 for (; *s; ++s)
 {
 if (*s >= 'A' && *s <= 'Z') {
 if (!first) {
 *p = delimiter;
 ++p;
 }

 *p = *s + ('a' - 'A');
 ++p;
 } else {
 *p = *s;
 ++p;
 }

 first = 0;
 }

 *p = 0;

 return res;
 }
#line 763 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_parent(Self *self,char *name_in_pascal)
{
 /* increase the size of the parent class list */
 ++selfp->parent_class_count;

 selfp->parent_class_name_pascal = (char **) realloc(selfp->parent_class_name_pascal, sizeof(char *) * selfp->parent_class_count);
 selfp->parent_class_name_lowercase = (char **) realloc(selfp->parent_class_name_lowercase, sizeof(char *) * selfp->parent_class_count);
 selfp->parent_class_name_uppercase = (char **) realloc(selfp->parent_class_name_uppercase, sizeof(char *) * selfp->parent_class_count);

 /* store the name of the parent class */
 selfp->parent_class_name_pascal[selfp->parent_class_count-1] = name_in_pascal;
 selfp->parent_class_name_lowercase[selfp->parent_class_count-1] = pascal_to_lowercase(name_in_pascal, '_');
 selfp->parent_class_name_uppercase[selfp->parent_class_count-1] = pascal_to_uppercase(name_in_pascal, '_');
 }
#line 778 "z-zco-source-generator.zco"
static void  z_zco_source_generator_add_function_pointer(Self *self,ZString *output,const char *_type_name,const char *_symbol_name_prefix,const char *_symbol_name,const char *_arglist)
{
 print_line_number(self, output);
 z_string_append_format(output, "\t%s (*%s%s)%s;\n", _type_name, _symbol_name_prefix, _symbol_name, _arglist);
 }
#line 784 "z-zco-source-generator.zco"
static char * z_zco_source_generator_strip_out_type(char *arg)
{
 int i, length = strlen(arg);

 for (i=length-1; i>=0; --i) {
 if (arg[i] == ' ' || arg[i] == '*')
 return arg + (i+1);
 }

 return arg;
 }
#line 796 "z-zco-source-generator.zco"
static void  z_zco_source_generator_strip_out_types(ZString *str,const char *arglist)
{
 char *arglist_no_paren = strdup(arglist+1);
 char *p;
 int is_first = 1;

 arglist_no_paren[strlen(arglist_no_paren)-1] = 0;

 p = strtok(arglist_no_paren, ",");
 while (p)
 {
 char *q = strip_out_type(p);
 p = strtok(NULL, ",");

 if (!is_first)
 z_string_push_back(str, ',');
 else
 is_first = 0;

 z_string_append_cstring(str, q, Z_STRING_ENCODING_UTF8);
 }

 free(arglist_no_paren);
 }
#line 822 "z-zco-source-generator.zco"
static void  z_zco_source_generator_virtual_member_function_decl(Self *self,const char *type,const char *symbol,const char *arglist,const char *code)
{
 if (selfp->access_mode == ACCESS_PRIVATE) {
 yyerror("Cannot declare virtual function with private access specifier");
 }

 /* virtual function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %s %s_virtual_%s%s;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* virtual function caller */
 ZString *vcode = z_string_new(CTX);

 z_string_append_format(vcode, 
 "\x7b\n"
 "\tZObject *obj = (ZObject *) self;\n"
 "\t((%sClass *) ((char *) obj->class_base + obj->vtable[%s_type_id]))->__%s(",
 selfp->current_class_name_pascal, selfp->current_class_name_lowercase, symbol);

 strip_out_types(vcode, arglist);
 z_string_append_cstring(vcode, ");\n\x7d", Z_STRING_ENCODING_UTF8);

 char *temp = z_string_get_cstring(vcode, Z_STRING_ENCODING_UTF8);
 member_function_decl(self, type, symbol, arglist, temp, 1);

 free(temp);
 z_object_unref(Z_OBJECT(vcode));

 /* virtual function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static %s %s_virtual_%s%s\n%s\n", type, selfp->current_class_name_lowercase, symbol, arglist, code);

 /* add function pointer as a data member */
 add_function_pointer(self, selfp->class_data, type, "__", symbol, arglist);

 /* assign the address of the function into the function pointer data member */
 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_format(selfp->virtual_function_ptr_inits, "\t\tglobal->_class->__%s = %s_virtual_%s;\n", symbol, selfp->current_class_name_lowercase, symbol);
 }
#line 863 "z-zco-source-generator.zco"
void  z_zco_source_generator_record_line_number(Self *self)
{
 selfp->real_lineno = yylineno;
 }
#line 868 "z-zco-source-generator.zco"
static void  z_zco_source_generator_override_member_function_decl(Self *self,const char *type,const char *symbol,const char *arglist,const char *code)
{
 /* virtual function caller prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %s %s_%s%s;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions,
 "#define PARENT_HANDLER self->_global->__parent_%s\n"
 "static %s %s_%s%s\n%s\n"
 "#undef PARENT_HANDLER\n",
 symbol,
 type, selfp->current_class_name_lowercase, symbol, arglist, code);

 /* add function pointer as a data member */
 add_function_pointer(self, selfp->global_data, type, "__parent_", symbol, arglist);

 char *base_name_uppercase = pascal_to_uppercase(selfp->virtual_base_name, '_');
 char *base_name_lowercase = pascal_to_lowercase(selfp->virtual_base_name, '_');

 /* up cast to parent class */
 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_cstring(selfp->virtual_function_ptr_inits, "\t\t\x7b\n", Z_STRING_ENCODING_UTF8);

 /* create a pointer to the parent class's dispatch object */
 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_format(selfp->virtual_function_ptr_inits, "\t\t\t%sClass *p_class = (%sClass *) ((char *) global->_class + global->vtable_off_list[%s_type_id]);\n",
 selfp->virtual_base_name, selfp->virtual_base_name, base_name_lowercase);

 /* backup the existing virtual function pointer for the PARENT_HANDLER macro */
 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_format(selfp->virtual_function_ptr_inits, "\t\t\tglobal->__parent_%s = p_class->__%s;\n", symbol, symbol);

 /* assign the address of the function into the function pointer data member */
 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_format(selfp->virtual_function_ptr_inits, "\t\t\tp_class->__%s = %s_%s;\n", symbol, selfp->current_class_name_lowercase, symbol);

 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_cstring(selfp->virtual_function_ptr_inits, "\t\t\x7d\n", Z_STRING_ENCODING_UTF8);

 free(base_name_lowercase);
 free(base_name_uppercase);
 }
#line 915 "z-zco-source-generator.zco"
void  z_zco_source_generator_prepare_class(Self *self,char *class_name)
{
 int i;

 selfp->global_data = z_string_new(CTX);
 selfp->class_data = z_string_new(CTX);
 selfp->private_data = z_string_new(CTX);
 selfp->protected_data = z_string_new(CTX);
 selfp->public_data = z_string_new(CTX);
 selfp->function_prototypes_c = z_string_new(CTX);
 selfp->function_definitions = z_string_new(CTX);
 selfp->virtual_function_ptr_inits = z_string_new(CTX);
 selfp->h_macros_head = z_string_new(CTX);
 selfp->h_macros_tail = z_string_new(CTX);
 selfp->c_macros = z_string_new(CTX);
 selfp->function_prototypes_h = z_string_new(CTX);
 selfp->function_registrations = z_string_new(CTX);
 selfp->signal_registrations = z_string_new(CTX);

 char * current_class_name_uppercase = pascal_to_uppercase(class_name, '_');
 selfp->current_class_name_lowercase = pascal_to_lowercase(class_name, '_');
 selfp->current_class_name_pascal = class_name;

 /* start the private data structure */
 z_string_append_format(selfp->private_data, "struct %sPrivate \x7b\n", class_name);

 /* start the protected data structure */
 z_string_append_format(selfp->protected_data, "struct %sProtected \x7b\n", class_name);

 /* define the Self macro in the header file */
 z_string_append_format(selfp->h_macros_head, "#define Self %s\n", class_name);

 /* define the macro to upcast a derived object */
 z_string_append_format(selfp->h_macros_head, "#define %s(s) ((%s *) ((char *) (s) + (s)->_global->vtable_off_list[%s_type_id]))\n\n",
 current_class_name_uppercase,
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase);

 free(current_class_name_uppercase);

 /* define the tailing macros */
 z_string_append_cstring(selfp->h_macros_tail, "#undef Self\n", Z_STRING_ENCODING_UTF8);

 /* define the Self macro in the source file */
 z_string_append_format(selfp->c_macros,
 "#define Self %s\n"
 "#define selfp (&self->_priv)\n"
 "#define GET_NEW(ctx) __%s_new(ctx)\n"
 "#define CTX self->_global->ctx\n", class_name, selfp->current_class_name_lowercase);

 /* start the global data structure */
 z_string_append_format(selfp->global_data,
 "struct %sGlobal \x7b\n"
 "\tint *vtable_off_list;\n"
 "\tint vtable_off_size;\n"
 "\tstruct %sClass *_class;\n"
 "\tstruct zco_context_t *ctx;\n"
 "\tconst char *name;\n"
 "\tint id;\n"
 "\tvoid *method_map;\n", class_name, class_name);

 /* start the klass data structure */
 z_string_append_format(selfp->class_data, "struct %sClass \x7b\n", class_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->class_data, "\tstruct %sClass parent_%s;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* start the public data structure */
 z_string_append_format(selfp->public_data, "struct %s \x7b\n", class_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->public_data, "\tstruct %s parent_%s;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* declare the _class pointer in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %sGlobal *_global;\n", class_name);

 /* declare the _priv member in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %sPrivate _priv;\n", class_name);

 /* declare the _prot member in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %sProtected _prot;\n", class_name);

 selfp->access_mode = ACCESS_PUBLIC;
 selfp->modifier_mode = MODIFIER_NONE;


 selfp->symbol_name = 0;
 selfp->type_name = 0;
 selfp->virtual_base_name = 0;

 selfp->class_needs_zvalue = 0;
 selfp->class_needs_vector = 0;
 selfp->class_needs_map = 0;
 selfp->class_needs_string = 0;
 }
#line 1013 "z-zco-source-generator.zco"
void  z_zco_source_generator_prepare_interface(Self *self,char *interface_name)
{
 int i;

 selfp->global_data = z_string_new(CTX);
 selfp->class_data = z_string_new(CTX);
 selfp->private_data = z_string_new(CTX);
 selfp->protected_data = z_string_new(CTX);
 selfp->public_data = z_string_new(CTX);
 selfp->function_prototypes_c = z_string_new(CTX);
 selfp->function_definitions = z_string_new(CTX);
 selfp->virtual_function_ptr_inits = z_string_new(CTX);
 selfp->h_macros_head = z_string_new(CTX);
 selfp->h_macros_tail = z_string_new(CTX);
 selfp->c_macros = z_string_new(CTX);
 selfp->function_prototypes_h = z_string_new(CTX);
 selfp->function_registrations = z_string_new(CTX);
 selfp->signal_registrations = z_string_new(CTX);

 char * current_class_name_uppercase = pascal_to_uppercase(interface_name, '_');
 selfp->current_class_name_lowercase = pascal_to_lowercase(interface_name, '_');
 selfp->current_class_name_pascal = interface_name;

 /* start the private data structure */
 z_string_append_format(selfp->private_data, "struct %sPrivate \x7b\n", interface_name);

 /* start the protected data structure */
 z_string_append_format(selfp->protected_data, "struct %sProtected \x7b\n", interface_name);

 /* define the Self macro in the header file */
 z_string_append_format(selfp->h_macros_head, "#define Self %s\n", interface_name);

 /* define the macro to upcast a derived object */
 z_string_append_format(selfp->h_macros_head, "#define %s(s) ((%s *) ((char *) (s) + (s)->_global->vtable_off_list[%s_type_id]))\n\n",
 current_class_name_uppercase,
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase);

 free(current_class_name_uppercase);

 /* define the tailing macros */
 z_string_append_cstring(selfp->h_macros_tail, "#undef Self\n", Z_STRING_ENCODING_UTF8);

 /* define the Self macro in the source file */
 z_string_append_format(selfp->c_macros,
 "#define Self %s\n"
 "#define selfp (&self->_priv)\n"
 "#define GET_NEW(ctx) __%s_new(ctx)\n"
 "#define CTX self->_global->ctx\n", interface_name, selfp->current_class_name_lowercase);

 /* start the global data structure */
 z_string_append_format(selfp->global_data,
 "struct %sGlobal \x7b\n"
 "\tint *vtable_off_list;\n"
 "\tint vtable_off_size;\n"
 "\tstruct %sClass *_class;\n"
 "\tstruct zco_context_t *ctx;\n"
 "\tconst char *name;\n"
 "\tint id;\n"
 "\tvoid *method_map;\n", interface_name, interface_name);

 /* start the klass data structure */
 z_string_append_format(selfp->class_data, "struct %sClass \x7b\n", interface_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->class_data, "\tstruct %sClass parent_%s;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* start the public data structure */
 z_string_append_format(selfp->public_data, "struct %s \x7b\n", interface_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->public_data, "\tstruct %s parent_%s;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* declare the _class pointer in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %sGlobal *_global;\n", interface_name);

 /* declare the _priv member in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %sPrivate _priv;\n", interface_name);

 /* declare the _prot member in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %sProtected _prot;\n", interface_name);

 selfp->access_mode = ACCESS_PUBLIC;
 selfp->modifier_mode = MODIFIER_NONE;

 selfp->symbol_name = 0;
 selfp->type_name = 0;
 selfp->virtual_base_name = 0;

 selfp->class_needs_zvalue = 0;
 selfp->class_needs_vector = 0;
 selfp->class_needs_map = 0;
 selfp->class_needs_string = 0;
 }
#line 1111 "z-zco-source-generator.zco"
static char *  z_zco_source_generator_get_base_filename(const char *full_filename,int *base_length)
{
 char *res;
 int length = strlen(full_filename);

 if (!strcmp(full_filename+length-4, ".zco")) {
 *base_length = length-4;

 /* allocating space for full file name. we will use the spare space
                           for new file extension */
 res = malloc(length);

 /* copy base part of the filename */
 memcpy(res, full_filename, length-4);

 /* null terminate */
 res[length-4] = 0;

 return res;
 }

 return NULL;
 }
#line 1135 "z-zco-source-generator.zco"
static char * z_zco_source_generator_macro_safe(const char *s)
{
 int i, length = strlen(s);
 char *res = malloc(length + 1);

 for (i=0; i<length; ++i)
 {
 char ch = s[i];

 if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
 res[i] = ch;

 } else if (ch >= 'a' && ch <= 'z') {
 res[i] = ch + ('A' - 'a');

 } else {
 res[i] = '_';
 }
 }

 res[length] = 0;
 return res;
 }
#line 1160 "z-zco-source-generator.zco"
void  z_zco_source_generator_external_declaration(Self *self)
{
 int i;

 /* includes in header file */
 z_file_write(selfp->header_file, "#include <zco-type.h>\n");

 /* includes in the source file */
 z_file_write(selfp->source_file,
 "#include <z-map.h>\n"
 "#include <string.h>\n");

 /* head macros in header file */
 z_file_write_format(selfp->header_file, "%S\n", selfp->h_macros_head);

 z_object_unref(Z_OBJECT(selfp->h_macros_head));
 selfp->h_macros_head = NULL;


 /* forward declarations of data structures */
 z_file_write_format(selfp->header_file,
 "struct %sPrivate;\n"
 "struct %sProtected;\n"
 "struct %sGlobal;\n"
 "struct %sClass;\n"
 "struct %s;\n\n",
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal);

 /* create typedefs */
 z_file_write_format(selfp->header_file,
 "typedef struct %sPrivate %sPrivate;\n"
 "typedef struct %sProtected %sProtected;\n"
 "typedef struct %sGlobal %sGlobal;\n"
 "typedef struct %sClass %sClass;\n"
 "typedef struct %s %s;\n\n",
 selfp->current_class_name_pascal, selfp->current_class_name_pascal,
 selfp->current_class_name_pascal, selfp->current_class_name_pascal,
 selfp->current_class_name_pascal, selfp->current_class_name_pascal,
 selfp->current_class_name_pascal, selfp->current_class_name_pascal,
 selfp->current_class_name_pascal, selfp->current_class_name_pascal);

 /* private data members */
 z_file_write_format(selfp->header_file, "%S\x7d;\n\n", selfp->private_data);

 z_object_unref(Z_OBJECT(selfp->private_data));
 selfp->private_data = NULL;

 /* protected data members */
 z_file_write_format(selfp->header_file, "%S\x7d;\n\n", selfp->protected_data);

 z_object_unref(Z_OBJECT(selfp->protected_data));
 selfp->protected_data = NULL;

 /* global data members */
 z_file_write_format(selfp->header_file, "%S\x7d;\n\n", selfp->global_data);

 z_object_unref(Z_OBJECT(selfp->global_data));
 selfp->global_data = NULL;

 /* klass data members */
 z_file_write_format(selfp->header_file, "%S\x7d;\n\n", selfp->class_data);

 z_object_unref(Z_OBJECT(selfp->class_data));
 selfp->class_data = NULL;

 /* public data members */
 z_file_write_format(selfp->header_file, "%S\x7d;\n", selfp->public_data);

 z_object_unref(Z_OBJECT(selfp->public_data));
 selfp->public_data = NULL;

 /* extern variables */
 z_file_write_format(selfp->header_file, "extern int %s_type_id;\n", selfp->current_class_name_lowercase);

 /* function prototypes in header file */
 z_file_write_format(selfp->header_file, "%sGlobal * %s_get_type(struct zco_context_t *ctx);\n", selfp->current_class_name_pascal, selfp->current_class_name_lowercase);
 z_file_write_format(selfp->header_file, "void __%s_init(struct zco_context_t *ctx, %s *self);\n", selfp->current_class_name_lowercase, selfp->current_class_name_pascal);
 z_file_write_format(selfp->header_file, "void __%s_class_init(struct zco_context_t *ctx, %sClass *_class);\n", selfp->current_class_name_lowercase, selfp->current_class_name_pascal);
 z_file_write_format(selfp->header_file, "%S\n", selfp->function_prototypes_h);

 z_object_unref(Z_OBJECT(selfp->function_prototypes_h));
 selfp->function_prototypes_h = NULL;


 /* tail macros in header file */
 z_file_write_format(selfp->header_file, "%S\n", selfp->h_macros_tail);

 z_object_unref(Z_OBJECT(selfp->h_macros_tail));
 selfp->h_macros_tail = NULL;

 /* includes in source file */
 z_file_write_format(selfp->source_file,
 "#include <%s>\n"
 "#include <zco-type.h>\n"
 "#include <stdlib.h>\n",
 selfp->header_filename);

 if (selfp->class_needs_vector) {
 selfp->class_needs_vector = 0;
 z_file_write(selfp->source_file, "#include <z-vector.h>\n");
 }

 if (selfp->class_needs_map) {
 selfp->class_needs_map = 0;
 z_file_write(selfp->source_file, "#include <z-map.h>\n");
 }

 if (selfp->class_needs_zvalue) {
 selfp->class_needs_zvalue = 0;
 z_file_write(selfp->source_file, "#include <z-value.h>\n");
 }

 if (selfp->class_needs_string) {
 selfp->class_needs_string = 0;
 z_file_write(selfp->source_file, "#include <z-string.h>\n");
 }

 /* macros in source file */
 z_file_write_format(selfp->source_file, "%S\n", selfp->c_macros);

 z_object_unref(Z_OBJECT(selfp->c_macros));
 selfp->c_macros = NULL;


 /* declare the global variables */
 z_file_write_format(selfp->source_file, "int %s_type_id = -1;\n\n", selfp->current_class_name_lowercase);

 /* function prototypes in source file */
 z_file_write_format(selfp->source_file,
 "static Self *__%s_new(struct zco_context_t *ctx)\n"
 "\x7b\n"
 "\tSelf *self = (Self *) malloc(sizeof(Self));\n"
 "\t__%s_init(ctx, self);\n"
 "\treturn self;\n"
 "\x7d\n"
 "\n"
 "static int __map_compare(ZMap *map, const void *a, const void *b)\n"
 "\x7b\n"
 "\treturn strcmp(a, b);\n"
 "\x7d\n",
 selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase);

 z_file_write_format(selfp->source_file, "%S\n", selfp->function_prototypes_c);

 z_object_unref(Z_OBJECT(selfp->function_prototypes_c));
 selfp->function_prototypes_c = NULL;


 /* define cleanup_signal_arg */
 z_file_write(selfp->source_file, "static void cleanup_signal_arg(void *item, void *userdata)\n"
 "\x7b\n"
 "\tZObject **obj = (ZObject **) item;\n"
 "\tz_object_unref(*obj);\n"
 "\x7d\n");


 /* define get_type */
 z_file_write_format(selfp->source_file, "%sGlobal * %s_get_type(struct zco_context_t *ctx)\n"
 "\x7b\n"
 "\tvoid **global_ptr = NULL;\n"
 "\tif (%s_type_id != -1) \x7b\n"
 "\t\tglobal_ptr = zco_get_ctx_type(ctx, %s_type_id);\n"
 "\t\x7d\n"
 "\tif (!global_ptr || !*global_ptr) \x7b\n"
 "\t\tstruct %sGlobal *global = (%sGlobal *) malloc(sizeof(struct %sGlobal));\n"
 "\t\tglobal->ctx = ctx;\n"
 "\t\tglobal->_class = malloc(sizeof(struct %sClass));\n"
 "\t\tmemset(global->_class, 0, sizeof(struct %sClass));\n"
 "\t\tglobal->name = \"%s\";\n"
 "\t\tglobal->vtable_off_list = NULL;\n"
 "\t\tglobal->vtable_off_size = 0;\n"
 "\n"
 "\t\tstruct %s temp;\n"
 "\n",
 selfp->current_class_name_pascal, selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal, selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal);

 /* inherit the vtable from the parent class */
 for (i=0; i < selfp->parent_class_count; ++i) {
 z_file_write_format(selfp->source_file,
 "\t\t\x7b\n"
 "\t\t\tstruct %sGlobal *p_class = %s_get_type(ctx);\n"
 "\t\t\tzco_inherit_vtable(\n"
 "\t\t\t\t&global->vtable_off_list,\n"
 "\t\t\t\t&global->vtable_off_size,\n"
 "\t\t\t\tp_class->vtable_off_list,\n"
 "\t\t\t\tp_class->vtable_off_size,\n"
 "\t\t\t\t&temp,\n"
 "\t\t\t\t&temp.parent_%s);\n",
 selfp->parent_class_name_pascal[i],
 selfp->parent_class_name_lowercase[i],
 selfp->parent_class_name_lowercase[i]);

 z_file_write_format(selfp->source_file,
 "\t\t\tunsigned long offset = global->vtable_off_list[%s_type_id];\n"
 "\t\t\tmemcpy((char *) global->_class + offset, p_class->_class, sizeof(struct %sClass));\n"
 "\t\t\x7d\n",
 selfp->parent_class_name_lowercase[i],
 selfp->parent_class_name_pascal[i]);
 }

 z_file_write_format(selfp->source_file,
 "\t\tif (%s_type_id == -1)\n"
 "\t\t\t%s_type_id = zco_allocate_type_id();\n"
 "\t\tglobal->id = %s_type_id;\n"
 "\t\tzco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, %s_type_id);\n"
 "\t\tglobal_ptr = zco_get_ctx_type(ctx, %s_type_id);\n"
 "\t\t*global_ptr = global;\n"
 "\t\t\n",
 selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase,
 selfp->current_class_name_lowercase);

 /* assign the virtual function pointers */
 z_file_write_format(selfp->source_file, "%S", selfp->virtual_function_ptr_inits);

 z_file_write_format(selfp->source_file,
 "\t\t__%s_class_init(ctx, (%sClass *) global->_class);\n",
 selfp->current_class_name_lowercase,
 selfp->current_class_name_pascal);

 z_object_unref(Z_OBJECT(selfp->virtual_function_ptr_inits));
 selfp->virtual_function_ptr_inits = NULL;


 /* register methods */
 z_file_write(selfp->source_file,
 "\t\tglobal->method_map = z_map_new(ctx);\n"
 "\t\tz_map_set_compare(global->method_map, __map_compare);\n"
 "\t\tz_map_set_key_destruct(global->method_map, (ZMapItemCallback) free);\n");

 z_file_write_format(selfp->source_file, "%S", selfp->function_registrations);

 z_object_unref(Z_OBJECT(selfp->function_registrations));
 selfp->function_registrations = NULL;


 z_file_write_format(selfp->source_file,
 "\t\t#ifdef GLOBAL_INIT_EXISTS\n"
 "\t\t\tglobal_init((%sGlobal *) global);\n"
 "\t\t#endif\n",
 selfp->current_class_name_pascal);

 /* It's important to return global inside the if-block because the value of *global_ptr can become invalid
                   due to memory reallocation inside zco-type.c. Since we cannot dereference global_ptr if the if-block
                   runs, we might as well just return the previously dereferenced value */
 z_file_write_format(selfp->source_file,
 "\t\treturn global;\n"
 "\t\x7d\n"
 "\treturn (%sGlobal *) *global_ptr;\n"
 "\x7d\n\n",
 selfp->current_class_name_pascal);

 /* define *_class_init */
 z_file_write_format(selfp->source_file,
 "void __%s_class_init(struct zco_context_t *ctx, %sClass *_class)\n"
 "\x7b\n",
 selfp->current_class_name_lowercase,
 selfp->current_class_name_pascal);

 for (i=0; i < selfp->parent_class_count; ++i) {
 z_file_write_format(selfp->source_file,
 "\t__%s_class_init(ctx, (%sClass *) _class);\n",
 selfp->parent_class_name_lowercase[i],
 selfp->parent_class_name_pascal[i]);
 }

 /* call user defined class_init() */
 z_file_write(selfp->source_file,
 "\t#ifdef CLASS_INIT_EXISTS\n"
 "\t\tclass_init(ctx, _class);\n"
 "\t#endif\n"
 "\x7d\n");

 /* define *_init */
 z_file_write_format(selfp->source_file,
 "void __%s_init(struct zco_context_t *ctx, Self *self)\n"
 "\x7b\n"
 "\tstruct %sGlobal *_global = %s_get_type(ctx);\n"
 "\tself->_global = _global;\n",
 selfp->current_class_name_lowercase,
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase);

 /* to break a circular dependency between
                   vector -> object -> map -> vector,

                   we have to ensure that we don't attempt to use the vtable_off_list
                   in the particular case. since we only support single inheritance with
                   multiple interfaces, it's safe to perform a reinterpret cast when
                   the current class has only one parent.
                 */
 if (selfp->parent_class_count == 1) {
 z_file_write_format(selfp->source_file,
 "\t__%s_init(ctx, (%s *) (self));\n",
 selfp->parent_class_name_lowercase[0],
 selfp->parent_class_name_pascal[0]);

 } else {
 for (i=0; i < selfp->parent_class_count; ++i) {
 z_file_write_format(selfp->source_file,
 "\t__%s_init(ctx, %s(self));\n",
 selfp->parent_class_name_lowercase[i],
 selfp->parent_class_name_uppercase[i]);

 }
 }

 /* assign current class as the active class */
 if (!selfp->is_interface) {
 z_file_write(selfp->source_file,
 "\t((ZObject *) self)->class_base = (void *) _global->_class;\n"
 "\t((ZObject *) self)->global_base = (void *) _global;\n"
 "\t((ZObject *) self)->vtable = _global->vtable_off_list;\n");
 }

 z_file_write_format(selfp->source_file, "%S", selfp->signal_registrations);

 z_object_unref(Z_OBJECT(selfp->signal_registrations));
 selfp->signal_registrations = NULL;


 /* call user defined init() */
 z_file_write(selfp->source_file,
 "\t#ifdef INIT_EXISTS\n"
 "\t\tinit(self);\n"
 "\t#endif\n");

 /* close the system defined init() definition */
 z_file_write(selfp->source_file, "\x7d\n");

 z_file_write_format(selfp->source_file, "%S\n", selfp->function_definitions);

 z_object_unref(Z_OBJECT(selfp->function_definitions));
 selfp->function_definitions = NULL;

 free(selfp->current_class_name_lowercase);

 /* free parent class name lists */
 for (i=0; i < selfp->parent_class_count; ++i) {
 free(selfp->parent_class_name_pascal[i]);
 free(selfp->parent_class_name_lowercase[i]);
 free(selfp->parent_class_name_uppercase[i]);
 }

 if (selfp->parent_class_count > 0) {
 free(selfp->parent_class_name_pascal);
 free(selfp->parent_class_name_lowercase);
 free(selfp->parent_class_name_uppercase);
 }

 selfp->parent_class_count = 0;

 /* record line number of the end of the class */
 record_line_number(self);
 print_line_number_on_file(self, selfp->source_file);
 }
#line 1532 "z-zco-source-generator.zco"
void  z_zco_source_generator_write_header_block(Self *self,char *s)
{
 record_line_number(self);
 print_line_number_on_file(self, selfp->header_file);

 z_file_write_format(selfp->header_file, "%s\n", s);
 }
#line 1540 "z-zco-source-generator.zco"
void  z_zco_source_generator_write_source_block(Self *self,char *s)
{
 record_line_number(self);
 print_line_number_on_file(self, selfp->source_file);

 z_file_write_format(selfp->source_file, "%s\n", s);
 }
#line 1548 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_declaration(Self *self)
{
 selfp->parent_class_name_pascal = 0;
 selfp->parent_class_name_lowercase = 0;
 selfp->parent_class_name_uppercase = 0;
 selfp->parent_class_count = 0;
 selfp->is_interface = 0;
 }
#line 1557 "z-zco-source-generator.zco"
void  z_zco_source_generator_interface_declaration(Self *self)
{
 selfp->parent_class_name_pascal = 0;
 selfp->parent_class_name_lowercase = 0;
 selfp->parent_class_name_uppercase = 0;
 selfp->parent_class_count = 0;
 selfp->is_interface = 1;
 }
#line 1566 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_virtual_mode(Self *self)
{
 selfp->modifier_mode = MODIFIER_VIRTUAL;
 if (selfp->virtual_base_name) { free(selfp->virtual_base_name); } selfp->virtual_base_name=0;
 }
#line 1572 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_override_mode(Self *self,char *s)
{
 selfp->modifier_mode = MODIFIER_OVERRIDE;
 record_line_number(self);
 if (selfp->virtual_base_name) { free(selfp->virtual_base_name); } selfp->virtual_base_name=s; 
 }
#line 1579 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_access_mode(Self *self,int mode)
{
 selfp->access_mode = mode;
 }
#line 1584 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_type_name(Self *self,char *s)
{
 if (selfp->type_name)
 free(selfp->type_name);

 selfp->type_name = s;
 }
#line 1592 "z-zco-source-generator.zco"
void  z_zco_source_generator_set_symbol_name(Self *self,char *s)
{
 if (selfp->symbol_name)
 free(selfp->symbol_name);

 selfp->symbol_name=s;
 record_line_number(self);

 /* reset state */
 selfp->is_attached_property = 0;
 }
#line 1604 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_class_data_member(Self *self)
{
 add_data_member(self, selfp->access_mode, selfp->type_name, selfp->symbol_name);
 }
#line 1609 "z-zco-source-generator.zco"
void  z_zco_source_generator_add_class_virtual_data_member(Self *self)
{
 add_virtual_data_member(self, selfp->access_mode, selfp->type_name, selfp->symbol_name);
 }
#line 1614 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_virtual_member_function_decl(Self *self,char *s1,char *s2,char *s3)
{
 virtual_member_function_decl(self, selfp->type_name, s1, s2, s3); 
 }
#line 1619 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_override_member_function_decl(Self *self,char *s1,char *s2,char *s3)
{
 override_member_function_decl(self, selfp->type_name, s1, s2, s3);
 }
#line 1624 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_member_function_decl(Self *self,char *s1,char *s2,char *s3)
{
 member_function_decl(self, selfp->type_name, s1, s2, s3, 1); 
 }
#line 1629 "z-zco-source-generator.zco"
void  z_zco_source_generator_class_signal_decl(Self *self,char *s1,char *s2)
{
 signal_decl(self, selfp->type_name, s1, s2); 
 }
#line 1634 "z-zco-source-generator.zco"
void  z_zco_source_generator_finalize_property(Self *self)
{
 if (selfp->is_attached_property) {
 /* add the global map that will hold the attached property for different objects */
 char *temp = strdup2(self, "attached_", selfp->symbol_name);
 add_data_member(self, ACCESS_GLOBAL, "void *", temp);
 free(temp);
 }
 }
#line 1644 "z-zco-source-generator.zco"
void  z_zco_source_generator_enable_attached_property(Self *self)
{
 selfp->is_attached_property = 1;
 }
#line 1649 "z-zco-source-generator.zco"
int  z_zco_source_generator_setup(Self *self,int argc,char **argv)
{
 char *filename;
 int base_length;
 int rc;

 if (argc < 2)
 {
 fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
 return -1;
 }

 selfp->zco_filename = argv[1];
 filename = get_base_filename(argv[1], &base_length);
 if (filename == NULL)
 {
 fprintf(stderr, "Input file must have a .zco extension\n");
 return -1;
 }

 selfp->real_lineno = 0;

 /* open the output header file for writing */
 filename[base_length] = '.';
 filename[base_length+1] = 'h';
 filename[base_length+2] = 0;
 selfp->header_filename = strdup(filename);

 selfp->header_file = z_file_new(CTX);

 if (z_file_open(selfp->header_file, selfp->header_filename, "w") != 0) {
 fputs("zco: ", stderr);
 perror(selfp->header_filename);
 return -1;
 }

 /* write the include guard in the header file */
 char *temp = macro_safe(selfp->header_filename);
 z_file_write_format(selfp->header_file, "#ifndef _%s_\n#define _%s_\n", temp, temp);
 free(temp);

 /* open the output source file for writing */
 filename[base_length+1] = 'c';


 selfp->source_file = z_file_new(CTX);

 if (z_file_open(selfp->source_file, filename, "w") != 0) {
 fputs("zco: ", stderr);
 perror(filename);
 return -1;
 }

 free(filename);

 /* use input .zco file as standard input */
 if (freopen(argv[1], "r", stdin) == NULL) {
 fputs("zco: ", stderr);
 perror(argv[1]);
 return -1;
 }

 return 0;
 }

#line 1713 "z-zco-source-generator.zco"


