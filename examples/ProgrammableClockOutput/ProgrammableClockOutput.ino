/*
  RV-3028-C7 Programmable Clock Output Example

  Outputs a square wave to trigger interrupts at a programmable clock frequency.

  Copyright (c) 2020 Macro Yau

  https://github.com/MacroYau/RV-3028-C7-Arduino-Library
*/

#include <RV3028C7.h>

const unsigned int interruptPin = 2; // Connected to pin 1 of RV-3028-C7

RV3028C7 rtc;

bool interruptTriggered = false;
unsigned int tickCounter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("RV-3028-C7 Programmable Clock Output Example");
  Serial.println();

  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onTick, FALLING);

  Wire.begin();

  while (rtc.begin() == false) {
    Serial.println("Failed to detect RV-3028-C7!");
    delay(5000);
  }

  rtc.disableClockOutput();
  delay(1000);

  rtc.enableClockOutput(CLKOUT_1HZ); // 1 Hz clock output
}

void loop() {
  if (interruptTriggered) {
    Serial.print("Tick: ");
    Serial.println(rtc.getCurrentDateTime());

    interruptTriggered = false;
    tickCounter++;

    if (tickCounter >= 30) {
      // Disables clock output after 30 rising edges
      rtc.disableClockOutput();
    }
  }
}

void onTick() { interruptTriggered = true; }
