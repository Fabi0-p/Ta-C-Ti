#include <stdio.h>
#include <string.h>
#include "cola.h"
#include "jugadores.h"
#include "ranking.h"
#include <time.h>


// Este valor eventualmente debe venir de configuracion.txt
#define PARTIDAS_POR_JUGADOR 3

void iniciarJuego() {
    srand(time(NULL));

    Cola colaJugadores;
    crearCola(&colaJugadores);

    int cant;
    printf("\n¿Cuántos jugadores van a jugar? ");
    scanf("%d", &cant);
    getchar(); // limpiar buffer

    for (int i = 0; i < cant; i++) {
        Jugador j;
        printf("Nombre del jugador %d: ", i + 1);
        fgets(j.nombre, sizeof(j.nombre), stdin);
        j.nombre[strcspn(j.nombre, "\n")] = '\0'; // eliminar el \n

        j.puntaje = 0;
        j.partidasJugadas = 0;
        j.partidasRestantes = PARTIDAS_POR_JUGADOR;

        ponerEnCola(&colaJugadores, &j, sizeof(Jugador));
    }

    while (!colaVacia(&colaJugadores)) {
        Jugador actual;
        sacarDeCola(&colaJugadores, &actual, sizeof(Jugador));

        printf("\nTurno de %s\n", actual.nombre);

        // Acá deberías mostrar el tablero e iniciar la partida contra IA
        // Por ahora simulamos resultado
            int resultadoSimulado = rand() % 3; // 0 = perdió, 1 = empató, 2 = ganó

        int puntaje = 0;
        if (resultadoSimulado == 0) {
            printf("Resultado simulado: Derrota (-1 punto)\n");
            puntaje = -1;
        } else if (resultadoSimulado == 1) {
            printf("Resultado simulado: Empate (+2 puntos)\n");
            puntaje = 2;
        } else {
            printf("Resultado simulado: Victoria (+3 puntos)\n");
            puntaje = 3;
        }// simular que ganó
        printf("Resultado simulado: +%d puntos\n", puntaje);
        actualizarPuntaje(&actual, puntaje);
        actual.partidasRestantes--;
        actual.partidasJugadas++;

        if (actual.partidasRestantes > 0) {
            ponerEnCola(&colaJugadores, &actual, sizeof(Jugador));
        }
    }

    printf("\n Todas las partidas han sido jugadas.\n");
}
