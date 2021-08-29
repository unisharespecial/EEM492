/***********************************************
 PIC16F877 ile K�z�l �tesi Al�c� Uygulamas�
************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>     // lcd.c dosyas� programa ekleniyor

#use rs232 (baud=2400,rcv=pin_C1,stop=1,parity=n)  // RS232 ayarlar� yap�l�yor

char data[16]; // dizi tan�mlan�yor

/******************* ANA PROGRAM FONKS�YONU *************************/
void main ()
{   
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���
   
   lcd_init(); // LCD haz�r hale getiriliyor
   
   delay_ms(2000);   // �leti�ime ba�lamadan 2 saniye bekleniyor

   while(1) // Sonsuz d�ng�
   {
      if (input(pin_c1)==0)   // RC1 ucu s�f�r ise (K�z�l �tesi al�c�, veri ald�ysa)
      {
         gets(data);                   // RX ucuna gelen veriyi al
         printf(lcd_putc,"\f%s",data); // LCD'ye al�nan string ifadeyi g�nder
         delay_ms(1000);               // 1 saniye bekleniyor
         printf(lcd_putc,"\f");        // LCD temizleniyor
         delay_ms(500);                // 0.5 saniye bekleniyor
      }
   }
}

