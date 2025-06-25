#include <Servo.h>

#include "joystick_helper.h"
#include "timer.h"

int counter = 1;
bool isRunning = true;

//Define grappler
#define GRAPPLERSERVOPIN 2
#define BASESERVOPIN 5

//Servos
Servo grapplerServo;
Servo baseServo;
int grapplerPos = 50;
int baseServoPos = 0;

void setup() {

  pinMode(joystickSw, INPUT_PULLUP);

  grapplerServo.attach(GRAPPLERSERVOPIN);
  baseServo.attach(BASESERVOPIN);

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
      Serial.println(grapplerServo.read());
      break;
    case UP:
      Serial.println("UP");
      break;
    case DOWN:
      Serial.println("DOWN");
      break;
    case LEFT:
      grapplerPos -= 5;
      baseServoPos -= 15;
      Serial.println("LEFT");
      Serial.println(grapplerServo.read());
      break;
    case RIGHT:
      grapplerPos += 5;
      baseServoPos += 15;
      Serial.println("RIGHT");
      Serial.println(grapplerServo.read());
      break;
  }

  grapplerPos = constrain(grapplerPos, 0, 100);
  baseServoPos = constrain(baseServoPos, 0, 200);

  grapplerServo.write(grapplerPos);
  baseServo.write(baseServoPos);
  Serial.println(grapplerPos);
  Serial.println(baseServoPos);


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
  
  Serial.println();

  isRunning = timer(isRunning);
  if (isRunning == false){
    digitalWrite(BUZZ, HIGH);
    Serial.println("Buzz On");
  }

  delay(100);
}
    




