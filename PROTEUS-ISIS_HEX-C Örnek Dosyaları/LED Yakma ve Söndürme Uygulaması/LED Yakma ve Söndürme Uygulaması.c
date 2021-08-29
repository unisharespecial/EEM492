/******************************************************
 Uygulama Ad�      : PIC16F877 ile Led Yakma ve S�nd�rme Program�
 Program�n Amac�   : RB0 pinine ba�l� LED'i belli aral�klarla yak�p s�nd�rmek
 PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
 Yazan             : SERDAR ���EK
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use fast_io(b) // Port y�nlendirme komutlar� B portu i�in ge�erli

/********* ANA PROGRAM FONKS�YONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_b(0x00);    // B portu komple ��k�� olarak y�nlendiriliyor

   output_b(0x00);        // B portu ��k��� komple s�f�r yap�l�yor.

   basla:               // Etiket ismi

   output_high(pin_b0);  // RB0 pini ��k��� lojik-1 yap�l�yor
   delay_ms(500);        // 500 ms gecikme veriliyor
   output_low(pin_b0);   // RB0 pini ��k��� lojik-1 yap�l�yor
   delay_ms(500);        // 500 ms gecikme veriliyor

   goto basla;           // basla etiketine dallan�l�yor
}
