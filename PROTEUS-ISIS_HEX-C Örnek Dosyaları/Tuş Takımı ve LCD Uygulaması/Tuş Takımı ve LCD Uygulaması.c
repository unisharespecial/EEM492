/******************************************************
      PIC16F877 ile Tu� Tak�m� ve LCD Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(b) //Port y�nlendirme komutlar� B portu i�in ge�erli
#use fast_io(d) //Port y�nlendirme komutlar� B portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

#define sut1   pin_d0 // sut1 ifadesi pin_d0 ifadesine e�itleniyor
#define sut2   pin_d1 // sut2 ifadesi pin_d1 ifadesine e�itleniyor
#define sut3   pin_d2 // sut3 ifadesi pin_d2 ifadesine e�itleniyor
#define sut4   pin_d3 // sut3 ifadesi pin_d2 ifadesine e�itleniyor

#define sat1   pin_d4 // sat1 ifadesi pin_d4 ifadesine e�itleniyor
#define sat2   pin_d5 // sat2 ifadesi pin_d5 ifadesine e�itleniyor
#define sat3   pin_d6 // sat3 ifadesi pin_d6 ifadesine e�itleniyor
#define sat4   pin_d7 // sat4 ifadesi pin_d7 ifadesine e�itleniyor

 char tus=0; // karakter tipinde de�i�ken tan�mlan�yor

//*********** Keypad Tarama Fonksiyonu *********

char keypad_oku() // Fonksiyon ismi
{
   output_d(0x00); // D portu ��k��� s�f�rlan�yor

   output_high(sat1); // 1. sat�r lojik-1 yap�l�yor
   if (input(sut1))   // 1. s�tun okunuyor
      { delay_ms(20); tus=1; }
   if (input(sut2))   // 2. s�tun okunuyor
      { delay_ms(20); tus=2; }
   if (input(sut3))   // 3. s�tun okunuyor
      { delay_ms(20); tus=3; }
   if (input(sut4))   // 4. s�tun okunuyor
      { delay_ms(20); tus=0xA; }
   output_low(sat1); // 1. sat�r lojik-0 yap�l�yor

   output_high(sat2); // 2. sat�r lojik-1 yap�l�yor
   if (input(sut1))   // 1. s�tun okunuyor
      { delay_ms(20); tus=4; }
   if (input(sut2))   // 2. s�tun okunuyor
      { delay_ms(20); tus=5; }
   if (input(sut3))   // 3. s�tun okunuyor
      { delay_ms(20); tus=6; }
   if (input(sut4))   // 4. s�tun okunuyor
      { delay_ms(20); tus=0xB; }
   output_low(sat2); // 2. sat�r lojik-0 yap�l�yor

   output_high(sat3); // 3. sat�r lojik-1 yap�l�yor
   if (input(sut1))   // 1. s�tun okunuyor
      { delay_ms(20); tus=7; }
   if (input(sut2))   // 2. s�tun okunuyor
      { delay_ms(20); tus=8; }
   if (input(sut3))   // 3. s�tun okunuyor
      { delay_ms(20); tus=9; }
   if (input(sut4))   // 4. s�tun okunuyor
      {delay_ms(20); tus=0x0C; }
   output_low(sat3); // 3. sat�r lojik-0 yap�l�yor

   output_high(sat4); // 3. sat�r lojik-1 yap�l�yor
   if (input(sut1))   // 1. s�tun okunuyor
      { delay_ms(20); tus=0xE; }
   if (input(sut2))   // 2. s�tun okunuyor
      { delay_ms(20); tus=0; }
   if (input(sut3))   // 3. s�tun okunuyor
      { delay_ms(20); tus=0xF; }
   if (input(sut4))   // 4. s�tun okunuyor
      {delay_ms(20); tus=0xD; }
   output_low(sat4); // 3. sat�r lojik-0 yap�l�yor

   return tus; // Fonksiyon "tus" de�eri ile geri d�ner
}

//********** ANA PROGRAM FONKS�YONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���

   set_tris_b(0x00);   // B portu komple ��k��
   set_tris_d(0x0F);   // Y�ksek de�erlikli 4 bit ��k��, d���k de�erlikli 4 bit giri�

   lcd_init();   // LCD haz�rlan�yor

   printf(lcd_putc,"\fBasilan Tus="); // LCD'ye string yazd�r�l�yor

   while(1) // Sonsuz d�ng�
   {
      lcd_gotoxy(13,1); // �mle� 3.s�tun, 1.sat�ra konumland�r�l�yor

      if (keypad_oku()>9)   // E�er bas�lan tu� de�eri 9'dan b�y�k ise
         printf(lcd_putc,"%d",keypad_oku());  // Tu� de�eri LCD'ye yazd�r�l�yor
      else                  // E�er bas�lan tu� de�eri 9'dan b�y�k de�ilse
         printf(lcd_putc,"%d ",keypad_oku()); // Tu� de�eri LCD'ye yazd�r�l�yor
   }
}

