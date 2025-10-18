
/* parser.y - Manejo de errores con producción 'error' */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
extern int yylex(void);
%}
%union { int num; char* id; }
%token <num> NUM
%token <id> ID
%token SEMI
%left '+' '-'
%left '*' '/'
%start input
%%
input: /* empty */ | input line ;
line: stmt ';' { printf("[OK] sentencia procesada\n"); }
    | error ';' { yyerror("Recuperado: error hasta ';'"); yyclearin; }
    ;
stmt: ID '=' expr { printf("Reduce: stmt -> ID = expr (asignación)\n"); free($1); }
    ;
expr: expr '+' expr { printf("Reduce: expr -> expr + expr\n"); $$ = NULL; }
    | expr '-' expr { printf("Reduce: expr -> expr - expr\n"); $$ = NULL; }
    | expr '*' expr { printf("Reduce: expr -> expr * expr\n"); $$ = NULL; }
    | expr '/' expr { printf("Reduce: expr -> expr / expr\n"); $$ = NULL; }
    | '(' expr ')'  { printf("Reduce: expr -> ( expr )\n"); $$ = NULL; }
    | NUM { printf("Reduce: expr -> NUM (%d)\n", $1); $$ = NULL; }
    | ID  { printf("Reduce: expr -> ID (%s)\n", $1); free($1); $$ = NULL; }
    ;
%%
void yyerror(const char *s) { fprintf(stderr, "Error: %s\n", s); }
int main(void) {
    printf("Ejemplo3_DeteccionErrores (modular) - muestra recovery con 'error'\n");
    printf("Formato: id = expr ;  (escriba varias sentencias)\n");
    yyparse();
    return 0;
}
