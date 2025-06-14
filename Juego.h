#ifndef JUEGO_H
#define JUEGO_H

#include "main.h"
#include <time.h>
void initTablaLineas(t_linea tab[8]);
void limpiarTablero(t_tablero tab);
int evalLinea(t_linea linea, t_tablero tablero);
int evalTablero(t_linea tabLinea[8], t_tablero tablero, enum t_jugador *ganador);
int evalTableroConGuias(t_linea tabLinea[8], t_tablero tablero, enum t_jugador *ganador);
int jugarFicha(t_tablero tab, enum t_jugador jug, short int casilla);
void turnoJugador(t_tablero tab, enum t_jugador jug, char* nombreJug);
int tableroCompararEstados(int evalActual, int evalCandidato, enum t_jugador jug);
void mostrarTablero(t_tablero tab);
void asignarFichas(enum t_jugador *jugH, enum t_jugador *IA);
int partida(char *nombreJug, void (jugadaIA)(t_linea[8], t_tablero, enum t_jugador));

#endif
