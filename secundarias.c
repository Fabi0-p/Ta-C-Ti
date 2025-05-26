#include "main.h"

void limpiarPantalla() 
{
  #ifdef _WIN32
      system("cls");
  #else
      system("clear");
  #endif
}
