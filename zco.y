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

#define YYSTYPE char *

struct string_t
{
   int length;
   char *data;
};

FILE *header_file, *source_file;
char *type_name, *symbol_name;
char *header_filename;

/* example_class_name */
char *current_class_name_underscore;

/* ExampleClassName */
char *current_class_name_pascal;


int parent_class_count;
char **parent_class_name_underscore;
char **parent_class_name_pascal;


enum access_mode_t
{
	ACCESS_PRIVATE,
	ACCESS_PROTECTED,
	ACCESS_PUBLIC,
	ACCESS_GLOBAL
};

enum access_mode_t access_mode;

/* struct definition for global (static) data members */
struct string_t global_data;

/* struct definition for private data members */
struct string_t private_data;

/* struct definition for public data members */
struct string_t public_data;;

/* list of function prototypes for private member function */
struct string_t function_prototypes_c;

/* list of function definitions */
struct string_t function_definitions;

struct string_t h_macros_head;
struct string_t h_macros_tail;
struct string_t c_macros;
struct string_t function_prototypes_h;

void yyerror(const char *s);

static char * strdup2(const char *s1, const char *s2)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);

	char *res = malloc(l1 + l2 + 1);

	memcpy(res, s1, l1);
	memcpy(res+l1, s2, l2);
	res[l1+l2] = 0;

	return res;
}

static char * strdup3(const char *s1, const char *s2, const char *s3)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int l3 = strlen(s3);

	char *res = malloc(l1 + l2 + l3 + 1);

	memcpy(res, s1, l1);
	memcpy(res+l1, s2, l2);
	memcpy(res+l1+l2, s3, l3);
	res[l1+l2+l3] = 0;

	return res;
}

static char * strdup4(const char *s1, const char *s2, const char *s3, const char *s4)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int l3 = strlen(s3);
	int l4 = strlen(s4);

	char *res = malloc(l1 + l2 + l3 + l4 + 1);

	memcpy(res, s1, l1);
	memcpy(res+l1, s2, l2);
	memcpy(res+l1+l2, s3, l3);
	memcpy(res+l1+l2+l3, s4, l4);
	res[l1+l2+l3+l4] = 0;

	return res;
}

static char * strdup5(const char *s1, const char *s2, const char *s3, const char *s4, const char *s5)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int l3 = strlen(s3);
	int l4 = strlen(s4);
	int l5 = strlen(s5);

	char *res = malloc(l1 + l2 + l3 + l4 + l5 + 1);

	memcpy(res, s1, l1);
	memcpy(res+l1, s2, l2);
	memcpy(res+l1+l2, s3, l3);
	memcpy(res+l1+l2+l3, s4, l4);
	memcpy(res+l1+l2+l3+l4, s5, l5);
	res[l1+l2+l3+l4+l5] = 0;

	return res;
}

static char * strdup6(const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int l3 = strlen(s3);
	int l4 = strlen(s4);
	int l5 = strlen(s5);
	int l6 = strlen(s6);

	char *res = malloc(l1 + l2 + l3 + l4 + l5 + l6 + 1);

	memcpy(res, s1, l1);
	memcpy(res+l1, s2, l2);
	memcpy(res+l1+l2, s3, l3);
	memcpy(res+l1+l2+l3, s4, l4);
	memcpy(res+l1+l2+l3+l4, s5, l5);
	memcpy(res+l1+l2+l3+l4+l5, s6, l6);
	res[l1+l2+l3+l4+l5+l6] = 0;

	return res;
}

static char * strdup7(const char *s1, const char *s2, const char *s3, const char *s4, const char *s5, const char *s6,
		const char *s7)
{
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int l3 = strlen(s3);
	int l4 = strlen(s4);
	int l5 = strlen(s5);
	int l6 = strlen(s6);
	int l7 = strlen(s7);

	char *res = malloc(l1 + l2 + l3 + l4 + l5 + l6 + l7 + 1);

	memcpy(res, s1, l1);
	memcpy(res+l1, s2, l2);
	memcpy(res+l1+l2, s3, l3);
	memcpy(res+l1+l2+l3, s4, l4);
	memcpy(res+l1+l2+l3+l4, s5, l5);
	memcpy(res+l1+l2+l3+l4+l5, s6, l6);
	memcpy(res+l1+l2+l3+l4+l5+l6, s7, l7);
	res[l1+l2+l3+l4+l5+l6+l7] = 0;

	return res;
}

