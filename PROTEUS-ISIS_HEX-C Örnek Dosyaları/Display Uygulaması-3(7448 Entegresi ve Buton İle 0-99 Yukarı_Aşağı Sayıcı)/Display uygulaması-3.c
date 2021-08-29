/******************************************************
 Uygulama Ad�      : Display Uygulamas�-3(7448 Entegresi ve Buton �le 0-99 Yukar�/A�a�� Say�c�)
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use fast_io(a) // Port y�nlendirme komutlar� a portu i�in ge�erli
#use fast_io(b) // Port y�nlendirme komutlar� b portu i�in ge�erli

#define   arttir      pin_a0   // arttir butonu pin_a0 ile e�leniyor
#define   azalt       pin_a1   // azalt butonu pin_a1 ile e�leniyor

char birler=0, onlar=0, sayi=0; // int tipinde de�i�kenler tan�mlan�yor

// Ortak katot display i�in veri de�erleri
const int digit[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};

/********* ANA PROGRAM FONKS�YONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0x03); // RA0 ve RA1 giri� olarak y�nlendiriliyor
   set_tris_b(0x00); // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   while(1)     // Sonsuz d�ng�
   {
       output_b(digit[birler]|(0b00010000)); // 1.display aktif, 2.display pasif yap�l�yor ve birler basama�� bilgisi B portuna g�nderiliyor
       delay_ms(5);                          // Gecikme veriliyor
       output_b(digit[onlar]|(0b00100000));  // 2.display aktif, 1.display pasif yap�l�yor ve onlar basama�� bilgisi B portuna g�nderiliyor
       delay_ms(5);                          // Gecikme veriliyor

       if (input(arttir))   // artt�r butonuna bas�ld���nda
       {
          sayi++;    // sayi de�erini 1 artt�r

          birler=sayi%10;;         // birler hanesi hesaplan�yor
          onlar=sayi/10;           // onlar hanesi hesaplan�yor

          while(input(arttir))     // artt�r butonundan el �ekilene kadar bekle
          {
             output_b(digit[birler]|(0b00010000)); // 1.display aktif, 2.display pasif yap�l�yor ve birler basama�� bilgisi B portuna g�nderiliyor
             delay_ms(5);                          // Gecikme veriliyor
             output_b(digit[onlar]|(0b00100000));  // 2.display aktif, 1.display pasif yap�l�yor ve onlar basama�� bilgisi B portuna g�nderiliyor
             delay_ms(5);                          // Gecikme veriliyor
          }
        }

      if (input(azalt)&&(sayi!=0))   // azalt butonuna bas�ld���nda
       {
          sayi--;     // sayi de�erini 1 azalt

         birler=sayi%10;;         // birler hanesi hesaplan�yor
         onlar=sayi/10;           // onlar hanesi hesaplan�yor

          while(input(azalt))      // azalt butonundan el �ekilene kadar bekle
          {
             output_b(digit[birler]|(0b00010000)); // 1.display aktif, 2.display pasif yap�l�yor ve birler basama�� bilgisi B portuna g�nderiliyor
             delay_ms(5);                          // Gecikme veriliyor
             output_b(digit[onlar]|(0b00100000));  // 2.display aktif, 1.display pasif yap�l�yor ve onlar basama�� bilgisi B portuna g�nderiliyor
             delay_ms(5);                          // Gecikme veriliyor

          }
       }
       if (sayi==100)   // sayi de�eri 100 ise de�eri s�f�rla
          sayi=0;
    }
}
