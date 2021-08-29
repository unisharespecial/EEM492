/******************************************************
 PIC16F877 ile CCS C Dosyalarýný Kullanarak Yazýlýmsal SPI Ýletiþim Ýle 25640 Harici EEPROM Uygulamasý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 iletiþim ayarlarý belirtiliyor
#use spi (master, DI=pin_B2, DO=pin_B1, CLK=pin_B0, SAMPLE_RISE, bits=8, MSB_FIRST,IDLE=0) // Yazýlýmsal SPI iletiþim ayarlarý tanýmlanýyor

#include <input.c>   // input.c dosyasý programa ekleniyor
#include <stdlib.h>  // stdlib.h dosyasý programa ekleniyor

#define CS PIN_B3    // CS ifadesi PIN_C2 pini yerine atanýyor

int8 _adres[4],veri,adres_high,adres_low;  // int8 tipinde deðiþkenler tanýmlanýyor
int16 adres;                                 // int16 tipinde deðiþken tanýmlanýyor
char islem;                                  // char tipinde deðiþken tanýmlanýyor

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

   printf("\n\r***********************************************************");
   printf("\n\r   25LC640 Harici EEPROM Bilgi Okuma ve Yazma Programi     ");
   printf("\n\r***********************************************************");
   printf("\n\r");

   output_high(cs); // Harici EEPROM CS ucu lojik-1 yapýlýyor

   while(1) // Sonsuz Döngü
   {
      do  // do-while döngüsü tanýmlanýyor
      {
         printf("\n\r\r\rBelirtilen adresteki veriyi oku (O)");
         printf("\n\rBelirtilen adrese istenen veriyi yaz (Y)>");
         
         islem=getc();  // RS232 portundan gelen veri alýnýyor
         islem=toupper(islem); // Alýnan karakter büyük forma getiriliyor (a > A gibi)
         putc(islem);   // "islem" deðiþkeni içeriði RS232 portuna gönderiliyor
      }  while ( (islem!='O') && (islem!='Y')); // Girilen karakter O, Y dýþýnda ise döngü baþýna dön

      if (islem=='O')  // Eðer okunan karakter "O" ise
      {
         printf("\n\r\rOkumak istediginiz adresi giriniz>");

         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak alýnýyor
         adres=atol(_adres);        // String olarak alýnan adres bilgisi tam sayýya çevriliyor
         adres_high=make8(adres,1); // Adres deðerinin 8 bitlik MSB deðeri adres_high deðiþkenine kaydediliyor
         adres_low=make8(adres,0);  // Adres deðerinin 8 bitlik LSB deðeri adres_low deðiþkenine kaydediliyor

         printf("\n\r\rVeri okunuyor...");
         
         output_low(cs);         // Entegre seçiliyor
         spi_xfer(0x03);        // Okuma komutu (READ) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_xfer(adres_high);  // Okunacak adres deðerinin 8 bitlik MSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_xfer(adres_low);   // Okunacak adres deðerinin 8 bitlik LSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         printf("\n\r\rAdres=%04lu    Deger=0x%02X",adres,spi_xfer(0) );  // Ýstenen adresteki deðer okunuyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         delay_ms(5);            // Gecikme veriliyor
      }
      
      if (islem=='Y')  // Eðer okunan karakter "Y" ise
      {
         printf("\n\r\rBilgi yazmak istediginiz adresi giriniz> ");
         
         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak alýnýyor
         adres=atol(_adres);        // String olarak alýnan adres bilgisi tam sayýya çevriliyor
         adres_high=make8(adres,1); // Adres deðerinin 8 bitlik MSB deðeri adres_high deðiþkenine kaydediliyor
         adres_low=make8(adres,0);  // Adres deðerinin 8 bitlik LSB deðeri adres_low deðiþkenine kaydediliyor
                 
         printf("\n\r\rBilgiyi giriniz> ");
         veri=gethex();          // Yazýlacak veri heksadesimal olarak alýnýyor
         printf("\n\r\rVeri yaziliyor...");

         output_low(cs);         // Entegre seçiliyor
         spi_xfer(0x06);        // Yazmaya izin ver komutu (WREN) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         
         output_low(cs);         // Entegre seçiliyor
         spi_xfer(0x02);        // Yazma komutu (WRITE) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_xfer(adres_high);  // Okunacak adres deðerinin 8 bitlik MSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_xfer(adres_low);   // Okunacak adres deðerinin 8 bitlik LSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_xfer(veri);        // Belirtilen adrese yazdýrýlacak veri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         printf("\n\r\rYazma islemi bitti.");
      }
   }
}


