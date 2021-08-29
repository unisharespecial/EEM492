/******************************************************
      PIC16F877 ile Paralel LCD Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

int x;      // Tamsay� tipinde de�i�ken tan�mlan�yor
float y;    // Ondal�kl� tipte de�i�ken tan�mlan�yor
char z;     //  Karakter tipinde de�i�ken tan�mlan�yor

byte dizi[6]={0x45,0xC6,0xA3,0xE2,0x56};

//********** ANA PROGRAM FONKS�YONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_b(0x00);   // B portu komple ��k��

   lcd_init();   // LCD haz�rlan�yor

   x=10;   // x de�i�kenine de�er veriliyor
   y=32.6; // y de�i�kenine de�er veriliyor
   
   
   
   while(1) // Sonsuz d�ng�
   {shift_right(dizi,4,1);
      lcd_send_byte(0,0x0d);   // LCD'ye komut g�nderiliyor. �mle� yan�p s�ns�n komutu.
      printf(lcd_putc,"\f     CCS C"); // LCD'ye veri g�nderiliyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\n  Derleyicisi");
      delay_ms(1000); // 1 sn gecikme
      lcd_gotoxy(1,2);   // Kurs�r 1.s�tun, 2.sat�ra konumland�r�l�yor.
      printf(lcd_putc,"\fX DEGERI=%d",x); // LCD'de tamsay� olarak x de�i�ken de�eri g�r�nt�leniyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\f\nY DEGERI=%f",y); // LCD'de ondal�kl� olarak y de�i�ken de�eri g�r�nt�leniyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\fDIRENC"); // LCD siliniyor ve "Direnc" stringi yazd�r�l�yor.
      delay_ms(1000); // 1 sn gecikme
      z=lcd_getc(3,1);  // LCD'de o an 3.S�tun ve 1.Sat�rda olan karakter al�n�yor. Al�nan de�er z de�i�kenine aktar�l�yor.
      printf(lcd_putc,"\f%c",z);    // z de�i�keni LCD'ye aktar�l�yor
      delay_ms(2000); // 2 sn gecikme
   }
}

