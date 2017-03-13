#include "Headers/Pin.h"

void SetPinMode(uint8_t pin, volatile uint8_t* regOut, INPUT_MODE mode)
{
	if(mode == OUTPUT)
		*regOut |= (1 << pin);
	else if(mode == INPUT)
		*regOut &= ~(1 << pin);
}

void SetPinState(uint8_t pin, volatile uint8_t* port, PIN_STATE state)
{
	if(state == HIGH)
		*port |= (1 << pin);
	else if(state == LOW)
		*port &= ~(1 << pin);
}

PIN_STATE GetPinState(uint8_t pin, volatile uint8_t pinReg)
{
	return pinReg & (1 << pin) ? HIGH : LOW;
}