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

#line 46 "z-zco-source-generator.zco"


#include <z-string.h>

struct ZZcoSourceGenerator;

typedef void(*CallbackFunc)(struct ZZcoSourceGenerator *self, const char *method_type, int is_first, ZString *token, ZString *output);


#include <z-object-tracker.h>
#include <z-map.h>
#include <string.h>
#include <z-memory-allocator.h>
#include <z-zco-source-generator-protected.h>
#include <zco-context.h>
#include <stdlib.h>
#define Self ZZcoSourceGenerator
#define selfp (&self->_priv)
#define GET_NEW(ctx,allocator) __z_zco_source_generator_new(ctx,allocator)
#define INIT_EXISTS
#define init z_zco_source_generator_init
#define shutdown z_zco_source_generator_shutdown
#define new z_zco_source_generator_new
#define new_string z_zco_source_generator_new_string
#define print_line_number z_zco_source_generator_print_line_number
#define print_line_number_on_file z_zco_source_generator_print_line_number_on_file
#define special_member_function_decl z_zco_source_generator_special_member_function_decl
#define self_strndup z_zco_source_generator_self_strndup
#define extract_argument z_zco_source_generator_extract_argument
#define signal_decl z_zco_source_generator_signal_decl
#define add_value_arg z_zco_source_generator_add_value_arg
#define member_function_decl z_zco_source_generator_member_function_decl
#define add_data_member z_zco_source_generator_add_data_member
#define add_virtual_data_member z_zco_source_generator_add_virtual_data_member
#define define_attached_property_getter z_zco_source_generator_define_attached_property_getter
#define define_attached_property_setter z_zco_source_generator_define_attached_property_setter
#define property_decl z_zco_source_generator_property_decl
#define pascal_to_uppercase z_zco_source_generator_pascal_to_uppercase
#define pascal_to_lowercase z_zco_source_generator_pascal_to_lowercase
#define add_parent z_zco_source_generator_add_parent
#define add_function_pointer z_zco_source_generator_add_function_pointer
#define strip_out_type z_zco_source_generator_strip_out_type
#define append_stripped_arg z_zco_source_generator_append_stripped_arg
#define for_each_arg z_zco_source_generator_for_each_arg
#define virtual_member_function_decl z_zco_source_generator_virtual_member_function_decl
#define record_line_number z_zco_source_generator_record_line_number
#define override_member_function_decl z_zco_source_generator_override_member_function_decl
#define prepare_class z_zco_source_generator_prepare_class
#define prepare_interface z_zco_source_generator_prepare_interface
#define get_base_filename z_zco_source_generator_get_base_filename
#define macro_safe z_zco_source_generator_macro_safe
#define finalize_class_definition z_zco_source_generator_finalize_class_definition
#define finalize_interface_definition z_zco_source_generator_finalize_interface_definition
#define external_definition z_zco_source_generator_external_definition
#define write_header_block z_zco_source_generator_write_header_block
#define write_protected_header_block z_zco_source_generator_write_protected_header_block
#define write_source_block z_zco_source_generator_write_source_block
#define class_declaration z_zco_source_generator_class_declaration
#define interface_declaration z_zco_source_generator_interface_declaration
#define enable_virtual_mode z_zco_source_generator_enable_virtual_mode
#define enable_override_mode z_zco_source_generator_enable_override_mode
#define set_access_mode z_zco_source_generator_set_access_mode
#define set_export_option z_zco_source_generator_set_export_option
#define set_type_name z_zco_source_generator_set_type_name
#define set_symbol_name z_zco_source_generator_set_symbol_name
#define add_class_data_member z_zco_source_generator_add_class_data_member
#define add_class_virtual_data_member z_zco_source_generator_add_class_virtual_data_member
#define class_virtual_member_function_decl z_zco_source_generator_class_virtual_member_function_decl
#define class_override_member_function_decl z_zco_source_generator_class_override_member_function_decl
#define class_member_function_decl z_zco_source_generator_class_member_function_decl
#define class_signal_decl z_zco_source_generator_class_signal_decl
#define finalize_property z_zco_source_generator_finalize_property
#define enable_attached_property z_zco_source_generator_enable_attached_property
#define setup z_zco_source_generator_setup

ZCO_DEFINE_CLASS_TYPE(z_zco_source_generator);

static void z_zco_source_generator_init(Self *self);
static void  z_zco_source_generator_dispose(ZObject *object);
static void  z_zco_source_generator_print_line_number(Self *self,ZString *str);
static void  z_zco_source_generator_print_line_number_on_file(Self *self,ZFile *file);
static char *  z_zco_source_generator_self_strndup(const char *s,int max_len);
static void  z_zco_source_generator_extract_argument(ZString *arg,ZString *arg_type,ZString *arg_name);
static void  z_zco_source_generator_signal_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist);
static void  z_zco_source_generator_add_value_arg(Self *self,const char *method_type,int is_first,ZString *token,ZString *output);
static void  z_zco_source_generator_member_function_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist,ZString *code,int should_register_method);
static void  z_zco_source_generator_add_data_member(Self *self,int mode,ZString *_type_name,ZString *_symbol_name);
static void  z_zco_source_generator_add_virtual_data_member(Self *self,int mode,ZString *_type_name,ZString *_symbol_name);
static void  z_zco_source_generator_define_attached_property_getter(Self *self,ZString *symbol_name,ZString *app_code);
static void  z_zco_source_generator_define_attached_property_setter(Self *self,ZString *symbol_name,ZString *app_code);
static ZString *  z_zco_source_generator_pascal_to_uppercase(Self *self,ZString *str,char delimiter);
static ZString *  z_zco_source_generator_pascal_to_lowercase(Self *self,ZString *str,char delimiter);
static void  z_zco_source_generator_add_function_pointer(Self *self,ZString *output,ZString *_type_name,const char *_symbol_name_prefix,ZString *_symbol_name,ZString *_arglist);
static ZString * z_zco_source_generator_strip_out_type(Self *self,ZString *arg);
static void  z_zco_source_generator_append_stripped_arg(Self *self,const char *method_type,int is_first,ZString *token,ZString *output);
static void  z_zco_source_generator_for_each_arg(Self *self,ZString *output,ZString *arglist,CallbackFunc callback,const char *method_type);
static void  z_zco_source_generator_virtual_member_function_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist,ZString *code);
static void  z_zco_source_generator_override_member_function_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist,ZString *code);
static char *  z_zco_source_generator_get_base_filename(const char *full_filename,int *base_length);
static char * z_zco_source_generator_macro_safe(const char *s);
static void  z_zco_source_generator_external_definition(Self *self,int is_object);
static void z_zco_source_generator_class_destroy(ZObjectGlobal *gbl);
static void z_zco_source_generator___delete(ZObject *self);

