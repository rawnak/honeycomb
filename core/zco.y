/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco.y: Parser for ZCO preprocessor
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

%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <z-string.h>

#define YYSTYPE char *

FILE *header_file, *source_file;
char *type_name, *symbol_name, *virtual_base_name;
char *header_filename;
char *zco_filename;

/* example_class_name */
char *current_class_name_lowercase;

/* ExampleClassName */
char *current_class_name_pascal;


int parent_class_count;
char **parent_class_name_lowercase;
char **parent_class_name_uppercase;
char **parent_class_name_pascal;
int is_attached_property;
int class_needs_zvalue;
int class_needs_vector;
int class_needs_map;

extern int yylineno;
int real_lineno;


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

enum access_mode_t access_mode;

enum modifier_mode_t modifier_mode;

ZString *global_data; /* struct definition for global (static) data members */
ZString *class_data; /* struct definition that is specific to the class and it inheritance */
ZString *private_data; /* struct definition for private data members */
ZString *protected_data; /* struct definition for protected data members */
ZString *public_data; /* struct definition for public data members */
ZString *function_prototypes_c; /* list of function prototypes for private member function */
ZString *function_definitions; /* list of function definitions */
ZString *virtual_function_ptr_inits; /* virtual function pointer initialization */
ZString *h_macros_head;
ZString *h_macros_tail;
ZString *c_macros;
ZString *function_prototypes_h;
ZString *signal_registrations;

static struct zco_context_t context;

int yylex(void);
void yyerror(const char *s);

static char * strdup2(const char *s1, const char *s2)
{
	ZString *str = z_string_new(&context);
	z_string_append_format(str, "%s%s", s1, s2);

	char *res = z_string_get_cstring(str, Z_STRING_ENCODING_ASCII);
	z_object_unref(Z_OBJECT(str));

	return res;
}

static char * strdup3(const char *s1, const char *s2, const char *s3)
{
	ZString *str = z_string_new(&context);
	z_string_append_format(str, "%s%s%s", s1, s2, s3);

	char *res = z_string_get_cstring(str, Z_STRING_ENCODING_ASCII);
	z_object_unref(Z_OBJECT(str));

	return res;
}

static char * strdup4(const char *s1, const char *s2, const char *s3, const char *s4)
{
	ZString *str = z_string_new(&context);
	z_string_append_format(str, "%s%s%s%s", s1, s2, s3, s4);

	char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
	z_object_unref(Z_OBJECT(str));

	return res;
}

static char * strdup5(const char *s1, const char *s2, const char *s3, const char *s4, const char *s5)
{
	ZString *str = z_string_new(&context);
	z_string_append_format(str, "%s%s%s%s%s", s1, s2, s3, s4, s5);

	char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
	z_object_unref(Z_OBJECT(str));

	return res;
}

