/******************************************************
      PIC16F877 ile Timer0 Uygulamas�-1
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

int i=0; // Tamsay� tipinde de�i�ken tan�mlan�yor

//****************** Timer0 Kesmesi *****************************
#int_timer0  // Timer0 kesmesi
void  timer0_kesme ()   // Kesme fonksiyonu ismi
{
    set_timer0(60);   // TMR0 de�eri belirleniyor
    i++;   // i de�eri 1 artt�r�l�yor
    if (i==10)  // i de�eri 10'a e�itse RB0 ��k��� lojik-1 olsun
       output_high(pin_b0);
    if (i==20)  // i de�eri 20'ye e�itse RB0 ��k��� lojik-1 olsun ve i de�eri s�f�rlans�n
       {
          output_low(pin_b0);
          i=0;
       }
}

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


   set_tris_b(0x00);   // B portu komple ��k��

   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); // Timer0 ayarlar� yap�l�yor
   set_timer0(60);   // TMR0 de�eri belirleniyor


   enable_interrupts(INT_timer0); // int_timer0 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1);   // Sonsuz d�ng�

 }
