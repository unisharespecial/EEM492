/******************************************************
      PIC16F877 ile DC Motor Uygulamas�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

// Giri� ve ��k�� pinlerine isim atan�yor
#define buton_ileri pin_a0
#define buton_geri  pin_a1
#define buton_stop  pin_a2
#define input1      pin_b0
#define input2      pin_b1
#define enable_a    pin_b2
#define enable_b    pin_b3

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

   output_high(enable_a); // K�pr� A se�ili
   output_low(enable_b);  // K�pr� B pasif

   while(1) // Sonsuz d�ng�
   {
      if (input(buton_ileri)) // �LER� Butonuna bas�ls� ise
      {
         output_high(input1); // L298 Input1 giri�i lojik-1
         output_low(input2);  // L298 Input2 giri�i lojik-0
      }

      if (input(buton_geri)) // GER� Butonuna bas�ls� ise
      {
         output_low(input1);  // L298 Input1 giri�i lojik-0
         output_high(input2); // L298 Input1 giri�i lojik-1
      }
      if (input(buton_stop)) // HIZLI STOP Butonuna bas�ls� ise
      {
         output_low(input1); // L298 Input1 giri�i lojik-0
         output_low(input2); // L298 Input1 giri�i lojik-0
         // H�zl� stop i�in burada her iki giri�te lojik-1 olabilirdi.
         // �nemli olan H�zl� Stop i�in, her iki giri�in ayn� seviyede olmas�
      }

   }
}
