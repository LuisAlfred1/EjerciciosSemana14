
/* scanner.l - tokens para asignaciones y expresiones */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
extern char *yytext;
%}
ID [a-zA-Z_][a-zA-Z0-9_]*
DIGIT [0-9]+
%%
{DIGIT}    { yylval.num = atoi(yytext); printf("Token: NUM(%s)\n", yytext); return NUM; }
{ID}       { yylval.id = strdup(yytext); printf("Token: ID(%s)\n", yytext); return ID; }
"="        { printf("Token: =\n"); return '='; }
";"        { printf("Token: ;\n"); return ';'; }
[ \t\r]+   { /* ignore */ }
"("        { printf("Token: (\n"); return '('; }
")"        { printf("Token: )\n"); return ')'; }
"+"|"-"|"*"|"/" { printf("Token: %s\n", yytext); return yytext[0]; }
\n         { /* ignore newline */ }
.          { printf("Char desconocido: %s\n", yytext); }
%%
int yywrap(void) { return 1; }
