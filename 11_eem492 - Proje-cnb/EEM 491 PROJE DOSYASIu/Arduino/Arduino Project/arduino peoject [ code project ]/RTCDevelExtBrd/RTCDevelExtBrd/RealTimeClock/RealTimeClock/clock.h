/*
 * Clock.h
 *
 * Created: 2/11/2012 10:51:31 AM
 *  Author: Mike
 *
 * Version 1.0 of the Clock library used to manage an PCF8583 Clock/Calendar chip.
 *
 * Note: Next version will have conversion methods for string totime/date and time/date to string.
 */ 
#ifndef CLOCK_H_
#define CLOCK_H_

enum { false, true };
typedef uint8_t bool;

#define DeviceAddress  0xA0

#define CNTRL_REG	0x00
#define TIMER_REG	0x07
#define ALARM_REG	0x08
#define CMP_REG		0x0f

#define ENABLE_ALARM	0x04
#define COUNTER			0x80

//Need these for registers 4-6 (Hour, Year/Date, Weekday/Month)
typedef struct Reg4
{
	unsigned h_lsb:		4;
	unsigned h_msb:		2;
	unsigned h_ampm:	1;
	unsigned h_1224:	1;
} Register4Hour;

typedef struct Reg5
{
	unsigned y_unit_days:	4;
	unsigned y_ten_day:		2;
	unsigned y_year:		2;
}Register5Year;

typedef struct  Reg6
{
	unsigned m_unit_months:	4;
	unsigned m_ten_months:	2;
	unsigned m_weekdays:	2;
}Register6Month;

typedef struct Time
{
	char hundreds;
	char seconds;
	char minutes;
	union
	{
		char hours;
		Register4Hour r4;	
	};
} Time;

typedef struct Date
{
	union
	{
		char year;
		Register5Year r5;
	};
	union
	{
		char month;
		Register6Month r6;
	};		
} Date;

void StartCounter(char sb);
void StopCounter();

bool WriteRegister(uint8_t addr, unsigned char cmd);
bool ReadRegister(uint8_t addr, unsigned char* pData);

void SetTime(Time* time, bool isAlarm);
void SetDate(Date* date, bool isAlarm);

bool ReadTime(bool isAlarm);
bool ReadDate(bool isAlarm);

#endif /* CLOCK_H_ */