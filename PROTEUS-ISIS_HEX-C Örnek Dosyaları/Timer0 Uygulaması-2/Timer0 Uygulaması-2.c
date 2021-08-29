/******************************************************
      PIC16F877 ile Timer0 Uygulamas�-2
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

int sayi=0; // Tamsay� tipinde de�i�ken tan�mlan�yor

//****************** Timer0 Kesmesi *****************************
#int_timer0  // Timer0 kesmesi
void  timer0_kesme ()   // Kesme fonksiyonu ismi
{
      set_timer0(254);   // TMR0 de�eri belirleniyor

       sayi++; // sayi de�eri 1 arttr�l�yor
       output_b(sayi);   // sayi de�eri B portuna g�nderiliyor

   if (sayi==15)   // sayi de�eri 15 olunca s�f�rla
      sayi=0;
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

   set_tris_a(0x10); // RA4 pini giri�
   set_tris_b(0x00);   // B portu komple ��k��

   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   setup_timer_0(RTCC_EXT_H_TO_L | RTCC_DIV_2); // Timer0 ayarlar� yap�l�yor
   set_timer0(254);   // TMR0 de�eri belirleniyor

   enable_interrupts(INT_timer0); // int_timer0 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1);   // Sonsuz d�ng�

 }
