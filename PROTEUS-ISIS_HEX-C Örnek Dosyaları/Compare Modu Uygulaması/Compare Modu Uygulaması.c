/******************************************************
      PIC16F877 ile Compare Modu Uygulamasý
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli
#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli

//*********** CCP1 KESMESÝ ******************
#INT_CCP1   // INT_CCP1 kesmesi fonksiyonu
void karsilastir1_kesmesi ()
{
   output_toggle(pin_b0); // RB0 çýkýþý tersleniyor
}

//*********** CCP2 KESMESÝ ******************
#INT_CCP2   // INT_CCP2 kesmesi fonksiyonu
void karsilastir2_kesmesi ()
{
   set_timer1(0);   // TMR1 içeriði sýfýrlanýyor
   output_toggle(pin_b1); // RB1 çýkýþý tersleniyor
}

/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý

   set_tris_b(0x00);   // B portu komple çýkýþ
   set_tris_c(0x01);   // RC0 pini giriþ

   output_b(0x00); // Ýlk anda B portu çýkýþý sýfýrlanýyor

   enable_interrupts(INT_CCP1);  // INT_CCP1 kesmesi aktif yapýlýyor
   enable_interrupts(INT_CCP2);  // INT_CCP2 kesmesi aktif yapýlýyor
   enable_interrupts(GLOBAL);    // Aktif edilen kesmelere izin ver

   setup_ccp1(CCP_COMPARE_INT); // CCP1 birimi COMPARE modunda kullanýlacak
   setup_ccp2(CCP_COMPARE_INT); // CCP2 birimi COMPARE modunda kullanýlacak


   setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1); // Timer1 ayarlarý yapýlýyor

   CCP_1_HIGH=0x00; // CCPR1H kaydedicisi sýfýrlanýyor
   CCP_1_LOW=0x05;  // CCPR1L kaydedicisine 05h deðeri yükleniyor.

   CCP_2_HIGH=0x00; // CCPR2H kaydedicisi sýfýrlanýyor
   CCP_2_LOW=0x0A;  // CCPR2L kaydedicisine 0Ah deðeri yükleniyor.

   set_timer1(0); // TMR1 içeriði sýfýrlanýyor

   while(1); // Sonsuz döngü
}


