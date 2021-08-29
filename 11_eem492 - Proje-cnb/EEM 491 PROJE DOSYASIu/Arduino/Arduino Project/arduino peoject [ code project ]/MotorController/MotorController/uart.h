
#ifndef _UART_H_
#define _UART_H_ 1

#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16L)-1)

//Method declaration
void uart_init(word);
void SendDataPacket(char*, byte);
void SendByte(byte);
byte* ReadData();

#endif  //_UART_H_
