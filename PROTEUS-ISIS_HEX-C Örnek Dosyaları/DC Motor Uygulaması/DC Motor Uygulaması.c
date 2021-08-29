/******************************************************
      PIC16F877 ile DC Motor Uygulamasý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

// Giriþ ve çýkýþ pinlerine isim atanýyor
#define buton_ileri pin_a0
#define buton_geri  pin_a1
#define buton_stop  pin_a2
#define input1      pin_b0
#define input2      pin_b1
#define enable_a    pin_b2
#define enable_b    pin_b3

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

   output_high(enable_a); // Köprü A seçili
   output_low(enable_b);  // Köprü B pasif

   while(1) // Sonsuz döngü
   {
      if (input(buton_ileri)) // ÝLERÝ Butonuna basýlsý ise
      {
         output_high(input1); // L298 Input1 giriþi lojik-1
         output_low(input2);  // L298 Input2 giriþi lojik-0
      }

      if (input(buton_geri)) // GERÝ Butonuna basýlsý ise
      {
         output_low(input1);  // L298 Input1 giriþi lojik-0
         output_high(input2); // L298 Input1 giriþi lojik-1
      }
      if (input(buton_stop)) // HIZLI STOP Butonuna basýlsý ise
      {
         output_low(input1); // L298 Input1 giriþi lojik-0
         output_low(input2); // L298 Input1 giriþi lojik-0
         // Hýzlý stop için burada her iki giriþte lojik-1 olabilirdi.
         // Önemli olan Hýzlý Stop için, her iki giriþin ayný seviyede olmasý
      }

   }
}