static void cleanup_signal_arg(void *item, void *userdata)
{
	ZObject **obj = (ZObject **) item;
	z_object_unref(*obj);
}
ZZcoSourceGeneratorGlobal * z_zco_source_generator_get_type(struct zco_context_t *ctx)
{
	ZCO_CREATE_CLASS(global, ZZcoSourceGenerator, z_zco_source_generator, 1);
	ZCO_INHERIT_CLASS(ZObject, z_object, ZZcoSourceGenerator);
	ZCO_REGISTER_TYPE(z_zco_source_generator);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_zco_source_generator, dispose);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_zco_source_generator, class_destroy);
	ZCO_OVERRIDE_VIRTUAL_METHOD(ZObject, z_object, z_zco_source_generator, __delete);
	ZCO_CREATE_METHOD_MAP(ZZcoSourceGenerator, z_zco_source_generator);
	ZCO_REGISTER_METHOD(shutdown);
	ZCO_REGISTER_METHOD(new);
	ZCO_REGISTER_METHOD(new_string);
	ZCO_REGISTER_METHOD(special_member_function_decl);
	ZCO_REGISTER_METHOD(property_decl);
	ZCO_REGISTER_METHOD(add_parent);
	ZCO_REGISTER_METHOD(record_line_number);
	ZCO_REGISTER_METHOD(prepare_class);
	ZCO_REGISTER_METHOD(prepare_interface);
	ZCO_REGISTER_METHOD(finalize_class_definition);
	ZCO_REGISTER_METHOD(finalize_interface_definition);
	ZCO_REGISTER_METHOD(write_header_block);
	ZCO_REGISTER_METHOD(write_protected_header_block);
	ZCO_REGISTER_METHOD(write_source_block);
	ZCO_REGISTER_METHOD(class_declaration);
	ZCO_REGISTER_METHOD(interface_declaration);
	ZCO_REGISTER_METHOD(enable_virtual_mode);
	ZCO_REGISTER_METHOD(enable_override_mode);
	ZCO_REGISTER_METHOD(set_access_mode);
	ZCO_REGISTER_METHOD(set_export_option);
	ZCO_REGISTER_METHOD(set_type_name);
	ZCO_REGISTER_METHOD(set_symbol_name);
	ZCO_REGISTER_METHOD(add_class_data_member);
	ZCO_REGISTER_METHOD(add_class_virtual_data_member);
	ZCO_REGISTER_METHOD(class_virtual_member_function_decl);
	ZCO_REGISTER_METHOD(class_override_member_function_decl);
	ZCO_REGISTER_METHOD(class_member_function_decl);
	ZCO_REGISTER_METHOD(class_signal_decl);
	ZCO_REGISTER_METHOD(finalize_property);
	ZCO_REGISTER_METHOD(enable_attached_property);
	ZCO_REGISTER_METHOD(setup);
	#ifdef GLOBAL_INIT_EXISTS
		global_init(global);
	#endif
	return global;
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
	ZCO_INIT_START(ZZcoSourceGenerator, z_zco_source_generator);
	__z_object_init(ctx, (ZObject *) (self));
	ZCO_SEAL_CLASS();
	#ifdef INIT_EXISTS
		init(self);
	#endif
}
static void z_zco_source_generator_init(Self *self)
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);
 
 selfp->str_class_init = z_string_new(ctx, allocator);
 selfp->str_global_init = z_string_new(ctx, allocator);
 selfp->str_init = z_string_new(ctx, allocator);
 selfp->str_global_destroy = z_string_new(ctx, allocator);
 selfp->str_get = z_string_new(ctx, allocator);
 selfp->str_set = z_string_new(ctx, allocator);
 selfp->str_comma = z_string_new(ctx, allocator);
 selfp->str_zvalue = z_string_new(ctx, allocator);
 selfp->str_self = z_string_new(ctx, allocator);
 selfp->str_z = z_string_new(ctx, allocator);
 selfp->str_char = z_string_new(ctx, allocator);
 selfp->str_int8_t = z_string_new(ctx, allocator);
 selfp->str_unsigned_char = z_string_new(ctx, allocator);
 selfp->str_uint8_t = z_string_new(ctx, allocator);
 selfp->str_short = z_string_new(ctx, allocator);
 selfp->str_int16_t = z_string_new(ctx, allocator);
 selfp->str_int = z_string_new(ctx, allocator);
 selfp->str_int32_t = z_string_new(ctx, allocator);
 selfp->str_long = z_string_new(ctx, allocator);
 selfp->str_long_long = z_string_new(ctx, allocator);
 selfp->str_int64_t = z_string_new(ctx, allocator);
 selfp->str_unsigned_short = z_string_new(ctx, allocator);
 selfp->str_uint16_t = z_string_new(ctx, allocator);
 selfp->str_unsigned_int = z_string_new(ctx, allocator);
 selfp->str_uint32_t = z_string_new(ctx, allocator);
 selfp->str_unsigned_long = z_string_new(ctx, allocator);
 selfp->str_unsigned_long_long = z_string_new(ctx, allocator);
 selfp->str_uint64_t = z_string_new(ctx, allocator);
 selfp->str_float = z_string_new(ctx, allocator);
 selfp->str_double = z_string_new(ctx, allocator);
 selfp->str_void = z_string_new(ctx, allocator);
 selfp->str_class_destroy = z_string_new(ctx, allocator);
 selfp->z_object_class_name_pascal = z_string_new(ctx, allocator);

 z_string_set_cstring(selfp->str_class_init, "class_init", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_global_init, "global_init", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_init, "init", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_global_destroy, "global_destroy", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_get, "get", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_set, "set", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_comma, ",", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_zvalue, "ZValue", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_self, "Self", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_z, "Z", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_char, "char", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_int8_t, "int8_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_unsigned_char, "unsigned char", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_uint8_t, "uint8_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_short, "short", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_int16_t, "int16_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_int, "int", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_int32_t, "int32_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_long, "long", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_long_long, "long long", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_int64_t, "int64_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_unsigned_short, "unsigned short", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_uint16_t, "uint16_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_unsigned_int, "unsigned int", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_uint32_t, "uint32_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_unsigned_long, "unsigned long", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_unsigned_long_long, "unsigned long long", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_uint64_t, "uint64_t", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_float, "float", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_double, "double", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_void, "void", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->str_class_destroy, "class_destroy", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(selfp->z_object_class_name_pascal, "ZObject", Z_STRING_ENCODING_UTF8);
 }
