/******************************************************
 Uygulama Adý      : 74164 ile 2 Çýkýþla 7 Segment Display Sürme 
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use fast_io(b) // Port yönlendirme komutlarý b portu için geçerli

#define data pin_b0   // data sabiti pin_b0'a eþitleniyor
#define clock pin_b1  // clock sabiti pin_b1'e eþitleniyor

// Ortak katot display için veri deðerleri
int digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};

char i=0,j=0;  // Karakter tipinde deðiþken tanýmlamasý yapýlýyor

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

   output_b(0x00); // Ýlk anda B portu çýkýþý sýfýrlanýyor

   while(1)
   {
     for(i=0;i<10;i++)   // Displayde gösterilecek 0-9 sayýlarý için döngü

     {

        for(j=0;j<8;j++) // Gönderilecek verinin bit bit gönderilmesi için
                         // oluþturulan döngü
        {
           output_bit(data,bit_test(digit[i],j)); // Bit deðeri data pinine gönderiliyor

           output_high(clock); // Clock sinyali lojik-1 yapýlýyor
           output_low(clock);  // Clock sinyali lojik-0 yapýlýyor
        }
        delay_ms(500); // Gecikme veriliyor
    }
   }
}
