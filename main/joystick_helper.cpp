#include "joystick_helper.h"


JoystickMovement getjoystickState() {

  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);

  if (xValue < 3) return LEFT;
  if (xValue > 1000) return RIGHT;
  if (yValue < 3) return UP;
  if (yValue > 1000) return DOWN;

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

