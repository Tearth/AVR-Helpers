#include "Headers/Timer.h"

Timer::Timer()
{
	ticks = 0;
}

Timer::~Timer()
{

}

void Timer::Init()
{
	//Set prescaler to 64 and frequency to 16MHz
	TCCR0 |= (1<<CS01) | (1<<CS00);
	
	//Timer overflow enabled
	TIMSK |= (1<<TOIE0);

	//Initial value
	TCNT0 = 6;

	//Enable interrupts
	sei();
}

void Timer::TimerInterrupt()
{
	ticks++;
}

long long int Timer::GetTicks()
{
	return ticks;
}