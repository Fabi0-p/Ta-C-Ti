#include "Lista.h"
#include "main.h"

void crearLista(Lista* p)
{
    *p = NULL;
}

int vaciarLista(Lista* p)
{
    int cant = 0;
    while(*p)
    {
        NodoLista* aux = *p;

        cant++;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
    return cant;
}

int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes)
{
    NodoLista* nuevo;

    // Avanza hasta el final de la lista
    while (*p)
        p = &(*p)->sig;

    nuevo = malloc(sizeof(NodoLista));
    if (!nuevo || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = NULL;
    *p = nuevo;

    return 1;
}

int vaciarListaYMostrar(Lista* p, void (*Mostrar)(const void* elem, FILE* arch), FILE* fp)
{
    int cant = 0;
    while(*p) //Mientras hay nodo
    {
        NodoLista* aux = *p; //"Memoriza" donde est�

        cant++;
        *p = aux->sig;  //Desengancho el nodo

        if(Mostrar && fp) //No falla si no recibe la funcion o el archivo
            Mostrar(aux->info, fp);

        free(aux->info);
        free(aux);
    }
    return cant;
}

int ListaLlena(const Lista* p, unsigned cantBytes)
{
    NodoLista* aux = malloc(sizeof(NodoLista));
    void* info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int listaVacia(const Lista* p)
{
    return *p == NULL;
}

int compararJugadorPorNombre(const void* a, const void* b)
{
    const InfoJugador* j1 = (const InfoJugador*)a;
    const InfoJugador* j2 = (const InfoJugador*)b;
    return strcmp(j1->nombre, j2->nombre);
}

int compararJugadorPorPrioridadRelativa(const void* a, const void* b)
{
    const InfoJugador* j1 = (const InfoJugador*)a;
    const InfoJugador* j2 = (const InfoJugador*)b;
    return j2->prioridadRelativa - j1->prioridadRelativa;
}

int compararJugadorPorPuntajeDesc(const void* a, const void* b) {
    const InfoJugador* j1 = (const InfoJugador*)a;
    const InfoJugador* j2 = (const InfoJugador*)b;
    return j2->puntaje - j1->puntaje; // mayor a menor
}

void ordenarLista(Lista* lista, int(*Comparar)(const void*, const void*)) {
    if (!lista || !*lista || !(*lista)->sig)
        return; // lista vac�a o con un solo elemento

    int ordenado;
    do {
        ordenado = 1;
        NodoLista* actual = *lista;

        while (actual && actual->sig) {
            if (!actual->info || !actual->sig->info)
                break; // evita crash si alg�n info es NULL

            if (Comparar(actual->info, actual->sig->info) > 0) {
                // intercambio seguro de info y tama�os
                void* tempInfo = actual->info;
                unsigned tempTam = actual->tamInfo;

                actual->info = actual->sig->info;
                actual->tamInfo = actual->sig->tamInfo;

                actual->sig->info = tempInfo;
                actual->sig->tamInfo = tempTam;

                ordenado = 0;
            }
            actual = actual->sig;
        }
    } while (!ordenado);
}

int mostrarLista(Lista* Lista, void (*Mostrar)(const void*, FILE*), FILE* fp)
{
    int cant = 0;

    while(*Lista)
    {
        Mostrar((*Lista)->info, fp);
        Lista = &(*Lista)->sig;
        cant++;
    }
    return cant;
}

int recorrerLista(Lista* Lista, void* extraParams, void (*Accion)(void*, void*)){
    int cant = 0;

    while(*Lista)
    {
        Accion((*Lista)->info, extraParams);
        Lista = &(*Lista)->sig;
        cant++;
    }
    return cant;
}

int ponerEnOrden(Lista* lista, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*),
                 int(*Acumular)(void**, unsigned*, const void*, unsigned))
{
    NodoLista* nuevo;

    while(*lista && Comparar((*lista)->info, d) < 0)
        lista = &(*lista)->sig;

    if(*lista && Comparar((*lista)->info, d) == 0)
    {
        if(Acumular)
            if(!Acumular(&(*lista)->info, &(*lista)->tamInfo, d, cantBytes))
                return SIN_MEM;
        return CLA_DUP;
    }

    if((nuevo = malloc(sizeof(NodoLista))) == NULL || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return SIN_MEM;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *lista;
    *lista = nuevo;

    return TODO_OK;
}

int ponerEnOrdenConRepetidos(Lista* lista, const void* d, unsigned cantBytes,
                 int(*Comparar)(const void*, const void*))
{
    NodoLista* nuevo;

    while(*lista && Comparar((*lista)->info, d) < 0)
        lista = &(*lista)->sig;

    if((nuevo = malloc(sizeof(NodoLista))) == NULL || (nuevo->info = malloc(cantBytes)) == NULL)
    {
        free(nuevo);
        return SIN_MEM;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *lista;
    *lista = nuevo;

    return TODO_OK;
}

int existeEnLista(Lista* lista, const void* d, int(*Comparar)(const void*, const void*))
{
    while(*lista && Comparar((*lista)->info, d) != 0)
        lista = &(*lista)->sig;

    if(*lista) return 1;
    return 0;
}




