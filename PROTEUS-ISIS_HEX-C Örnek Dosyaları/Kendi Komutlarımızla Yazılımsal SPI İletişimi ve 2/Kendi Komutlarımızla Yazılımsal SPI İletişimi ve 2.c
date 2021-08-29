/******************************************************
     PIC16F877 ile Kendi Komutlar�m�zla Yaz�l�msal 
       SPI �leti�imi ve 25640 EEPROM Uygulamas�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 ileti�im ayarlar� belirtiliyor

#include <input.c>   // input.c dosyas� programa ekleniyor
#include <stdlib.h>  // stdlib.h dosyas� programa ekleniyor

#define SCK PIN_B0    // SCK ifadesi PIN_B0 pini yerine atan�yor
#define SDO PIN_B1    // SDO ifadesi PIN_B1 pini yerine atan�yor
#define SDI PIN_B2    // SDI ifadesi PIN_B2 pini yerine atan�yor
#define CS  PIN_B3    // CS  sifadesi PIN_B3 pini yerine atan�yor

int8 _adres[4],veri,adres_high,adres_low,i,oku,yaz,yazma_izin;  // int8 tipinde de�i�kenler tan�mlan�yor
int16 adres;                                 // int16 tipinde de�i�ken tan�mlan�yor
char islem;                                  // char tipinde de�i�ken tan�mlan�yor

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

   printf("\n\r***********************************************************");
   printf("\n\r   25LC640 Harici EEPROM Bilgi Okuma ve Yazma Programi     ");
   printf("\n\r***********************************************************");
   printf("\n\r");
 
   output_high(cs);  // Harici EEPROM CS ucu lojik-1 yap�l�yor
   output_low(SCK);  // Clock sinyali beklemeye al�n�yor

   while(1) // Sonsuz D�ng�
   {
      do  // do-while d�ng�s� tan�mlan�yor
      {
         printf("\n\r\r\rBelirtilen adresteki veriyi oku (O)");
         printf("\n\rBelirtilen adrese istenen veriyi yaz (Y)>");
         
         islem=getc();  // RS232 portundan gelen veri al�n�yor
         islem=toupper(islem); // Al�nan karakter b�y�k forma getiriliyor (a > A gibi)
         putc(islem);   // "islem" de�i�keni i�eri�i RS232 portuna g�nderiliyor
      }  while ( (islem!='O') && (islem!='Y')); // Girilen karakter O, Y d���nda ise d�ng� ba��na d�n
      
//**************** Okuma ��lemi Se�ilmi�se ************************************
      if (islem=='O')  // E�er okunan karakter "O" ise
      {
         printf("\n\r\rOkumak istediginiz adresi giriniz>");

         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak al�n�yor
         adres=atol(_adres);        // String olarak al�nan adres bilgisi tam say�ya �evriliyor
         adres_high=make8(adres,1); // Adres de�erinin 8 bitlik MSB de�eri adres_high de�i�kenine kaydediliyor
         adres_low=make8(adres,0);  // Adres de�erinin 8 bitlik LSB de�eri adres_low de�i�kenine kaydediliyor

         printf("\n\r\rVeri okunuyor...");
         
         output_low(cs);         // Entegre se�iliyor
         
         oku=0x03;   // Okuma komutu
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&oku,1,0)); // oku komutu g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock hatt� beklemeye al�n�yor
         }
         delay_ms(5);            // Gecikme veriliyor
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&adres_high,1,0)); // adres de�erinin MSB k�sm� g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }   
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&adres_low,1,0)); // adres de�erinin LSB k�sm� g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }
         delay_ms(5);            // Gecikme veriliyor

         for(i=0;i<8;i++)
         {
            shift_left(&veri,1,input(SDI));  // Bit bit gelen veri okunuyor
            output_high(SCK); // Bilgi okunuyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }         

         printf("\n\r\rAdres=%04lu    Deger=0x%02X",adres,veri );
         
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         delay_ms(5);            // Gecikme veriliyor
      }
 
 //**************** Yazma ��lemi Se�ilmi�se ************************************
      if (islem=='Y')  // E�er okunan karakter "Y" ise
      {
         printf("\n\r\rBilgi yazmak istediginiz adresi giriniz> ");
         
         get_string(_adres,4);      // Seri porttan gelen adres bilgisi string olarak al�n�yor
         adres=atol(_adres);        // String olarak al�nan adres bilgisi tam say�ya �evriliyor
         adres_high=make8(adres,1); // Adres de�erinin 8 bitlik MSB de�eri adres_high de�i�kenine kaydediliyor
         adres_low=make8(adres,0);  // Adres de�erinin 8 bitlik LSB de�eri adres_low de�i�kenine kaydediliyor
                 
         printf("\n\r\rBilgiyi giriniz> ");
         veri=gethex();  // Yaz�lacak veri heksadesimal olarak al�n�yor
         printf("\n\r\rVeri yaziliyor...");

         output_low(cs);         // Entegre se�iliyor
         
         yazma_izin=0x06;  // yazmaya izin verme komutu
         yaz=0x02;         // yaz komutu
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&yazma_izin,1,0));   // yazmaya izin verme komutu g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }

         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         
         output_low(cs);         // Entegre se�iliyor
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&yaz,1,0)); // yaz komutu g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }
         delay_ms(5);         // Gecikme veriliyor
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&adres_high,1,0)); // adres de�erinin MSB k�sm� g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }
         delay_ms(5);         // Gecikme veriliyorr
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&adres_low,1,0)); // adres de�erinin LSB k�sm� g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }
         delay_ms(5);         // Gecikme veriliyor
         
         for(i=0;i<8;i++)
         {
            output_bit(SDO, shift_left(&veri,1,0));   // yazd�r�lacak veri bit bit g�nderiliyor
            output_high(SCK); // Bilgi g�nderiliyor
            output_low(SCK);  // clock sinyali beklemeye al�n�yor
         }
         delay_ms(5);            // Gecikme veriliyor
         output_high(cs);        // Entegre bekleme konumuna getiriliyor
         printf("\n\r\rYazma islemi bitti.");
      }
   }
}


