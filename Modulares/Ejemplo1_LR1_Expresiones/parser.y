%{
    #include <stdio.h>

    int yylex(void);
    void yyerror(const char* s);
%}

/* Valor semántico entero para todas las reglas */
%define api.value.type {int}

/* Forzar analizador LR(1) canónico */
%define lr.type canonical-lr

/* Tokens */
%token NUM
%token SEMI

/* Precedencia y asociatividad */
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input
    : /* vacío */
    | input stmt
    ;

stmt
    : expr SEMI                 { printf("Resultado = %d\n", $1); printf("Ingrese otra entrada => "); fflush(stdout); }
    | error SEMI                { printf("Recuperado tras error hasta ';'\n"); fflush(stdout); yyerrok; }
    ;

expr
    : NUM
    | expr '+' expr             { $$ = $1 + $3; }
    | expr '-' expr             { $$ = $1 - $3; }
    | expr '*' expr             { $$ = $1 * $3; }
    | expr '/' expr             {
                                    if ($3 == 0) {
                                        yyerror("division por cero");
                                        $$ = 0;
                                    } else {
                                        $$ = $1 / $3;
                                    }
                                 }
    | '(' expr ')'              { $$ = $2; }
    | '-' expr %prec UMINUS     { $$ = -$2; }
    ;
%%

void yyerror(const char* s) {
    fprintf(stderr, "Error de parseo: %s\n", s);
}