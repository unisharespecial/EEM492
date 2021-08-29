
#include <avr/io.h>
#include <avr/portpins.h>
#include "DCMotor.h"

/* -- DCMotor_init --------------------------------------------------------
**
**	Description: Initialize port for DC motor
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
void DCMotor_init()
{
	CMD_PORT = _BV(ENABLE1) | _BV(IN1) | _BV(IN2);
	DATA_PORT = 0;	

}

/* -- DCMotor_cmd --------------------------------------------------------
**
**	Description: Main routine
**
**	Params:	DC_MOTOR_CMDS - command to execute
**	Returns: None
** -----------------------------------------------------------------------*/
void DCMotor_cmd(DC_MOTOR_CMDS cmd)
{
	switch(cmd)
	{
		case forward:
			DATA_PORT = _BV(ENABLE1) | ~_BV(IN1) | _BV(IN2);
			break;
		case reverse:
			DATA_PORT = _BV(ENABLE1) | _BV(IN1) | ~_BV(IN2);
			break;
		case stop:
			DATA_PORT = ~_BV(ENABLE1) | ~_BV(IN1) | ~_BV(IN2);
			break;
	}
}
