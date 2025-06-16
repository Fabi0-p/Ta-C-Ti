#include<stdio.h>
#include<time.h>
#include"main.h"

#include "secundarias.h"
#include"ranking.h"
#include"api.h"
#include"lista.h"
#include"RivalIA.h"
#include"Juego.h"

// Este valor eventualmente debe venir de configuracion.txt
#define PARTIDAS_POR_JUGADOR 2

void iniciarJuego();

int main(){
    srand(time(NULL));

    int op = 0;

    while(op != 3){
        printf("1) Jugar\n");
        printf("2) Ver ranking de equipo\n");
        printf("3) Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &op);
        if(op < 1 || op > 3)
            printf("\nLa opcion ingresada no es valida\n\n");

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
    printf("\nPlaceholder para cargar la configuracion\n\n");
}

void iniciarJuego() {
    Lista listaJugadores;
    ProcesarJugadorExtraParams extraParams;
    int cant;

    extraParams.partidasPorJugador = PARTIDAS_POR_JUGADOR; // Esto se tiene que levantar de la config
    crearCola(&extraParams.colaInfo);
    crearLista(&listaJugadores);

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
        // Insertamos cualquier número como prioridad relativa. No usamos bun % porque no nos interesa el valor preciso, solo que sea menor o mayor a los demás y que sea aleatorio
        // Además al no usar un % hacemos que sea menos probable que los valores se repitan
        j.prioridadRelativa = rand();
        j.partidasRestantes = PARTIDAS_POR_JUGADOR;

        ponerEnOrdenConRepetidos(&listaJugadores, &j, sizeof(InfoJugador), compararJugadorPorPrioridadRelativa);
    }

    printf("\nOrden de los jugadores:\n");
    mostrarLista(&listaJugadores, mostrarJugador, stdout);
    recorrerLista(&listaJugadores, &extraParams, procesarJugador);

    printf("\n Todas las partidas han sido jugadas.\n");

    // acá hay que llamar la función que genere el informe y pasarle como parámetro extraParams.colaInfo
    enviarRankingPorPOST("proceso", &listaJugadores);
    vaciarLista(&listaJugadores);
    vaciarCola(&extraParams.colaInfo);
}

void procesarJugador(void* elem, void* extraParams){
    // en params->colaInfo se puede guardar la información que se necesite para el informe TXT
    InfoJugador *actual = (InfoJugador*)elem;
    ProcesarJugadorExtraParams* params = (ProcesarJugadorExtraParams*)extraParams;
    for(int i = 0; i < params->partidasPorJugador; i++){
        printf("\nQue el jugador \"%s\" se prepare para la partida %d/%d. Presione [Enter] cuando este listo... ", actual->nombre, i+1, PARTIDAS_POR_JUGADOR);
        fflush(stdin);
        getchar();
        int puntaje = partida(actual->nombre, IAjugarTurno);
        actual->puntaje += puntaje;
    }
}

void mostrarJugador(const void* dato, FILE* fp) {
    const InfoJugador* j = (const InfoJugador*)dato;
    fprintf(fp, "  - %s\n", j->nombre);
}
