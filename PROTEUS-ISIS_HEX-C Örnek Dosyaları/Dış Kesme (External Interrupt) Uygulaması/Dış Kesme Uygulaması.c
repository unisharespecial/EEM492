/******************************************************
      PIC16F877 ile Dýþ Kesme (INT_EXT) Uygulamasý
      PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli

int i; // Tamsayý tipinde deðiþken tanýmlanýyor

//****** Dýþ Kesme Fonksiyonu *****************
#int_ext                // Dýþ (External) RB0/INT kesmesi
void  ext_kesmesi ()    // Dýþ kesme fonksiyonu
{
   output_high(pin_b1);
   delay_ms(1000);
   output_low(pin_b1);
   delay_ms(3000);

   for (i=0;i<10;i++)
   {
      output_high(pin_b1);
      delay_ms(500);
      output_low(pin_b1);
      delay_ms(500);
   }
}


/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý


   set_tris_b(0x01);   // RB0 pini giriþ,diðer uçlar çýkýþ olarak yönlendiriliyor
   output_b(0x00);     // B portu çýkýþý ilk anda sýfýrlanýyor

   ext_int_edge(H_TO_L);   // INT_EXT kesmesinin düþen kenarda aktif olacaðýný belirtir

   enable_interrupts(INT_EXT);  // INT_EXT kesmesini aktif yapar
   enable_interrupts(GLOBAL);   // Aktif edilen kesmelere izin ver

   while(1);  // Sonsuz döngü
 }
