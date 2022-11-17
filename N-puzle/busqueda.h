/*******************************************/
/* 		    BUSQUEDA.H                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#ifndef _tNodo_
#define _tNodo_
typedef struct NodoBusqueda_{
    tEstado *estado;
    unsigned operador;
    int costeCamino;
    int profundidad;
    int valHeuristica;
    struct NodoBusqueda_ *padre;
} tNodo;

#endif

int busqueda(void);
void solucionFin(int res);
int busquedaAnchuraRep(void);
int busquedaProfundidad(void);
int busquedaProfundidadLimitada(int);
int busquedaProfundidadLimitadaIter(int,int);
int busqueda_voraz(void);
int busqueda_A(void);
int estado_repetido(LISTA, tNodo *);
LISTA Ordenar_Abiertos_Voraz(LISTA, LISTA);
LISTA Ordenar_Abiertos_A(LISTA, LISTA);
LISTA ordenacion_A(LISTA, tNodo *);
LISTA ordenacion_voraz(LISTA, tNodo *);
