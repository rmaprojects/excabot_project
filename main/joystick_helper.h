#ifndef JOYSTICK_HELPER_H
#define JOYSTICK_HELPER_H
#include <Arduino.h>

const int yAxis = A0;
const int xAxis = A1;

const int joystickSw = 5;
const int ledHijau = 2;
const int ledKuning = 3;
const int ledMerah = 4;


typedef enum {
  IDLE, // 0
  RIGHT, // 1
  LEFT, // 2
  UP, // 3
  DOWN  // 4
} JoystickMovement;

typedef enum {
  HIJAU,
  KUNING,
  MERAH
} onJoystickClicked;

JoystickMovement getjoystickState();
onJoystickClicked joystickcolour(int counter);

#endif
