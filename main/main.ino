#include "joystick_helper.h"
<<<<<<< HEAD
int counter = 1;

=======
#include "timer.h"
const int BUZZ = ;
bool isRunning = true;
  
>>>>>>> 1f1db757e71bac26856506f10dd55a35532cdec1
void setup() {
  pinMode(joystickSw, INPUT_PULLUP);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  initTimer();
  Serial.begin(9600);
<<<<<<< HEAD
  pinMode(ledHijau, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledMerah, OUTPUT);

  // Matikan semua LED dulu
    digitalWrite(ledHijau, HIGH);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, LOW);
=======
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BUZZ, LOW);

>>>>>>> 1f1db757e71bac26856506f10dd55a35532cdec1
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
  if (digitalRead(joystickSw) == LOW) {
    delay(100); // debounce
    counter++;
    if (counter > 3) counter = 1;

    onJoystickClicked warna = joystickcolour(counter);

    // Matikan semua LED dulu
    digitalWrite(ledHijau, LOW);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledMerah, LOW);

    if (warna == GREEN) digitalWrite(ledHijau, HIGH);
    else if (warna == YELLOW) digitalWrite(ledKuning, HIGH);
    else if (warna == RED) digitalWrite(ledMerah, HIGH);

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
    




