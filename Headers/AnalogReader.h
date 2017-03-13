#ifndef ADC_H
#define ADC_H

#include "Pin.h"

class AnalogReader
{
public:
	AnalogReader();
	~AnalogReader();

	void Init();

	//Reads the value from an analog pin
	uint16_t Read(uint8_t pin);
private:
};

#endif