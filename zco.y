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
char *current_class_name;
char *type_name;
char *symbol_name;
int access_mode;

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

static void member_function_decl(const char *type, const char *symbol, const char *arglist, const char *code)
{
   if (access_mode == 2) {
         /* for function prototype */
         strcat_safe(&function_prototypes_h, type);
         strcat_safe(&function_prototypes_h, " ");
         strcat_safe(&function_prototypes_h, current_class_name);
         strcat_safe(&function_prototypes_h, "_");
         strcat_safe(&function_prototypes_h, symbol);
         strcat_safe(&function_prototypes_h, arglist);
         strcat_safe(&function_prototypes_h, ";\n");

         /* for function definition */
         strcat_safe(&function_definitions, type);
         strcat_safe(&function_definitions, " ");
         strcat_safe(&function_definitions, current_class_name);
         strcat_safe(&function_definitions, "_");
         strcat_safe(&function_definitions, symbol);
         strcat_safe(&function_definitions, arglist);
         strcat_safe(&function_definitions, "\n");
         strcat_safe(&function_definitions, code);
         strcat_safe(&function_definitions, "\n");

   } else if (access_mode == 1) {
         /* for function prototype */
         strcat_safe(&function_prototypes_c, "static ");
         strcat_safe(&function_prototypes_c, type);
         strcat_safe(&function_prototypes_c, " ");
         strcat_safe(&function_prototypes_c, current_class_name);
         strcat_safe(&function_prototypes_c, "_");
         strcat_safe(&function_prototypes_c, symbol);
         strcat_safe(&function_prototypes_c, arglist);
         strcat_safe(&function_prototypes_c, ";\n");

         /* for function definition */
         strcat_safe(&function_definitions, "static ");
         strcat_safe(&function_definitions, type);
         strcat_safe(&function_definitions, " ");
         strcat_safe(&function_definitions, current_class_name);
         strcat_safe(&function_definitions, "_");
         strcat_safe(&function_definitions, symbol);
         strcat_safe(&function_definitions, arglist);
         strcat_safe(&function_definitions, "\n");
         strcat_safe(&function_definitions, code);
         strcat_safe(&function_definitions, "\n");
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

static char * pascal_to_lowercase(const char *s)
{
   int first = 1;
   char *res = malloc(strlen(s) * 2 + 1);
   char *p = res;

   for (; *s; ++s)
   {
      if (*s >= 'A' && *s <= 'Z') {
         if (!first) {
            *p = '_';
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

static void init_string(struct string_t *s)
{
   s->length = 0;
   s->data = 0;
}

static void add_data_member()
{
   if (access_mode == 1) {
      strcat_safe(&private_data, "\t");
      strcat_safe(&private_data, type_name);
      strcat_safe(&private_data, " ");
      strcat_safe(&private_data, symbol_name);
      strcat_safe(&private_data, ";\n");

   } else if (access_mode == 2) {
      strcat_safe(&public_data, "\t");
      strcat_safe(&public_data, type_name);
      strcat_safe(&public_data, " ");
      strcat_safe(&public_data, symbol_name);
      strcat_safe(&public_data, ";\n");
   }
}

static void class_init(const char *class_name, const char *parent_name)
{
      init_string(&private_data);
      init_string(&public_data);
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

      /* start the public data structure */
      strcat_safe(&public_data, "struct ");
      strcat_safe(&public_data, class_name);
      strcat_safe(&public_data, " {\n");
      
      if (parent_name) {
         strcat_safe(&public_data, "\tstruct ");
         strcat_safe(&public_data, parent_name);
         strcat_safe(&public_data, " parent;\n");
      }

      strcat_safe(&public_data, "\tstruct ");
      strcat_safe(&public_data, class_name);
      strcat_safe(&public_data, "Private _priv;\n");
      
      access_mode = 2;
      current_class_name = pascal_to_lowercase(class_name);
}

%}

%token HEADER_BLK_START SOURCE_BLK_START FILE_BLK_END CLASS FROM PUBLIC PRIVATE PROPERTY GET SET 
%token OVERRIDE VIRTUAL WORD CODE OBRACE EBRACE OPAREN EPAREN SEMICOLON SPACE 

%expect 1

%start translation_unit

%%

translation_unit
	: external_declaration
	| translation_unit external_declaration 
   | translation_unit white_space 
	;

external_declaration
	: header_block
	| source_block
	| class_definition
   {
      /* head macros in header file */
      dump_string(&h_macros_head, header_file);
      fprintf(header_file, "\n");

      /* private data members */
      dump_string(&private_data, header_file);
      fprintf(header_file, "};\n\n");

      /* public data members */
      dump_string(&public_data, header_file);
      fprintf(header_file, "};\n");

      /* function prototypes in header file */
      dump_string(&function_prototypes_h, header_file);
      fprintf(source_file, "\n");

      /* tail macros in header file */
      dump_string(&h_macros_tail, header_file);
      fprintf(header_file, "\n");

      /* macros in source file */
      dump_string(&c_macros, source_file);
      fprintf(source_file, "\n");

      /* function prototypes in source file */
      dump_string(&function_prototypes_c, source_file);
      fprintf(source_file, "\n");

      /* function definitions */
      dump_string(&function_definitions, source_file);
      fprintf(source_file, "\n");

      free(current_class_name);
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
	| ccodes CODE           { $$=strdup2($1,$2); free($1); free($2); }
	| WORD
	| ccodes WORD           { $$=strdup2($1,$2); free($1); free($2); }
	| CLASS                 { $$=strdup($1); }
	| ccodes CLASS          { $$=strdup2($1,$2); free($1); }
	| FROM                  { $$=strdup($1); }
	| ccodes FROM           { $$=strdup2($1,$2); free($1); }
	| OPAREN                { $$=strdup($1); }
	| ccodes OPAREN         { $$=strdup2($1,$2); free($1); }
	| EPAREN                { $$=strdup($1); }
	| ccodes EPAREN         { $$=strdup2($1,$2); free($1); }
	| SEMICOLON             { $$=strdup($1); }
	| ccodes SEMICOLON      { $$=strdup2($1,$2); free($1); }
	| PUBLIC                { $$=strdup($1); }
	| ccodes PUBLIC         { $$=strdup2($1,$2); free($1); }
	| PRIVATE               { $$=strdup($1); }
	| ccodes PRIVATE        { $$=strdup2($1,$2); free($1); }
	| PROPERTY              { $$=strdup($1); }
	| ccodes PROPERTY       { $$=strdup2($1,$2); free($1); }
	| GET                   { $$=strdup($1); }
	| ccodes GET            { $$=strdup2($1,$2); free($1); }
	| SET                   { $$=strdup($1); }
	| ccodes SET            { $$=strdup2($1,$2); free($1); }
	| OVERRIDE              { $$=strdup($1); }
	| ccodes OVERRIDE       { $$=strdup2($1,$2); free($1); }
	| VIRTUAL               { $$=strdup($1); }
	| ccodes VIRTUAL        { $$=strdup2($1,$2); free($1); }
   | white_space           { $$=strdup($1); }
   | ccodes white_space    { $$=strdup2($1,$2); free($1); }
	| ccodes_block
	| ccodes ccodes_block   { $$=strdup2($1,$2); free($1); free($2); }
	;

subclass_declaration
   : CLASS white_space WORD   { $$=$3; }
   ;

parent_declaration
   : white_space FROM white_space WORD { $$=$4; }
   ;

full_class_declaration
	: subclass_declaration                                   { class_init($1,0); free($1); }
	| subclass_declaration white_space                       { class_init($1,0); free($1); }
	| subclass_declaration parent_declaration                { class_init($1,$2); free($1); free($2); }
	| subclass_declaration parent_declaration white_space    { class_init($1,$2); free($1); free($2); }
   ;

class_definition
	: full_class_declaration OBRACE class_objects EBRACE
	;

class_objects
	: class_object 
	| class_objects class_object 
   | white_space 
   | class_objects white_space 
	;

argument_list
	: OPAREN EPAREN               { $$=strdup("()"); }
	| OPAREN white_space EPAREN   { $$=strdup("()"); }
	| OPAREN arguments EPAREN     { $$=strdup3("(",$2,")"); }
	;

arguments
	: argument
	| arguments ',' argument                           { $$=strdup3($1,$2,$3); free($1); free($3); }
	| arguments ',' white_space argument               { $$=strdup3($1,$2,$4); free($1); free($4); }
	| arguments white_space ',' argument               { $$=strdup3($1,$3,$4); free($1); free($4); }
	| arguments white_space ',' white_space argument   { $$=strdup3($1,$3,$5); free($1); free($5); }
	;

argument
   /* prefer shift over reduce */
	: WORD white_space WORD                   { $$=strdup3($1,$2,$3); free($1); free($3); }
	| WORD white_space WORD white_space WORD  { $$=strdup5($1,$2,$3,$4,$5); free($1); free($3); free($5); }
	;

access_specifier
	: PRIVATE   { access_mode = 1; }
	| PUBLIC    { access_mode = 2; }
   ;

type_name
   : WORD { if (type_name) { free(type_name); } type_name=$1; }
   ;

symbol_name
   : WORD { if (symbol_name) { free(symbol_name); } symbol_name=$1; }
   ;

class_object
	: access_specifier white_space type_name white_space symbol_name SEMICOLON
   { add_data_member(); }

	| access_specifier white_space type_name white_space symbol_name white_space SEMICOLON
   { add_data_member(); }

   | access_specifier white_space type_name white_space symbol_name argument_list ccodes_block
   { member_function_decl($3, $5, $6, $7); free($6); free($7); }

	| access_specifier white_space type_name white_space symbol_name white_space argument_list ccodes_block
   { member_function_decl($3, $5, $7, $8); free($7); free($8); }

	| access_specifier white_space type_name white_space symbol_name argument_list white_space ccodes_block
   { member_function_decl($3, $5, $6, $8); free($6); free($8); }

	| access_specifier white_space type_name white_space symbol_name white_space argument_list white_space ccodes_block
   { member_function_decl($3, $5, $7, $9); free($7); free($9); }

	| access_specifier white_space type_name white_space symbol_name OBRACE property_objects EBRACE
	| access_specifier white_space type_name white_space symbol_name white_space OBRACE property_objects EBRACE
	;

property_objects
	: property_object 
	| property_objects property_object  { $$=strdup2($1,$2); }
   | white_space 
   | property_objects white_space 
   ;

property_object
   : GET ccodes_block               { property_decl($1,$2); }
   | GET white_space ccodes_block   { property_decl($1,$3); }
   | SET ccodes_block               { property_decl($1,$2); }
   | SET white_space ccodes_block   { property_decl($1,$3); }
   ;

white_space
   : SPACE  { $$ = (strchr($1,'\n'))? "\n" : " "; }
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

int main(int argc, char **argv)
{
   char *filename, *temp;
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
   header_file = fopen(filename, "w");

   /* open the output source file for writing */
   filename[base_length+1] = 'c';
   source_file = fopen(filename, "w");

   /* use input .zco file as standard input */
   freopen(argv[1], "r", stdin);

	yyparse();


   fprintf(header_file, "\n\n");
   fprintf(source_file, "\n\n");

   fclose(header_file);
   fclose(source_file);
}


