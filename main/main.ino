#include "joystick_helper.h"

void setup() {
  pinMode(joystickSw, INPUT_PULLUP);
  Serial.begin(9600);
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
  Serial.println();

  delay(100);
}





