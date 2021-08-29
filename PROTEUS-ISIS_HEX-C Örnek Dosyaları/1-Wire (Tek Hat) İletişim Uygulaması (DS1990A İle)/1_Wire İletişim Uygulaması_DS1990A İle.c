/******************************************************
      PIC16F877 ile 1-Wire (Tek Hat) Ýletiþim Uygulamasý (DS1990A Ýle)
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#include <1_wire.c>  // 1-Wire iletiþim fonksiyonlarýnýn kaydedildiði dosya programa ekleniyor

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

int1 sonuc; // 1 bitlik deðiþken tanýmlanýyor
int8 seri_no1=0,seri_no2=0,seri_no3=0,seri_no4=0,seri_no5=0,seri_no6=0,seri_no7=0,seri_no8=0; // 8 bitlik deðiþkenler tanýmlanýyor
int32 seri_no=0; // 32 bitlik deðiþken tanýmlanýyor

//********** ANA PROGRAM FONKSÝYONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   lcd_init();   // LCD hazýrlanýyor

   ow_hiz(1);   // 1-Wire iletiþim hýzý standart seçildi

   while(1) // Sonsuz döngü
   {
      sonuc=ow_reset();  // 1-Wire cihazýna reset sinyalini gönder

      if (sonuc==0)  // Eðer data hattýnda 1-wire cihazý var ve saðlam ise
      {
         printf(lcd_putc,"\fCihaz calisiyor"); // LCD'ye veri gönderiliyor.
         delay_ms(1500); // 1.5 sn gecikme veriliyor

         ow_yaz_byte(0x33); //ROM numarasý okuma komutu cihaza gönderiliyor

         seri_no1=ow_oku_byte(); // ROM numarasýnýn ilk byte deðeri aile (family) kodu'dur.
         seri_no2=ow_oku_byte(); // ROM numarasýnýn 2. byte ile 7.byte deðerleri
         seri_no3=ow_oku_byte();    // cihazýn 48 bitlik seri nosunu oluþturur
         seri_no4=ow_oku_byte();
         seri_no5=ow_oku_byte();
         seri_no6=ow_oku_byte();
         seri_no7=ow_oku_byte();
         seri_no8=ow_oku_byte(); // ROM numarasýnýn 8. byte deðeri cihazýn CRC deðeridir

         seri_no=make32(seri_no2,seri_no3,seri_no4,seri_no5); // 8 bitlik deðerleri birleþtirerek 32 bitlik deðer oluþturur

         printf(lcd_putc,"\fCihaz Aile Kodu"); // LCD'ye veri gönderiliyor.
         printf(lcd_putc,"\n%X",seri_no1); // Cihaz aile kodu LCD'ye gönderiliyor
         delay_ms(2000); // 2 sn gecikme veriliyor
         printf(lcd_putc,"\fCihaz Seri No"); // LCD'ye veri gönderiliyor.
         printf(lcd_putc,"\n%X%X%X%X%X%X",seri_no2,seri_no3,seri_no4,seri_no5,seri_no6,seri_no7); // Cihaz seri no LCD'ye gönderiliyor
         delay_ms(2000); // 2 sn gecikme veriliyor
         printf(lcd_putc,"\fCihaz CRC Degeri"); // LCD'ye veri gönderiliyor.
         printf(lcd_putc,"\n%X",seri_no8); // Cihazýn CRC deðeri LCD'ye gönderiliyor
         delay_ms(2000); // 2 sn gecikme veriliyor

         if (seri_no==0x2CC5B800) // Eðer doðru cihaz sistemdeyse
            output_high(pin_c1);  // RC1 pinine baðlý role çeker
      }
      else  // Eðer data hattýnda 1-wire cihazý yok veya saðlam deðilse
         printf(lcd_putc,"\fCihaz calismiyor");
      delay_ms(1500);  // 1.5 sn gecikme veriliyor
   }
}
