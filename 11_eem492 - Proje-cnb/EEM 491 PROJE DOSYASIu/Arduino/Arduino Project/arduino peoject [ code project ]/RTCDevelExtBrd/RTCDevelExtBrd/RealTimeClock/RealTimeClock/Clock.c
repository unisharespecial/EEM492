/*
 * Clock.c
 *
 * Created: 2/11/2012 3:18:19 PM
 * Author: Mike Hankey
 * 
 */ 

#include <avr/io.h>
#include "i2cmaster.h"
#include "clock.h"

volatile Time _current_time;
volatile Date _current_date;

volatile uint8_t _current_control_reg;
volatile uint8_t _current_alarm_reg;

/// <summary>
///	StartCounter - Starts the counter.
/// </summary>   
void StartCounter(char sb)
{
	WriteRegister(CNTRL_REG, sb);
}

/// <summary>
///	StopCounter - Stops the counter and resets divider.
/// </summary>   
void StopCounter()
{
	WriteRegister(CNTRL_REG, 0x00);	
}

/// <summary>
///	WriteRegister - Write an 8-bit value to the addr specified.
/// </summary>   
/// <param name="addr"> uint8_t register address</param>
/// <param name="data"> unsigned char - character to write to register</param>
/// <returns>bool - write status</returns>
bool WriteRegister(uint8_t addr, unsigned char data)
{
	bool status;
    
	status = i2c_start(DeviceAddress+I2C_WRITE);       // set device address and write mode
	if ( !status )
	{
		i2c_write(addr); 
		i2c_write(data);
	}		
	i2c_stop();                              // set stop condition = release bus
	
	return status;
}

/// <summary>
///	ReadRegister - Reads an 8-bit value from the addr specified.
/// </summary>   
/// <param name="addr"> uint8_t register address</param>
/// <param name="data"> unsigned char* - Pointer to storage for result</param>
/// <returns>bool - read status</returns>
bool ReadRegister(uint8_t addr, unsigned char* pData)
{
    bool status;
    
	status = i2c_start(DeviceAddress+I2C_WRITE);       // set device address and write mode
	if ( !status ) 
	{
		i2c_write(addr); 
		i2c_rep_start(DeviceAddress+I2C_READ);        // set device address and read mode
		*(pData) = i2c_readNak();                       //  "    "    "    "     "    3
	}	
	i2c_stop();                              // set stop condition = release bus
	
	return status;	
}

/// <summary>
/// SetTime - Sets either the Clock or Alarm time based on value of isAlarm.
/// </summary>
/// <param name="time">Time* - pointer to the Time structure</param>
/// <param name="isAlarm">isAlarm - boolean indicating setting of alarm or clock time.</param>
/// <returns>void</returns>
void SetTime(Time* time, bool isAlarm)
{
    bool status;
    uint8_t wa = 0x01;
	
	if (isAlarm)
		wa = 0x09;
		
	status = i2c_start(DeviceAddress+I2C_WRITE);       // set device address and write mode
	if ( !status ) 
	{
		i2c_write(wa);
	
		i2c_write(time->hundreds);
		i2c_write(time->seconds);
		i2c_write(time->minutes);
		i2c_write(time->hours);			
	}		
	i2c_stop();
}	

/// <summary>
///	SetDate - Sets either the clock or alarm date.
/// </summary>   
/// <param name="date"> Date* - pointer to date structure</param>
/// <param name="isAlarm"> bool - is this an alarm date</param>
/// <returns>void</returns>
void SetDate(Date* date, bool isAlarm)
{
	bool status;
    uint8_t wa = 0x05;
	
	if (isAlarm)
		wa = 0x0d;
		
	status = i2c_start(DeviceAddress+I2C_WRITE);       // set device address and write mode	
		if ( !status ) 
	{
		i2c_write(wa);
	
		i2c_write(date->year);
		i2c_write(date->month);
	}	
	i2c_stop();
}

/// <summary>
///	ReadTime - Reads either the clock or alarm time.
/// </summary>   
/// <param name="isAlarm"> bool - read alarm time or clock time is not set</param>
/// <returns>bool read status</returns>
bool ReadTime(bool isAlarm)
{
    bool status;
    uint8_t wa = 0x01;
	
	if (isAlarm)
		wa = 0x09;
		
	status = i2c_start(DeviceAddress+I2C_WRITE);
	if ( !status ) 
	{
		i2c_write(wa);
		status = i2c_rep_start(DeviceAddress+I2C_READ);
		if (!status)
		{
			_current_time.hundreds = i2c_readAck();
			_current_time.seconds = i2c_readAck();
			_current_time.minutes = i2c_readAck();
			_current_time.hours = i2c_readNak();
		}
	}
	i2c_stop();
	
	return status;				
}

/// <summary>
///	ReadDate - Reads either the clock or alarm date.
/// </summary>   
/// <param name="isAlarm"> bool - read alarm date or clock date is not set</param>
/// <returns>bool read status</returns>
bool ReadDate(bool isAlarm)
{
    bool status;
    uint8_t wa = 0x05;
	
	if (isAlarm)
		wa = 0x0d;
		
	status = i2c_start(DeviceAddress+I2C_WRITE);       // set device address and write mode
	if ( !status ) 
	{
		i2c_write(wa);
		status = i2c_rep_start(DeviceAddress+I2C_READ);
		if (!status)
		{
			_current_date.year = i2c_readAck();
			_current_date.month = i2c_readNak();
		}
	}
	i2c_stop();
	
	return status;				
	
}
