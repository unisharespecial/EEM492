/******************************************************************
 Kendi Harici EEPROM Fonksiyonlar�m�z �le 24C02 EEPROM Uygulamas�
*******************************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k                 // dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan                // osilat�r frekans� belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1)   // RS232 ayarlar� belirtiliyor

#use i2c(master,sda=pin_c4,scl=pin_c3,slow=100000)//I2C ileti�imi SDA ve SCL pinleri ve ileti�im h�z� belirleniyor

#include <kendi_input.c> // kendi_input.c dosyas� programa ekleniyor
#include <kendi_2402.c>  // kendi_2402.c dosyas� programa ekleniyor

byte veri,adres;
char islem;

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
   
   printf("\n\r*************************************************");
   printf("\n\r  24C02C Harici EEPROM Bilgi Okuma Yazma  ");
   printf("\n\r*************************************************");
   printf("\n\n\r Bir islem seciniz>");

   while(1)
   {
      do
      {
         printf("\n\rOkuma (O) veya Yazma (Y) >");
         islem=getc();
         islem=toupper(islem);
         putc(islem);
      }  while ( (islem!='O') && (islem!='Y') );

      if (islem=='O')
      {
         printf("\n\rOkumak istediginiz adresi giriniz> ");
         adres=hex_oku2();
         printf("\n\rDeger= %X",eeprom_oku(adres) );
      }

      if (islem=='Y')
      {
         printf("\n\rBilgi yazmak istediginiz adresi giriniz> ");
         adres=hex_oku2();
         printf("\n\rBilgiyi giriniz> ");
         veri=hex_oku2();
         eeprom_yaz(adres,veri);
      }
   }
}

