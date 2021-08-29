/******************************************************************
 PIC16F877 ile DS1868 Dijital Potansiyometre Uygulamas�
*******************************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k                 // dosyas� tan�t�l�yor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#include <DS1868.c>  // DS1868.c dosyas� programa ekleniyor

// Butonlar ve Anahtar Tan�mlamalar� Yap�l�yor
#define pot_reset pin_a0
#define pot_sec   pin_a1
#define arttir    pin_a2
#define azalt     pin_a3

int i=0,j=0; // Tam say� tipinde de�i�kenler tan�mlan�yor

//******************* ANA PROGRAM FONKS�YONU *******************
void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   init_pots(); // 2 potansiyometre de�eri ilk anda s�f�rlan�yor

   while(1) // Sonsuz d�ng�
   {
     if (input(pot_reset))  // E�er Pot reset butonuna bas�ld� ise
     {
        init_pots();        // 2 potansiyometreyi de s�f�rla
        i=0; j=0;           // i ve j de�erleri de s�f�rla
     }

     if (input(pot_sec)) // 0. Potansiyometre se�ilmi� ise
     {
        if (input(arttir))       // Arttir butonuna bas�lm�� ise
        {
           i++;                  // i de�erini bir artt�r
           set_pot(0,i);         // 0. potansiyometreyi i de�erine ayarla
           while(input(arttir)); // Butondan el �ekile kadar bekle
        }

        if (input(azalt) && (i!=0)) // Azalt butonuna bas�lm�� ise ve
        {                           // i de�eri 0 de�il ise
           i--;                     // i de�erini bir azalt
           set_pot(0,i);            // 0. potansiyometreyi i de�erine ayarla
           while(input(azalt));     // Butondan el �ekile kadar bekle
        }
     }
     else  // 1. potansiyometre se�ilmi� ise
     {
        if (input(arttir))       // Arttir butonuna bas�lm�� ise
        {
           j++;                  // j de�erini bir artt�r
           set_pot(1,j);         // 1. potansiyometreyi j de�erine ayarla
           while(input(arttir)); // Butondan el �ekile kadar bekle
        }

        if (input(azalt) && (j!=0)) // Azalt butonuna bas�lm�� ise ve
        {                           // j de�eri 0 de�il ise
           j--;                     // j de�erini bir azalt
           set_pot(1,j);            // 1. potansiyometreyi j de�erine ayarla
           while(input(azalt));     // Butondan el �ekile kadar bekle
        }
     }
   }
}
