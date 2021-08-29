/******************************************************
 Uygulama Adý      : Display Uygulamasý-2 (Buton Ýle 0-99 Yukarý Sayýcý)
 PIC PROG/DEKA     : Port B jumper'ý 7-seg konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor


#use fast_io(a) // Port yönlendirme komutlarý a portu için geçerli
#use fast_io(b) // Port yönlendirme komutlarý b portu için geçerli

#define   display_1   pin_a0      //display_1 ifadesi pin_a0 ifadesine eþleniyor
#define   display_2   pin_a1      // display_2 ifadesi pin_a1 ifadesine eþleniyor
#define   buton      pin_a2      // buton ifadesi pin_a2 ifadesine eþitleniyor

char birler=0, onlar=0, sayi=0;       // char tipinde deðiþkenler tanýmlanýyor

// Ortak katot display için veri deðerleri
const int digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};

/********* ANA PROGRAM FONKSÝYONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_a(0xFC);
   set_tris_b(0x00); // B portu tümüyle çýkýþ olarak yönlendiriliyor

   output_low(display_1);      // 1. display pasif durumda
   output_low(display_2);      // 2. display pasif durumda

   while(1)
   {
         birler=sayi%10;  // birler hanesi hesaplanýyor
         onlar=sayi/10;   // onlar hanesi hesaplanýyor

         output_high(display_2);  // 2. display aktif durumda
         output_b(digit[birler]); // displaye bilgi gönderiliyor
         delay_ms(5);             // gecikme veriliyor
         output_low(display_2);   // 2. display pasif durumda
         output_high(display_1);  // 1. display aktif durumda
         output_b(digit[onlar]);  // displaye bilgi gönderiliyor
         delay_ms(5);             // gecikme veriliyor
         output_low(display_1);   // 1. display pasif durumda

         if (input(buton))  // Arttýr butonuna basýldý ise
         {
            delay_ms(10);   // Buton arklarýný önleme gecikmesi

            sayi++;         // sayi deðiþkenini 1 arttýr

            if (sayi==100)  // Eðer sayi deðiþkeni 100 oldu ise sýfýrla
              sayi=0;

            birler=sayi%10;          // birler hanesi hesaplanýyor
            onlar=sayi/10;           // onlar hanesi hesaplanýyor

            while(input(buton))  // Buton býrakýlana kadar döngüyü iþle
            {
               output_high(display_2);  // 2. display aktif durumda
               output_b(digit[birler]); // displaye bilgi gönderiliyor
               delay_ms(5);             // gecikme veriliyor
               output_low(display_2);   // 2. display pasif durumda
               output_high(display_1);  // 1. display aktif durumda
               output_b(digit[onlar]);  // displaye bilgi gönderiliyor
               delay_ms(5);             // gecikme veriliyor
               output_low(display_1);   // 1. display pasif durumda
            }
         }
   }
}

