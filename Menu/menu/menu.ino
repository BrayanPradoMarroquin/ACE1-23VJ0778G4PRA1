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

int xAvion = 0;
int yAvion = 0;
int xMina = -1;
int yMina = -1;

int state = 0;
int vidaInicial = 3;
int vida = 1;
int t = 0;
int velocidad = 200;
int direccion = 1;
int aumentar = -4;
int cantidadEdificios = 3;
int edificioscolocados = 0;

int punteoGlobal = 0;
int punteos[5][2] = { { 0, 0 },
                      { 0, 0 },
                      { 0, 0 },
                      { 0, 0 },
                      { 0, 0 } };

void limpiarBuffer() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++)
      buffer[i][j] = 0;
  }
}

void frase() {
  Serial.begin(9600);
  int reading = digitalRead(13);
  int reading10 = digitalRead(10);
  t1 = millis();
  if ((t1 - t0) >= 150) {
    t0 = millis();
    aumentar = aumentar + direccion;
  }

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (reading10 != lastButtonState10P) {
    lastDebounceTime10 = millis();

    if (reading10 == HIGH) {  //press/hold
      Serial.println("testing1");
      buttonPressStartTime10 = millis();
    }
    if (reading == LOW) {  //release
      Serial.println("testing2");
      buttonPressStartTime10P = millis();
    }
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        if (direccion == 1) {
          direccion = -1;
        } else {
          direccion = 1;
        };
      }
    }
  }

  Serial.println(millis() - buttonPressStartTime10);
  Serial.println(buttonPressStartTime10);
  Serial.println(buttonPressStartTime10P);
  Serial.println("  ");
  if (buttonPressStartTime10 != buttonPressStartTime10P) {
    if (reading10 == LOW && (buttonPressStartTime10P - buttonPressStartTime10) >= 2000) {
      delay(100);
      buttonPressStartTime10P = buttonPressStartTime10;
      state = 1;
    }
  }
  lastButtonState10P = reading10;
  lastButtonState = reading;
  setMatriz();
  delay(2);
  mostrarMatriz();
  delay(1);
}

void iniciarJuego() {
  int reading = digitalRead(13);
  borrarAvion();
  t1 = millis();
  if ((t1 - t0) >= velocidad) {
    t0 = millis();
    xAvion++;
    if (xAvion == 16) {
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
  mostrarMatriz();
  delayMicroseconds(0.5);
}

void pausarJuego() {
  mostrarVidas();
  Serial.begin(9600);
  delay(100);
  int reading = digitalRead(10);
  if (reading != lastButtonState10P) {
    lastDebounceTime10 = millis();

    if (reading == HIGH) {  //press/hold
      Serial.println("testing1");
      buttonPressStartTime10 = millis();
    }
    if (reading == LOW) {  //release
      Serial.println("testing2");
      buttonPressStartTime10P = millis();
    }
  }

  if ((millis() - lastDebounceTime10) > debounceDelay) {
    if (reading != buttonState10P) {
      buttonState10P = reading;
    }
  }
  Serial.println(millis() - buttonPressStartTime10);
  Serial.println(buttonPressStartTime10);
  Serial.println(buttonPressStartTime10P);
  Serial.println("  ");

  if (buttonPressStartTime10 != buttonPressStartTime10P) {
    if (reading == LOW && (buttonPressStartTime10P - buttonPressStartTime10) >= 3000) {
      limpiarEdificios();
      buttonPressStartTime10P = buttonPressStartTime10;
      delay(100);
      state = 1;
    }
    if (reading == LOW && (buttonPressStartTime10P - buttonPressStartTime10) >= 2000 && (buttonPressStartTime10P - buttonPressStartTime10) < 3000) {
      state = 2;
      buttonPressStartTime10P = buttonPressStartTime10;
    }
  }
  lastButtonState10P = reading;
}

void loop() {
  //Frase Inicial
  if (state == 0) {
    frase();
  }
  //Mostrar Menu
  if (state == 1) {
    limpiarBuffer();
    delay(10);
    mostrarMenu();
    int reading = digitalRead(12);
    if (reading != lastButtonState12) {
      lastDebounceTime12 = millis();
    }

    if ((millis() - lastDebounceTime12) > debounceDelay) {
      if (reading != buttonState12) {
        buttonState12 = reading;
        if (buttonState12 == HIGH) {
          vida = vidaInicial;
          Serial.println("ttttttttt: ");
          Serial.println(edificioscolocados);
          Serial.println(cantidadEdificios);
          posicionRandom();  //crear nuevos edificios
          delay(100);
          state = 2;
        }
      }
    }
    lastButtonState12 = reading;
    //---------------------------------------------------
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
    //---------------------------------------------------
  } else if (state == 3) {
    pausarJuego();
  }

  /*nivel = 10;
  mostrarNiveles();
  matriz.clearDisplay(0);*/
}
