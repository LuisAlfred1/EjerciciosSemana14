
/* parser.y - Construcción de AST con Bison */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"   // <- aquí incluyes Node
void yyerror(const char *s);
extern int yylex(void);
int eval(Node* n); /* prototipo para que sea visible en las acciones */

Node* mknode(const char *v, Node* l, Node* r){
    Node* n = malloc(sizeof(Node));
    n->val = strdup(v);
    n->left = l; n->right = r;
    return n;
}

void printTree(Node* n, int indent){
    if (!n) return;
    for(int i=0;i<indent;i++) printf("  ");
    printf("%s\n", n->val);
    printTree(n->left, indent+1);
    printTree(n->right, indent+1);
}
%}
%union { int num; char* id; Node* node; }
%token <num> NUM
%token <id> ID
%type <node> expr
%left '+' '-'
%left '*' '/'
%start input
%%
input:
  /* empty */ { printf("Reduce: input -> ε\n"); }
| input line  { printf("Reduce: input -> input line\n"); }
;
line: expr ';' { int val = eval($1); printf("Linea completa -> resultado: %d\n", val); printf("Linea completa -> imprimir AST:\n"); printTree($1,0); }
;
expr:
   expr '+' expr { $$ = mknode("+", $1, $3); printf("Reduce: expr -> expr + expr (crear nodo '+')\n"); }
 | expr '-' expr { $$ = mknode("-", $1, $3); printf("Reduce: expr -> expr - expr (crear nodo '-')\n"); }
 | expr '*' expr { $$ = mknode("*", $1, $3); printf("Reduce: expr -> expr * expr (crear nodo '*')\n"); }
 | expr '/' expr { $$ = mknode("/", $1, $3); printf("Reduce: expr -> expr / expr (crear nodo '/')\n"); }
 | '(' expr ')'  { $$ = $2; printf("Reduce: expr -> ( expr )\n"); }
 | NUM           { char buf[64]; sprintf(buf, "%d", $1); $$ = mknode(buf, NULL, NULL); printf("Reduce: expr -> NUM (%d)\n", $1); }
 | ID            { $$ = mknode($1, NULL, NULL); printf("Reduce: expr -> ID (%s)\n", $1); free($1); }
;
%%
void yyerror(const char *s) { fprintf(stderr, "Error: %s\n", s); }
/* main moved to main.c to avoid duplicate symbol when linking */

/* Evalua el AST y devuelve un entero (asume operaciones enteras) */
int eval(Node* n){
  if (!n) return 0;
  /* Si hoja: intentar convertir a número, si no, valor 0 */
  if (!n->left && !n->right){
    if (n->val){
      char *endptr = NULL;
      long v = strtol(n->val, &endptr, 10);
      if (endptr && *endptr == '\0') return (int)v;
      /* no es número: variable/ID -> valor 0 por defecto */
    }
    return 0;
  }
  /* Nodo interno: operadores binarios */
  int l = eval(n->left);
  int r = eval(n->right);
  if (strcmp(n->val, "+") == 0) return l + r;
  if (strcmp(n->val, "-") == 0) return l - r;
  if (strcmp(n->val, "*") == 0) return l * r;
  if (strcmp(n->val, "/") == 0) { if (r==0) { fprintf(stderr, "Error: division por cero\n"); return 0; } return l / r; }
  return 0;
}
