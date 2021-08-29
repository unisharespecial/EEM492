/******************************************************
      PIC16F877 ile RS232 Seri Ýletiþim Uygulamasý
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 protokolünün 9600 bit/sn baud hýzýnda olacaðýný ve
                                                                  // TX,RX uçlarýnýn hangi pinler olacaðýný tanýmlýyor
                                                                  // parity bitinin olmadýðýný, stop bitinin 1 bit olacaðý belirtiliyor

char   klavye[80];  // klavye isminde 80 üyeli bir dizi tanýmlanýyor

#int_rda   // RX ucuna veri gelince meydane gelen kesme
void serihaberlesme_kesmesi ()
{
   disable_interrupts(int_rda); // int_rda kesmesini pasif yap
   output_high(pin_c5);  // RC5 çýkýþý lojik-1
   gets(klavye); // String ifadeyi al ve "klavye" adlý dizi deðiþkenine aktar.
   printf("\n\rYazdiginiz Metin>  %s\n",klavye); // Satýr atla, yeni satýr,RS232 üzerinden klavye string ifadesini gönder,satýr atla
   printf(lcd_putc,"\f%s",klavye);  //LCD'yi temizle ve klavye string ifadesini LCD'de göster
   output_low(pin_c5); // RC5 çýkýþý lojik-0
   printf("\n\rKlavyeden bir metin giriniz ve enter tusuna basiniz>"); // Satýr atla, yeni satýr,RS232 üzerinden belirtilen metni gönder
}

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

   output_low(pin_c5); // RC5 çýkýþý ilk anda sýfýrlanýyor
   lcd_init();   // LCD'yi hazýrla

   printf("\r**************** Merhaba *********************"); // Yeni satýr, RS232 üzerinden belirtilen metni gönder ve satýr atla.
   printf("\n\rKlavyeden girdiginiz bilgiler LCD'de gorunecektir\n\n"); // Satýr atla, yeni satýr, RS232 üzerinden belirtilen metni gönder
   printf("\n\rKlavyeden bir metin giriniz ve enter tusuna basiniz>"); // Satýr atla, yeni satýr,RS232 üzerinden belirtilen metni gönder

   enable_interrupts(GLOBAL);  // Aktif edilen tüm kesmelere izin ver

   while(1) // Sonsuz döngü
   {
      enable_interrupts(int_rda); // int_rda kesmesi aktif
   }
}
