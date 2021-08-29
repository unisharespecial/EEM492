/******************************************************
 Uygulama Ad�      : Buton ile BCD Say�c�
 Program�n Amac�   : RA0 butonuna her bas��ta 0'dan itibaren artan BCD say�lar
                     B portuna ba�l� LED'lerde g�r�necektir
 PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#define buton pin_A0    // "buton" ad�nda "pin_A0" kelimesine e�it bir sabit tan�mlan�yor

int i=1;     // 8 bitlik tamsay� tipinde de�i�ken tan�mlan�yor

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

   set_tris_a(0x01);    // RA0 pini giri� olarak y�nlendiriliyor
   set_tris_b(0x00);    // RB0 portu t�m�yle ��k�� olarak y�nlendiriliyor

   output_b(0x00);      // B portu ��k��lar� s�f�rlan�yor

   while(1)       // Sonsuz d�ng� olu�turuluyor
   {
      if (input(buton))
      {
         delay_ms(15);  // Butona bas�l�nca meydana gelen ark�n etkisini �nlemek i�in verilen gecikme
         output_b(i);   // b portuna i de�eri y�kleniyor
         i=i+1;         // i de�eri 1 artt�r�l�yor
         while(input(buton)); // Buton b�rak�lana kadar bekle
         if (i==10)     // i de�eri test ediliyor.i de�eri 10 olunca s�f�rlan�yor.
         {
            i=0;        // i de�eri s�f�rlan�yor
         }
      }
   }
}
