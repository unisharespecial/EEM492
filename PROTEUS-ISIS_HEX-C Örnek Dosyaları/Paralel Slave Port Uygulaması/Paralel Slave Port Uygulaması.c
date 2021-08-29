/******************************************************
      PIC16F877A ile Paralel Slave Port Modülü Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/

#include <16f877A.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

/********* ANA PROGRAM FONKSÝYONU********/
void main ( )
{
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý
   setup_comparator(NC_NC_NC_NC);  // Karþýlaþtýrýcý birimi devre dýþý
   setup_VREF(FALSE);              // Voltaj referans birimi devre dýþý

   setup_psp(PSP_ENABLED);  // PSP modülü açýk

   while (1)  // Sonsuz döngü
   {
      output_b(PSP_DATA); // PSP veri yolundaki bilgiyi B portuna gönder
   }
}
