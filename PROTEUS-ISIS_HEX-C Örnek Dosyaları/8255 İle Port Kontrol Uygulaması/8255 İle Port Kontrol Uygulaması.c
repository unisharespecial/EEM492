/******************************************************
 Uygulama Ad�      : 8255 �le Port Kontrol Uygulamas�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use standard_io (a) // A portu i�in giri�/��k�� y�nlendirmesi yap�lmas�na gerek yok
#use standard_io (b) // B portu i�in giri�/��k�� y�nlendirmesi yap�lmas�na gerek yok

int data; // Tamsay� tipinde de�i�ken tan�mlan�yor

//************** 8255 OKUMA FONKS�YONU ***************
void _8255_yazma (char x, char bilgi)
{
   switch (x)
   {
      case   'k':                   // Kaydediciye yazma se�ilirse
             output_a(0b00001101);  // Kaydediciye yazma
             output_b(bilgi);       // Yaz�lacak bilgi g�nderiliyor
             break;

      case   'a':                   // A portuna yazma se�ilirse
             output_a(0b00000001);  // A portuna yazma
             output_b(bilgi);       // Yaz�lacak bilgi g�nderiliyor
             break;

      case   'b':                   // B portuna yazma se�ilirse
             output_a(0b00000101);  // B portuna yazma
             output_b(bilgi);       // Yaz�lacak bilgi g�nderiliyor
             break;

      case   'c':                   // C portuna yazma se�ilirse
             output_a(0b00001001);  // C portuna yazma
             output_b(bilgi);       // Yaz�lacak bilgi g�nderiliyor
             break;

      default:
             break;
     }
}

//************** 8255 YAZMA FONKS�YONU ***************
int _8255_okuma (char x)
{
   switch (x)
   {
      case   'k':
             output_a(0b00001110); // Kaydediciden okuma
             return(input_b());    // Kaydedici de�eri okunuyor
             break;
      case   'a':
             output_a(0b00000010); // A portundan okuma
             return(input_b());    // A portu de�eri okunuyor ve fonksiyondan bu de�erle ��k�l�yor
             break;
      case   'b':
             output_a(0b00000110); // B portu okuma
             return(input_b());    // B portu de�eri okunuyor ve fonksiyondan bu de�erle ��k�l�yor
             break;
      case   'c':
             output_a(0b00001010); // C portu okuma
             return(input_b());    // C portu de�eri okunuyor ve fonksiyondan bu de�erle ��k�l�yor
             break;
      default:
             break;
   }
}
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

   _8255_yazma('k',0b10001001); // A portu ��k��, C portu giri�, B portu ��k�� yap�l�yor

   while(1) // Sonsuz d�ng�
   {
      data=(_8255_okuma('c'));  // C portu okunuyor
      _8255_yazma('a',data);    // A portuna okunan C portu de�eri yaz�l�yor
   }
}