static char * strdup6(const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6)
{
	ZString *str = z_string_new(&context);
	z_string_append_format(str, "%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6);

	char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
	z_object_unref(Z_OBJECT(str));

	return res;
}

static char * strdup7(const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6,
		const char *s7)
{
	ZString *str = z_string_new(&context);
	z_string_append_format(str, "%s%s%s%s%s%s%s", s1, s2, s3, s4, s5, s6, s7);

	char *res = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
	z_object_unref(Z_OBJECT(str));

	return res;
}

static void dump_string(ZString *str, FILE *file)
{
	z_string_validate(str);
	char *s = z_string_get_cstring(str, Z_STRING_ENCODING_UTF8);
	fputs(s, file);
	free(s);
	z_string_clear(str);
}

static void record_line_number()
{
	real_lineno = yylineno;
}

static void print_line_number(ZString *str)
{
	z_string_append_format(str, "#line %d \"%s\"\n", real_lineno, zco_filename);
}

static void special_member_function_decl(const char *symbol, const char *arglist, const char *code)
{
	if (!strcmp(symbol, "class_init"))
		z_string_append_cstring(c_macros, "#define CLASS_INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

	else if (!strcmp(symbol, "init"))
		z_string_append_cstring(c_macros, "#define INIT_EXISTS\n", Z_STRING_ENCODING_UTF8);

	print_line_number(c_macros);
	z_string_append_format(c_macros, "#define %s %s_%s\n", symbol, current_class_name_lowercase, symbol);

	/* for function prototype */
	print_line_number(function_prototypes_c);
	z_string_append_format(function_prototypes_c, "static void %s_%s%s;\n", current_class_name_lowercase, symbol, arglist);

	/* for function definition */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions, "static void %s_%s%s\n%s\n", current_class_name_lowercase, symbol, arglist, code);
}

static char * self_strndup(const char *s, int max_len)
{
	int length = strlen(s);

	if (length > max_len)
		length = max_len;

	char *str = malloc(length + 1);
	memcpy(str, s, length);
	str[length] = 0;

	return str;
}

static void extract_argument(char *arg, char **arg_type, char **arg_name)
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


static void signal_decl(const char *type, const char *symbol, const char *arglist)
{
	print_line_number(c_macros);
	z_string_append_format(c_macros, "#define %s %s_%s\n", symbol, current_class_name_lowercase, symbol);

	switch (access_mode)
	{
		case ACCESS_PRIVATE:
			/* for function prototype */
			print_line_number(function_prototypes_c);
			z_string_append_format(function_prototypes_c, "static %s %s_%s%s;\n", type, current_class_name_lowercase, symbol, arglist);

			/* for function definition */
			print_line_number(function_definitions);
			z_string_append_format(function_definitions, "static %s %s_%s%s\n", type, current_class_name_lowercase, symbol, arglist);
			break;

		case ACCESS_PUBLIC:
			/* for function prototype */
			print_line_number(function_prototypes_h);
			z_string_append_format(function_prototypes_h, "%s %s_%s%s;\n", type, current_class_name_lowercase, symbol, arglist);

			/* for function definition */
			print_line_number(function_definitions);
			z_string_append_format(function_definitions, "%s %s_%s%s\n", type, current_class_name_lowercase, symbol, arglist);
			break;

		default:
			abort();
	}

	class_needs_vector = 1;
	class_needs_zvalue = 1;

	/* start of function body */
	z_string_append_format(function_definitions,
			"{\n"
			"\tZVector *args = z_vector_new(CTX, sizeof(ZValue *));\n"
			"\tz_vector_set_item_destruct(args, (ZVectorItemCallback) z_object_unref);\n");


	char *arglist_no_paren = strdup(arglist+1);
	char *p;

	arglist_no_paren[strlen(arglist_no_paren)-1] = 0;

	p = strtok(arglist_no_paren, ",");
	while (p)
	{
		char *arg_type, *arg_name, *temp;
		int is_pointer, length;

		extract_argument(p, &arg_type, &arg_name);
		p = strtok(NULL, ",");

		/* create the ZValue object */
		z_string_append_format(function_definitions,
				"\t{\n"
				"\t\tZValue *a = z_value_new(CTX);\n");

		/* check if the parameter has pointers */
		length = strlen(arg_type);
		temp = strchr(arg_type, '*');
		is_pointer = temp != NULL;

		/* make sure there is at most one '*' character */
		if (is_pointer && temp != arg_type + (length-1))
			z_string_append_format(function_definitions, "\t\t#error \"Invalid signal parameter type %s\"\n", arg_type);

		/* set the value into the ZValue */
		else if (is_pointer && (!strncmp(arg_type, "Self", 4) || arg_type[0] == 'Z'))
			z_string_append_format(function_definitions, "\t\tz_value_set_as_object(a, Z_OBJECT(%s));\n", arg_name);

		else if (!strcmp(arg_type, "char") ||
		         !strcmp(arg_type, "int8_t")) {

			if (is_pointer)
				z_string_append_format(function_definitions, 
						"\t\tZString *_temp = z_string_new(CTX);\n"
						"\t\tz_string_set_cstring(_temp, %s, Z_STRING_ENCODING_UTF8);\n"
						"\t\tz_value_set_as_object(a, Z_OBJECT(_temp));\n"
						"\t\tz_object_unref(Z_OBJECT(_temp));\n",
						arg_name);
			else 
				z_string_append_format(function_definitions, "\t\tz_value_set_as_int8(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "short") ||
			 !strcmp(arg_type, "int16_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_int16(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "int") ||
			 !strcmp(arg_type, "int32_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_int32(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "long") ||
			 !strcmp(arg_type, "long long") ||
			 !strcmp(arg_type, "int64_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_int64(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "unsigned char") ||
			 !strcmp(arg_type, "uint8_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_uint8(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "unsigned short") ||
			 !strcmp(arg_type, "uint16_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_uint16(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "unsigned int") ||
			 !strcmp(arg_type, "uint32_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_uint32(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "unsigned long") ||
			 !strcmp(arg_type, "unsigned long long") ||
			 !strcmp(arg_type, "uint64_t")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_uint64(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "float")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_real32(a, %s);\n", arg_name);

		} else if (!strcmp(arg_type, "double")) {
			z_string_append_format(function_definitions, "\t\tz_value_set_as_real64(a, %s);\n", arg_name);

		} else {
			z_string_append_format(function_definitions, "\t\t#error \"Invalid signal parameter type %s\"\n", arg_type);
		}

		/* add the ZValue into the vector */
		z_string_append_format(function_definitions,
				"\t\tz_vector_push_back(args, a);\n"
				"\t}\n");

		free(arg_type);
		free(arg_name);
	}

	free(arglist_no_paren);

	/* end of function body */
	z_string_append_format(function_definitions,
			"\tz_object_emit_signal(Z_OBJECT(self), \"%s\", args);\n"
			"\tz_object_unref(Z_OBJECT(args));\n"
			"}\n", symbol);

	z_string_append_format(signal_registrations, "\tz_object_register_signal(Z_OBJECT(self), \"%s\");\n", symbol);
}

static void member_function_decl(const char *type, const char *symbol, const char *arglist, const char *code)
{
	print_line_number(c_macros);
	z_string_append_format(c_macros, "#define %s %s_%s\n", symbol, current_class_name_lowercase, symbol);

	switch (access_mode)
	{
		case ACCESS_PRIVATE:
			/* for function prototype */
			print_line_number(function_prototypes_c);
			z_string_append_format(function_prototypes_c, "static %s %s_%s%s;\n", type, current_class_name_lowercase, symbol, arglist);

			/* for function definition */
			print_line_number(function_definitions);
			z_string_append_format(function_definitions, "static %s %s_%s%s\n%s\n", type, current_class_name_lowercase, symbol, arglist, code);
			break;

		case ACCESS_PUBLIC:
			/* for function prototype */
			print_line_number(function_prototypes_h);
			z_string_append_format(function_prototypes_h, "%s %s_%s%s;\n", type, current_class_name_lowercase, symbol, arglist);

			/* for function definition */
			print_line_number(function_definitions);
			z_string_append_format(function_definitions, "%s %s_%s%s\n%s\n", type, current_class_name_lowercase, symbol, arglist, code);
			break;
		default:
			abort();
	}
}

static void add_data_member(int mode, const char *_type_name, const char *_symbol_name)
{
	switch (mode)
	{
		case ACCESS_PRIVATE:
			print_line_number(private_data);
			z_string_append_format(private_data, "\t%s%s;\n", _type_name, _symbol_name);
			break;

		case ACCESS_PROTECTED:
			print_line_number(protected_data);
			z_string_append_format(protected_data, "\t%s%s;\n", _type_name, _symbol_name);
			break;

		case ACCESS_PUBLIC:
			print_line_number(public_data);
			z_string_append_format(public_data, "\t%s%s;\n", _type_name, _symbol_name);
			break;

		case ACCESS_GLOBAL:
			print_line_number(global_data);
			z_string_append_format(global_data, "\t%s%s;\n", _type_name, _symbol_name);
			z_string_append_format(c_macros, "#define %s (%s_global->%s)\n", _symbol_name, current_class_name_lowercase, _symbol_name);
			break;
		default:
			abort();
	}
}

static void define_attached_property_getter(char *symbol_name, char *app_code)
{
	ZString *code;
	const char *arglist = "(ZObject *object)";
	char *symbol, *temp;

	/* define the helper macro to get the current value of the attached property */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions,
			"#define get_current_value() get_attached_%s(object)\n", symbol_name);

	/* define the exposed getter of the attached property */
	symbol = strdup2("get_", symbol_name);
	member_function_decl(type_name, symbol, arglist, app_code);
	free(symbol);

	/* undefine the helper macro previously defined before the exposed getter */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions, "#undef get_current_value\n");

	/* define the method to get the value of the attached property */
   class_needs_map = 1;
	code = z_string_new(&context);
	z_string_format(code,
		"{\n"
		"\tZMap *map = (ZMap *) attached_%s;\n"
		"\tZMapIter *it = z_map_find(map, object);\n"
		"\tvoid *value = z_map_get_value(map, it);\n"
		"\tz_object_unref(Z_OBJECT(it));\n"
		"\treturn (%s) (unsigned long) value;\n"
		"}", symbol_name, type_name);

	symbol = strdup2("get_attached_", symbol_name);
	temp = z_string_get_cstring(code, Z_STRING_ENCODING_UTF8);
	member_function_decl(type_name, symbol, arglist, temp);
	free(temp);
	free(symbol);

	z_object_unref(Z_OBJECT(code));
}

static void define_attached_property_setter(char *symbol_name, char *app_code)
{
	ZString *code;
	char *arglist = strdup3("(ZObject *object, ", type_name, " value)");
	char *symbol, *temp;

	/* define the helper macro to get the current value of the attached property */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions,
			"#define set_current_value(val) set_attached_%s(object,value)\n", symbol_name);

	/* define the exposed setter of the attached property */
	symbol = strdup2("set_", symbol_name);
	member_function_decl(type_name, symbol, arglist, app_code);
	free(symbol);

	/* undefine the helper macro previously defined before the exposed setter */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions, "#undef set_current_value\n");

	/* define the method to set the value of the attached property */
   class_needs_map = 1;
	code = z_string_new(&context);
	z_string_format(code,
		"{\n"
		"\tZMap *map = (ZMap *) attached_%s;\n"
		"\tif (z_map_assign(map, object, (void *) (unsigned long) value) == 0)\n"
		"\t\tz_object_add_attached_property_map(object, map);\n"
		"}", symbol_name);

	symbol = strdup2("set_attached_", symbol_name);
	temp = z_string_get_cstring(code, Z_STRING_ENCODING_UTF8);
	member_function_decl("void", symbol, arglist, temp);
	free(temp);
	free(symbol);
	free(arglist);

	z_object_unref(Z_OBJECT(code));
}

static void property_decl(char *get_or_set, char *code)
{
	char *arglist, *symbol;

	if (is_attached_property) {
		/* attached property */
		if (!strcmp(get_or_set, "get"))
			define_attached_property_getter(symbol_name, code);

		else if (!strcmp(get_or_set, "set"))
			define_attached_property_setter(symbol_name, code);

	} else {
		/* regular property */

		if (!strcmp(get_or_set, "get")) {
			arglist = "(Self *self)";
			symbol = strdup2("get_", symbol_name);
			member_function_decl(type_name, symbol, arglist, code);
			free(symbol);

		} else if (!strcmp(get_or_set, "set")) {
			arglist = strdup3("(Self *self, ", type_name, " value)");
			symbol = strdup2("set_", symbol_name);
			member_function_decl("void", symbol, arglist, code);
			free(arglist);
			free(symbol);
		}
	}
}

static char * pascal_to_uppercase(const char *s, char delimiter)
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

static char * pascal_to_lowercase(const char *s, char delimiter)
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

static void add_parent(char *name_in_pascal)
{
	/* increase the size of the parent class list */
	++parent_class_count;

	parent_class_name_pascal = (char **) realloc(parent_class_name_pascal, sizeof(char *) * parent_class_count);
	parent_class_name_lowercase = (char **) realloc(parent_class_name_lowercase, sizeof(char *) * parent_class_count);
	parent_class_name_uppercase = (char **) realloc(parent_class_name_uppercase, sizeof(char *) * parent_class_count);

	/* store the name of the parent class */
	parent_class_name_pascal[parent_class_count-1] = name_in_pascal;
	parent_class_name_lowercase[parent_class_count-1] = pascal_to_lowercase(name_in_pascal, '_');
	parent_class_name_uppercase[parent_class_count-1] = pascal_to_uppercase(name_in_pascal, '_');
}

static void add_function_pointer(ZString *output, const char *_type_name, const char *_symbol_name_prefix, const char *_symbol_name, const char *_arglist)
{
	print_line_number(output);
	z_string_append_format(output, "\t%s (*%s%s)%s;\n", _type_name, _symbol_name_prefix, _symbol_name, _arglist);
}

static char *strip_out_type(char *arg)
{
	int i, length = strlen(arg);

	for (i=length-1; i>=0; --i) {
		if (arg[i] == ' ' || arg[i] == '*')
			return arg + (i+1);
	}

	return arg;
}

static void strip_out_types(ZString *str, const char *arglist)
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

static void virtual_member_function_decl(const char *type, const char *symbol, const char *arglist, const char *code)
{
	if (access_mode == ACCESS_PRIVATE) {
		yyerror("Cannot declare virtual function with private access specifier");
	}

	/* virtual function prototype */
	print_line_number(function_prototypes_c);
	z_string_append_format(function_prototypes_c, "static %s %s_virtual_%s%s;\n", type, current_class_name_lowercase, symbol, arglist);

	/* virtual function caller */
	ZString *vcode = z_string_new(&context);

	z_string_append_format(vcode, 
			"{\n"
			"\tZObject *obj = (ZObject *) self;\n"
			"\t((%sClass *) ((char *) obj->class_base + obj->vtable[%s_type_id]))->__%s(",
			current_class_name_pascal, current_class_name_lowercase, symbol);

	strip_out_types(vcode, arglist);
	z_string_append_cstring(vcode, ");\n}", Z_STRING_ENCODING_UTF8);

	char *temp = z_string_get_cstring(vcode, Z_STRING_ENCODING_UTF8);
	member_function_decl(type, symbol, arglist, temp);

	free(temp);
	z_object_unref(Z_OBJECT(vcode));

	/* virtual function definition */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions, "static %s %s_virtual_%s%s\n%s\n", type, current_class_name_lowercase, symbol, arglist, code);

	/* add function pointer as a data member */
	add_function_pointer(class_data, type, "__", symbol, arglist);

	/* assign the address of the function into the function pointer data member */
	print_line_number(virtual_function_ptr_inits);
	z_string_append_format(virtual_function_ptr_inits, "\t\tglobal->_class->__%s = %s_virtual_%s;\n", symbol, current_class_name_lowercase, symbol);
}

static void override_member_function_decl(const char *type, const char *symbol, const char *arglist, const char *code)
{
	/* virtual function caller prototype */
	print_line_number(function_prototypes_c);
	z_string_append_format(function_prototypes_c, "static %s %s_%s%s;\n", type, current_class_name_lowercase, symbol, arglist);

	/* for function definition */
	print_line_number(function_definitions);
	z_string_append_format(function_definitions,
			"#define PARENT_HANDLER self->_global->__parent_%s\n"
			"static %s %s_%s%s\n%s\n"
			"#undef PARENT_HANDLER\n",
			symbol,
			type, current_class_name_lowercase, symbol, arglist, code);

	/* add function pointer as a data member */
	add_function_pointer(global_data, type, "__parent_", symbol, arglist);

	char *base_name_uppercase = pascal_to_uppercase(virtual_base_name, '_');
	char *base_name_lowercase = pascal_to_lowercase(virtual_base_name, '_');

	/* up cast to parent class */
	print_line_number(virtual_function_ptr_inits);
	z_string_append_cstring(virtual_function_ptr_inits, "\t\t{\n", Z_STRING_ENCODING_UTF8);

	/* create a pointer to the parent class's dispatch object */
	print_line_number(virtual_function_ptr_inits);
	z_string_append_format(virtual_function_ptr_inits, "\t\t\t%sClass *p_class = (%sClass *) ((char *) global->_class + global->vtable_off_list[%s_type_id]);\n",
			virtual_base_name, virtual_base_name, base_name_lowercase);
	
	/* backup the existing virtual function pointer for the PARENT_HANDLER macro */
	print_line_number(virtual_function_ptr_inits);
	z_string_append_format(virtual_function_ptr_inits, "\t\t\tglobal->__parent_%s = p_class->__%s;\n", symbol, symbol);

	/* assign the address of the function into the function pointer data member */
	print_line_number(virtual_function_ptr_inits);
	z_string_append_format(virtual_function_ptr_inits, "\t\t\tp_class->__%s = %s_%s;\n", symbol, current_class_name_lowercase, symbol);

	print_line_number(virtual_function_ptr_inits);
	z_string_append_cstring(virtual_function_ptr_inits, "\t\t}\n", Z_STRING_ENCODING_UTF8);

	free(base_name_lowercase);
	free(base_name_uppercase);
}

static void class_init(char *class_name)
{
	int i;

	global_data = z_string_new(&context);
	class_data = z_string_new(&context);
	private_data = z_string_new(&context);
	protected_data = z_string_new(&context);
	public_data = z_string_new(&context);
	function_prototypes_c = z_string_new(&context);
	function_definitions = z_string_new(&context);
	virtual_function_ptr_inits = z_string_new(&context);
	h_macros_head = z_string_new(&context);
	h_macros_tail = z_string_new(&context);
	c_macros = z_string_new(&context);
	function_prototypes_h = z_string_new(&context);
	signal_registrations = z_string_new(&context);

	char * current_class_name_uppercase = pascal_to_uppercase(class_name, '_');
	current_class_name_lowercase = pascal_to_lowercase(class_name, '_');
	current_class_name_pascal = class_name;

	/* start the private data structure */
	z_string_append_format(private_data, "struct %sPrivate {\n", class_name);

	/* start the protected data structure */
	z_string_append_format(protected_data, "struct %sProtected {\n", class_name);

	/* define the Self macro in the header file */
	z_string_append_format(h_macros_head, "#define Self %s\n", class_name);

	/* define the macro to upcast a derived object */
	z_string_append_format(h_macros_head, "#define %s(s) ((%s *) (s))\n\n", current_class_name_uppercase, current_class_name_pascal);
	free(current_class_name_uppercase);

	/* define the tailing macros */
	z_string_append_cstring(h_macros_tail, "#undef Self\n", Z_STRING_ENCODING_UTF8);

	/* define the Self macro in the source file */
	z_string_append_format(c_macros,
			"#define Self %s\n"
			"#define selfp (&self->_priv)\n"
			"#define GET_NEW(ctx) __%s_new(ctx)\n"
			"#define CTX self->_global->ctx\n", class_name, current_class_name_lowercase);

	/* start the global data structure */
	z_string_append_format(global_data,
			"struct %sGlobal {\n"
			"\tint *vtable_off_list;\n"
			"\tint vtable_off_size;\n"
			"\tstruct %sClass *_class;\n"
			"\tstruct zco_context_t *ctx;\n"
			"\tconst char *name;\n"
			"\tint id;\n", class_name, class_name);

	/* start the klass data structure */
	z_string_append_format(class_data, "struct %sClass {\n", class_name);
	for (i=0; i<parent_class_count; ++i)
	{
		z_string_append_format(class_data, "\tstruct %sClass parent_%s;\n", parent_class_name_pascal[i], parent_class_name_lowercase[i]);
	}

	/* start the public data structure */
	z_string_append_format(public_data, "struct %s {\n", class_name);
	for (i=0; i<parent_class_count; ++i)
	{
		z_string_append_format(public_data, "\tstruct %s parent_%s;\n", parent_class_name_pascal[i], parent_class_name_lowercase[i]);
	}

	/* declare the _class pointer in the public structure */
	z_string_append_format(public_data, "\tstruct %sGlobal *_global;\n", class_name);

	/* declare the _priv member in the public structure */
	z_string_append_format(public_data, "\tstruct %sPrivate _priv;\n", class_name);

	/* declare the _prot member in the public structure */
	z_string_append_format(public_data, "\tstruct %sProtected _prot;\n", class_name);

	access_mode = ACCESS_PUBLIC;
	modifier_mode = MODIFIER_NONE;


	symbol_name = 0;
	type_name = 0;
	virtual_base_name = 0;

   class_needs_zvalue = 0;
   class_needs_vector = 0;
   class_needs_map = 0;
}

%}

%token HEADER_BLK_START SOURCE_BLK_START FILE_BLK_END CLASS STRUCT UNION CONST SIGNED UNSIGNED COLON GLOBAL PUBLIC PRIVATE PROPERTY GET SET 
%token OVERRIDE VIRTUAL WORD CODE OBRACE EBRACE OPAREN EPAREN SEMICOLON VAR_ARGS SPACE ASTERISK COMMENT COMMA HASH BANG


%start translation_unit

%%

translation_unit
: external_declaration
| translation_unit external_declaration 
| ignorable                      { free($1); }
| translation_unit ignorable     { free($2); }
;

external_declaration
: header_block
| source_block
| class_definition
{
	int i;

	/* includes in header file */
	fprintf(header_file, "#include <zco-type.h>\n");

	/* includes in the source file */
	fprintf(source_file, "#include <string.h>\n");

	/* head macros in header file */
	dump_string(h_macros_head, header_file);
	fprintf(header_file, "\n");

	/* forward declarations of data structures */
	fprintf(header_file,
			"struct %sPrivate;\n"
			"struct %sProtected;\n"
			"struct %sGlobal;\n"
			"struct %sClass;\n"
			"struct %s;\n\n",
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal);

	/* create typedefs */
	fprintf(header_file,
			"typedef struct %sPrivate %sPrivate;\n"
			"typedef struct %sProtected %sProtected;\n"
			"typedef struct %sGlobal %sGlobal;\n"
			"typedef struct %sClass %sClass;\n"
			"typedef struct %s %s;\n\n",
			current_class_name_pascal, current_class_name_pascal,
			current_class_name_pascal, current_class_name_pascal,
			current_class_name_pascal, current_class_name_pascal,
			current_class_name_pascal, current_class_name_pascal,
			current_class_name_pascal, current_class_name_pascal);

	/* private data members */
	dump_string(private_data, header_file);
	fprintf(header_file, "};\n\n");

	/* protected data members */
	dump_string(protected_data, header_file);
	fprintf(header_file, "};\n\n");

	/* global data members */
	dump_string(global_data, header_file);
	fprintf(header_file, "};\n\n");

	/* klass data members */
	dump_string(class_data, header_file);
	fprintf(header_file, "};\n\n");

	/* public data members */
	dump_string(public_data, header_file);
	fprintf(header_file, "};\n");

	/* extern variables */
	fprintf(header_file, "extern int %s_type_id;\n", current_class_name_lowercase);

	/* function prototypes in header file */
	fprintf(header_file, "%sGlobal * %s_get_type(struct zco_context_t *ctx);\n", current_class_name_pascal, current_class_name_lowercase);
	fprintf(header_file, "void __%s_init(struct zco_context_t *ctx, %s *self);\n", current_class_name_lowercase, current_class_name_pascal);
	dump_string(function_prototypes_h, header_file);
	fprintf(header_file, "\n");

	/* tail macros in header file */
	dump_string(h_macros_tail, header_file);
	fprintf(header_file, "\n");

	/* includes in source file */
	fprintf(source_file,
			"#include <%s>\n"
			"#include <zco-type.h>\n"
			"#include <stdlib.h>\n",
			header_filename);

   if (class_needs_vector) {
      class_needs_vector = 0;
      fprintf(source_file, "#include <z-vector.h>\n");
   }

   if (class_needs_map) {
      class_needs_map = 0;
      fprintf(source_file, "#include <z-map.h>\n");
   }

   if (class_needs_zvalue) {
      class_needs_zvalue = 0;
      fprintf(source_file, "#include <z-value.h>\n");
   }

	/* macros in source file */
	dump_string(c_macros, source_file);
	fprintf(source_file, "\n");

	/* declare the global variables */
	fprintf(source_file, "int %s_type_id = -1;\n", current_class_name_lowercase);
	fprintf(source_file, "static %sGlobal * %s_global;\n", current_class_name_pascal, current_class_name_lowercase);
	fprintf(source_file, "\n");

	/* function prototypes in source file */
	fprintf(source_file,
			"static Self *__%s_new(struct zco_context_t *ctx)\n"
			"{\n"
			"\tSelf *self = (Self *) malloc(sizeof(Self));\n"
			"\t__%s_init(ctx, self);\n"
			"\treturn self;\n"
			"}\n",
			current_class_name_lowercase,
			current_class_name_lowercase);

	dump_string(function_prototypes_c, source_file);
	fprintf(source_file, "\n");

	/* define get_type */
	fprintf(source_file, "%sGlobal * %s_get_type(struct zco_context_t *ctx)\n"
			"{\n"
			"\tif (%s_type_id == -1)\n"
			"\t\t%s_type_id = zco_allocate_type_id();\n\n"
			"\tvoid **global_ptr = zco_get_ctx_type(ctx, %s_type_id);\n"
			"\tif (*global_ptr == 0) {\n"
			"\t\t*global_ptr = malloc(sizeof(struct %sGlobal));\n"
			"\t\tstruct %sGlobal *global = (%sGlobal *) *global_ptr;\n"
			"\t\t%s_global = global;\n"
			"\t\tglobal->ctx = ctx;\n"
			"\t\tglobal->_class = malloc(sizeof(struct %sClass));\n"
			"\t\tmemset(global->_class, 0, sizeof(struct %sClass));\n"
			"\t\tglobal->name = \"%s\";\n"
			"\t\tglobal->id = %s_type_id;\n"
			"\t\tglobal->vtable_off_list = NULL;\n"
			"\t\tglobal->vtable_off_size = 0;\n"
			"\n"
			"\t\tstruct %sClass temp;\n"
			"\n",
			current_class_name_pascal, current_class_name_lowercase,
			current_class_name_lowercase,
			current_class_name_lowercase,
			current_class_name_lowercase,
			current_class_name_pascal,
			current_class_name_pascal, current_class_name_pascal,
			current_class_name_lowercase,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_lowercase,
			current_class_name_pascal);

	/* inherit the vtable from the parent class */
	for (i=0; i < parent_class_count; ++i) {
		fprintf(source_file,
				"\t\t{\n"
				"\t\t\tstruct %sGlobal *p_class = %s_get_type(ctx);\n"
				"\t\t\tzco_inherit_vtable(\n"
				"\t\t\t\t&global->vtable_off_list,\n"
				"\t\t\t\t&global->vtable_off_size,\n"
				"\t\t\t\tp_class->vtable_off_list,\n"
				"\t\t\t\tp_class->vtable_off_size,\n"
				"\t\t\t\t&temp,\n"
				"\t\t\t\t&temp.parent_%s);\n",
				parent_class_name_pascal[i],
				parent_class_name_lowercase[i],
				parent_class_name_lowercase[i]);

		fprintf(source_file,
				"\t\t\tunsigned long offset = global->vtable_off_list[%s_type_id];\n"
				"\t\t\tmemcpy((char *) global->_class + offset, p_class->_class, sizeof(struct %sClass));\n",
				parent_class_name_lowercase[i],
				parent_class_name_pascal[i]);

		fprintf(source_file, "\t\t}\n");
	}

	fprintf(source_file,
			"\t\tzco_add_to_vtable(&global->vtable_off_list, &global->vtable_off_size, %s_type_id);"
			"\t\t\n",
			current_class_name_lowercase);

	/* assign the virtual function pointers */
	dump_string(virtual_function_ptr_inits, source_file);

	fprintf(source_file,
			"\t\t#ifdef CLASS_INIT_EXISTS\n"
			"\t\t\tclass_init((%sGlobal *) global);\n"
			"\t\t#endif\n",
			current_class_name_pascal);

	fprintf(source_file,
			"\t}\n"
			"\treturn (%sGlobal *) *global_ptr;\n"
			"}\n\n",
			current_class_name_pascal);

	/* define *_init */
	fprintf(source_file,
			"void __%s_init(struct zco_context_t *ctx, Self *self)\n"
			"{\n"
			"\tstruct %sGlobal *_global = %s_get_type(ctx);\n"
			"\tself->_global = _global;\n",
			current_class_name_lowercase,
			current_class_name_pascal,
			current_class_name_lowercase);

	for (i=0; i < parent_class_count; ++i) {
		fprintf(source_file,
				"\t__%s_init(ctx, %s(self));\n",
				parent_class_name_lowercase[i],
				parent_class_name_uppercase[i]);

	}


	/* assign current class as the active class */
	fprintf(source_file, "\t((ZObject *) self)->class_base = (void *) _global->_class;\n");
	fprintf(source_file, "\t((ZObject *) self)->vtable = _global->vtable_off_list;\n");

	/* call user defined init() */
	fprintf(source_file,
			"\t#ifdef INIT_EXISTS\n"
			"\t\tinit(self);\n"
			"\t#endif\n");

	/* register signals */
	dump_string(signal_registrations, source_file);

	/* close the system defined init() definition */
	fprintf(source_file, "}\n");

	dump_string(function_definitions, source_file);
	fprintf(source_file, "\n");

	free(current_class_name_lowercase);

	/* free parent class name lists */
	for (i=0; i < parent_class_count; ++i) {
		free(parent_class_name_pascal[i]);
		free(parent_class_name_lowercase[i]);
		free(parent_class_name_uppercase[i]);
	}

	if (parent_class_count > 0) {
		free(parent_class_name_pascal);
		free(parent_class_name_lowercase);
		free(parent_class_name_uppercase);
	}
}
;

header_block_start
	: HEADER_BLK_START 
	;

source_block_start
	: SOURCE_BLK_START 
	;

header_block
	: header_block_start ccodes FILE_BLK_END
	{
		fprintf(header_file, "%s\n", $2);
		free($2);
	}
	;

source_block
	: source_block_start ccodes FILE_BLK_END
	{
		fprintf(source_file, "%s\n", $2);
		free($2);
	}
	;

ccodes_block
	: OBRACE ccodes EBRACE { $$=strdup3($1,$2,$3); free($2); }
	| OBRACE EBRACE        { $$=strdup2($1,$2); }
	;

ccodes
	: CODE
	| ccodes CODE
	{ $$=strdup2($1,$2); free($1); free($2); }

	| WORD
	| ccodes WORD
	{ $$=strdup2($1,$2); free($1); free($2); }

	| CLASS
	{ $$=strdup($1); }

	| ccodes CLASS
	{ $$=strdup2($1,$2); free($1); }

	| struct_union
	{ $$=strdup($1); }

	| ccodes struct_union
	{ $$=strdup2($1,$2); free($1); }

	| VAR_ARGS
	{ $$=strdup($1); }

	| ccodes VAR_ARGS
	{ $$=strdup2($1,$2); free($1); }

	| CONST
	{ $$=strdup($1); }

	| ccodes CONST
	{ $$=strdup2($1,$2); free($1); }

	| sign
	{ $$=strdup($1); }

	| ccodes sign
	{ $$=strdup2($1,$2); free($1); }

	| COLON
	{ $$=strdup($1); }

	| ccodes COLON
	{ $$=strdup2($1,$2); free($1); }

	| COMMA
	{ $$=strdup($1); }

	| ccodes COMMA
	{ $$=strdup2($1,$2); free($1); }

	| OPAREN
	{ $$=strdup($1); }

	| ccodes OPAREN
	{ $$=strdup2($1,$2); free($1); }

	| EPAREN
	{ $$=strdup($1); }

	| ccodes EPAREN
	{ $$=strdup2($1,$2); free($1); }

	| ASTERISK
	{ $$=strdup($1); }

	| ccodes ASTERISK
	{ $$=strdup2($1,$2); free($1); }

	| HASH
	{ $$=strdup($1); }

	| ccodes HASH
	{ $$=strdup2($1,$2); free($1); }

	| BANG
	{ $$=strdup($1); }

	| ccodes BANG
	{ $$=strdup2($1,$2); free($1); }

	| SEMICOLON
	{ $$=strdup($1); }

	| ccodes SEMICOLON
	{ $$=strdup2($1,$2); free($1); }

	| GLOBAL
	{ $$=strdup($1); }

	| ccodes GLOBAL
	{ $$=strdup2($1,$2); free($1); }

	| PUBLIC
	{ $$=strdup($1); }

	| ccodes PUBLIC
	{ $$=strdup2($1,$2); free($1); }

	| PRIVATE
	{ $$=strdup($1); }

	| ccodes PRIVATE
	{ $$=strdup2($1,$2); free($1); }

	| PROPERTY
	{ $$=strdup($1); }

	| ccodes PROPERTY
	{ $$=strdup2($1,$2); free($1); }

	| GET
	{ $$=strdup($1); }

	| ccodes GET
	{ $$=strdup2($1,$2); free($1); }

	| SET
	{ $$=strdup($1); }

	| ccodes SET
	{ $$=strdup2($1,$2); free($1); }

	| OVERRIDE
	{ $$=strdup($1); }

	| ccodes OVERRIDE
	{ $$=strdup2($1,$2); free($1); }

	| VIRTUAL
	{ $$=strdup($1); }

	| ccodes VIRTUAL
	{ $$=strdup2($1,$2); free($1); }

	| ignorable
	| ccodes ignorable
	{ $$=strdup2($1,$2); free($1); free($2); }

	| ccodes_block
	| ccodes ccodes_block
	{ $$=strdup2($1,$2); free($1); free($2); }
	;

subclass_declaration
	: CLASS ignorables WORD 
	{
		parent_class_name_pascal = 0;
		parent_class_name_lowercase = 0;
		parent_class_name_uppercase = 0;
		parent_class_count = 0;

		$$=$3;
		free($2);
	}
	;

/* $4 should not be freed because it will be pointed to by parent_class_name_pascal */
parent_declaration
	: WORD
	{ add_parent($1); }

	| parent_declaration COMMA WORD
	{ add_parent($3); }

	| parent_declaration COMMA ignorables WORD
	{ add_parent($4); free($3); }

	| parent_declaration ignorables COMMA WORD
	{ add_parent($4); free($2); }

	| parent_declaration ignorables COMMA ignorables WORD
	{ add_parent($5); free($2); free($4); }
	;


/* $1 should not be freed because it will be pointed to by current_class_name_pascal */
full_class_declaration
	: subclass_declaration
	{ class_init($1); }

	| subclass_declaration ignorables
	{ class_init($1); free($2); }

	| subclass_declaration ignorables COLON ignorables parent_declaration
	{ class_init($1); free($2); }

	| subclass_declaration ignorables COLON ignorables parent_declaration ignorables
	{ class_init($1); free($2); free($4); free($6); }
	;

class_definition
	: full_class_declaration OBRACE class_objects EBRACE
	;

class_objects
	: class_object 
	| class_objects class_object 
	| ignorable                      { free($1); }
	| class_objects ignorable        { free($2); }
	;

argument_list
	: OPAREN EPAREN               { $$=strdup("()"); }
	| OPAREN ignorables EPAREN    { $$=strdup("()"); free($2); }
	| OPAREN arguments EPAREN     { $$=strdup3("(",$2,")"); }
	;

arguments
	: argument
	| arguments COMMA argument
	{ $$=strdup3($1,$2,$3); free($1); free($3);  }

	| arguments COMMA ignorables argument
	{ $$=strdup3($1,$2,$4); free($1); free($3); free($4);  }

	| arguments COMMA ignorables argument ignorables
	{ $$=strdup3($1,$2,$4); free($1); free($3); free($4);  }
	;

pointers
	: ASTERISK
	| pointers ASTERISK	{ $$=strdup2($1,$2); free($1); free($2); }
	| ignorable
	| pointers ignorable	{ $$=strdup2($1,$2); free($1); free($2); }
	;

struct_union
	: STRUCT
	| UNION
	;

argument
	: WORD pointers WORD
	{ $$=strdup3($1,$2,$3); free($1); free($2); free($3); }

	| CONST ignorables WORD pointers WORD
	{ $$=strdup5($1,$2,$3,$4,$5); free($2); free($3); free($4); free($5); }

	| struct_union ignorables WORD pointers WORD
	{ $$=strdup5($1,$2,$3,$4,$5); free($2); free($3); free($4); free($5); }

	| CONST ignorables struct_union ignorables WORD pointers WORD
	{ $$=strdup7($1,$2,$3,$4,$5,$6,$7); free($2); free($4); free($5); free($6); free($7); }

	| sign ignorables WORD pointers WORD
	{ $$=strdup5($1,$2,$3,$4,$5); free($2); free($3); free($4); free($5); }

	| CONST ignorables sign ignorables WORD pointers WORD
	{ $$=strdup7($1,$2,$3,$4,$5,$6,$7); free($2); free($4); free($5); free($6); free($7); }

	| VAR_ARGS
	{ $$=strdup($1); }
	;

virtual_mode
	: VIRTUAL
	{
		modifier_mode = MODIFIER_VIRTUAL;
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=0;
	}
	;

override_mode
	: OVERRIDE OPAREN WORD EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$3; 
	}

	| OVERRIDE OPAREN WORD ignorables EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$3; 
	}

	| OVERRIDE OPAREN ignorables WORD EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$4; 
	}

	| OVERRIDE OPAREN ignorables WORD ignorables EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$4; 
	}

	| OVERRIDE ignorables OPAREN WORD EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$4; 
	}

	| OVERRIDE ignorables OPAREN WORD ignorables EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$4; 
	}

	| OVERRIDE ignorables OPAREN ignorables WORD EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$5; 
	}

	| OVERRIDE ignorables OPAREN ignorables WORD ignorables EPAREN
	{
		modifier_mode = MODIFIER_OVERRIDE;
		record_line_number();
		if (virtual_base_name) { free(virtual_base_name); } virtual_base_name=$5; 
	}
	;

