%{
#include "parser.h"
#include <string.h>
#include <stdlib.h>
%}

%%
[0-9]+              { yylval.str = strdup(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }
"("                 { return '('; }
")"                 { return ')'; }
"+"                 { return '+'; }
"-"                 { return '-'; }
[ \t\r\n]+          { /* ignorar espacios y tabulaciones */ }
.                   { return yytext[0]; }
%%

int yywrap() { return 1; }