static void strcat_safe(struct string_t *str, const char *new_str)
{
	int l1 = str->length;
	int l2 = strlen(new_str);

	str->data = realloc(str->data, l1+l2+1);
	memcpy(str->data+l1, new_str, l2);
	str->length = l1+l2;
	str->data[str->length] = 0;
}

static void dump_string(struct string_t *str, FILE *file)
{
	if (!str->length)
		return;

	fputs(str->data, file);
	free(str->data);
	str->data = 0;
	str->length = 0;
}

static void special_member_function_decl(const char *symbol, const char *arglist, const char *code)
{
	if (!strcmp(symbol, "class_init"))
		strcat_safe(&c_macros, "#define SHOULD_CALL_CLASS_INIT\n");

	else if (!strcmp(symbol, "init"))
		strcat_safe(&c_macros, "#define SHOULD_CALL_INIT\n");

	strcat_safe(&c_macros, "#define ");
	strcat_safe(&c_macros, symbol);
	strcat_safe(&c_macros, " ");
	strcat_safe(&c_macros, current_class_name_underscore);
	strcat_safe(&c_macros, "_");
	strcat_safe(&c_macros, symbol);
	strcat_safe(&c_macros, "\n");

	/* for function prototype */
	strcat_safe(&function_prototypes_c, "static void ");
	strcat_safe(&function_prototypes_c, current_class_name_underscore);
	strcat_safe(&function_prototypes_c, "_");
	strcat_safe(&function_prototypes_c, symbol);
	strcat_safe(&function_prototypes_c, arglist);
	strcat_safe(&function_prototypes_c, ";\n");

	/* for function definition */
	strcat_safe(&function_definitions, "static void ");
	strcat_safe(&function_definitions, current_class_name_underscore);
	strcat_safe(&function_definitions, "_");
	strcat_safe(&function_definitions, symbol);
	strcat_safe(&function_definitions, arglist);
	strcat_safe(&function_definitions, "\n");
	strcat_safe(&function_definitions, code);
	strcat_safe(&function_definitions, "\n");
}

static void member_function_decl(const char *type, const char *symbol, const char *arglist, const char *code)
{
	strcat_safe(&c_macros, "#define ");
	strcat_safe(&c_macros, symbol);
	strcat_safe(&c_macros, " ");
	strcat_safe(&c_macros, current_class_name_underscore);
	strcat_safe(&c_macros, "_");
	strcat_safe(&c_macros, symbol);
	strcat_safe(&c_macros, "\n");


	switch (access_mode)
	{
		case ACCESS_PRIVATE:
			/* for function prototype */
			strcat_safe(&function_prototypes_c, "static ");
			strcat_safe(&function_prototypes_c, type);
			strcat_safe(&function_prototypes_c, " ");
			strcat_safe(&function_prototypes_c, current_class_name_underscore);
			strcat_safe(&function_prototypes_c, "_");
			strcat_safe(&function_prototypes_c, symbol);
			strcat_safe(&function_prototypes_c, arglist);
			strcat_safe(&function_prototypes_c, ";\n");

			/* for function definition */
			strcat_safe(&function_definitions, "static ");
			strcat_safe(&function_definitions, type);
			strcat_safe(&function_definitions, " ");
			strcat_safe(&function_definitions, current_class_name_underscore);
			strcat_safe(&function_definitions, "_");
			strcat_safe(&function_definitions, symbol);
			strcat_safe(&function_definitions, arglist);
			strcat_safe(&function_definitions, "\n");
			strcat_safe(&function_definitions, code);
			strcat_safe(&function_definitions, "\n");
			break;

		case ACCESS_PUBLIC:
			/* for function prototype */
			strcat_safe(&function_prototypes_h, type);
			strcat_safe(&function_prototypes_h, " ");
			strcat_safe(&function_prototypes_h, current_class_name_underscore);
			strcat_safe(&function_prototypes_h, "_");
			strcat_safe(&function_prototypes_h, symbol);
			strcat_safe(&function_prototypes_h, arglist);
			strcat_safe(&function_prototypes_h, ";\n");

			/* for function definition */
			strcat_safe(&function_definitions, type);
			strcat_safe(&function_definitions, " ");
			strcat_safe(&function_definitions, current_class_name_underscore);
			strcat_safe(&function_definitions, "_");
			strcat_safe(&function_definitions, symbol);
			strcat_safe(&function_definitions, arglist);
			strcat_safe(&function_definitions, "\n");
			strcat_safe(&function_definitions, code);
			strcat_safe(&function_definitions, "\n");
			break;
	}
}

