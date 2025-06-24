#include "joystick_helper.h"
#include "timer.h"
const int BUZZ = ;
bool isRunning = true;
  
void setup() {
  pinMode(joystickSw, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  initTimer();
  Serial.begin(9600);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BUZZ, LOW);

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

  isRunning = timer(isRunning);
  if (isRunning == false){
    digitalWrite(BUZZ, HIGH);
    Serial.println("Buzz On");
  }

  delay(100);
}
    




