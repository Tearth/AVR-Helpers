#ifndef DS18B20_H
#define DS18B20_H

//Frequency of microcontroller (default is 16MHz)
#define F_CPU 16000000UL

//Configuration of pins
#define DS_PIN PD2
#define DS_PORT PORTD
#define DS_REG DDRD
#define DS_PINREG PIND

#include <stdio.h>
#include <util/delay.h>
#include "Pin.h"
#include "UART.h"

class DS18B20
{
public:
	DS18B20();
	~DS18B20();

	void Init();

	//Resets communication with device
	bool Reset();

	//Reads temperature from sensor. Conversion times:
	// 9 bits resolution - ~100ms
	// 10 bits resolution - ~200ms
	// 11 bits resolution - ~400ms
	// 12 bits resolution - ~750ms
	float GetTemp();

	//Sends single bit to device
	void WriteBit(char bit);

	//Sends single byte to device
	void WriteByte(uint8_t byte);

	//Reads single bit from device
	char ReadBit();

	//Reads single byte from device
	uint8_t ReadByte();

	//Sets temperature resolution (9/10/11/12 bits)
	void SetResolution(uint8_t resolution);
private:
	uint8_t resolution;
};

#endif