/******************************************************
 Uygulama Adý      : PIC16F877 ile Led Yakma ve Söndürme Programý
 Programýn Amacý   : RB0 pinine baðlý LED'i belli aralýklarla yakýp söndürmek
 PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
 Yazan             : SERDAR ÇÝÇEK
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

   set_tris_b(0x00);    // B portu komple çýkýþ olarak yönlendiriliyor

   output_b(0x00);        // B portu çýkýþý komple sýfýr yapýlýyor.

   basla:               // Etiket ismi

   output_high(pin_b0);  // RB0 pini çýkýþý lojik-1 yapýlýyor
   delay_ms(500);        // 500 ms gecikme veriliyor
   output_low(pin_b0);   // RB0 pini çýkýþý lojik-1 yapýlýyor
   delay_ms(500);        // 500 ms gecikme veriliyor

   goto basla;           // basla etiketine dallanýlýyor
}
