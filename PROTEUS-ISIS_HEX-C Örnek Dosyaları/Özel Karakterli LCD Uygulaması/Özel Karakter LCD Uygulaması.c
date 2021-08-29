/*******************************************************
PIC16F877 ile Kendi Özel Karakterli LCD Dosyamýzla LCD Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#include <özel_karakter_LCD.c> // özelkarakter__LCD.c dosyasý programa ekleniyor

float x=23.5;  // Ondalýklý tipte deðiþken tanýmlanýyor

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
   ozel_karakterler(); // Özel karakterler CGRAM'e yükleniyor

   while(1) // Sonsuz döngü
   {
      imlec(1,1); // Ýmlec 1.satýr 1.sütunda
      printf(lcd_veri,"ÖZEL KARAKTERLÝ"); // LCD'ye veri yazdýrýlýyor

      imlec(2,1); // Ýmlec 2.satýr 1.sütunda
      printf(lcd_veri,"LCD UYGULAMASI"); // LCD'ye veri yazdýrýlýyor
      delay_ms(1000);

      lcd_komut(0x01); // LCD sýfýrlanýyor
      printf(lcd_veri,"ÖZEL KARAKTERLER"); // LCD'ye veri yazdýrýlýyor

      imlec(2,1); // Ýmlec 2.satýr 1.sütunda
      printf(lcd_veri,"Ç"); delay_ms(1000);
      printf(lcd_veri,"Ð"); delay_ms(1000);
      printf(lcd_veri,"Ý"); delay_ms(1000);
      printf(lcd_veri,"Ö"); delay_ms(1000);
      printf(lcd_veri,"Þ"); delay_ms(1000);
      printf(lcd_veri,"Ü"); delay_ms(1000);
      printf(lcd_veri,"'"); delay_ms(1000);
      printf(lcd_veri,"I"); delay_ms(1000);

      lcd_komut(0x01); // LCD sýfýrlanýyor
      printf(lcd_veri,"SICAKLIK %f'C",x); delay_ms(3000);

      lcd_komut(0x01); // LCD sýfýrlanýyor
   }
}

