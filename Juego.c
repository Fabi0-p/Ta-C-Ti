#ifndef JUEGO_C
#define JUEGO_C

#include <stdio.h>
#include <stdlib.h>
#include "secundarias.h"
#include "Juego.h"

void initTablaLineas(t_linea tab[8]){
    int count = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tab[j][i] = count;
            count++;
        }
    }
    count = 0;
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 3; j++){
            tab[i][j] = count;
            count++;
        }
    }
    tab[6][0] = 0;
    tab[6][1] = 4;
    tab[6][2] = 8;
    tab[7][0] = 2;
    tab[7][1] = 4;
    tab[7][2] = 6;
}

int evalLinea(t_linea linea, t_tablero tablero){
    return tablero[linea[0]] + tablero[linea[1]] + tablero[linea[2]];
}

int tableroCompararEstados(int evalActual, int evalCandidato, enum t_jugador jug){
    // Al evaluar las líneas del tablero, hay cierta prioridad que nos interesa. No nos importa que una línea tenga una sola ficha si hay otra línea que ya sabemos que está ganada.
    // Definimos un orden de 4 prioridades, esta función retorna 1 si la evaluación candidata tiene prioridad sobre la de mayor prioridad actual.
    // Llamamos "evaluación" a la suma de los 3 casilleros de una línea, considerando que una O vale 1, X vale -1, y un casillero vacío 0.

    // Prioridad 1: El módulo de la evaluación es 3.
    if(abs(evalCandidato) == 3)
        return 1;
    if(abs(evalActual) == 3)
        return 0;

    // Prioridad 2: El módulo de la evaluación es 2, y el jugador y la evaluación tienen el mismo signo (su producto es positivo)
    if(abs(evalCandidato) == 2 && evalCandidato * jug > 0)
        return 1;
    if(abs(evalActual) == 2 && evalActual * jug > 0)
        return 0;

    // Prioridad 3: El módulo de la evaluación es 2, y el jugador y la evaluación tienen el diferente signo
    if(abs(evalCandidato) == 2)
        return 1;
    if(abs(evalActual) == 2)
        return 0;

    // Prioridad 4: Si llegamos acá pisamos siempre
    return 1;
}

int evalTablero(t_linea tabLinea[8], t_tablero tablero, enum t_jugador *ganador){
    int resTablero = 0, resLineaActual, empatado = 1, i;
    for(i = 0; i < 8; i++){
        resLineaActual = evalLinea(tabLinea[i], tablero);
        // Mandamos jugador cero porque solo nos interesa saber si el tablero está ganado o no, así que el jugador no pincha ni corta.
        if(tableroCompararEstados(resTablero, resLineaActual, 0)){
            resTablero = resLineaActual;
        }
    }
    if(abs(resTablero) == 3){
        *ganador = resTablero / 3; // Al dividir por 3 nos queda 1 del signo del jugador, así que va a ser o J_O o J_X
        return EST_GANADO;
    }
    i = 0;
    while(i < 9 && empatado){
        if(tablero[i] == J_VACIO)
            empatado = 0;
        i++;
    }
    if(empatado)
        return EST_EMPATE;

    return EST_EN_CURSO;
}

void mostrarTablero(t_tablero tab){
    printf("\n+-+-+-+");
    for(int i = 0; i < 3; i++){
        printf("\n|");
        for(int j = 0; j < 3; j++){
            char ficha = ' ';
            if(tab[j+i*3] == J_O)
                ficha = 'O';
            if(tab[j+i*3] == J_X)
                ficha = 'X';
            printf("%c|", ficha);
        }
        printf("\n+-+-+-+");
    }
}

void mostrarTableroConGuias(t_tablero tab){
    int count = 1;
    printf("\n+-+-+-+   +-+-+-+");
    for(int i = 0; i < 3; i++){
        printf("\n|");
        for(int j = 0; j < 3; j++){
            char ficha = ' ';
            if(tab[j+i*3] == J_O)
                ficha = 'O';
            if(tab[j+i*3] == J_X)
                ficha = 'X';
            printf("%c|", ficha);
        }
        printf("   |");
        for(int j = 0; j < 3; j++){
            printf("%d|", count++);
        }
        printf("\n+-+-+-+   +-+-+-+");
    }
}

void procesarPartida(){

}

void limpiarTablero(t_tablero tablero){
    for(int i = 0; i < 9; i++)
        tablero[i] = J_VACIO;
}

void turnoJugador(t_tablero tab, enum t_jugador jug, char* nombreJug){
    int casilleroElegido = -1, fichaColocada = 0;
    while(!fichaColocada){
        limpiarPantalla();
        printf("\nTurno de %s\n", nombreJug);
        mostrarTableroConGuias(tab);
        printf("\nSeleccione un casillero: ");
        scanf("%d", &casilleroElegido);
        casilleroElegido--;
        if(casilleroElegido >= 0 && casilleroElegido <= 8){
            if(tab[casilleroElegido] == J_VACIO){
                jugarFicha(tab, jug, casilleroElegido);
                fichaColocada = 1;
            }
        }
    }
}

int jugarFicha(t_tablero tab, enum t_jugador jug, short int casilla){
    tab[casilla] = jug;
    return 1;
}
void asignarFichas(enum t_jugador *jugH, enum t_jugador *IA)
{
    if(rand()%2==0)
    {
        *jugH=J_O;
        *IA=J_X;
    }else
    {
        *jugH=J_X;
        *IA=J_O;
    }

}

int partida(char* nombreJug, void (jugadaIA)(t_linea[8], t_tablero, enum t_jugador)){
    t_tablero tablero;
    int estado = EST_EN_CURSO;
    enum t_jugador jugHumano;
    enum t_jugador jugIA;
    enum t_jugador ganador = J_VACIO;
    t_linea tabLinea[8];

    asignarFichas(&jugHumano,&jugIA);
    initTablaLineas(tabLinea);
    limpiarTablero(tablero);
    while(estado == EST_EN_CURSO){
        turnoJugador(tablero, jugHumano, nombreJug);
        estado = evalTablero(tabLinea, tablero, &ganador);
        if(estado != EST_EN_CURSO)
            break;
        jugadaIA(tabLinea, tablero, jugIA);
        estado = evalTablero(tabLinea, tablero, &ganador);
    }
    limpiarPantalla();
    printf("\nFin del juego! ");
    mostrarTablero(tablero);
    switch(ganador){
        case J_O:
            printf("\nGanador: Os\n");
            break;
        case J_X:
            printf("\nGanador: Xs\n");
            break;
        case J_VACIO:
            printf("\nEmpate\n");
            break;
    }

    // Retornamos la cantidad de puntos ganados
    if(ganador == J_VACIO)
        return 2;
    if(ganador == jugHumano)
        return 3;
    return -1;
}

#endif
