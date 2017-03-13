#include "Headers/UART.h"

UART::UART()
{

}

UART::~UART()
{

}

void UART::Init()
{
	//Set baud rate (16 bit register)
	UBRRH = (51>>8);
	UBRRL = 51;
	
	//Enable RX/TX
	UCSRB = (1<<TXEN)|(1<<RXEN);

	//Synchronous mode. 8 bits for data
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void UART::SendChar(unsigned char c)
{
	while (!( UCSRA & (1<<UDRE)));
	
	UDR = c;
}

void UART::SendString(char* string)
{
	while(*string != '\0')
	{
		SendChar(*string);
		string++;
	}
}