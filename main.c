#include<stdio.h>
#include<time.h>
#include"main.h"

#include "secundarias.h"
#include"ranking.h"
#include"cola.h"
#include"api.h"
#include"lista.h"
#include"RivalIA.h"
#include"Juego.h"

// Este valor eventualmente debe venir de configuracion.txt
#define PARTIDAS_POR_JUGADOR 3

void iniciarJuego();

int main(){
    srand(time(NULL));

    inicializarRanking();
    //char codigoGrupo[] = "proceso";
    //obtenerRankingDesdeAPI(codigoGrupo);

    int op = 0;

    while(op != 3){

        printf("1) Jugar\n");
        printf("2) Ver ranking de equipo\n");
        printf("3) Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &op);
        if(op < 1 || op > 3)
            printf("\nLa opción ingresada no es válida\n\n");

        switch (op) {
            case 1:
                iniciarJuego();
                break;
            case 2:
                verRanking();
                break;
            case 3:
                break;
        }
    }

    printf("\n[DEBUG] Programa finalizado correctamente.\n");

    return 0;
}

void cargarConfig(){
    printf("\nPlaceholder para cargar la configuración\n\n");
}

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
        InfoJugador j;
        printf("Nombre del jugador %d: ", i + 1);
        fgets(j.nombre, sizeof(j.nombre), stdin);
        j.nombre[strcspn(j.nombre, "\n")] = '\0';

        j.puntaje = 0;
        j.partidasJugadas = 0;
        j.partidasRestantes = PARTIDAS_POR_JUGADOR;

        ponerEnCola(&colaJugadores, &j, sizeof(InfoJugador));
    }

    while (!colaVacia(&colaJugadores)) {
        InfoJugador actual;
        sacarDeCola(&colaJugadores, &actual, sizeof(InfoJugador));

        printf("\nPresiona [Enter] para comenzar siguiente partida...");
        fflush(stdin);
        getchar();

        int puntaje = partida(actual.nombre, IAjugarTurno);

        InfoJugador nuevoResultado;
        strcpy(nuevoResultado.nombre, actual.nombre);
        nuevoResultado.puntaje = puntaje;
        nuevoResultado.partidasJugadas = 1;
        nuevoResultado.partidasRestantes = 0;

        ponerEnOrden(obtenerListaRanking(), &nuevoResultado, sizeof(InfoJugador),
                     compararJugadorPorNombre, acumularPuntaje);

        actual.partidasRestantes--;
        actual.partidasJugadas++;

        if (actual.partidasRestantes > 0) {
            ponerEnCola(&colaJugadores, &actual, sizeof(InfoJugador));
        }
    }

    printf("\n Todas las partidas han sido jugadas.\n");

    enviarRankingPorPOST("proceso");
}
