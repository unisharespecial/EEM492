/******************************************************
      PIC16F877A ile Kar��la�t�r�c� Mod�l� Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/

#include <16f877A.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

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

   set_tris_a(0x0B);   // RA0,RA1,RA3 pini giri�,RA2 ��k��
   set_tris_b(0x00);   // B portu komple ��k��

   output_b(0x00);     // �lk anda B portu ��k���n� s�f�rla

   setup_comparator(A0_A3_A1_A3);      // Kar��la�t�r�c� mod�l� ayarlar� yap�l�yor
   setup_vref (VREF_A2|VREF_HIGH |15); // Voltaj referans mod�l� ayarlar� yap�l�yor

   while (1)  // Sonsuz d�ng�
   {
      if (C1OUT==1)  // Kar��la�t�r�c�-1 ��k��� "1" ise
         output_high(pin_b0);  // RB0 ��k��� lojik-1
      else
         output_low(pin_b0);   // RB0 ��k��� lojik-0

      if (C2OUT==1) // Kar��la�t�r�c�-2 ��k��� "1" ise
         output_high(pin_b1); // RB1 ��k��� lojik-1
      else
         output_low(pin_b1);  // RB1 ��k��� lojik-0
   }
}
