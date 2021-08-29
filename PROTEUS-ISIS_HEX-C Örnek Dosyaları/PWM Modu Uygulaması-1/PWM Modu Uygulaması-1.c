/******************************************************
      PIC16F877 ile PWM Modu Uygulamasý-1
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli
#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli

int i=5; // Tamsayý tipinde deðiþken tanýmlanýyor

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý

   set_tris_a(0x03);   // RA0 ve RA1 pinleri giriþ
   set_tris_c(0x00);   // RC0, RC1 ve RC2 pini giriþ

   setup_ccp1(CCP_PWM);  // CCP1 birimi PWM çýkýþý için ayarlandý
   setup_ccp2(CCP_PWM);  // CCP2 birimi PWM çýkýþý için ayarlandý

   setup_timer_2(T2_DIV_BY_16,170,1); // Timer2 ayarlarý yapýlýyor

   set_pwm1_duty(i); // PWM1 çýkýþý görev saykýlý belirleniyor
   set_pwm2_duty(i); // PWM2 çýkýþý görev saykýlý belirleniyor

   while(1) // Sonsuz döngü
   {
      if (input(pin_a0)) // Eðer RA0 giriþine baðlý butona basýlýrsa
      {
         delay_ms(20);   // Buton arký önleme gecikmesi
         while(input(pin_a0)); // Basýlý butondan el çekile kadar bekle
         i+=3; // i=i+3 anlamýndadýr.

         if (i>=170) // i deðeri 170'dan büyükse i deðeri 170 olsun
            i=170;

         set_pwm1_duty(i); // PWM1 çýkýþý görev saykýlý belirleniyor
         set_pwm2_duty(i); // PWM2 çýkýþý görev saykýlý belirleniyor
      }

      if (input(pin_a1)) // Eðer RA1 giriþine baðlý butona basýlýrsa
      {
         delay_ms(20);  // Buton arký önleme gecikmesi
         while(input(pin_a1)); // Basýlý butondan el çekile kadar bekle
         i-=3;  // i=i-3 anlamýndadýr.

         if (i<5) // i deðeri 5'den küçük ise i deðeri 10 olsun
            i=5;

         set_pwm1_duty(i); // PWM1 çýkýþý görev saykýlý belirleniyor
         set_pwm2_duty(i); // PWM2 çýkýþý görev saykýlý belirleniyor
      }
   }
}

