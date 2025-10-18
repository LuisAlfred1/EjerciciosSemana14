/* parser.y - Paréntesis balanceados (Bison con LR(1)) */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
extern int yylex(void);
%}

/* Genera parser.tab.h en el directorio de build */
%defines

/* Hace que YYSTYPE sea char* */
%define api.value.type {char *}

/* 🚀 Activa el analizador LR(1) canónico */
%define lr.type canonical-lr

/* Opcional: agrega más mensajes informativos si hay conflictos */
%define parse.error verbose

%token LP RP ID OTHER
%start input

%%
input:
      /* vacío */        { printf("Reduccion: entrada =>\n"); }
    | input element       { printf("Reduccion: entrada -> entrada elemento\n"); }
    ;

element:
      LP input RP         { printf("Reduccion: elemento -> ( entrada ) -> Parentesis balanceados\n"); }
    | ID                  { printf("Reduccion: elemento -> IDENTIFICADOR (%s)\n", $1); free($1); }
    | OTHER               { printf("Reduccion: elemento -> OTRO (%s)\n", $1); free($1); }
    ;
%%

void yyerror(const char *s) {
    (void)s; /* Ignorar mensaje en inglés */
    fprintf(stderr, "❌ Error de sintaxis detectado\n");
}

int main(void) {
    printf("Parser LR(1) - Verificador de paréntesis balanceados\n");
    printf("Ingrese una linea y finalice con EOF (Ctrl+D / Ctrl+Z).\n");
    yyparse();
    return 0;
}
