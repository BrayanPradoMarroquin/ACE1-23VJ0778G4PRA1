#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5


int tamanio = 3;
//{ x, y }
int edificios[16][2] = {
  { 0, 0 },
  { 1, 0 },
  { 2, 0 },
  { 3, 0 },
  { 4, 0 },
  { 5, 0 },
  { 6, 0 },
  { 7, 0 },
  { 8, 0 },
  { 9, 0 },
  { 10, 0 },
  { 11, 0 },
  { 12, 0 },
  { 13, 0 },
  { 14, 0 },
  { 15, 0 },
};

void limpiarEdificios() {
  for (int i = 0; i < 16; i++) {
      edificios[i][1] = 0;
  }
  edificioscolocados = 0;
}
void posicionRandom() {
  Serial.println("xxxxx");
  Serial.println(edificioscolocados);
  Serial.println(cantidadEdificios);
  while (edificioscolocados < cantidadEdificios) {
    randomSeed(millis());            // Inicializa la semilla aleatoria con un valor analógico
    int posRandmon = random(0, 15);  // Genera un número aleatorio entre 0 y 99e
    delayMicroseconds(500);

    randomSeed(millis() + 1);
    int altRandom = random(1, 4);
    delayMicroseconds(500);

    if (edificios[posRandmon][1] == 0) {
      edificios[posRandmon][1] = altRandom;
      edificioscolocados++;
      Serial.println(edificioscolocados);
      Serial.println(posRandmon);
      Serial.println(altRandom);
      Serial.println();
    }
  }
  crearedificios();
}

void borrarEdificio(int x) {
  int y = edificios[x][1];
  for (int i = 0; i < y; i++) {
    buffer[7 - i][x] = 0;
  }
  edificios[x][1] = 0;
}

void crearedificios() {
  //CON DRIVER
  for (int k = 0; k < 16; k++) {
    if (edificios[k][1] != 0) {
      for (int i = 0; i < edificios[k][1]; i++) {
        buffer[7 - i][edificios[k][0]] = 1;
      }
    }
  }
}
