#ifndef PIN_H
#define PIN_H

#include <avr/io.h>

enum INPUT_MODE
{
	INPUT = 0,
	OUTPUT = 1
};

enum PIN_STATE
{
	LOW = 0,
	HIGH = 1
};

//Sets the pin mode (INPUT/OUTPUT)
void SetPinMode(uint8_t pin, volatile uint8_t* regOut, INPUT_MODE mode);

//Sets the pin state (LOW/HIGH), only digital
void SetPinState(uint8_t pin, volatile uint8_t* port, PIN_STATE state);

//Gets the pin state (LOW/HIGH), only digital
PIN_STATE GetPinState(uint8_t pin, volatile uint8_t pinReg);

#endif