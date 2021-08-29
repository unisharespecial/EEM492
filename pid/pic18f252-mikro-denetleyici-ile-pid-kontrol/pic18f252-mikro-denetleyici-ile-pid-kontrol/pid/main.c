#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pic18.h>
#include "serial.h"

#define PWM_TICKS 1

/*Current Gain settings are:
 * Kp = 1600
 * Ki = 400
 */

#define INTEGRAL_CONSTANT (i_gain);
#define PROPORTIONAL_CONSTANT (p_gain);
#define DIFFERENTIAL_CONSTANT (d_gain);
#define JOINT_CONSTANT (j_gain);
#define ARC_CONSTANT (a_gain);
#define STOP_DEADBAND 1
#define PCONTROL_DEADBAND 5
#define MIN_SPEED 1
#define MAX_STEP 1

#define RIGHT_DIRECTION RA4
#define LEFT_DIRECTION RB5

/*Right = A = Bottom*/
#define RIGHT_PWM_H CCPR1L
#define RIGHT_PWM_M DC1B1
#define RIGHT_PWM_L DC1B0

/*Left = B = Top*/
#define LEFT_PWM_H CCPR2L
#define LEFT_PWM_M DC2B1
#define LEFT_PWM_L DC2B0

#define FORWARD_LEFT 1
#define BACKWARD_LEFT 0
#define FORWARD_RIGHT 0
#define BACKWARD_RIGHT 1
#define RIGHT_BRAKE RA2
#define LEFT_BRAKE RA3

#define DEBUG 0
#define DEBUG_ALL 0 
#define USE_SPI
#define USE_EEPROM

#define EEPROM_KP_ADDRESS 0
#define EEPROM_KI_ADDRESS 0x08
#define EEPROM_KD_ADDRESS 0x10
#define EEPROM_KJ_ADDRESS 0x18
#define EEPROM_KA_ADDRESS 0x20

#define SPEED_SET 5
#define DIST_SET 10
#define LEFT_SPEED_SET 15
#define RIGHT_SPEED_SET 20
#define LEFT_DIST_SET 25
#define RIGHT_DIST_SET 30
#define GENERAL_READ 35
#define SHIFTED_DIST 40
#define RESET_DIST 45

void LoopTime(void);
void Initialize(void);
void PwmInitialize(void);
void BlinkAlive(void);
void UpdatePWM(void);
void ManageAccel(void);
void puthex(unsigned int c);
void puthexc(unsigned char c);
void get_params(void);
void write_pwm_left(unsigned int duty_cycle);
void write_pwm_right(unsigned int duty_cycle);
void position_control(void);
void parse_SPI(void);
void set_left_position_target(long new_target);
void set_right_position_target(long new_target);
void write_float_to_eeprom( float value, unsigned int address );
void read_float_from_eeprom( float *value, unsigned int address );

/*JF had made all of these static*/
static long last_count_left = 0;
static long last_count_right = 0;
static long error_integral_left = 0;
static long error_integral_right = 0;
static long last_error_left = 0;
static long last_error_right = 0;
static float joint_integral_error = 0;

volatile long count_left = 0;
volatile long count_right = 0;
unsigned char portb_copy = 0;
volatile long count_left_reference = 0;
volatile long count_right_reference = 0;
volatile long count_left_reference_report = 0;
volatile long count_right_reference_report = 0;
float applied_right = 0;
float applied_left = 0;
long left_tick_target;
long right_tick_target;

char controlling_position = 0;
char position_slowdown = 0;

//SPI parsing flags
char newmessage = 0;
char setspeed = 0;
char setdist = 0;
int interrupt_speed_left;
int interrupt_speed_right;
int interrupt_dist_left;
int interrupt_dist_right;

/*Delete Between These*/
char printmessage = 0;
char spi_temp = 0;
char sawthis = 0;
/*Delete Between THese*/

int desired_target_right =0;
int desired_target_left = 0;
long target_right =0;
long target_left = 0;
float p_gain = 0.01;
float i_gain = 0.01;
float d_gain = 0.00;
float j_gain = 0.00;
float a_gain = 0.00;
volatile char rx_message[8];
char tx_message1[8];
char tx_message2[8];
char *current_tx_message = tx_message1;
char *newest_tx_message = tx_message1;

