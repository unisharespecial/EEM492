/*******************************************************
PIC16F877 ile Kendi �zel Karakterli LCD Dosyam�zla LCD Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#include <�zel_karakter_LCD.c> // �zelkarakter__LCD.c dosyas� programa ekleniyor

float x=23.5;  // Ondal�kl� tipte de�i�ken tan�mlan�yor

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
   ozel_karakterler(); // �zel karakterler CGRAM'e y�kleniyor

   while(1) // Sonsuz d�ng�
   {
      imlec(1,1); // �mlec 1.sat�r 1.s�tunda
      printf(lcd_veri,"�ZEL KARAKTERL�"); // LCD'ye veri yazd�r�l�yor

      imlec(2,1); // �mlec 2.sat�r 1.s�tunda
      printf(lcd_veri,"LCD UYGULAMASI"); // LCD'ye veri yazd�r�l�yor
      delay_ms(1000);

      lcd_komut(0x01); // LCD s�f�rlan�yor
      printf(lcd_veri,"�ZEL KARAKTERLER"); // LCD'ye veri yazd�r�l�yor

      imlec(2,1); // �mlec 2.sat�r 1.s�tunda
      printf(lcd_veri,"�"); delay_ms(1000);
      printf(lcd_veri,"�"); delay_ms(1000);
      printf(lcd_veri,"�"); delay_ms(1000);
      printf(lcd_veri,"�"); delay_ms(1000);
      printf(lcd_veri,"�"); delay_ms(1000);
      printf(lcd_veri,"�"); delay_ms(1000);
      printf(lcd_veri,"'"); delay_ms(1000);
      printf(lcd_veri,"I"); delay_ms(1000);

      lcd_komut(0x01); // LCD s�f�rlan�yor
      printf(lcd_veri,"SICAKLIK %f'C",x); delay_ms(3000);

      lcd_komut(0x01); // LCD s�f�rlan�yor
   }
}

