#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5

LedControl matriz = LedControl(DIN, CLK, LOAD, 1);

void setup() {
  //avionmina.ino
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

long int t0 = 0;
long int t1 = 0;
const unsigned long debounceDelay = 50;
int buttonState = LOW;
int lastButtonState = LOW;

int buttonState12 = LOW;
int lastButtonState12 = LOW;

int buttonState11 = LOW;
int lastButtonState11 = LOW;

int buttonState10 = LOW;
int lastButtonState10 = LOW;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime12 = 0;
unsigned long lastDebounceTime11 = 0;
unsigned long lastDebounceTime10 = 0;

int xAvion = 0;
int yAvion = 0;
int xMina = -1;
int yMina = -1;
int state = 1;

int vidaInicial = 3;
int vida = 1;
int t = 0;
int velocidad = 200;

void iniciarJuego(){
  int reading = digitalRead(13);
  borrarAvion();
  t1 = millis();
  if ((t1 - t0) >= velocidad) {
    t0 = millis();
    xAvion++;
    if(xAvion == 16){
      xAvion = 0;
      yAvion++;
    }
    if (yMina != -1) {
    moverMina();
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
  
  //Edificio.ino
  crearedificios();
  mostrarMatriz();
  delayMicroseconds(0.5);
}

void pausarJuego(){
  mostrarVidas();
}

void loop() {
  //Mostrar Menu
  if (state == 1) {
    mostrarMenu();
    int reading = digitalRead(12);
    if (reading != lastButtonState12) {
      lastDebounceTime12 = millis();
    }

    if ((millis() - lastDebounceTime12) > debounceDelay) {
      if (reading != buttonState12) {
        buttonState12 = reading;
        if (buttonState12 == HIGH) {
          state = 2;
          vida = vidaInicial;
        }
      }
    }
    lastButtonState12 = reading;
  } else if (state == 2) {
    iniciarJuego();
    int reading = digitalRead(10);
    if (reading != lastButtonState10) {
      lastDebounceTime10 = millis();
    }

    if ((millis() - lastDebounceTime10) > debounceDelay) {
      if (reading != buttonState10) {
        buttonState10 = reading;
        if (buttonState10 == HIGH) {
          state = 3;
        }
      }
    }
    lastButtonState10 = reading;
  } else if(state == 3){
    pausarJuego();
  }

  /*nivel = 10;
  mostrarNiveles();
  matriz.clearDisplay(0);*/
}
