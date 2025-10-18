%{
#define YY_NO_UNISTD_H 1

#ifdef _WIN32
#include <io.h>
#define isatty  _isatty
#define fileno  _fileno
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
#define strdup _strdup
#endif
#include "parser.tab.h"
extern char *yytext;
%}

/* Reglas y opciones */
ID      [A-Za-z_][A-Za-z0-9_]*
WS      [ \t\r]+
LPAR    \(
RPAR    \)
OTHER   [^()\t\r\nA-Za-z_]+

%%
{LPAR}      { printf("Token: PAR_IZQ (\n"); return LP; }
{RPAR}      { printf("Token: PAR_DER )\n"); return RP; }
{ID}        { yylval = strdup(yytext); printf("Token: ID(%s)\n", yytext); return ID; }
{OTHER}     { yylval = strdup(yytext); printf("Token: OTRO(%s)\n", yytext); return OTHER; }
{WS}        { /* ignorar */ }
\n          { /* ignorar fin de línea */ }
%%

int yywrap(void) { return 1; }
