#include <18F452.h>
#device adc=8

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES RC_IO                 	//Resistor/Capacitor Osc
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES NOOSCSEN              	//Oscillator switching is disabled, main oscillator is source
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES BORV20                	//Brownout reset at 2.0V
#FUSES NOPUT                 	//No Power Up Timer
#FUSES STVREN                	//Stack full/underflow will cause reset
#FUSES NODEBUG               	//No Debug mode for ICD
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                 	//Program memory not write protected
#FUSES NOWRTD                	//Data EEPROM not write protected
#FUSES NOWRTB                	//Boot block not write protected
#FUSES NOWRTC                	//configuration not registers write protected
#FUSES NOCPD                 	//No EE protection
#FUSES NOCPB                 	//No Boot Block code protection
#FUSES NOEBTR                	//Memory not protected from table reads
#FUSES NOEBTRB               	//Boot block not protected from table reads

#use delay(clock=4000000)

