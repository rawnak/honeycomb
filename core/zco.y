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


#define YYSTYPE ZString *

ZZcoSourceGenerator *source_generator;

int yylex(void);
%}

%token HEADER_BLK_START SOURCE_BLK_START FILE_BLK_END CLASS INTERFACE STRUCT UNION CONST SIGNED UNSIGNED COLON GLOBAL
%token OVERRIDE VIRTUAL WORD CODE OBRACE EBRACE OPAREN EPAREN SEMICOLON VAR_ARGS SPACE ASTERISK COMMENT COMMA HASH
%token BANG VOLATILE PUBLIC PROTECTED PRIVATE GET SET EXPORT ENUM STRING_LITERAL

%start translation_unit


%%

translation_unit
	: external_declaration
	| translation_unit external_declaration 
	| ignorable                      { z_object_unref((ZObject *) $1); }
	| translation_unit ignorable     { z_object_unref((ZObject *) $2); }
	;

external_declaration
	: header_block
	| source_block
	| class_definition
	| interface_definition
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
		z_object_unref(Z_OBJECT($2));
	}
	;

source_block
	: source_block_start ccodes FILE_BLK_END
	{
		z_zco_source_generator_write_source_block(source_generator, $2);
		z_object_unref(Z_OBJECT($2));
	}
	;

ccodes_block
	: OBRACE ccodes EBRACE
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;

		z_string_append_format(res, "%S%S%S", $1, $2, $3);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
	}

	| OBRACE EBRACE
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;

		z_string_append_format(res, "%S%S", $1,$2);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
	}
	;

ccodes
	: CODE
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes CODE
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| STRING_LITERAL
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes STRING_LITERAL
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| WORD
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes WORD
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| CLASS
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes CLASS
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| INTERFACE
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes INTERFACE
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| custom_type
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes custom_type
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| VAR_ARGS
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes VAR_ARGS
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| var_keyword
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes var_keyword
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| sign
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes sign
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| COLON
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes COLON
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| COMMA
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes COMMA
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| OPAREN
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes OPAREN
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| EPAREN
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes EPAREN
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| ASTERISK
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes ASTERISK
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| HASH
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes HASH
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| BANG
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes BANG
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| SEMICOLON
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes SEMICOLON
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| GLOBAL
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes GLOBAL
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| EXPORT
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes EXPORT
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| PUBLIC
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes PUBLIC
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| PROTECTED
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes PROTECTED
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| PRIVATE
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes PRIVATE
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| GET
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes GET
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| SET
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes SET
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| OVERRIDE
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes OVERRIDE
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| VIRTUAL
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| ccodes VIRTUAL
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}

	| ignorable
	| ccodes ignorable
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref((ZObject *) $2);
	}

	| ccodes_block
	| ccodes ccodes_block
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref((ZObject *) $2);
	}
	;

class_declaration
	: CLASS ignorables WORD 
	{
		z_zco_source_generator_class_declaration(source_generator);
		$$=$3;
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
	}
	;

interface_declaration
	: INTERFACE ignorables WORD 
	{
		z_zco_source_generator_interface_declaration(source_generator);
		$$=$3;
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
	}
	;

