
#include <avr/io.h>
#include <avr/portpins.h>
#include "Common.h"
#include "StepMotor.h"

const byte wave_table[] = { 0x08, 0x04, 0x02, 0x01 };
const byte full_table[] = { 0x0C, 0x06, 0x03, 0x09 };
const byte half_table[] = { 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09, 0x08 };

volatile byte* current_table = null;
volatile byte table_size = 0;
volatile byte current_step = 0;
volatile byte current_direction = step_forward;

/* -- DCMotor_init --------------------------------------------------------
**
**	Description: Initialize port for DC motor
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
void StepMotor_init()
{
	CMD_PORT =  _BV(IN1) | _BV(IN2) | _BV(IN3) | _BV(IN4);
	DATA_PORT = 0;	

}

/* -- DCMotor_cmd --------------------------------------------------------
**
**	Description: Main routine
**
**	Params:	DC_MOTOR_CMDS - command to execute
**	Returns: None
** -----------------------------------------------------------------------*/
void StepMotor_cmd(STEP_MOTOR_CMDS cmd)
{
	
	switch(cmd)
	{
		case wave_forward:
			current_direction = step_forward;
			current_table = (byte*)wave_table;
			table_size = 4;
			break;
		case wave_reverse:
			current_direction = step_reverse;
			current_table = (byte*)wave_table;
			table_size = 4;
			break;
		case full_forward:
			current_direction = step_forward;
			current_table = (byte*)full_table;
			table_size = 4;
			break;
		case full_reverse:
			current_direction = step_reverse;
			current_table = (byte*)full_table;
			table_size = 4;
			break;
		case half_forward:
			current_direction = step_forward;
			current_table = (byte*)half_table;
			table_size = 8;
			break;
		case half_reverse:
			current_direction = step_reverse;
			current_table = (byte*)half_table;
			table_size = 8;
			break;
		case stop_hold:
			current_table = null;
			table_size = 0;
			break;
		case stop_release:
			DATA_PORT = 0;
			current_table = null;
			table_size = 0;
			break;
	}
	current_step = 0;
}

/* -- StepMotor_next -----------------------------------------------------
**
**	Description: Main routine
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
void StepMotor_next()
{
	if (current_table == null)
		return;


	DATA_PORT = *(current_table + current_step);

	if (current_direction == step_forward)
	{
		if (++current_step >= table_size)
			current_step = 0;
	}
	else
	{
		if (--current_step == 0xff)
			current_step = table_size - 1;
	}
}
