# Modelo de Kepler - Simulación de Ondas Gravitacionales
## Introducción:
El modelo de Kepler se basa en las tres leyes del movimiento planetario formuladas por el astrónomo alemán Johannes Kepler en el siglo XVII. Estas leyes describen el movimiento de los planetas alrededor del Sol y se utilizan ampliamente en la simulación y predicción de órbitas planetarias.

Las tres leyes de Kepler son las siguientes:

1. Primera ley de Kepler, Ley de las órbitas: Cada planeta se mueve alrededor del Sol siguiendo una órbita elíptica, con el Sol en uno de los focos de la elipse. Esta ley establece que las órbitas planetarias no son círculos perfectos, sino elipses con el Sol ubicado en uno de los puntos focales.

2. Segunda ley de Kepler, Ley de las áreas: El radio que une al planeta con el Sol barre áreas iguales en tiempos iguales. Esto significa que los planetas se mueven más rápido cuando están más cerca del Sol (en el perihelio) y más lento cuando están más lejos (en el afelio).

3. Tercera ley de Kepler, Ley de los períodos: El cuadrado del período orbital de un planeta es proporcional al cubo de la longitud semieje mayor de su órbita. En otras palabras, la relación entre el tiempo que tarda un planeta en dar una vuelta completa alrededor del Sol (su período) y la distancia promedio al Sol elevada al cubo es constante para todos los planetas.

Para simular órbitas planetarias utilizando el modelo de Kepler, se deben conocer los parámetros orbitales de un planeta en particular, como su distancia media al Sol, la excentricidad de su órbita y su período orbital. Estos parámetros se utilizan para calcular la trayectoria del planeta en función del tiempo.

Existen varias herramientas y software disponibles que utilizan el modelo de Kepler para simular órbitas planetarias. Estos programas permiten ingresar los parámetros orbitales de un planeta y generan visualizaciones de su movimiento orbital a lo largo del tiempo. Algunos ejemplos populares incluyen programas de astronomía y software de simulación espacial.

En resumen, el modelo de Kepler proporciona un marco matemático para describir y simular las órbitas planetarias en función de las tres leyes de Kepler. Utilizando los parámetros orbitales de un planeta, se puede utilizar este modelo para predecir y representar su movimiento en relación con el Sol.

## Fórmulas Importantes:

1. **Cálculo de la velocidad orbital (v):**
   La velocidad orbital de un planeta en un punto determinado de su órbita se puede calcular utilizando la siguiente fórmula:

   v = √(G * M * ((2 / r) - (1 / a)))

   Donde:
   - G es la constante de gravitación universal.
   - M es la masa del cuerpo central (por ejemplo, el Sol).
   - r es la distancia entre el planeta y el cuerpo central en ese punto de la órbita.
   - a es la longitud del semieje mayor de la órbita elíptica.

2. **Cálculo del período orbital (T):**
   El período orbital de un planeta, es decir, el tiempo que tarda en dar una vuelta completa alrededor del cuerpo central, se puede calcular utilizando la siguiente fórmula:

   T = 2π * √(a³ / (G * M))

   Donde:
   - G es la constante de gravitación universal.
   - M es la masa del cuerpo central.
   - a es la longitud del semieje mayor de la órbita.

3. **Cálculo de la excentricidad (e):**
   La excentricidad de una órbita elíptica se puede calcular utilizando la siguiente fórmula:

   e = √(1 - (b² / a²))

   Donde:
   - a es la longitud del semieje mayor de la órbita.
   - b es la longitud del semieje menor de la órbita.

4. **Cálculo de la distancia al cuerpo central (r):**
La distancia entre el planeta y el cuerpo central en un punto de la órbita se puede calcular utilizando la siguiente fórmula:

   r = a * (1 - e * cos(θ))

   Donde:
   - a es la longitud del semieje mayor de la órbita.
   - e es la excentricidad de la órbita.
   - θ es el ángulo entre la posición del planeta y el perihelio (el punto más cercano al cuerpo central en la órbita).

## Calcular una Elipse:
Para calcular una elipse a partir del perihelio y el afelio de una órbita, se necesita conocer la distancia entre el cuerpo central y los dos puntos extremos de la elipse. Estos puntos extremos son el perihelio y el afelio, y la distancia entre ellos se denomina el eje mayor (a) de la elipse.

El eje mayor (a) se calcula sumando la distancia del perihelio al cuerpo central (r_peri) y la distancia del afelio al cuerpo central (r_afelio):

a = r_peri + r_afelio

La excentricidad (e) de la elipse también es un parámetro importante. Se puede calcular utilizando la fórmula:

e = (r_afelio - r_peri) / (r_afelio + r_peri)

Una vez que se conoce el eje mayor (a) y la excentricidad (e), se puede obtener la longitud del semieje menor (b) utilizando la siguiente fórmula:

b = a * √(1 - e²)

Ahora tienes los parámetros necesarios (a y b) para definir completamente la elipse. Puedes utilizar estos valores para simular y representar la órbita en un sistema de coordenadas adecuado, como un plano cartesiano o un sistema orbital tridimensional.

Es importante tener en cuenta que el cuerpo central debe ubicarse en uno de los focos de la elipse. Además, estas fórmulas asumen una órbita elíptica sin considerar perturbaciones gravitacionales significativas de otros cuerpos celestes. Para una mayor precisión en la simulación, podrías considerar otras correcciones y factores que influyen en las órbitas planetarias.

## Calcular la Posición al Transcurrir un Tiempo X:
Para calcular la posición de un objeto en un modelo de Kepler después de transcurrir x cantidad de segundos, se requiere conocer los siguientes datos: el punto de partida (r_0), el punto del perihelio (r_peri), el punto del afelio (r_afelio), y la masa del cuerpo central (M). Además, asumiremos que el objeto está en una órbita elíptica alrededor del cuerpo central.

1. Calcula el eje mayor (a) de la elipse utilizando la fórmula:
   a = (r_peri + r_afelio) / 2

2. Calcula la excentricidad (e) de la elipse utilizando la fórmula:
   e = (r_afelio - r_peri) / (r_afelio + r_peri)

3. Calcula la longitud del semieje menor (b) de la elipse utilizando la fórmula:
   b = a * √(1 - e²)

4. Calcula el período orbital (T) del objeto utilizando la tercera ley de Kepler:
   T = 2π * √(a³ / (G * M))
   Donde G es la constante de gravitación universal.

5. Calcula la velocidad media (v_media) del objeto en la órbita utilizando la fórmula:
   v_media = 2π * a / T

6. Calcula el ángulo (θ) que el objeto ha recorrido después de transcurrir x segundos utilizando la fórmula:
   θ = 2π * x / T

7. Calcula la distancia radial (r) desde el cuerpo central al objeto en ese momento utilizando la fórmula:
   r = a * (1 - e²) / (1 + e * cos(θ))

8. Calcula la posición (x, y) del objeto en coordenadas polares utilizando la distancia radial (r) y el ángulo (θ).

   - Coordenada x: x = r * cos(θ)
   - Coordenada y: y = r * sin(θ)

Estos cálculos te permitirán determinar la posición del objeto en el modelo de Kepler después de transcurrir x segundos desde el punto de partida. Recuerda que estas fórmulas asumen una órbita elíptica idealizada y no consideran perturbaciones significativas de otros cuerpos celestes. Para una mayor precisión, pueden requerirse ajustes adicionales en la simulación.