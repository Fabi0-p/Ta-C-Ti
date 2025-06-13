#include "cola.h"

void crearCola(Cola* p)
{
    p->pri = NULL;
    p->ult = NULL;
}

int colaLlena(const Cola* p, unsigned tamDato)
{
    Nodo* aux = malloc(sizeof(Nodo));
    void* info = malloc(tamDato);
    free(aux);
    free(info);
    return aux ==NULL || info==NULL;
}

int ponerEnCola(Cola* p,const void* dato, unsigned tamDato)
{
    Nodo* nue = malloc(sizeof(Nodo));

    if(nue==NULL || (nue->info = malloc(tamDato))== NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,dato,tamDato);
    nue->tamInfo = tamDato;
    nue->sig = NULL;
    if(p->ult)
        p->ult->sig = nue;
    else
        p->pri = nue;
    p->ult = nue;
    return 1;
}

int verPrimeroCola(const Cola* p, void* dato, unsigned tamDato)
{
    if(p->pri == NULL)
        return 0;
    memcpy(dato,p->pri, minimo(tamDato, p->pri->tamInfo));
    return 1;
}

int colaVacia(const Cola* p)
{
    return p->pri == NULL;
}

int sacarDeCola(Cola* p, void* dato, unsigned tamDato)
{
    Nodo* aux = p->pri;
    if(aux == NULL)
        return 0;
    p->pri = aux->sig;
    memcpy(dato, aux->info, minimo(aux->tamInfo, tamDato));
    free(aux->info);
    free(aux);
    if(p->pri == NULL)
        p->ult =NULL;
    return 1;
}

void vaciarCola(Cola* p)
{
    while(p->pri)
    {
        Nodo* aux = p->pri;
        p->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->ult = NULL;
}



