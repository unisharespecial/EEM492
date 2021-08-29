/******************************************************
 Uygulama Adý      : Yürüyen Iþýk
 PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

int i, led; //i ve led isminde tam sayý tipinde 8 bitlik deðiþkenler tanýtýlýyor.

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

   set_tris_b(0x00);    // B portu tümüyle çýkýþ olarak yönlendiriliyor

   output_b(0x00);      // B portu çýkýþlarý sýfýrlanýyor

   while(1)
   {
      led=1;      //led deðiþkeni deðeri 1 oluyor

      for(i=0;i<=7;i++)   // for döngüsü oluþturuluyor
      {
         output_b(led);      // led deðiþkeni deðeri B portuna gönder
         led=led<<1;         // led deðiþkeni deðerini 1 bit sola kaydýr
         delay_ms(100);      // 100 msn'lik gecikme veriliyor
      }

      led=0x80;       //led deðiþkenine deðer yükleniyor
      output_b(led);  //B portuna 0b10000000 bilgisi gönderiliyor
      delay_ms(100);  // 100 msn'lik gecikme veriliyor
      
       for(i=0;i<=6;i++)  // for döngüsü oluþturuluyor
      {
         led=led>>1;    // led deðiþkeni deðerini 1 bit saða kaydýr
         output_b(led); // led deðiþkeni deðeri B portuna gönder
         delay_ms(100); // 100 msn'lik gecikme veriliyor
      }
   }
}




