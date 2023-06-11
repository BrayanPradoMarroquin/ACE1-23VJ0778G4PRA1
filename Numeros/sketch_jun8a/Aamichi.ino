
#include "LedControl.h"

#define DIN 7
#define CLK 6
#define LOAD 5

LedControl matriz = LedControl(DIN, CLK, LOAD, 1);
void setup() {
  // put your setup code here, to run once:
  matriz.shutdown(0, false);
  matriz.setIntensity(0, 8);

  //_________________
  for (int i = 14; i <= 21; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 22; i <= 29; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 14; i <= 21; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 22; i <= 29; i++) {
    digitalWrite(i, LOW);
  }
  /* for (int i = 0; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 14; i <= 21; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 0; i <= 7; i++) {
    pinMode(i, HIGH);
  }
  for (int i = 14; i <= 21; i++) {
    pinMode(i, LOW);
  }*/
  //pinMode(13, INPUT);
}
int aumentar = 0;
long int t0 = millis();
long int t1 = millis();
bool direccion = true;
int numeros = 1;

byte matrizO[8][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

//_________________Sección de matrices con numeros_______________________
int cero[8][16] = {

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }
};

int uno[8][16] = {

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int dos[8][16] = {

  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//tRES
int tres[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//cuatro
int cuatro[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }
};
//Cinco
int cinco[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//seis
int seis[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//siete
int siete[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//ocho
int ocho[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//nuevo
int nueve[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//diez
int diez[8][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
//M_______________Menu_______________
int menu[8][16] = {
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }
};
//___________________________________________________
void pintarLED(int x, int y) {
  // put your main code here, to run repeatedly:

  //digitalWrite(PIN,HIGH)
  digitalWrite(14 + y, LOW);
  digitalWrite(22 + x, HIGH);
  delay(1);
  digitalWrite(14 + y, HIGH);
  digitalWrite(22 + x, LOW);
}
int pos2 = 0;

void pintarMatriz() {
  //Con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, matrizO[i][j] == 1 ? true : false);
    }
  }
  //_____Sin driver

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (matrizO[i][j] == 1) {
        pintarLED(j, i);

      } else {
        delayMicroseconds(200);
      }
    }
  }
}
/*
  ___________________Metodos para mostras los numeros___________________________________

*/
void mostrarCero() {
  //Mostrar 0 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, cero[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 0 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (cero[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//
void mostrarUno() {
  //Mostrar 1 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, uno[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 1 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (uno[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para mostra el numero dos
void mostrarDos() {
  //Mostrar 1 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, dos[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 1 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (dos[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el tres
void mostrarTres() {
  //Mostrar 3 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, tres[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 3 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (tres[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el cuatro
void mostrarCuatro() {
  //Mostrar 4 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, cuatro[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 4 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (cuatro[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el cinco
void mostrarCinco() {
  //Mostrar 5 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, cinco[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 5 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (cinco[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el seis
void mostrarSeis() {
  //Mostrar 6 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, seis[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 6 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (seis[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el siete
void mostrarSiete() {
  //Mostrar 7 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, siete[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 7 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (siete[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el ocho
void mostrarOcho() {
  //Mostrar 8 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, ocho[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 8 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (ocho[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el nueve
void mostrarNueve() {
  //Mostrar 9 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, nueve[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 1 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (nueve[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//Metodo para motrar el diez
void mostrarDiez() {
  //Mostrar 1 con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, diez[i][j] == 1 ? true : false);
    }
  }
  //Mostrar 1 sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (diez[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}  //_____________Mostrar Menu_______________

void mostrarMenu() {
  //Mostrar menu con driver
  for (int i = 0; i < 8; i++) {
    for (int j = 8; j < 16; j++) {
      matriz.setLed(0, i, j - 8, menu[i][j] == 1 ? true : false);
    }
  }
  //Mostrar menu sin driver
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int residuo = 80;

      if (menu[i][j] == 1) {
        pintarLED(j, i);
      }
    }
  }
}
//_________Vidas____________________
int vida = 0;
int t = 0;
void mostrarVidas() {
  if (vida == 0) {
    if (t >= 0 && t < 20) {
      mostrarCero();
      t++;
    } else if (t >= 20 && t < 30) {
      pintarMatriz();
      t++;
    } else {
      mostrarMenu();
      matriz.clearDisplay(0);
    }
  } else if (vida == 1) {
    mostrarUno();
  } else if (vida == 2) {
    mostrarDos();
  } else if (vida == 3) {
    mostrarTres();
  } else if (vida == 4) {
    mostrarCuatro();
  } else if (vida == 5) {
    mostrarCinco();
  } else if (vida == 6) {
    mostrarSeis();
  } else if (vida == 7) {
    mostrarSiete();
  } else if (vida == 8) {
    mostrarOcho();
  } else if (vida == 9) {
    mostrarNueve();
  } else if (vida == 10) {
    mostrarDiez();
  }
}
/*
   __________Mostrar la cantidad de nivles ___________________
*/
int nivel = 0;
void mostrarNiveles() {
  if (nivel == 0) {
    mostrarCero();
  } else if (nivel == 1) {
    mostrarUno();
  } else if (nivel == 2) {
    mostrarDos();
  } else if (nivel == 3) {
    mostrarTres();
  } else if (nivel == 4) {
    mostrarCuatro();
  } else if (nivel == 5) {
    mostrarCinco();
  } else if (nivel == 6) {
    mostrarSeis();
  } else if (nivel == 7) {
    mostrarSiete();
  } else if (nivel == 8) {
    mostrarOcho();
  } else if (nivel == 9) {
    mostrarNueve();
  } else if (nivel == 10) {
    mostrarDiez();
  }
}
//____________Loops____________________

void loop() {
  nivel = 10;
  mostrarNiveles();
  matriz.clearDisplay(0);
}
