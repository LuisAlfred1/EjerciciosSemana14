
/* parser.y - Construcción de AST con Bison */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
extern int yylex(void);
typedef struct Node {
    char *val;
    struct Node *left;
    struct Node *right;
} Node;
Node* mknode(const char *v, Node* l, Node* r){
    Node* n = malloc(sizeof(Node));
    n->val = strdup(v);
    n->left = l; n->right = r; return n;
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
%type <node> expr term factor
%left '+' '-'
%left '*' '/'
%start input
%%
input:
  /* empty */ { printf("Reduce: input -> ε\n"); }
| input line  { printf("Reduce: input -> input line\n"); }
;
line: expr ';' { printf("Linea completa -> imprimir AST:\n"); printTree($1,0); }
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
int main(void) {
    printf("Ejemplo4_ArbolSintactico (modular) - construye y muestra AST\n");
    printf("Ingrese expresiones terminadas en ';'\n");
    yyparse();
    return 0;
}