void main(void)
{
    unsigned char PWM_counter = 0;
    char c;

    TRISA = 0xFE; 
	//RA0 = 1;
    Initialize();
    PwmInitialize();

    serial_init();
	//RA0 = 1;

    while(1)
    { 	
        if(RA1 == 0 && kbhit())
        {
            if(kbhit())
            {
                c = getch();
            }
			if(c == 'q')
			{
				printf("QuickBug\n\r");
				asm("goto 0x6002");
			}
			else if(c == 'r')
            {
                desired_target_left = -desired_target_left;
                desired_target_right = -desired_target_right;
            }
			else if(c == 'a')
			{
				desired_target_left = -25;
				desired_target_right = 25;
			}
			else if(c == 'w')
			{
				desired_target_left = 25;
				desired_target_right = 25;
			}
			else if( c == 'd')
			{
				desired_target_left = 25;
				desired_target_right = -25;
			}
			else if(c == 'x')
			{
				desired_target_left = -25;
				desired_target_right = -25;
			}
            else if(c == 's')
            {
                desired_target_left = 0;
                desired_target_right = 0;
            }
            else if(c == 'b')
            {
                RA2 ^= 1;
				RA3 ^= 1;
                printf("Brakes: %d, %d", RA2, RA3);
            }
			else if(c == 'p')
			{
				set_left_position_target(0);
            	set_right_position_target(3375);	
			}
			else if(c == '[')
			{
				set_left_position_target(1687);
				set_right_position_target(-1687);
			}
			else if(c == ']')
			{
				set_left_position_target(-1687); 	
				set_right_position_target(1687);
			}
            else 
            {
                write_pwm_left(0);
                write_pwm_right(0);
                get_params();
                count_left = 0;
                count_right = 0;
                last_count_left = 0;
                last_count_right = 0;
                error_integral_left = 0;
                error_integral_right = 0;
                last_error_left = 0;
                last_error_right = 0;
            }
        }
        BlinkAlive();
        PWM_counter++;
        if(PWM_counter == PWM_TICKS)
        {
            PWM_counter = 0;
			if(sawthis)
			{
				putch('T');
				sawthis = 0;
			}
            if(printmessage)
            {
				printmessage = 0;
#if 0  
				putch('.');
                putch('\n'); 
				putch('\r');
                putch('[');
				for( i = 0; i < 8; i++ )
				{
					puthexc( rx_message[i] );
                    putch( ' ' );
				}
				putch(']');
                putch(' ');
#endif
				
                if( WCOL )
                {
                    putch( 'C' );
                    WCOL = 0;
                }
                if( SSPOV )
                {
                    putch( 'O' );
                    SSPOV = 0;
                }
            }
            parse_SPI();
            position_control();
            UpdatePWM();
            ManageAccel();
        }
        LoopTime();
    }
}

/* parse_SPI ******************************************************************
 * This function will run when the newmessage flag is non-zero.  When it runs,
 * parse_SPI reads the recieved message (rx_message) and carries out sets
 * requested by the controlling processor.
 * ***************************************************************************/
void parse_SPI(void)
{
    if (newmessage)
    {
		putch(newmessage);
		newmessage = 0;
		if(setspeed)
		{
			putch('s');	
			setspeed = 0;  //we've delt with speed update
			GIEL = 0;
			desired_target_left = interrupt_speed_left;
			desired_target_right = interrupt_speed_right;
			GIEL = 1;
			if((desired_target_left < 0) && (desired_target_right < 0))
			{
				putch('-');
			}
		}	
		if(setdist)
		{
			putch('d');
			setdist = 0; //we've delt with the distance update
			GIEL = 0;
            set_left_position_target(interrupt_dist_left);
            set_right_position_target(interrupt_dist_right);
			GIEL =1;
		}
    }
}


