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
#define YYSTYPE char *

#include <stdio.h>
#include <string.h>
#include "zco.tab.h"
%}

%%
"\%h{"			         { yylval="%h{";            return HEADER_BLK_START;   }
"\%{"			            { yylval="%{";             return SOURCE_BLK_START;   }
"\%}"			            { yylval="%}";             return FILE_BLK_END;       }
"class"			         { yylval="class";          return CLASS;              }
"from"			         { yylval="from";           return FROM;               }
"{"			            { yylval="{";              return OBRACE;             }
"}"			            { yylval="}";              return EBRACE;             }
"("			            { yylval="(";              return OPAREN;             }
")"			            { yylval=")";              return EPAREN;             }
";"			            { yylval=";";              return SEMICOLON;          }
"public"		            { yylval="public";         return PUBLIC;             }
"private"		         { yylval="private";        return PRIVATE;            }
"property"		         { yylval="property";       return PROPERTY;           }
"get"			            { yylval="get";            return GET;                }
"set"			            { yylval="set";            return SET;                }
"override"		         { yylval="override";       return OVERRIDE;           }
"virtual"		         { yylval="virtual";        return VIRTUAL;            }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval=strdup(yytext);   return WORD;               }
[ \t\v\f\n]*            { yylval=yytext;           return SPACE;              }
.			               { yylval=strdup(yytext);   return CODE;               }

%%

int yywrap(void)
{
	return 1;
}

int column = 0;


