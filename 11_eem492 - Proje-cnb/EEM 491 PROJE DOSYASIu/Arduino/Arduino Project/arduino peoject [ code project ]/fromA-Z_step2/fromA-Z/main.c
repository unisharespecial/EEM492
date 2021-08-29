#include <stm32f10x_lib.h>
#include "STM32_Init.h"

void SendByte (int byte);

int main (void)
{
	stm32_Init();
	while(1);
	return 0;
}
void USART1_IRQHandler (void)
{
    volatile unsigned int vsr;

    int ByteSent;
    vsr= USART1->SR;
    if (vsr& USART_FLAG_RXNE)                   // did we interrupt on the read
    {
        USART1->SR &= ~(USART_FLAG_RXNE);        // clear the interrupt since we are processing it
        ByteSent = (USART1->DR & 0x1FF);

        SendByte(ByteSent);

     }
}
void SendByte (int byte)  
{
	//Wait for the uart to finish sending the byte.
 	while (!(USART1->SR & USART_FLAG_TXE));
	USART1->DR = (byte & 0xFF);
}