#include "Headers/AnalogReader.h"

AnalogReader::AnalogReader()
{

}

AnalogReader::~AnalogReader()
{

}

void AnalogReader::Init()
{
	//ADC Control and Status Register
	ADCSRA =  (1<<ADEN)		//Enable ADC
			| (1<<ADPS0)	//Set prescaler to 128
			| (1<<ADPS1)
			| (1<<ADPS2);

	//ADC Multiplexer Selection Register
	//Ref voltage to Vcc
	ADMUX =   (1<<REFS0); 
}

uint16_t AnalogReader::Read(uint8_t pin)
{
	SetPinMode(pin, &DDRC, INPUT);

	ADMUX |= pin;

	//ADSC: run conversion
	ADCSRA |= (1<<ADSC); 

	//Wait for finish
	while(ADCSRA & (1<<ADSC)); 

	ADMUX &= 0xF0;

	return ADC;
}