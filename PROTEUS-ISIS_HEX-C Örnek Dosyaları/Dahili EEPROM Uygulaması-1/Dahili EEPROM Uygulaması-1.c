/*****************************************************************
      PIC16F877 ile Dahili EEPROM Uygulamasý-1 (Hafýzalý Kronometre)
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
******************************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlarý A portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c> // LCD.c dosyasý programa ekleniyor

int8 _10ms=0;           // Tam sayý tipinde deðiþken tanýmlanýyor
unsigned int8 saniye=0; // Ýþaretsiz tam sayý tipinde deðiþken tanýmlanýyor

//****************** Timer0 Kesmesi *****************************
#int_timer0  // Timer0 kesmesi. Her 10 msn'de bir kesme oluþur.
void  timer0_kesme ()   // Kesme fonksiyonu ismi
{
    set_timer0(217); // TMR0 deðeri belirleniyor

    _10ms++;        // _10ms deðiþkeni deðerini 1 arttýr
       
    if (_10ms==100) // _10ms deðeri 100 olunca (Geçen süre 1 saniye olunca)
    {
       _10ms=0;    // _10ms deðiþkenini sýfýrla
       saniye++;   // saniye deðiþkenini bir arttýr
       if (saniye==255) // Eðer saniye deðiþkeni 999 olursa sýfýrla
          saniye=0; // saniye deðiþkenini sýfýrla
    }
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

   set_tris_a(0x0F);   // RA0, RA1, RA2, RA3 pinleri giriþ

   lcd_init();         // LCD kurulumu yapýlýyor

   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); // Timer0 ayarlarý yapýlýyor
   set_timer0(217);   // TMR0 deðeri belirleniyor
   
   lcd_gotoxy(1,1); // Ýmleç 1.sütun, 1. satýrda
   printf(lcd_putc,"Sure=%03u.%02d",saniye,_10ms); // Saniye ve milisaniye LCD'ye yazdýrýlýyor
   lcd_gotoxy(1,2); // Ýmleç 1.sütun, 2. satýrda
   printf(lcd_putc,"Sonuc=%03u.%02d",read_eeprom(0),read_eeprom(1)); // EEPROM'da saklanan saniye ve milisaniye deðerleri LCD'ye yazdýrýlýyor

   while(1)
   {
      if(input(pin_a3))  // SIFIRLA butonuna basýldý ise
      {
         saniye=_10ms=0;
         write_eeprom(0,saniye);  // 0 (0x00) adresine saniye deðerini yaz
         write_eeprom(1,_10ms);   // 1 (0x01) adresine milisaniye deðerini yaz
         lcd_gotoxy(1,1); // Ýmleç 1.sütun, 1. satýrda
         printf(lcd_putc,"Sure=%03u.%02d",saniye,_10ms); // Sýfýrlanan süre LCD'ye yazdýrýlýyor
         lcd_gotoxy(1,2); // Ýmleç 1.sütun, 2. satýrda
         printf(lcd_putc,"Sonuc=%03u.%02d",saniye,_10ms);// Sýfýrlanan kayýtlý süre LCD'ye yazdýrýlýyor
         while(input(pin_a3)); // Butondan el çekilene kadar bekle
      }
 
      if(input(pin_a0)) // BAÞLA butonuna basýldý ise
      {
         while(!input(pin_a2)) // DUR butonuna basýlana kadar döngü dönsün
         {
            enable_interrupts(INT_timer0); // int_timer0 kesmesini aktif yapar
            enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

            lcd_gotoxy(1,1); // Ýmleç 1.sütun, 1. satýrda
            printf(lcd_putc,"Sure=%03u.%02d",saniye,_10ms); // Süre LCD'ye yazdýrýlýyor
            lcd_gotoxy(1,2); // Ýmleç 1.sütun, 2. satýrda
            printf(lcd_putc,"Sonuc=%03u.%02d",read_eeprom(0),read_eeprom(1)); // EEPROM'da saklanan saniye ve milisaniye deðerleri LCD'ye yazdýrýlýyor


            if (input(pin_a1))  // YAKALA butonuna basýlmýþsa
            {
             write_eeprom(0,saniye);  // 0 (0x00) adresine saniye deðerini yaz
             write_eeprom(1,_10ms);   // 1 (0x01) adresine milisaniye deðerini yaz
             lcd_gotoxy(7,2);         // Ýmleç 7.sütun, 2. satýrda
             printf(lcd_putc,"%03u.%02d",read_eeprom(0),read_eeprom(1));  // LCD'de yakalanan zamaný göster
             while(input(pin_a1));     // Butondan elimizi çekene kadar bekle
            }
            
            lcd_gotoxy(6,1);                // Ýmleç 6.sütun, 1. satýrda
            printf(lcd_putc,"%03u.%02d",saniye,_10ms); // Geçen zamaný LCD'de göster     
         }
         disable_interrupts(GLOBAL); // Tüm kesmeleri pasif yap.
     }
  }
}

