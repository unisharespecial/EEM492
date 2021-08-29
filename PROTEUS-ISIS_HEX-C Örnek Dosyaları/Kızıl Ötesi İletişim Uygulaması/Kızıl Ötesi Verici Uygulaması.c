/***********************************************
 PIC16F877 ile Kýzýl Ötesi Verici Uygulamasý
************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use rs232(baud=2400, xmit=PIN_C6, stop=1, parity=n)  // RS232 iletiþim ayarlarý yapýlýyor


/******************* ANA PROGRAM FONKSÝYONU *************************/
void main ()
{   
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý
       
   setup_timer_2(T2_DIV_BY_1,25,1); // Timer2 ayarlarý yapýlýyor, PWM sinyali frekansý=~38Khz olacak þekilde
   set_pwm1_duty(12);               // PWM sinyalinin görev saykýl oraný belirleniyor
   setup_CCP1(CCP_PWM);             // CCP modülü PWM çýkýþý için ayarlanýyor   

   while(1) // Sonsuz döngü
   {
      printf("CCS C\r");   // Seri port çýkýþýndan (TX) bilgi gönderiliyor
      delay_ms(500);       // 0.5 saniye gecikme veriliyor
   }  
}

