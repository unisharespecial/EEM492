/******************************************************************
 PIC16F877 ile DS1621 S�cakl�k ve Termostat Entegresi Uygulamas�
*******************************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k                 // dosyas� tan�t�l�yor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#define use_portb_lcd TRUE   // LCD B portuna ba�l�
#include <lcd.c>     // LCD.c dosyas� programa ekleniyor
#include <DS1302.c>  // DS1302.c dosyas� programa ekleniyor

byte saniye,dakika,saat,gun,ay,yil,haftanin_gunu; // byte t�r�nde de�i�kenler tan�mlan�yor

//******************* ANA PROGRAM FONKS�YONU *******************
void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   lcd_init();  // LCD ba�lang�� ayarlar� yap�l�yor
   rtc_init();  // DS1302 ba�lang�� ayarlar� yap�l�yor

   rtc_set_datetime(20,07,07,6,22,52); // Tarih ve Saat ayarlar� yap�l�yor

   while(1)
   {
      rtc_get_time(saat,dakika,saniye);       // DS1302'den saat,dakika,saniye bilgileri al�n�yor
      rtc_get_date(gun,ay,yil,haftanin_gunu); // DS1302'den g�n,ay,yil ve g�n�n isim bilgisi al�n�yor
      printf(lcd_putc,"\fT:%02d/%02d/20%02d ",gun,ay,yil); //LCD'ye g�n,ay,y�l bilgileri yazd�r�l�yor

      switch(haftanin_gunu)  // DS1302'den say�sal olarak al�nan haftan�n g�n� bilgisine
      {                      // metin olarak kar��l�k atan�yor
         case 1: printf(lcd_putc,"PAZ"); break; // E�er "1" ise LCD'ye PAZ yaz
         case 2: printf(lcd_putc,"PZT"); break; // E�er "2" ise LCD'ye PZT yaz
         case 3: printf(lcd_putc,"SAL"); break; // E�er "3" ise LCD'ye SAL yaz
         case 4: printf(lcd_putc,"CRS"); break; // E�er "4" ise LCD'ye CRS yaz
         case 5: printf(lcd_putc,"PER"); break; // E�er "5" ise LCD'ye PER yaz
         case 6: printf(lcd_putc,"CUM"); break; // E�er "6" ise LCD'ye CUM yaz
         case 7: printf(lcd_putc,"CTS"); break; // E�er "7" ise LCD'ye CTS yaz
      }
      printf(lcd_putc,"\nSaat:%02d:%02d:%02d",saat,dakika,saniye); // LCD'ye saat,dakika ve saniye de�erlerini yaz
      delay_ms(1000); // 1 sn gecikme veriliyor
   }
}
