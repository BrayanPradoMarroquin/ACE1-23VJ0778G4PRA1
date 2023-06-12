#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5

LedControl matriz = LedControl(DIN, CLK, LOAD, 1);

void setup(){
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
  // put your main code here, to run repeatedly:

  //digitalWrite(PIN,HIGH)
  digitalWrite(14 + y, LOW);
  digitalWrite(22 + x, HIGH);
  delay(1);
  digitalWrite(14 + y, HIGH);
  digitalWrite(22 + x, LOW);
}


void configuracion() {
  Serial.begin(9600);
  potenciometroVelocidad = map(analogRead(A0), 0, 1024, 0, 7);
  potenciometroVidas = map(analogRead(A1), 0, 1024, 0, 7);

  for (int i = 1; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      if (7 - j < potenciometroVelocidad)
        buffer[j][i] = 1;
      else
        buffer[j][i] = 0;
    }
  }

  for (int i = 4; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      if (8 - j < potenciometroVidas)
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

void loop(){
  configuracion();
}