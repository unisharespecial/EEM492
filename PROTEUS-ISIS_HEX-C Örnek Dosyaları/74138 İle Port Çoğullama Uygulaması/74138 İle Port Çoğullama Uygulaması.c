/******************************************************
 Uygulama Adý      : 74138 Ýle Port Çoðullama Uygulamasý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use fast_io(b) // Port yönlendirme komutlarý b portu için geçerli

int i; // Tamsayý tipinde deðiþken tanýmlanýyor

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
   
   set_tris_b(0x00); // B portu tümüyle çýkýþ olarak yönlendiriliyor

   while(1) // Sonsuz döngü
   {
      for(i=0;i<8;i++) // 1. 74138 entegresi çýkýþ kontrolü
      {
         output_b(i|0b00000000); // Ýlk 74138 seçiliyor ve sýrayla çýkýþlar aktif yapýlýyor
         delay_ms(250);          // Gecikme veriliyor
      }
      for (i=0;i<8;i++) // 2. 74138 entegresi çýkýþ kontrolü
      {
         output_b(i|0b00010000); // Ýkinci 74138 seçiliyor ve sýrayla çýkýþlar aktif yapýlýyor
         delay_ms(250);          // Gecikme veriliyor
      }
      for(i=0;i<8;i++) // 3. 74138 entegresi çýkýþ kontrolü
      {
         output_b(i|0b00100000); // Üçüncü 74138 seçiliyor ve sýrayla çýkýþlar aktif yapýlýyor
         delay_ms(250);          // Gecikme veriliyor
      }
      for (i=0;i<8;i++) //  4. 74138 entegresi çýkýþ kontrolü
      {
         output_b(i|0b00110000); // Dördüncü 74138 seçiliyor ve sýrayla çýkýþlar aktif yapýlýyor
         delay_ms(250);          // Gecikme veriliyor
      }
   }
}

