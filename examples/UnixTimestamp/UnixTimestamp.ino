/*
  RV-3028-C7 Unix Timestamp Example

  Configures date and time in ISO 8601 format to the RTC module via the serial 
  console, and then prints the current Unix timestamp every second.

  Copyright (c) 2020 Macro Yau

  https://github.com/MacroYau/RV-3028-C7-Arduino-Library
*/

#include <RV3028C7.h>

RV3028C7 rtc;

void setup() {
  Serial.begin(9600);
  Serial.println("RV-3028-C7 Unix Timestamp Example");
  Serial.println();

  Wire.begin();

  while (rtc.begin() == false) {
    Serial.println("Failed to detect RV-3028-C7!");
    delay(5000);
  }

  Serial.print("Enter current date and time in ISO 8601 format: "); // e.g., 2018-01-01T08:00:00
  while (Serial.available() == false);
  if (Serial.available() > 0) {
    String dateTime = Serial.readString();
    Serial.println(dateTime);
    rtc.setDateTimeFromISO8601(dateTime);
    rtc.synchronize(); // Writes the new date time to RTC
  }

  Serial.println();
}

void loop() {
  Serial.println(rtc.getCurrentDateTime());
  Serial.print(F("Unix timestamp: "));
  Serial.println(rtc.getUnixTimestamp());
  delay(1000);
}
