/******************************************************
      PIC16F877 ile Compare Modu Uygulamas�
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli
#use fast_io(c) //Port y�nlendirme komutlar� C portu i�in ge�erli

//*********** CCP1 KESMES� ******************
#INT_CCP1   // INT_CCP1 kesmesi fonksiyonu
void karsilastir1_kesmesi ()
{
   output_toggle(pin_b0); // RB0 ��k��� tersleniyor
}

//*********** CCP2 KESMES� ******************
#INT_CCP2   // INT_CCP2 kesmesi fonksiyonu
void karsilastir2_kesmesi ()
{
   set_timer1(0);   // TMR1 i�eri�i s�f�rlan�yor
   output_toggle(pin_b1); // RB1 ��k��� tersleniyor
}

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���

   set_tris_b(0x00);   // B portu komple ��k��
   set_tris_c(0x01);   // RC0 pini giri�

   output_b(0x00); // �lk anda B portu ��k��� s�f�rlan�yor

   enable_interrupts(INT_CCP1);  // INT_CCP1 kesmesi aktif yap�l�yor
   enable_interrupts(INT_CCP2);  // INT_CCP2 kesmesi aktif yap�l�yor
   enable_interrupts(GLOBAL);    // Aktif edilen kesmelere izin ver

   setup_ccp1(CCP_COMPARE_INT); // CCP1 birimi COMPARE modunda kullan�lacak
   setup_ccp2(CCP_COMPARE_INT); // CCP2 birimi COMPARE modunda kullan�lacak


   setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1); // Timer1 ayarlar� yap�l�yor

   CCP_1_HIGH=0x00; // CCPR1H kaydedicisi s�f�rlan�yor
   CCP_1_LOW=0x05;  // CCPR1L kaydedicisine 05h de�eri y�kleniyor.

   CCP_2_HIGH=0x00; // CCPR2H kaydedicisi s�f�rlan�yor
   CCP_2_LOW=0x0A;  // CCPR2L kaydedicisine 0Ah de�eri y�kleniyor.

   set_timer1(0); // TMR1 i�eri�i s�f�rlan�yor

   while(1); // Sonsuz d�ng�
}


