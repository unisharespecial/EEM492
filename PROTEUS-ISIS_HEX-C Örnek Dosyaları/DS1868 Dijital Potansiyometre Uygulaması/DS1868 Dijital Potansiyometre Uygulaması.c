/******************************************************************
 PIC16F877 ile DS1868 Dijital Potansiyometre Uygulamasý
*******************************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk                 // dosyasý tanýtýlýyor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#include <DS1868.c>  // DS1868.c dosyasý programa ekleniyor

// Butonlar ve Anahtar Tanýmlamalarý Yapýlýyor
#define pot_reset pin_a0
#define pot_sec   pin_a1
#define arttir    pin_a2
#define azalt     pin_a3

int i=0,j=0; // Tam sayý tipinde deðiþkenler tanýmlanýyor

//******************* ANA PROGRAM FONKSÝYONU *******************
void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   init_pots(); // 2 potansiyometre deðeri ilk anda sýfýrlanýyor

   while(1) // Sonsuz döngü
   {
     if (input(pot_reset))  // Eðer Pot reset butonuna basýldý ise
     {
        init_pots();        // 2 potansiyometreyi de sýfýrla
        i=0; j=0;           // i ve j deðerleri de sýfýrla
     }

     if (input(pot_sec)) // 0. Potansiyometre seçilmiþ ise
     {
        if (input(arttir))       // Arttir butonuna basýlmýþ ise
        {
           i++;                  // i deðerini bir arttýr
           set_pot(0,i);         // 0. potansiyometreyi i deðerine ayarla
           while(input(arttir)); // Butondan el çekile kadar bekle
        }

        if (input(azalt) && (i!=0)) // Azalt butonuna basýlmýþ ise ve
        {                           // i deðeri 0 deðil ise
           i--;                     // i deðerini bir azalt
           set_pot(0,i);            // 0. potansiyometreyi i deðerine ayarla
           while(input(azalt));     // Butondan el çekile kadar bekle
        }
     }
     else  // 1. potansiyometre seçilmiþ ise
     {
        if (input(arttir))       // Arttir butonuna basýlmýþ ise
        {
           j++;                  // j deðerini bir arttýr
           set_pot(1,j);         // 1. potansiyometreyi j deðerine ayarla
           while(input(arttir)); // Butondan el çekile kadar bekle
        }

        if (input(azalt) && (j!=0)) // Azalt butonuna basýlmýþ ise ve
        {                           // j deðeri 0 deðil ise
           j--;                     // j deðerini bir azalt
           set_pot(1,j);            // 1. potansiyometreyi j deðerine ayarla
           while(input(azalt));     // Butondan el çekile kadar bekle
        }
     }
   }
}
