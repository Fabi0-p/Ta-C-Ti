#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "lista.h"
#include "api.h"
#include "ranking.h"

int acumularPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo) {
    InfoJugador* existente = (InfoJugador*)(*destino);
    const InfoJugador* nuevoJ = (const InfoJugador*)nuevo;

    existente->puntaje += nuevoJ->puntaje;
    existente->partidasJugadas += nuevoJ->partidasJugadas;

    return 1;
}

int reemplazarPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo) {
    InfoJugador* existente = (InfoJugador*)(*destino);
    const InfoJugador* nuevoJ = (const InfoJugador*)nuevo;

    existente->puntaje = fmax(nuevoJ->puntaje, existente->puntaje);

    return 1;
}

void mostrarJugadorConPuntos(const void* dato, FILE* fp) {
    const InfoJugador* j = (const InfoJugador*)dato;
    fprintf(fp, "%s: %d puntos\n", j->nombre, j->puntaje);
}

void verRanking() {
    Lista listaRanking;
    printf("\n====== RANKING DE EQUIPO ======\n");
    crearLista(&listaRanking);
    obtenerRankingDesdeAPI("proceso", &listaRanking);
    ordenarLista(&listaRanking, compararJugadorPorPuntajeDesc);
    mostrarLista(&listaRanking, mostrarJugadorConPuntos, stdout);
    vaciarLista(&listaRanking);
}



void generarInformeTXT(Cola *p) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char nombreArchivo[100];
    int suma = 0;
    Lista mejoresPuntajes;
    crearLista(&mejoresPuntajes);
    strftime(nombreArchivo, sizeof(nombreArchivo), "informe-juego_%Y-%m-%d-%H-%M.txt", tm_info);

    FILE* f = fopen(nombreArchivo, "w");
    if (!f) {
        perror("No se pudo crear el informe");
        return;
    }

    fprintf(f, "======= INFORME DE PARTIDAS =======\n\n");
    InfoPartida partida;
    while (!colaVacia(p)) {
        sacarDeCola(p, &partida, sizeof(InfoPartida));
        if(!listaLlena(&mejoresPuntajes,sizeof(Lista))){
            // Metemos los jugadores en orden alfabético, y cuando hay un jugador repetido pisamos el puntaje por el mayor
            ponerEnOrden(&mejoresPuntajes,&partida.j,sizeof(InfoJugador),compararJugadorPorNombre, reemplazarPuntaje);
        }
        // Y después ordenamos por puntaje
        ordenarLista(&mejoresPuntajes, compararJugadorPorPuntajeAsc);

        fprintf(f, "Jugador: %s\n", partida.j.nombre);
        fprintf(f, "Partida nro: %d\n", partida.numeroPartida);
        fprintf(f, "Puntaje de esta partida: %d\n", partida.puntajePartida);
        fprintf(f, "Tablero final:\n");
        imprimirTableroTXT(partida.tablero, f);
        fprintf(f, "\n------------------------\n\n");
        suma +=partida.puntajePartida;
        if(partida.numeroPartida == PARTIDAS_POR_JUGADOR)
        {           
            fprintf(f, "\n");
            fprintf(f, "El Jugador: %s\n", partida.j.nombre);
            fprintf(f, "Sumo en total : %d\n", suma);
            fprintf(f, "\n------------------------\n\n");
            suma =0;
        }
    }
    imprimirRankingTXT(&mejoresPuntajes,f);
    vaciarLista(&mejoresPuntajes);
    fclose(f);

    printf(" Informe generado: %s\n", nombreArchivo);
}
void imprimirTableroTXT(t_tablero tab,FILE *f)
{
    for (int i = 0; i < 9; i++) {
        char c;
        switch (tab[i]) {
            case J_X: c = 'X'; break;
            case J_O: c = 'O'; break;
            case J_VACIO: c = ' '; break;

        }
        fprintf(f, " %c ", c);
        if ((i + 1) % 3 == 0)
            fprintf(f, "\n");
        else
            fprintf(f, "|");
    }
}
void imprimirRankingTXT(Lista *p,FILE *f)
{   fprintf(f, "\n--------------------\n");
    fprintf(f, "RANKING DE JUGADORES EN ESTA PARTIDA\n");
    recorrerLista(p, f, imprimirJugadorTXT);
}
void imprimirJugadorTXT(void* elem, void* extraParams) {
    InfoJugador* jugador = (InfoJugador*) elem;
    FILE* f = (FILE*) extraParams;

    fprintf(f, "Jugador: %s - Puntaje total: %d\n", jugador->nombre, jugador->puntaje);
}



