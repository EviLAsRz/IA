#ifndef TABLERO_H
#define TABLERO_H

#include <stdio.h>
#include <stdlib.h>
#define ARRIBA_A 1
#define ABAJO_A 2
#define IZQ_A 3
#define DER_A 4

#define ARRIBA_B 5
#define ABAJO_B 6
#define IZQ_B 7
#define DER_B 8

#define ARRIBA_C 9
#define ABAJO_C 10
#define IZQ_C 11
#define DER_C 12

#define NUM_OPERADORES 12
#define N 6
#define nf 3

typedef struct{

    int tablero[N][N];
    int filas[nf+1];
    int cols[nf+1];

}tEstado;

tEstado *crearEstado(int celda[N][N]);
int testObjetivo(tEstado *, tEstado *);
int esValido(unsigned, tEstado *);
tEstado *aplicaOperador(unsigned, tEstado *);

#endif