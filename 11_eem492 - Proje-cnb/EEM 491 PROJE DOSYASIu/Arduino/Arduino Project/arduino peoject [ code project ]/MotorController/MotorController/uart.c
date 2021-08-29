/* ------------------------------------------------------------------------
**	 Module:uart.c: 	
**	 Author:    Mike Hankey
**	 Hardware 	AVR ATmega328
**	 Software:	gcc 4.3.3, AVR Studio 4.18 Build 700
**
**	 DESCRIPTION: Handles UART communications
**						  
**    Version: 1.0
** ------------------------------------------------------------------------*/

#include <avr/interrupt.h>
#include "common.h"
#include "uart.h"

volatile byte buf[16];
volatile byte bptr = 0;

/* -- USART_RX_vect ------------------------------------------------------
**
**	Description: USART0 interrupt vector
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
ISR(USART_RX_vect)
{
	buf[bptr++] = UDR0;
}

/* -- uart_init ----------------------------------------------------------
**
**	Description: USART0 initialization
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
void uart_init(word baud)
{
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
	UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);

	UBRR0 = baud;
}


/* -- SendByte -----------------------------------------------------------
**
**	Description: Sends a byte of data
**
**	Params:	uint8_t	byte to send
**	Returns: None
** -----------------------------------------------------------------------*/
void SendByte(byte data)
{
   // Wait for empty transmit buffer
   while ( !( UCSR0A & (1<<UDRE0)) );             
   // Putting data into the buffer, forces transmission
   UDR0 = data;                                   
}

/* -- SendDataPacket -----------------------------------------------------
**
**	Description: Sends an XBee Transmit Request Packet
**
**	Params:	byte* - pointer to buffer
**			byte	- number of bytes to send
**	Returns: None
** -----------------------------------------------------------------------*/
void SendDataPacket(char* buf, byte len)
{
	for(int i = 0; i < len; i++)
		SendByte(*buf++);
}

/* -- ReadData -----------------------------------------------------------
**
**	Description: Reads data input from UART
**
**	Params:	None
**	Returns: byte* - pointer to data buffer.
** -----------------------------------------------------------------------*/
byte* ReadData()
{
	if (bptr == 0)
		return 0;
	else
	{
		bptr = 0;
		return (byte*)buf;
	}
}
