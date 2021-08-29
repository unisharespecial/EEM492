/* ------------------------------------------------------------------------
**	 Module:Keypad-II.c: 	
**	 Author:    Mike Hankey
**	 Hardware 	AVR ATmega328
**	 Software:	gcc 4.3.3 AVR Studio 4.18 Build 700
**
**	 DESCRIPTION: Application to interact with Experimentor keypad.
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
**    This product includes software developed by Mike Hankey
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
#ifndef F_CPU
#define F_CPU 16000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "common.h"
#include "uart.h"

#define UART_BAUD_RATE  	9600

#define CMD_PORT 	DDRC
#define DATA_PORT 	PORTC
#define PIN_PORT	PINC

#define CLOCK		PC5
#define MISO		PC4
#define MOSI		PC3
#define LATCH		PC2
#define LOAD		PC1

static char buffer[] = "Pressed: x";
static char scan_table[5][5] = { { '<', '0', '1', '2', '3' },
								{ 'D', '4', '5', '6', '7' },
								{ '>', '8', '9', 'A', 'B' },
								{ 'E', 'C', 'D', 'E', 'F' },
								{ 'S', 'W', 'X', 'Y', 'Z' }};

void init();
void output_data(byte);
byte input_data();
ushort scan();
byte convert_result(byte);

/* -- main ---------------------------------------------------------------
**
**	Description: Main routine
**
**	Params:	None
**	Returns: int
** -----------------------------------------------------------------------*/
int main()
{
	ushort result;
	byte row, col;
	char chr;

	init();

	//Initialize our UART0 (PC<->Master)
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );

	while(1)
	{
		//Scan keypad
		result = scan();

		//If a key was pressed convert values and do lookup
		if (result.Short > 0)
		{
			row = convert_result(result.Byte[0]);
			col = convert_result(result.Byte[1]);
			chr = scan_table[col][row];

			buffer[9] = chr;
			
			//Send result via UART to PC
			SendDataPacket(buffer, 10);
		}
		_delay_ms(200);
	}

	return 0;
}

/* -- init ---------------------------------------------------------------
**
**	Description: Initializes ports
**
**	Params:	None
**	Returns: None
** -----------------------------------------------------------------------*/
void init()
{
	CMD_PORT = _BV(CLOCK) | _BV(MOSI) | _BV(LATCH) | _BV(LOAD);

	DATA_PORT = _BV(LATCH) | _BV(LOAD);
}

/* -- scan ---------------------------------------------------------------
**
**	Description: Transfers one byte of data to 74HC595
**
**	Params:	None
**	Returns: ushort - 2 bit scan code made up of row and column
** -----------------------------------------------------------------------*/
ushort scan()
{
	byte mask = 0x80;
	volatile byte result = 0;
	ushort scan_code;

	scan_code.Short = 0;
	for(byte i = 0; i < 8; i++)
	{
		//Shift in column data
		output_data(mask);

		result = input_data();
		if (result != 0)
		{
			scan_code.Byte[0] = result; 
			scan_code.Byte[1] = mask;
			break;
		}
		mask >>= 1;
	}
	return scan_code;
}

/* -- output_data --------------------------------------------------------
**
**	Description: Transfers one byte of data to 74HC595
**
**	Params:	byte - data to send
**	Returns: None
** -----------------------------------------------------------------------*/
void output_data(byte data)
{
	DATA_PORT &= ~_BV(LATCH);

	//Shift data bits out one at a time
	for (byte i = 0; i < 8;i++)
	{
		//Set the data bit 0 or 1
		if ((data & 0x80) == 0x80)
			DATA_PORT |= _BV(MOSI);
		else
			DATA_PORT &= ~_BV(MOSI);

		//Clock the bit into the shift register
		DATA_PORT &= ~_BV(CLOCK);
		DATA_PORT |= _BV(CLOCK);

		data <<= 1;
	}
	//Latch the data we just sent
	DATA_PORT |= _BV(LATCH);
}

/* -- input_data --------------------------------------------------------
**
**	Description: Shifts one byte of data from 74LS165
**
**	Params:	None
**	Returns: byte - data returned from shift register
** -----------------------------------------------------------------------*/
byte input_data()
{
	volatile byte result = 0;

	//Load the parallel data into the shift register
	DATA_PORT &= ~_BV(LOAD);
	DATA_PORT |= _BV(LOAD);

	//Shift data bits out one at a time
	for (byte i = 0; i < 8;i++)
	{		
		result <<= 1;

		if ((PINC & 0x10) == 0x10)
			result |= 0x01;		

		//Clock the bit into the shift register
		DATA_PORT &= ~_BV(CLOCK);
		DATA_PORT |= _BV(CLOCK);
	}
	return result;
}

/* -- convert_result -----------------------------------------------------
**
**	Description: Converts the bit position to a number for lookup
**
**	Params:	byte - number to be converted
**	Returns: byte - converted value
** -----------------------------------------------------------------------*/
byte convert_result(byte data)
{
	byte value = 0;
	
	do
	{
		if (data & 1)
			break;

		++value;
		data >>= 1;

	} while(value < 8);

	return value;
}


