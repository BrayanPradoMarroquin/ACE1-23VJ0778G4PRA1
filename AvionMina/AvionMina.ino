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
  pinMode(13, INPUT);
}

void pintarLED(int x, int y) {
  digitalWrite(14 + y, LOW);
  digitalWrite(22 + x, HIGH);
  delayMicroseconds(1100);
  digitalWrite(14 + y, HIGH);
  digitalWrite(22 + x, LOW);
}


byte buffer[8][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int xAvion = 0;
int yAvion = 0;
int xMina = -1;
int yMina = -1;
void pintarAvion() {
  if (buffer[yAvion + 1][xAvion + 2] == 1) {
    yAvion = yAvion - 2;
    xAvion = xAvion - 2;
  } else {
    buffer[yAvion][xAvion] = 1;
    buffer[yAvion + 1][xAvion] = 1;
    buffer[yAvion + 1][xAvion + 1] = 1;
    buffer[yAvion + 1][xAvion + 2] = 1;
  }
}

void borrarAvion() {
  buffer[yAvion][xAvion] = 0;
  buffer[yAvion + 1][xAvion] = 0;
  buffer[yAvion + 1][xAvion + 1] = 0;
  buffer[yAvion + 1][xAvion + 2] = 0;
}

void mina() {
  if (xMina == -1 && yMina == -1) {
    xMina = xAvion;
    yMina = yAvion + 2;
    buffer[yMina][xMina] = 1;
  }
}

void moverMina() {
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

long int t0 = 0;
long int t1 = 0;
const unsigned long debounceDelay = 50;
int buttonState = LOW;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;

void loop() {
  int reading = digitalRead(13);
  borrarAvion();
  t1 = millis();
  if ((t1 - t0) >= 150) {
    t0 = millis();
    xAvion++;
    if (xAvion == 16) {
      xAvion = 0;
      yAvion++;
    }
  }
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        mina();
      }
    }
  }
  lastButtonState = reading;

  pintarAvion();
  if (yMina != -1) {
    moverMina();
  }
  mostrarMatriz();
}
