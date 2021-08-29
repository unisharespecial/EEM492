/******************************************************
      PIC16F877 ile LM35 S�cakl�k Sens�r� Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#device ADC=10  // 10 bitlik ADC kullan�laca�� belirtiliyor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

unsigned long int bilgi; // ��aretsiz 16 bitlik tam say� tipinde de�i�ken tan�mlan�yor
float voltaj,sicaklik;   // ondal�kl� tipte de�i�kenler tan�t�l�yor

//********** ANA PROGRAM FONKS�YONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0x01);  // RA0 Giri� olarak y�nlendiriliyor

   setup_adc(adc_clock_div_32);   // ADC clock frekans� fosc/32
   setup_adc_ports(AN0); //RA0/AN0 giri�i analog

   lcd_init();   // LCD haz�r hale getiriliyor

   set_adc_channel(0);   // RA0/AN0 ucundaki sinyal A/D i�lemine tabi tutulacak
   delay_us(20);         // Kanal se�iminde sonra bu bekleme s�resi verilmelidir

   printf(lcd_putc,"\fSicaklik="); // LCD'ye yaz� yazd�r�l�yor
   while(1)   // sonsuz d�ng�
   {
      bilgi=read_adc();  // ADC sonucu okunuyor ve bilgi de�i�kenine aktar�l�yor

      voltaj=(0.0048828125*bilgi)*1000;   // Dijitale �evirme i�lemine u�rayan sinyalin mV olarak gerilimi hesaplan�yor
      sicaklik=(voltaj/10)+2;    // Her 10mV'ta 1 derece artma

      lcd_gotoxy(10,1); // �mle� 1. sat�r 10.s�tunda
      printf(lcd_putc,"%5.1f'C",sicaklik); // LCD'ye s�cakl�k de�eri yazd�r�l�yor
      // G�sterilecek ondal�kl� de�erin toplam basamak say�s� 5 olacak.
      // G�sterilecek de�erin ondal�kl� k�sm� ise 1 basamak olacak. %5.1f
      // komutu ile bu i�lemler yapt�r�lm��t�r.
      delay_ms(100); // 100 msn gecikme
   }
}


