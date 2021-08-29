/******************************************************
      PIC16F877 ile Flash Program Haf�zas� Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c> // LCD.c dosyas� programa ekleniyor

int16  adres=0,deger=0;

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

   set_tris_a(0x01);   // RA1 pini giri�

   lcd_init();         // LCD kurulumu yap�l�yor

   printf(lcd_putc,"\fProgram Kodlari"); // LCD'ye yaz� yazd�r�l�yor
   delay_ms(1000);
   printf(lcd_putc,"\fAdres       Kod"); // LCD'ye yaz� yazd�r�l�yor

   while (!(adres==0x3FFF)) // Program kodu 0x3FFF de�erine e�it oluncaya kadar d�ng�y� i�le
                            // 0x3FFF Bo� olan program bellek kodudur.
   {
      deger=read_program_eeprom(adres); // Program kod haf�zas�nda belirtilen adresteki kodu oku
      lcd_gotoxy(1,2); // �mle� 1.s�tun 2.sat�rda
      printf(lcd_putc,"\n%lx        %lx",adres,deger); // LCD'ye program kod haf�zas� adresini ve i�indeki kodu yaz
      delay_ms(500);
      adres++; // adres de�i�keni i�eri�ini 1 artt�r

      if (input(pin_a0)) // E�er RA0 giri�indeki butona bas�l�rsa
      {
         delay_ms(20);  // Buton ark�n� �nlemek i�in
         write_program_eeprom(adres, 0x0000); // Belirtilen program kod haf�zas� adresine 0 bilgi yaz
      }
   }
   printf(lcd_putc,"\fProgram Bitti..."); // Program�n sonuna geldi�ini bildirir
}
