/*******************************************************
      PIC16F877 ile Kendi LCD Dosyam�zla LCD Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#include <benim_LCD.c> // benim_LCD.c dosyas� programa ekleniyor

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   lcd_hazirla(); // LCD ba�lang�� ayarlar� yapt�r�l�yor

   while(1) // Sonsuz d�ng�
   {
      imlec(1,1); // �mlec 1.sat�r 1.s�tunda
      printf(lcd_veri,"Kendi LCD  Dosya"); // LCD'ye veri yazd�r�l�yor
      delay_ms(1000);
      imlec(2,4); // �mlec 2.sat�r 4.s�tunda
      printf(lcd_veri,"Denememiz"); // LCD'ye veri yazd�r�l�yor
      delay_ms(1000);

      lcd_komut(0x01); // LCD s�f�rlan�yor
      lcd_komut(0x0E); // �mle� alt �izgi modunda
      imlec(1,6); // �mlec 1.sat�r 6.s�tunda
      printf(lcd_veri,"C"); delay_ms(1000);
      printf(lcd_veri,"C"); delay_ms(1000);
      printf(lcd_veri,"S"); delay_ms(1000);
      printf(lcd_veri," C"); delay_ms(1000);

       lcd_komut(0x01); // LCD s�f�rlan�yor
   }
}
