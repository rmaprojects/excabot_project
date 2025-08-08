#include "joystick_helper.h"


JoystickMovement getjoystickState() {

  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);

  Serial.println(xValue);
  Serial.println(yValue);

  if (xValue < 200) return RIGHT;
  if (xValue > 800) return LEFT;
  if (yValue < 200) return UP;
  if (yValue > 800) return DOWN;

  

  return IDLE;
}

onJoystickClicked joystickcolour(int counter) {
  if (digitalRead(joystickSw) == LOW) {
    // Nyalakan LED sesuai urutan
    if (counter == 1) {
      return HIJAU;
    } else if (counter == 2) {
      return KUNING;
    } else if (counter == 3) {
      return MERAH;
    }
  }
}