/* $4 should not be freed because it will be pointed to by parent_class_name_pascal */
parent_declaration
	: WORD
	{
		z_zco_source_generator_add_parent(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
	}

	| parent_declaration COMMA WORD
	{
		z_zco_source_generator_add_parent(source_generator, $3);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
	}

	| parent_declaration COMMA ignorables WORD
	{
		z_zco_source_generator_add_parent(source_generator, $4);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
	}

	| parent_declaration ignorables COMMA WORD
	{
		z_zco_source_generator_add_parent(source_generator, $4);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
	}

	| parent_declaration ignorables COMMA ignorables WORD
	{
		z_zco_source_generator_add_parent(source_generator, $5);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}
	;


/* $1 should not be freed because it will be pointed to by current_class_name_pascal */
full_class_declaration
	: class_declaration
	{
		z_zco_source_generator_prepare_class(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
	}

	| class_declaration ignorables
	{
		z_zco_source_generator_prepare_class(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
	}

	| class_declaration ignorables COLON ignorables parent_declaration
	{
		z_zco_source_generator_prepare_class(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
	}

	| class_declaration ignorables COLON ignorables parent_declaration ignorables
	{
		z_zco_source_generator_prepare_class(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($6));
	}
	;

full_interface_declaration
	: interface_declaration
	{
		z_zco_source_generator_prepare_interface(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
	}

	| interface_declaration ignorables
	{
		z_zco_source_generator_prepare_interface(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
	}

	| interface_declaration ignorables COLON ignorables parent_declaration
	{
		z_zco_source_generator_prepare_interface(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
	}

	| interface_declaration ignorables COLON ignorables parent_declaration ignorables
	{
		z_zco_source_generator_prepare_interface(source_generator, $1);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($6));
	}
	;

class_definition
	: full_class_declaration OBRACE class_objects EBRACE
	{
		z_zco_source_generator_finalize_class_definition(source_generator);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($4));
	}
	;

interface_definition
	: full_interface_declaration OBRACE class_objects EBRACE
	{
		z_zco_source_generator_finalize_interface_definition(source_generator);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($4));
	}
	;

class_objects
	: class_object 
	| class_objects class_object 
	| ignorable                      { z_object_unref((ZObject *) $1); }
	| class_objects ignorable        { z_object_unref((ZObject *) $2); }
	;

argument_list
	: OPAREN EPAREN
	{
		ZString *res = z_zco_source_generator_new_string(source_generator, NULL);
		z_string_append_format(res, "()");
		$$=res;
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
	}
	| OPAREN ignorables EPAREN
	{
		ZString *res = z_zco_source_generator_new_string(source_generator, NULL);
		z_string_append_format(res, "()");
		$$=res;
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
	}
	| OPAREN arguments EPAREN
	{
		ZString *res = z_zco_source_generator_new_string(source_generator, NULL);
		z_string_append_format(res, "(%S)", $2);
		$$=res;
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
	}
	;

arguments
	: argument
	| arguments COMMA argument
	{
		z_string_append_format((ZString *) $1, "%S%S", $2, $3);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
	}

	| arguments COMMA ignorables argument
	{
		z_string_append_format((ZString *) $1, "%S%S", $2, $4);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
	}

	| arguments COMMA ignorables argument ignorables
	{
		z_string_append_format((ZString *) $1, "%S%S", $2, $4);
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}
	;

pointers
	: ASTERISK
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	| pointers ASTERISK
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref(Z_OBJECT($2));
	}
	| ignorable
	| pointers ignorable
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref((ZObject *) $2);
	}
	;

custom_type
	: STRUCT
	| UNION
        | ENUM
	;

var_keyword
        : CONST
        | var_keyword CONST
        | VOLATILE
        | var_keyword VOLATILE
        ;

argument
	: WORD pointers WORD
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;

		z_string_append_format(res, "%S%S%S", $1,$2,$3);

		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
	}

	| var_keyword ignorables WORD pointers WORD
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;
		z_string_append_format(res, "%S %S%S%S", $1,$3,$4,$5);

		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}

	| custom_type ignorables WORD pointers WORD
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;
		z_string_append_format(res, "%S %S%S%S", $1,$3,$4,$5);

		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}

	| var_keyword ignorables custom_type ignorables WORD pointers WORD
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;
		z_string_append_format(res, "%S %S %S%S%S", $1,$3,$5,$6,$7);

		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
		z_object_unref(Z_OBJECT($7));
	}

	| sign ignorables WORD pointers WORD
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;
		z_string_append_format(res, "%S %S%S%S", $1,$3,$4,$5);

		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}

	| var_keyword ignorables sign ignorables WORD pointers WORD
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		$$=res;
		z_string_append_format(res, "%S %S %S%S%S", $1,$3,$5,$6,$7);

		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
		z_object_unref(Z_OBJECT($7));
	}

	| VAR_ARGS
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
	;

