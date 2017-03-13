#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <string.h>

class UART
{
public:
	UART();
	~UART();

	void Init();

	//Sends single char to the device
	void SendChar(unsigned char c);

	//Sends string to the device (must be ended with \0)
	void SendString(char* string);
private:
};

#endif