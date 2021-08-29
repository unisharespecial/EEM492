/******************************************************
 Uygulama Adý     : Buton ile Led Kontrol Uygulamasý
 Programýn Amacý  : Bu program ile B0 portuna baðlý LED, RA0 giriþine baðlý buton ile kontrol edilmektedir.
 PIC PROG/DEKA    : Port B jumper'ý LED konumunda olmalý
 Yazan            : SERDAR ÇÝÇEK
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use fast_io(a) // Port yönlendirme komutlarý A portu için geçerli
#use fast_io(b) // Port yönlendirme komutlarý B portu için geçerli

int1 x; // 1 bitlik x adýnda tamsayý tipinde bir deðiþken tanýmlanýyor.

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

   set_tris_a(0b00000001);    // RA0 ucu giriþ olarak ayarlandý.
   set_tris_b(0x00);    // RB0 portu tümüyle çýkýþ olarak ayarlandý.
   
   output_b(0x00);

   basla:
   x=input(pin_a0);      // RA0 giriþi okunuyor, tersleniyor ve x deðiþkenine aktarýlýyor.
   output_bit(pin_b0,x);  // x deðiþkeni deðeri RB0 pini çýkýþýna aktarýlýyor.
   goto basla;            // basla etiketinin olduðu yere gidilir.
}

