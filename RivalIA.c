#ifndef RIVAL_IA_C
#define RIVAL_IA_C

#include <stdlib.h>
#include "RivalIA.h"
#include "Juego.h"

int IAbuscarJugada(t_linea tabLinea[8], t_tablero tablero, enum t_jugador jug, int *lineaAJugar){
    int resTablero = 0, resLineaActual;
    for(int i = 0; i < 8; i++){
        resLineaActual = evalLinea(tabLinea[i], tablero);
        if(tableroCompararEstados(resTablero, resLineaActual, jug)){
            resTablero = resLineaActual;
            *lineaAJugar = i;
        }
    }
    return resTablero;
}

void jugarPrimerOpLinea(t_linea linea, t_tablero tab, enum t_jugador jug){
    for(int i = 0; i < 3; i++){
        if(tab[linea[i]] == J_VACIO){
            jugarFicha(tab, jug, linea[i]);
        }
    }
}

void IAjugarTurno(t_linea tabLinea[8], t_tablero tablero, enum t_jugador jug){
    int lineaAJugar, resTablero;
    resTablero = IAbuscarJugada(tabLinea, tablero, jug, &lineaAJugar);
    if(abs(resTablero) == 2)
        jugarPrimerOpLinea(tabLinea[lineaAJugar], tablero, jug);
    else
        jugarCasillaAzar(tablero, jug);

}

void jugarCasillaAzar(t_tablero tab, enum t_jugador jug){
    int jugado = 0, i = 0, empatado = 1;
    while(i < 8 && empatado){
        if(tab[i] == 0)
            empatado = 0;
        i++;
    }
    // Esto no debería ocurrir nunca, pero lo agrego para que si el programa se rompe no sea por un bucle infinito (sería muy molesto)
    if(empatado) 
        return;
    while(!jugado){
        int casilla = rand() % 8;
        if(tab[casilla] == J_VACIO){
            jugarFicha(tab, jug, casilla);
            jugado = 1;
        }
    }
}

#endif
