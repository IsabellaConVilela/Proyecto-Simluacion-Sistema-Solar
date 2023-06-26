#ifndef ENTRADA_C
#define ENTRADA_C

#include "../classes/respuesta.c"
#include "formulas.c"

#include "../classes/consulta.c"
#include "../classes/objeto.c"
#include <stdio.h>
#include <string.h>

static Objeto objetos[50];
static Consulta consultas[50];
static Respuesta respuestas[50];

static void interpretador_objetos(int *indice, char *linea) {
  int counter = 0;
  char *dato = strtok(linea, ",");
  while (dato) {

    if (counter == 0) {
      strcpy(objetos[*indice].id_objeto, dato);
    } else if (counter == 1) {
      objetos[*indice].masa = strtod(dato, NULL);
    } else if (counter == 2) {
      objetos[*indice].x_perihelio = strtod(dato, NULL);
    } else if (counter == 3) {
      objetos[*indice].y_perihelio = strtod(dato, NULL);
    } else if (counter == 4) {
      objetos[*indice].x_afelio = strtod(dato, NULL);
    } else if (counter == 5) {
      objetos[*indice].y_afelio = strtod(dato, NULL);
    } else if (counter == 6) {
      objetos[*indice].x_inicio = strtod(dato, NULL);
    } else if (counter == 7) {
      objetos[*indice].y_inicio = strtod(dato, NULL);
    }

    dato = strtok(NULL, ",");
    ++counter;
  }
  *indice += 1;
}

static void interpretador_consultas(int *indice, char *linea) {
  int counter = 0;
  char *dato = strtok(linea, ",");
  while (dato) {

    if (counter == 0) {
      strcpy(consultas[*indice].id_consulta, dato);
    } else if (counter == 1) {
      strcpy(consultas[*indice].id_objeto, dato);
    } else if (counter == 2) {
      consultas[*indice].segundos = strtod(dato, NULL);
    }

    dato = strtok(NULL, ",");
    ++counter;
  }
  *indice += 1;
}

static void procesador_respuestas(Consulta *consultas, Objeto *objetos) {

  for (int i = 0; i < sizeof(consultas); i++) {
    if (consultas[i].id_objeto[0] != '\0') {
      for (int j = 0; j < sizeof(objetos); j++) {
        if (objetos[j].id_objeto[0] != '\0' &&
            !strcmp(consultas[i].id_objeto, objetos[j].id_objeto)) {
          printf("REALIZANDO CONSULTA: %s\n", consultas[i].id_consulta);

          Coordenadas foco = {0, 0};

          Coordenadas afelio = {objetos[j].x_afelio, objetos[j].y_afelio};

          Coordenadas perihelio = {objetos[j].x_perihelio, objetos[j].y_perihelio};
          Coordenadas iniciales={objetos[j].x_inicio,objetos[j].y_inicio};

          double r_afelio = calcularDistancia(afelio);
          double r_perihelio = calcularDistancia(perihelio);
          double ejeMayor = calcularEjeMayor(r_perihelio, r_afelio);
          Coordenadas centro = calcularCentro(ejeMayor, perihelio, afelio);
          double ejeMenor = calcularEjeMenor(ejeMayor, centro);
          double periodoOrbital = calcularPeriodoOrbital(ejeMayor / 2, objetos[j].masa);
          double anguloRecorido = calcularAnguloDeRecorrido(consultas[i].segundos, periodoOrbital,iniciales);
          Coordenadas coordenadasFinales = calcularCoordenadasFinales(ejeMayor, ejeMenor, centro, anguloRecorido);

          Respuesta respuesta;
          strcpy(respuesta.id_consulta, consultas[i].id_consulta);
          respuesta.x = coordenadasFinales.x;
          respuesta.y = coordenadasFinales.y;

          respuestas[i] = respuesta;
        }
      }
    }
  }
}

static void generar_salida() {
  FILE *archivo_respuestas;
  archivo_respuestas = fopen("respuestas.txt", "w");
  fputs("[Respuestas]\n", archivo_respuestas);
  for (int i = 0; i < sizeof(*respuestas); i++) {
    if (respuestas[i].id_consulta[0] != '\0') {
      fprintf(archivo_respuestas, "ID:%s, X:%lf, Y:%lf\n",
              respuestas[i].id_consulta, respuestas[i].x, respuestas[i].y);
    }
  }
  fclose(archivo_respuestas);
  printf("Finalizado con exito! Documento de respuestas generado satisfactoriamente!");
}

static void abrir_archivo(char *nombre) {
  char linea[150];
  int obj_i = 0;
  int con_i = 0;
  FILE *archivo = fopen(nombre, "r");

  char seccion_actual[25]; // almacena cabecera de la seccion actual

  while (fgets(linea, sizeof(linea), archivo) != NULL) {
    if (linea[0] == '[') {
      strcpy(seccion_actual, linea);
    } else if (seccion_actual[1] == 'd') {
      interpretador_objetos(&obj_i, linea);
    } else if (seccion_actual[1] == 'c') {
      interpretador_consultas(&con_i, linea);
    }
  }

   fclose(archivo);
   procesador_respuestas(consultas, objetos);
   generar_salida();

  
}

#endif // ENTRADA_C