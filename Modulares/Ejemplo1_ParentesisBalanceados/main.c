#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    extern int yyparse(void);
    yyparse();
    return 0;
}

/*
Ejemplos de entradas válidas
- (a(b)c)
- abc _id (x) y
- ()() 123+45
- (foo) bar (baz(qux)) !!!
- Línea vacía o solo espacios

Ejemplos de entradas inválidas
- (
- )
- (a))
- ((a)
  */

/*

 */