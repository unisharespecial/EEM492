#include <htc.h>
#include "stdio.h"
#include "usart.h"
void usart_init(void)
{
unsigned char speed,nine_bits;
unsigned int divider;
RX_PIN = 1; // Seri iletiGim pinleri giriG olarak tanýmlanýyor
TX_PIN = 1;
if(HIGH_SPEED==1) // Hýzlý iletiGim yapýlacaksa
speed=0x4;
else // Yaval iletiGim yapýlacaksa
speed=0x00;
if(NINE==1) // 9 bitlik iletiGim yapýlacaksa
nine_bits=0x04;
else // 8 bitlik iletiGim yapýlacaksa
nine_bits=0x00;
SPBRG = DIVIDER; // Hýz deðeri SPBRG'ye yükleniyor
RCSTA = (nine_bits|0x90); // Alým kaydedicisi ayarlanýyor
TXSTA = (speed|nine_bits|0x20); // Gönderim kaydedicisi ayarlanýyor
}
void putch(unsigned char byte)
{
// Tek byte gönder
while(!TXIF); // Transfer tamponu boG mu
TXREG = byte; // Tek byte gönderiliyor
}
unsigned char getch(void)
{
// Tek byte al
while(!RCIF); // Alým tamponu boG mu
return RCREG; // Tek byte alýnýyor
}