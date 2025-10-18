#include <stdio.h>

int yyparse(void);

int main(void) {
    printf("Ejemplo3_DeteccionErrores (modular) - muestra recovery con 'error'\n");
    printf("Formato: id = expr ;  (escriba varias sentencias)\n");
    yyparse();
    return 0;
}
