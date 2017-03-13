#ifndef RTC_H
#define RTC_H

#include <stdlib.h>
#include <avr/io.h>

struct DateTime
{
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Day;
	uint8_t DayOfWeek;
	uint8_t Month;
	uint8_t Year;
};

class RTC
{
public:
	RTC();
	~RTC();

	void InitRTC();

	//Starts communication with device
	int StartTransmission();

	//Stops communication with device
	void StopTransmission();

	//Sends byte to device
	int WriteByte(uint8_t data);

	//Receives single byte from device
	uint8_t ReceiveByte(uint8_t ACK);

	//Gets date and time from device
	DateTime* GetDateTime();

	//Sets date and time in device
	void SetDateTime(DateTime dateTime);

	//Gets temperature from internal sensor
	float GetTemperature();

private:
	uint8_t bcd2Dec(uint8_t bd);
	uint8_t dec2Bcd(uint8_t dec);
};

#endif