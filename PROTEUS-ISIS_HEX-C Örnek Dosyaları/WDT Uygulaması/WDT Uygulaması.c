/******************************************************
      PIC16F877 ile WDT Uygulamas�
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,WDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 birimi devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0x01);   // RA0 pini giri�
   set_tris_b(0x00);   // B portu komple ��k��

   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   setup_WDT(WDT_2304MS); // WDT ayarlar� yap�l�yor

   while(1)    // Sonsuz d�ng�
   {
      output_toggle(pin_b0); // RB0 ucunun ��k�� durumu tersleniyor

      while (input(pin_a0)) // E�er RA0 giri�indeki butona bas�ld� ise
         restart_wdt();     // WDT'� s�f�rla

      sleep();   // Denetleyici uyku moduna al�n�yor.
   }

 }
