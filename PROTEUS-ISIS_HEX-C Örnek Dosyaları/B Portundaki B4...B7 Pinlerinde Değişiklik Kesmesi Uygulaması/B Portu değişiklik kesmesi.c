/******************************************************
      PIC16F877 ile B portu RB4...RB7 De�i�iklik Kesmesi Uygulamas�
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

//*Port B RB4, RB5, RB6 ve RB7 pinleri de�i�iklik Kesme Fonksiyonu *
#int_RB                // PORTB de B4...B7 pinlerinde meydana gelen de�i�im kesmesi
void  B_degisiklik ()   // Kesme fonksiyonu ismi
{
   if (input(pin_b4))      // RB4 pini giri�i okunuyor.
      output_high(pin_b0); // RB0 ��k��� lojik-1 yap�l�yor.
   if (input(pin_b5))      // RB5 pini giri�i okunuyor.
      output_high(pin_b1); // RB1 ��k��� lojik-1 yap�l�yor.
   if (input(pin_b6))      // RB6 pini giri�i okunuyor.
      output_high(pin_b2); // RB2 ��k��� lojik-1 yap�l�yor.
   if (input(pin_b7))      // RB7 pini giri�i okunuyor.
      output_high(pin_b3); // RB3 ��k��� lojik-1 yap�l�yor
   delay_ms(2000);   // 2 sn gecikme veriliyor.
   output_b(0x00);   // B portu ��k��� komple s�f�rlan�yor.
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


   set_tris_b(0xF0);   // RB7,RB6,RB5,RB4 giri�, di�er u�lar ��k��

   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   enable_interrupts(INT_RB);  // INT_EXT kesmesini aktif yapar
   enable_interrupts(GLOBAL);  // Aktif edilen kesmelere izin ver
   
   while(1);   // Sonsuz d�ng�

 }
