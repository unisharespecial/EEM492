/******************************************************
 Uygulama Adý      : 8255 Ýle Port Kontrol Uygulamasý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use standard_io (a) // A portu için giriþ/çýkýþ yönlendirmesi yapýlmasýna gerek yok
#use standard_io (b) // B portu için giriþ/çýkýþ yönlendirmesi yapýlmasýna gerek yok

int data; // Tamsayý tipinde deðiþken tanýmlanýyor

//************** 8255 OKUMA FONKSÝYONU ***************
void _8255_yazma (char x, char bilgi)
{
   switch (x)
   {
      case   'k':                   // Kaydediciye yazma seçilirse
             output_a(0b00001101);  // Kaydediciye yazma
             output_b(bilgi);       // Yazýlacak bilgi gönderiliyor
             break;

      case   'a':                   // A portuna yazma seçilirse
             output_a(0b00000001);  // A portuna yazma
             output_b(bilgi);       // Yazýlacak bilgi gönderiliyor
             break;

      case   'b':                   // B portuna yazma seçilirse
             output_a(0b00000101);  // B portuna yazma
             output_b(bilgi);       // Yazýlacak bilgi gönderiliyor
             break;

      case   'c':                   // C portuna yazma seçilirse
             output_a(0b00001001);  // C portuna yazma
             output_b(bilgi);       // Yazýlacak bilgi gönderiliyor
             break;

      default:
             break;
     }
}

//************** 8255 YAZMA FONKSÝYONU ***************
int _8255_okuma (char x)
{
   switch (x)
   {
      case   'k':
             output_a(0b00001110); // Kaydediciden okuma
             return(input_b());    // Kaydedici deðeri okunuyor
             break;
      case   'a':
             output_a(0b00000010); // A portundan okuma
             return(input_b());    // A portu deðeri okunuyor ve fonksiyondan bu deðerle çýkýlýyor
             break;
      case   'b':
             output_a(0b00000110); // B portu okuma
             return(input_b());    // B portu deðeri okunuyor ve fonksiyondan bu deðerle çýkýlýyor
             break;
      case   'c':
             output_a(0b00001010); // C portu okuma
             return(input_b());    // C portu deðeri okunuyor ve fonksiyondan bu deðerle çýkýlýyor
             break;
      default:
             break;
   }
}
/********* ANA PROGRAM FONKSÝYONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   _8255_yazma('k',0b10001001); // A portu çýkýþ, C portu giriþ, B portu çýkýþ yapýlýyor

   while(1) // Sonsuz döngü
   {
      data=(_8255_okuma('c'));  // C portu okunuyor
      _8255_yazma('a',data);    // A portuna okunan C portu deðeri yazýlýyor
   }
}


