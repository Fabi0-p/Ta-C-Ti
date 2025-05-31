#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"
#include "jugadores.h"
#include "api.h"

// 🔹 Este archivo se genera al hacer curl
#define ARCHIVO_JSON "api_response.json"

void enviarRankingPorPOST(const char* codigoGrupo) {
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


 // función auxiliar que devuelve el `Lista`
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
    printf("Contenido del JSON a enviar:\n");
    FILE* preview = fopen("post_body.json", "r");
        if (preview) {
            char ch;
        while ((ch = fgetc(preview)) != EOF)
            putchar(ch);
        fclose(preview);
}

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



void obtenerRankingDesdeAPI(const char* codigoGrupo) {
    char comandoCurl[256];
    sprintf(comandoCurl,"curl https://algoritmos-api.azurewebsites.net/api/TaCTi/%s -s -o %s",codigoGrupo, ARCHIVO_JSON);
    int r = system(comandoCurl);
    if (r != 0) {
        printf("Error al ejecutar curl\n");
        return;
    }

    FILE* f = fopen(ARCHIVO_JSON, "r");
    if (!f)
    {
        printf("No se pudo abrir el archivo %s\n", ARCHIVO_JSON);
        return;
    }

    char linea[512];
    Jugador j;

    while (fgets(linea, sizeof(linea), f))
        {
        if (strstr(linea, "\"nombreJugador\""))
            {
                char nombre[50];
                sscanf(linea, " %*[^:] : \"%[^\"]\"", nombre);
                strcpy(j.nombre, nombre);
            } else if (strstr(linea, "\"puntaje\""))
            {
                int puntos;
                sscanf(linea, " %*[^:] : %d", &puntos);
                j.puntaje = puntos;
                j.partidasJugadas = 0;
                j.partidasRestantes = 0;

                // Cargamos el jugador al ranking
                actualizarPuntaje(&j, j.puntaje);
            }
        }

    fclose(f);
    printf(" Ranking cargado desde la API con éxito.\n");
}
