/******************************************************
      PIC16F877 ile Tu� Tak�m� Uygulamas�-2 (74C922 �le)
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k                 // dosyas� tan�t�l�yor.
// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.
#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli
#use fast_io(c) //Port y�nlendirme komutlar� C portu i�in ge�erli

#byte   portc=0x07   // C portu "portc" ismine e�itleniyor.

char const keys[] ={1,2,3,0,   // Gelen bilgilere g�re g�sterilmesi
                    4,5,6,0,    // istenen karakterler
                    7,8,9,0,
                    0xF,0,0xF,0 };

//*********** D�� Kesme Fonksiyonu Tan�mlan�yor ********
#int_ext            // D�� kesme fonksiyonu
void dis_kesme ()
{
   portc=keys[portc>>4];  // C portuna C portunun okunan y�ksek de�erlikli 4 biti aktar�l�yor
}


//********** ANA PROGRAM FONKS�YONU*******
void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���

   set_tris_b(0x01);   // B portu komple ��k��
   set_tris_c(0xF0);   // C portunun Y�ksek de�erlikli 4 bit ��k��, d���k de�erlikli 4 bit giri�

   ext_int_edge(L_TO_H);  // INT_EXT d�� kesmesinin y�kselen kenarda aktif olaca��n� belirtir

   enable_interrupts(INT_EXT);  // D�� kesme aktif
   enable_interrupts(GLOBAL);   // Aktif edilen kesmelere izin ver

   portc=0;  // Ba�lang��ta C portu ��k��� s�f�rlan�yor

   while(1);  // Sonsuz d�ng�
}

