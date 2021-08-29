/******************************************************
      PIC16F877 ile Led Toggle Uygulamasý

Bu program ile B portuna baðlý 8 LED'i TOGGLE komutu ile
sýrayla yakýp söndürmektedir.

Yazan   :SERDAR ÇÝÇEK
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use fast_io(b) // Port yönlendirme komutlarý B portu için geçerli

/********* ANA PROGRAM FONKSÝYONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_b(0x00);    // RB0 portu tümüyle çýkýþ olarak ayarlandý.

   output_b(0x00);      // B portu çýkýþý sýfýrlanýyor

   basla:

   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b0);  // RB0 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b1);  // RB1 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b2);  // RB2 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b3);  // RB3 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b4);  // RB4 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b5);  // RB5 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b6);  // RB6 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor
   output_toggle(pin_b7);  // RB7 ucunun çýkýþ durumu tersleniyor
   delay_ms(500);          // 500 ms'lik gecikme veriliyor

   goto basla;
}