virtual_mode
	: VIRTUAL
	{
		z_zco_source_generator_enable_virtual_mode(source_generator);
		z_object_unref(Z_OBJECT($1));
	}
	;

override_mode
	: OVERRIDE OPAREN WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $3);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
	}

	| OVERRIDE OPAREN WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $3);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}

	| OVERRIDE OPAREN ignorables WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}

	| OVERRIDE OPAREN ignorables WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
	}

	| OVERRIDE ignorables OPAREN WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
	}

	| OVERRIDE ignorables OPAREN WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $4);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
	}

	| OVERRIDE ignorables OPAREN ignorables WORD EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $5);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
	}

	| OVERRIDE ignorables OPAREN ignorables WORD ignorables EPAREN
	{
		z_zco_source_generator_enable_override_mode(source_generator, $5);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
		z_object_unref(Z_OBJECT($7));
	}
	;

access_specifier
	: PRIVATE
	{
		z_zco_source_generator_set_access_mode(source_generator, ACCESS_PRIVATE);
		z_object_unref(Z_OBJECT($1));
	}
	| PUBLIC
	{
		z_zco_source_generator_set_access_mode(source_generator, ACCESS_PUBLIC);
		z_object_unref(Z_OBJECT($1));
	}
	| PROTECTED
	{
		z_zco_source_generator_set_access_mode(source_generator, ACCESS_PROTECTED);
		z_object_unref(Z_OBJECT($1));
	}
	| GLOBAL
	{
		z_zco_source_generator_set_access_mode(source_generator, ACCESS_GLOBAL);
		z_object_unref(Z_OBJECT($1));
	}
	;

export_options
        : EXPORT
        {
                z_zco_source_generator_set_export_option(source_generator, 1);
                z_object_unref(Z_OBJECT($1));
        }
        ;

type_name
	: WORD pointers
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format(res, "%S%S", $1,$2);

		z_zco_source_generator_set_type_name(source_generator, res);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT(res));
	}

	| var_keyword ignorables WORD pointers
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format(res, "%S %S%S", $1,$3,$4);

		z_zco_source_generator_set_type_name(source_generator, res);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT(res));
	}

	| custom_type ignorables WORD pointers
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format(res, "%S %S%S", $1,$3,$4);

		z_zco_source_generator_set_type_name(source_generator, res);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT(res));
	}

	| var_keyword ignorables custom_type ignorables WORD pointers
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format(res, "%S %S %S%S", $1,$3,$5,$6);

		z_zco_source_generator_set_type_name(source_generator, res);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
		z_object_unref(Z_OBJECT(res));
	}

	| sign ignorables WORD pointers
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format(res, "%S %S%S", $1,$3,$4);

		z_zco_source_generator_set_type_name(source_generator, res);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT(res));
	}

	| var_keyword ignorables sign ignorables WORD pointers
	{
		ZString *res = z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format(res, "%S %S %S%S",$1,$3,$5,$6);

		z_zco_source_generator_set_type_name(source_generator, res);
		z_object_unref(Z_OBJECT($1));
		z_object_unref(Z_OBJECT($2));
		z_object_unref(Z_OBJECT($3));
		z_object_unref(Z_OBJECT($4));
		z_object_unref(Z_OBJECT($5));
		z_object_unref(Z_OBJECT($6));
		z_object_unref(Z_OBJECT(res));
	}
	;

symbol_name
	: WORD
	{
		z_zco_source_generator_set_symbol_name(source_generator, $1);
	}
	;

