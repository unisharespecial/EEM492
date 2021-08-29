#include "C:\Users\AKIN\Desktop\bitirme\Sadik_carsamba\den2.h"
#fuses HS,NOWDT,NOPROTECT
#use delay(clock=20M)
#use rs232(uart1,baud=9600)
#include "flex_lcd.c"


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   set_tris_b(0x00);
   output_b(0x00);
   printf("\n\r Hello1 World");
   
   lcd_init();
   printf(lcd_putc,"\f Deneme");
   int sayi=0;
   char ref=0;
   while(1){
   delay_ms(200);
   sayi++;
   if(kbhit()){
   ref=getc();
   printf(lcd_putc,"\f");
   lcd_putc(ref);
   putc(ref);
   }
   if(ref=='a'){
   output_high(PIN_B0);
   ref=0;
   }
   if(ref=='b'){
   output_low(PIN_B0);
   ref=0;
   }
   }

   //TODO: User Code

}
