/******************************************************
      PIC16F877 ile Timer0 Uygulamasý-1
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

int i=0; // Tamsayý tipinde deðiþken tanýmlanýyor

//****************** Timer0 Kesmesi *****************************
#int_timer0  // Timer0 kesmesi
void  timer0_kesme ()   // Kesme fonksiyonu ismi
{
    set_timer0(60);   // TMR0 deðeri belirleniyor
    i++;   // i deðeri 1 arttýrýlýyor
    if (i==10)  // i deðeri 10'a eþitse RB0 çýkýþý lojik-1 olsun
       output_high(pin_b0);
    if (i==20)  // i deðeri 20'ye eþitse RB0 çýkýþý lojik-1 olsun ve i deðeri sýfýrlansýn
       {
          output_low(pin_b0);
          i=0;
       }
}

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


   set_tris_b(0x00);   // B portu komple çýkýþ

   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); // Timer0 ayarlarý yapýlýyor
   set_timer0(60);   // TMR0 deðeri belirleniyor


   enable_interrupts(INT_timer0); // int_timer0 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1);   // Sonsuz döngü

 }
