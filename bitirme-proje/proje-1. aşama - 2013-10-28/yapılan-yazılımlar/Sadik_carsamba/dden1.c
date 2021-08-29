#include "C:\Users\AKIN\Desktop\bitirme-proje\Sadik_carsamba\dden1.h"
#fuses HS,NOWDT,NOPROTECT
#use delay(clock=20M)
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
   lcd_init();
   unsigned int ar=0;
   while(1){
   printf(lcd_putc,"\f  Sayi: %d",ar);
   ar++;
   delay_ms(1000);
   }

   //TODO: User Code

}
