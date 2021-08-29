/******************************************************
      PIC16F877 ile Tuþ Takýmý ve LCD Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli
#use fast_io(d) //Port yönlendirme komutlarý B portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

#define sut1   pin_d0 // sut1 ifadesi pin_d0 ifadesine eþitleniyor
#define sut2   pin_d1 // sut2 ifadesi pin_d1 ifadesine eþitleniyor
#define sut3   pin_d2 // sut3 ifadesi pin_d2 ifadesine eþitleniyor
#define sut4   pin_d3 // sut3 ifadesi pin_d2 ifadesine eþitleniyor

#define sat1   pin_d4 // sat1 ifadesi pin_d4 ifadesine eþitleniyor
#define sat2   pin_d5 // sat2 ifadesi pin_d5 ifadesine eþitleniyor
#define sat3   pin_d6 // sat3 ifadesi pin_d6 ifadesine eþitleniyor
#define sat4   pin_d7 // sat4 ifadesi pin_d7 ifadesine eþitleniyor

 char tus=0; // karakter tipinde deðiþken tanýmlanýyor

//*********** Keypad Tarama Fonksiyonu *********

char keypad_oku() // Fonksiyon ismi
{
   output_d(0x00); // D portu çýkýþý sýfýrlanýyor

   output_high(sat1); // 1. satýr lojik-1 yapýlýyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=1; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=2; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=3; }
   if (input(sut4))   // 4. sütun okunuyor
      { delay_ms(20); tus=0xA; }
   output_low(sat1); // 1. satýr lojik-0 yapýlýyor

   output_high(sat2); // 2. satýr lojik-1 yapýlýyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=4; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=5; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=6; }
   if (input(sut4))   // 4. sütun okunuyor
      { delay_ms(20); tus=0xB; }
   output_low(sat2); // 2. satýr lojik-0 yapýlýyor

   output_high(sat3); // 3. satýr lojik-1 yapýlýyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=7; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=8; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=9; }
   if (input(sut4))   // 4. sütun okunuyor
      {delay_ms(20); tus=0x0C; }
   output_low(sat3); // 3. satýr lojik-0 yapýlýyor

   output_high(sat4); // 3. satýr lojik-1 yapýlýyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=0xE; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=0; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=0xF; }
   if (input(sut4))   // 4. sütun okunuyor
      {delay_ms(20); tus=0xD; }
   output_low(sat4); // 3. satýr lojik-0 yapýlýyor

   return tus; // Fonksiyon "tus" deðeri ile geri döner
}

//********** ANA PROGRAM FONKSÝYONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý

   set_tris_b(0x00);   // B portu komple çýkýþ
   set_tris_d(0x0F);   // Yüksek deðerlikli 4 bit çýkýþ, düþük deðerlikli 4 bit giriþ

   lcd_init();   // LCD hazýrlanýyor

   printf(lcd_putc,"\fBasilan Tus="); // LCD'ye string yazdýrýlýyor

   while(1) // Sonsuz döngü
   {
      lcd_gotoxy(13,1); // Ýmleç 3.sütun, 1.satýra konumlandýrýlýyor

      if (keypad_oku()>9)   // Eðer basýlan tuþ deðeri 9'dan büyük ise
         printf(lcd_putc,"%d",keypad_oku());  // Tuþ deðeri LCD'ye yazdýrýlýyor
      else                  // Eðer basýlan tuþ deðeri 9'dan büyük deðilse
         printf(lcd_putc,"%d ",keypad_oku()); // Tuþ deðeri LCD'ye yazdýrýlýyor
   }
}

