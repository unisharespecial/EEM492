/******************************************************
      PIC16F877 ile Capture Modu Uygulamasý
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli
#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli

int i=0; // Tamsayý tipinde deðiþken tanýmlanýyor

//*********** CCP1 KESMESÝ ******************
#INT_CCP1   // INT_CCP1 kesmesi fonksiyonu
void yakala1_kesmesi ()
{
   i++;   // i deðerini 1 arttýr
   output_b(i); // i deðerini B portuna gönder
}

//*********** CCP2 KESMESÝ ******************
#INT_CCP2   // INT_CCP2 kesmesi fonksiyonu
void yakala2_kesmesi ()
{
   if(i==0)   // Eðer i deðeri sýfýrsa
      i=1;    // i deðeri içeriði 1 olsun

   i--;       // i deðerini 1 azalt
   output_b(i); // i deðerini B portuna gönder
}

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý

   set_tris_b(0x00);   // B portu komple çýkýþ
   set_tris_c(0x07);   // RC0, RC1 ve RC2 pini giriþ

   output_b(0x00); // Ýlk anda B portu çýkýþý sýfýrlanýyor

   enable_interrupts(INT_CCP1);  // INT_CCP1 kesmesi aktif yapýlýyor
   enable_interrupts(INT_CCP2);  // INT_CCP2 kesmesi aktif yapýlýyor
   enable_interrupts(GLOBAL);    // Aktif edilen kesmelere izin ver

   setup_ccp1(CCP_CAPTURE_DIV_4); // CCP1 kesmesi her 4 yükselen kenarda 1 yakalama yapacak
   setup_ccp2(CCP_CAPTURE_RE);    // CCP2 kesmesi her yükselen kenarda 1 yakalama yapacak

   CCP_1_HIGH=0x00; // CCPR1H kaydedicisi sýfýrlanýyor
   CCP_1_LOW=0x00;  // CCPR1H kaydedicisi sýfýrlanýyor

   CCP_2_HIGH=0x00; // CCPR2H kaydedicisi sýfýrlanýyor
   CCP_2_LOW=0x00;  // CCPR2H kaydedicisi sýfýrlanýyor

   while(1); // Sonsuz döngü
}

