#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"
#include "jugadores.h"
#include "api.h"
#define ARCHIVO_JSON "api_response.json"


void enviarRankingPorPOST(const char* codigoGrupo){
    FILE* f = fopen("post_body.json", "w");
    if (!f) {
        printf(" No se pudo crear el archivo post_body.json\n");
        return;
    }

    // Escribimos el comienzo del JSON
    fprintf(f, "{\n");
    fprintf(f, "  \"CodigoGrupo\": \"%s\",\n", codigoGrupo);
    fprintf(f, "  \"Jugadores\": [\n");

    Lista* lista = obtenerListaRanking();
    NodoLista* actual = *lista; //  correcto — lista apunta a NodoLista*


    int primero = 1;

    while (actual) {
        Jugador* j = (Jugador*)actual->info;

        if (!primero)
            fprintf(f, ",\n");
        primero = 0;

        fprintf(f, "    {\n");
        fprintf(f, "      \"nombre\": \"%s\",\n", j->nombre);
        fprintf(f, "      \"puntos\": %d\n", j->puntaje);
        fprintf(f, "    }");

        actual = actual->sig;
    }

    fprintf(f, "\n  ]\n}");

    fclose(f);

    printf(" JSON de POST generado correctamente.\n");

    // Enviamos con curl
    int res = system("curl -X POST https://algoritmos-api.azurewebsites.net/api/TaCTi "
                     "-H \"Content-Type: application/json\" "
                     "-d @post_body.json -s -o resultado_post.txt");

    if (res == 0)
        printf(" POST enviado correctamente.\n");
    else
        printf(" Error al enviar POST.\n");
}


void obtenerRankingDesdeAPI(const char* codigoGrupo)
{
    char comandoCurl[256];
    sprintf(comandoCurl, "curl https://algoritmos-api.azurewebsites.net/api/TaCTi/%s -s -o api_response.json", codigoGrupo);

    int r = system(comandoCurl);
    if (r != 0) {
        printf(" Error al ejecutar curl.\n");
        return;
    }

    FILE* f = fopen("api_response.json", "r");
    if (!f) {
        printf(" No se pudo abrir el archivo de respuesta.\n");
        return;
    }
    vaciarLista(obtenerListaRanking());

    char buffer[4096];
    fread(buffer, sizeof(char), sizeof(buffer) - 1, f);
    buffer[sizeof(buffer) - 1] = '\0'; // Null-terminate
    fclose(f);

    char* ptr = buffer;
    while ((ptr = strstr(ptr, "\"nombreJugador\"")) != NULL) {
        char nombre[50];
        int puntos;

        if(sscanf(ptr, " %*[^:] : \"%[^\"]\"", nombre)!=1)
        {
            printf("ERROR no se pudo leer puntaje para jugador %s", nombre);
            break;
        }
        ptr = strstr(ptr, "\"puntaje\"");
        if (ptr) {
            sscanf(ptr, " %*[^:] : %d", &puntos);

            Jugador j;
            strcpy(j.nombre, nombre);
            j.puntaje = puntos;
            j.partidasJugadas = 0;
            j.partidasRestantes = 0;

            if (!ponerAlFinal(obtenerListaRanking(), &j, sizeof(Jugador)))
                {
                    printf("[ERROR] Falló insertar jugador en lista\n");
                    break;
                }

            ptr++;
        } else {
            break;
        }
    }

    printf(" Ranking cargado desde la API con exito.\n");
}





