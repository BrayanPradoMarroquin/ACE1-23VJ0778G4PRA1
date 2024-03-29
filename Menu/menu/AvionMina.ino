#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5

void pintarAvion() {
  if (buffer[yAvion + 1][xAvion + 2] == 1) {
    yAvion = yAvion - 2;
    xAvion = xAvion - 2;
    vida--;
    if (vida == 0) {
      state = 0;
      xAvion = 0;
      yAvion = 0;
      punteos[Partida%5][1] = punteoPartida;
    }
  } else {
    buffer[yAvion][xAvion] = 1;
    buffer[yAvion + 1][xAvion % 16] = 1;
    buffer[yAvion + 1][(xAvion + 1) % 16] = 1;
    buffer[yAvion + 1][(xAvion + 2) % 16] = 1;
  }
}

void borrarAvion() {
  buffer[yAvion][xAvion] = 0;
  buffer[yAvion + 1][xAvion % 16] = 0;
  buffer[yAvion + 1][(xAvion + 1) % 16] = 0;
  buffer[yAvion + 1][(xAvion + 2) % 16] = 0;
}

void mina() {
  if (xMina == -1 && yMina == -1) {
    xMina = xAvion + 1;
    yMina = yAvion + 2;
    buffer[yMina][xMina] = 1;
  }
}

void moverMina() {
  if (buffer[yMina + 1][xMina] == 1) {
    borrarEdificio(xMina);
    punteoPartida++;
    if(punteoPartida % 5 == 0 && punteoPartida != 0){
      vida++;
    }
    edificioscolocados--;
    if (edificioscolocados == 0) {
      nivel++;
      cantidadEdificios++;
      state = 5;
    }
    buffer[yMina][xMina] = 0;
    xMina = -1;
    yMina = -1;
  } else {
    if (yMina != -1) {
      buffer[yMina][xMina] = 0;
      if (yMina < 7) {
        yMina++;
        buffer[yMina][xMina] = 1;
      } else {
        xMina = -1;
        yMina = -1;
      }
    }
  }
}

void mostrarMatriz() {
  // Con driver
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      matriz.setLed(0, i, j, buffer[i][j] == 1 ? true : false);
  // Sin driver
  for (int k = 0; k < 3; k++)
    for (int i = 0; i < 8; i++)
      for (int j = 8; j < 16; j++)
        if (buffer[i][j] == 1)
          pintarLED(j - 8, i);
        else
          delayMicroseconds(50);
}
