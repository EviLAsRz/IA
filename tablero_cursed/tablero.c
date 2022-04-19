#include "tablero.h"

int testObjetivo(tEstado *a, tEstado *obj)
{
    /*Se compara si el elemento central de cada pieza está en la misma posición que objetivo*/
    return((a->filas[1] == obj->filas[1] && a->cols[1] == obj->cols[1])
        &&(a->filas[2] == obj->filas[2] && a->cols[2] == obj->cols[2])
        &&(a->filas[3] == obj->filas[3] && a->cols[3] == obj->cols[3]));
}

int esValido(unsigned op, tEstado *e){
    int valido = 0;

    switch(op){
        case ARRIBA_A:
            valido = ((e->filas[1] > 1) && (e->tablero[e->filas[1]-2][e->cols[1]] == 0)
            && (e->tablero[e->filas[1]-1][e->cols[1]-1] == 0)
            && (e->tablero[e->filas[1]-1][e->cols[1]+1] == 0) );
            break;
        case ABAJO_A:
        
    }
}