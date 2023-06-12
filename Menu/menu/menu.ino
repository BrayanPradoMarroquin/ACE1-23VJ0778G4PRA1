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

double punteos[5][4] = { { 1, 0, 0, 0 },
                         { 2, 0, 0, 0 },
                         { 3, 0, 0, 0 },
                         { 4, 0, 0, 0 },
                         { 5, 0, 0, 0 } };

long int t0 = 0;
long int t1 = 0;
long int t3 = 0;  // 1s avion desenso
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
int velocidad = 150;
int direccion = 1;
int aumentar = -4;
int cantidadEdificios = 3;
int edificioscolocados = 0;
int nivel = 1;
int puntaje = 0;
double porcentaje = 0.0;
int cont = 0;

int temp = 0;

int Partida = -1; //Numero de partidas jugadas
int punteoPartida = 0; //Punteo por partida

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
  if ((t1 - t0) >= velocidad) {
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

/// CABIO DE VIDAS Y VELOCIDAD (CONFIGURACION)
int potenciometroVidas = 0;
int potenciometroVelocidad = 0;

void configuracion() {
  potenciometroVelocidad = map(analogRead(A0), 0, 1024, 0, 8);
  potenciometroVidas = map(analogRead(A1), 0, 1024, 0, 8);
  velocidad = 200 - (potenciometroVelocidad * 15);
  vidaInicial = 3 + potenciometroVidas;

  for (int i = 1; i < 3; i++) {  //horizontal
    for (int j = 0; j < 16; j++) {
      if (j <= potenciometroVelocidad)
        buffer[i][j] = 1;
      else
        buffer[i][j] = 0;
    }
  }

  for (int i = 4; i < 6; i++) {
    for (int j = 0; j < 16; j++) {
      if (j <= potenciometroVidas)
        buffer[i][j] = 1;
      else
        buffer[i][j] = 0;
    }
  }

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
      buttonPressStartTime10P = buttonPressStartTime10;
      delay(100);
      state = 1;
    }
  }
  lastButtonState10P = reading;
  mostrarMatriz();
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
    }
    if (yMina != -1) {
      moverMina();
    }
  }
  if (millis() - t3 >= 1000) {
    t3 = millis();
    yAvion++;
    delayMicroseconds(0.5);
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
      punteos[Partida%5][1] = punteoPartida;
      delay(100);
      state = 1;
    }
    if (reading == LOW && (buttonPressStartTime10P - buttonPressStartTime10) >= 2000 && (buttonPressStartTime10P - buttonPressStartTime10) < 3000) {
      t3 = millis();
      buttonPressStartTime10P = buttonPressStartTime10;
      state = 2;
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
    int reading11 = digitalRead(11);
    int reading10 = digitalRead(13);
    if (reading != lastButtonState12) {
      lastDebounceTime12 = millis();
    }
    if (reading11 != lastButtonState11) {
      lastDebounceTime11 = millis();
    }

    if ((millis() - lastDebounceTime12) > debounceDelay) {
      if (reading != buttonState12) {
        buttonState12 = reading;
        if (buttonState12 == HIGH) {
          vida = vidaInicial;
          punteoPartida = 0;
          Partida++;
          limpiarEdificios();
          cantidadEdificios = 3;
          nivel = 1;
          t3 = millis();
          delay(50);
          state = 5;
        }
      }
    }

    if ((millis() - lastDebounceTime11) > debounceDelay) {
      if (reading11 != buttonState11) {
        buttonState11 = reading11;
        if (buttonState11 == HIGH) {
          delay(100);
          state = 4;
        }
      }
    }

  if ((millis() - lastDebounceTime10) > debounceDelay) {
      if (reading10 != buttonState10) {
        buttonState10 = reading10;
        if (buttonState10 == HIGH) {
          delay(100);
          state = 6;
        }
      }
    }

    lastButtonState11 = reading11;
    lastButtonState12 = reading;
    lastButtonState10 = reading10;
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
    //---------------------------------------------------
  } else if (state == 4) {
    if (temp == 0) {
      limpiarBuffer();
      mostrarMatriz();
      temp++;
    } else {
      configuracion();
    }
    //---------------------------------------------------
  } else if (state == 5) {  //show level number
    mostrarNiveles();
    matriz.clearDisplay(0);
    if (millis() - t3 >= 2000) {
      borrarAvion();
      posicionRandom();  //crear nuevos edificios
      xAvion = 0;
      yAvion = 0;
      t3 = millis();
      state = 2;
    }
  } else if (state == 6) {
    if (cont == 0) {
      calcularP();
      cont++;
    }
    configuracionC();
  }
}
