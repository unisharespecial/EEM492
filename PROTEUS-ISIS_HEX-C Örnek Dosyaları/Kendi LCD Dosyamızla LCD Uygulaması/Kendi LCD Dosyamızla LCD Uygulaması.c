/*******************************************************
      PIC16F877 ile Kendi LCD Dosyamýzla LCD Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#include <benim_LCD.c> // benim_LCD.c dosyasý programa ekleniyor

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   lcd_hazirla(); // LCD baþlangýç ayarlarý yaptýrýlýyor

   while(1) // Sonsuz döngü
   {
      imlec(1,1); // Ýmlec 1.satýr 1.sütunda
      printf(lcd_veri,"Kendi LCD  Dosya"); // LCD'ye veri yazdýrýlýyor
      delay_ms(1000);
      imlec(2,4); // Ýmlec 2.satýr 4.sütunda
      printf(lcd_veri,"Denememiz"); // LCD'ye veri yazdýrýlýyor
      delay_ms(1000);

      lcd_komut(0x01); // LCD sýfýrlanýyor
      lcd_komut(0x0E); // Ýmleç alt çizgi modunda
      imlec(1,6); // Ýmlec 1.satýr 6.sütunda
      printf(lcd_veri,"C"); delay_ms(1000);
      printf(lcd_veri,"C"); delay_ms(1000);
      printf(lcd_veri,"S"); delay_ms(1000);
      printf(lcd_veri," C"); delay_ms(1000);

       lcd_komut(0x01); // LCD sýfýrlanýyor
   }
}
