/******************************************************
      PIC16F877 ile RS232 Seri �leti�im Uygulamas�
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 protokol�n�n 9600 bit/sn baud h�z�nda olaca��n� ve
                                                                  // TX,RX u�lar�n�n hangi pinler olaca��n� tan�ml�yor
                                                                  // parity bitinin olmad���n�, stop bitinin 1 bit olaca�� belirtiliyor

char   klavye[80];  // klavye isminde 80 �yeli bir dizi tan�mlan�yor

#int_rda   // RX ucuna veri gelince meydane gelen kesme
void serihaberlesme_kesmesi ()
{
   disable_interrupts(int_rda); // int_rda kesmesini pasif yap
   output_high(pin_c5);  // RC5 ��k��� lojik-1
   gets(klavye); // String ifadeyi al ve "klavye" adl� dizi de�i�kenine aktar.
   printf("\n\rYazdiginiz Metin>  %s\n",klavye); // Sat�r atla, yeni sat�r,RS232 �zerinden klavye string ifadesini g�nder,sat�r atla
   printf(lcd_putc,"\f%s",klavye);  //LCD'yi temizle ve klavye string ifadesini LCD'de g�ster
   output_low(pin_c5); // RC5 ��k��� lojik-0
   printf("\n\rKlavyeden bir metin giriniz ve enter tusuna basiniz>"); // Sat�r atla, yeni sat�r,RS232 �zerinden belirtilen metni g�nder
}

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

   output_low(pin_c5); // RC5 ��k��� ilk anda s�f�rlan�yor
   lcd_init();   // LCD'yi haz�rla

   printf("\r**************** Merhaba *********************"); // Yeni sat�r, RS232 �zerinden belirtilen metni g�nder ve sat�r atla.
   printf("\n\rKlavyeden girdiginiz bilgiler LCD'de gorunecektir\n\n"); // Sat�r atla, yeni sat�r, RS232 �zerinden belirtilen metni g�nder
   printf("\n\rKlavyeden bir metin giriniz ve enter tusuna basiniz>"); // Sat�r atla, yeni sat�r,RS232 �zerinden belirtilen metni g�nder

   enable_interrupts(GLOBAL);  // Aktif edilen t�m kesmelere izin ver

   while(1) // Sonsuz d�ng�
   {
      enable_interrupts(int_rda); // int_rda kesmesi aktif
   }
}
