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
  //Lanzar mina pin -> 13

  pinMode(12, INPUT);
  // Botones -> L12 y R11
  pinMode(11, INPUT);

  pinMode(10, INPUT);
  //Pausa juego pin -> 10
}

double punteos[5][4] = { { 1, 3, 0, 0 },
                         { 2, 4, 0, 0 },
                         { 3, 5, 0, 0 },
                         { 4, 6, 0, 0 },
                         { 5, 4, 0, 0 } };

int totalpunteo = 0;


byte buffer[8][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

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

int potenciometroVidas = 0;
int potenciometroVelocidad = 0;
int puntaje = 0;
double porcentaje = 0.0;
int vidaInicial = 3;
int vida = 1;
int velocidad = 200;

long int t0 = 0;
long int t1 = 0;
int state = 0;

const unsigned long debounceDelay = 50;
int buttonState = LOW;
int lastButtonState = LOW;

int buttonState12 = LOW;
int lastButtonState12 = LOW;

int buttonState11 = LOW;
int lastButtonState11 = LOW;

int buttonState10 = LOW;
int buttonState10P = LOW;
int lastButtonState10 = LOW;
int lastButtonState10P = LOW;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime12 = 0;
unsigned long lastDebounceTime11 = 0;
unsigned long lastDebounceTime10 = 0;

unsigned long buttonPressStartTime = 0;
unsigned long buttonPressStartTime12 = 0;
unsigned long buttonPressStartTime11 = 0;
unsigned long buttonPressStartTime10 = 0;
unsigned long buttonPressStartTime10P = 0;

void pintarLED(int x, int y) {
  digitalWrite(14 + y, LOW);
  digitalWrite(22 + x, HIGH);
  delayMicroseconds(1100);
  digitalWrite(14 + y, HIGH);
  digitalWrite(22 + x, LOW);
}

int temp1 = 0;

void calcularP() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    totalpunteo = totalpunteo + punteos[i][1];
    Serial.println(totalpunteo);
  }

  for (int j = 0; j < 5; j++) {
    retorno((punteos[j][1] / totalpunteo) * 100);
    punteos[j][2] = temp1;
    Serial.println(punteos[j][2]);
  }
}

void retorno(double porcentaje) {
  if (porcentaje > 0 && porcentaje <= 13) {
    temp1 = 1;
  } else if (porcentaje > 13 && porcentaje <= 25) {
    temp1 = 2;
  } else if (porcentaje > 25 && porcentaje <= 38) {
    temp1 = 3;
  } else if (porcentaje > 38 && porcentaje <= 50) {
    temp1 = 4;
  } else if (porcentaje > 50 && porcentaje <= 53) {
    temp1 = 5;
  } else if (porcentaje > 53 && porcentaje <= 75) {
    temp1 = 6;
  } else if (porcentaje > 75 && porcentaje <= 88) {
    temp1 = 7;
  } else if (porcentaje > 88 && porcentaje <= 100) {
    temp1 = 8;
  }
}

void configuracion() {
  potenciometroVelocidad = map(analogRead(A0), 0, 1024, 0, 8);
  potenciometroVidas = map(analogRead(A1), 0, 1024, 0, 8);
  velocidad = 200 - (potenciometroVelocidad * 15);
  vidaInicial = 3 + potenciometroVidas;

  for (int i = 1; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      if (7 - j < punteos[0][2])
        buffer[j][i] = 1;
      else
        buffer[j][i] = 0;
    }
  }

  for (int i = 4; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      if (7 - j < punteos[1][2])
        buffer[j][i] = 1;
      else
        buffer[j][i] = 0;
    }
  }

  for (int i = 7; i < 9; i++) {
    for (int j = 0; j < 8; j++) {
      if (7 - j < punteos[2][2])
        buffer[j][i] = 1;
      else
        buffer[j][i] = 0;
    }
  }

  for (int i = 10; i < 12; i++) {
    for (int j = 0; j < 8; j++) {
      if (7 - j < punteos[3][2])
        buffer[j][i] = 1;
      else
        buffer[j][i] = 0;
    }
  }

  for (int i = 13; i < 15; i++) {
    for (int j = 0; j < 8; j++) {
      if (7 - j < punteos[4][2])
        buffer[j][i] = 1;
      else
        buffer[j][i] = 0;
    }
  }

  int reading = digitalRead(10);
  if (reading != lastButtonState10P) {
    lastDebounceTime10 = millis();

    if (reading == HIGH) {  //press/hold
      buttonPressStartTime10 = millis();
    }
    if (reading == LOW) {  //release
      buttonPressStartTime10P = millis();
    }
  }

  if ((millis() - lastDebounceTime10) > debounceDelay) {
    if (reading != buttonState10P) {
      buttonState10P = reading;
    }
  }

  if (buttonPressStartTime10 != buttonPressStartTime10P) {
    if (reading == LOW && (buttonPressStartTime10P - buttonPressStartTime10) >= 3000) {
      buttonPressStartTime10P = buttonPressStartTime10;
      delay(100);
      state = 1;
    }
  }
  lastButtonState10P = reading;
  mostrarMatriz();
}

int temp = 0;

void loop() {
  if (temp == 0) {
    calcularP();
    temp++;
  }
  configuracion();
}