/******************************************************
      PIC16F877 ile Step Motor Uygulamas� (ULN2003A �le)
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

// Giri� ve ��k�� pinlerine isim atan�yor
#define buton_ileri pin_a0
#define buton_geri  pin_a1

int i=0,hiz=10;

const int yarim_adim[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09}; // Step motor yar�m ad�m d�n�� ad�mlar�

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

   output_b(0x00);

   while(1) // Sonsuz d�ng�
   {

      if (input(buton_ileri)) // �LER� Butonuna bas�ld� ise
      {
         output_b(yarim_adim[i]);  // Step motor 1 ad�m ileri
         while(input(buton_ileri));// Bas�lan tu� b�rak�lana kadar bekle
         delay_ms(hiz);            // Ad�mlar aras� bekleme s�resi

         if (i==7)                 // i de�i�keni 7 olunca i de�eri -1 olsun
            i=-1;
         i++;                      // i de�i�kenini 1 artt�r

      }

      if (input(buton_geri)) // GER� Butonuna bas�ld� ise
      {
         if (i==0)                 // i de�i�keni 0 ise i de�eri 8 olsun
            i=8;
         i--;                      // i de�i�kenini 1 azalt
         output_b(yarim_adim[i]); // Step motora 1 ad�m geri
         while(input(buton_geri)); // Bas�lan tu� b�rak�lana kadar bekle
         delay_ms(hiz);            // Ad�mlar aras� bekleme s�resi
      }
   }
}
