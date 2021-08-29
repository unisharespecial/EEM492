/******************************************************
      PIC16F877 ile Timer2 Uygulamasý
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli
#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

unsigned int kesme=0; // Tamsayý tipinde 16 bitlik deðiþken tanýmlanýyor

//****************** Timer2 Kesmesi *****************************
#int_timer2  // Timer2 kesmesi
void  timer2_kesme ()   // Kesme fonksiyonu ismi
{
   kesme++; // kesme deðeri 1 arttýrýlýyor
   output_high(pin_b0); // RB0 lojik-1 yapýlýyor
   output_low(pin_b0);  // RB0 lojik-0 yapýlýyor
}

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

   setup_timer_2(T2_DIV_BY_16,250,16); // Timer2 ayarlarý yapýlýyor

   enable_interrupts(INT_timer2); // int_timer2 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1)    // Sonsuz döngü
   {
      if (input(pin_a0))   // RA0 butonuna basýldýðýnda
         output_b(kesme);  // kesme deðerini B portuna gönder
   }

 }
