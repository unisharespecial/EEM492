/******************************************************************
 PIC16F877 ile DS1621 Sýcaklýk ve Termostat Entegresi Uygulamasý
*******************************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk                 // dosyasý tanýtýlýyor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#define use_portb_lcd TRUE   // LCD B portuna baðlý
#include <lcd.c>     // LCD.c dosyasý programa ekleniyor
#include <DS1302.c>  // DS1302.c dosyasý programa ekleniyor

byte saniye,dakika,saat,gun,ay,yil,haftanin_gunu; // byte türünde deðiþkenler tanýmlanýyor

//******************* ANA PROGRAM FONKSÝYONU *******************
void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   lcd_init();  // LCD baþlangýç ayarlarý yapýlýyor
   rtc_init();  // DS1302 baþlangýç ayarlarý yapýlýyor

   rtc_set_datetime(20,07,07,6,22,52); // Tarih ve Saat ayarlarý yapýlýyor

   while(1)
   {
      rtc_get_time(saat,dakika,saniye);       // DS1302'den saat,dakika,saniye bilgileri alýnýyor
      rtc_get_date(gun,ay,yil,haftanin_gunu); // DS1302'den gün,ay,yil ve günün isim bilgisi alýnýyor
      printf(lcd_putc,"\fT:%02d/%02d/20%02d ",gun,ay,yil); //LCD'ye gün,ay,yýl bilgileri yazdýrýlýyor

      switch(haftanin_gunu)  // DS1302'den sayýsal olarak alýnan haftanýn günü bilgisine
      {                      // metin olarak karþýlýk atanýyor
         case 1: printf(lcd_putc,"PAZ"); break; // Eðer "1" ise LCD'ye PAZ yaz
         case 2: printf(lcd_putc,"PZT"); break; // Eðer "2" ise LCD'ye PZT yaz
         case 3: printf(lcd_putc,"SAL"); break; // Eðer "3" ise LCD'ye SAL yaz
         case 4: printf(lcd_putc,"CRS"); break; // Eðer "4" ise LCD'ye CRS yaz
         case 5: printf(lcd_putc,"PER"); break; // Eðer "5" ise LCD'ye PER yaz
         case 6: printf(lcd_putc,"CUM"); break; // Eðer "6" ise LCD'ye CUM yaz
         case 7: printf(lcd_putc,"CTS"); break; // Eðer "7" ise LCD'ye CTS yaz
      }
      printf(lcd_putc,"\nSaat:%02d:%02d:%02d",saat,dakika,saniye); // LCD'ye saat,dakika ve saniye deðerlerini yaz
      delay_ms(1000); // 1 sn gecikme veriliyor
   }
}
