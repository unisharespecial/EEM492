#include <pic18.h>
#include <stdio.h>
#include "serial.h"

void my_puts(const char *s);

char tx_buffer[TX_BUFFER_SIZE];

/* Read and write pointers into the serial circular buffer */
volatile static char *tx_wp;
volatile static char *tx_rp;
/* Number of bytes currently in the serial circular buffer */
volatile static char tx_numbytes = 0;

void serial_init(void)
{
    tx_wp = &tx_buffer[0];
    tx_rp = &tx_buffer[0];
    tx_numbytes = 0;
    /* Make TX reg clear interrupt low priority */
    TXIP = 0;
    /* Disable the TX reg clear interrupt for now */
    TXIE = 0;
#if 0
    my_puts("Switching to 57600 Baud... press key to continue\r\n");
#endif
    BRGH = 1;
    SPBRG = 10;
#if 0
    my_puts("Switch complete\r\n");
    /* Wait for the last byte of the previous string to be transmitted */
    while(!TXIF);
#endif
}

void putch(unsigned char c)
{
    TXIE = 0;
    if( tx_numbytes == 0 && TXIF )
    {
        TXREG = c;
    }
    else
    {
        if( tx_numbytes == TX_BUFFER_SIZE )
        {
            /* Buffer is full, so wait for serial port to do its thing */
            TXIE = 1;
            while( tx_numbytes == TX_BUFFER_SIZE );
            TXIE = 0;
        }
        *tx_wp = c;
        tx_wp++;
        if(tx_wp == tx_buffer + TX_BUFFER_SIZE)
        {
            tx_wp = tx_buffer;
        }
        tx_numbytes++;
        TXIE = 1;
    }
}

void serial_tx_isr(void)
{
    TXREG = *tx_rp;
    tx_rp++;
    if(tx_rp == tx_buffer + TX_BUFFER_SIZE)
    {
        tx_rp = tx_buffer;
    }
    tx_numbytes--;
    if(tx_numbytes == 0)
    {
        TXIE = 0;
    }
}

unsigned char getch()
{
	/* retrieve one byte */
	while(!RCIF)	/* set when register is not empty */
		continue;
	return RCREG;	
}

unsigned char getche(void)
{
	unsigned char c;
	putch(c = getch());
	return c;
}

bit kbhit(void)
{
    return RCIF;
}

void my_puts(const char *s)
{
    while(*s)
    {
        while(TXIF == 0);
        TXREG = *s;
        s++;
    }
}
