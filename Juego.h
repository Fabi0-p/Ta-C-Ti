#ifndef JUEGO_H
#define JUEGO_H

#define EST_EN_CURSO 0
#define EST_EMPATE 1
#define EST_GANADO 2


enum t_jugador{
    J_X = -1,
    J_VACIO = 0,
    J_O = 1
};

typedef enum t_jugador t_tablero[9]; 
typedef short int t_linea[3]; 

void initTablaLineas(t_linea tab[8]);
void limpiarTablero(t_tablero tab);
int evalLinea(t_linea linea, t_tablero tablero);
int evalTablero(t_linea tabLinea[8], t_tablero tablero, enum t_jugador *ganador);
int jugarFicha(t_tablero tab, enum t_jugador jug, short int casilla);
void turnoJugador(t_tablero tab, enum t_jugador jug);
int tableroCompararEstados(int evalActual, int evalCandidato, enum t_jugador jug);
void mostrarTablero(t_tablero tab);
void procesarPartida();

#endif