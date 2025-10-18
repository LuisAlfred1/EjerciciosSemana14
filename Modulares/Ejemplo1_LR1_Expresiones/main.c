#include <stdio.h>

//Tarea: en el primer proceso me de resultado

// Declaración adelantada del analizador sintáctico generado por Bison.
int yyparse(void);

int main(void) {
    // Mantén stdout sin buffer (o con buffer por línea). Evita tocar stdin.
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    puts("Ingrese expresiones aritmeticas terminadas con ;");
    puts("Soporta enteros, + - * /, parentesis y menos unario. Ejemplos:");
    puts("  1+2*3;         -> 7");
    puts("  (5-2)*10;      -> 30");
    puts("  -8 + (3*4);    -> 4");
    puts("Finalice con: Ctrl+Z y Enter (Windows).");

    printf("Ingrese entrada => ");
    fflush(stdout);

    return yyparse();
}

