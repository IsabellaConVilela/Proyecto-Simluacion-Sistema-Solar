#ifndef ENTRADA_C
#define ENTRADA_C

#include "objeto.c"
#include <stdio.h>
#include <string.h>
#include "consulta.c"

static Objeto objetos[50];
static Consulta consultas[50];

static void interpretador_objetos(int seccion_contador, char *linea ){
  int counter = 0;
  char *dato = strtok(linea, ",");
  while (dato) {

    switch(counter) {
      case 0:
        objetos[seccion_contador].id_objeto = dato;
        break;
      case 1:
        objetos[seccion_contador].masa = strtod(dato, NULL);
        break;
      case 2:
        objetos[seccion_contador].x_perihelio = strtod(dato, NULL);
        break;
      case 3:
        objetos[seccion_contador].y_perihelio = strtod(dato, NULL);
        break;
      case 4:
        objetos[seccion_contador].x_afelio = strtod(dato, NULL);
        break;
      case 5:
        objetos[seccion_contador].y_afelio = strtod(dato, NULL);
        break;
      case 6:
        objetos[seccion_contador].x_inicio = strtod(dato, NULL);
        break;
      case 7:
        objetos[seccion_contador].y_inicio = strtod(dato, NULL);
        break;
    }
    
    dato = strtok(NULL,",");
    ++counter;
  }

  // printf("ID: %s\n", objetos[seccion_contador].id_objeto);
  // printf("MASA: %lf\n", objetos[seccion_contador].masa);
  // printf("PERIHELIO: %lf, %lf\n", objetos[seccion_contador].x_perihelio, objetos[seccion_contador].y_perihelio);
  // printf("AFELIO: %lf, %lf\n", objetos[seccion_contador].x_afelio, objetos[seccion_contador].y_afelio);
  // printf("INICIO: %lf, %lf\n", objetos[seccion_contador].x_inicio, objetos[seccion_contador].y_inicio);
  ++seccion_contador;
}

static void interpretador_consultas(int seccion_contador, char *linea) {
  int counter = 0;
      char *dato = strtok(linea, ",");
      while (dato) {

        switch(counter) {
          case 0:
            consultas[seccion_contador].id_consulta = dato;
            break;
          case 1:
            consultas[seccion_contador].id_objeto = dato;
            break;
          case 2:
            consultas[seccion_contador].segundos = strtod(dato, NULL);
            break;
        }
        
        dato = strtok(NULL,",");
        ++counter;
      }

      // printf("ID: %s\n", consultas[seccion_contador].id_consulta);
      // printf("OBJETO: %s\n", consultas[seccion_contador].id_objeto);
      // printf("SEGUNDOS: %lf\n", consultas[seccion_contador].segundos);
      ++seccion_contador;
}

static void abrir_archivo(char *nombre) {
  char linea[150];
  int objCounter = 0;
  int conCounter = 0;
  FILE *archivo = fopen(nombre, "r");

  char seccion_actual[150];

  while (fgets(linea, sizeof(linea), archivo) != NULL) {
    if (linea[0] == '[') 
    {
      strcpy(seccion_actual, linea);
    } 
    else if (seccion_actual[1] == 'd') 
    {
      interpretador_objetos(objCounter, linea);
    } 
    else if (seccion_actual[1] == 'c') 
    {
      interpretador_consultas(conCounter, linea);
    }
  }

  fclose(archivo);
}

#endif // ENTRADA_C