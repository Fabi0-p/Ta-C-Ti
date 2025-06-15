#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include"cola.h"

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
    int prioridadRelativa;
} InfoJugador;

typedef struct{
    int partidasPorJugador;
    Cola colaInfo;
}ProcesarJugadorExtraParams;

typedef enum t_jugador t_tablero[9]; 
typedef short int t_linea[3]; 

void iniciarJuego();
void verRanking();
void cargarConfig();
void procesarJugador(void* elem, void* extraParams);
void mostrarJugador(const void* dato, FILE* fp);

#endif
