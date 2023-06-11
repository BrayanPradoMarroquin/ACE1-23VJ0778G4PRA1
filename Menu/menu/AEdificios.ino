#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5


int tamanio = 3;
                       //{ x, y }
int edificios[16][2] = { { 0, 0 },
                         { 1, 3 },
                         { 2, 3 },
                         { 3, 0 },
                         { 4, 0 },
                         { 5, 0 },
                         { 6, 0 },
                         { 7, 0 },
                         { 8, 4 },
                         { 9, 0 },
                         { 10, 0 },
                         { 11, 0 },
                         { 12, 0 },
                         { 13, 0 },
                         { 14, 0 },
                         { 15, 0 },
                        };

void pintarLED(int x, int y) {
    digitalWrite(14  + y, LOW);
    digitalWrite(22 + x, HIGH);
    delayMicroseconds(1100);
    digitalWrite(14  + y, HIGH);
    digitalWrite(22 + x, LOW);
}

void borrarEdificio(int x) {
  int y = edificios[x][1];
  for(int i = 0; i < y; i++){
    buffer[7-i][x] = 0;
  }
  edificios[x][1] = 0;
}

void crearedificios() {
  //CON DRIVER
  for(int k = 0; k < 16; k++){
    if (edificios[k][1] != 0){
      for(int i = 0; i < edificios[k][1]; i++){
        buffer[7 - i][edificios[k][0]] = 1;
      }
    }
  }
}




