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

#include <z-zco-source-generator.h>
#include <z-string.h>
#include <z-file.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define YYSTYPE char *

ZZcoSourceGenerator *source_generator;

int yylex(void);
%}

%token HEADER_BLK_START SOURCE_BLK_START FILE_BLK_END CLASS INTERFACE STRUCT UNION CONST SIGNED UNSIGNED COLON GLOBAL PUBLIC PRIVATE PROPERTY GET SET 
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
	z_zco_source_generator_external_declaration(source_generator);
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
		z_zco_source_generator_write_header_block(source_generator, $2);
		free($2);
	}
	;

source_block
	: source_block_start ccodes FILE_BLK_END
	{
		z_zco_source_generator_write_source_block(source_generator, $2);
		free($2);
	}
	;

ccodes_block
	: OBRACE ccodes EBRACE { $$=z_zco_source_generator_strdup3(source_generator,$1,$2,$3); free($2); }
	| OBRACE EBRACE        { $$=z_zco_source_generator_strdup2(source_generator,$1,$2); }
	;

ccodes
	: CODE
	| ccodes CODE
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); free($2); }

	| WORD
	| ccodes WORD
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); free($2); }

	| CLASS
	{ $$=strdup($1); }

	| ccodes CLASS
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| INTERFACE
	{ $$=strdup($1); }

	| ccodes INTERFACE
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| struct_union
	{ $$=strdup($1); }

	| ccodes struct_union
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| VAR_ARGS
	{ $$=strdup($1); }

	| ccodes VAR_ARGS
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| CONST
	{ $$=strdup($1); }

	| ccodes CONST
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| sign
	{ $$=strdup($1); }

	| ccodes sign
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| COLON
	{ $$=strdup($1); }

	| ccodes COLON
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| COMMA
	{ $$=strdup($1); }

	| ccodes COMMA
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| OPAREN
	{ $$=strdup($1); }

	| ccodes OPAREN
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| EPAREN
	{ $$=strdup($1); }

	| ccodes EPAREN
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| ASTERISK
	{ $$=strdup($1); }

	| ccodes ASTERISK
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| HASH
	{ $$=strdup($1); }

	| ccodes HASH
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| BANG
	{ $$=strdup($1); }

	| ccodes BANG
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| SEMICOLON
	{ $$=strdup($1); }

	| ccodes SEMICOLON
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| GLOBAL
	{ $$=strdup($1); }

	| ccodes GLOBAL
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| PUBLIC
	{ $$=strdup($1); }

	| ccodes PUBLIC
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| PRIVATE
	{ $$=strdup($1); }

	| ccodes PRIVATE
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| PROPERTY
	{ $$=strdup($1); }

	| ccodes PROPERTY
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| GET
	{ $$=strdup($1); }

	| ccodes GET
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| SET
	{ $$=strdup($1); }

	| ccodes SET
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| OVERRIDE
	{ $$=strdup($1); }

	| ccodes OVERRIDE
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| VIRTUAL
	{ $$=strdup($1); }

	| ccodes VIRTUAL
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }

	| ignorable
	| ccodes ignorable
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); free($2); }

	| ccodes_block
	| ccodes ccodes_block
	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); free($2); }
	;

class_declaration
	: CLASS ignorables WORD 
	{
		z_zco_source_generator_class_declaration(source_generator);
		$$=$3;
		free($2);
	}
	;

interface_declaration
	: INTERFACE ignorables WORD 
	{
		z_zco_source_generator_interface_declaration(source_generator);
		$$=$3;
		free($2);
	}
	;

/* $4 should not be freed because it will be pointed to by parent_class_name_pascal */
parent_declaration
	: WORD
	{ z_zco_source_generator_add_parent(source_generator, $1); }

	| parent_declaration COMMA WORD
	{ z_zco_source_generator_add_parent(source_generator, $3); }

	| parent_declaration COMMA ignorables WORD
	{ z_zco_source_generator_add_parent(source_generator, $4); free($3); }

	| parent_declaration ignorables COMMA WORD
	{ z_zco_source_generator_add_parent(source_generator, $4); free($2); }

	| parent_declaration ignorables COMMA ignorables WORD
	{ z_zco_source_generator_add_parent(source_generator, $5); free($2); free($4); }
	;


