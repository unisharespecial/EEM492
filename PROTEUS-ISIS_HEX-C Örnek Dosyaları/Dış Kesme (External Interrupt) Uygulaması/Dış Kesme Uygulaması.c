/******************************************************
      PIC16F877 ile D�� Kesme (INT_EXT) Uygulamas�
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

int i; // Tamsay� tipinde de�i�ken tan�mlan�yor

//****** D�� Kesme Fonksiyonu *****************
#int_ext                // D�� (External) RB0/INT kesmesi
void  ext_kesmesi ()    // D�� kesme fonksiyonu
{
   output_high(pin_b1);
   delay_ms(1000);
   output_low(pin_b1);
   delay_ms(3000);

   for (i=0;i<10;i++)
   {
      output_high(pin_b1);
      delay_ms(500);
      output_low(pin_b1);
      delay_ms(500);
   }
}


/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���


   set_tris_b(0x01);   // RB0 pini giri�,di�er u�lar ��k�� olarak y�nlendiriliyor
   output_b(0x00);     // B portu ��k��� ilk anda s�f�rlan�yor

   ext_int_edge(H_TO_L);   // INT_EXT kesmesinin d��en kenarda aktif olaca��n� belirtir

   enable_interrupts(INT_EXT);  // INT_EXT kesmesini aktif yapar
   enable_interrupts(GLOBAL);   // Aktif edilen kesmelere izin ver

   while(1);  // Sonsuz d�ng�
 }
