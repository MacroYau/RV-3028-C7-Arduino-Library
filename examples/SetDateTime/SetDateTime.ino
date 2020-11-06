/*
  RV-3028-C7 Set Date Time Example

  Configures date and time to the RTC module via the serial console, and then
  prints the current date and time in ISO 8601 format every second.

  Copyright (c) 2020 Macro Yau

  https://github.com/MacroYau/RV-3028-C7-Arduino-Library
*/

#include <RV3028C7.h>

RV3028C7 rtc;

void setup() {
  Serial.begin(9600);
  Serial.println("RV-3028-C7 Set Date Time Example");
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

  // Since ISO 8601 does not include day of week, the RTC cannot keep track of it unless input separately
  Serial.print("Enter day of week (0 for Sunday, 1 for Monday, and so on): ");
  while (Serial.available() == false);
  if (Serial.available() > 0) {
    int dayOfWeek = Serial.parseInt();
    Serial.println(dayOfWeek);
    rtc.setDateTimeComponent(DATETIME_DAY_OF_WEEK, dayOfWeek);
    rtc.synchronize();
  }

  Serial.println();
}

void loop() {
  Serial.println(rtc.getCurrentDateTime());
  delay(1000);
}