/* $1 should not be freed because it will be pointed to by current_class_name_pascal */
full_class_declaration
	: class_declaration
	{ z_zco_source_generator_prepare_class(source_generator, $1); }

	| class_declaration ignorables
	{ z_zco_source_generator_prepare_class(source_generator, $1); free($2); }

	| class_declaration ignorables COLON ignorables parent_declaration
	{ z_zco_source_generator_prepare_class(source_generator, $1); free($2); free($4); }

	| class_declaration ignorables COLON ignorables parent_declaration ignorables
	{ z_zco_source_generator_prepare_class(source_generator, $1); free($2); free($4); free($6); }

	| interface_declaration
	{ z_zco_source_generator_prepare_interface(source_generator, $1); }

	| interface_declaration ignorables
	{ z_zco_source_generator_prepare_interface(source_generator, $1); free($2); }

	| interface_declaration ignorables COLON ignorables parent_declaration
	{ z_zco_source_generator_prepare_interface(source_generator, $1); free($2); free($4); }

	| interface_declaration ignorables COLON ignorables parent_declaration ignorables
	{ z_zco_source_generator_prepare_interface(source_generator, $1); free($2); free($4); free($6); }

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
	| OPAREN arguments EPAREN     { $$=z_zco_source_generator_strdup3(source_generator,"(",$2,")"); free($2); }
	;

arguments
	: argument
	| arguments COMMA argument
	{ $$=z_zco_source_generator_strdup3(source_generator,$1,$2,$3); free($1); free($3);  }

	| arguments COMMA ignorables argument
	{ $$=z_zco_source_generator_strdup3(source_generator,$1,$2,$4); free($1); free($3); free($4);  }

	| arguments COMMA ignorables argument ignorables
	{ $$=z_zco_source_generator_strdup3(source_generator,$1,$2,$4); free($1); free($3); free($4); free($5);  }
	;

pointers
	: ASTERISK
	| pointers ASTERISK	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); }
	| ignorable
	| pointers ignorable	{ $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); free($2); }
	;

struct_union
	: STRUCT
	| UNION
	;

argument
	: WORD pointers WORD
	{ $$=z_zco_source_generator_strdup3(source_generator,$1,$2,$3); free($1); free($2); free($3); }

	| CONST ignorables WORD pointers WORD
	{ $$=z_zco_source_generator_strdup5(source_generator,$1,$2,$3,$4,$5); free($2); free($3); free($4); free($5); }

	| struct_union ignorables WORD pointers WORD
	{ $$=z_zco_source_generator_strdup5(source_generator,$1,$2,$3,$4,$5); free($2); free($3); free($4); free($5); }

	| CONST ignorables struct_union ignorables WORD pointers WORD
	{ $$=z_zco_source_generator_strdup7(source_generator,$1,$2,$3,$4,$5,$6,$7); free($2); free($4); free($5); free($6); free($7); }

	| sign ignorables WORD pointers WORD
	{ $$=z_zco_source_generator_strdup5(source_generator,$1,$2,$3,$4,$5); free($2); free($3); free($4); free($5); }

	| CONST ignorables sign ignorables WORD pointers WORD
	{ $$=z_zco_source_generator_strdup7(source_generator,$1,$2,$3,$4,$5,$6,$7); free($2); free($4); free($5); free($6); free($7); }

	| VAR_ARGS
	{ $$=strdup($1); }
	;

virtual_mode
	: VIRTUAL
	{
		z_zco_source_generator_enable_virtual_mode(source_generator);
	}
	;

override_mode
	: OVERRIDE OPAREN WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $3);
	}

	| OVERRIDE OPAREN WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $3);
		free($4);
	}

	| OVERRIDE OPAREN ignorables WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		free($3);
	}

	| OVERRIDE OPAREN ignorables WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		free($3);
		free($5);
	}

	| OVERRIDE ignorables OPAREN WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		free($2);
	}

	| OVERRIDE ignorables OPAREN WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		free($2);
		free($5);
	}

	| OVERRIDE ignorables OPAREN ignorables WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $5);
		free($2);
		free($4);
	}

	| OVERRIDE ignorables OPAREN ignorables WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $5);
		free($2);
		free($4);
		free($6);
	}
	;

