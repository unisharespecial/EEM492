#include "C:\Users\AKIN\Desktop\bitirme-proje\Sadik_carsamba\dden4.h"
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
   printf(lcd_putc,"\f Deneme13");
   delay_ms(1000);
   unsigned int ar=0;
   unsigned int start_bit=0;
   unsigned int ref=0;
   set_tris_b(0x00);
   output_b(0x01);
   unsigned int arr[41];
   unsigned int16 RH=0;
   int RH_low;
   unsigned int16 Temp=0;
   int Temp_low;
   int sayac=0;
   
   while(1){
   //Master Start bit
   set_tris_b(0x00);
   output_low(PIN_B0);
   delay_ms(8);
   output_high(PIN_B0);
   delay_us(30);
   output_low(PIN_B0);
   set_tris_b(0x01);//input oldu
   //Master Start bit son
   while(input(PIN_B0)==1);//Hat low'da ise beklesin diye

   while(ref<41){
   while(input(PIN_B0)==0);//Hat low'da ise beklesin diye
   start_bit=0;
   while(input(PIN_B0)==1){
   delay_us(1);
   start_bit++;
   }
   arr[ref]=start_bit;
   ref++;
   }
   
   sayac=1;
   while(sayac<17){
   if((arr[sayac]>6) && (arr[sayac]<14)){
   bit_clear(RH,(sayac-1));
   }
   else{
   if((arr[sayac]>24) && (arr[sayac]<30)){
   bit_set(RH,(sayac-1));
   }
   }
   sayac++;
   }

   while(sayac<33){
   if((arr[sayac]>6) && (arr[sayac]<14)){
   bit_clear(Temp,(sayac-17));
   }
   else{
   if((arr[sayac]>24) && (arr[sayac]<30)){
   bit_set(Temp,(sayac-17));
   }
   }
   sayac++;
   }
   
   RH_low=RH/10;
   Temp_low=Temp/10;
   
   printf(lcd_putc,"\f%u : %u",Temp_low,RH_low);
   //Line pull-up by master
   set_tris_b(0x00);
   output_b(0x01);
   delay_ms(5000);
   }

   //TODO: User Code

}
