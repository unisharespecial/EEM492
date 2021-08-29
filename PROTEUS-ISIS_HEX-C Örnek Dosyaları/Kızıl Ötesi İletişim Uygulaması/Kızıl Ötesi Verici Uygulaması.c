/***********************************************
 PIC16F877 ile K�z�l �tesi Verici Uygulamas�
************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use rs232(baud=2400, xmit=PIN_C6, stop=1, parity=n)  // RS232 ileti�im ayarlar� yap�l�yor


/******************* ANA PROGRAM FONKS�YONU *************************/
void main ()
{   
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���
       
   setup_timer_2(T2_DIV_BY_1,25,1); // Timer2 ayarlar� yap�l�yor, PWM sinyali frekans�=~38Khz olacak �ekilde
   set_pwm1_duty(12);               // PWM sinyalinin g�rev sayk�l oran� belirleniyor
   setup_CCP1(CCP_PWM);             // CCP mod�l� PWM ��k��� i�in ayarlan�yor   

   while(1) // Sonsuz d�ng�
   {
      printf("CCS C\r");   // Seri port ��k���ndan (TX) bilgi g�nderiliyor
      delay_ms(500);       // 0.5 saniye gecikme veriliyor
   }  
}

