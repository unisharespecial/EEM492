/******************************************************
      PIC16F877 ile Flash Program Hafýzasý Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c> // LCD.c dosyasý programa ekleniyor

int16  adres=0,deger=0;

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

   set_tris_a(0x01);   // RA1 pini giriþ

   lcd_init();         // LCD kurulumu yapýlýyor

   printf(lcd_putc,"\fProgram Kodlari"); // LCD'ye yazý yazdýrýlýyor
   delay_ms(1000);
   printf(lcd_putc,"\fAdres       Kod"); // LCD'ye yazý yazdýrýlýyor

   while (!(adres==0x3FFF)) // Program kodu 0x3FFF deðerine eþit oluncaya kadar döngüyü iþle
                            // 0x3FFF Boþ olan program bellek kodudur.
   {
      deger=read_program_eeprom(adres); // Program kod hafýzasýnda belirtilen adresteki kodu oku
      lcd_gotoxy(1,2); // Ýmleç 1.sütun 2.satýrda
      printf(lcd_putc,"\n%lx        %lx",adres,deger); // LCD'ye program kod hafýzasý adresini ve içindeki kodu yaz
      delay_ms(500);
      adres++; // adres deðiþkeni içeriðini 1 arttýr

      if (input(pin_a0)) // Eðer RA0 giriþindeki butona basýlýrsa
      {
         delay_ms(20);  // Buton arkýný önlemek için
         write_program_eeprom(adres, 0x0000); // Belirtilen program kod hafýzasý adresine 0 bilgi yaz
      }
   }
   printf(lcd_putc,"\fProgram Bitti..."); // Programýn sonuna geldiðini bildirir
}
