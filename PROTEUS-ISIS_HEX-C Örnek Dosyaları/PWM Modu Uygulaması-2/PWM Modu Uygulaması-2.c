/******************************************************
      PIC16F877 ile PWM Modu Uygulamas�-2
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(c) //Port y�nlendirme komutlar� C portu i�in ge�erli

int i=65; // Tamsay� tipinde de�i�ken tan�mlan�yor

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���

   set_tris_a(0x03);   // RA0 ve RA1 pinleri giri�
   set_tris_c(0x00);   // C portu komple ��k��

   setup_ccp1(CCP_PWM);  // CCP1 birimi PWM ��k��� i�in ayarland�

   setup_timer_2(T2_DIV_BY_16,i,1); // Timer2 ayarlar� yap�l�yor

   set_pwm1_duty(50); // PWM1 ��k��� g�rev sayk�l� belirleniyor

   while(1) // Sonsuz d�ng�
   {
      if (input(pin_a0)) // E�er RA1 giri�ine ba�l� butona bas�l�rsa
      {
         delay_ms(20);         // Buton ark� �nleme gecikmesi
         while(input(pin_a0)); // Bas�l� butondan el �ekile kadar bekle
         i+=5; // i=i+5 anlam�ndad�r.

         if (i>250) // i de�eri 250'dan b�y�kse i de�eri 250 olsun
            i=250;
         setup_timer_2(T2_DIV_BY_16,i,1); // Timer2 ayarlar� yap�l�yor
      }

      if (input(pin_a1)) // E�er RA0 giri�ine ba�l� butona bas�l�rsa
      {
         delay_ms(20);         // Buton ark� �nleme gecikmesi
         while(input(pin_a1)); // Bas�l� butondan el �ekile kadar bekle
         i-=5;  // i=i-5 anlam�ndad�r.

         if (i<65) // i de�eri 65'den k���k ise i de�eri 65 olsun
            i=65;
         setup_timer_2(T2_DIV_BY_16,i,1); // Timer2 ayarlar� yap�l�yor
      }
   }
}

