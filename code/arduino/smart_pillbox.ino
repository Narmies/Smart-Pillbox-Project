#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// PIN TANIMLARI
#define SOLENOID_1 25
#define SOLENOID_2 26
#define LIMIT_1    32
#define LIMIT_2    33
#define BUZZER     27
#define BUTTON     14

// ÖRNEK İLAÇ SAATLERİ
int pill1_hour = 9;
int pill1_min  = 0;

int pill2_hour = 21;
int pill2_min  = 0;

bool pill1_taken = false;
bool pill2_taken = false;

void setup() {
  Serial.begin(115200);

  pinMode(SOLENOID_1, OUTPUT);
  pinMode(SOLENOID_2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LIMIT_1, INPUT_PULLUP);
  pinMode(LIMIT_2, INPUT_PULLUP);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(SOLENOID_1, LOW);
  digitalWrite(SOLENOID_2, LOW);
  digitalWrite(BUZZER, LOW);

  if (!rtc.begin()) {
    Serial.println("RTC bulunamadi!");
    while (1);
  }

  Serial.println("Smart Pill Box basladi");
}

void loop() {
  DateTime now = rtc.now();

  // BÖLME 1
  if (now.hour() == pill1_hour && now.minute() == pill1_min && !pill1_taken) {
    openCompartment(1);
  }

  // BÖLME 2
  if (now.hour() == pill2_hour && now.minute() == pill2_min && !pill2_taken) {
    openCompartment(2);
  }

  checkLids();
  delay(1000);
}

void openCompartment(int id) {
  digitalWrite(BUZZER, HIGH);

  if (id == 1) {
    digitalWrite(SOLENOID_1, HIGH);
  } else {
    digitalWrite(SOLENOID_2, HIGH);
  }

  Serial.print("Bolme ");
  Serial.print(id);
  Serial.println(" acildi");
}

void checkLids() {
  if (digitalRead(LIMIT_1) == LOW && !pill1_taken) {
    pill1_taken = true;
    digitalWrite(SOLENOID_1, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.println("Ilac 1 alindi");
  }

  if (digitalRead(LIMIT_2) == LOW && !pill2_taken) {
    pill2_taken = true;
    digitalWrite(SOLENOID_2, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.println("Ilac 2 alindi");
  }
}

