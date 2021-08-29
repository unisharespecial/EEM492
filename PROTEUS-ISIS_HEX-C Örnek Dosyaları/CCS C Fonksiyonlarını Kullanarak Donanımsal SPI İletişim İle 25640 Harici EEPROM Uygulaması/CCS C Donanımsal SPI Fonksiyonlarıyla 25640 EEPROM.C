/******************************************************
 PIC16F877 ile CCS C Dosyalar�n� Kullanarak Donan�msal SPI �leti�im �le 25640 Harici EEPROM Uygulamas�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 ileti�im ayarlar� belirtiliyor

#include <input.c>   // input.c dosyas� programa ekleniyor
#include <stdlib.h>  // stdlib.h dosyas� programa ekleniyor

#define CS PIN_C2    // CS ifadesi PIN_C2 pini yerine atan�yor

int8 _adres[4],veri,adres_high,adres_low,i;  // int8 tipinde de�i�kenler tan�mlan�yor
int16 adres;                                 // int16 tipinde de�i�ken tan�mlan�yor
char islem;                                  // char tipinde de�i�ken tan�mlan�yor

#int_ssp // SPI ileti�iminde yazma veya okuma yap�ld���nda meydana gelen kesme
void SPI_kesmesi()
{
   output_high(pin_c0); // RC0'a ba�l� LED yans�n
   delay_ms(250);       // Gecikme veriliyor
   output_low(pin_c0);  // RC0'a ba�l� LED s�ns�n
}


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
   
   setup_spi(spi_master| spi_L_to_H | spi_clk_div_4);  // SPI ileti�im ayarlar� belirtiliyor
   
   enable_interrupts(int_ssp);   // SPI kesmesi aktif yap�l�yor
   enable_interrupts(GLOBAL);    // Aktif edilen t�m kesmelere izin ver  

   printf("\n\r***********************************************************");
   printf("\n\r   25LC640 Harici EEPROM Bilgi Okuma ve Yazma Programi     ");
   printf("\n\r***********************************************************");
   printf("\n\r");
 
   output_high(cs); // Harici EEPROM CS ucu lojik-1 yap�l�yor

   while(1) // Sonsuz D�ng�
   {
      do  // do-while d�ng�s� tan�mlan�yor
      {
         printf("\n\r\r\r1-Belirtilen adresteki veriyi oku");
         printf("\n\r2-Belirtilen adresten itibaren sona kadar tum adresleri oku");
         printf("\n\r3-Belirtilen adrese istenen veriyi yaz");
         printf("\n\r4-Tum bellege ayni veriyi yaz");
         printf("\n\r5-Durum (Status) kaydedicisi degerini oku");
         printf("\n\r\rBir islem seciniz (1,2,3,4,5) >");
         
         islem=getc();  // RS232 portundan gelen veri al�n�yor
         putc(islem);   // "islem" de�i�keni i�eri�i RS232 portuna g�nderiliyor
      }  while ( (islem!='1') && (islem!='2') && (islem!='3') && (islem!='4') && (islem!='5')); // Girilen karakter 1,2,3,4 d���nda ise d�ng� ba��na d�n

      if (islem=='1')  // E�er okunan karakter "1" ise
      {
         printf("\n\r\rOkumak istediginiz adresi giriniz>");

         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak al�n�yor
         adres=atol(_adres);        // String olarak al�nan adres bilgisi tam say�ya �evriliyor
         adres_high=make8(adres,1); // Adres de�erinin 8 bitlik MSB de�eri adres_high de�i�kenine kaydediliyor
         adres_low=make8(adres,0);  // Adres de�erinin 8 bitlik LSB de�eri adres_low de�i�kenine kaydediliyor

         printf("\n\r\rVeri okunuyor...");
         
         output_low(cs);         // Entegre se�iliyor
         spi_write(0x03);        // Okuma komutu (READ) g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_high);  // Okunacak adres de�erinin 8 bitlik MSB de�eri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_low);   // Okunacak adres de�erinin 8 bitlik LSB de�eri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         printf("\n\r\rAdres=%04lu    Deger=0x%02X",adres,spi_read(0) );  // �stenen adresteki de�er okunuyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         delay_ms(5);            // Gecikme veriliyor
      }
      
      if (islem=='2')  // E�er okunan karakter "2" ise
      {
         printf("\n\r\rOkumaya baslamak istediginiz adresi giriniz>");
         
         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak al�n�yor
         adres=atol(_adres);        // String olarak al�nan adres bilgisi tam say�ya �evriliyor
         adres_high=make8(adres,1); // Adres de�erinin 8 bitlik MSB de�eri adres_high de�i�kenine kaydediliyor
         adres_low=make8(adres,0);  // Adres de�erinin 8 bitlik LSB de�eri adres_low de�i�kenine kaydediliyor
                 
         output_low(cs);         // Entegre se�iliyor
         spi_write(0x03);        // Okuma komutu (READ) g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_high);  // Okunacak adres de�erinin 8 bitlik MSB de�eri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_low);   // Okunacak adres de�erinin 8 bitlik LSB de�eri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         
         for(;adres<=0x1FFF;adres++)   // Belle�in sonuna gelene kadar d�ng� d�ns�n
         {
            printf("\n\r\rAdres=%04lu    Deger=0x%02X",adres,spi_read(0)); // �stenen adresteki de�er okunuyor
            delay_ms(5);         // Gecikme veriliyor
         }         
         
         output_high(cs);  // Entegre bekleme konumuna getiriliyor
      }


      if (islem=='3')  // E�er okunan karakter "3" ise
      {
         printf("\n\r\rBilgi yazmak istediginiz adresi giriniz> ");
         
         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak al�n�yor
         adres=atol(_adres);        // String olarak al�nan adres bilgisi tam say�ya �evriliyor
         adres_high=make8(adres,1); // Adres de�erinin 8 bitlik MSB de�eri adres_high de�i�kenine kaydediliyor
         adres_low=make8(adres,0);  // Adres de�erinin 8 bitlik LSB de�eri adres_low de�i�kenine kaydediliyor
                 
         printf("\n\r\rBilgiyi giriniz> ");
         veri=gethex();          // Yaz�lacak veri heksadesimal olarak al�n�yor
         printf("\n\r\rVeri yaziliyor...");

         output_low(cs);         // Entegre se�iliyor
         spi_write(0x06);        // Yazmaya izin ver komutu (WREN) g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         
         output_low(cs);         // Entegre se�iliyor
         spi_write(0x02);        // Yazma komutu (WRITE) g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_high);  // Okunacak adres de�erinin 8 bitlik MSB de�eri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(adres_low);   // Okunacak adres de�erinin 8 bitlik LSB de�eri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         spi_write(veri);        // Belirtilen adrese yazd�r�lacak veri g�nderiliyor
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         printf("\n\r\rYazma islemi bitti.");
      }
      
      if (islem=='4')  // E�er okunan karakter "4" ise
      {
         disable_interrupts(GLOBAL);    // T�m kesmeleri pasif hale getirir. T�m belle�e yazma i�lemi daha h�zl� yap�ls�n diye.  
         printf("\n\r\rBilgiyi giriniz> ");
         veri=gethex();             // Yaz�lacak veri heksadesimal olarak al�n�yor
         
         printf("\n\r\rVeri yaziliyor...");
         
         for(adres=0;adres<8192;adres=adres+32) // Her sayfa (page) yaz�m� bitince adres de�eri di�er sayfa ba�lang�c� olsun
         {
            adres_high=make8(adres,1); // Adres de�erinin 8 bitlik MSB de�eri adres_high de�i�kenine kaydediliyor
            adres_low=make8(adres,0);  // Adres de�erinin 8 bitlik LSB de�eri adres_low de�i�kenine kaydediliyor
         
            output_low(cs);         // Entegre se�iliyor
            spi_write(0x06);        // Yazmaya izin ver komutu (WREN) g�nderiliyor
            delay_ms(5);            // Gecikme veriliyor
            output_high(cs);        // Entegre bekleme konumuna getiriliyor
         
            delay_ms(5);            // Gecikme veriliyor
            output_low(cs);         // Entegre se�iliyor
            spi_write(0x02);        // Yazma komutu (WRITE) g�nderiliyor
            delay_ms(5);            // Gecikme veriliyor
            spi_write(adres_high);  // Okunacak adres de�erinin 8 bitlik MSB de�eri g�nderiliyor
            delay_ms(5);            // Gecikme veriliyor
            spi_write(adres_low);   // Okunacak adres de�erinin 8 bitlik LSB de�eri g�nderiliyor
            delay_ms(5);            // Gecikme veriliyor
         
            for(i=0;i<=32;i++)      // Her sayfa (page) 32 byte oldu�undan 
            {
               spi_write(veri);     // Belirtilen adrese yazd�r�lacak veri g�nderiliyor
               delay_ms(5);         // Gecikme veriliyor
            }
            output_high(cs);        // Entegre bekleme konumuna getiriliyor
            delay_ms(20);           // Gecikme veriliyor
         }
         
         printf("\n\r\rYazma islemi bitti.");
         enable_interrupts(GLOBAL);    // Aktif edilen t�m kesmelere izin ver 
      }
      
      if (islem=='5')      // E�er okunan karakter "5" ise
      {
         output_low(cs);   // Entegre se�iliyor
         spi_write(0x06);  // Yazmaya izin ver komutu (WREN) g�nderiliyor
         delay_ms(5);      // Gecikme veriliyor
         output_high(cs);  // Entegre bekleme konumuna getiriliyor
                
         output_low(cs);   // Entegre se�iliyor
         spi_write(0x05);  // Durum kaydedicisi okuma komutu (WRSR) g�nderiliyor
         delay_ms(5);      // Gecikme veriliyor
         printf("\n\r\rDurum (Status) Kaydedicisi Degeri=0x%02X",spi_read(0));   // Durum kaydedicisi de�eri okunuyor
         output_high(cs);  // Entegre bekleme konumuna getiriliyor
      }
   }
}


