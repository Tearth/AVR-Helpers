#include "Headers/Display.h"

Display::Display()
{

}

Display::~Display()
{

}

void Display::Pulse()
{
	SetPinState(E, &PORTB, LOW);
	_delay_us(1);

	SetPinState(E, &PORTB, HIGH);
	_delay_us(1);

	SetPinState(E, &PORTB, LOW);
	_delay_us(100);
}

void Display::Write4Bytes(uint8_t data)
{
	SetPinState(D7, &PORTB, (PIN_STATE)((data >> 3) & 0x01));
	SetPinState(D6, &PORTB, (PIN_STATE)((data >> 2) & 0x01));
	SetPinState(D5, &PORTD, (PIN_STATE)((data >> 1) & 0x01));
	SetPinState(D4, &PORTD, (PIN_STATE)((data) & 0x01));

	Pulse();
}

void Display::Write8Bytes(uint8_t data)
{
	Write4Bytes(data >> 4);
	Write4Bytes(data & 0x0F);
}

void Display::Init()
{
	_delay_ms(100);

	//Set Register Select to output LOW
	SetPinMode(RS, &DDRD, OUTPUT);
	SetPinState(RS, &PORTD, LOW);

	//Set Enabled to output LOW
	SetPinMode(E, &DDRB, OUTPUT);
	SetPinState(E, &PORTB, LOW);

	//Set data pins to output LOW
	SetPinMode(D4, &DDRD, OUTPUT);
	SetPinMode(D5, &DDRD, OUTPUT);
	SetPinMode(D6, &DDRB, OUTPUT);
	SetPinMode(D7, &DDRB, OUTPUT);

	SetPinState(D4, &PORTD, LOW);
	SetPinState(D5, &PORTD, LOW);
	SetPinState(D6, &PORTB, LOW);
	SetPinState(D7, &PORTB, LOW);

	//Start transmission
	//Call Function Set
	Write4Bytes(0x03);
	_delay_ms(5);

	Write4Bytes(0x03);
	_delay_us(100);

	Write4Bytes(0x03);
	_delay_us(100);

	//Call true Function Set and reset to 4bit mode
	Write4Bytes(0x02);
	_delay_us(100);

	//We are in 4bit mode
	//Set number of lines (2) and font size(5x7)
	Write8Bytes(0x28);
	_delay_us(60);
	
	//Display on/off control
	Write8Bytes(0x08);
	_delay_us(60);
	
	//Clear Display
	Write8Bytes(0x01);
	_delay_ms(5);

	//Entry Mode Set (curor increment from left to right, display without shift)
	Write8Bytes(0x06);
	_delay_us(100);

	//End of initialization
}

void Display::Clear()
{
	SetPinState(RS, &PORTD, LOW);
	_delay_ms(10);

	//0x01 - clear command
	Write8Bytes(0x01);
	_delay_ms(5);
}

void Display::WriteChar(char c)
{
	SetPinState(RS, &PORTD, HIGH);
	_delay_us(500);

	Write8Bytes(c);
	_delay_us(500);
}

void Display::WriteString(const char* string)
{
	while(*string != '\0')
	{
		WriteChar(*string);
		string++;
	}
}

void Display::SetDDRAM(uint8_t address)
{
	SetPinState(RS, &PORTD, LOW);
	_delay_ms(10);

	Write8Bytes((0x01 << 7) | address);
	_delay_ms(5);
}

void Display::SetLine(uint8_t line)
{
	if(line == 1)
		SetDDRAM(0x0);
	else if(line == 2)
		SetDDRAM(0x40);
}

void Display::Cursor(bool show, bool blink)
{
	SetPinState(RS, &PORTD, LOW);
	_delay_ms(10);

	Write8Bytes(0xC | (show << 1) | blink);
	_delay_us(100);
}