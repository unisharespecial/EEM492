#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

int x;      // Tamsay� tipinde de�i�ken tan�mlan�yor

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

   x=0;   // x de�i�kenine de�er veriliyor
   
   while(1) // Sonsuz d�ng�
   {
      lcd_send_byte(0,0x0d);   // LCD'ye komut g�nderiliyor. �mle� yan�p s�ns�n komutu.
      printf(lcd_putc,"\f  Ayturan"); // LCD'ye veri g�nderiliyor.
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\n  Derleyicisi");
      delay_ms(1000); // 1 sn gecikme
      printf(lcd_putc,"\f  Ayturan"); // LCD'ye veri g�nderiliyor.
         while(1) // Sonsuz d�ng�
            {
            x++;
      printf(lcd_putc,"\n  ARTAN SAYI=%d",x); // LCD'de tamsay� olarak x de�i�ken de�eri g�r�nt�leniyor.
      delay_ms(1000); // 1 sn gecikme
            }
   }
}

