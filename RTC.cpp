#include "Headers/RTC.h"

RTC::RTC()
{

}

RTC::~RTC()
{

}

void RTC::InitRTC()
{
	TWSR = 0x00;
	TWBR = 0x48;
}

int RTC::StartTransmission()
{
	TWCR = 0;
	TWCR = (1<<TWINT) |( 1<<TWSTA) | (1<<TWEN);

	while (! (TWCR & (1<<TWINT)));
	
	return TWSR;
}

void RTC::StopTransmission()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while (! (TWCR & (1<<TWSTO)));
}

int RTC::WriteByte(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while (! (TWCR & (1<<TWINT)));

	return TWSR;
}

uint8_t RTC::ReceiveByte(uint8_t ACK)
{
	TWCR = (1<<TWINT) | (ACK<<TWEA) | (1<<TWEN);
	while (! (TWCR & (1<<TWINT)));

	return TWDR;
}

DateTime* RTC::GetDateTime()
{
	DateTime* dateTime = (DateTime*)malloc(sizeof(DateTime));

	StartTransmission();
	WriteByte(0xD0);
	WriteByte(0x00);
	StartTransmission();
	WriteByte(0xD1);
	dateTime->Second = bcd2Dec(ReceiveByte(1));
	dateTime->Minute = bcd2Dec(ReceiveByte(1));
	dateTime->Hour = bcd2Dec(ReceiveByte(1));
	dateTime->DayOfWeek = bcd2Dec(ReceiveByte(1));
	dateTime->Day = bcd2Dec(ReceiveByte(1));
	dateTime->Month = bcd2Dec(ReceiveByte(1));
	dateTime->Year = bcd2Dec(ReceiveByte(0));
	StopTransmission();

	return dateTime;
}

void RTC::SetDateTime(DateTime dateTime)
{
	StartTransmission();
	WriteByte(0xD0);
	WriteByte(0x00);
	WriteByte(dec2Bcd(dateTime.Second));
	WriteByte(dec2Bcd(dateTime.Minute));
	WriteByte(dec2Bcd(dateTime.Hour));
	WriteByte(dec2Bcd(dateTime.DayOfWeek));
	WriteByte(dec2Bcd(dateTime.Day));
	WriteByte(dec2Bcd(dateTime.Month));
	WriteByte(dec2Bcd(dateTime.Year));
	StopTransmission();
}

uint8_t RTC::bcd2Dec(uint8_t bcd)
{
	return ((bcd/16 * 10) + (bcd % 16));
}

uint8_t RTC::dec2Bcd(uint8_t dec)
{
	return ((dec/10 * 16) + (dec % 10));
}

float RTC::GetTemperature()
{
	StartTransmission();
	WriteByte(0xD0);
	WriteByte(0x11);
	StartTransmission();
	WriteByte(0xD1);

	uint8_t h = ReceiveByte(1);
	uint8_t l = ReceiveByte(0);
	StopTransmission();

	return (float)h + (0.5f * ((l >> 7) & 0x01)) + (0.25f * ((l >> 6) & 0x01));
}