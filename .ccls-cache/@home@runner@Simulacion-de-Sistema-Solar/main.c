#include "utils/entrada.c"
#include <stdio.h>

int main(void) {
  char filename[100];
  printf("Introduzca el nombre del archivo: ");
  scanf("%s", filename);
  abrir_archivo(filename);
}