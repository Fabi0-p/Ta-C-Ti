#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIN_MEM  1
#define CLA_DUP  2
#define TODO_OK  0

// Estructura de nodo para lista genérica
typedef struct nodoLista {
    void* info;
    unsigned tamInfo;
    struct nodoLista* sig;
} NodoLista;

typedef NodoLista* Lista;

// Funciones básicas
void crearLista(Lista* p);
int vaciarLista(Lista* p);


int listaLlena(const Lista* p, unsigned cantBytes);
int listaVacia(const Lista* p);

// Inserción
int ponerAlComienzo(Lista* p, const void* d, unsigned cantBytes);
int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes);

// Ordenamiento
void ordenarLista(Lista* p, int(*Comparar)(const void*, const void*));
int ponerEnOrden(Lista* lista, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*),
                 int(*Acumular)(void**, unsigned*, const void*, unsigned));

// Función auxiliar que el ranking exporta para acceder a la lista
Lista* obtenerListaRanking();

#endif // LISTA_H_INCLUDED

