/******************************************************
 Uygulama Ad�      : Y�r�yen I��k
 PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

int i, led; //i ve led isminde tam say� tipinde 8 bitlik de�i�kenler tan�t�l�yor.

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

   set_tris_b(0x00);    // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   output_b(0x00);      // B portu ��k��lar� s�f�rlan�yor

   while(1)
   {
      led=1;      //led de�i�keni de�eri 1 oluyor

      for(i=0;i<=7;i++)   // for d�ng�s� olu�turuluyor
      {
         output_b(led);      // led de�i�keni de�eri B portuna g�nder
         led=led<<1;         // led de�i�keni de�erini 1 bit sola kayd�r
         delay_ms(100);      // 100 msn'lik gecikme veriliyor
      }

      led=0x80;       //led de�i�kenine de�er y�kleniyor
      output_b(led);  //B portuna 0b10000000 bilgisi g�nderiliyor
      delay_ms(100);  // 100 msn'lik gecikme veriliyor
      
       for(i=0;i<=6;i++)  // for d�ng�s� olu�turuluyor
      {
         led=led>>1;    // led de�i�keni de�erini 1 bit sa�a kayd�r
         output_b(led); // led de�i�keni de�eri B portuna g�nder
         delay_ms(100); // 100 msn'lik gecikme veriliyor
      }
   }
}




