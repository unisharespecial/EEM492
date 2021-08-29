/******************************************************************
 PIC16F877 ile Ses Uygulamas�
*******************************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k                 // dosyas� tan�t�l�yor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#include <TONES.c>  // TONES.c dosyas� programa ekleniyor

// Ses tonlar�ndan olu�an dizi tan�mlan�yor
const char muzik[48]={C_NOTE[0],C_NOTE[1],C_NOTE[2],C_NOTE[3],Db_NOTE[0],Db_NOTE[1],Db_NOTE[2],Db_NOTE[3],
                    D_NOTE[0],D_NOTE[1],D_NOTE[2],D_NOTE[3],Eb_NOTE[0],Eb_NOTE[1],Eb_NOTE[2],Eb_NOTE[3],
                    E_NOTE[0],E_NOTE[1],E_NOTE[2],E_NOTE[3],F_NOTE[0],F_NOTE[1],F_NOTE[2],F_NOTE[3],
                    Gb_NOTE[0],Gb_NOTE[1],Gb_NOTE[2],Gb_NOTE[3],G_NOTE[0],G_NOTE[1],G_NOTE[2],G_NOTE[3],
                    Ab_NOTE[0],Ab_NOTE[1],Ab_NOTE[2],Ab_NOTE[3],A_NOTE[0],A_NOTE[1],A_NOTE[2],A_NOTE[3],
                    Bb_NOTE[0],Bb_NOTE[1],Bb_NOTE[2],Bb_NOTE[3],B_NOTE[0],B_NOTE[1],B_NOTE[2],B_NOTE[3]   };

int i;  // Tam say� tipinde de�i�ken tan�mlan�yor

//******************* ANA PROGRAM FONKS�YONU *******************
void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   output_low(pin_b0); // RB0 ��k��� ilk anda lojik-0

   while(1) // Sonsuz d�ng�
   {
      for(i=0;i<48;i++)
      {
         generate_tone(muzik[i],100); delay_ms(50); // S�rayla muz�k[] dizisindeki
      }                                             // tonlar olu�turuluyor
  }
}
