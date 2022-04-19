/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include "puzle.h"

tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=puzle[i][j];
         estado->celdas[i][j]=ficha;
         estado->fila[ficha]=i;
         estado->col[ficha]=j;
      }
   return estado;
}

tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACION DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Funcion auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
    int i,j,iguales = 1;
/*Opción 1: Dos puzles son iguales si el contenido del tablero(celdas) es el mismo*/
    for(i=0;i<N && iguales;i++)
    {
        for(j=0;j<N && iguales;j++)
        {
            iguales &= (s->celdas[i][j]==t->celdas[i][j]);
            //iguales= iguales & 1 -> iguales= 1 & 1 -> iguales=1
            //iguales= iguales & 0 -> iguales= 1 & 0 -> iguales=0
        }
    }
/* Opción 2: Dos puzles son iguales si sus fichas ocupan la misma posición, es decir, misma fila y columna
    
 for(i=0; i<N*N && iguales; i++)
 {
    iguales &= (s->fila[i] == t->fila[i] && s->col[i] == t->col[i]);
 }
 */
return iguales;
}


int testObjetivo(tEstado *estado)
{
int i,j,res=1;
    for(i=0;i<N && res;i++)
    {
        for(j=0;j<N && res;j++)
        {
            res &= (estado->celdas[i][j] == puzle_final[i][j]);
        }
    }
    return res;
    //return iguales(estado,estadoObjetivo()); //usando la funcion iguales
}


int esValido(unsigned op, tEstado *estado)
{
    int valido = 0;
    switch (op){

        case ARRIBA: valido = (estado->fila[0] > 0); break;
        case ABAJO: valido = (estado->fila[0] < N - 1); break;
        case IZQUIERDA: valido = (estado->col[0] > 0); break;
        case DERECHA: valido = (estado->col[0] < N - 1); break;
        default: break;
    }

    return valido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
     tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
    int ficha;

    switch (op){

       case ARRIBA:
         ficha = estado->celdas[estado->fila[0]-1][estado->col[0]];
         nuevo->fila[0]--;
         nuevo->fila[ficha]++; break;

      case ABAJO:
         ficha = estado->celdas[estado->fila[0]+1][estado->col[0]];
         nuevo->fila[0]++;
         nuevo->fila[ficha]--; break;

      case IZQUIERDA:
         ficha = estado->celdas[estado->fila[0]][estado->col[0]-1];
         nuevo->col[0]--;
         nuevo->col[ficha]++; break;

      case DERECHA:
         ficha = estado->celdas[estado->fila[0]][estado->col[0]+1];
         nuevo->col[0]++;
         nuevo->col[ficha]--; break;
      
      default: printf("Movimiento invalido.\n");
    }

   nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = 0;
   nuevo->celdas[nuevo->fila[ficha]][nuevo->col[ficha]] = ficha;
return nuevo;
}

int valor_heuristico_p(tEstado *a, tEstado *objetivo){
   int i,j,b = 0;
   for(i = 0;i<N;i++)
      for(j = 0;j<N;j++){
         if(a->celdas[i][j] != objetivo->celdas[i][j])
         b++;
      }
   return b;
}


