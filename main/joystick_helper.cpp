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