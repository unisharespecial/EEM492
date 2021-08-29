#include <htc.h>
#include "stdio.h"
#include "usart.h"
void usart_init(void)
{
unsigned char speed,nine_bits;
unsigned int divider;
RX_PIN = 1; // Seri iletiGim pinleri giriG olarak tan�mlan�yor
TX_PIN = 1;
if(HIGH_SPEED==1) // H�zl� iletiGim yap�lacaksa
speed=0x4;
else // Yaval iletiGim yap�lacaksa
speed=0x00;
if(NINE==1) // 9 bitlik iletiGim yap�lacaksa
nine_bits=0x04;
else // 8 bitlik iletiGim yap�lacaksa
nine_bits=0x00;
SPBRG = DIVIDER; // H�z de�eri SPBRG'ye y�kleniyor
RCSTA = (nine_bits|0x90); // Al�m kaydedicisi ayarlan�yor
TXSTA = (speed|nine_bits|0x20); // G�nderim kaydedicisi ayarlan�yor
}
void putch(unsigned char byte)
{
// Tek byte g�nder
while(!TXIF); // Transfer tamponu boG mu
TXREG = byte; // Tek byte g�nderiliyor
}
unsigned char getch(void)
{
// Tek byte al
while(!RCIF); // Al�m tamponu boG mu
return RCREG; // Tek byte al�n�yor
}