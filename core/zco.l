/* ZCO - Cross-platform Application Framework
 * Copyright (C) 2014  Syeda Sultana
 *
 * zco.l: Lexer for ZCO preprocessor
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
#define YYSTYPE ZString *

#include <z-string.h>
#include "zco.tab.h"
#include <z-zco-source-generator.h>
#include <stdio.h>
#include <string.h>

extern ZZcoSourceGenerator *source_generator;

static ZString *to_zstring(char *s)
{
	return z_zco_source_generator_new_string(source_generator, s);
}

%}

%x IN_COMMENT

%%

"\%h{" { yylval=NULL;  return HEADER_BLK_START; }
"\%{"  { yylval=NULL;  return SOURCE_BLK_START; }
"\%}"  { yylval=NULL;  return FILE_BLK_END;     }

<INITIAL>{
   "/*"     yylval=to_zstring(yytext);  BEGIN(IN_COMMENT);  return COMMENT;
}
<IN_COMMENT>{
   "*/"     yylval=to_zstring(yytext);  BEGIN(INITIAL); return COMMENT;
   [^*\n]+  yylval=to_zstring(yytext);                  return COMMENT;   /* eat comment in chunks */
   "*"      yylval=to_zstring(yytext);                  return COMMENT;   /* eat the lone star */
   \n       yylval=to_zstring(yytext);  ++yylineno;     return COMMENT;
}

\/\/.*$                 { yylval=to_zstring(yytext);                return COMMENT;        }
L?\"(\\.|[^\\"])*\"     { yylval=to_zstring(yytext);                return STRING_LITERAL; }
"enum"                  { yylval=to_zstring("enum");                return ENUM;           }
"struct"                { yylval=to_zstring("struct");              return STRUCT;         }
"union"                 { yylval=to_zstring("union");               return UNION;          }
"const"                 { yylval=to_zstring("const");               return CONST;          }
"unsigned"              { yylval=to_zstring("unsigned");            return UNSIGNED;       }
"signed"                { yylval=to_zstring("signed");              return SIGNED;         }
"class"                 { yylval=to_zstring("class");               return CLASS;          }
"interface"             { yylval=to_zstring("interface");           return INTERFACE;      }
"volatile"              { yylval=to_zstring("volatile");            return VOLATILE;       }
":"                     { yylval=to_zstring(":");                   return COLON;          }
"{"                     { yylval=to_zstring("{");                   return OBRACE;         }
"}"                     { yylval=to_zstring("}");                   return EBRACE;         }
"("                     { yylval=to_zstring("(");                   return OPAREN;         }
")"                     { yylval=to_zstring(")");                   return EPAREN;         }
";"                     { yylval=to_zstring(";");                   return SEMICOLON;      }
"..."                   { yylval=to_zstring("...");                 return VAR_ARGS;       }
"*"                     { yylval=to_zstring("*");                   return ASTERISK;       }
"!"                     { yylval=to_zstring("!");                   return BANG;           }
"#"                     { yylval=to_zstring("#");                   return HASH;           }
"export"                { yylval=to_zstring("export");              return EXPORT;         }
"global"                { yylval=to_zstring("global");              return GLOBAL;         }
"public"                { yylval=to_zstring("public");              return PUBLIC;         }
"protected"             { yylval=to_zstring("protected");           return PROTECTED;      }
"private"               { yylval=to_zstring("private");             return PRIVATE;        }
"get"                   { yylval=to_zstring("get");                 return GET;            }
"set"                   { yylval=to_zstring("set");                 return SET;            }
"override"              { yylval=to_zstring("override");            return OVERRIDE;       }
"virtual"               { yylval=to_zstring("virtual");             return VIRTUAL;        }
","                     { yylval=to_zstring(",");                   return COMMA;          }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval=to_zstring(yytext);                return WORD;           }
\n                      { yylval=to_zstring(yytext);   ++yylineno;  return SPACE;          }
[ \t\v\f]*              { yylval=to_zstring(yytext);                return SPACE;          }
.                       { yylval=to_zstring(yytext);                return CODE;           }

%%

int yywrap(void)
{
        return 1;
}

int column = 0;


