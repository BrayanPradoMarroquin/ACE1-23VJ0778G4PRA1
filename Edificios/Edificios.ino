#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5

LedControl matriz = LedControl(DIN, CLK, LOAD, 1);

void setup() {
  matriz.shutdown(0, false);
  matriz.setIntensity(0, 8);
  for (int i = 14; i <= 21; i++)
    pinMode(i, OUTPUT);
  for (int i = 22; i <= 29; i++)
    pinMode(i, OUTPUT);
  for (int i = 14; i <= 21; i++)
    digitalWrite(i, HIGH);
  for (int i = 22; i <= 29; i++)
    digitalWrite(i, LOW);
}

byte buffer[8][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


int tamanio = 3;

int edificios[16][2] = { { 1, 3 },
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
                         { 0, 0 },
                        };

void pintarLED(int x, int y) {
    digitalWrite(14  + y, LOW);
    digitalWrite(22 + x, HIGH);
    delayMicroseconds(1100);
    digitalWrite(14  + y, HIGH);
    digitalWrite(22 + x, LOW);
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

  void pintaredificio(){
    //CON DRIVER
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        matriz.setLed(0, i, j, buffer[i][j] == 1 ? true : false);
      }
    }
      
    //SIN DRIVER
    for(int k = 0; k < 3; k++){
      for(int i = 0; i < 8; i++){
        for(int j = 8; j < 16; j++)
          if(buffer[i][j] == 1){
            pintarLED(j - 8, i);
          }else{
            delayMicroseconds(50);
          }
      }
    }
  }

void loop() {
  crearedificios();
  pintaredificio();
  delayMicroseconds(0.5);
}
