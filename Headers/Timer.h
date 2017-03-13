#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h> 

class Timer
{
public:
	Timer();
	~Timer();

	void Init();

	//Updates ticks counter, call this method in ISR(TIMER0_OVF_vect)
	void TimerInterrupt();

	//Returns ticks count
	long long int GetTicks();
private:
	long long int ticks;
};

#endif