access_specifier
	: PRIVATE	{ z_zco_source_generator_set_access_mode(source_generator, ACCESS_PRIVATE);	}
	| PUBLIC	{ z_zco_source_generator_set_access_mode(source_generator, ACCESS_PUBLIC);	}
	| GLOBAL	{ z_zco_source_generator_set_access_mode(source_generator, ACCESS_GLOBAL);	}
	;

type_name
	: WORD pointers
	{ z_zco_source_generator_set_type_name(source_generator, z_zco_source_generator_strdup2(source_generator,$1,$2)); free($1); free($2); }

	| CONST ignorables WORD pointers
	{ z_zco_source_generator_set_type_name(source_generator, z_zco_source_generator_strdup4(source_generator,$1," ",$3,$4)); free($2); free($3); free($4); }

	| struct_union ignorables WORD pointers
	{ z_zco_source_generator_set_type_name(source_generator, z_zco_source_generator_strdup4(source_generator,$1," ", $3,$4)); free($2); free($3); free($4); }

	| CONST ignorables struct_union ignorables WORD pointers
	{ z_zco_source_generator_set_type_name(source_generator, z_zco_source_generator_strdup6(source_generator,$1," ",$3," ", $5,$6)); free($2); free($4); free($5); free($6); }

	| sign ignorables WORD pointers
	{ z_zco_source_generator_set_type_name(source_generator, z_zco_source_generator_strdup4(source_generator,$1," ",$3,$4)); free($2); free($3); free($4); }

	| CONST ignorables sign ignorables WORD pointers
	{ z_zco_source_generator_set_type_name(source_generator, z_zco_source_generator_strdup5(source_generator,"const ",$3," ",$5,$6)); free($2); free($4); free($5); free($6); }
	;

symbol_name
	: WORD
	{ z_zco_source_generator_set_symbol_name(source_generator, $1); }
	;

