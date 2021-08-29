/******************************************************
 PIC16F877 ile CCS C Dosyalarýný Kullanarak 24C02 Harici EEPROM Uygulamasý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 ayarlarý belirtiliyor

#use i2c(master,sda=pin_c4,scl=pin_c3,slow=100000) // I2C Fonksiyonu,SDA ve SCL pinleri ve iletiþim hýzý belirleniyor

#include <input.c> // input.c dosyasý programa ekleniyor
#include <2402.c>  // 2402.c dosyasý programa ekleniyor

byte veri,adres; // byte tipinde deðiþken tanýmlanýyor
char islem;      // char tipinde deðiþken tanýmlanýyor

#int_ssp // I2C iletiþiminde yazma veya okuma yapýldýðýnda meydana gelen kesme
void I2C_kesmesi()
{
   output_high(pin_C5); // RC5'e baðlý LED yansýn
   delay_ms(250);       // Gecikme veriliyor
   output_low(pin_C5);  // RC5'e baðlý LED sönsün
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
   
   enable_interrupts(int_ssp);   // SSP kesmesine izin ver
   enable_interrupts(GLOBAL);    // Tüm izin verilen kesmeler

   printf("\n\r***********************************************************");
   printf("\n\r          24C02C Harici EEPROM Bilgi Okuma Yazma           ");
   printf("\n\r***********************************************************");
   printf("\n\r");
   printf("\n\r Bir islem seciniz>");

   while(1)
   {
      do  // do-while döngüsü tanýmlanýyor
      {
         printf("\n\rOkuma (O) veya Yazma (Y) >"); // RS232 portuna veri gönderiliyor
         islem=getc(); // RS232 portundan gelen veri alýnýyor
         islem=toupper(islem); // toupper fonksiyonu tüm karakterleri büyük karaktere çevirir a>A
         putc(islem); // "islem" deðiþkeni içeriði RS232 portuna gönderiliyor
      }  while ( (islem!='O') && (islem!='Y') ); // Girilen karakter "0" veya "Y" dýþýnda ise döngü baþýna dön

      if (islem=='O')  // Eðer okunan karakter "O" ise
      {
         printf("\n\rOkumak istediginiz adresi giriniz> ");
         adres=gethex(); // RS232 portundan gelen veriyi hex formatýnda al
         printf("\n\rDeger= %X",read_ext_eeprom(adres) );
      }

      if (islem=='Y')  // Eðer okunan karakter "Y" ise
      {
         printf("\n\rBilgi yazmak istediginiz adresi giriniz> ");
         adres=gethex(); // RS232 portundan gelen veriyi hex formatýnda al
         printf("\n\rBilgiyi giriniz> ");
         veri=gethex();  // RS232 portundan gelen veriyi hex formatýnda al
         write_ext_eeprom(adres,veri); // Harici EEPROM'da belirtilen adrese "veri" deðerini yaz
      }
   }
}