class_object
	/* data members */
	: access_specifier ignorables type_name symbol_name SEMICOLON
	{
		z_zco_source_generator_add_class_data_member(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
	}

	| access_specifier ignorables type_name symbol_name ignorables SEMICOLON
	{
		z_zco_source_generator_add_class_data_member(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
	}

	/* virtual data members */
	| access_specifier ignorables virtual_mode ignorables type_name symbol_name SEMICOLON
	{
		z_zco_source_generator_add_class_virtual_data_member(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
	}

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables SEMICOLON
	{
		z_zco_source_generator_add_class_virtual_data_member(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	/* virtual member functions */
	| access_specifier ignorables virtual_mode ignorables type_name symbol_name argument_list ccodes_block
	{
		z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, (ZString *) $7, (ZString *) $8);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables argument_list ccodes_block
	{
		z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, (ZString *) $8, (ZString *) $9);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
	}

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, (ZString *) $7, (ZString *) $9);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
	}

	| access_specifier ignorables virtual_mode ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_virtual_member_function_decl(source_generator, $6, (ZString *) $8, (ZString *) $10);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
		z_object_unref((ZObject *) $10);
	}

	/* override member functions */
	| override_mode ignorables type_name symbol_name argument_list ccodes_block
	{
		z_zco_source_generator_class_override_member_function_decl(source_generator, $4, (ZString *) $5, (ZString *) $6);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
	}

	| override_mode ignorables type_name symbol_name ignorables argument_list ccodes_block
	{
		z_zco_source_generator_class_override_member_function_decl(source_generator, $4, (ZString *) $6, (ZString *) $7);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
	}

	| override_mode ignorables type_name symbol_name argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_override_member_function_decl(source_generator, $4, (ZString *) $5, (ZString *) $7);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
	}

	| override_mode ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_override_member_function_decl(source_generator, $4, (ZString *) $6, (ZString *) $8);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	/* member functions */
	| access_specifier ignorables type_name symbol_name argument_list ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $4, (ZString *) $5, (ZString *) $6);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
	}

	| access_specifier ignorables type_name symbol_name ignorables argument_list ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $4, (ZString *) $6, (ZString *) $7);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
	}

	| access_specifier ignorables type_name symbol_name argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $4, (ZString *) $5, (ZString *) $7);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
	}

	| access_specifier ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $4, (ZString *) $6, (ZString *) $8);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	| access_specifier ignorables export_options ignorables type_name symbol_name argument_list ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $6, (ZString *) $7, (ZString *) $8);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	| access_specifier ignorables export_options ignorables type_name symbol_name ignorables argument_list ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $6, (ZString *) $8, (ZString *) $9);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
	}

	| access_specifier ignorables export_options ignorables type_name symbol_name argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $6, (ZString *) $7, (ZString *) $9);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
	}

	| access_specifier ignorables export_options ignorables type_name symbol_name ignorables argument_list ignorables ccodes_block
	{
		z_zco_source_generator_class_member_function_decl(source_generator, $6, (ZString *) $8, (ZString *) $10);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
		z_object_unref((ZObject *) $10);
	}

	/* special member functions (ie. init() or global_init() */
	| symbol_name argument_list ccodes_block
	{
		z_zco_source_generator_special_member_function_decl(source_generator, $1, (ZString *) $2, (ZString *) $3);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
	}

	| symbol_name ignorables argument_list ccodes_block
	{
		z_zco_source_generator_special_member_function_decl(source_generator, $1, (ZString *) $3, (ZString *) $4);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
		z_object_unref((ZObject *) $4);
	}

	| symbol_name argument_list ignorables ccodes_block
	{
		z_zco_source_generator_special_member_function_decl(source_generator, $1, (ZString *) $2, (ZString *) $4);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
		z_object_unref((ZObject *) $4);
	}

	| symbol_name ignorables argument_list ignorables ccodes_block
	{
		z_zco_source_generator_special_member_function_decl(source_generator, $1, (ZString *) $3, (ZString *) $5);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
	}

	/* signals */
	| access_specifier ignorables type_name symbol_name BANG argument_list SEMICOLON
	{
		z_zco_source_generator_class_signal_decl(source_generator, $4, (ZString *) $6);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
	}

	| access_specifier ignorables type_name symbol_name BANG ignorables argument_list SEMICOLON
	{
		z_zco_source_generator_class_signal_decl(source_generator, $4, (ZString *) $7);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	| access_specifier ignorables type_name symbol_name BANG argument_list ignorables SEMICOLON
	{
		z_zco_source_generator_class_signal_decl(source_generator, $4, (ZString *) $6);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
	}

	| access_specifier ignorables type_name symbol_name BANG ignorables argument_list ignorables SEMICOLON
	{
		z_zco_source_generator_class_signal_decl(source_generator, $4, (ZString *) $7);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $8);
		z_object_unref((ZObject *) $9);
	}

	/* properties */
	| access_specifier ignorables type_name symbol_name OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $7);
	}

	| access_specifier ignorables type_name symbol_name ignorables OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $5);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $8);
	}

	/* attached properties */
	| access_specifier ignorables type_name symbol_name hash OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $8);
	}

	| access_specifier ignorables type_name symbol_name hash ignorables OBRACE property_objects EBRACE
	{ 
		z_zco_source_generator_finalize_property(source_generator);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $4);
		z_object_unref((ZObject *) $6);
		z_object_unref((ZObject *) $7);
		z_object_unref((ZObject *) $9);
	}
	;

