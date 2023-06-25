#ifndef ENTRADA_C
#define ENTRADA_C

#include "formulas.c"
#include "../classes/respuesta.c"

#include "../classes/objeto.c"
#include <stdio.h>
#include <string.h>
#include "../classes/consulta.c"

static Objeto objetos[100];
static Consulta consultas[100];
static Respuesta respuestas[100];


static void interpretador_objetos(int seccion_contador, char *linea){
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
  // ++seccion_contador;
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

static void procesador_respuestas(Consulta *consultas, Objeto *objetos ){
  for(int i=0; i<sizeof *consultas; i++){
    if (consultas[i].id_objeto != NULL){
      //printf("%s\n",consultas[i].id_objeto);
      for(int j=0; j<sizeof *objetos; j++){
        if(objetos[j].id_objeto != NULL && strcmp(consultas[i].id_objeto,objetos[j].id_objeto)){
          Coordenadas centro = {0,0};
          Coordenadas afelio= {objetos[j].x_afelio,objetos[j].y_afelio};
          Coordenadas perihelio={objetos[j].x_perihelio,objetos[j].x_perihelio};

          double r_afelio = calcularDistancia(centro,afelio);
          double r_perihelio= calcularDistancia(centro,perihelio);
          double ejeMayor= calcularEjeMayor( r_perihelio,  r_afelio);
          double excentricidad= calcularExcentricidad( r_perihelio,  r_afelio);
          double ejeMenor= calcularEjeMenor (ejeMayor, excentricidad);
          double periodoOrbital= calcularPeriodoOrbital(ejeMayor, objetos[j].masa);
          double velocidadMedia= calcularVelocidadMedia(ejeMayor, periodoOrbital);
          double anguloRecorido= calcularAnguloDeRecorrido(consultas[i].segundos, periodoOrbital);
          double distanciaRadial= calcularDistanciaRadial( ejeMayor, excentricidad, anguloRecorido);
          Coordenadas coordenadasFinales= calcularCoordenadasFinales(distanciaRadial, anguloRecorido);
          
          printf("%lf\n", coordenadasFinales.x);
          printf("%lf", coordenadasFinales.y);

          // printf("ID: %s\n", objetos[j].id_objeto);
          // printf("MASA: %lf\n", objetos[j].masa);
          // printf("PERIHELIO: %lf, %lf\n", objetos[j].x_perihelio,objetos[j].x_perihelio);
          // printf("AFELIO: %lf, %lf\n", objetos[j].x_afelio, objetos[j].y_afelio);
          // printf("INICIO: %lf, %lf\n", objetos[j].x_inicio, objetos[j].y_inicio);

          Respuesta respuesta={consultas[i].id_consulta, coordenadasFinales.x, coordenadasFinales.y};
          respuestas[i]=respuesta;

          
        }
      }
    }
  }
}

static void generar_salida(){
  FILE *archivo_respuestas;
  archivo_respuestas = fopen("respuestas.txt", "w");
  fputs("[Respuestas]\n", archivo_respuestas);
  for(int i=0; i<sizeof(*respuestas);i++){
    if(respuestas[i].id_consulta!=NULL){
      fprintf(archivo_respuestas,"ID:%s, X:%lf, Y:%lf", respuestas[i].id_consulta, respuestas[i].x, respuestas[i].y); 
    }
  }
  fclose(archivo_respuestas);
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
  procesador_respuestas(consultas,objetos);
  generar_salida();
  
}



#endif // ENTRADA_C