static void property_decl(char *get_or_set, char *code)
{
	char *arglist, *symbol;

	if (!strcmp(get_or_set, "get")) {
		arglist = "()";
		symbol = strdup2("get_", symbol_name);
		member_function_decl(type_name, symbol, arglist, code);
		free(symbol);

	} else if (!strcmp(get_or_set, "set")) {
		arglist = strdup3("(", type_name, " value)");
		symbol = strdup2("set_", symbol_name);
		member_function_decl("void", symbol, arglist, code);
		free(arglist);
		free(symbol);
	}
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
	parent_class_name_underscore = (char **) realloc(parent_class_name_underscore, sizeof(char *) * parent_class_count);

	/* store the name of the parent class */
	parent_class_name_pascal[parent_class_count-1] = name_in_pascal;
	parent_class_name_underscore[parent_class_count-1] = pascal_to_lowercase(name_in_pascal, '_');
}

static void init_string(struct string_t *s)
{
	s->length = 0;
	s->data = 0;
}

static void add_data_member()
{
	switch (access_mode)
	{
		case ACCESS_PRIVATE:
			strcat_safe(&private_data, "\t");
			strcat_safe(&private_data, type_name);
			strcat_safe(&private_data, " ");
			strcat_safe(&private_data, symbol_name);
			strcat_safe(&private_data, ";\n");
			break;

		case ACCESS_PUBLIC:
			strcat_safe(&public_data, "\t");
			strcat_safe(&public_data, type_name);
			strcat_safe(&public_data, " ");
			strcat_safe(&public_data, symbol_name);
			strcat_safe(&public_data, ";\n");
			break;

		case ACCESS_GLOBAL:
			strcat_safe(&global_data, "\t");
			strcat_safe(&global_data, type_name);
			strcat_safe(&global_data, " ");
			strcat_safe(&global_data, symbol_name);
			strcat_safe(&global_data, ";\n");
			break;
	}
}

