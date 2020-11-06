/*
  RV-3028-C7 Hourly Alarm Interrupt Example

  Sets an hourly alarm at a specific minute, and triggers an interrupt.

  Copyright (c) 2020 Macro Yau

  https://github.com/MacroYau/RV-3028-C7-Arduino-Library
*/

#include <RV3028C7.h>

const unsigned int interruptPin = 2; // Connected to pin 2 of RV-3028-C7

RV3028C7 rtc;

bool interruptTriggered = false;

void setup() {
  Serial.begin(9600);
  Serial.println("RV-3028-C7 Alarm Interrupt Example");
  Serial.println();

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), rtcInterrupt, FALLING);

  Wire.begin();

  while (rtc.begin() == false) {
    Serial.println("Failed to detect RV-3028-C7!");
    delay(5000);
  }

  rtc.setDateTimeFromISO8601("2018-01-01T08:00:00"); // Hard-coded for testing
  rtc.synchronize(); // Writes the new date time to RTC

  Serial.print("Start: ");
  Serial.println(rtc.getCurrentDateTime());

  rtc.setHourlyAlarm(/*minute=*/1);
  rtc.enableInterrupt(INTERRUPT_ALARM);
}

void loop() {
  if (interruptTriggered) {
    if (rtc.isInterruptDetected(INTERRUPT_ALARM)) {
      Serial.print("Alarm: ");
      Serial.println(rtc.getCurrentDateTime());
      rtc.clearInterrupt(INTERRUPT_ALARM);
    }
    interruptTriggered = false;
  }
}

void rtcInterrupt() { interruptTriggered = true; }
