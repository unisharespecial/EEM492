/******************************************************
      PIC16F877 ile B portu RB4...RB7 Deðiþiklik Kesmesi Uygulamasý
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

//*Port B RB4, RB5, RB6 ve RB7 pinleri deðiþiklik Kesme Fonksiyonu *
#int_RB                // PORTB de B4...B7 pinlerinde meydana gelen deðiþim kesmesi
void  B_degisiklik ()   // Kesme fonksiyonu ismi
{
   if (input(pin_b4))      // RB4 pini giriþi okunuyor.
      output_high(pin_b0); // RB0 çýkýþý lojik-1 yapýlýyor.
   if (input(pin_b5))      // RB5 pini giriþi okunuyor.
      output_high(pin_b1); // RB1 çýkýþý lojik-1 yapýlýyor.
   if (input(pin_b6))      // RB6 pini giriþi okunuyor.
      output_high(pin_b2); // RB2 çýkýþý lojik-1 yapýlýyor.
   if (input(pin_b7))      // RB7 pini giriþi okunuyor.
      output_high(pin_b3); // RB3 çýkýþý lojik-1 yapýlýyor
   delay_ms(2000);   // 2 sn gecikme veriliyor.
   output_b(0x00);   // B portu çýkýþý komple sýfýrlanýyor.
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


   set_tris_b(0xF0);   // RB7,RB6,RB5,RB4 giriþ, diðer uçlar çýkýþ

   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   enable_interrupts(INT_RB);  // INT_EXT kesmesini aktif yapar
   enable_interrupts(GLOBAL);  // Aktif edilen kesmelere izin ver
   
   while(1);   // Sonsuz döngü

 }
