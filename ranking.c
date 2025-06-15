#include <stdio.h>
#include <string.h>
#include <time.h>
#include"lista.h"
#include"api.h"
#include "ranking.h"

int acumularPuntaje(void** destino, unsigned* tamDestino, const void* nuevo, unsigned tamNuevo) {
    InfoJugador* existente = (InfoJugador*)(*destino);
    const InfoJugador* nuevoJ = (const InfoJugador*)nuevo;

    existente->puntaje += nuevoJ->puntaje;
    existente->partidasJugadas += nuevoJ->partidasJugadas;

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


/*
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
*/
