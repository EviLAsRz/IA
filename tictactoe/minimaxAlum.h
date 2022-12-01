/*******************************************/
/* 		    minimaxAlum.h                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

tNodo *jugadaAdversario(tNodo *t);
tNodo *PSEUDOminimax(tNodo *Nodo);
int valorMax(tNodo*);
int valorMin(tNodo*);
tNodo *minimax(tNodo*, int);
tNodo *poda_ab(tNodo *);
int min(int, int);
int max (int, int);
