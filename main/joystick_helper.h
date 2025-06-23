#ifndef JOYSTICK_HELPER_H
#define JOYSTICK_HELPER_H
#include <Arduino.h>

const int yAxis = A2;
const int xAxis = A3;

const int joystickSw = 12;

typedef enum {
  IDLE, // 0
  RIGHT, // 1
  LEFT, // 2
  UP, // 3
  DOWN  // 4
} JoystickMovement;

JoystickMovement getjoystickState();

#endif
