#include "Lista.h"

#define minimo(x, y)((x) <= (y) ? (x) : (y))

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

int vaciarListaYMostrar(Lista* p, void (*Mostrar)(const void* elem, FILE* arch), FILE* fp)
{
    int cant = 0;
    while(*p) //Mientras hay nodo
    {
        NodoLista* aux = *p; //"Memoriza" donde está

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

int ponerAlComienzo(Lista* p, const void* d, unsigned cantBytes)
{
    NodoLista* nuevo;

    if((nuevo = malloc(sizeof(NodoLista))) == NULL ||
       (nuevo->info = malloc(cantBytes)) ==  NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, d, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *p;
    *p = nuevo;

    return 1;
}

int ponerAlFinal(Lista* p, const void* d, unsigned cantBytes)
{
    NodoLista* nuevo;

    while(*p)
        p = &(*p)->sig;

    if((nuevo = malloc(sizeof(NodoLista))) == NULL ||
       (nuevo->info = malloc(cantBytes)) == NULL)
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




void ordenarLista(Lista* lista, int(*Comparar)(const void*, const void*))
{
    Lista* primero = lista;

    if(*lista == NULL) //Si no hay lista no se puede ordenar
        return;

    while((*lista)->sig) //Mientras haya siguiente...
    {
        if(Comparar((*lista)->info, (*lista)->sig->info) > 0) //Si el actual es mayor que el siguiente...
        {
            Lista* q = primero; //Prepara para comenzar desde el inicio de la lista
            NodoLista* aux = (*lista)->sig; //Toma la direccion del nodo

            (*lista)->sig = aux->sig; //Desvincula el nodo de la lista
            while(Comparar((*q)->info, aux->info) > 0) //Avanza buscando el lugar de insercion
                q = &(*q)->sig;
            aux->sig = *q;
            *q = aux; //Vincula el nodo en la lista
        }
        else
            lista = &(*lista)->sig;
    }
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




