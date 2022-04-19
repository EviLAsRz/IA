/*******************************************/
/*             MAIN.C                      */
/*                                         */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"

int main(){

    int op,limite,iterativo;
    do{
    puts("");
    puts("Seleccione el tipo de busqueda:");
    puts("1-.Busqueda por anchura.");
    puts("2-.Busqueda por anchura con control de estados repetidos.");
    puts("3-.Busqueda por profundidad.");
    puts("4-.Busqueda por profundidad limitada.");
    puts("5-.Busqueda por profundidad limitada iterativa.");
    puts("6-.Busqueda Voraz.");
    puts("7-.Busqueda A.");
    printf("opcion: ");
    scanf("%d",&op);
    switch(op){
        case 1: solucionFin(busqueda());break;
        case 2: solucionFin(busquedaAnchuraRep());break;
        case 3: solucionFin(busquedaProfundidad());break;
        case 4:
        printf("Introduce el limite de expansion de la busqueda: ");
        scanf("%d",&limite);
        solucionFin(busquedaProfundidadLimitada(limite));break;
        case 5: 
        printf("Introduce el limite de expansion de la busqueda y la iteración: ");
        scanf("%d,%d",&limite,&iterativo);
        solucionFin(busquedaProfundidadLimitadaIter(limite,iterativo));break;
        default: puts("Busqueda invalida.");
    }
}while (op > 0 || op < 8);
    return 0;
}
