#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include "lista.h"
#include "main.h"
void inicializarRanking();
void actualizarPuntaje(const InfoJugador* j, int puntos);
void verRanking();
void generarInformeTXT(Cola *p, Lista *mejoresPuntajes, Config *conf);
void imprimirTableroTXT(t_tablero,FILE *);
void imprimirRankingTXT(Lista *,FILE *);
void imprimirJugadorTXT(void* elem, void* extraParams);
int acumularPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo);
int reemplazarPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo);

#endif // RANKING_H_INCLUDED