void set_left_position_target(long new_target)
{
	GIEH = 0;  //disable interrupts so we don't get wack reference data
    count_left_reference = count_left;
	GIEH = 1;  //reenable interrupts
    left_tick_target = new_target;
 	controlling_position |= 0x01;	
	
	if(((new_target > 0) && (desired_target_left < 0)) || 
	   ((new_target < 0) && (desired_target_left > 0)))
    {
        desired_target_left = -desired_target_left;
    }
}


void set_right_position_target(long new_target)
{
	GIEH = 0;  //disable interrupts so we don't get wack reference data
    count_right_reference = count_right;
	GIEH = 1;  //reenable interrupts
    right_tick_target = new_target;
	controlling_position |= 0x02;
	
    if(((new_target > 0) && (desired_target_right < 0)) || 
	   ((new_target < 0) && (desired_target_right > 0)))
    {
        desired_target_right = -desired_target_right;
    }
}

void position_control(void)
{
    static int posn_error_left;
    static int posn_error_right;
	
    if(controlling_position)
    {			
		GIEH = 0;
        posn_error_left = left_tick_target - ( count_left - count_left_reference ); 
        posn_error_right = right_tick_target - ( count_right - count_right_reference );
		GIEH = 1;

 		putch('\n');
		putch('\r');
		puthex(posn_error_left);
		putch(' ');
		puthex(posn_error_right);		
		putch('|');
		puthex(count_left);
		putch(' ');
		puthex(count_right);
		putch('|');
		puthex(desired_target_left);
		putch(' ');
		puthex(desired_target_right);
		putch('|');
				
		
		
		/*CONTROL LEFT WHEEL*/

		if(controlling_position & 0x01)
		{
			if((posn_error_left > 0 && desired_target_left < 0) || 
	  	 	   (posn_error_left < 0 && desired_target_left > 0))
   		 	{
				putch('<');
   		     	desired_target_left = -desired_target_left;
	   	 	}
			
			if((posn_error_left < (desired_target_left)) && 
			   (posn_error_left > -(desired_target_left)))
			{
				desired_target_left = 0;
				controlling_position &= 0xFE;
			}
		}
		else
		{
			desired_target_left = 0;
		}

		
		
		/*CONTROL RIGHT WHEEL*/

		if(controlling_position & 0x02)
		{
			if((posn_error_right > 0 && desired_target_right < 0) || 
			   (posn_error_right < 0 && desired_target_right > 0))
	    	{
				putch('>');
	        	desired_target_right = -desired_target_right;
	    	}
			if((posn_error_right < (desired_target_right)) && 
			   (posn_error_right > -(desired_target_right)))
			{
				desired_target_right = 0;
				controlling_position &= 0xFD;
			}
		}
		else
		{
			desired_target_right = 0;
		}
    }
}

