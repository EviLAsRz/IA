#include "3puzle.h"

tEstado *crearEstado(int celdas[N][N], int filas[nf+1], int cols[nf+1]){

    tEstado *estado =(tEstado *)malloc(sizeof(tEstado));
    int i,j,k;

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            estado->tablero[i][j] = celdas[i][j];

    for(k=1;i<nf+1;k++){

        estado->filas[k] = filas[k];
        estado->columnas[k] = cols[k];
    }
    return estado;
}

int testObjetivo(tEstado *e){

    int i,bool = 1;
    tEstado *final = crearEstado(tablero_final, filas_final, cols_final);

    for(i=1;i<nf+1;i++){
            if(e->filas[i] != final->filas[i])
                bool = 0;
        }
    return bool;
};

int esValido(unsigned op,tEstado *e){

    int valido = 0;

    switch (op){

        case ABAJO_A:
            valido = (e->filas[1]<N )&& (e->tablero[e->filas[1]+2][e->columnas[1]] == 0)&&
            (e->tablero[e->filas[1]+1][e->columnas[1]-1] == 0)&&
            (e->tablero[e->filas[1]+1][e->columnas[1]+1] == 0);
        
        case ABAJO_B:
    };
}

