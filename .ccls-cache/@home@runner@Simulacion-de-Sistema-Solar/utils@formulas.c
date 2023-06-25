#include <math.h>
#include "../classes/coordenadas.c"

//d=Sqrt((x2-x1)^2 + (y2-y1)^2)
static double calcularDistancia(Coordenadas a, Coordenadas b){
  return sqrt(pow(b.x- a.x,2) + pow(b.y-a.y,2));
}

// a=(r_peri + r_afelio)/2
static double calcularEjeMayor(double r_perihelio, double r_afelio){
  return (r_perihelio +r_afelio)/2;
}

// e= (r-afelio - r_peri)/(r_afelio + r_peri)
static double calcularExcentricidad(double r_perihelio, double r_afelio){
  return ((r_afelio - r_perihelio/ (r_afelio + r_perihelio)));
}

//b=a* sqrt(1-e^2)
static double calcularEjeMenor (double a, double e){
  return (a*sqrt(1-pow(e,2)));
}

// T = 2π * √(a³ / (G * M))
static double calcularPeriodoOrbital(double a, double M) {
  const double G = 0.0000000000667;
  return ((2 * M_PI) * sqrt(pow(a, 3) / (G * M)));
}

// v_media = 2π * a / T
static double calcularVelocidadMedia(double a, double T) {
  return ((2 * M_PI) * (a / T));
}

// θ = 2π * x / T
static double calcularAnguloDeRecorrido(double seg, double T) {
  return ((2 * M_PI) * (seg / T));
}

// r = a * (1 - e²) / (1 + e * cos(θ))
static double calcularDistanciaRadial(double a, double e, double ang) {
  return a * (1 - pow(e, 2)) / (1 + (e * cos(ang)));
}

// coords = (x = r * cos(θ), y = r * sin(θ))
static Coordenadas calcularCoordenadasFinales(double r, double ang) {
  
  Coordenadas coords;
  coords.x = r * cos(ang);
  coords.y = r * sin(ang);
  
  return coords;
}

