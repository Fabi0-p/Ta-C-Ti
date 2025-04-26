#include<stdio.h>
#include"main.h"

int main(){
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
    printf("\nPlaceholder para el juego\n\n");
}

void verRanking(){
    printf("\nPlaceholder para el ranking\n\n");
}

void cargarConfig(){
    printf("\nPlaceholder para cargar la configuración\n\n");
}