/******************************************************
      PIC16F877 ile Led Toggle Uygulamas�

Bu program ile B portuna ba�l� 8 LED'i TOGGLE komutu ile
s�rayla yak�p s�nd�rmektedir.

Yazan   :SERDAR ���EK
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

   set_tris_b(0x00);    // RB0 portu t�m�yle ��k�� olarak ayarland�.

   output_b(0x00);      // B portu ��k��� s�f�rlan�yor

   basla:

   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b0);  // RB0 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b1);  // RB1 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b2);  // RB2 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b3);  // RB3 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b4);  // RB4 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b5);  // RB5 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b6);  // RB6 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b7);  // RB7 ucunun ��k�� durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor

   goto basla;
}
