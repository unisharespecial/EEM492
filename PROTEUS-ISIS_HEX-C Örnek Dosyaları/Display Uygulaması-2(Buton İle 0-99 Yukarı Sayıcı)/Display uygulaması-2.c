/******************************************************
 Uygulama Ad�      : Display Uygulamas�-2 (Buton �le 0-99 Yukar� Say�c�)
 PIC PROG/DEKA     : Port B jumper'� 7-seg konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor


#use fast_io(a) // Port y�nlendirme komutlar� a portu i�in ge�erli
#use fast_io(b) // Port y�nlendirme komutlar� b portu i�in ge�erli

#define   display_1   pin_a0      //display_1 ifadesi pin_a0 ifadesine e�leniyor
#define   display_2   pin_a1      // display_2 ifadesi pin_a1 ifadesine e�leniyor
#define   buton      pin_a2      // buton ifadesi pin_a2 ifadesine e�itleniyor

char birler=0, onlar=0, sayi=0;       // char tipinde de�i�kenler tan�mlan�yor

// Ortak katot display i�in veri de�erleri
const int digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};

/********* ANA PROGRAM FONKS�YONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0xFC);
   set_tris_b(0x00); // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   output_low(display_1);      // 1. display pasif durumda
   output_low(display_2);      // 2. display pasif durumda

   while(1)
   {
         birler=sayi%10;  // birler hanesi hesaplan�yor
         onlar=sayi/10;   // onlar hanesi hesaplan�yor

         output_high(display_2);  // 2. display aktif durumda
         output_b(digit[birler]); // displaye bilgi g�nderiliyor
         delay_ms(5);             // gecikme veriliyor
         output_low(display_2);   // 2. display pasif durumda
         output_high(display_1);  // 1. display aktif durumda
         output_b(digit[onlar]);  // displaye bilgi g�nderiliyor
         delay_ms(5);             // gecikme veriliyor
         output_low(display_1);   // 1. display pasif durumda

         if (input(buton))  // Artt�r butonuna bas�ld� ise
         {
            delay_ms(10);   // Buton arklar�n� �nleme gecikmesi

            sayi++;         // sayi de�i�kenini 1 artt�r

            if (sayi==100)  // E�er sayi de�i�keni 100 oldu ise s�f�rla
              sayi=0;

            birler=sayi%10;          // birler hanesi hesaplan�yor
            onlar=sayi/10;           // onlar hanesi hesaplan�yor

            while(input(buton))  // Buton b�rak�lana kadar d�ng�y� i�le
            {
               output_high(display_2);  // 2. display aktif durumda
               output_b(digit[birler]); // displaye bilgi g�nderiliyor
               delay_ms(5);             // gecikme veriliyor
               output_low(display_2);   // 2. display pasif durumda
               output_high(display_1);  // 1. display aktif durumda
               output_b(digit[onlar]);  // displaye bilgi g�nderiliyor
               delay_ms(5);             // gecikme veriliyor
               output_low(display_1);   // 1. display pasif durumda
            }
         }
   }
}

