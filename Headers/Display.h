//Frequency of microcontroller (default is 16MHz)
#define F_CPU 16000000UL

#ifndef DISPLAY_H
#define DISPLAY_H

//Configuration of pins
#define D4 PD6
#define D5 PD7
#define D6 PB0
#define D7 PB2
#define E  PB1
#define RS PD5

#include <util/delay.h>
#include "Pin.h"

class Display
{
public:
	Display();
	~Display();

	void Init();

	//Pulses the Enable pin
	void Pulse();

	//Sends 4 bytes to the device
	void Write4Bytes(uint8_t data);

	//Sends 8 bytes (two packets of 4 bytes)
	void Write8Bytes(uint8_t data);

	//Clears display
	void Clear();

	//Writes single char at display
	void WriteChar(char c);

	//Writes string at display (must be ended with \0)
	void WriteString(const char* string);

	//Sets cursor position to specific address
	void SetDDRAM(uint8_t address);

	//Sets cursor at begin of specific line
	void SetLine(uint8_t line);

	//Sets cursor parameters
	void Cursor(bool show, bool blink);
private:
};

#endif