void UpdatePWM(void)
{
	/*Remember for this section: 
	 * A = Bottom Port = Left
	 * B = Top Port = Right
	 */
		
    long saved_left;
    long saved_right;
    long diff_left;
    long diff_right;
    long error_left;
    long error_right;
	long distance_left;
	long distance_right;
	long report_distance_left;
	long report_distance_right;
	

    /* We need to disable interrupts here or we'll have a race
     * condition while copying these 2-byte values because the ISR
     * could jump in and change the value under us -- JF
     */
    GIEH = 0;
    saved_left = count_left;
    saved_right = count_right;
    GIEH = 1; 

	distance_left = saved_left - count_left_reference;
	distance_right = saved_right - count_right_reference;

	//This section smooths rapid changes in target speed, and sets
	//the target_left and target_right variables accordingly
	if(1)//(position_slowdown & 0x01) == 0)  //position isn't slowing left wheel
	{
		if((desired_target_left - target_left) > MAX_STEP)
		{
			target_left += MAX_STEP;
		}
		else if ((desired_target_left - target_left) < -MAX_STEP)
		{
			target_left -= MAX_STEP;
		}
		else
		{	
			target_left = desired_target_left;
		}
	}
	
	if(1)//(position_slowdown & 0x02) == 0)  //position isn't slowing right wheel
	{
		if((desired_target_right - target_right) > MAX_STEP)
		{
			target_right += MAX_STEP;
		}
		else if ((desired_target_right - target_right) < -MAX_STEP)
		{
			target_right -= MAX_STEP;
   	    }
	    else
	   	{
	   		target_right = desired_target_right;
	   	}
	}

    diff_left = saved_left - last_count_left;
    diff_right = saved_right - last_count_right;
	
#if 1 //DEBUG
    //putch('\r');
    //putch('\n');
		if(controlling_position){
	 	puthex(diff_left >> 16);
		puthex(diff_left);
	    putch(' ');
	    puthex(diff_right >> 16);
		puthex(diff_right);
	}
#endif

    error_left = target_left - diff_left;
    error_right = target_right - diff_right;
#if DEBUG_ALL
    putch('|');
    puthex(error_left);
    putch(' ');
    puthex(error_right);
#endif

    error_integral_left += error_left;
    error_integral_right += error_right;
	
	if(desired_target_right == desired_target_left && desired_target_right != 0 && desired_target_left != 0)
	{
		joint_integral_error += diff_left - diff_right + ARC_CONSTANT;
	}

    /******** Control Left Wheel ********/
    if( target_left == 0 && desired_target_left == 0 &&
		((diff_left >= -STOP_DEADBAND) && (diff_left <= STOP_DEADBAND)))
    {
        applied_left = error_integral_left * INTEGRAL_CONSTANT;
	}
    else 
    {   
        applied_left = error_integral_left * INTEGRAL_CONSTANT;
		applied_left += error_left * PROPORTIONAL_CONSTANT;
		applied_left += (error_left - last_error_left) * DIFFERENTIAL_CONSTANT;
		if(desired_target_left == desired_target_right)
		{   /*We will only add the straightness gain if we want to go straight*/
			applied_left -= joint_integral_error * JOINT_CONSTANT;
		}
    }
	
    if(applied_left > 1023)
    {
        applied_left = 1023;
    }
    else if(applied_left < -1023)
    {
        applied_left = -1023;
    }

    /******** Control Right Wheel ********/
    if(target_right == 0 && desired_target_right == 0 &&
		((diff_right >= -STOP_DEADBAND) && (diff_right <= STOP_DEADBAND)))
    {
        applied_right = error_integral_right * INTEGRAL_CONSTANT;
    }
    else
    {   
        applied_right = error_integral_right * INTEGRAL_CONSTANT;
        applied_right += error_right * PROPORTIONAL_CONSTANT;
        applied_right += (error_right - last_error_right) * DIFFERENTIAL_CONSTANT;
		if(desired_target_left == desired_target_right)
		{  /*We will only add the straightness gain if we want to go straight*/
			applied_right += joint_integral_error * JOINT_CONSTANT;
		}

    }
	
	if(applied_right > 1023)
    {
        applied_right = 1023;
    }
    else if(applied_right < -1023)
    {
        applied_right = -1023;
    }


    //Loads the outgoing status message
	/* Write into the tx buffer that isn't currently being transmitted */
	if( current_tx_message == tx_message1 )
	{
		newest_tx_message = tx_message2;
	}
	else
	{
		newest_tx_message = tx_message1;
	}
#if 0
    newest_tx_message[0] = (char)((diff_left & 0xFF00) >> 8);
    newest_tx_message[1] = (char)(diff_left & 0x00FF);
    newest_tx_message[2] = (char)((diff_right & 0xFF00) >> 8);
    newest_tx_message[3] = (char)(diff_right & 0x00FF);
    newest_tx_message[4] = (char)((distance_left & 0xFF00) >> 8);
    newest_tx_message[5] = (char)(distance_left & 0x00FF);
    newest_tx_message[6] = (char)((distance_right & 0xFF00) >> 8);
    newest_tx_message[7] = (char)(distance_right & 0x00FF);
#else
	report_distance_left = (saved_left - count_left_reference_report) / 426;
	report_distance_right = (saved_right - count_right_reference_report) / 426;
	
    newest_tx_message[0] = (char)(diff_left);
    newest_tx_message[1] = (char)(diff_right);
    newest_tx_message[2] = (char)((report_distance_left & 0xFF00) >> 8);
    newest_tx_message[3] = (char)(report_distance_left & 0x00FF);
    newest_tx_message[4] = (char)((report_distance_right & 0xFF00) >> 8);
    newest_tx_message[5] = (char)(report_distance_right & 0x00FF);
    newest_tx_message[6] = (char)(controlling_position);
    newest_tx_message[7] = (char)(0xFF);
	
#endif
	/* If we aren't transmitting, preload SSPBUF */
	if( current_tx_message == NULL )
	{
		SSPBUF = newest_tx_message[0];
	}
   
    last_count_left = saved_left;
    last_count_right = saved_right;
    last_error_left = error_left;
    last_error_right = error_right;
}

