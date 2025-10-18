%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat(const char* a, const char* b, const char* c) {
    char* result = malloc(strlen(a) + strlen(b) + strlen(c) + 1);
    strcpy(result, a);
    strcat(result, b);
    strcat(result, c);
    return result;
}

int yylex(void);
int yyerror(const char* s);
%}

%union {
    char* str;
}

%token <str> ID
%token <str> NUM
%type  <str> expr

%%

input:
    expr { printf("\nExpresion final: %s\n", $1); free($1); }
;

expr:
      expr '+' expr  {
          printf("Suma: %s + %s\n", $1, $3);
          $$ = concat($1, " + ", $3);
          free($1); free($3);
      }
    | expr '-' expr  {
          printf("Resta: %s - %s\n", $1, $3);
          $$ = concat($1, " - ", $3);
          free($1); free($3);
      }
    | '(' expr ')'   {
          printf("Agrupacion: (%s)\n", $2);
          $$ = concat("(", $2, ")");
          free($2);
      }
    | ID             { $$ = strdup($1); printf("Identificador: %s\n", $1); }
    | NUM            { $$ = strdup($1); printf("Numero: %s\n", $1); }
;

%%

int yyerror(const char* s) {
    printf("Error: %s\n", s);
    return 0;
}
