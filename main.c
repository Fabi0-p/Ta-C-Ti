#include<stdio.h>
#include"main.h"
#include "Juego.h"
#include "RivalIA.h"
#include "secundarias.h"

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
            printf("\nLa opción ingresada no es válida\n\n");

        switch (op) {
            case 1:
                iniciarJuego();
                break;
            case 2:
                verRanking();
                break;
        }
    }

    return 0;
}


void iniciarJuego(){
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
        turnoJugador(tablero, jugHumano);
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
}

void verRanking(){
    printf("\nPlaceholder para el ranking\n\n");
}

void cargarConfig(){
    printf("\nPlaceholder para cargar la configuración\n\n");
}