void ManageAccel(void)
{
    unsigned int duty_cycle;

    if(applied_left >= 0)
    {
        duty_cycle = (unsigned int)applied_left;
        LEFT_DIRECTION = FORWARD_LEFT;
#if DEBUG_ALL
        putch('|');
        putch('+');
        puthex(duty_cycle);
#endif
    }
    else
    {
        duty_cycle = (unsigned int)(-applied_left);
        LEFT_DIRECTION = BACKWARD_LEFT;
#if DEBUG_ALL
        putch('|');
        putch('-');
        puthex(duty_cycle);
#endif
    }
    write_pwm_left(duty_cycle);

    if(applied_right >= 0)
    {
        duty_cycle = (unsigned int)applied_right;
        RIGHT_DIRECTION = FORWARD_RIGHT;
#if DEBUG_ALL
        putch(' ');
        putch('+');
        puthex(duty_cycle);
#endif
    }
    else
    {
        duty_cycle = (unsigned int)(-applied_right);
        RIGHT_DIRECTION = BACKWARD_RIGHT;
#if DEBUG_ALL
        putch(' ');
        putch('-');
        puthex(duty_cycle);
#endif
    }
    write_pwm_right(duty_cycle);
#if DEBUG_ALL
	putch('|');
	puthex(desired_target_left);
	putch(' ');
	puthex(desired_target_right);
#endif
}

void Initialize(void)
{
    ADCON1 = 0b10001110;
    TRISA = 0b11100010;
    TRISB = 0b11011111;
    TRISC = 0b11011000;
    TRISD = 0b00011111;
    TRISE = 0b00000100;
    T0CON = 0b10001000;
    T3CON = 0b10001001;
    CCP2CON = 0b00000101;
    IPEN = 1;           
    INTEDG0 = 0;        // RB0 interrupt on falling edge
    INTEDG1 = 1;        // RB1 interrupt on rising edge
    INTEDG2 = 1;        // RB2 interrupt on rising edge
    INT1IP = 1;         // Set RB1 to be high priority interrupt
    INT2IP = 1;         // Set RB2 to be high priority interrupt
	INT0IE = 1;         // Enable interrupts on RB0
    INT1IE = 1;         // Enabled interrupts on RB1
    INT2IE = 1;         // Enabled interrupts on RB2
    CCP2IP = 1;         // Setup HiPri
    RA2 = 1;            // Release Right Brake
    RA3 = 1;            // Release Left Brake
    GIE = 1;            // 
    GIEH = 1;           // Setup HiPri,
    GIEL = 1;
    controlling_position = 0;

#ifdef USE_SPI
    SSPSTAT = 0x00;
	/* SPI Slave mode, use Slave Select pin */
    SSPCON1 = 0x14;
	/* Enable SSP */
    SSPEN = 1;
	/* Low clock = idle */
    CKP = 0;
	/* Sample on rising edge of clock */
    CKE = 1;
	/* Enable SSP interrupt */
    SSPIE = 1;
	/* SSP interrupt is low priority */
    SSPIP = 0;
    
	/* INT0 is hooked up to the slave select line. When Slavesel
	 * goes high, we know the message is done */
	/* Rising edge */
	INTEDG0 = 1;
	/* Enable interrupt */
	INT0IE = 0;
	/* 1:8 Prescaler */
    T1CKPS1 = 1;
    T1CKPS0 = 1;
    /* Increment on every instruction */
    TMR1CS = 0;
    /* Disable the Timer1 oscillator */
    T1OSCEN = 0;
    /* Set the timer to be as long as possible (approx 50 ms) */
    TMR1H = 0xB6;
    TMR1L = 0xC2;
    /* Low priority interrupt */
    TMR1IP = 0;
    /* Enable the interrupt the interrupt until it's needed */
    TMR1IE = 1;
    /* Disable Timer1 to start*/
    TMR1ON = 0;
#endif

#ifdef USE_EEPROM
    read_float_from_eeprom( &p_gain, EEPROM_KP_ADDRESS );
    read_float_from_eeprom( &i_gain, EEPROM_KI_ADDRESS );
    read_float_from_eeprom( &d_gain, EEPROM_KD_ADDRESS );
	read_float_from_eeprom( &j_gain, EEPROM_KJ_ADDRESS );
	read_float_from_eeprom( &a_gain, EEPROM_KA_ADDRESS );
#endif
}

