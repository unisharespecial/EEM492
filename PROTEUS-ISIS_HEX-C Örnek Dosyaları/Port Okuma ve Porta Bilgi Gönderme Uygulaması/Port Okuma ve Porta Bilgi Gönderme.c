/******************************************************
 Uygulama Adý      : Port Okuma ve Porta Bilgi Gönderme
 Programýn Amacý   : A portu RA0,RA1,RA2 ve RA3 pinlerine baðlý butonlarýn durumunun
                     okunarak, okunan bu bilginin B portuna baðlý LED'lerde gösterilmesi
 PIC PROG/DEKA     : Port B jumper'ý LED konumunda olmalý
 Yazan             : SERDAR ÇÝÇEK
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use fast_io(a) // Port yönlendirme komutlarý A portu için geçerli
#use fast_io(b) // Port yönlendirme komutlarý B portu için geçerli

#byte portb=6  // Bu komutla portb kelimesi denetleyicinin B portu kaydedicisi adresiyle eþleþtirilmiþtir

int giris;     // 8 bitlik tamsayý tipinde deðiþken tanýmlanýyor

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

   set_tris_a(0xFF);    // A portu tümüyle giriþ olarak yönlendiriliyor
   set_tris_b(0x00);    // B portu tümüyle çýkýþ olarak yönlendiriliyor

   output_b(0x00);      // B portu çýkýþlarý sýfýrlanýyor

   basla:

   giris=input_a();   // A port giriþi komple okunuyor ve okunan deðer giris deðiþkenine aktarýlýyor
   giris=giris&0b00111111;  // giris deðerinin yüksek deðerlikli son 2 biti maskeleniyor
   portb=giris;       // giris deðiþkeni deðeri B portuna çýkýþ olarak gönderiliyor

   goto basla;        // basla etiketine dallanýlýyor
}
