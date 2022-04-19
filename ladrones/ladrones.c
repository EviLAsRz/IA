#include "ladrones.h"

tEstado *crearEstado(int cinta[N])
{

    tEstado *e = malloc(sizeof(tEstado));
    for(int i = 0; i< N; i++)
    {
        e->cinta[i] = cinta[i];
    }
    e->ladoizq = 0;
    e->ladoder = 0;
    e->robado = 0;
    e->recuperado = 0;

    return e;
}

int esValido(unsigned op, tEstado *e)
{
    int valido = 0;
    if(op == DER || op == IZQ)
    {
        if(N%2 == 0)
        {
            valido = (e->ladoizq < e->ladoder);
        }
    }else
        {
        valido = (e->ladoizq < e->ladoder-1);
        }
return valido;
}

tEstado *aplicaOperador(unsigned op, tEstado *e)
{
    tEstado *nuevo = malloc (sizeof(tEstado));
    memcpy(nuevo,e,sizeof(tEstado));
    switch(op)
    {
    case IZQ: nuevo->ladoizq++; nuevo->ladoder--;
        nuevo->robado += nuevo->cinta[e->ladoizq]; nuevo->recuperado += nuevo->cinta[e->ladoder];
        break;
    
    case DER: nuevo->ladoder-= 2;
        nuevo->robado += nuevo->cinta[e->ladoder]; nuevo->recuperado += nuevo->cinta[e->ladoder-1];

    default:
        break;
    }
return nuevo;
}

int testObjetivo(tEstado *e)
{
    int objetivo = 0;
    if(N%2 == 0)
    {
        objetivo = ((e->ladoizq > e->ladoder) && (e->robado > e->recuperado));
    }else
    {
        objetivo = ((e->ladoizq == e->ladoder) && (e->robado > e->recuperado));
    }
return objetivo;
}