void PwmInitialize(void)
{
    PR2 = 0xFF;               // PWM period = 255
    T2CON = 0b01111111;       // No postscaling, timer on, prescale by 16 
    CCPR1L = 0;                 // Start duty cycle at 0
    TRISC &= ~(1 << 2);          // RC2 = output
    CCP1CON = 0b00001111;       // CCP1 in PWM mode
    
    CCPR2L = 0x00;              // Start duty cycle at 0
    TRISC &= ~(1 << 1);          // RC1 = output
    CCP2CON = 0b00001111;       // CCP2 in PWM mode
}

void LoopTime(void)
{
    while(TMR0IF != 1);
    TMR0IF = 0;
    WRITETIMER0(40536);
}

void interrupt low_priority LowPriISR(void)
{
	int i;
    static int msg_index = 0;
	/* If the transmit buffer is empty and we have
	 * something to transmit (we only enable TXIE when
	 * we have something to transmit) */
    if(TXIF == 1 && TXIE == 1)
    {
        serial_tx_isr();
        TXIF = 0;
    }

    if(SSPIF == 1)
    {
		RA0 = 1;
        if(msg_index == 0)
		{
			if( current_tx_message == NULL )
			{
				current_tx_message = newest_tx_message;
			}
			TMR1ON = 1;  //turn on timer
		}
        rx_message[msg_index] = SSPBUF;
        msg_index++;
        SSPIF = 0;
		TMR1H = 0xB6;
		TMR1L = 0xC2;
        if(msg_index > 7)
        {
            msg_index = 0;
			TMR1ON = 0;  //turn off timer
			current_tx_message = NULL;
			/* Preload SSPBUF for the next go round */
			SSPBUF = newest_tx_message[0];
			
			switch(rx_message[0]){
	    	    case SPEED_SET:
	    	        interrupt_speed_left = rx_message[2] + (rx_message[1] << 8);
		            interrupt_speed_right = rx_message[4] + (rx_message[3] << 8); 
					setspeed = 1;
					newmessage = 'S';
            		break;
		        case DIST_SET:
		            interrupt_dist_left = ((long)(rx_message[2] + (rx_message[1] << 8)));
		            interrupt_dist_right = ((long)(rx_message[4] + (rx_message[3] << 8)));
					setdist = 1;
					newmessage = 'D';
		            break;
		        case GENERAL_READ:
					newmessage = 'R';
					break;
				case RESET_DIST:
				    GIEH = 0;
					count_left_reference_report = count_left;
					count_right_reference_report = count_right;
					GIEH = 1;	
		        default:
					newmessage = '!';
		            break;
			}//end switch			

			/* Enable INT0 so we know when the SLAVESEL for the first byte
			 * of the next message comes in */
			INT0IF = 0;
			INT0IE = 1;
        }
		else
		{
			SSPBUF = current_tx_message[msg_index];
		}
		RA0 = 0;
    }

	if(TMR1IF == 1)
	{
		TMR1ON = 0;  //Disable the timer
		TMR1IF = 0;  //Clear the flag

		msg_index = 0;    //reset the message
		for(i = 0; i<8; i++)   //clear the message
		{
			rx_message[i] = 0;
		}
		
		//Reset the timer for next time
		TMR1H = 0xB6;
    	TMR1L = 0xC2;

		sawthis = 1;

	}

}

