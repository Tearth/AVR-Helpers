#include "Headers/DS18B20.h"

DS18B20::DS18B20()
{
	//Set default resolution to 9
	SetResolution(9);
}

DS18B20::~DS18B20()
{

}

void DS18B20::Init()
{
	
}

bool DS18B20::Reset()
{
	bool presence = false;

	SetPinMode(DS_PIN, &DS_REG, OUTPUT);
	SetPinState(DS_PIN, &DS_PORT, LOW);

	_delay_us(500);
	
	SetPinMode(DS_PIN, &DS_REG, INPUT);

	_delay_us(30);

	if(GetPinState(DS_PIN, DS_PINREG) == LOW)
		presence = true;

	_delay_us(500);

	return presence;
}

float DS18B20::GetTemp()
{
	Reset();
	WriteByte(0xCC);
	WriteByte(0x44);
	
	if(resolution == 9) _delay_ms(100);
	else if(resolution == 10)  _delay_ms(200);
	else if(resolution == 11)  _delay_ms(400);
	else if(resolution == 12)  _delay_ms(750);

	Reset();
	WriteByte(0xCC);
	WriteByte(0xBE);

	uint8_t t1 = ReadByte();
	uint8_t t2 = ReadByte();

	Reset();

	float result = (float)(t1 + (t2 * 256)) / 16;

	return result;
}


void DS18B20::WriteBit(char bit)
{
	SetPinMode(DS_PIN, &DS_REG, OUTPUT);
	SetPinState(DS_PIN, &DS_PORT, LOW);

	_delay_us(5);

	if(bit == 1)
		SetPinState(DS_PIN, &DS_PORT, HIGH);

	_delay_us(80);
	
	SetPinMode(DS_PIN, &DS_REG, INPUT);
	SetPinState(DS_PIN, &DS_PORT, LOW);
}

void DS18B20::WriteByte(uint8_t byte)
{
	for(int i=0; i<8; i++)
	{
		WriteBit((byte >> i) & 0x01);
	}

	_delay_us(20);
}

char DS18B20::ReadBit()
{
	SetPinMode(DS_PIN, &DS_REG, OUTPUT);
	SetPinState(DS_PIN, &DS_PORT, LOW);

	_delay_us(15);
	
	SetPinState(DS_PIN, &DS_PORT, LOW);
	SetPinMode(DS_PIN, &DS_REG, INPUT);

	PIN_STATE status = GetPinState(DS_PIN, DS_PINREG);

	return status == HIGH ? 1 : 0;
}

uint8_t DS18B20::ReadByte()
{
	uint8_t result = 0;
	for(int i=0; i<8; i++)
	{
		bool bit = ReadBit();
		result |= bit << i;

		_delay_us(15);
	}

	return result;
}

void DS18B20::SetResolution(uint8_t resolution)
{
	uint8_t memRes = resolution - 9;
	this.resolution = resolution;

	Reset();
	WriteByte(0xCC);
	WriteByte(0x4E);
	WriteByte(0xFF);
	WriteByte(0xFF);
	WriteByte((memRes << 5) | 0x01f);
	
	Reset();
}