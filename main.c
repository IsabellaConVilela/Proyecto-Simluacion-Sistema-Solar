#include "utils/entrada.c"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

bool existe(const char *filename) {
  return access(filename, F_OK) == 0;
}

int main(void) {
  char filename[100];
  printf("Introduzca el nombre del archivo: ");
  scanf("%s", filename);
  
  if (existe(filename)) {
    abrir_archivo(filename);
  } else {
    printf("\nError, el archivo no existe!\n\n");
    main();
  }
}