#include <stdio.h>
#include "jarras.h"

int main() {
//pruebas del código generado
int op;
tEstado *s,*a;
a=estadoInicial(); // considerar distintas situaciones iniciales
for (op=1; op<=NUM_OPERADORES; op++) {
if (esValido(op, a)){
s=aplicaOperador(op,a);
dispOperador(op);
dispEstado(s);
}//if
} //for
}//main
