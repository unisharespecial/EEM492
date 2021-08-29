/******************************************************
      PIC16F877A ile Paralel Slave Port Mod�l� Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/

#include <16f877A.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

/********* ANA PROGRAM FONKS�YONU********/
void main ( )
{
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���
   setup_comparator(NC_NC_NC_NC);  // Kar��la�t�r�c� birimi devre d���
   setup_VREF(FALSE);              // Voltaj referans birimi devre d���

   setup_psp(PSP_ENABLED);  // PSP mod�l� a��k

   while (1)  // Sonsuz d�ng�
   {
      output_b(PSP_DATA); // PSP veri yolundaki bilgiyi B portuna g�nder
   }
}
