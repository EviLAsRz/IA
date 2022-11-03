#ifndef _3PUZLE_H_
#define _3PUZLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 6
//Entorno
#define VACIO 0
#define OBSTACULO -1
//movimientos pieza A
#define ARRIBA_A 1
#define ABAJO_A 2
#define IZQUIERDA_A 3
#define DERECHA_A 4
//Movimientos pieza B
#define ARRIBA_B 5
#define ABAJO_B 6
#define IZQUIERDA_B 7
#define DERECHA_B 8
//Movimientos pieza C
#define ARRIBA_C 9
#define ABAJO_C 10
#define IZQUIERDA_C 11
#define DERECHA_C 12
//num de operadores
#define NUM_OPERADORES 12
#define nf 3


#ifndef _T_ESTADO_
#define _T_ESTADO_

typedef struct tEstado {
    int tablero[N][N];
    int filas[nf + 1];
    int columnas[nf + 1];
}tEstado;

#endif

static int tablero_inicial[N][N]=
{
    {-1,0,0,3,0,0},
    {-1,0,0,3,0,0},
    {0,1,0,3,0,0},
    {1,1,1,-1,2,0},
    {0,1,0,2,2,2},
    {0,0,0,0,0,0}
};

static int tablero_final[N][N]=
{
    {-1,0,0,0,0,0},
    {-1,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,1,0,-1,0,3},
    {1,1,1,2,0,3},
    {0,1,2,2,2,3}
};

static int filas_inicial[nf+1]={0,4,2,5};
static int cols_inicial[nf+1]={0,2,5,4};
static int filas_final[nf+1]={0,5,6,5};
static int cols_final[nf+1]={0,2,4,6};

tEstado *crearEstado(int celdas[N][N], int filas[nf+1], int cols[nf+1]);
int testObjetivo(tEstado *);
int esValido(unsigned, tEstado *);
tEstado *aplicaOperador(unsigned, tEstado *);

#endif 


