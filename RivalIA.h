#ifndef RIVAL_IA_H
#define RIVAL_IA_H

#include"main.h"
#include"Juego.h"

int IAbuscarJugada(t_linea tabLinea[8], t_tablero tablero, enum t_jugador jug, int *lineaAJugar);
void jugarPrimerOpLinea(t_linea linea, t_tablero tab, enum t_jugador jug);
void IAjugarTurno(t_linea tabLinea[8], t_tablero tablero, enum t_jugador jug);
void jugarCasillaAzar(t_tablero tab, enum t_jugador jug);

#endif
