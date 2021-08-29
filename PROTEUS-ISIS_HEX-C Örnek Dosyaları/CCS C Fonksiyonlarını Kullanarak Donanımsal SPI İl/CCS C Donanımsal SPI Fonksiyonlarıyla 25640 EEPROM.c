/******************************************************
 PIC16F877 ile CCS C Dosyalarýný Kullanarak Donanýmsal SPI Ýletiþim Ýle 25640 Harici EEPROM Uygulamasý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 iletiþim ayarlarý belirtiliyor

#include <input.c>   // input.c dosyasý programa ekleniyor
#include <stdlib.h>  // stdlib.h dosyasý programa ekleniyor

#define CS PIN_C2    // CS ifadesi PIN_C2 pini yerine atanýyor

int8 _adres[4],veri,adres_high,adres_low,i;  // int8 tipinde deðiþkenler tanýmlanýyor
int16 adres;                                 // int16 tipinde deðiþken tanýmlanýyor
char islem;                                  // char tipinde deðiþken tanýmlanýyor

#int_ssp // SPI iletiþiminde yazma veya okuma yapýldýðýnda meydana gelen kesme
void SPI_kesmesi()
{
   output_high(pin_c0); // RC0'a baðlý LED yansýn
   delay_ms(250);       // Gecikme veriliyor
   output_low(pin_c0);  // RC0'a baðlý LED sönsün
}


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
   
   setup_spi(spi_master| spi_L_to_H | spi_clk_div_4);  // SPI iletiþim ayarlarý belirtiliyor
   
   enable_interrupts(int_ssp);   // SPI kesmesi aktif yapýlýyor
   enable_interrupts(GLOBAL);    // Aktif edilen tüm kesmelere izin ver  

   printf("\n\r***********************************************************");
   printf("\n\r   25LC640 Harici EEPROM Bilgi Okuma ve Yazma Programi     ");
   printf("\n\r***********************************************************");
   printf("\n\r");
 
   output_high(cs); // Harici EEPROM CS ucu lojik-1 yapýlýyor

   while(1) // Sonsuz Döngü
   {
      do  // do-while döngüsü tanýmlanýyor
      {
         printf("\n\r\r\r1-Belirtilen adresteki veriyi oku");
         printf("\n\r2-Belirtilen adresten itibaren sona kadar tum adresleri oku");
         printf("\n\r3-Belirtilen adrese istenen veriyi yaz");
         printf("\n\r4-Tum bellege ayni veriyi yaz");
         printf("\n\r5-Durum (Status) kaydedicisi degerini oku");
         printf("\n\r\rBir islem seciniz (1,2,3,4,5) >");
         
         islem=getc();  // RS232 portundan gelen veri alýnýyor
         putc(islem);   // "islem" deðiþkeni içeriði RS232 portuna gönderiliyor
      }  while ( (islem!='1') && (islem!='2') && (islem!='3') && (islem!='4') && (islem!='5')); // Girilen karakter 1,2,3,4 dýþýnda ise döngü baþýna dön

      if (islem=='1')  // Eðer okunan karakter "1" ise
      {
         printf("\n\r\rOkumak istediginiz adresi giriniz>");

         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak alýnýyor
         adres=atol(_adres);        // String olarak alýnan adres bilgisi tam sayýya çevriliyor
         adres_high=make8(adres,1); // Adres deðerinin 8 bitlik MSB deðeri adres_high deðiþkenine kaydediliyor
         adres_low=make8(adres,0);  // Adres deðerinin 8 bitlik LSB deðeri adres_low deðiþkenine kaydediliyor

         printf("\n\r\rVeri okunuyor...");
         
         output_low(cs);         // Entegre seçiliyor
         spi_write(0x03);        // Okuma komutu (READ) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_high);  // Okunacak adres deðerinin 8 bitlik MSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_low);   // Okunacak adres deðerinin 8 bitlik LSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         printf("\n\r\rAdres=%04lu    Deger=0x%02X",adres,spi_read(0) );  // Ýstenen adresteki deðer okunuyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         delay_ms(5);            // Gecikme veriliyor
      }
      
      if (islem=='2')  // Eðer okunan karakter "2" ise
      {
         printf("\n\r\rOkumaya baslamak istediginiz adresi giriniz>");
         
         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak alýnýyor
         adres=atol(_adres);        // String olarak alýnan adres bilgisi tam sayýya çevriliyor
         adres_high=make8(adres,1); // Adres deðerinin 8 bitlik MSB deðeri adres_high deðiþkenine kaydediliyor
         adres_low=make8(adres,0);  // Adres deðerinin 8 bitlik LSB deðeri adres_low deðiþkenine kaydediliyor
                 
         output_low(cs);         // Entegre seçiliyor
         spi_write(0x03);        // Okuma komutu (READ) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_high);  // Okunacak adres deðerinin 8 bitlik MSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_low);   // Okunacak adres deðerinin 8 bitlik LSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         
         for(;adres<=0x1FFF;adres++)   // Belleðin sonuna gelene kadar döngü dönsün
         {
            printf("\n\r\rAdres=%04lu    Deger=0x%02X",adres,spi_read(0)); // Ýstenen adresteki deðer okunuyor
            delay_ms(5);         // Gecikme veriliyor
         }         
         
         output_high(cs);  // Entegre bekleme konumuna getiriliyor
      }


      if (islem=='3')  // Eðer okunan karakter "3" ise
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
         spi_write(0x06);        // Yazmaya izin ver komutu (WREN) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         
         output_low(cs);         // Entegre seçiliyor
         spi_write(0x02);        // Yazma komutu (WRITE) gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_high);  // Okunacak adres deðerinin 8 bitlik MSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_low);   // Okunacak adres deðerinin 8 bitlik LSB deðeri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(veri);        // Belirtilen adrese yazdýrýlacak veri gönderiliyor
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         printf("\n\r\rYazma islemi bitti.");
      }
      
      if (islem=='4')  // Eðer okunan karakter "4" ise
      {
         disable_interrupts(GLOBAL);    // Tüm kesmeleri pasif hale getirir. Tüm belleðe yazma iþlemi daha hýzlý yapýlsýn diye.  
         printf("\n\r\rBilgiyi giriniz> ");
         veri=gethex();             // Yazýlacak veri heksadesimal olarak alýnýyor
         
         printf("\n\r\rVeri yaziliyor...");
         
         for(adres=0;adres<8192;adres=adres+32) // Her sayfa (page) yazýmý bitince adres deðeri diðer sayfa baþlangýcý olsun
         {
            adres_high=make8(adres,1); // Adres deðerinin 8 bitlik MSB deðeri adres_high deðiþkenine kaydediliyor
            adres_low=make8(adres,0);  // Adres deðerinin 8 bitlik LSB deðeri adres_low deðiþkenine kaydediliyor
         
            output_low(cs);         // Entegre seçiliyor
            spi_write(0x06);        // Yazmaya izin ver komutu (WREN) gönderiliyor
            delay_ms(5);            // Gecikme veriliyor
            output_high(cs);        // Entegre bekleme konumuna getiriliyor
         
            delay_ms(5);            // Gecikme veriliyor
            output_low(cs);         // Entegre seçiliyor
            spi_write(0x02);        // Yazma komutu (WRITE) gönderiliyor
            delay_ms(5);            // Gecikme veriliyor
            spi_write(adres_high);  // Okunacak adres deðerinin 8 bitlik MSB deðeri gönderiliyor
            delay_ms(5);            // Gecikme veriliyor
            spi_write(adres_low);   // Okunacak adres deðerinin 8 bitlik LSB deðeri gönderiliyor
            delay_ms(5);            // Gecikme veriliyor
         
            for(i=0;i<=32;i++)      // Her sayfa (page) 32 byte olduðundan 
            {
               spi_write(veri);     // Belirtilen adrese yazdýrýlacak veri gönderiliyor
               delay_ms(5);         // Gecikme veriliyor
            }
            output_high(cs);        // Entegre bekleme konumuna getiriliyor
            delay_ms(20);           // Gecikme veriliyor
         }
         
         printf("\n\r\rYazma islemi bitti.");
         enable_interrupts(GLOBAL);    // Aktif edilen tüm kesmelere izin ver 
      }
      
      if (islem=='5')      // Eðer okunan karakter "5" ise
      {
         output_low(cs);   // Entegre seçiliyor
         spi_write(0x06);  // Yazmaya izin ver komutu (WREN) gönderiliyor
         delay_ms(5);      // Gecikme veriliyor
         output_high(cs);  // Entegre bekleme konumuna getiriliyor
                
         output_low(cs);   // Entegre seçiliyor
         spi_write(0x05);  // Durum kaydedicisi okuma komutu (WRSR) gönderiliyor
         delay_ms(5);      // Gecikme veriliyor
         printf("\n\r\rDurum (Status) Kaydedicisi Degeri=0x%02X",spi_read(0));   // Durum kaydedicisi deðeri okunuyor
         output_high(cs);  // Entegre bekleme konumuna getiriliyor
      }
   }
}


