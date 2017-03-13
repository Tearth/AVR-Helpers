# AVR Helpers
Set of useful classes for AVR platform. It's a part of my old AVR project (LCD display with a temperature sensor and a clock) for ATmega8. Note that this is not the complete library (a lot of hard-coded values in the implementation of classes), but it will help with writing an own implementation. In the future, I will try to rewrite this to true library.

# Supported devices and features:
* Display: HD44780
* Real-time clock: DS3231 I2C
* Temperature sensor: DS18B20
* UART
* Timer