static void class_init(char *class_name)
{
	int i;

	init_string(&private_data);
	init_string(&public_data);
	init_string(&global_data);
	init_string(&function_prototypes_c);
	init_string(&function_prototypes_h);
	init_string(&function_definitions);
	init_string(&h_macros_head);
	init_string(&h_macros_tail);
	init_string(&c_macros);

	/* start the private data structure */
	strcat_safe(&private_data, "struct ");
	strcat_safe(&private_data, class_name);
	strcat_safe(&private_data, "Private {\n");

	/* define the Self macro in the header file */
	strcat_safe(&h_macros_head, "#define Self struct ");
	strcat_safe(&h_macros_head, class_name);
	strcat_safe(&h_macros_head, "\n\n");

	strcat_safe(&h_macros_tail, "#undef Self\n");

	/* define the Self macro in the source file */
	strcat_safe(&c_macros, "#define Self struct ");
	strcat_safe(&c_macros, class_name);
	strcat_safe(&c_macros, "\n");
	strcat_safe(&c_macros, "#define selfp (&self->_priv)\n");
	strcat_safe(&c_macros, "#define GET_NEW(ctx) __class_init(ctx)\n");

	/* start the global data structure */
	strcat_safe(&global_data, "struct ");
	strcat_safe(&global_data, class_name);
	strcat_safe(&global_data, "Class {\n"
			"\tconst char *name;\n"
			"\tint id;\n"
			"\tint *vtable_off_list;\n"
			"\tint vtable_off_size;\n");

	/* start the public data structure */
	strcat_safe(&public_data, "struct ");
	strcat_safe(&public_data, class_name);
	strcat_safe(&public_data, " {\n");

	for (i=0; i<parent_class_count; ++i)
	{
		strcat_safe(&public_data, "\tstruct ");
		strcat_safe(&public_data, parent_class_name_pascal[i]);
		strcat_safe(&public_data, " parent_");
		strcat_safe(&public_data, parent_class_name_underscore[i]);
		strcat_safe(&public_data, ";\n");
	}

	/* declare the _class pointer in the public structure */
	strcat_safe(&public_data, "\tstruct ");
	strcat_safe(&public_data, class_name);
	strcat_safe(&public_data, "Class *_class;\n");

	/* declare the _priv member in the public structure */
	strcat_safe(&public_data, "\tstruct ");
	strcat_safe(&public_data, class_name);
	strcat_safe(&public_data, "Private _priv;\n");

	access_mode = ACCESS_PUBLIC;
	current_class_name_underscore = pascal_to_lowercase(class_name, '_');
	current_class_name_pascal = class_name;
}

%}

%token HEADER_BLK_START SOURCE_BLK_START FILE_BLK_END CLASS COLON GLOBAL PUBLIC PRIVATE PROPERTY GET SET 
%token OVERRIDE VIRTUAL WORD CODE OBRACE EBRACE OPAREN EPAREN SEMICOLON SPACE ASTERISK COMMENT COMMA


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

	/* head macros in header file */
	dump_string(&h_macros_head, header_file);
	fprintf(header_file, "\n");

	/* private data members */
	dump_string(&private_data, header_file);
	fprintf(header_file, "};\n\n");

	/* global data members */
	dump_string(&global_data, header_file);
	fprintf(header_file, "};\n\n");

	/* public data members */
	dump_string(&public_data, header_file);
	fprintf(header_file, "};\n");

	/* function prototypes in header file */
	fprintf(header_file, "struct %sClass * get_type(struct zco_context_t *ctx);\n", current_class_name_pascal);
	dump_string(&function_prototypes_h, header_file);
	fprintf(header_file, "\n");

	/* tail macros in header file */
	dump_string(&h_macros_tail, header_file);
	fprintf(header_file, "\n");

	/* includes in source file */
	fprintf(source_file, "#include <%s>\n#include <zco.h>\n", header_filename);

	/* macros in source file */
	dump_string(&c_macros, source_file);
	fprintf(source_file, "\n");

	/* declare the global variables */
	fprintf(source_file, "static struct %sClass global;\n", current_class_name_pascal);
	fprintf(source_file, "static int type_id = -1;\n");
	fprintf(source_file, "\n");

	/* function prototypes in source file */
	dump_string(&function_prototypes_c, source_file);
	fprintf(source_file, "\n");

	/* define get_type */
	fprintf(source_file, "struct %sClass * get_type(struct zco_context_t *ctx)\n"
			"{\n"
			"\tif (type_id == -1)\n"
			"\t\ttype_id = zco_allocate_type_id();\n\n"
			"\tvoid **class_ptr = zco_get_ctx_field(ctx, type_id);\n"
			"\tif (*class_ptr == 0) {\n"
			"\t\t*class_ptr = malloc(sizeof(struct %sClass));\n"
			"\t\tstruct %sClass *class = (struct %sClass *) *class_ptr;\n"
			"\t\tclass->name = \"%s\";\n"
			"\t\tclass->id = type_id;\n"
			"\t\tclass->vtable_off_list = NULL;\n"
			"\t\tclass->vtable_off_size = 0;\n"
			"\t\t\n"
			"\t\tstruct %s temp;\n"
			"\t\t\n",
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal,
			current_class_name_pascal
				);

	/* inherit the vtable from the parent class */
	for (i=0; i < parent_class_count; ++i) {
		fprintf(source_file,
				"\t\t{\n"
				"\t\t\tstruct %sClass *p_class = %s_get_type();\n"
				"\t\t\tzco_inherit_vtable(&class->vtable_off_list, &class->vtable_off_size, "
				"p_class->vtable_off_list, p_class->vtable_off_size, "
				"&temp, &temp.parent_%s);\n"
				"\t\t}\n",
				parent_class_name_pascal[i],
				parent_class_name_underscore[i],
				parent_class_name_underscore[i]);

		free(parent_class_name_pascal[i]);
		free(parent_class_name_underscore[i]);
	}

	if (parent_class_count > 0) {
		free(parent_class_name_pascal);
		free(parent_class_name_underscore);
	}

	fprintf(source_file,
			"\t\tzco_add_to_vtable(&class->vtable_off_list, &class->vtable_off_size, type_id);"
			"\t\t\n"
			"\t\t#ifdef SHOULD_CALL_CLASS_INIT\n"
			"\t\t\tclass_init((struct ZCObjectClass *) class);\n"
			"\t\t#endif\n"
			"\t}\n"
			"\treturn (struct %sClass *) *class_ptr;\n"
			"}\n\n",
			current_class_name_pascal);

	/* define _init */
	fprintf(source_file, "static Self * __init(struct zco_context_t *ctx)\n"
			"{\n"
			"\t%s_get_type();\n"
			"\tSelf *self = (Self *) malloc(sizeof(Self));\n"
			"\tself->_class = (struct %sClass *) *class_ptr;\n"
			"\t#ifdef SHOULD_CALL_INIT\n"
			"\t\tinit((struct ZCObject *) self);\n"
			"\t#endif\n"
			"\treturn self;\n"
			"}\n",
			current_class_name_pascal,
			current_class_name_pascal);

	dump_string(&function_definitions, source_file);
	fprintf(source_file, "\n");

	free(current_class_name_underscore);
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
		parent_class_name_underscore = 0;
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
	| arguments COMMA argument             { $$=strdup3($1,$2,$3); free($1); free($3);  }
	| ignorables argument                  { $$=$2; free($1); }
	| arguments COMMA ignorables argument  { $$=strdup3($1,$2,$4); free($1); free($3); free($4);  }
	;

