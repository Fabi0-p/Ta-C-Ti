#include <stdlib.h>

#include "secundarias.h"

void limpiarPantalla() 
{
  #ifdef _WIN32
      system("cls");
  #else
      system("clear");
  #endif
}
