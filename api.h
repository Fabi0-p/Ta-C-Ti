#ifndef API_H_INCLUDED
#define API_H_INCLUDED
#include"lista.h"

void obtenerRankingDesdeAPI(const char* codigoGrupo, Lista* lista);
void enviarRankingPorPOST(const char* codigoGrupo, Lista* lista);

#endif // API_H_INCLUDED
