/*
 * RealTimeClock.c
 *
 * Created: 2/10/2012 11:17:26 PM
 *  Author: Mike
 */ 
#ifndef FCPU
#define F_CPU 8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "i2cmaster.h"
#include "clock.h"

void pci_init();
void io_init();

void SetClockModeAlarm();
void SetTimeModeAlarm();
void SetAlarmTimeNodeAlarm();

ISR(PCINT1_vect)
{
	PORTB = (1<<PB5);	
}

int main(void)
{
	unsigned char dummy;
	bool line = false;
		
    i2c_init();   // init I2C interface
	
	io_init();
	
	StopCounter();
	
	//Pin change interrupt init
	pci_init();
	
	//uncomment the one of the following
	//SetClockModeAlarm();
	SetTimerModeAlarm();
	//SetAlarmTimerAlarm();
				
	StartCounter(0x04);
	
	bool done = false;
	
	sei();
	
	while(1)
	{
  		ReadTime(false);
		if (!done)
		{	
			ReadTime(true);
			done = true;
		}	  
		
		_delay_ms(100);
	}  
}

void io_init() 
{
	DDRB = (1<<PB5);
	DDRC |= (1<<PC4) | (1<<PC5);
}

void pci_init()
{
	PCIFR = (1<<PCIF1);
	PCMSK1 = (1<<PCINT8);
	PCICR = (1<<PCIE1);
}

void SetClockModeAlarm() 
{
	Time now;
	Date date;
	
	WriteRegister(ALARM_REG, 0xb0);
	
	date.year = 0x12;
	date.month = 0x02;
	SetDate(&date, false);
	SetDate(&date, true);
	
	now.hundreds = 0x00;
	now.seconds = 0x00;
	now.minutes = 0x13;
	now.hours = 0x08;
	now.r4.h_1224 = 1;
	SetTime(&now, false);
	
	now.hundreds = 0x50;
	now.seconds = 0x02;
	SetTime(&now, true);
}

void SetTimerModeAlarm()
{
	WriteRegister(ALARM_REG, 0x89);
	WriteRegister(TIMER_REG, 0x00);
}

void SetAlarmTimerAlarm()
{
	WriteRegister(ALARM_REG, 0xc2);
	WriteRegister(CMP_REG, 0x3);	
}
