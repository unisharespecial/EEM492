/*******************************************************
      PIC16F877 ile Grafik LCD Uygulamasý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses HS,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=20000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#include <HDM64GS12.c> // HDM64GS12.c dosyasý programa ekleniyor
#include <graphics.c>  // graphics.c dosyasý programa ekleniyor

char yazi1[]="GAZI";        // Karakter dizisi tanýmlanýyor
char yazi2[]="UNIVERSITY";  // Karakter dizisi tanýmlanýyor
int i,x1,y1,x2,y2;

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   glcd_init(ON); // Grafik LCD hazýrlanýyor ve ekran siliniyor

   while(1)
   {
      glcd_init(ON); // Ekran siliniyor
      glcd_text57(39, 5, yazi1, 2, ON);  // GLCD'de yazý yazdýrýlýyor
      glcd_text57(5, 30, yazi2, 2, ON);  // GLCD'de yazý yazdýrýlýyor
      delay_ms(2000);

      glcd_init(ON); // Ekran siliniyor
      x1=5;
      y1=5;
      x2=100;
      y2=5;
      for(i=0;i<6;i++)
      {
         glcd_line(x1, y1, x2, y2, ON); // GLCD'de Çizgi çizdiriliyor
         y2=y1+=10; // y2=y1=y2+10; anlamýnda
         x2-=10;    // x2=x2-10; anlamýnda
         delay_ms(1000);
      }

      glcd_init(ON); // Ekran siliniyor
      x1=y1=10;
      for (i=0;i<120;i++)
      {
         glcd_pixel(x1,y1,ON); // Ekranda istenen pikseller aktif yapýlýyor
         y1=x1++;   // y1=x1+1; anlamýnda
         delay_ms(50);
      }

      glcd_init(ON); // Ekran siliniyor
      y2=60;
      x1=5;
      for (i=0;i<8;i++)
      {
         glcd_bar(x1, 0, x1, y2, 10, ON); // GLCD'de çubuk çizdiriliyor
         delay_ms(1000);
         x1+=15; // x1=x1+15; anlamýnda
         y2-=5;  // y2=y2-5; anlamýnda
      }

      glcd_init(ON); // Ekran siliniyor
      for(i=0;i<=30;i=i+5)
      {
         glcd_circle(60, 30, i, NO, ON); // GLCD'de Daire çizdiriliyor
         delay_ms(1000);
      }

      glcd_init(ON); // Ekran siliniyor
      x1=5;
      y1=5;
      x2=120;
      y2=63;
      for(i=0;i<6;i++)
      {
         glcd_rect(x1, y1, x2, y2, NO, ON); // GLCD'de dikdötrgen çizdiriliyor
         y1=x1+=5; // y1=x1+5; anlamýnda
         x2-=5;    // x2=x2-5; anlamýnda
         y2-=5;    // y2=y2-5; anlamýnda
         delay_ms(500);
      }


   }
}
