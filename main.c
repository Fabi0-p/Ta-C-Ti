#include<stdio.h>
#include"main.h"
#include"ranking.h"
#include"api.h"
#include"lista.h"
#include"jugadores.h"


int main(){


    inicializarRanking(); // ← muy importante, inicia listaRanking

    char codigoGrupo[] = "proceso"; // después se puede leer desde config.txt
    obtenerRankingDesdeAPI(codigoGrupo); // carga los datos ya existentes desde la API

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
                enviarRankingPorPOST(codigoGrupo);
        }
    }

    printf("\n[DEBUG] Programa finalizado correctamente.\n");


    return 0;
}

