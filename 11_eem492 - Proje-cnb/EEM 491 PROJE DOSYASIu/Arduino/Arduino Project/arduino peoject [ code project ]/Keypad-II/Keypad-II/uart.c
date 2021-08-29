/* ------------------------------------------------------------------------
**	 Module:uart.c: 	
**	 Author:    Mike Hankey
**	 Hardware 	AVR ATmega328
**	 Software:	gcc 4.3.3 AVR Studio 4.18 Build 700
**
**	 DESCRIPTION: Handles UART communications
**						  
**    Version: 1.0
**
**    Copyright © 2010, Mike Hankey
**    All rights reserved. [BSD License]
**    http://www.JaxCoder.com/
** 
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. All advertising materials mentioning features or use of this software
**    must display the following acknowledgement:
**    This product includes software developed by the Mike Hankey.
** 4. Neither the name of the <organization> nor the
**    names of its contributors may be used to endorse or promote products
**    derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY Mike Hankey ''AS IS'' AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** 
** ------------------------------------------------------------------------*/

#include <avr/interrupt.h>
#include "common.h"
#include "uart.h"

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
