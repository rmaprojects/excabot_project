#include "joystick_helper.h"
int counter = 1;

void setup() {
  pinMode(joystickSw, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledMerah, OUTPUT);

  // Matikan semua LED dulu
    digitalWrite(ledHijau, HIGH);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, LOW);
}


void loop() {
  int buttonState = digitalRead(joystickSw);

  JoystickMovement joystickState = getjoystickState();

  switch(joystickState) {
    case IDLE:
      Serial.println("IDLE");
      break;
    case UP:
      Serial.println("UP");
      break;
    case DOWN:
      Serial.println("DOWN");
      break;
    case LEFT:
      Serial.println("LEFT");
      break;
    case RIGHT:
      Serial.println("RIGHT");
      break;
  }

  if (buttonState == HIGH) {
    Serial.println("OFF");
  } else {
    Serial.println("ON");
    
  }
  if (digitalRead(joystickSw) == LOW) {
    delay(100); // debounce
    counter++;
    if (counter > 3) counter = 1;

    onJoystickClicked warna = joystickcolour(counter);

    // Matikan semua LED dulu
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, LOW);

    if (warna == GREEN) digitalWrite(ledHijau, HIGH);
    else if (warna == YELLOW) digitalWrite(ledKuning, HIGH);
    else if (warna == RED) digitalWrite(ledMerah, HIGH);

    // Tunggu tombol dilepas (biar 1 klik = 1 efek)
    while (digitalRead(joystickSw) == LOW);
    Serial.println(counter);
  }
  
  Serial.println();

  delay(100);
}





