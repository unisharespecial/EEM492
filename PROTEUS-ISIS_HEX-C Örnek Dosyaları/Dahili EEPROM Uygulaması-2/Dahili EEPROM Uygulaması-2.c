/*****************************************************************
      PIC16F877 ile Dahili EEPROM Uygulamas�-2
PIC PROG/DEKA     :Port B jumper'� LCD konumunda olmal�
******************************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c> // LCD.c dosyas� programa ekleniyor

#include <math.h>       // math.h dosyas� programa dahil ediliyor.

unsigned int8 eeprom_adres,data[1]; //eeprom_adres de�i�keni ve data dizisi tan�mlan�yor
int16 i; // 16 bitlik i de�i�keni tan�mlan�yor

/********* ANA PROGRAM FONKS�YONU********/
void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0x03);   // RA0,RA1 pinleri giri�

   lcd_init();         // LCD kurulumu yap�l�yor

   printf(lcd_putc,"\fEEPROM Adres="); // LCD'ye veri yazd�r�l�yor
   lcd_gotoxy(1,2);                    // �mle� 1.s�tun, 2.sat�ra gidiyor
   printf(lcd_putc,"EEPROM Veri =");   // LCD'ye veri yazd�r�l�yor
   
   while(1)      // Sonsuz d�ng�
   {
      for(i=0; i<=2048; i++)  // 256 Byte veri kaydetmek i�in d�ng�
      {
         while (!input(PIN_A0)); // RA0 butonuna bas�ld���nda
         shift_left(data,1,input(PIN_A1));   // bilgiyi sola kayd�rarak kaydet
         eeprom_adres=floor(i/8);            // EEPROM adres de�erini hesapla
         write_eeprom(eeprom_adres,data[0]); // Belirtilen adrese bilgiyi yaz
         lcd_gotoxy(14,1);                   // �mle� 14.s�tun, 1.sat�ra gidiyor
         printf(lcd_putc,"%3u",eeprom_adres);  // LCD'ye veri yazd�r�l�yor
         lcd_gotoxy(14,2);                      // �mle� 14.s�tun, 1.sat�ra gidiyor
         printf(lcd_putc,"%X",read_eeprom(eeprom_adres));   // LCD'ye veri yazd�r�l�yor       
         while (input(PIN_A0)); // RA0 butonundan el �ekile kadar bekle
      }     
   }
}