void  z_zco_source_generator_shutdown(Self *self)
{
{
 z_file_write(selfp->protected_header_file, "\n#endif\n");
 z_file_write(selfp->header_file, "\n#endif\n");
 z_file_write(selfp->source_file, "\n\n");
 }
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_dispose
static void  z_zco_source_generator_dispose(ZObject *object)
{
 Self *self = (Self *) object;

 z_object_unref(Z_OBJECT(selfp->str_class_init));
 z_object_unref(Z_OBJECT(selfp->str_global_init));
 z_object_unref(Z_OBJECT(selfp->str_init));
 z_object_unref(Z_OBJECT(selfp->str_global_destroy));
 z_object_unref(Z_OBJECT(selfp->str_get));
 z_object_unref(Z_OBJECT(selfp->str_set));
 z_object_unref(Z_OBJECT(selfp->str_comma));
 z_object_unref(Z_OBJECT(selfp->str_zvalue));
 z_object_unref(Z_OBJECT(selfp->str_self));
 z_object_unref(Z_OBJECT(selfp->str_z));
 z_object_unref(Z_OBJECT(selfp->str_char));
 z_object_unref(Z_OBJECT(selfp->str_int8_t));
 z_object_unref(Z_OBJECT(selfp->str_unsigned_char));
 z_object_unref(Z_OBJECT(selfp->str_uint8_t));
 z_object_unref(Z_OBJECT(selfp->str_short));
 z_object_unref(Z_OBJECT(selfp->str_int16_t));
 z_object_unref(Z_OBJECT(selfp->str_int));
 z_object_unref(Z_OBJECT(selfp->str_int32_t));
 z_object_unref(Z_OBJECT(selfp->str_long));
 z_object_unref(Z_OBJECT(selfp->str_long_long));
 z_object_unref(Z_OBJECT(selfp->str_int64_t));
 z_object_unref(Z_OBJECT(selfp->str_unsigned_short));
 z_object_unref(Z_OBJECT(selfp->str_uint16_t));
 z_object_unref(Z_OBJECT(selfp->str_unsigned_int));
 z_object_unref(Z_OBJECT(selfp->str_uint32_t));
 z_object_unref(Z_OBJECT(selfp->str_unsigned_long));
 z_object_unref(Z_OBJECT(selfp->str_unsigned_long_long));
 z_object_unref(Z_OBJECT(selfp->str_uint64_t));
 z_object_unref(Z_OBJECT(selfp->str_float));
 z_object_unref(Z_OBJECT(selfp->str_double));
 z_object_unref(Z_OBJECT(selfp->str_void));
 z_object_unref(Z_OBJECT(selfp->str_class_destroy));
 z_object_unref(Z_OBJECT(selfp->z_object_class_name_pascal));

 free(selfp->header_filename);
 free(selfp->protected_header_filename);

 z_file_close(selfp->protected_header_file);
 z_file_close(selfp->header_file);
 z_file_close(selfp->source_file);

 z_object_unref(Z_OBJECT(selfp->protected_header_file));
 z_object_unref(Z_OBJECT(selfp->header_file));
 z_object_unref(Z_OBJECT(selfp->source_file));

 if (selfp->type_name) {
 z_object_unref(Z_OBJECT(selfp->type_name));
 }

 if (selfp->current_class_name_pascal) {
 z_object_unref(Z_OBJECT(selfp->current_class_name_pascal));
 }

 if (selfp->symbol_name) {
 z_object_unref(Z_OBJECT(selfp->symbol_name));
 }

 if (selfp->virtual_base_name) {
 z_object_unref(Z_OBJECT(selfp->virtual_base_name));
 }

 PARENT_HANDLER(object);
 }
#undef PARENT_HANDLER
Self * z_zco_source_generator_new(struct zco_context_t *ctx,ZMemoryAllocator *allocator)
{
{
 Self *self = GET_NEW(ctx, allocator);
 return self;
 }
}
ZString *  z_zco_source_generator_new_string(Self *self,const char *s1)
{
{
 ZString *str = z_string_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 if (s1)
 z_string_append_format(str, "%s", s1);
 return str;
 }
}
static void  z_zco_source_generator_print_line_number(Self *self,ZString *str)
{
{
 }
}
static void  z_zco_source_generator_print_line_number_on_file(Self *self,ZFile *file)
{
{
 }
}
void  z_zco_source_generator_special_member_function_decl(Self *self,ZString *symbol,ZString *arglist,ZString *code)
{
{
 if (!z_string_compare(symbol, NULL, selfp->str_class_init, NULL, 0, -1))
 z_string_append_cstring(selfp->c_macros, "#define CLASS_INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

 else if (!z_string_compare(symbol, NULL, selfp->str_global_init, NULL, 0, -1))
 z_string_append_cstring(selfp->c_macros, "#define GLOBAL_INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

 else if (!z_string_compare(symbol, NULL, selfp->str_init, NULL, 0, -1))
 z_string_append_cstring(selfp->c_macros, "#define INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

 else if (!z_string_compare(symbol, NULL, selfp->str_global_destroy, NULL, 0, -1))
 z_string_append_cstring(selfp->c_macros, "#define GLOBAL_DESTROY_EXISTS\n", Z_STRING_ENCODING_UTF8);

 print_line_number(self, selfp->c_macros);
 z_string_append_format(selfp->c_macros, "#define %S %S_%S\n", symbol, selfp->current_class_name_lowercase, symbol);

 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static void %S_%S%S;\n", selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static void %S_%S%S\n%S\n", selfp->current_class_name_lowercase, symbol, arglist, code);
 }
}
static char *  z_zco_source_generator_self_strndup(const char *s,int max_len)
{
{
 int length = strlen(s);

 if (length > max_len)
 length = max_len;

 char *str = malloc(length + 1);
 memcpy(str, s, length);
 str[length] = 0;

 return str;
 }
}
static void  z_zco_source_generator_extract_argument(ZString *arg,ZString *arg_type,ZString *arg_name)
{
{
 int length = z_string_get_length(arg);
 ZStringIter *it, *begin;

 it = z_string_get_end(arg);
 begin = z_string_get_begin(arg);

 z_string_iter_decrement(it);
 z_string_iter_decrement(begin);

 for (; !z_string_iter_is_equal(it, begin); z_string_iter_decrement(it)) {
 uint32_t ch = z_string_get_char(arg, it);

 if (ch == ' ' || ch == '*') {
 /* copy the argument name (starting after the ' ' or '*') */
 z_string_iter_increment(it);
 z_string_append(arg_name, arg, it, NULL);
 z_string_iter_decrement(it);

 /* trim the spaces from the arg_type string and copy it */
 while (!z_string_iter_is_equal(it, begin) && ch == ' ') {
 ch = z_string_get_char(arg, it);
 z_string_iter_decrement(it);
 }

 z_string_iter_increment(it);
 z_string_append(arg_type, arg, NULL, it);

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(begin));
 return;
 }
 }

 z_string_clear(arg_type);
 z_string_append(arg_name, arg, NULL, NULL);

 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(it));
 }
}
static void  z_zco_source_generator_signal_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist)
{
{
 print_line_number(self, selfp->c_macros);
 z_string_append_format(selfp->c_macros, "#define %S %S_%S\n", symbol, selfp->current_class_name_lowercase, symbol);

 switch (selfp->access_mode)
 {
 case ACCESS_PRIVATE:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static %S %S_%S%S\n", type, selfp->current_class_name_lowercase, symbol, arglist);
 break;

 case ACCESS_PUBLIC:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_h);
 z_string_append_format(selfp->function_prototypes_h, "%S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "%S %S_%S%S\n", type, selfp->current_class_name_lowercase, symbol, arglist);
 break;

 default:
 abort();
 }

 selfp->class_needs_vector = 1;
 selfp->class_needs_zvalue = 1;

 /* start of function body */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "{\n");

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\tZCO_SIGNAL_START(args);\n");

 for_each_arg(self, NULL, arglist, add_value_arg, "signal");

 /* end of function body */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "\tZCO_SIGNAL_END(args, %S)\n", symbol);

 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "}\n");

 print_line_number(self, selfp->signal_registrations);
 z_string_append_format(selfp->signal_registrations, "\tz_object_register_signal(Z_OBJECT(self), \"%S\");\n", symbol);
 }
}
static void  z_zco_source_generator_add_value_arg(Self *self,const char *method_type,int is_first,ZString *token,ZString *output)
{
{
 ZString *arg_type;
 ZString *arg_name;
 ZStringIter *last, *it;
 char *temp;
 int is_pointer, length;

 /* always skip the first argument */
 if (is_first)
 return;


 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 arg_type = z_string_new(ctx, allocator);
 arg_name = z_string_new(ctx, allocator);
 extract_argument(token, arg_type, arg_name);

 print_line_number(self, selfp->function_definitions);

 /* check if the parameter has pointers */
 length = z_string_get_length(arg_type);

 it = z_string_get_begin(arg_type);

 last = z_string_get_end(arg_type);
 z_string_iter_decrement(last);

 is_pointer = z_string_find_char(arg_type, it, '*', 0);

 /* set the value into the ZValue */
 if (is_pointer) {
 /* make sure there is at most one '*' character */
 if (!z_string_iter_is_equal(it, last)) {
 /* if the value is already a ZValue, use it directly */
 z_string_append_format(selfp->function_definitions, "\t#error \"Invalid %s parameter type %S - cannot have multipointer types\"\n", method_type, arg_type);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_zvalue, NULL, 0, 6)) {
 /* if the value is derived from ZObject, treat it as an object type */
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_ZVALUE_ARG(args, %S);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_self, NULL, 0, 4) ||
 !z_string_compare(arg_type, NULL, selfp->str_z, NULL, 0, 1)) {

 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_OBJECT_ARG(args, %S);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_char, NULL, 0, 4) ||
 !z_string_compare(arg_type, NULL, selfp->str_int8_t, NULL, 0, 6) ||
 !z_string_compare(arg_type, NULL, selfp->str_unsigned_char, NULL, 0, 13) ||
 !z_string_compare(arg_type, NULL, selfp->str_uint8_t, NULL, 0, 7)) {

 selfp->class_needs_string = 1;
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_STRING_ARG(args, %S);\n", arg_name);

 } else {
 z_string_append_format(selfp->function_definitions, "\t#error \"Invalid %s parameter type %S - Unknown pointer type\"\n", method_type, arg_type);
 }


 } else if (!z_string_compare(arg_type, NULL, selfp->str_char, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_int8_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, int8);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_short, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_int16_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, int16);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_int, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_int32_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, int32);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_long, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_long_long, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_int64_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, int64);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_unsigned_char, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_uint8_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, uint8);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_unsigned_short, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_uint16_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, uint16);\n", arg_name);


 } else if (!z_string_compare(arg_type, NULL, selfp->str_unsigned_int, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_uint32_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, uint32);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_unsigned_long, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_unsigned_long_long, NULL, 0, -1) ||
 !z_string_compare(arg_type, NULL, selfp->str_uint64_t, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, uint64);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_float, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, real32);\n", arg_name);

 } else if (!z_string_compare(arg_type, NULL, selfp->str_double, NULL, 0, -1)) {
 z_string_append_format(selfp->function_definitions, "\tZCO_ADD_PRIMITIVE_ARG(args, %S, real64);\n", arg_name);

 } else {
 z_string_append_format(selfp->function_definitions, "\t#error \"Invalid %s parameter type %S\"\n", method_type, arg_type);
 }

 z_object_unref(Z_OBJECT(arg_name));
 }
}
static void  z_zco_source_generator_member_function_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist,ZString *code,int should_register_method)
{
{
 print_line_number(self, selfp->c_macros);
 z_string_append_format(selfp->c_macros, "#define %S %S_%S\n", symbol, selfp->current_class_name_lowercase, symbol);

 switch (selfp->access_mode)
 {
 case ACCESS_PRIVATE:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static %S %S_%S%S\n{\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 if (selfp->export_option) {
 selfp->class_needs_vector = 1;
 selfp->class_needs_zvalue = 1;

 z_string_append_format(selfp->function_definitions, "\tZCO_METHOD_HOOK_START(self, args);\n");
 for_each_arg(self, NULL, arglist, add_value_arg, "method");
 z_string_append_format(selfp->function_definitions, "\tZCO_METHOD_HOOK_END(self, args, %S, %S);\n", symbol, type);
 }

 z_string_append_format(selfp->function_definitions, "%S\n}\n", code);
 break;

 case ACCESS_PROTECTED:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_ph);
 z_string_append_format(selfp->function_prototypes_ph, "%S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "%S %S_%S%S\n{\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 if (selfp->export_option) {
 selfp->class_needs_vector = 1;
 selfp->class_needs_zvalue = 1;

 z_string_append_format(selfp->function_definitions, "\tZCO_METHOD_HOOK_START(self, args);\n");
 for_each_arg(self, NULL, arglist, add_value_arg, "method");
 z_string_append_format(selfp->function_definitions, "\tZCO_METHOD_HOOK_END(self, args, %S, %S);\n", symbol, type);
 }

 z_string_append_format(selfp->function_definitions, "%S\n}\n", code);
 break;

 case ACCESS_PUBLIC:
 if (should_register_method) {
 /* register method in look up table */
 print_line_number(self, selfp->function_registrations);
 z_string_append_format(selfp->function_registrations, "\tZCO_REGISTER_METHOD(%S);\n", symbol);
 }

 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_h);
 z_string_append_format(selfp->function_prototypes_h, "%S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "%S %S_%S%S\n{\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 if (selfp->export_option) {
 selfp->class_needs_vector = 1;
 selfp->class_needs_zvalue = 1;

 z_string_append_format(selfp->function_definitions, "\tZCO_METHOD_HOOK_START(self, args);\n");
 for_each_arg(self, NULL, arglist, add_value_arg, "method");
 z_string_append_format(selfp->function_definitions, "\tZCO_METHOD_HOOK_END(self, args, %S, %S);\n", symbol, type);
 }

 z_string_append_format(selfp->function_definitions, "%S\n}\n", code);
 break;

 case ACCESS_GLOBAL:
 /* for function prototype */
 print_line_number(self, selfp->function_prototypes_h);
 z_string_append_format(selfp->function_prototypes_h, "%S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "%S %S_%S%S\n%S\n", type, selfp->current_class_name_lowercase, symbol, arglist, code);
 break;

 default:
 abort();
 }
 }
}
static void  z_zco_source_generator_add_data_member(Self *self,int mode,ZString *_type_name,ZString *_symbol_name)
{
{
 switch (mode)
 {
 case ACCESS_PRIVATE:
 print_line_number(self, selfp->private_data);
 z_string_append_format(selfp->private_data, "\t%S%S;\n", _type_name, _symbol_name);
 break;

 case ACCESS_PROTECTED:
 print_line_number(self, selfp->protected_data);
 z_string_append_format(selfp->protected_data, "\t%S%S;\n", _type_name, _symbol_name);
 break;

 case ACCESS_PUBLIC:
 print_line_number(self, selfp->public_data);
 z_string_append_format(selfp->public_data, "\t%S%S;\n", _type_name, _symbol_name);
 break;

 case ACCESS_GLOBAL:
 print_line_number(self, selfp->global_data);
 z_string_append_format(selfp->global_data, "\t%S_%S;\n", _type_name, _symbol_name);
 z_string_append_format(selfp->c_macros, "#define %S (GLOBAL_FROM_OBJECT(self)->_%S)\n", _symbol_name, _symbol_name);
 break;
 default:
 abort();
 }
 }
}
static void  z_zco_source_generator_add_virtual_data_member(Self *self,int mode,ZString *_type_name,ZString *_symbol_name)
{
{
 switch (mode)
 {
 case ACCESS_PUBLIC:
 print_line_number(self, selfp->public_data);
 z_string_append_format(selfp->class_data, "\t%S %S;\n", _type_name, _symbol_name);
 break;

 default:
 abort();
 }
 }
}
static void  z_zco_source_generator_define_attached_property_getter(Self *self,ZString *symbol_name,ZString *app_code)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 ZString *code;
 ZString *arglist = z_string_new(ctx, allocator);
 z_string_format(arglist, "(ZObject *object)");
 char *temp;
 ZString *symbol;

 /* define the helper macro to get the current value of the attached property */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions,
 "#define get_current_value() get_attached_%S(object)\n", symbol_name);

 /* define the exposed getter of the attached property */
 symbol = z_string_new(ctx, allocator);
 z_string_format(symbol, "get_%S", symbol_name);
 member_function_decl(self, selfp->type_name, symbol, arglist, app_code, 0);
 z_object_unref(Z_OBJECT(symbol));

 /* undefine the helper macro previously defined before the exposed getter */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "#undef get_current_value\n");

 /* define the method to get the value of the attached property */
 selfp->class_needs_map = 1;

 z_string_append_format(selfp->function_definitions, "ZCO_DEFINE_ATTACHED_PROP_GETTER(%S, %S, %S, %S)\n",
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase,
 symbol_name,
 selfp->type_name);

 z_object_unref(Z_OBJECT(arglist));
 }
}
static void  z_zco_source_generator_define_attached_property_setter(Self *self,ZString *symbol_name,ZString *app_code)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 ZString *arglist = z_string_new(ctx, allocator);
 z_string_format(arglist, "(ZObject *object, %S value)", selfp->type_name);
 char *temp;
 ZString *symbol;

 /* define the helper macro to get the current value of the attached property */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions,
 "#define set_current_value(val) set_attached_%S(object,value)\n", symbol_name);

 /* define the exposed setter of the attached property */
 symbol = z_string_new(ctx, allocator);
 z_string_format(symbol, "set_%S", symbol_name);
 member_function_decl(self, selfp->type_name, symbol, arglist, app_code, 0);
 z_object_unref(Z_OBJECT(symbol));
 z_object_unref(Z_OBJECT(arglist));

 /* undefine the helper macro previously defined before the exposed setter */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "#undef set_current_value\n");

 /* define the method to set the value of the attached property */
 selfp->class_needs_map = 1;

 z_string_append_format(selfp->function_definitions, "ZCO_DEFINE_ATTACHED_PROP_SETTER(%S, %S, %S)\n",
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase,
 symbol_name);
 }
}
void  z_zco_source_generator_property_decl(Self *self,ZString *get_or_set,ZString *code)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 ZString *arglist = z_string_new(ctx, allocator);
 ZString *symbol;

 if (selfp->is_attached_property) {
 /* attached property */
 if (!z_string_compare(get_or_set, NULL, selfp->str_get, NULL, 0, -1))
 define_attached_property_getter(self, selfp->symbol_name, code);

 else if (!z_string_compare(get_or_set, NULL, selfp->str_set, NULL, 0, -1))
 define_attached_property_setter(self, selfp->symbol_name, code);

 } else {
 /* regular property */

 if (!z_string_compare(get_or_set, NULL, selfp->str_get, NULL, 0, -1)) {
 z_string_format(arglist, "(Self *self)");
 symbol = z_string_new(ctx, allocator);
 z_string_format(symbol, "get_%S", selfp->symbol_name);
 member_function_decl(self, selfp->type_name, symbol, arglist, code, 0);
 z_object_unref(Z_OBJECT(symbol));

 } else if (!z_string_compare(get_or_set, NULL, selfp->str_set, NULL, 0, -1)) {
 z_string_format(arglist, "(Self *self, %S value)", selfp->type_name);
 symbol = z_string_new(ctx, allocator);
 z_string_format(symbol, "set_%S", selfp->symbol_name);

 ZString *temp2 = z_string_new(ctx, allocator);
 z_string_format(temp2, "void");
 member_function_decl(self, temp2, symbol, arglist, code, 0);
 z_object_unref(Z_OBJECT(temp2));

 z_object_unref(Z_OBJECT(symbol));
 }
 }

 z_object_unref(Z_OBJECT(arglist));
 }
}
static ZString *  z_zco_source_generator_pascal_to_uppercase(Self *self,ZString *str,char delimiter)
{
{
 ZString *res;
 ZStringIter *it, *end;
 int first = 1;

 res = z_string_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));
 it = z_string_get_begin(str);
 end = z_string_get_end(str);

 for (; !z_string_iter_is_equal(it, end); z_string_iter_increment(it)) {
 uint32_t ch = z_string_get_char(str, it);

 if (ch >= 'A' && ch <= 'Z') {
 if (!first) {
 z_string_push_back(res, delimiter);
 }

 z_string_push_back(res, ch);
 } else if (ch >= 'a' && ch <= 'z') {
 uint32_t out = ch + ('A' - 'a');
 z_string_push_back(res, out);

 } else if (ch > 0) {
 z_string_push_back(res, ch);
 } else {
 break;
 }

 first = 0;
 }

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(end));

 return res;
 }
}
static ZString *  z_zco_source_generator_pascal_to_lowercase(Self *self,ZString *str,char delimiter)
{
{
 ZString *res;
 ZStringIter *it, *end;
 int first = 1;

 res = z_string_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));

 it = z_string_get_begin(str);
 end = z_string_get_end(str);

 for (; !z_string_iter_is_equal(it, end); z_string_iter_increment(it)) {
 uint32_t ch = z_string_get_char(str, it);

 if (ch >= 'A' && ch <= 'Z') {
 if (!first)
 z_string_push_back(res, delimiter);

 uint32_t out = ch + ('a' - 'A');
 z_string_push_back(res, out);
 } else if (ch > 0) {
 z_string_push_back(res, ch);
 } else {
 break;
 }

 first = 0;
 }

 z_object_unref(Z_OBJECT(it));
 z_object_unref(Z_OBJECT(end));

 return res;
 }
}
void  z_zco_source_generator_add_parent(Self *self,ZString *name_in_pascal)
{
{
 /* increase the size of the parent class list */
 ++selfp->parent_class_count;

 selfp->parent_class_name_pascal = (ZString **) realloc(selfp->parent_class_name_pascal, sizeof(ZString *) * selfp->parent_class_count);
 selfp->parent_class_name_lowercase = (ZString **) realloc(selfp->parent_class_name_lowercase, sizeof(ZString *) * selfp->parent_class_count);
 selfp->parent_class_name_uppercase = (ZString **) realloc(selfp->parent_class_name_uppercase, sizeof(ZString *) * selfp->parent_class_count);

 /* store the name of the parent class */
 selfp->parent_class_name_pascal[selfp->parent_class_count-1] = name_in_pascal;
 selfp->parent_class_name_lowercase[selfp->parent_class_count-1] = pascal_to_lowercase(self, name_in_pascal, '_');
 selfp->parent_class_name_uppercase[selfp->parent_class_count-1] = pascal_to_uppercase(self, name_in_pascal, '_');

 z_object_ref(Z_OBJECT(name_in_pascal));
 }
}
static void  z_zco_source_generator_add_function_pointer(Self *self,ZString *output,ZString *_type_name,const char *_symbol_name_prefix,ZString *_symbol_name,ZString *_arglist)
{
{
 print_line_number(self, output);
 z_string_append_format(output, "\t%S (*%s%S)%S;\n", _type_name, _symbol_name_prefix, _symbol_name, _arglist);
 }
}
static ZString * z_zco_source_generator_strip_out_type(Self *self,ZString *arg)
{
{
 ZString *res;
 ZStringIter *it, *begin;

 it = z_string_get_end(arg);
 begin = z_string_get_begin(arg);

 z_string_iter_decrement(it);
 z_string_iter_decrement(begin);

 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 for (; !z_string_iter_is_equal(it, begin); z_string_iter_decrement(it)) {
 uint32_t ch = z_string_get_char(arg, it);
 if (ch == ' ' || ch == '*') {
 res = z_string_new(ctx, allocator);
 z_string_iter_increment(it);
 z_string_append(res, arg, it, NULL);

 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(it));

 return res;
 }
 }


 res = arg;
 z_object_ref(Z_OBJECT(res));

 z_object_unref(Z_OBJECT(begin));
 z_object_unref(Z_OBJECT(it));

 return res;
 }
}
static void  z_zco_source_generator_append_stripped_arg(Self *self,const char *method_type,int is_first,ZString *token,ZString *output)
{
{
 /* strip out the type names from the token */
 ZString *q = strip_out_type(self, token);

 if (!is_first)
 z_string_push_back(output, ',');

 z_string_append_format(output, "%S", q);
 z_object_unref(Z_OBJECT(q));
 }
}
static void  z_zco_source_generator_for_each_arg(Self *self,ZString *output,ZString *arglist,CallbackFunc callback,const char *method_type)
{
{
 int is_first = 1;
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 /* strip out the first parenthesis character */
 ZString *arglist_no_paren = z_string_new(ctx, allocator);
 ZStringIter *it1 = z_string_get_begin(arglist);
 ZStringIter *it2 = z_string_get_end(arglist);
 z_string_iter_increment(it1);
 z_string_iter_decrement(it2);
 z_string_append(arglist_no_paren, arglist, it1, it2);
 z_object_unref(Z_OBJECT(it2));
 z_object_unref(Z_OBJECT(it1));

 /* start the tokenizer */
 z_string_token_start(arglist_no_paren);

 while (1) {
 /* extract the token */
 ZStringIter *first, *last;

 first = z_string_iter_new(ctx, allocator);
 last = z_string_iter_new(ctx, allocator);

 int rc = z_string_token_next(arglist_no_paren, selfp->str_comma, first, last);

 ZString *token = z_string_new(ctx, allocator);
 z_string_append(token, arglist_no_paren, first, last);

 z_object_unref(Z_OBJECT(last));
 z_object_unref(Z_OBJECT(first));

 callback(self, method_type, is_first, token, output);
 z_object_unref(Z_OBJECT(token));

 is_first = 0;

 if (rc == 0)
 break;
 }

 z_object_unref(Z_OBJECT(arglist_no_paren));
 }
}
static void  z_zco_source_generator_virtual_member_function_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist,ZString *code)
{
{
 /* virtual function prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %S %S_virtual_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* virtual function caller */
 ZString *vcode = z_string_new(CTX_FROM_OBJECT(self), ALLOCATOR_FROM_OBJECT(self));

 if (selfp->access_mode == ACCESS_GLOBAL) {
 z_string_append_format(vcode, 
 "{\n"
 "\tZObjectClass *class_base = CLASS_FROM_GLOBAL(gbl);\n"
 "\tZCommonGlobal *common_global = class_base->real_global;\n");
 } else {
 z_string_append_format(vcode, 
 "{\n"
 "\tZObject *obj = (ZObject *) self;\n"
 "\tZObjectClass *class_base = (ZObjectClass *) obj->class_base;\n"
 "\tZCommonGlobal *common_global = class_base->real_global;\n");
 }

 z_string_append_format(vcode,
 "\tunsigned long offset = common_global->svtable_off_list[%S_type_id];\n",
 selfp->current_class_name_lowercase);

 z_string_append_format(vcode,
 "\t((%SClass *) ((char *) class_base + offset))->__%S(",
 selfp->current_class_name_pascal, symbol);

 for_each_arg(self, vcode, arglist, append_stripped_arg, NULL);
 z_string_append_cstring(vcode, ");\n}", Z_STRING_ENCODING_UTF8);

 member_function_decl(self, type, symbol, arglist, vcode, 1);
 z_object_unref(Z_OBJECT(vcode));

 /* virtual function definition */
 print_line_number(self, selfp->function_definitions);
 z_string_append_format(selfp->function_definitions, "static %S %S_virtual_%S%S\n%S\n", type, selfp->current_class_name_lowercase, symbol, arglist, code);

 /* add function pointer as a data member */
 add_function_pointer(self, selfp->class_data, type, "__", symbol, arglist);

 /* assign the address of the function into the function pointer data member */
 print_line_number(self, selfp->virtual_function_ptr_inits);
 z_string_append_format(selfp->virtual_function_ptr_inits, "\tZCO_CREATE_VIRTUAL_METHOD(%S, %S);\n", selfp->current_class_name_lowercase, symbol);
 }
}
void  z_zco_source_generator_record_line_number(Self *self)
{
{
 selfp->real_lineno = yylineno;
 }
}
static void  z_zco_source_generator_override_member_function_decl(Self *self,ZString *type,ZString *symbol,ZString *arglist,ZString *code)
{
{
 /* virtual function caller prototype */
 print_line_number(self, selfp->function_prototypes_c);
 z_string_append_format(selfp->function_prototypes_c, "static %S %S_%S%S;\n", type, selfp->current_class_name_lowercase, symbol, arglist);

 /* for function definition */
 print_line_number(self, selfp->function_definitions);

 z_string_append_format(selfp->function_definitions,
 "#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_%S\n",
 symbol);

 z_string_append_format(selfp->function_definitions,
 "static %S %S_%S%S\n%S\n"
 "#undef PARENT_HANDLER\n",
 type, selfp->current_class_name_lowercase, symbol, arglist, code);


 /* add function pointer as a data member */
 add_function_pointer(self, selfp->global_data, type, "__parent_", symbol, arglist);

 ZString *base_name_lowercase = pascal_to_lowercase(self, selfp->virtual_base_name, '_');

 /* up cast to parent class */
 /* create a pointer to the parent class's dispatch object */
 print_line_number(self, selfp->virtual_function_ptr_inits);

 z_string_append_format(selfp->virtual_function_ptr_inits,
 "\tZCO_OVERRIDE_VIRTUAL_METHOD(%S, %S, %S, %S);\n",
 selfp->virtual_base_name,
 base_name_lowercase,
 selfp->current_class_name_lowercase,
 symbol);

 z_object_unref(Z_OBJECT(base_name_lowercase));
 }
}
void  z_zco_source_generator_prepare_class(Self *self,ZString *class_name)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);
 int i;

 selfp->global_data = z_string_new(ctx, allocator);
 selfp->class_data = z_string_new(ctx, allocator);
 selfp->private_data = z_string_new(ctx, allocator);
 selfp->protected_data = z_string_new(ctx, allocator);
 selfp->public_data = z_string_new(ctx, allocator);
 selfp->function_prototypes_c = z_string_new(ctx, allocator);
 selfp->function_definitions = z_string_new(ctx, allocator);
 selfp->virtual_function_ptr_inits = z_string_new(ctx, allocator);
 selfp->h_macros_head = z_string_new(ctx, allocator);
 selfp->h_macros_tail = z_string_new(ctx, allocator);
 selfp->c_macros = z_string_new(ctx, allocator);
 selfp->function_prototypes_h = z_string_new(ctx, allocator);
 selfp->function_prototypes_ph = z_string_new(ctx, allocator);
 selfp->function_registrations = z_string_new(ctx, allocator);
 selfp->signal_registrations = z_string_new(ctx, allocator);
 selfp->attached_prop_registrations = z_string_new(ctx, allocator);
 selfp->class_destroy_code = z_string_new(ctx, allocator);

 ZString * current_class_name_uppercase = pascal_to_uppercase(self, class_name, '_');
 selfp->current_class_name_lowercase = pascal_to_lowercase(self, class_name, '_');
 selfp->current_class_name_pascal = class_name;
 z_object_ref(Z_OBJECT(class_name));

 /* start the private data structure */
 z_string_append_format(selfp->private_data, "struct %SPrivate {\n", class_name);

 /* start the protected data structure */
 z_string_append_format(selfp->protected_data, "struct %SProtected {\n", class_name);

 /* define the Self macro in the header file */
 z_string_append_format(selfp->h_macros_head, "#define Self %S\n", class_name);

 /* define the macro to upcast a derived object */
 z_string_append_format(selfp->h_macros_head, "#define %S(s) ((%S *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[%S_type_id]))\n\n",
 current_class_name_uppercase,
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase);

 z_object_unref(Z_OBJECT(current_class_name_uppercase));

 /* define the tailing macros */
 z_string_append_cstring(selfp->h_macros_tail, "#undef Self\n", Z_STRING_ENCODING_UTF8);

 /* define the Self macro in the source file */
 z_string_append_format(selfp->c_macros,
 "#define Self %S\n"
 "#define selfp (&self->_priv)\n"
 "#define GET_NEW(ctx,allocator) __%S_new(ctx,allocator)\n", class_name, selfp->current_class_name_lowercase);

 /* start the global data structure */
 z_string_append_format(selfp->global_data,
 "struct %SGlobal {\n"
 "\tZCO_CLASS_GLOBAL_HEAD(%S);\n",
 class_name, class_name);

 /* start the klass data structure */
 z_string_append_format(selfp->class_data, "struct %SClass {\n", class_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->class_data, "\tstruct %SClass parent_%S;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* start the public data structure */
 z_string_append_format(selfp->public_data, "struct %S {\n", class_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->public_data, "\tstruct %S parent_%S;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* declare the _class pointer in the public structure */
 /* declare the _priv member in the public structure */
 /* declare the _prot member in the public structure */
 z_string_append_format(selfp->public_data, "\tZCO_CLASS_PUBLIC_HEAD(%S);\n", class_name);

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
}
void  z_zco_source_generator_prepare_interface(Self *self,ZString *interface_name)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);
 int i;

 selfp->global_data = z_string_new(ctx, allocator);
 selfp->class_data = z_string_new(ctx, allocator);
 selfp->private_data = z_string_new(ctx, allocator);
 selfp->protected_data = z_string_new(ctx, allocator);
 selfp->public_data = z_string_new(ctx, allocator);
 selfp->function_prototypes_c = z_string_new(ctx, allocator);
 selfp->function_definitions = z_string_new(ctx, allocator);
 selfp->virtual_function_ptr_inits = z_string_new(ctx, allocator);
 selfp->h_macros_head = z_string_new(ctx, allocator);
 selfp->h_macros_tail = z_string_new(ctx, allocator);
 selfp->c_macros = z_string_new(ctx, allocator);
 selfp->function_prototypes_h = z_string_new(ctx, allocator);
 selfp->function_prototypes_ph = z_string_new(ctx, allocator);
 selfp->function_registrations = z_string_new(ctx, allocator);
 selfp->signal_registrations = z_string_new(ctx, allocator);
 selfp->attached_prop_registrations = z_string_new(ctx, allocator);
 selfp->class_destroy_code = z_string_new(ctx, allocator);

 ZString * current_class_name_uppercase = pascal_to_uppercase(self, interface_name, '_');
 selfp->current_class_name_lowercase = pascal_to_lowercase(self, interface_name, '_');
 selfp->current_class_name_pascal = interface_name;
 z_object_ref(Z_OBJECT(interface_name));

 /* start the private data structure */
 z_string_append_format(selfp->private_data, "struct %SPrivate {\n", interface_name);

 /* start the protected data structure */
 z_string_append_format(selfp->protected_data, "struct %SProtected {\n", interface_name);

 /* define the Self macro in the header file */
 z_string_append_format(selfp->h_macros_head, "#define Self %S\n", interface_name);

 /* define the macro to upcast a derived object */
 z_string_append_format(selfp->h_macros_head, "#define %S(s) ((%S *) ((char *) (s) + GLOBAL_FROM_CLASS(CLASS_FROM_OBJECT((ZObject *) (s)))->vtable_off_list[%S_type_id]))\n\n",
 current_class_name_uppercase,
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase);


 z_object_unref(Z_OBJECT(current_class_name_uppercase));

 /* define the tailing macros */
 z_string_append_cstring(selfp->h_macros_tail, "#undef Self\n", Z_STRING_ENCODING_UTF8);

 /* define the Self macro in the source file */
 z_string_append_format(selfp->c_macros,
 "#define Self %S\n"
 "#define selfp (&self->_priv)\n"
 "#define GET_NEW(ctx,allocator) __%S_new(ctx,allocator)\n", interface_name, selfp->current_class_name_lowercase);

 /* start the global data structure */
 z_string_append_format(selfp->global_data,
 "struct %SGlobal {\n"
 "\tstruct ZCommonGlobal common;\n"
 "\tstruct %SClass *_class;\n",
 interface_name, interface_name);

 /* start the klass data structure */
 z_string_append_format(selfp->class_data, "struct %SClass {\n", interface_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->class_data, "\tstruct %SClass parent_%S;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* start the public data structure */
 z_string_append_format(selfp->public_data, "struct %S {\n", interface_name);
 for (i=0; i<selfp->parent_class_count; ++i)
 {
 z_string_append_format(selfp->public_data, "\tstruct %S parent_%S;\n", selfp->parent_class_name_pascal[i], selfp->parent_class_name_lowercase[i]);
 }

 /* declare the _class pointer in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %SGlobal *_global;\n", interface_name);

 /* declare the _priv member in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %SPrivate _priv;\n", interface_name);

 /* declare the _prot member in the public structure */
 z_string_append_format(selfp->public_data, "\tstruct %SProtected _prot;\n", interface_name);

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
}
static char *  z_zco_source_generator_get_base_filename(const char *full_filename,int *base_length)
{
{
 char *res;
 int length = strlen(full_filename);

 if (!strcmp(full_filename+length-4, ".zco")) {
 *base_length = length-4;

 /* allocating space for full file name. we will use the spare space
                           for new file extension */
 res = malloc(length + 16);

 /* copy base part of the filename */
 memcpy(res, full_filename, length-4);

 /* null terminate */
 res[length-4] = 0;

 return res;
 }

 return NULL;
 }
}
static char * z_zco_source_generator_macro_safe(const char *s)
{
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
}
void  z_zco_source_generator_finalize_class_definition(Self *self)
{
{
 external_definition(self, 1);
 }
}
void  z_zco_source_generator_finalize_interface_definition(Self *self)
{
{
 external_definition(self, 0);
 }
}
static void  z_zco_source_generator_external_definition(Self *self,int is_object)
{
{
 int i;

 /* override z_object_class_destroy */
 if (z_string_compare(selfp->current_class_name_pascal, NULL,
 selfp->z_object_class_name_pascal, NULL,
 0, -1) != 0) {

 // FIXME: investigate this

 if (is_object) {
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 ZString *symbol = z_string_new(ctx, allocator);
 ZString *arglist = z_string_new(ctx, allocator);
 ZString *code = z_string_new(ctx, allocator);

 /* define class_destroy function */
 z_string_set_cstring(symbol, "class_destroy", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(arglist, "(ZObjectGlobal *gbl)", Z_STRING_ENCODING_UTF8);
 z_string_append_format(code,
 "{\n"
 "\t%SGlobal *_global = (%SGlobal *) gbl;\n"
 "\t#ifdef GLOBAL_DESTROY_EXISTS\n"
 "\t\tglobal_destroy(_global);\n"
 "\t#endif\n"
 "%S\n"
 "}\n",
 selfp->current_class_name_pascal,
 selfp->current_class_name_pascal,
 selfp->class_destroy_code);

 //selfp->access_mode == ACCESS_GLOBAL;
 ZString *virtual_base = z_string_new(ctx, allocator);
 z_string_set_cstring(virtual_base, "ZObject", Z_STRING_ENCODING_UTF8);
 enable_override_mode(self, virtual_base);
 z_object_unref(Z_OBJECT(virtual_base));

 override_member_function_decl(self, selfp->str_void, symbol, arglist, code);


 /* define __delete function */
 z_string_set_cstring(symbol, "__delete", Z_STRING_ENCODING_UTF8);
 z_string_set_cstring(arglist, "(ZObject *self)", Z_STRING_ENCODING_UTF8);
 z_string_clear(code);
 z_string_append_format(code,
 "{\n"
 "\tZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;\n"
 "\tif (allocator)\n"
 "\t\tz_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));\n"
 "\telse\n"
 "\t\tfree(self);\n"
 "}\n");

 virtual_base = z_string_new(ctx, allocator);
 z_string_set_cstring(virtual_base, "ZObject", Z_STRING_ENCODING_UTF8);
 enable_override_mode(self, virtual_base);
 z_object_unref(Z_OBJECT(virtual_base));

 override_member_function_decl(self, selfp->str_void, symbol, arglist, code);

 z_object_unref(Z_OBJECT(code));
 z_object_unref(Z_OBJECT(arglist));
 z_object_unref(Z_OBJECT(symbol));
 }
 }


 /* includes in header file */
 z_file_write(selfp->header_file,
 "#include <zco-context.h>\n");

 z_file_write_format(selfp->protected_header_file,
 "#include <%s>\n",
 selfp->header_filename);

 /* includes in the source file */
 z_file_write(selfp->source_file,
 "#include <z-object-tracker.h>\n"
 "#include <z-map.h>\n"
 "#include <string.h>\n"
 "#include <z-memory-allocator.h>\n");

 /* head macros in header file */
 z_file_write_format(selfp->header_file, "%S\n", selfp->h_macros_head);

 z_object_unref(Z_OBJECT(selfp->h_macros_head));
 selfp->h_macros_head = NULL;


 /* forward declarations and typedefs of data structures */
 z_file_write_format(selfp->header_file, "ZCO_TYPEDEF_FWD_DECL_CLASS(%S);\n\n", selfp->current_class_name_pascal);

 /* private data members */
 z_file_write_format(selfp->header_file, "%S};\n\n", selfp->private_data);

 z_object_unref(Z_OBJECT(selfp->private_data));
 selfp->private_data = NULL;

 /* protected data members */
 z_file_write_format(selfp->header_file, "%S};\n\n", selfp->protected_data);

 z_object_unref(Z_OBJECT(selfp->protected_data));
 selfp->protected_data = NULL;

 /* global data members */
 z_file_write_format(selfp->header_file, "%S};\n\n", selfp->global_data);

 z_object_unref(Z_OBJECT(selfp->global_data));
 selfp->global_data = NULL;

 /* klass data members */
 z_file_write_format(selfp->header_file, "%S};\n\n", selfp->class_data);

 z_object_unref(Z_OBJECT(selfp->class_data));
 selfp->class_data = NULL;

 /* public data members */
 z_file_write_format(selfp->header_file, "%S};\n", selfp->public_data);

 z_object_unref(Z_OBJECT(selfp->public_data));
 selfp->public_data = NULL;

 /* extern variables */
 z_file_write_format(selfp->header_file, "extern int %S_type_id;\n", selfp->current_class_name_lowercase);

 /* function prototypes in header file */
 z_file_write_format(selfp->header_file, "%SGlobal * %S_get_type(struct zco_context_t *ctx);\n", selfp->current_class_name_pascal, selfp->current_class_name_lowercase);
 z_file_write_format(selfp->header_file, "void __%S_init(struct zco_context_t *ctx, %S *self);\n", selfp->current_class_name_lowercase, selfp->current_class_name_pascal);
 z_file_write_format(selfp->header_file, "void __%S_class_init(struct zco_context_t *ctx, %SClass *_class);\n", selfp->current_class_name_lowercase, selfp->current_class_name_pascal);
 z_file_write_format(selfp->header_file, "%S\n", selfp->function_prototypes_h);

 z_object_unref(Z_OBJECT(selfp->function_prototypes_h));
 selfp->function_prototypes_h = NULL;

 /* function prototypes in protected header file */
 z_file_write_format(selfp->protected_header_file, "%S\n", selfp->function_prototypes_ph);

 z_object_unref(Z_OBJECT(selfp->function_prototypes_ph));
 selfp->function_prototypes_ph = NULL;


 /* tail macros in header file */
 z_file_write_format(selfp->header_file, "%S\n", selfp->h_macros_tail);

 z_object_unref(Z_OBJECT(selfp->h_macros_tail));
 selfp->h_macros_tail = NULL;

 /* includes in source file */
 z_file_write_format(selfp->source_file,
 "#include <%s>\n"
 "#include <zco-context.h>\n"
 "#include <stdlib.h>\n",
 selfp->protected_header_filename);

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
 z_file_write_format(selfp->source_file, "ZCO_DEFINE_CLASS_TYPE(%S);\n\n", selfp->current_class_name_lowercase);

 /* function prototypes in source file */
 z_file_write_format(selfp->source_file, "%S\n", selfp->function_prototypes_c);

 z_object_unref(Z_OBJECT(selfp->function_prototypes_c));
 selfp->function_prototypes_c = NULL;


 /* define cleanup_signal_arg */
 z_file_write(selfp->source_file, "static void cleanup_signal_arg(void *item, void *userdata)\n"
 "{\n"
 "\tZObject **obj = (ZObject **) item;\n"
 "\tz_object_unref(*obj);\n"
 "}\n");

 /* define get_type */
 z_file_write_format(selfp->source_file,
 "%SGlobal * %S_get_type(struct zco_context_t *ctx)\n"
 "{\n"
 "\tZCO_CREATE_CLASS(global, %S, %S, %d);\n",
 selfp->current_class_name_pascal, selfp->current_class_name_lowercase,
 selfp->current_class_name_pascal, selfp->current_class_name_lowercase, is_object);

 /* inherit the vtable from the parent class */
 for (i=0; i < selfp->parent_class_count; ++i) {
 z_file_write_format(selfp->source_file,
 "\tZCO_INHERIT_CLASS(%S, %S, %S);\n",
 selfp->parent_class_name_pascal[i],
 selfp->parent_class_name_lowercase[i],
 selfp->current_class_name_pascal);
 }

 z_file_write_format(selfp->source_file,
 "\tZCO_REGISTER_TYPE(%S);\n",
 selfp->current_class_name_lowercase);

 /* assign the virtual function pointers */
 z_file_write_format(selfp->source_file, "%S", selfp->virtual_function_ptr_inits);

 /* register methods */

 z_file_write_format(selfp->source_file, "\tZCO_CREATE_METHOD_MAP(%S, %S);\n",
 selfp->current_class_name_pascal,
 selfp->current_class_name_lowercase);


 z_object_unref(Z_OBJECT(selfp->virtual_function_ptr_inits));
 selfp->virtual_function_ptr_inits = NULL;


 z_file_write_format(selfp->source_file, "%S", selfp->function_registrations);

 z_object_unref(Z_OBJECT(selfp->function_registrations));
 selfp->function_registrations = NULL;

 /* create attached property maps */
 z_file_write_format(selfp->source_file, "%S", selfp->attached_prop_registrations);
 z_object_unref(Z_OBJECT(selfp->attached_prop_registrations));
 selfp->attached_prop_registrations = NULL;

 z_file_write_format(selfp->source_file,
 "\t#ifdef GLOBAL_INIT_EXISTS\n"
 "\t\tglobal_init(global);\n"
 "\t#endif\n");

 /* It's important to return global inside the if-block because the value of *global_ptr can become invalid
                   due to memory reallocation inside zco-context.c. Since we cannot dereference global_ptr if the if-block
                   runs, we might as well just return the previously dereferenced value */
 z_file_write_format(selfp->source_file,
 "\treturn global;\n"
 "}\n\n");

 /* define *_class_init */
 z_file_write_format(selfp->source_file,
 "void __%S_class_init(struct zco_context_t *ctx, %SClass *_class)\n"
 "{\n",
 selfp->current_class_name_lowercase,
 selfp->current_class_name_pascal);

 for (i=0; i < selfp->parent_class_count; ++i) {
 z_file_write_format(selfp->source_file,
 "\t__%S_class_init(ctx, (%SClass *) _class);\n",
 selfp->parent_class_name_lowercase[i],
 selfp->parent_class_name_pascal[i]);
 }

 /* call user defined class_init() */
 z_file_write(selfp->source_file,
 "\t#ifdef CLASS_INIT_EXISTS\n"
 "\t\tclass_init(ctx, _class);\n"
 "\t#endif\n"
 "}\n");

 z_object_unref(Z_OBJECT(selfp->class_destroy_code));
 selfp->class_destroy_code = NULL;

 /* define *_init */
 z_file_write_format(selfp->source_file,
 "void __%S_init(struct zco_context_t *ctx, Self *self)\n"
 "{\n"
 "\tZCO_INIT_START(%S, %S);\n",
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
 "\t__%S_init(ctx, (%S *) (self));\n",
 selfp->parent_class_name_lowercase[0],
 selfp->parent_class_name_pascal[0]);

 } else {
 for (i=0; i < selfp->parent_class_count; ++i) {
 z_file_write_format(selfp->source_file,
 "\t__%S_init(ctx, ((%S *) ((char *) self + GLOBAL_FROM_OBJECT(self)->common.vtable_off_list[%S_type_id])));\n",
 selfp->parent_class_name_lowercase[i],
 selfp->parent_class_name_pascal[i],
 selfp->parent_class_name_lowercase[i]);
 }
 }

 /* assign current class as the active class */
 if (!selfp->is_interface) {
 z_file_write(selfp->source_file, "\tZCO_SEAL_CLASS();\n");
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
 z_file_write(selfp->source_file, "}\n");

 z_file_write_format(selfp->source_file, "%S\n", selfp->function_definitions);

 z_object_unref(Z_OBJECT(selfp->function_definitions));
 selfp->function_definitions = NULL;

 z_object_unref(Z_OBJECT(selfp->current_class_name_lowercase));

 /* free parent class name lists */
 for (i=0; i < selfp->parent_class_count; ++i) {
 z_object_unref(Z_OBJECT(selfp->parent_class_name_pascal[i]));
 z_object_unref(Z_OBJECT(selfp->parent_class_name_lowercase[i]));
 z_object_unref(Z_OBJECT(selfp->parent_class_name_uppercase[i]));
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
}
void  z_zco_source_generator_write_header_block(Self *self,ZString *s)
{
{
 record_line_number(self);
 print_line_number_on_file(self, selfp->header_file);

 z_file_write_format(selfp->header_file, "%S\n", s);
 }
}
void  z_zco_source_generator_write_protected_header_block(Self *self,ZString *s)
{
{
 record_line_number(self);
 print_line_number_on_file(self, selfp->protected_header_file);

 z_file_write_format(selfp->protected_header_file, "%S\n", s);
 }
}
void  z_zco_source_generator_write_source_block(Self *self,ZString *s)
{
{
 record_line_number(self);
 print_line_number_on_file(self, selfp->source_file);

 z_file_write_format(selfp->source_file, "%S\n", s);
 }
}
void  z_zco_source_generator_class_declaration(Self *self)
{
{
 selfp->parent_class_name_pascal = 0;
 selfp->parent_class_name_lowercase = 0;
 selfp->parent_class_name_uppercase = 0;
 selfp->parent_class_count = 0;
 selfp->is_interface = 0;
 }
}
void  z_zco_source_generator_interface_declaration(Self *self)
{
{
 selfp->parent_class_name_pascal = 0;
 selfp->parent_class_name_lowercase = 0;
 selfp->parent_class_name_uppercase = 0;
 selfp->parent_class_count = 0;
 selfp->is_interface = 1;
 }
}
void  z_zco_source_generator_enable_virtual_mode(Self *self)
{
{
 selfp->modifier_mode = MODIFIER_VIRTUAL;
 if (selfp->virtual_base_name) {
 z_object_unref(Z_OBJECT(selfp->virtual_base_name));
 }
 selfp->virtual_base_name=0;
 }
}
void  z_zco_source_generator_enable_override_mode(Self *self,ZString *s)
{
{
 selfp->modifier_mode = MODIFIER_OVERRIDE;
 record_line_number(self);

 if (selfp->virtual_base_name) {
 z_object_unref(Z_OBJECT(selfp->virtual_base_name));
 }
 
 selfp->virtual_base_name=s; 
 z_object_ref(Z_OBJECT(s));
 }
}
void  z_zco_source_generator_set_access_mode(Self *self,int mode)
{
{
 selfp->access_mode = mode;
 }
}
void  z_zco_source_generator_set_export_option(Self *self,int option)
{
{
 selfp->export_option = option;
 }
}
void  z_zco_source_generator_set_type_name(Self *self,ZString *s)
{
{
 if (selfp->type_name)
 z_object_unref(Z_OBJECT(selfp->type_name));

 selfp->type_name = s;
 z_object_ref(Z_OBJECT(s));
 }
}
void  z_zco_source_generator_set_symbol_name(Self *self,ZString *s)
{
{
 if (selfp->symbol_name)
 z_object_unref(Z_OBJECT(selfp->symbol_name));

 selfp->symbol_name=s;
 z_object_ref(Z_OBJECT(s));
 record_line_number(self);

 /* reset state */
 selfp->is_attached_property = 0;
 }
}
void  z_zco_source_generator_add_class_data_member(Self *self)
{
{
 add_data_member(self, selfp->access_mode, selfp->type_name, selfp->symbol_name);
 }
}
void  z_zco_source_generator_add_class_virtual_data_member(Self *self)
{
{
 add_virtual_data_member(self, selfp->access_mode, selfp->type_name, selfp->symbol_name);
 }
}
void  z_zco_source_generator_class_virtual_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3)
{
{
 virtual_member_function_decl(self, selfp->type_name, s1, s2, s3); 
 }
}
void  z_zco_source_generator_class_override_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3)
{
{
 override_member_function_decl(self, selfp->type_name, s1, s2, s3);
 }
}
void  z_zco_source_generator_class_member_function_decl(Self *self,ZString *s1,ZString *s2,ZString *s3)
{
{
 member_function_decl(self, selfp->type_name, s1, s2, s3, 1); 
 set_export_option(self, 0);
 }
}
void  z_zco_source_generator_class_signal_decl(Self *self,ZString *s1,ZString *s2)
{
{
 signal_decl(self, selfp->type_name, s1, s2); 
 }
}
void  z_zco_source_generator_finalize_property(Self *self)
{
{
 if (selfp->is_attached_property) {
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

 /* add the global map that will hold the attached property for different objects */
 ZString *symbol_name = z_string_new(ctx, allocator);
 ZString *type_name = z_string_new(ctx, allocator);
 z_string_format(type_name, "void *");
 z_string_format(symbol_name, "attached_%S", selfp->symbol_name);
 add_data_member(self, ACCESS_GLOBAL, type_name, symbol_name);
 z_object_unref(Z_OBJECT(type_name));
 z_object_unref(Z_OBJECT(symbol_name));

 z_string_append_format(selfp->attached_prop_registrations,
 "\tglobal->_attached_%S = z_map_new(ctx, NULL);\n"
 "\tz_map_set_key_destruct(global->_attached_%S, (ZMapItemCallback) z_object_unref);\n",
 selfp->symbol_name,
 selfp->symbol_name);

 z_string_append_format(selfp->class_destroy_code,
 "\tz_object_unref(_global->_attached_%S);\n",
 selfp->symbol_name);

 }
 }
}
void  z_zco_source_generator_enable_attached_property(Self *self)
{
{
 selfp->is_attached_property = 1;
 }
}
int  z_zco_source_generator_setup(Self *self,int argc,char **argv)
{
{
 struct zco_context_t *ctx = CTX_FROM_OBJECT(self);
 ZMemoryAllocator *allocator = ALLOCATOR_FROM_OBJECT(self);

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

 selfp->header_file = z_file_new(ctx, allocator);

 if (z_file_open(selfp->header_file, selfp->header_filename, "w") != 0) {
 fputs("zco: ", stderr);
 perror(selfp->header_filename);
 return -1;
 }

 char *temp;

 /* write the include guard in the header file */
 temp = macro_safe(selfp->header_filename);
 z_file_write_format(selfp->header_file, "#ifndef _%s_\n#define _%s_\n", temp, temp);
 free(temp);

 /* open the output protected header file for writing */
 filename[base_length] = 0;
 strcat(filename, "-protected.h");
 selfp->protected_header_filename = strdup(filename);

 selfp->protected_header_file = z_file_new(ctx, allocator);

 if (z_file_open(selfp->protected_header_file, selfp->protected_header_filename, "w") != 0) {
 fputs("zco: ", stderr);
 perror(selfp->protected_header_filename);
 return -1;
 }

 /* write the include guard in the protected header file */
 temp = macro_safe(selfp->protected_header_filename);
 z_file_write_format(selfp->protected_header_file, "#ifndef _%s_\n#define _%s_\n", temp, temp);
 free(temp);

 /* open the output source file for writing */
 filename[base_length] = '.';
 filename[base_length+1] = 'c';
 filename[base_length+2] = 0;

 selfp->source_file = z_file_new(ctx, allocator);

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
}
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent_class_destroy
static void z_zco_source_generator_class_destroy(ZObjectGlobal *gbl)
{
	ZZcoSourceGeneratorGlobal *_global = (ZZcoSourceGeneratorGlobal *) gbl;
	#ifdef GLOBAL_DESTROY_EXISTS
		global_destroy(_global);
	#endif

}

#undef PARENT_HANDLER
#define PARENT_HANDLER GLOBAL_FROM_OBJECT(self)->__parent___delete
static void z_zco_source_generator___delete(ZObject *self)
{
	ZMemoryAllocator *allocator = CTX_FROM_OBJECT(self)->fixed_allocator;
	if (allocator)
		z_memory_allocator_deallocate_by_size(allocator, self, sizeof(Self));
	else
		free(self);
}

#undef PARENT_HANDLER



