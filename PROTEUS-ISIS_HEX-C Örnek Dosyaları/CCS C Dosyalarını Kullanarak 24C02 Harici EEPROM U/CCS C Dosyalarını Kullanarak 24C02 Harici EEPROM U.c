/******************************************************
 PIC16F877 ile CCS C Dosyalar�n� Kullanarak 24C02 Harici EEPROM Uygulamas�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 ayarlar� belirtiliyor

#use i2c(master,sda=pin_c4,scl=pin_c3,slow=100000) // I2C Fonksiyonu,SDA ve SCL pinleri ve ileti�im h�z� belirleniyor

#include <input.c> // input.c dosyas� programa ekleniyor
#include <2402.c>  // 2402.c dosyas� programa ekleniyor

byte veri,adres; // byte tipinde de�i�ken tan�mlan�yor
char islem;      // char tipinde de�i�ken tan�mlan�yor

#int_ssp // I2C ileti�iminde yazma veya okuma yap�ld���nda meydana gelen kesme
void I2C_kesmesi()
{
   output_high(pin_C5); // RC5'e ba�l� LED yans�n
   delay_ms(250);       // Gecikme veriliyor
   output_low(pin_C5);  // RC5'e ba�l� LED s�ns�n
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
   
   enable_interrupts(int_ssp);   // SSP kesmesine izin ver
   enable_interrupts(GLOBAL);    // T�m izin verilen kesmeler

   printf("\n\r***********************************************************");
   printf("\n\r          24C02C Harici EEPROM Bilgi Okuma Yazma           ");
   printf("\n\r***********************************************************");
   printf("\n\r");
   printf("\n\r Bir islem seciniz>");

   while(1)
   {
      do  // do-while d�ng�s� tan�mlan�yor
      {
         printf("\n\rOkuma (O) veya Yazma (Y) >"); // RS232 portuna veri g�nderiliyor
         islem=getc(); // RS232 portundan gelen veri al�n�yor
         islem=toupper(islem); // toupper fonksiyonu t�m karakterleri b�y�k karaktere �evirir a>A
         putc(islem); // "islem" de�i�keni i�eri�i RS232 portuna g�nderiliyor
      }  while ( (islem!='O') && (islem!='Y') ); // Girilen karakter "0" veya "Y" d���nda ise d�ng� ba��na d�n

      if (islem=='O')  // E�er okunan karakter "O" ise
      {
         printf("\n\rOkumak istediginiz adresi giriniz> ");
         adres=gethex(); // RS232 portundan gelen veriyi hex format�nda al
         printf("\n\rDeger= %X",read_ext_eeprom(adres) );
      }

      if (islem=='Y')  // E�er okunan karakter "Y" ise
      {
         printf("\n\rBilgi yazmak istediginiz adresi giriniz> ");
         adres=gethex(); // RS232 portundan gelen veriyi hex format�nda al
         printf("\n\rBilgiyi giriniz> ");
         veri=gethex();  // RS232 portundan gelen veriyi hex format�nda al
         write_ext_eeprom(adres,veri); // Harici EEPROM'da belirtilen adrese "veri" de�erini yaz
      }
   }
}

