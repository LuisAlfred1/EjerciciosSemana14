#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variables globales y funciones

char input[256];
char *ptr;
char token_str[64];
int token;

//Definición de tokens
#define ID  256
#define NUM 257

//Funciones auxiliares
char* concat(const char* a, const char* b, const char* c) {
    char* result = (char*) malloc(strlen(a) + strlen(b) + strlen(c) + 1);
    strcpy(result, a);
    strcat(result, b);
    strcat(result, c);
    return result;
}

//Scanner
int yylex() {
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\r' || *ptr == '\n')
        ptr++;

    if (*ptr == '\0')
        return 0;

    if (*ptr == '(') { ptr++; return '('; }
    if (*ptr == ')') { ptr++; return ')'; }
    if (*ptr == '+') { ptr++; return '+'; }
    if (*ptr == '-') { ptr++; return '-'; }

    if ((*ptr >= '0' && *ptr <= '9')) {
        int i = 0;
        while (*ptr >= '0' && *ptr <= '9') token_str[i++] = *ptr++;
        token_str[i] = '\0';
        return NUM;
    }

    if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || *ptr == '_') {
        int i = 0;
        while ((*ptr >= 'a' && *ptr <= 'z') ||
               (*ptr >= 'A' && *ptr <= 'Z') ||
               (*ptr >= '0' && *ptr <= '9') ||
               *ptr == '_') {
            token_str[i++] = *ptr++;
        }
        token_str[i] = '\0';
        return ID;
    }

    return *ptr++;
}

/* -------------------------------
   Parser (descenso recursivo)
   Gramática equivalente:
     expr → term ((+|-) term)*
     term → ID | NUM | ( expr )
   ------------------------------- */
void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

/* Prototipos */
char* expr();
char* term();

//Implementación de la gramática
char* term() {
    char* result = NULL;

    if (token == ID) {
        printf("Identificador: %s\n", token_str);
        result = strdup(token_str);
        token = yylex();
    }
    else if (token == NUM) {
        printf("Numero: %s\n", token_str);
        result = strdup(token_str);
        token = yylex();
    }
    else if (token == '(') {
        token = yylex();
        char* inner = expr();
        if (token != ')') yyerror("Falta ')'");
        else token = yylex();
        printf("Agrupacion: (%s)\n", inner);
        result = concat("(", inner, ")");
        free(inner);
    }
    else {
        yyerror("Termino inesperado");
        token = yylex();
        result = strdup("?");
    }

    return result;
}

char* expr() {
    char* left = term();

    while (token == '+' || token == '-') {
        char op = token;
        token = yylex();
        char* right = term();

        if (op == '+') {
            printf("Suma: %s + %s\n", left, right);
            char* tmp = concat(left, " + ", right);
            free(left); free(right);
            left = tmp;
        } else {
            printf("Resta: %s - %s\n", left, right);
            char* tmp = concat(left, " - ", right);
            free(left); free(right);
            left = tmp;
        }
    }

    return left;
}

int main() {
    printf("Ingrese una expresion:\n");

    if (fgets(input, sizeof(input), stdin)) {
        ptr = input;
        token = yylex();

        expr();
    }

    return 0;
}