/******************************************************
 Uygulama Adý      : Display Uygulamasý-1 (0-F Sayýcý)
 PIC PROG/DEKA     : Port B jumper'ý 7-seg konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

int i;  // i isminde 8 bitlik bir deðiþken tanýtýlýyor.

// Ortak katot display için veri deðerleri
const int digit[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

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

   set_tris_a(0x00); // A portu tümüyle çýkýþ olarak yönlendiriliyor
   set_tris_b(0x00); // B portu tümüyle çýkýþ olarak yönlendiriliyor

   output_b(0x00);  // B portu çýkýþlarý sýfýrlanýyor
   output_a(0x02);  // RA1 pini lojik-1 yapýlýyor, diðer pinler lojik-0

   while(1)   // Sonsuz döngü oluþturuluyor
   {
      for(i=0;i<=15;i++)
      {
         output_b(digit[i]); // digit[i] deðerini B portuna gönder
         delay_ms(500);      // 500 msn bekle
      }
   }
}

