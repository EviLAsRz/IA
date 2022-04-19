#include "jarras.h"

tEstado *estadoInicial() {
tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
estado->J4=0;
estado->J3=0;
return estado;
} //estadoInicial
int testObjetivo(tEstado *estado){
return(estado->J4==2);
} //testObjetivo

// restricciones para realizar el movimiento
int esValido(unsigned op, tEstado *a){
int valido;
switch(op){
case LLENAR4: valido = a->J4<4; break;
case LLENAR3: valido = a->J3<3; break;
case VACIAR4: valido = a->J4>0; break;
case VACIAR3: valido = a->J3>0; break;
case LLENAR4CON3: valido = (a->J3 > 0 && 4 <= a->J4 + a->J3); break;
case LLENAR3CON4: valido = (a->J4 >= 3 - a->J3 && a->J3 < 3); break;
case VACIAR3EN4: valido = (a->J3 > 0 && a->J3 <= 4 - (a->J4)); break;
case VACIAR4EN3: valido = (a->J4 > 0 && a->J4 <= 3 - (a->J3)); break;
default: valido=0;
break; }

return valido;
} //esValido

tEstado *aplicaOperador(unsigned op, tEstado *a){
tEstado *s = (tEstado *) malloc(sizeof(tEstado));
memcpy(s,a, sizeof(tEstado));
switch(op) {
case LLENAR4: s->J4=4; break;
case LLENAR3: s->J3=3; break;
case VACIAR4: s->J4 = 0; break;
case VACIAR3: s->J3 = 0; break;
case LLENAR4CON3: s->J3 -= s->J4; s->J4 = 4; break;
case LLENAR3CON4: s->J4 -= s->J3; s->J3 = 3; break;
case VACIAR3EN4: s->J4 += s->J3; s->J3 = 0; break;
case VACIAR4EN3: s->J3 += s->J4; s->J4 = 0; break;
default: break;
}
return s;
} //aplicaOperador

void dispEstado(tEstado *a){
printf("\n J4=%d J3=%d\n", a->J4, a->J3);
} //dispEstado
void dispOperador(unsigned op){
switch(op) {
case LLENAR4: printf("\n Llenar4\n"); break;
case LLENAR3: printf("\n Llenar3\n"); break;
case VACIAR4: printf("\n Vaciar4\n"); break;
case VACIAR3: printf("\n Vaciar3\n"); break;
case LLENAR4CON3: printf("\n Llenar4Con3\n"); break;
case LLENAR3CON4: printf("\n Llenar3Con4\n"); break;
case VACIAR3EN4: printf("\n Vaciar4En3\n"); break;
case VACIAR4EN3: printf("\n Vaciar3En4\n"); break;
default: printf("\n No Operador \n"); break;
} //dispOperador
