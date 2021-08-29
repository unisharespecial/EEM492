
#ifndef _H_STEPMOTOR_
#define _H_STEPMOTOR_

#define CMD_PORT	DDRC
#define DATA_PORT	PORTC

#define IN1			PC0
#define IN2			PC1
#define IN3			PC2
#define IN4			PC3

typedef enum 
{
	stop_release = '0',
	wave_forward = '1',
	wave_reverse = '2',
	full_forward = '3',
	full_reverse = '4',
	half_forward = '5',
	half_reverse = '6',
	stop_hold = '7'
}STEP_MOTOR_CMDS;

typedef enum
{
	step_forward,
	step_reverse
} MOTOR_DIRECTION;

void StepMotor_init();
void StepMotor_cmd(STEP_MOTOR_CMDS);
void StepMotor_next();

#endif //_H_STEPMOTOR_
