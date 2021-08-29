/******************************************************
      PIC16F877 ile Timer1 Uygulamasý-1
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

int i=0; // Tamsayý tipinde deðiþken tanýmlanýyor

//****************** Timer0 Kesmesi *****************************
#int_timer1  // Timer1 kesmesi
void  timer1_kesme ()   // Kesme fonksiyonu ismi
{
   set_timer1(63036); // TMR1 deðeri belirleniyor

   i++; // i deðeri 1 arttýrýlýyor

   if (i==50)    // i deðeri 50'ye eþit olursa RB0 lojik-1 olsun
      output_high(pin_b0);
   if (i==100)  // i deðeri 100'e eþit olursa RB0 lojik-0 ve i=0 olsun 
   {
      output_low(pin_b0);
      i=0;
   }
}

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý


   set_tris_b(0x00);   // B portu komple çýkýþ

   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); // Timer1 ayarlarý yapýlýyor
   set_timer1(63036);   // TMR1 deðeri belirleniyor


   enable_interrupts(INT_timer1); // int_timer0 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1); // Sonsuz döngü

 }

