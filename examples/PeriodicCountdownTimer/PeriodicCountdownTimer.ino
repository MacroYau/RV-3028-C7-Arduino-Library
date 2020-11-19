/*
  RV-3028-C7 Periodic Countdown Timer Example

  Sets a repeating countdown timer that triggers an interrupt.

  Copyright (c) 2020 Macro Yau

  https://github.com/MacroYau/RV-3028-C7-Arduino-Library
*/

#include <RV3028C7.h>

const unsigned int interruptPin = 2; // Connected to pin 2 of RV-3028-C7

RV3028C7 rtc;

bool interruptTriggered = false;

void setup() {
  Serial.begin(9600);
  Serial.println("RV-3028-C7 Countdown Timer Example");
  Serial.println();

  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), timerExpired, FALLING);

  Wire.begin();

  while (rtc.begin() == false) {
    Serial.println("Failed to detect RV-3028-C7!");
    delay(5000);
  }

  // Refer to page 63 of Application Manual to configure timer value and timer
  // clock frequency
  rtc.setPeriodicCountdownTimer(/*timerValue=*/5, /*frequency=*/TIMER_1HZ,
                                /*repeat=*/true);
  rtc.enableInterrupt(INTERRUPT_PERIODIC_COUNTDOWN_TIMER);
  rtc.startPeriodicCountdownTimer();

  Serial.print("Countdown Timer Started: ");
  Serial.println(rtc.getCurrentDateTime());
}

void loop() {
  if (interruptTriggered) {
    if (rtc.isInterruptDetected(INTERRUPT_PERIODIC_COUNTDOWN_TIMER)) {
      Serial.print("Countdown Timer Expired: ");
      Serial.println(rtc.getCurrentDateTime());
      rtc.clearInterrupt(INTERRUPT_PERIODIC_COUNTDOWN_TIMER);
    }
    interruptTriggered = false;
  }
}

void timerExpired() { interruptTriggered = true; }
