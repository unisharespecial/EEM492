/******************************************************
 Uygulama Ad�      : 74164 ile 2 ��k��la 7 Segment Display S�rme 
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use fast_io(b) // Port y�nlendirme komutlar� b portu i�in ge�erli

#define data pin_b0   // data sabiti pin_b0'a e�itleniyor
#define clock pin_b1  // clock sabiti pin_b1'e e�itleniyor

// Ortak katot display i�in veri de�erleri
int digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};

char i=0,j=0;  // Karakter tipinde de�i�ken tan�mlamas� yap�l�yor

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

   set_tris_b(0x00); // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   output_b(0x00); // �lk anda B portu ��k��� s�f�rlan�yor

   while(1)
   {
     for(i=0;i<10;i++)   // Displayde g�sterilecek 0-9 say�lar� i�in d�ng�

     {

        for(j=0;j<8;j++) // G�nderilecek verinin bit bit g�nderilmesi i�in
                         // olu�turulan d�ng�
        {
           output_bit(data,bit_test(digit[i],j)); // Bit de�eri data pinine g�nderiliyor

           output_high(clock); // Clock sinyali lojik-1 yap�l�yor
           output_low(clock);  // Clock sinyali lojik-0 yap�l�yor
        }
        delay_ms(500); // Gecikme veriliyor
    }
   }
}
