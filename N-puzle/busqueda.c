/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"

void solucionFin(int res){
    printf("\nFin de la busqueda\n");
    if (res)
        printf("Se ha llegado al objetivo\n");
    else
        printf("No se ha llegado al objetivo\n");
}
void dispNodo(tNodo *nodo){
    dispEstado(nodo->estado);
    printf("\n");
}
void dispCamino(tNodo *nodo){
    if (nodo->padre==NULL){
        printf("\n Desde el inicio\n");
        dispEstado(nodo->estado);
    }
    else {
        dispCamino(nodo->padre);
        dispOperador(nodo->operador);
        dispEstado(nodo->estado);
    }
}

void dispSolucion(tNodo *nodo){
    printf("Profundidad=%d\n",nodo->profundidad);
    printf("Coste=%d\n",nodo->costeCamino);
    dispCamino(nodo);
}


/* Crea el nodo raiz. */
tNodo *nodoInicial(){
    tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
    inicial->estado=estadoInicial();
    inicial->padre=NULL;
    inicial->costeCamino=0;
    inicial->profundidad=0;
    return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){
        if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
            s=aplicaOperador(op,nodo->estado);
            nuevo->estado=s;
            nuevo->padre=nodo;
            nuevo->operador=op;
            nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
            nuevo->profundidad=nodo->profundidad+1;
            nuevo->valHeuristica = valor_heuristico_p(nuevo->estado,estadoObjetivo());
            InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
        }
    }
    return sucesores;
}

int busqueda(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            visitados++;
            Abiertos=Concatenar(Abiertos,Sucesores);
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}
/*busqueda por anchura con control de estado repetido*/
int busquedaAnchuraRep(){
    
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    //implementado a parte
    LISTA Cerrados = VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        //dispOperador(Actual->operador);
        //dispEstado(Actual->estado);
        
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
        //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            visitados++;
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            Abiertos=Concatenar(Abiertos,Sucesores);
        }

    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}
/*Busqueda por profundidad sin control de estados repetidos*/
int busquedaProfundidad(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        dispOperador(Actual->operador);
        dispEstado(Actual->estado);
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
            //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            visitados++;
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/*Busqueda por profundidad con limite*/

int busquedaProfundidadLimitada(int limite){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados = VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo && (limite >0)){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        dispOperador(Actual->operador);
        dispEstado(Actual->estado);
        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
            //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            visitados++;
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
            limite--;
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProfundidadLimitadaIter(int limite, int iterativo){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados = VACIA;

    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo ){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        
        objetivo=testObjetivo(Actual->estado);
        dispOperador(Actual->operador);
        dispEstado(Actual->estado);

        if(!objetivo&&estado_repetido(Cerrados,Actual)==0){
            //si no esta repetido entonces expande
            Sucesores = expandir(Actual);
            InsertarUltimo(&Cerrados,Actual,sizeof(tNodo));
            Abiertos = Concatenar(Sucesores,Abiertos);//profundidad
            limite--;

            if(limite == 0){
                limite = iterativo;
            }
            visitados++;
        }


    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/*Busqueda voraz*/

int busqueda_voraz(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;

    InsertarPrimero(&Abiertos, Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo && estado_repetido(Cerrados,Actual)==0){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        dispOperador(Actual->operador);
        dispEstado(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Ordenar_Abiertos_Voraz(Abiertos,Sucesores);
            visitados++;
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/*ordenacion voraz de la lista abiertos*/

LISTA Ordenar_Abiertos_Voraz(LISTA A, LISTA S){

    tNodo *nodo=calloc(1,sizeof(tNodo));

    while(S != NULL){

        ExtraerPrimero(S,nodo, sizeof(tNodo));
        A = ordenacion_voraz(S,nodo);
        S = S->next;
    }
    return A;
}

LISTA ordenacion_voraz(LISTA L, tNodo* nuevo){

    LISTA aux = NULL;
    tNodo *nodo = calloc(1,sizeof(tNodo));

    if(esVacia(L)){

        InsertarPrimero(&L,nuevo,sizeof(tNodo));
    }
    else{

        ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
        while(!(esVacia(L)) && ((nodo->valHeuristica) < ( nuevo->valHeuristica))){

            InsertarUltimo(&aux,(tNodo *)nodo,sizeof(tNodo));
            L = L->next; 
            if(!(esVacia(L))){

                ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
            }
        }
        InsertarUltimo(&aux,(tNodo *)nuevo,sizeof(tNodo));
        aux= Concatenar(aux,L);
    }

    return aux;
}

/*Busqueda A*/

int busqueda_A(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;

    InsertarPrimero(&Abiertos, Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo && estado_repetido(Cerrados,Actual)==0){

        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);

        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Ordenar_Abiertos_A(Abiertos,Sucesores);
            visitados++;
        }
    }//while

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

/*Funcion para determinar si el estado es repetido*/

int estado_repetido(LISTA cerrados, tNodo* nodo)
{
    int res=0;
    tNodo * aux= (tNodo*) calloc (1,sizeof(tNodo));
    LISTA actual = cerrados;
    
    while(!esVacia(actual) && !res)
    {
        ExtraerPrimero(actual,aux,sizeof(tNodo));
        if(iguales(aux->estado, nodo->estado))
        {
            res=1;
        }
        else
        {
            //siguiente(&actual, &actual);
            actual = actual->next;
        }
    }
    return res;
}

LISTA Ordenar_Abiertos_A(LISTA A, LISTA S){

    tNodo *nodo=calloc(1,sizeof(tNodo));

    while(S != NULL){

        ExtraerPrimero(S,nodo, sizeof(tNodo));
        A = ordenacion_A(S,nodo);
        S = S->next;
    }
    return A;
}

LISTA ordenacion_A(LISTA L, tNodo* nuevo){

    LISTA aux = NULL;
    tNodo *nodo = calloc(1,sizeof(tNodo));

    if(esVacia(L)){

        InsertarPrimero(&L,nuevo,sizeof(tNodo));
    }
    else{

        ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
        while(!(esVacia(L)) && ((nodo->valHeuristica + nodo->costeCamino) < ( nuevo->valHeuristica + nuevo->costeCamino ))){

            InsertarUltimo(&aux,(tNodo *)nodo,sizeof(tNodo));
            L = L->next; 
            if(!(esVacia(L))){

                ExtraerPrimero(L,(tNodo *)nodo,sizeof(tNodo));
            }
        }
        InsertarUltimo(&aux,(tNodo *)nuevo,sizeof(tNodo));
        aux= Concatenar(aux,L);
    }

    return aux;
}
