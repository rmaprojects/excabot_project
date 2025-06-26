#include <Servo.h>

#include "joystick_helper.h"
#include "timer.h"

int counter = 1;
bool isRunning = true;

//Define servo pins
#define GRAPPLERSERVOPIN 2
#define BASESERVOPIN 5
#define ARMSERVOPIN 3

//Servos
Servo grapplerServo;
Servo baseServo;
Servo armServo;

int grapplerPos = 50;
int baseServoPos = 0;
int armServoPos = 21;

void setup() {

  pinMode(joystickSw, INPUT_PULLUP);

  //Servos
  grapplerServo.attach(GRAPPLERSERVOPIN);
  baseServo.attach(BASESERVOPIN);
  armServo.attach(ARMSERVOPIN);

  //LED Timer
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  initTimer();

  Serial.begin(9600);

  //LED Joystick
  pinMode(ledHijau, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledMerah, OUTPUT);
}


void loop() {
  int buttonState = digitalRead(joystickSw);

  JoystickMovement joystickState = getjoystickState();

  switch(joystickState) {
    case IDLE:
      Serial.println("IDLE");
      break;
    case UP:
      if(counter == 2){
        armServoPos += 7;
      }
      Serial.println("UP");
      break;
    case DOWN:
      if(counter == 2){
        armServoPos -= 7;
      }
      Serial.println("DOWN");
      break;
    case LEFT:
      if(counter == 1){
        baseServoPos -= 15;
      }else if(counter == 3){
        grapplerPos -= 7;
      }
      Serial.println("LEFT");
      break;
    case RIGHT:
      if(counter == 1){
        baseServoPos += 15;
      }else if(counter == 3){
        grapplerPos += 7;
      }
      Serial.println("RIGHT");
      break;
  }
  
  grapplerPos = constrain(grapplerPos, 0, 100);
  baseServoPos = constrain(baseServoPos, 0, 200);
  armServoPos = constrain(armServoPos, 0, 180);

  grapplerServo.write(grapplerPos);
  baseServo.write(baseServoPos);
  armServo.write(armServoPos);

  Serial.println(grapplerPos);
  Serial.println(baseServoPos);
  Serial.println(armServoPos);


  if (buttonState == HIGH) {
    Serial.println("OFF");
  } else {
    Serial.println("ON");
    
  }

  if (digitalRead(joystickSw) == LOW) {
    delay(50); // debounce
    counter++;
    if (counter > 3) counter = 1;

    onJoystickClicked warna = joystickcolour(counter);

    // Matikan semua LED dulu
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, LOW);

    if (warna == HIJAU) digitalWrite(ledHijau, HIGH);
    else if (warna == KUNING) digitalWrite(ledKuning, HIGH);
    else if (warna == MERAH) digitalWrite(ledMerah, HIGH);

    // Tunggu tombol dilepas (biar 1 klik = 1 efek)
    while (digitalRead(joystickSw) == LOW);
    Serial.println(counter);
  }
  
  isRunning = timer(isRunning);
  if (isRunning == false){
    digitalWrite(BUZZ, HIGH);
    Serial.println("Buzz On");
  }

  delay(100);
}