#include <stdio.h>

int yyparse(void);

int main() {
    printf("Ingrese una expresion:\n");
    yyparse();
    return 0;
}


/*
Entradas válidas

a+3	Suma simple entre variable y número
(a+b)-5	Agrupación con resta
((3+2)-a)	Expresión con paréntesis anidados
x-(y+7)	Variable menos una agrupación
m+(n-(p+2))	Expresión combinada con anidamiento múltiple
(1+2)+(3+4)	Dos sumas agrupadas
x+y+z	Varias sumas en cadena
(a)	Variable dentro de paréntesis (agrupación simple)
((a+b))	Agrupación doble válida
a-(b-(c-1))	Resta con anidamiento correcto

Entradas No Válidas

a+	Falta un operando después del +
-a	No se permite el signo unario al inicio
a++b	Dos operadores consecutivos
a+*b	Orden incorrecto de operadores
(a+b	Falta el paréntesis de cierre
a+b)	Falta el paréntesis de apertura
3a+5	El número no puede ir seguido de variable sin operador
@a+5	Carácter @ no reconocido
a b	Falta de operador entre a y b
(a)+(b	Paréntesis desbalanceados
 */