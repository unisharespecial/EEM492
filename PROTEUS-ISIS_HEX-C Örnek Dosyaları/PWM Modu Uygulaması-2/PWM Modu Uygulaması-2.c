/******************************************************
      PIC16F877 ile PWM Modu Uygulamasý-2
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli
#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli

int i=65; // Tamsayý tipinde deðiþken tanýmlanýyor

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý

   set_tris_a(0x03);   // RA0 ve RA1 pinleri giriþ
   set_tris_c(0x00);   // C portu komple çýkýþ

   setup_ccp1(CCP_PWM);  // CCP1 birimi PWM çýkýþý için ayarlandý

   setup_timer_2(T2_DIV_BY_16,i,1); // Timer2 ayarlarý yapýlýyor

   set_pwm1_duty(50); // PWM1 çýkýþý görev saykýlý belirleniyor

   while(1) // Sonsuz döngü
   {
      if (input(pin_a0)) // Eðer RA1 giriþine baðlý butona basýlýrsa
      {
         delay_ms(20);         // Buton arký önleme gecikmesi
         while(input(pin_a0)); // Basýlý butondan el çekile kadar bekle
         i+=5; // i=i+5 anlamýndadýr.

         if (i>250) // i deðeri 250'dan büyükse i deðeri 250 olsun
            i=250;
         setup_timer_2(T2_DIV_BY_16,i,1); // Timer2 ayarlarý yapýlýyor
      }

      if (input(pin_a1)) // Eðer RA0 giriþine baðlý butona basýlýrsa
      {
         delay_ms(20);         // Buton arký önleme gecikmesi
         while(input(pin_a1)); // Basýlý butondan el çekile kadar bekle
         i-=5;  // i=i-5 anlamýndadýr.

         if (i<65) // i deðeri 65'den küçük ise i deðeri 65 olsun
            i=65;
         setup_timer_2(T2_DIV_BY_16,i,1); // Timer2 ayarlarý yapýlýyor
      }
   }
}