void interrupt HiPriISR(void)
{
	portb_copy = PORTB;
	
	/*Bottom Port on Board*/
    if( INT2IF == 1 )
    {
        INT2IF = 0;
        if( portb_copy & 0x10 )
        {
            count_left--;
        }
        else
        {
            count_left++;
        }
    }
	
	/*Top Port on Board*/
    if( INT1IF == 1 )
    {
        INT1IF = 0;
        if( portb_copy & 0x08 )
        {
            count_right++;
            //count_right_accumulator++;
        }
        else
        {
            count_right--;
            //count_right_accumulator--;
        }
    }

	/* /SLAVESEL was just asserted and we're looking for the first
	 * byte of the tx message */
	if( INT0IF == 1 && INT0IE == 1 )
	{
		INT0IE = 0;
		current_tx_message = newest_tx_message;
	}
}

void get_params(void)
{
    char buffer[20];
    int good = 0;
    int i;
    do
    {
        printf("\r\nEnter target left speed (%d): ", desired_target_left);
        gets(buffer);
        if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0)
        {
            desired_target_left = atoi(buffer);
        }
        printf("\r\nEnter target right speed (%d): ", desired_target_right);
        gets(buffer);
        if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0)
        {
            desired_target_right = atoi(buffer);
        }
		do
		{
		printf("\r\nDo you want to adjust gains? (y/n) ");
		gets(buffer);
		}
		while(strcmp(buffer, "y") != 0 && strcmp(buffer, "n") != 0);
		if(strcmp(buffer, "y") == 0)
		{
		
	        printf("\r\nEnter 1000*Kp (%d): ", (int)(p_gain * 1000));
 	       	gets(buffer);
   	    	if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0)
    	    {
            	p_gain = atoi(buffer) * 0.001;
        	}
        	printf("\r\nEnter 1000*Ki (%d): ", (int)(i_gain * 1000));
        	gets(buffer);
        	if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0)
        	{
            	i_gain = atoi(buffer) * 0.001;
        	}
        	printf("\r\nEnter 1000*Kd (%d): ", (int)(d_gain * 1000));
        	gets(buffer);
        	if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0)
        	{
            	d_gain = atoi(buffer) * 0.001;
        	}
        	printf("\r\nEnter 1000*Kj (%d): ", (int)(j_gain * 1000));
        	gets(buffer);
        	if(buffer[0] != '\r' && buffer[0] != '\n' && buffer[0] != 0)
        	{
            	j_gain = atoi(buffer) * 0.001;
        	}		
			printf("\r\nEnter  1000*Ka (%d): ", (int)(a_gain *  1000));
			gets(buffer);
			if(buffer[0] != '\r' && buffer [0] != '\n' && buffer[0] != 0)
			{
				a_gain = atoi(buffer) * 0.001;
			}
   		} 
 
        do
        {
            printf("\n\rDo you want to control position? (y/n): ");
            gets(buffer);
        }
        while(strcmp(buffer, "y") != 0 && strcmp(buffer, "n") != 0);
        if(strcmp(buffer, "y") == 0)
        {
            printf("\r\nEnter Left Position Target (0): ");
            gets(buffer);
            if(buffer[0] != '\r' && buffer[0] != '\n')
            {
                set_left_position_target(atoi(buffer));
            }
            printf("\r\nEnter Right Position Target (0): ");            
            gets(buffer);
            if(buffer[0] != '\r' && buffer[0] != '\n')
            {
                
                set_right_position_target(atoi(buffer));
            }
        }
        else
        {
            controlling_position = 0;
        }
		printf("\r\n\r\nTarget left:  %d\r\n", desired_target_left);
        printf("Target right: %d\r\n", desired_target_right);
        printf("Kp: %dE-3\r\n", (int)(p_gain * 1000));
        printf("Ki: %dE-3\r\n", (int)(i_gain * 1000));
        printf("Kd: %dE-3\r\n", (int)(d_gain * 1000));
		printf("Kj: %dE-3\r\n", (int)(j_gain * 1000));
		printf("Ka: %dE-2\r\n", (int)(a_gain * 1000));
        do
        {
            printf("\r\nAre these acceptable? (y/n): ");
            gets(buffer);
        }
        while(strcmp(buffer, "y") != 0 && strcmp(buffer, "n") != 0);
        if(strcmp(buffer, "y") == 0)
        {
            good = 1;
        }
    }
    while(!good);

