#ifndef LADRONES_H
#define LADRONES_H

#include <stdio.h>
#include <stdlib.h>
#define N 8
#define IZQ 1
#define DER 2
#define NUM_OPERADORES 2

typedef struct{

    int cinta[N];
    int ladoizq, ladoder, robado, recuperado;
}tEstado;

static int cinta_inicial[N] = {4,3,2,5,7,1,8,6};

tEstado *crearEstado(int cinta[N]);

int esValido(unsigned op, tEstado *e);

tEstado *aplicaOperador(unsigned op, tEstado *e);

int testObjetivo(tEstado *e);




#endif

