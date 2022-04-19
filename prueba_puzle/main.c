#include "puzle.h"

tEstado *e,*a,*i;
int valido = 0,op,igual;

int main()
{
a = estadoInicial();
i = estadoObjetivo();
e = estadoInicial();
igual = iguales(a,i);
printf("%d.\n",igual);

dispEstado(e);
while (op > 0 || op < 5){
puts("Introduce un estado: ");
scanf("%d",&op);
dispOperador(op);
valido = (esValido(op, e));
    if(valido)
    {
    e = aplicaOperador(op, e);
    dispEstado(e);
    }
}
return 0;
}