pointers
	: ASTERISK
	| pointers ASTERISK
	;

argument
	: WORD ignorables WORD
	{ $$=strdup3($1,$2,$3); free($1); free($2); free($3); }

	| WORD pointers ignorables WORD
	{ $$=strdup4($1,$2,$3,$4); free($1); free($3); free($4); }

	| WORD ignorables pointers WORD
	{ $$=strdup4($1,$2,$3,$4); free($1); free($2); free($4); }

	| WORD ignorables pointers ignorables WORD
	{ $$=strdup5($1,$2,$3,$4,$5); free($1); free($2); free($4); free($5); }

	| WORD ignorables WORD ignorables WORD
	{ $$=strdup5($1,$2,$3,$4,$5); free($1); free($2); free($3); free($4); free($5); }

	| WORD ignorables WORD pointers ignorables WORD
	{ $$=strdup6($1,$2,$3,$4,$5,$6); free($1); free($2); free($3); free($5); free($6); }

	| WORD ignorables WORD ignorables pointers WORD
	{ $$=strdup6($1,$2,$3,$4,$5,$6); free($1); free($2); free($3); free($4); free($6); }

	| WORD ignorables WORD ignorables pointers ignorables WORD
	{ $$=strdup7($1,$2,$3,$4,$5,$6,$7); free($1); free($2); free($3); free($4); free($6); free($7); }
	;

access_specifier
	: PRIVATE   { access_mode = ACCESS_PRIVATE; }
	| PUBLIC    { access_mode = ACCESS_PUBLIC; }
	| GLOBAL    { access_mode = ACCESS_GLOBAL; }
	;

