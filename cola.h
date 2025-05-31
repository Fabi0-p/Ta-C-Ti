#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#define minimo(X,Y) (( (X) > (Y) ) ? (X) : (Y) )
typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
}Nodo;

typedef struct
{
    Nodo* pri;
    Nodo* ult;
}Cola;

// Firmas de Cola

void crearCola(Cola*);
int ponerEnCola(Cola*, const void*, unsigned);
int sacarDeCola(Cola*, void* dato, unsigned);
void vaciarCola(Cola*);
int verPrimeroCola(const Cola*, void*, unsigned);
int colaVacia(const Cola*);
int colaLlena(const Cola*, unsigned);



#endif // COLA_H_INCLUDED
