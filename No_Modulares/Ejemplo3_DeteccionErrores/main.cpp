#include <stdio.h>
#include <string.h>

//Definiciones de tokens
enum Tokens {
    NUM = 256,
    ID
};

//Variables globales
char input[256];
char *ptr;
int yylval_num;
char yylval_id[64];

//Scanner (analizador léxico)
int yylex() {
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\r' || *ptr == '\n')
        ptr++;

    if (*ptr == '\0')
        return 0;

    if (*ptr == ';') { printf("Token: ;\n"); return *ptr++; }
    if (*ptr == '=') { printf("Token: =\n"); return *ptr++; }
    if (*ptr == '(') { printf("Token: (\n"); return *ptr++; }
    if (*ptr == ')') { printf("Token: )\n"); return *ptr++; }
    if (strchr("+-*/", *ptr)) {
        printf("Token: %c\n", *ptr);
        return *ptr++;
    }

    if (*ptr >= '0' && *ptr <= '9') {
        yylval_num = 0;
        while (*ptr >= '0' && *ptr <= '9') {
            yylval_num = yylval_num * 10 + (*ptr - '0');
            ptr++;
        }
        printf("Token: NUM(%d)\n", yylval_num);
        return NUM;
    }

    if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || *ptr == '_') {
        int i = 0;
        while ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= '0' && *ptr <= '9') || *ptr == '_') {
            yylval_id[i++] = *ptr++;
        }
        yylval_id[i] = '\0';
        printf("Token: ID(%s)\n", yylval_id);
        return ID;
    }

    printf("Carácter desconocido: %c\n", *ptr);
    ptr++;
    return -1;
}

//Funciones del parser
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

//Prototipos
void input_();
void line();
void stmt();
int expr();

//Gramática (descenso recursivo)
int token;

void match(int expected) {
    if (token == expected) {
        token = yylex();
    } else {
        yyerror("token inesperado");
        token = yylex(); // intenta recuperarse
    }
}

void input_() {
    while (token != 0) {
        line();
    }
}

void line() {
    if (token == ID) {
        stmt();
        if (token == ';') {
            match(';');
            printf("[OK] sentencia procesada\n");
        } else {
            yyerror("falta ';'");
            while (token != ';' && token != 0) token = yylex();
            if (token == ';') token = yylex(); // recuperación
        }
    } else {
        yyerror("línea inválida");
        token = yylex();
    }
}

void stmt() {
    char id_local[64];
    strcpy(id_local, yylval_id);
    match(ID);
    if (token == '=') {
        match('=');
        expr();
        printf("Reduce: stmt -> ID = expr (asignación)\n");
    } else {
        yyerror("falta '='");
    }
}

int expr() {
    // expr → término { (+|-) término }
    int val = 0;
    if (token == NUM) {
        printf("Reduce: expr -> NUM(%d)\n", yylval_num);
        match(NUM);
    } else if (token == ID) {
        printf("Reduce: expr -> ID(%s)\n", yylval_id);
        match(ID);
    } else if (token == '(') {
        match('(');
        expr();
        match(')');
        printf("Reduce: expr -> ( expr )\n");
    } else {
        yyerror("expresión inválida");
        token = yylex();
    }

    while (token == '+' || token == '-' || token == '*' || token == '/') {
        char op = token;
        match(token);
        expr();
        printf("Reduce: expr -> expr %c expr\n", op);
    }

    return val;
}

//Función principal
int main() {
    printf("Ejemplo3_No_Modular - Manejo de errores con 'error'\n");
    printf("Formato: id = expr ;\n");
    printf("Escriba varias sentencias: \n");

    while (fgets(input, sizeof(input), stdin)) {
        ptr = input;
        token = yylex();
        input_();
    }

    return 0;
}