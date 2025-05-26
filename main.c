#include<stdio.h>
#include <ctype.h>
#include"main.h"

int main(){
    int op = 0;

    do{

        printf("[A] Jugar\n");
        printf("[B] Ver ranking equipo\n");
        printf("[C] Salir\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &op);

        op = tolower(op);

        switch (op) {
            case 'a':
                iniciarJuego();
                break;
            case 'b':
                verRanking();
                break;
            case 'c':
                printf("\nQue tenga un buen dia!\n");
                break;
            default:
                printf("\nLa opción ingresada no es válida\n\n");
            break;

        }
            
    }while(op != 'c');
        
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
