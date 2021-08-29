/******************************************************
      PIC16F877 Ýle Bilgisayar Ýle Step Motor Uygulamasý
******************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 protokolü ayarlarý belirtiliyor

int i,hiz=500; // Tam sayý tipinde deðiþkenler tanýmlanýyor
char islem=0;  // Karakter tipinde deðiþken tanýmlanýyor

const int yarim_adim[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09}; // Step motor yarým adým dönüþ adýmlarý

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

   output_b(0x00); // B portu çýkýþý baþlangýçta sýfýrlanýyor

/****************MENÜ**********************************/

   printf("\n\r************************************************");
   printf("\n\r           ADIM MOTOR KONTROLÜ                  ");
   printf("\n\r************************************************");
   printf("\n\n");
   printf("\n\rIslem Seciniz:\n");
   printf("\n\r------------------------------------------------");
   printf("\n\r   Saga Dondur   (R)");
   printf("\n\r   Sola Dondur   (L)");
   printf("\n\r   Motoru Durdur (R ve L disindaki herhangi bir tus)");
   printf("\n\r------------------------------------------------");
   printf("\n\rYapmak istediginiz islemi seciniz>");

   while(1)
   {
      islem="null";    // islem deðiþkeninin içeriðini boþ olarak ayarla
      islem=getchar(); // Seri port üzerinden gelen karakter islem deðiþkenine aktarýlýyor
      putc(islem);     // RS232 üzerinden klavye'den girilen karakteri ekrana gönder.

      while (islem=='R'||islem=='r')   //Saða döndürme iþlemi seçildi ise
      {
         printf("\n\rMotor Saga Donuyor...");
         for (;i<8;i++)   // Sýra ile saða dönme deðerlerini gönder
         {
            output_b(yarim_adim[i]); // Step motor 1 adým ileri
            delay_ms(hiz);           // Adýmlar arasýndaki süre

            if (i==7)   // Eðer i deðeri 7 olursa sýfýrla
               i=0;

           if (kbhit()) break;   //Seri portan bir veri alýndý ise döngüden çýk
         }
         if (kbhit()) break;     //Seri portan bir veri alýndý ise döngüden çýk
      }

      while (islem=='L'||islem=='l')   //Sola döndürme iþlemi seçildi ise
      {
         printf("\n\rMotor Sola Donuyor...");

         for (;i>=0;i--)   // Sýra ile sola dönme deðerlerini gönder
         {
            if (i==0)   // Eðer i deðeri 0 ise i deðeri 7 olsun
               i=7;
            output_b(yarim_adim[i]);   // Step motor 1 adým geri
            delay_ms(hiz);             // Adýmlar arasýndaki süre

            if (kbhit()) break;        // Seri portan bir veri alýndý ise döngüden çýk
         }
         if (kbhit()) break;           // Seri portan bir veri alýndý ise döngüden çýk
      }
   }
}
