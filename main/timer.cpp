#include <LowPower.h>
#include "timer.h"

unsigned long timerMillis = 0;

void initTimer() {
    timerMillis = millis();
}

bool timer(bool isRunning){
// Logika timer
  if (isRunning) {
    unsigned long currentMillis = millis();
    if (currentMillis < 20000) { // 0-20 detik: Hijau menyala
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
      Serial.println("Green ON");
    } else if (currentMillis < 40000) { // 20-40 detik: Kuning menyala
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(RED, LOW);
      Serial.println("Yellow ON");
    } else if (currentMillis < 60000) { // 40-60 detik: Merah menyala
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, HIGH);
      Serial.println("Red ON");
    } else { // Timer selesai
      isRunning = false;
      digitalWrite(RED, LOW); // Matikan semua lampu saat selesai
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
      Serial.println("Timer finished!");
    }
  }
  return isRunning;
}