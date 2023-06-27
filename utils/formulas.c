#include "../classes/coordenadas.c"
#include <math.h>

// d=Sqrt((x2-x1)^2 + (y2-y1)^2)
static double calcularDistancia(Coordenadas a) {
  // return sqrt(pow(b.x- a.x,2) + pow(b.y-a.y,2));
  return fabsl(a.x);
}

// a=(r_peri + r_afelio)/2
static double calcularEjeMayor(double r_perihelio, double r_afelio) {
  return (r_perihelio + r_afelio);
}

// c = a - p;
static Coordenadas calcularCentro(double eje_mayor, Coordenadas perihelio, Coordenadas afelio) {

  if (perihelio.x < 0) {
    Coordenadas centro = {((eje_mayor / 2) + perihelio.x), 0};
    return centro;
  } else if (afelio.x < 0) {
    Coordenadas centro = {((eje_mayor / 2) + afelio.x), 0};
    return centro;
  } else if (perihelio.x == 0 && afelio.x == 0) {
    Coordenadas centro = {0, 0};
    return centro;
  } else {
    printf("Error: Segun las especificaciones del proyecto, los datos no se pueden "
           "calcular, por lo tanto se retorna un centro igual a (0, 0)\n");
    Coordenadas centro = {0, 0};
    return centro;
  }
}

// b=sqrt(a^2-c^2)
static double calcularEjeMenor(double a, Coordenadas c) {
  return sqrtf(pow(a / 2, 2) - pow(c.x, 2)) * 2;
}

// T = 2π * √(a³ / (G * M))
static double calcularPeriodoOrbital(double a, double M) {
  const double G = 0.0000000000667;
  const double A = 1;
  return ((2 * M_PI) * sqrt(pow(a, 3) / (G * M)));
}

// θ = (segundos/ T)* π/180 + arcos(x/r)
static double calcularAnguloDeRecorrido(double seg, double T, Coordenadas inicio) {
  double r = sqrt(pow(inicio.x, 2) + pow(inicio.y, 2));
  double theta = acos(inicio.x / r);
  double angulo_tiempo = (seg / T) * (360 * M_PI / 180);

  if (inicio.x == 0) {
    return 0;
  } else {
    return (angulo_tiempo + theta);
  }
}

// coords = (x = r * cos(θ), y = r * sin(θ))
static Coordenadas calcularCoordenadasFinales(double a, double b, Coordenadas c, double angulo) {

  Coordenadas coords;
  coords.x = ((a/2 * cos(angulo)) + c.x);
  coords.y = ((b/2 * sin(angulo)) + c.y);

  return coords;
}
