# Arduino Library for RV-3028-C7

Supports Micro Crystal [RV-3028-C7](https://www.microcrystal.com/en/products/real-time-clock-rtc/rv-3028-c7/) 
extreme low power RTC module.


## Usage

Search the library using the Library Manager of Arduino IDE, or download it 
directly via GitHub.

Connect an RV-3028-C7 device to your Arduino board according to the datasheet. 
There are three examples that come with the library:

- `SetDateTime`: Configures date and time to the RTC module via the serial 
  console, and then prints the current date and time in ISO 8601 format every 
  second.
- `HourlyAlarmInterrupt`: Sets an hourly alarm at a specific minute, and 
  triggers an interrupt.
- `PeriodicCountdownTimer`: Sets a repeating countdown timer that triggers an 
  interrupt.
- `ProgrammableClockOutput`: Outputs a square wave to trigger interrupts at a 
  programmable clock frequency.

You can find more API functions in `src/RV3028C7.h`, which are pretty much 
self-explanatory if you have read the datasheet.


## Compatibility

This library has been tested on SAMD21 only. However, it should also be 
compatible with any architecture that provides `Wire.h` I<sup>2</sup>C support.


## License

MIT