access_specifier
	: PRIVATE	{ access_mode = ACCESS_PRIVATE;	}
	| PUBLIC	{ access_mode = ACCESS_PUBLIC;	}
	| GLOBAL	{ access_mode = ACCESS_GLOBAL;	}
	;

type_name
	: WORD pointers
	{ if (type_name) { free(type_name); } type_name=strdup2($1,$2); free($1); free($2); }

	| CONST ignorables WORD pointers
	{ if (type_name) { free(type_name); } type_name=strdup4($1," ",$3,$4); free($2); free($3); free($4); }

	| struct_union ignorables WORD pointers
	{ if (type_name) { free(type_name); } type_name=strdup4($1," ", $3,$4); free($2); free($3); free($4); }

	| CONST ignorables struct_union ignorables WORD pointers
	{ if (type_name) { free(type_name); } type_name=strdup6($1," ",$3," ", $5,$6); free($2); free($4); free($5); free($6); }

	| sign ignorables WORD pointers
	{ if (type_name) { free(type_name); } type_name=strdup4($1," ",$3,$4); free($2); free($3); free($4); }

	| CONST ignorables sign ignorables WORD pointers
	{ if (type_name) { free(type_name); } type_name=strdup5("const ",$3," ",$5,$6); free($2); free($4); free($5); free($6); }
	;

