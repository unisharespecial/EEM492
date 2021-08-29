#ifndef F_CPU
#define F_CPU 16000000L
#endif

//Comment out this define if you're using DC motor and
//	uncomment if using stepper motor.
#define STEP_MODE

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include "Common.h"
#include "DCMotor.h"
#include "StepMotor.h"
#include "uart.h"

#define UART_BAUD_RATE  	9600

const char prompt[] = "\n0 - Stop\n1 - Forward\n2 - Reverse\n?>";
const char sprompt[] = "\n0 - Stop (Release)\n1 - Wave Fwd\n2 - Wave Rev\n3 - Full Fwd\n4 - Full Rev\n5 - Half Fwd\n6 - Half Rev\n7 - Hold\n?>";

void init();

/* -- main ---------------------------------------------------------------
**
**	Description: Main routine
**
**	Params:	None
**	Returns: int
** -----------------------------------------------------------------------*/
int main()
{
	byte* cmd;

	//Initialize our UART0 (PC<->Master)
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );

	init();

	sei();

	while(1)
	{

#ifdef STEP_MODE
		SendDataPacket((char*)sprompt, sizeof(sprompt));
#else
		SendDataPacket((char*)prompt, sizeof(prompt));
#endif

		do
		{
			cmd = ReadData();
#ifdef STEP_MODE
			StepMotor_next();
#endif
			_delay_ms(200);
		} while (cmd == null);
		
#ifdef STEP_MODE
		StepMotor_cmd(*cmd);
#else
		DCMotor_cmd(*cmd);
#endif


	}

	return 0;
}

/* -- init ---------------------------------------------------------------
**
**	Description: Initialize port
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
void init()
{
	DCMotor_init();
	StepMotor_init();
}
