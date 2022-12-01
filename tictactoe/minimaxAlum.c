/*******************************************/
/* 		    minimaxAlum.c                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tictactoe.h"
#include "minimaxAlum.h"
#define MAX 1
#define MIN -1
#define LIMITE 100

int min(int a, int b) {
      if (a < b) return a;
      else return b; 
}

int max(int a, int b) {
      if (a > b) return a;
      else return b;
}

tNodo *PSEUDOminimax(tNodo *t) {
      int mejorJugada = -1;
      int puntos = -2;
      int i, temp;
      tNodo *intento=malloc(sizeof(tNodo));
      printf("\n Mi turno: \n");
      for(i = 0; i < 9; ++i){
      if (esValida(t,i)) {
            intento=aplicaJugada(t,1,i); //Intenta jugada
            temp =terminal(intento); // Calcula el valor minimax
            if(temp > puntos) {
            puntos = temp;
            mejorJugada = i;
            }
      }}//for
      t=aplicaJugada(t,1,mejorJugada);
      return t;
}

tNodo *jugadaAdversario(tNodo *t) {
      int jugada = 0;
      printf("\nJugada ([0..8])?: ");
      scanf("%d", &jugada);
      while (!esValida(t,jugada))
      {
            printf("\n Intenta otra posicion del tablero \n");
            printf("\n");
            printf("\nJugada ([0..8])?: ");
            scanf("%d", &jugada);
      }
      t=aplicaJugada(t,-1,jugada);
      return t;
}

int valorMin(tNodo *t) {
      
      int valor_min, jugada, jugador = -1;
      if(terminal(t) || t->vacias == 0) valor_min = terminal(t);
      else valor_min = 100000;
      for(jugada = 0; jugada < N; jugada++) {
            if (esValida(t, jugada))
                  valor_min = min(valor_min, valorMax(aplicaJugada(t, jugador, jugada)));
      }
      return valor_min;
}

int valorMax(tNodo *t) {

      int valor_max, jugada, jugador = 1;
      if(terminal(t) || t->vacias == 0) valor_max = terminal(t);
      else valor_max = -100000;
      for(jugada = 0; jugada < N; jugada++) {
            if (esValida(t, jugada))
                  valor_max = max(valor_max, valorMin(aplicaJugada(t, jugador, jugada)));
      }
      return valor_max;
}

tNodo *minimax(tNodo* t, int jugador) {

      int max, max_actual, jugada, mejorJugada;
      tNodo *intento;
      max = -10000;

      for(jugada=0; jugada < N; jugada++) {
            if (esValida(t, jugada)) {
                  intento = aplicaJugada(t, jugador, jugada);
                  max_actual = valorMin(intento);
                  if (max_actual > max) {
                        max = max_actual;
                        mejorJugada = jugada;
                  }
            }
      }
      t = aplicaJugada(t, jugador, mejorJugada);
}

/*
tNodo *poda_ab(tNodo *t) {
      int max_Actual, jugada = 0, mejorjugada, prof = 0, v;
      tNodo* intento;
      int alfa = -1000000;
      int beta = 1000000;
      while( jugada <=N) {
            if (esValida(t, jugada)) {
                  intento = aplicaJugada(t, MAX, jugada);
                  v = valorMin_ab(intento, prof+1, alfa, beta);
                  if (v > alfa) {
                        alfa = v;
                        mejorjugada = jugada;
                  }
            }
      }
      if (esValida(t, jugada))
            t = aplicaJugada(t, MAX, mejorjugada);
      
      return t;
}
*/
