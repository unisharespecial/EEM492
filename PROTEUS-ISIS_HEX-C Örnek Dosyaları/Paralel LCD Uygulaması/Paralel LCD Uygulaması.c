/******************************************************
      PIC16F877 ile Paralel LCD Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

int x;      // Tamsayý tipinde deðiþken tanýmlanýyor
float y;    // Ondalýklý tipte deðiþken tanýmlanýyor
char z;     //  Karakter tipinde deðiþken tanýmlanýyor

byte dizi[6]={0x45,0xC6,0xA3,0xE2,0x56};

//********** ANA PROGRAM FONKSÝYONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_b(0x00);   // B portu komple çýkýþ

   lcd_init();   // LCD hazýrlanýyor

   x=10;   // x deðiþkenine deðer veriliyor
   y=32.6; // y deðiþkenine deðer veriliyor
   
   
   
   while(1) // Sonsuz döngü
   {shift_right(dizi,4,1);
      lcd_send_byte(0,0x0d);   // LCD'ye komut gönderiliyor. Ýmleç yanýp sönsün komutu.
      printf(lcd_putc,"\f     CCS C"); // LCD'ye veri gönderiliyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\n  Derleyicisi");
      delay_ms(1000); // 1 sn gecikme
      lcd_gotoxy(1,2);   // Kursör 1.sütun, 2.satýra konumlandýrýlýyor.
      printf(lcd_putc,"\fX DEGERI=%d",x); // LCD'de tamsayý olarak x deðiþken deðeri görüntüleniyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\f\nY DEGERI=%f",y); // LCD'de ondalýklý olarak y deðiþken deðeri görüntüleniyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\fDIRENC"); // LCD siliniyor ve "Direnc" stringi yazdýrýlýyor.
      delay_ms(1000); // 1 sn gecikme
      z=lcd_getc(3,1);  // LCD'de o an 3.Sütun ve 1.Satýrda olan karakter alýnýyor. Alýnan deðer z deðiþkenine aktarýlýyor.
      printf(lcd_putc,"\f%c",z);    // z deðiþkeni LCD'ye aktarýlýyor
      delay_ms(2000); // 2 sn gecikme
   }
}

