#include <stdio.h>
#include <string.h>
#include "cola.h"
#include "jugadores.h"
#include "ranking.h"
#include "secundarias.h"
#include "api.h"
#include <time.h>

#include "Juego.h"
#include "RivalIA.h"

// Este valor eventualmente debe venir de configuracion.txt
#define PARTIDAS_POR_JUGADOR 3

void iniciarJuego() {
    srand(time(NULL));
    Cola colaJugadores;
    crearCola(&colaJugadores);
    vaciarLista(obtenerListaRanking());


    int cant;
    printf("\nCuantos jugadores van a jugar? ");
    scanf("%d", &cant);
    getchar();

    for (int i = 0; i < cant; i++) {
        Jugador j;
        printf("Nombre del jugador %d: ", i + 1);
        fgets(j.nombre, sizeof(j.nombre), stdin);
        j.nombre[strcspn(j.nombre, "\n")] = '\0';

        j.puntaje = 0;
        j.partidasJugadas = 0;
        j.partidasRestantes = PARTIDAS_POR_JUGADOR;

        ponerEnCola(&colaJugadores, &j, sizeof(Jugador));
    }

    while (!colaVacia(&colaJugadores)) {
        Jugador actual;
        sacarDeCola(&colaJugadores, &actual, sizeof(Jugador));

        printf("\nComenzar siguiente partida");
        getchar();
        getchar();

        int puntaje = partida(actual.nombre);

        Jugador nuevoResultado;
        strcpy(nuevoResultado.nombre, actual.nombre);
        nuevoResultado.puntaje = puntaje;
        nuevoResultado.partidasJugadas = 1;
        nuevoResultado.partidasRestantes = 0;

        ponerEnOrden(obtenerListaRanking(), &nuevoResultado, sizeof(Jugador),
                     compararJugadorPorNombre, acumularPuntaje);

        actual.partidasRestantes--;
        actual.partidasJugadas++;

        if (actual.partidasRestantes > 0) {
            ponerEnCola(&colaJugadores, &actual, sizeof(Jugador));
        }
    }

    printf("\n Todas las partidas han sido jugadas.\n");

    enviarRankingPorPOST("proceso");
}

int partida(char* nombreJug){
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
        IAjugarTurno(tabLinea, tablero, jugIA);
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
    if(ganador == J_X)
        return 2;
    if(ganador == jugHumano)
        return 3;
    return -1;
}
