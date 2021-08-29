/******************************************************
      PIC16F877 ile Capture Modu Uygulamas�
      PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli
#use fast_io(c) //Port y�nlendirme komutlar� C portu i�in ge�erli

int i=0; // Tamsay� tipinde de�i�ken tan�mlan�yor

//*********** CCP1 KESMES� ******************
#INT_CCP1   // INT_CCP1 kesmesi fonksiyonu
void yakala1_kesmesi ()
{
   i++;   // i de�erini 1 artt�r
   output_b(i); // i de�erini B portuna g�nder
}

//*********** CCP2 KESMES� ******************
#INT_CCP2   // INT_CCP2 kesmesi fonksiyonu
void yakala2_kesmesi ()
{
   if(i==0)   // E�er i de�eri s�f�rsa
      i=1;    // i de�eri i�eri�i 1 olsun

   i--;       // i de�erini 1 azalt
   output_b(i); // i de�erini B portuna g�nder
}

/********* ANA PROGRAM FONKS�YONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���

   set_tris_b(0x00);   // B portu komple ��k��
   set_tris_c(0x07);   // RC0, RC1 ve RC2 pini giri�

   output_b(0x00); // �lk anda B portu ��k��� s�f�rlan�yor

   enable_interrupts(INT_CCP1);  // INT_CCP1 kesmesi aktif yap�l�yor
   enable_interrupts(INT_CCP2);  // INT_CCP2 kesmesi aktif yap�l�yor
   enable_interrupts(GLOBAL);    // Aktif edilen kesmelere izin ver

   setup_ccp1(CCP_CAPTURE_DIV_4); // CCP1 kesmesi her 4 y�kselen kenarda 1 yakalama yapacak
   setup_ccp2(CCP_CAPTURE_RE);    // CCP2 kesmesi her y�kselen kenarda 1 yakalama yapacak

   CCP_1_HIGH=0x00; // CCPR1H kaydedicisi s�f�rlan�yor
   CCP_1_LOW=0x00;  // CCPR1H kaydedicisi s�f�rlan�yor

   CCP_2_HIGH=0x00; // CCPR2H kaydedicisi s�f�rlan�yor
   CCP_2_LOW=0x00;  // CCPR2H kaydedicisi s�f�rlan�yor

   while(1); // Sonsuz d�ng�
}

