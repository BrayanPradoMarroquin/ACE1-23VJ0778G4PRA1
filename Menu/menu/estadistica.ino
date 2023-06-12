int totalpunteo = 0;

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
  if(porcentaje == 0){
    temp1 = 0;
  }else if (porcentaje > 0 && porcentaje <= 13) {
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

void configuracionC() {
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
      cont = 0;
    }
  }
  lastButtonState10P = reading;
  mostrarMatriz();
}