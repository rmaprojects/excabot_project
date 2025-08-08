#ifndef TIMER_CONTROL_H
#define TIMER_CONTROL_H
#include "joystick_helper.h"


const int RED = 10;
const int YELLOW = 11;
const int GREEN = 12;

const int BUZZ = 13;


void initTimer();
bool timer(bool isRunning);

void resetTimer();

#endif