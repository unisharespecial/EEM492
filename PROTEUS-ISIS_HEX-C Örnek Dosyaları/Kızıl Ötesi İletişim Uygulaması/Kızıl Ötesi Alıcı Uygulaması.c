/***********************************************
 PIC16F877 ile Kýzýl Ötesi Alýcý Uygulamasý
************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>     // lcd.c dosyasý programa ekleniyor

#use rs232 (baud=2400,rcv=pin_C1,stop=1,parity=n)  // RS232 ayarlarý yapýlýyor

char data[16]; // dizi tanýmlanýyor

/******************* ANA PROGRAM FONKSÝYONU *************************/
void main ()
{   
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý
   
   lcd_init(); // LCD hazýr hale getiriliyor
   
   delay_ms(2000);   // Ýletiþime baþlamadan 2 saniye bekleniyor

   while(1) // Sonsuz döngü
   {
      if (input(pin_c1)==0)   // RC1 ucu sýfýr ise (Kýzýl ötesi alýcý, veri aldýysa)
      {
         gets(data);                   // RX ucuna gelen veriyi al
         printf(lcd_putc,"\f%s",data); // LCD'ye alýnan string ifadeyi gönder
         delay_ms(1000);               // 1 saniye bekleniyor
         printf(lcd_putc,"\f");        // LCD temizleniyor
         delay_ms(500);                // 0.5 saniye bekleniyor
      }
   }
}

