#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include"main.h"

#include "secundarias.h"
#include"ranking.h"
#include"api.h"
#include"lista.h"
#include"RivalIA.h"
#include"Juego.h"

void iniciarJuego();

int main(){
    srand(time(NULL));
    Config conf;
    cargarConfig(&conf);
    printf("leidos correctamente los valores de :\n");
    printf("URL : %s  PASWW %s  \n",conf.url,conf.passw);
    printf("Cant de partidas %d:\n",conf.cantPartidas);
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
                iniciarJuego(&conf);
                break;
            case 2:
                verRanking(&conf);
                break;
            case 3:
                break;
        }
    }

    printf("\n[DEBUG] Programa finalizado correctamente.\n");

    return 0;
}

int cargarConfig(Config *c){
    FILE *f;
    f = fopen(ARCH_CONFIG,"r");
    if(!f)
    {
        printf("\n error al abrir el archivo de configuraciones\n");
        return 1;
    }
    if (fscanf(f, " %[^|]| %[^\n]\n", c->url, c->passw) != 2) {
        printf("error al leer url y la passw\n");
        fclose(f);
        return 1;
    }
    if (fscanf(f, "%d", &c->cantPartidas) != 1) {
        printf("error al leer cant partidas\n");
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

void iniciarJuego(Config *conf) {
    Lista listaJugadores;
    ProcesarJugadorExtraParams extraParams;
    int cant,leido;

    extraParams.partidasPorJugador = conf->cantPartidas;// Esto se tiene que levantar de la config
    crearCola(&extraParams.colaInfo);
    crearLista(&listaJugadores);

    do{
        printf("\n Cuantos jugadores van a jugar? ");
        leido = scanf("%d", &cant);
        if(leido!=1 || (cant < 1 && cant >999))
            printf("\n Ingrese un numero valido \n");

        while(getchar()!= '\n');//en el caso de que haya tomado una letra, entra en bucle hasta limpiar el buffer

    }while(leido!=1 || (cant < 1 && cant >999) );

    for (int i = 0; i < cant; i++) {
        agregarJugadores(&listaJugadores, i, conf);
    }

    printf("\nOrden de los jugadores:\n");
    mostrarLista(&listaJugadores, mostrarJugador, stdout);
    recorrerLista(&listaJugadores, &extraParams, procesarJugador);
    ordenarLista(&listaJugadores, compararJugadorPorPuntajeDesc);

    printf("\n Todas las partidas han sido jugadas.\n");

    // acá hay que llamar la función que genere el informe y pasarle como parámetro extraParams.colaInfo
    generarInformeTXT(&extraParams.colaInfo, &listaJugadores, conf);
    enviarRankingPorPOST(conf->passw, &listaJugadores);//aca cambie "proceso" -> por conf->pasww
    vaciarLista(&listaJugadores);
    vaciarCola(&extraParams.colaInfo);
}

void procesarJugador(void* elem, void* extraParams){
    // en params->colaInfo se puede guardar la información que se necesite para el informe TXT
    InfoJugador *actual = (InfoJugador*)elem;
    ProcesarJugadorExtraParams* params = (ProcesarJugadorExtraParams*)extraParams;
    for(int i = 0; i < params->partidasPorJugador; i++){
        printf("\nQue el jugador \"%s\" se prepare para la partida %d/%d. Presione [Enter] cuando este listo... ", actual->nombre, i+1, params->partidasPorJugador);
        fflush(stdin);
        getchar();
        t_tablero tableroFinal;
        int puntaje = partida(actual->nombre, IAjugarTurno, &tableroFinal);
        actual->puntaje += puntaje;
        actual->partidasJugadas++;

        InfoPartida pActual;
        pActual.j = *actual;
        pActual.puntajePartida=puntaje;
        pActual.numeroPartida=i+1;
        memcpy(pActual.tablero,tableroFinal,sizeof(t_tablero));
        ponerEnCola(&(params->colaInfo),&pActual,sizeof(InfoPartida));
    }
}

void mostrarJugador(const void* dato, FILE* fp) {
    const InfoJugador* j = (const InfoJugador*)dato;
    fprintf(fp, "  - %s\n", j->nombre);
}

void agregarJugadores(Lista *listaJugadores, int num, Config *conf){
    InfoJugador j;
    int valido = 0;
    while(!valido){
        valido = 1;
        printf("Nombre del jugador %d: ", num + 1);
        fgets(j.nombre, sizeof(j.nombre), stdin);
        j.nombre[strcspn(j.nombre, "\n")] = '\0';
        for(int i = 0; i < strlen(j.nombre); i++){
            if(valido){
                if(!isalpha(j.nombre[i]) && !isdigit(j.nombre[i]) && j.nombre[i] != ' '){
                    printf("El nombre solo puede estar compuesto por caracteres alfanumericos y espacios en blanco.\n");
                    valido = 0;
                }
            }
        }
        if(existeEnLista(listaJugadores, &j, compararJugadorPorNombre)){
            printf("Ya se ha ingresado un jugador con ese nombre.\n");
            valido = 0;
        }
    }

    j.puntaje = 0;
    j.partidasJugadas = 0;
    // Insertamos cualquier número como prioridad relativa. No usamos bun % porque no nos interesa el valor preciso, solo que sea menor o mayor a los demás y que sea aleatorio
    // Además al no usar un % hacemos que sea menos probable que los valores se repitan
    j.prioridadRelativa = rand();
    j.partidasRestantes = conf->cantPartidas;

    ponerEnOrdenConRepetidos(listaJugadores, &j, sizeof(InfoJugador), compararJugadorPorPrioridadRelativa);
}