class_object
	/* data members */
	: access_specifier ignorables type_name symbol_name SEMICOLON
	{ z_zco_source_generator_add_class_data_member(source_generator); free($2); }

	| access_specifier ignorables type_name symbol_name ignorables SEMICOLON
	{ z_zco_source_generator_add_class_data_member(source_generator); free($2); free($5); free($6); }

	/* virtual data members */
	| access_specifier ignorables virtual_mode ignorables type_name symbol_name SEMICOLON
	{ z_zco_source_generator_add_class_virtual_data_member(source_generator); free($2); free($4); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables SEMICOLON
	{ z_zco_source_generator_add_class_virtual_data_member(source_generator); free($2); free($4); free($6); free($7); }

	/* virtual member functions */
	| access_specifier ignorables virtual_mode ignorables type_name symbol_name argument_list ccodes_block
	{ z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, $7, $8); free($2); free($4); free($7); free($8); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables argument_list ccodes_block
	{ z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, $8, $9); free($2); free($4); free($7); free($8); free($9); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name argument_list ignorables ccodes_block
	{ z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, $7, $9); free($2); free($4); free($7); free($8); free($9); }

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{ z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, $8, $10); free($2); free($4); free($7); free($8); free($9); free($10); }

	/* override member functions */
	| override_mode ignorables type_name symbol_name argument_list ccodes_block
	{ z_zco_source_generator_class_override_member_function_decl(source_generator, $4, $5, $6); free($2); free($5); free($6); }

	| override_mode ignorables type_name symbol_name ignorables argument_list ccodes_block
	{ z_zco_source_generator_class_override_member_function_decl(source_generator, $4, $6, $7); free($2); free($5); free($6); free($7); }

	| override_mode ignorables type_name symbol_name argument_list ignorables ccodes_block
	{ z_zco_source_generator_class_override_member_function_decl(source_generator, $4, $5, $7); free($2); free($5); free($6); free($7); }

	| override_mode ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{ z_zco_source_generator_class_override_member_function_decl(source_generator, $4, $6, $8); free($2); free($5); free($6); free($7); free($8); }

	/* member functions */
	| access_specifier ignorables type_name symbol_name argument_list ccodes_block
	{ z_zco_source_generator_class_member_function_decl(source_generator, $4, $5, $6); free($2); free($5); free($6); }

	| access_specifier ignorables type_name symbol_name ignorables argument_list ccodes_block
	{ z_zco_source_generator_class_member_function_decl(source_generator, $4, $6, $7); free($2); free($5); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name argument_list ignorables ccodes_block
	{ z_zco_source_generator_class_member_function_decl(source_generator, $4, $5, $7); free($2); free($5); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{ z_zco_source_generator_class_member_function_decl(source_generator, $4, $6, $8); free($2); free($5); free($6); free($7); free($8); }

	/* special member functions (ie. init() or global_init() */
	| symbol_name argument_list ccodes_block
	{ z_zco_source_generator_special_member_function_decl(source_generator, $1, $2, $3); free($2); free($3); }

	| symbol_name ignorables argument_list ccodes_block
	{ z_zco_source_generator_special_member_function_decl(source_generator, $1, $3, $4); free($2); free($3); free($4); }

	| symbol_name argument_list ignorables ccodes_block
	{ z_zco_source_generator_special_member_function_decl(source_generator, $1, $2, $4); free($2); free($3); free($4); }

	| symbol_name ignorables argument_list ignorables ccodes_block
	{ z_zco_source_generator_special_member_function_decl(source_generator, $1, $3, $5); free($2); free($3); free($4); free($5); }

	/* signals */
	| access_specifier ignorables type_name symbol_name BANG argument_list SEMICOLON
	{ z_zco_source_generator_class_signal_decl(source_generator, $4, $6); free($2); free($6); }

	| access_specifier ignorables type_name symbol_name BANG ignorables argument_list SEMICOLON
	{ z_zco_source_generator_class_signal_decl(source_generator, $4, $7); free($2); free($5); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name BANG argument_list ignorables SEMICOLON
	{ z_zco_source_generator_class_signal_decl(source_generator, $4, $6); free($2); free($6); free($7); }

	| access_specifier ignorables type_name symbol_name BANG ignorables argument_list ignorables SEMICOLON
	{ z_zco_source_generator_class_signal_decl(source_generator, $4, $7); free($2); free($6); free($7); free($8); }

	/* properties */
	| access_specifier ignorables type_name symbol_name OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		free($2);
	}

	| access_specifier ignorables type_name symbol_name ignorables OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		free($2);
		free($5);
	}

	/* attached properties */
	| access_specifier ignorables type_name symbol_name hash OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		free($2);
	}

	| access_specifier ignorables type_name symbol_name hash ignorables OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		free($2);
		free($6);
	}
	;

hash
	: HASH { z_zco_source_generator_enable_attached_property(source_generator); }
	;

property_objects
	: property_object 
	| property_objects property_object 
	| ignorable                            { free($1); }
	| property_objects ignorable           { free($2); }
	;

get_keyword
	: GET { z_zco_source_generator_record_line_number(source_generator); }
	;

set_keyword
	: SET { z_zco_source_generator_record_line_number(source_generator); }
	;

property_object
	: get_keyword ccodes_block		{ z_zco_source_generator_property_decl(source_generator,$1,$2); free($2); }
	| get_keyword ignorables ccodes_block	{ z_zco_source_generator_property_decl(source_generator,$1,$3); free($2); free($3); }
	| set_keyword ccodes_block		{ z_zco_source_generator_property_decl(source_generator,$1,$2); free($2); }
	| set_keyword ignorables ccodes_block	{ z_zco_source_generator_property_decl(source_generator,$1,$3); free($2); free($3); }
	;

ignorables
	: ignorable
	| ignorables ignorable { $$=z_zco_source_generator_strdup2(source_generator,$1,$2); free($1); free($2); }
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

void yyerror(const char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


int main(int argc, char **argv)
{
	static struct zco_context_t context;
	zco_context_init(&context);

	source_generator = z_zco_source_generator_new(&context);
	int rc = z_zco_source_generator_setup(source_generator, argc, argv);

	if (rc != 0)
		return rc;

	rc = yyparse();

	z_object_unref(Z_OBJECT(source_generator));
	zco_context_destroy(&context);

	return rc;
}


