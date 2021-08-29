
#ifndef _H_DCMOTOR_
#define _H_DCMOTOR_

#define CMD_PORT	DDRC
#define DATA_PORT	PORTC

#define IN1			PC0
#define IN2			PC1
#define ENABLE1		PC2

typedef enum 
{
	forward = '1',
	reverse = '2',
	stop = '0'
}DC_MOTOR_CMDS;

void DCMotor_init();
void DCMotor_cmd(DC_MOTOR_CMDS);

#endif //_H_DCMOTOR_
