%option noyywrap
%option nounput
%option noinput
%option interactive

%{
#include <stdlib.h>
#include "parser.tab.h"
#include <unistd.h>

%}

%%
[0-9]+         { yylval = (int)strtol(yytext, NULL, 10); return NUM; }
[;]            { return SEMI; }
[-+*/()]       { return (int)yytext[0]; }
[ \t\r\n]+     { /* ignorar espacios y CRLF de Windows */ }
.              { fprintf(stderr, "Caracter desconocido: '%c'\n", yytext[0]); }
%%

/* fin */