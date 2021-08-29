/******************************************************
      PIC16F877 ile Timer2 Uygulamas�
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

unsigned int kesme=0; // Tamsay� tipinde 16 bitlik de�i�ken tan�mlan�yor

//****************** Timer2 Kesmesi *****************************
#int_timer2  // Timer2 kesmesi
void  timer2_kesme ()   // Kesme fonksiyonu ismi
{
   kesme++; // kesme de�eri 1 artt�r�l�yor
   output_high(pin_b0); // RB0 lojik-1 yap�l�yor
   output_low(pin_b0);  // RB0 lojik-0 yap�l�yor
}

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 birimi devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0x01);   // RA0 pini giri�
   set_tris_b(0x00);   // B portu komple ��k��

   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   setup_timer_2(T2_DIV_BY_16,250,16); // Timer2 ayarlar� yap�l�yor

   enable_interrupts(INT_timer2); // int_timer2 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1)    // Sonsuz d�ng�
   {
      if (input(pin_a0))   // RA0 butonuna bas�ld���nda
         output_b(kesme);  // kesme de�erini B portuna g�nder
   }

 }
