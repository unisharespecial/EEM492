#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

int x;      // Tamsayý tipinde deðiþken tanýmlanýyor

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

   x=0;   // x deðiþkenine deðer veriliyor
   
   while(1) // Sonsuz döngü
   {
      lcd_send_byte(0,0x0d);   // LCD'ye komut gönderiliyor. Ýmleç yanýp sönsün komutu.
      printf(lcd_putc,"\f  Ayturan"); // LCD'ye veri gönderiliyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\n  Derleyicisi");
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\f  Ayturan"); // LCD'ye veri gönderiliyor.
         while(1) // Sonsuz döngü
            {
            x++;
      printf(lcd_putc,"\n  ARTAN SAYI=%d",x); // LCD'de tamsayý olarak x deðiþken deðeri görüntüleniyor.
      delay_ms(1000); // 1 sn gecikme
            }
   }
}

