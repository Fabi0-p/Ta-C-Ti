#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include"cola.h"
#include"lista.h"

#define MAX_URL 200
#define MAX_PASSW 30
#define ARCH_CONFIG "config.txt"
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

typedef struct {
    InfoJugador j;
    t_tablero tablero;
    int puntajePartida;
    int numeroPartida;
}InfoPartida;

typedef struct {
    char url[MAX_URL];
    char passw[MAX_PASSW];
    int cantPartidas;
}Config;

void iniciarJuego(Config *c);
void verRanking(Config *c);
int cargarConfig(Config *c);
void procesarJugador(void* elem, void* extraParams);
void mostrarJugador(const void* dato, FILE* fp);
void agregarJugadores(Lista *listaJugadores, int num);

#endif
