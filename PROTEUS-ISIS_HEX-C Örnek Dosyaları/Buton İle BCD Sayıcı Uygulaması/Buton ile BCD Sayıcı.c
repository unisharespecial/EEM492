/******************************************************
 Uygulama Adý      : Buton ile BCD Sayýcý
 Programýn Amacý   : RA0 butonuna her basýþta 0'dan itibaren artan BCD sayýlar
                     B portuna baðlý LED'lerde görünecektir
 PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#define buton pin_A0    // "buton" adýnda "pin_A0" kelimesine eþit bir sabit tanýmlanýyor

int i=1;     // 8 bitlik tamsayý tipinde deðiþken tanýmlanýyor

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

   set_tris_a(0x01);    // RA0 pini giriþ olarak yönlendiriliyor
   set_tris_b(0x00);    // RB0 portu tümüyle çýkýþ olarak yönlendiriliyor

   output_b(0x00);      // B portu çýkýþlarý sýfýrlanýyor

   while(1)       // Sonsuz döngü oluþturuluyor
   {
      if (input(buton))
      {
         delay_ms(15);  // Butona basýlýnca meydana gelen arkýn etkisini önlemek için verilen gecikme
         output_b(i);   // b portuna i deðeri yükleniyor
         i=i+1;         // i deðeri 1 arttýrýlýyor
         while(input(buton)); // Buton býrakýlana kadar bekle
         if (i==10)     // i deðeri test ediliyor.i deðeri 10 olunca sýfýrlanýyor.
         {
            i=0;        // i deðeri sýfýrlanýyor
         }
      }
   }
}
