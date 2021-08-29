/*****************************************************************
      PIC16F877 ile Dahili EEPROM Uygulamasý-2
PIC PROG/DEKA     :Port B jumper'ý LCD konumunda olmalý
******************************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c> // LCD.c dosyasý programa ekleniyor

#include <math.h>       // math.h dosyasý programa dahil ediliyor.

unsigned int8 eeprom_adres,data[1]; //eeprom_adres deðiþkeni ve data dizisi tanýmlanýyor
int16 i; // 16 bitlik i deðiþkeni tanýmlanýyor

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

   set_tris_a(0x03);   // RA0,RA1 pinleri giriþ

   lcd_init();         // LCD kurulumu yapýlýyor

   printf(lcd_putc,"\fEEPROM Adres="); // LCD'ye veri yazdýrýlýyor
   lcd_gotoxy(1,2);                    // Ýmleç 1.sütun, 2.satýra gidiyor
   printf(lcd_putc,"EEPROM Veri =");   // LCD'ye veri yazdýrýlýyor
   
   while(1)      // Sonsuz döngü
   {
      for(i=0; i<=2048; i++)  // 256 Byte veri kaydetmek için döngü
      {
         while (!input(PIN_A0)); // RA0 butonuna basýldýðýnda
         shift_left(data,1,input(PIN_A1));   // bilgiyi sola kaydýrarak kaydet
         eeprom_adres=floor(i/8);            // EEPROM adres deðerini hesapla
         write_eeprom(eeprom_adres,data[0]); // Belirtilen adrese bilgiyi yaz
         lcd_gotoxy(14,1);                   // Ýmleç 14.sütun, 1.satýra gidiyor
         printf(lcd_putc,"%3u",eeprom_adres);  // LCD'ye veri yazdýrýlýyor
         lcd_gotoxy(14,2);                      // Ýmleç 14.sütun, 1.satýra gidiyor
         printf(lcd_putc,"%X",read_eeprom(eeprom_adres));   // LCD'ye veri yazdýrýlýyor       
         while (input(PIN_A0)); // RA0 butonundan el çekile kadar bekle
      }     
   }
}