type_name
	: WORD { if (type_name) { free(type_name); } type_name=$1; }
	;

symbol_name
	: WORD { if (symbol_name) { free(symbol_name); } symbol_name=$1; }
	;

class_object
	/* data members */
	: access_specifier ignorables type_name ignorables symbol_name SEMICOLON
	{ add_data_member(); free($2); free($4); }

	| access_specifier ignorables type_name ignorables symbol_name ignorables SEMICOLON
	{ add_data_member(); free($2); free($4); free($6); }

	/* member functions */
	| access_specifier ignorables type_name ignorables symbol_name argument_list ccodes_block
	{ member_function_decl($3, $5, $6, $7); free($2); free($4); free($6); free($7); }

	| access_specifier ignorables type_name ignorables symbol_name ignorables argument_list ccodes_block
	{ member_function_decl($3, $5, $7, $8); free($2); free($4); free($6); free($7); free($8); }

	| access_specifier ignorables type_name ignorables symbol_name argument_list ignorables ccodes_block
	{ member_function_decl($3, $5, $6, $8); free($2); free($4); free($6); free($7); free($8); }

	| access_specifier ignorables type_name ignorables symbol_name ignorables argument_list ignorables ccodes_block
	{ member_function_decl($3, $5, $7, $9); free($2); free($4); free($6); free($7); free($8); free($9); }

	/* special member functions (ie. init() or class_init() */
	| symbol_name argument_list ccodes_block
	{ special_member_function_decl($1, $2, $3); free($2); free($3); }

	| symbol_name ignorables argument_list ccodes_block
	{ special_member_function_decl($1, $3, $4); free($2); free($3); free($4); }

	| symbol_name argument_list ignorables ccodes_block
	{ special_member_function_decl($1, $2, $4); free($2); free($3); free($4); }

	| symbol_name ignorables argument_list ignorables ccodes_block
	{ special_member_function_decl($1, $3, $5); free($2); free($3); free($4); free($5); }

	/* properties */
	| access_specifier ignorables type_name ignorables symbol_name OBRACE property_objects EBRACE
	{ free($2); free($4); }

	| access_specifier ignorables type_name ignorables symbol_name ignorables OBRACE property_objects EBRACE
	{ free($2); free($4); free($6); }
	;

property_objects
	: property_object 
	| property_objects property_object     { $$=strdup2($1,$2); }
	| ignorable                            { free($1); }
	| property_objects ignorable           { free($2); }
	;

property_object
	: GET ccodes_block               { property_decl($1,$2); }
	| GET ignorables ccodes_block    { property_decl($1,$3); free($2); }
	| SET ccodes_block               { property_decl($1,$2); }
	| SET ignorables ccodes_block    { property_decl($1,$3); free($2); }
	;

ignorables
	: ignorable
	| ignorables ignorable { $$=strdup2($1,$2); free($1); free($2); }
	;

ignorable
	: SPACE     { $$ = strdup((strchr($1,'\n'))? "\n" : " "); free($1); }
	| COMMENT
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

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
		return -1;
	}

	filename = get_base_filename(argv[1], &base_length);
	if (filename == NULL)
	{
		fprintf(stderr, "Input file must have a .zco extension\n");
		return -1;
	}

	/* open the output header file for writing */
	filename[base_length] = '.';
	filename[base_length+1] = 'h';
	filename[base_length+2] = 0;
	header_filename = strdup(filename);
	header_file = fopen(header_filename, "w");

	/* write the include guard in the header file */
	char *temp = macro_safe(header_filename);
	fprintf(header_file, "#ifndef _%s_\n#define _%s_\n", temp, temp);
	free(temp);

	/* open the output source file for writing */
	filename[base_length+1] = 'c';
	source_file = fopen(filename, "w");

	/* use input .zco file as standard input */
	freopen(argv[1], "r", stdin);

	yyparse();

	free(header_filename);

	fprintf(header_file, "\n#endif\n");
	fprintf(source_file, "\n\n");

	fclose(header_file);
	fclose(source_file);
}


