#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include "lista.h"
#include "jugadores.h"

void inicializarRanking();
void actualizarPuntaje(const Jugador* j, int puntos);
void verRanking();
void generarInformeTXT();
int acumularPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo);


#endif // RANKING_H_INCLUDED
