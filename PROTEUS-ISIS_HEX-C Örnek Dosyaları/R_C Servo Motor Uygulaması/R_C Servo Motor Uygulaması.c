/******************************************************
      PIC16F877 Ýle R/C Servo Motor Uygulamasý
******************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses HS,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=20000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

// R/C Servo motor dönme açý deðerleri
const int8 servo_derece_1[]={8,9,10,11,12,13,14,15,16,17,18};
const int8 servo_derece_2[]={18,17,16,15,14,13,12,11,10,9,8};
const int8 servo_derece_3[]={8,12,18,8,12,18,8,12,18,8,12};

int i=0,pwm=0,duty_0=0,duty_1=0,duty_2=0;
int16 zaman=0; // 16 bitlik deðiþken tanýmlanýyor

#int_timer0  // Timer0 taþma kesmesi
void kesme ()
{
   set_timer0(113);  // TMR0 kaydedicisine 113 deðeri yükleniyor
   if (pwm==0)       // Eðer PWM deðiþkeni 0 ise
   {
      output_high(pin_b0); // RB0 çýkýþý lojik-1
      output_high(pin_b1); // RB1 çýkýþý lojik-1
      output_high(pin_b2); // RB2 çýkýþý lojik-1
   }

   if (pwm>=duty_0) output_low(pin_b0);
   if (pwm>=duty_1) output_low(pin_b1);
   if (pwm>=duty_2) output_low(pin_b2);

   zaman++; // zaman deðiþkenini 1 arttýr

   // Servo motor dönüþ adýmlarý arasý bekleme süresi için
   if (zaman>17350) // 17350x114,4µsn=1.984.840µsn, yaklaþýk 2msn
   {
      zaman=0;  // zaman deðiþkenini sýfýrla
      i++;      // i deðiþkeni deðerini 1 arttýr
      if(i==11) // Eðer i deðeri 11 ise-Tüm adýmlar bitti ise
         i=0;   // i deðiþkenini sýfýrla
   }

   pwm++;       // pwm deðiþkenini 1 arttýr
   if (pwm>=173) // pwm deðeri 173'den büyük ise
      pwm=0;    // pwm deðiþkenini sýfýrla
}

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


   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_4); // Timer0 ayarlarý belirtiliyor
   set_timer0(113);  // TMR0 kaydedicisine 113 deðeri yükleniyor

   enable_interrupts(int_timer0); // Timer0 taþma kesmesi aktif
   enable_interrupts(global);     // Aktif edilen tüm kesmelere izin ver

   output_b(0x00);  // Ýlk anda B portu çýkýþý sýfýrlanýyor

   while(1)  // Sonsuz döngü
   {
      duty_0=servo_derece_1[i]; // 1. R/C servo PWM görev saykýlý
      duty_1=servo_derece_2[i]; // 2. R/C servo PWM görev saykýlý
      duty_2=servo_derece_3[i]; // 3. R/C servo PWM görev saykýlý
   }
}
