#include <Servo.h>

#include "joystick_helper.h"
#include "timer.h"

int counter = 1;
bool isRunning = true;
bool isGame = true;

//Define servo pins
#define GRAPPLERSERVOPIN 2
#define BASESERVOPIN 4
#define ARMSERVOPIN 3
#define LIFTSERVOPIN 5

#define PBRESET 51
#define PBGAME 49
#define PBEXCA 47

//Servos
Servo grapplerServo;
Servo baseServo;
Servo armServo;
Servo liftServo;

int grapplerPos = 50;
int baseServoPos = 60;
int armServoPos = 21;
int liftServoPos = 5;

void setup() {

  pinMode(joystickSw, INPUT_PULLUP);

  //Servos
  grapplerServo.attach(GRAPPLERSERVOPIN);
  baseServo.attach(BASESERVOPIN);
  armServo.attach(ARMSERVOPIN);
  liftServo.attach(LIFTSERVOPIN);

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

  pinMode(PBRESET, INPUT_PULLUP);
  pinMode(PBGAME, INPUT_PULLUP);
  pinMode(PBEXCA, INPUT_PULLUP);
}


void loop() {
  int buttonState = digitalRead(joystickSw);
  int resetState = digitalRead(PBRESET);
  int gameState = digitalRead(PBGAME);
  int excaState = digitalRead(PBEXCA);

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
      }else if(counter == 2){
        liftServoPos -= 7;
      }
      Serial.println("LEFT");
      break;
    case RIGHT:
      if(counter == 1){
        baseServoPos += 15;
      }else if(counter == 3){
        grapplerPos += 7;
      }else if(counter == 2){
        liftServoPos += 7;
      }
      Serial.println("RIGHT");
      break;
  }
  
  grapplerPos = constrain(grapplerPos, 0, 100);
  baseServoPos = constrain(baseServoPos, 0, 200);
  armServoPos = constrain(armServoPos, 0, 180);
  liftServoPos = constrain(liftServoPos, 0, 180);

  grapplerServo.write(grapplerPos);
  baseServo.write(baseServoPos);
  armServo.write(armServoPos);
  liftServo.write(liftServoPos);

  Serial.println(grapplerPos);
  Serial.println(baseServoPos);
  Serial.println(armServoPos);
  Serial.println(liftServoPos);


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
  
  if(isGame){
    isRunning = timer(isRunning);
    if (isRunning == false){
      digitalWrite(BUZZ, HIGH);
      Serial.println("Buzz On");
    }
    Serial.println("Mode Game");
  }else{
    Serial.println("Mode Biasa");
  }

  //tess=====================================
    // Tombol Game: aktifkan mode dengan timer
  if (gameState == LOW) {
    delay(50);
    if (digitalRead(PBGAME) == LOW) {
      isGame = true;
      isRunning = true; // mulai ulang timer
      resetTimer();
      Serial.println("Mode: Game (Timer Aktif)");
    }
  }

  // Tombol Exca: mode bebas (tanpa timer)
  if (excaState == LOW) {
    delay(50);
    if (digitalRead(PBEXCA) == LOW) {
      isGame = false;
      Serial.println("Mode: Bebas (Timer OFF)");
      digitalWrite(BUZZ, LOW); // Matikan buzzer jika nyala
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    }
  }

  // Tombol Reset: kembalikan posisi servo
  if (resetState == LOW) {
    delay(50);
    if (digitalRead(PBRESET) == LOW) {
      Serial.println("Reset posisi servo");
      
      // Reset semua posisi servo
      grapplerPos = 50;
      baseServoPos = 60;
      armServoPos = 21;
      liftServoPos = 5;

      grapplerServo.write(grapplerPos);
      baseServo.write(baseServoPos);
      armServo.write(armServoPos);
      liftServo.write(liftServoPos);

      isRunning = true; // Reset timer
      digitalWrite(BUZZ, LOW); // Matikan buzzer
    }
  }

  delay(100);
}