#ifdef USE_EEPROM
    write_float_to_eeprom( p_gain, EEPROM_KP_ADDRESS );
    write_float_to_eeprom( i_gain, EEPROM_KI_ADDRESS );
    write_float_to_eeprom( d_gain, EEPROM_KD_ADDRESS );
	write_float_to_eeprom( j_gain, EEPROM_KJ_ADDRESS );
	write_float_to_eeprom( a_gain, EEPROM_KA_ADDRESS );
#endif
    
    printf("\r\n");
    while(RA1)
    {
        if(kbhit())
        {
            if(getch() == 's')
            {
                break;
            }
        }
    }
    if( controlling_position )
    {
        printf("Position control: ON\n" );
    }
    else
    {
        printf("Position control: OFF\n" );
    }
	printf("Speed (L|R) Error (L|R) Applied (L|R)\n\r");
    printf("Output Starts Here\r\nPeriod: %d ms",PWM_TICKS * 10);
    for(i = 0; i < 10000; i++);
}


void BlinkAlive(void)
{
#if 0
    static unsigned char alive_count = 250;
    RA0 = 1;
    if(--alive_count == 0)
    {
        alive_count = 250;
        RA0 = 0;
    }
#endif
}

/* Print out two hex bytes */
void puthex(unsigned int c)
{
    char digit;
    int i;
    char buffer[5];
    buffer[4] = 0;
    for(i= 0; i < 4; i++)
    {
        digit = c & 0x0F;
        if(digit > 9)
        {
            buffer[3-i] = 'A' + digit - 10;
        }
        else
        {
            buffer[3-i] = '0' + digit;
        }
        c >>= 4;
    }
    putch(buffer[0]);
    putch(buffer[1]);
    putch(buffer[2]);
    putch(buffer[3]);
}

/* Print out a single hex byte */
void puthexc(unsigned char c)
{
    char digit;
    int i;
    char buffer[3];
    buffer[2] = 0;
    for(i= 0; i < 2; i++)
    {
        digit = c & 0x0F;
        if(digit > 9)
        {
            buffer[1-i] = 'A' + digit - 10;
        }
        else
        {
            buffer[1-i] = '0' + digit;
        }
        c >>= 4;
    }
    putch(buffer[0]);
    putch(buffer[1]);
}

void write_pwm_left(unsigned int duty_cycle)
{
    LEFT_PWM_H = duty_cycle >> 2;
    LEFT_PWM_M = (duty_cycle >> 1) & 0x01;
    LEFT_PWM_L = duty_cycle & 0x01;

}

void write_pwm_right(unsigned int duty_cycle)
{
    RIGHT_PWM_H = duty_cycle >> 2;
    RIGHT_PWM_M = (duty_cycle >> 1) & 0x01;
    RIGHT_PWM_L = duty_cycle & 0x01;
}

#ifdef USE_EEPROM
/*
 * Writes the given float value to the given address in EEPROM in
 * a portable way. Note that sizeof(float) bytes need to be available
 * starting at address in EEPROM and that the size of a float can change
 * depending on compiler options. 8 bytes should always be safe, but we
 * use 16 to be super duper duper sure.
 */
void write_float_to_eeprom( float value, unsigned int address )
{
    char *pointer;
    unsigned int i;
    char byte;
    
    pointer = (char *)&value;
    for( i = 0; i < sizeof(value); i++ )
    {
        byte = pointer[i];
        EEPROM_WRITE( address + i, byte );
    }
}

/*
 * Reads a float value from the given address in EEPROM in portable
 * way.
 */
void read_float_from_eeprom( float *value, unsigned int address )
{
    float temp;
    char *pointer;
    unsigned int i;

    pointer = (char *)&temp;
    for(i = 0; i < sizeof(temp); i++)
    {
        pointer[i] = EEPROM_READ( address + i );
    }

    *value = temp;
}
#endif
