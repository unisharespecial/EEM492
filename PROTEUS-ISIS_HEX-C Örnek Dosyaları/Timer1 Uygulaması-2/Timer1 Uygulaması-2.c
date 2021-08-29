/******************************************************
      PIC16F877 ile Timer1 Uygulamas�-2
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli
#use fast_io(c) //Port y�nlendirme komutlar� C portu i�in ge�erli

unsigned int kesme=0; // Tamsay� tipinde 16 bitlik de�i�ken tan�mlan�yor

//****************** Timer1 Kesmesi *****************************
#int_timer1 // Timer1 kesmesi
void  timer1_kesme ()   // Kesme fonksiyonu ismi
{clear_interrupt(int_timer1);
   set_timer1(65530); // TMR1 de�eri belirleniyor

   kesme++; // kesme de�eri 1 artt�r�l�yor
   output_b(kesme); // kesme de�eri B portuna aktar�l�yor

   if (kesme==255)   // E�er kesme de�eri 255 olursa kesme de�erini s�f�rla
      kesme=0;
}

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���


   set_tris_b(0x00);   // B portu komple ��k��
   set_tris_c(0x01);   // RC0 pini giri�

   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   setup_timer_1(T1_EXTERNAL | T1_DIV_BY_2); // Timer1 ayarlar� yap�l�yor
   set_timer1(65530);   // TMR1 de�eri belirleniyor


   enable_interrupts(INT_timer1); // int_timer1 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1); // Sonsuz d�ng�

 }
