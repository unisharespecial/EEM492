/******************************************************
      PIC16F877 ile Step Motor Uygulamasý (ULN2003A Ýle)
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

// Giriþ ve çýkýþ pinlerine isim atanýyor
#define buton_ileri pin_a0
#define buton_geri  pin_a1

int i=0,hiz=10;

const int yarim_adim[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09}; // Step motor yarým adým dönüþ adýmlarý

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   output_b(0x00);

   while(1) // Sonsuz döngü
   {

      if (input(buton_ileri)) // ÝLERÝ Butonuna basýldý ise
      {
         output_b(yarim_adim[i]);  // Step motor 1 adým ileri
         while(input(buton_ileri));// Basýlan tuþ býrakýlana kadar bekle
         delay_ms(hiz);            // Adýmlar arasý bekleme süresi

         if (i==7)                 // i deðiþkeni 7 olunca i deðeri -1 olsun
            i=-1;
         i++;                      // i deðiþkenini 1 arttýr

      }

      if (input(buton_geri)) // GERÝ Butonuna basýldý ise
      {
         if (i==0)                 // i deðiþkeni 0 ise i deðeri 8 olsun
            i=8;
         i--;                      // i deðiþkenini 1 azalt
         output_b(yarim_adim[i]); // Step motora 1 adým geri
         while(input(buton_geri)); // Basýlan tuþ býrakýlana kadar bekle
         delay_ms(hiz);            // Adýmlar arasý bekleme süresi
      }
   }
}
