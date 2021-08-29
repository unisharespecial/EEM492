/******************************************************
      PIC16F877A ile Karþýlaþtýrýcý Modülü Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/

#include <16f877A.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli
#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

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

   set_tris_a(0x0B);   // RA0,RA1,RA3 pini giriþ,RA2 çýkýþ
   set_tris_b(0x00);   // B portu komple çýkýþ

   output_b(0x00);     // Ýlk anda B portu çýkýþýný sýfýrla

   setup_comparator(A0_A3_A1_A3);      // Karþýlaþtýrýcý modülü ayarlarý yapýlýyor
   setup_vref (VREF_A2|VREF_HIGH |15); // Voltaj referans modülü ayarlarý yapýlýyor

   while (1)  // Sonsuz döngü
   {
      if (C1OUT==1)  // Karþýlaþtýrýcý-1 çýkýþý "1" ise
         output_high(pin_b0);  // RB0 çýkýþý lojik-1
      else
         output_low(pin_b0);   // RB0 çýkýþý lojik-0

      if (C2OUT==1) // Karþýlaþtýrýcý-2 çýkýþý "1" ise
         output_high(pin_b1); // RB1 çýkýþý lojik-1
      else
         output_low(pin_b1);  // RB1 çýkýþý lojik-0
   }
}
