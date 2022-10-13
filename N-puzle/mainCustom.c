//
//  main.c
//  PuzleAlum
//
//  Created by elisa on 13/10/21.
//  Copyright © 2021 elisa. All rights reserved.
//

#include <stdio.h>
#include "puzle.h"

int main(int argc, const char * argv[]) {

    int estado_inicial[N][N]={1,7,3,6,0,4,8,5,2}, estado_final[N][N]={1,2,3,8,0,4,7,6,5}, op;
    tEstado *t = crearEstado(estado_inicial);
    printf("EstadoActual: \n"); dispEstado(t);
    do{
        printf("Selecciona una operación:");
        scanf("%i",&op);

        if (esValido(op,t) == 1)
        {
        t = aplicaOperador(op,t);
        dispOperador(op);
        dispEstado(t);
        }
    }while (testObjetivo(t) == 0);
    
    printf("Estado Final: \n");
    dispEstado(t);

    return 0;
}
