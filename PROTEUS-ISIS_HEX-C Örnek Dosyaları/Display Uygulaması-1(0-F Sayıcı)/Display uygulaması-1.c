/******************************************************
 Uygulama Ad�      : Display Uygulamas�-1 (0-F Say�c�)
 PIC PROG/DEKA     : Port B jumper'� 7-seg konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

int i;  // i isminde 8 bitlik bir de�i�ken tan�t�l�yor.

// Ortak katot display i�in veri de�erleri
const int digit[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

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

   set_tris_a(0x00); // A portu t�m�yle ��k�� olarak y�nlendiriliyor
   set_tris_b(0x00); // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   output_b(0x00);  // B portu ��k��lar� s�f�rlan�yor
   output_a(0x02);  // RA1 pini lojik-1 yap�l�yor, di�er pinler lojik-0

   while(1)   // Sonsuz d�ng� olu�turuluyor
   {
      for(i=0;i<=15;i++)
      {
         output_b(digit[i]); // digit[i] de�erini B portuna g�nder
         delay_ms(500);      // 500 msn bekle
      }
   }
}