hash
	: HASH
	{
		z_zco_source_generator_enable_attached_property(source_generator);
		z_object_unref(Z_OBJECT($1));
	}
	;

property_objects
	: property_object 
	| property_objects property_object 
	| ignorable                            { z_object_unref((ZObject *) $1); }
	| property_objects ignorable           { z_object_unref((ZObject *) $2); }
	;

get_keyword
	: GET
	{
		z_zco_source_generator_record_line_number(source_generator);
	}
	;

set_keyword
	: SET
	{
		z_zco_source_generator_record_line_number(source_generator);
	}
	;

property_object
	: get_keyword ccodes_block
	{
		z_zco_source_generator_property_decl(source_generator,$1, (ZString *) $2);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
	}
	| get_keyword ignorables ccodes_block
	{
		z_zco_source_generator_property_decl(source_generator,$1, (ZString *) $3);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
	}
	| set_keyword ccodes_block
	{
		z_zco_source_generator_property_decl(source_generator,$1, (ZString *) $2);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
	}
	| set_keyword ignorables ccodes_block
	{
		z_zco_source_generator_property_decl(source_generator,$1, (ZString *) $3);
		z_object_unref((ZObject *) $1);
		z_object_unref((ZObject *) $2);
		z_object_unref((ZObject *) $3);
	}
	;

ignorables
	: ignorable
	| ignorables ignorable
	{
		z_string_append_format((ZString *) $1, "%S", $2);
		z_object_unref((ZObject *) $2);
	}
	;

ignorable
	: SPACE
	{
		char *input = z_string_get_cstring($1, Z_STRING_ENCODING_UTF8);
		const char *str = (strchr(input,'\n'))? "\n" : " ";
		ZString *res = z_zco_source_generator_new_string(source_generator, str);
		$$=res;
		free(input);
		z_object_unref(Z_OBJECT($1));
	}
	| COMMENT
	{
		$$=z_zco_source_generator_new_string(source_generator,NULL);
		z_string_append_format($$, "%S", $1);
		z_object_unref(Z_OBJECT($1));
	}
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

	source_generator = z_zco_source_generator_new(&context, NULL);
	int rc = z_zco_source_generator_setup(source_generator, argc, argv);

	if (rc != 0)
		return rc;

	rc = yyparse();

        z_zco_source_generator_shutdown(source_generator);
	z_object_unref(Z_OBJECT(source_generator));
	zco_context_destroy(&context);

	return rc;
}


