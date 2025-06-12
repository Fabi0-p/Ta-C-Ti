#include <stdio.h>
#include <string.h>
#include <time.h>
#include"lista.h"
#include"api.h"
#include "ranking.h"

static Lista listaRanking;

void inicializarRanking() {
    crearLista(&listaRanking);
}
Lista* obtenerListaRanking() {
    return &listaRanking;
}



int acumularPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo) {
    Jugador* existente = (Jugador*)(*destino);
    const Jugador* nuevoJ = (const Jugador*)nuevo;

    existente->puntaje += nuevoJ->puntaje;
    existente->partidasJugadas += nuevoJ->partidasJugadas;

    return 1;
}





void mostrarJugador(const void* dato, FILE* fp) {
    const Jugador* j = (const Jugador*)dato;
    fprintf(fp, "%s - %d puntos (%d partidas)\n", j->nombre, j->puntaje, j->partidasJugadas);
}

void verRanking() {
    printf("\n====== RANKING DE EQUIPO ======\n");
    obtenerRankingDesdeAPI("proceso");
    ordenarLista(&listaRanking, compararJugadorPorPuntajeDesc);
    mostrarLista(&listaRanking, mostrarJugador, stdout);
}



void generarInformeTXT() {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char nombreArchivo[100];
    strftime(nombreArchivo, sizeof(nombreArchivo), "informes/informe-juego_%Y-%m-%d-%H-%M.txt", tm_info);

    FILE* f = fopen(nombreArchivo, "w");
    if (!f) {
        perror("No se pudo crear el informe");
        return;
    }

    fprintf(f, "======= INFORME DE PARTIDAS =======\n\n");
    mostrarLista(&listaRanking, mostrarJugador, f);
    fclose(f);

    printf(" Informe generado: %s\n", nombreArchivo);
}
