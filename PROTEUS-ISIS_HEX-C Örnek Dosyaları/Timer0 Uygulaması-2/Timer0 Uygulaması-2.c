/******************************************************
      PIC16F877 ile Timer0 Uygulamasý-2
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli
#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

int sayi=0; // Tamsayý tipinde deðiþken tanýmlanýyor

//****************** Timer0 Kesmesi *****************************
#int_timer0  // Timer0 kesmesi
void  timer0_kesme ()   // Kesme fonksiyonu ismi
{
      set_timer0(254);   // TMR0 deðeri belirleniyor

       sayi++; // sayi deðeri 1 arttrýlýyor
       output_b(sayi);   // sayi deðeri B portuna gönderiliyor

   if (sayi==15)   // sayi deðeri 15 olunca sýfýrla
      sayi=0;
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

   set_tris_a(0x10); // RA4 pini giriþ
   set_tris_b(0x00);   // B portu komple çýkýþ

   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   setup_timer_0(RTCC_EXT_H_TO_L | RTCC_DIV_2); // Timer0 ayarlarý yapýlýyor
   set_timer0(254);   // TMR0 deðeri belirleniyor

   enable_interrupts(INT_timer0); // int_timer0 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1);   // Sonsuz döngü

 }
