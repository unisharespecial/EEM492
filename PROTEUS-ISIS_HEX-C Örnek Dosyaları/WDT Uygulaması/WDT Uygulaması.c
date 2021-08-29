/******************************************************
      PIC16F877 ile WDT Uygulamasý
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,WDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli
#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 birimi devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_a(0x01);   // RA0 pini giriþ
   set_tris_b(0x00);   // B portu komple çýkýþ

   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   setup_WDT(WDT_2304MS); // WDT ayarlarý yapýlýyor

   while(1)    // Sonsuz döngü
   {
      output_toggle(pin_b0); // RB0 ucunun çýkýþ durumu tersleniyor

      while (input(pin_a0)) // Eðer RA0 giriþindeki butona basýldý ise
         restart_wdt();     // WDT'ý sýfýrla

      sleep();   // Denetleyici uyku moduna alýnýyor.
   }

 }