symbol_name
	: WORD
	{
		if (symbol_name)
			free(symbol_name);
		
		symbol_name=$1;
		record_line_number();

		/* reset state */
		is_attached_property = 0;
	}
	;

class_object
	/* data members */
	: access_specifier ignorables type_name symbol_name SEMICOLON
	{ add_data_member(access_mode, type_name, symbol_name); free($2); }

	| access_specifier ignorables type_name symbol_name ignorables SEMICOLON
	{ add_data_member(access_mode, type_name, symbol_name); free($2); free($6); }

	/* virtual member functions */
	| access_specifier ignorables virtual_mode ignorables type_name symbol_name argument_list ccodes_block
	{ virtual_member_function_decl(type_name, $6, $7, $8); free($2); free($4); free($7); free($8); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables argument_list ccodes_block
	{ virtual_member_function_decl(type_name, $6, $8, $9); free($2); free($4); free($7); free($8); free($9); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name argument_list ignorables ccodes_block
	{ virtual_member_function_decl(type_name, $6, $7, $9); free($2); free($4); free($7); free($8); free($9); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{ virtual_member_function_decl(type_name, $6, $8, $10); free($2); free($4); free($7); free($8); free($9); free($10); }

	/* override member functions */
	| override_mode ignorables type_name symbol_name argument_list ccodes_block
	{ override_member_function_decl(type_name, $4, $5, $6); free($2); free($5); free($6); }

	| override_mode ignorables type_name symbol_name ignorables argument_list ccodes_block
	{ override_member_function_decl(type_name, $4, $6, $7); free($2); free($5); free($6); free($7); }

	| override_mode ignorables type_name symbol_name argument_list ignorables ccodes_block
	{ override_member_function_decl(type_name, $4, $5, $7); free($2); free($5); free($6); free($7); }

	| override_mode ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{ override_member_function_decl(type_name, $4, $6, $8); free($2); free($5); free($6); free($7); free($8); }

	/* member functions */
	| access_specifier ignorables type_name symbol_name argument_list ccodes_block
	{ member_function_decl(type_name, $4, $5, $6); free($2); free($5); free($6); }

	| access_specifier ignorables type_name symbol_name ignorables argument_list ccodes_block
	{ member_function_decl(type_name, $4, $6, $7); free($2); free($5); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name argument_list ignorables ccodes_block
	{ member_function_decl(type_name, $4, $5, $7); free($2); free($5); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{ member_function_decl(type_name, $4, $6, $8); free($2); free($5); free($6); free($7); free($8); }

	/* special member functions (ie. init() or class_init() */
	| symbol_name argument_list ccodes_block
	{ special_member_function_decl($1, $2, $3); free($2); free($3); }

	| symbol_name ignorables argument_list ccodes_block
	{ special_member_function_decl($1, $3, $4); free($2); free($3); free($4); }

	| symbol_name argument_list ignorables ccodes_block
	{ special_member_function_decl($1, $2, $4); free($2); free($3); free($4); }

	| symbol_name ignorables argument_list ignorables ccodes_block
	{ special_member_function_decl($1, $3, $5); free($2); free($3); free($4); free($5); }

	/* signals */
	| access_specifier ignorables type_name symbol_name BANG argument_list SEMICOLON
	{ signal_decl(type_name, $4, $6); free($2); free($6); }

	| access_specifier ignorables type_name symbol_name BANG ignorables argument_list SEMICOLON
	{ signal_decl(type_name, $4, $7); free($2); free($5); free($7); }

	| access_specifier ignorables type_name symbol_name BANG argument_list ignorables SEMICOLON
	{ signal_decl(type_name, $4, $6); free($2); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name BANG ignorables argument_list ignorables SEMICOLON
	{ signal_decl(type_name, $4, $7); free($2); free($6); free($7); free($8); }

	/* properties */
	| access_specifier ignorables type_name symbol_name OBRACE property_objects EBRACE
	{ 
		if (is_attached_property) {
			/* add the global map that will hold the attached property for different objects */
			char *temp = strdup2("attached_", symbol_name);
			add_data_member(ACCESS_GLOBAL, "void *", temp);
			free(temp);
		}
		free($2);
	}

	| access_specifier ignorables type_name symbol_name ignorables OBRACE property_objects EBRACE
	{ 
		if (is_attached_property) {
			/* add the global map that will hold the attached property for different objects */
			char *temp = strdup2("attached_", symbol_name);
			add_data_member(ACCESS_GLOBAL, "void *", temp);
			free(temp);
		}
		free($2);
	}

	/* attached properties */
	| access_specifier ignorables type_name symbol_name hash OBRACE property_objects EBRACE
	{ 
		if (is_attached_property) {
			/* add the global map that will hold the attached property for different objects */
			char *temp = strdup2("attached_", symbol_name);
			add_data_member(ACCESS_GLOBAL, "void *", temp);
			free(temp);
		}
		free($2);
	}

	| access_specifier ignorables type_name symbol_name hash ignorables OBRACE property_objects EBRACE
	{ 
		if (is_attached_property) {
			/* add the global map that will hold the attached property for different objects */
			char *temp = strdup2("attached_", symbol_name);
			add_data_member(ACCESS_GLOBAL, "void *", temp);
			free(temp);
		}
		free($2);
	}
	;

hash
	: HASH { is_attached_property = 1; }
	;

property_objects
	: property_object 
	| property_objects property_object     { $$=strdup2($1,$2); }
	| ignorable                            { free($1); }
	| property_objects ignorable           { free($2); }
	;

get_keyword
	: GET { record_line_number(); }
	;

set_keyword
	: SET { record_line_number(); }
	;

property_object
	: get_keyword ccodes_block		{ property_decl($1,$2); }
	| get_keyword ignorables ccodes_block	{ property_decl($1,$3); free($2); }
	| set_keyword ccodes_block		{ property_decl($1,$2); }
	| set_keyword ignorables ccodes_block	{ property_decl($1,$3); free($2); }
	;

ignorables
	: ignorable
	| ignorables ignorable { $$=strdup2($1,$2); free($1); free($2); }
	;

ignorable
	: SPACE     { $$ = strdup((strchr($1,'\n'))? "\n" : " "); free($1); }
	| COMMENT
	;

sign
	: SIGNED
	| UNSIGNED
	;

%%

#include <stdio.h>

extern char yytext[];
extern int column;
//int yydebug=1;

void yyerror(const char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

static char * get_base_filename(const char *full_filename, int *base_length)
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

static char *macro_safe(const char *s)
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

	return res;
}

int main(int argc, char **argv)
{
	char *filename;
	int base_length;
	int rc;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
		return -1;
	}

	zco_filename = argv[1];
	filename = get_base_filename(argv[1], &base_length);
	if (filename == NULL)
	{
		fprintf(stderr, "Input file must have a .zco extension\n");
		return -1;
	}

	zco_context_init(&context);
	real_lineno = 0;

	/* open the output header file for writing */
	filename[base_length] = '.';
	filename[base_length+1] = 'h';
	filename[base_length+2] = 0;
	header_filename = strdup(filename);
	if ((header_file = fopen(header_filename, "w")) == NULL) {
		fputs("zco: ", stderr);
		perror(header_filename);
		return -1;
	}

	/* write the include guard in the header file */
	char *temp = macro_safe(header_filename);
	fprintf(header_file, "#ifndef _%s_\n#define _%s_\n", temp, temp);
	free(temp);

	/* open the output source file for writing */
	filename[base_length+1] = 'c';
	source_file = fopen(filename, "w");

	/* use input .zco file as standard input */
	if (freopen(argv[1], "r", stdin) == NULL) {
		fputs("zco: ", stderr);
		perror(argv[1]);
		return -1;
	}

	rc = yyparse();

	free(header_filename);

	fprintf(header_file, "\n#endif\n");
	fprintf(source_file, "\n\n");

	fclose(header_file);
	fclose(source_file);

	return rc;
}


