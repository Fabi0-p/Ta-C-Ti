#ifndef MAIN_H
#define MAIN_H

#define EST_EN_CURSO 0
#define EST_EMPATE 1
#define EST_GANADO 2

enum t_jugador{
    J_X = -1,
    J_VACIO = 0,
    J_O = 1
};

typedef struct {
    char nombre[50];
    int puntaje;
    int partidasJugadas;
    int partidasRestantes;
} InfoJugador;

typedef enum t_jugador t_tablero[9]; 
typedef short int t_linea[3]; 

void iniciarJuego();
void verRanking();
void cargarConfig();

#endif
