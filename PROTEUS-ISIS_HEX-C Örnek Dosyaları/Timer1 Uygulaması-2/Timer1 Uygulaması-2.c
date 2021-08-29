/******************************************************
      PIC16F877 ile Timer1 Uygulamasý-2
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli
#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli

unsigned int kesme=0; // Tamsayý tipinde 16 bitlik deðiþken tanýmlanýyor

//****************** Timer1 Kesmesi *****************************
#int_timer1 // Timer1 kesmesi
void  timer1_kesme ()   // Kesme fonksiyonu ismi
{clear_interrupt(int_timer1);
   set_timer1(65530); // TMR1 deðeri belirleniyor

   kesme++; // kesme deðeri 1 arttýrýlýyor
   output_b(kesme); // kesme deðeri B portuna aktarýlýyor

   if (kesme==255)   // Eðer kesme deðeri 255 olursa kesme deðerini sýfýrla
      kesme=0;
}

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý


   set_tris_b(0x00);   // B portu komple çýkýþ
   set_tris_c(0x01);   // RC0 pini giriþ

   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   setup_timer_1(T1_EXTERNAL | T1_DIV_BY_2); // Timer1 ayarlarý yapýlýyor
   set_timer1(65530);   // TMR1 deðeri belirleniyor


   enable_interrupts(INT_timer1); // int_timer1 kesmesini aktif yapar
   enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

   while(1); // Sonsuz döngü

 }
