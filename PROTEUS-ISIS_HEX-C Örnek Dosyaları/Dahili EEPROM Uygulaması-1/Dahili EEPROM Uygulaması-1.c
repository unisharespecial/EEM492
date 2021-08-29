/*****************************************************************
      PIC16F877 ile Dahili EEPROM Uygulamas�-1 (Haf�zal� Kronometre)
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
******************************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(a) //Port y�nlendirme komutlar� A portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c> // LCD.c dosyas� programa ekleniyor

int8 _10ms=0;           // Tam say� tipinde de�i�ken tan�mlan�yor
unsigned int8 saniye=0; // ��aretsiz tam say� tipinde de�i�ken tan�mlan�yor

//****************** Timer0 Kesmesi *****************************
#int_timer0  // Timer0 kesmesi. Her 10 msn'de bir kesme olu�ur.
void  timer0_kesme ()   // Kesme fonksiyonu ismi
{
    set_timer0(217); // TMR0 de�eri belirleniyor

    _10ms++;        // _10ms de�i�keni de�erini 1 artt�r
       
    if (_10ms==100) // _10ms de�eri 100 olunca (Ge�en s�re 1 saniye olunca)
    {
       _10ms=0;    // _10ms de�i�kenini s�f�rla
       saniye++;   // saniye de�i�kenini bir artt�r
       if (saniye==255) // E�er saniye de�i�keni 999 olursa s�f�rla
          saniye=0; // saniye de�i�kenini s�f�rla
    }
}

/********* ANA PROGRAM FONKS�YONU********/
void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0x0F);   // RA0, RA1, RA2, RA3 pinleri giri�

   lcd_init();         // LCD kurulumu yap�l�yor

   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); // Timer0 ayarlar� yap�l�yor
   set_timer0(217);   // TMR0 de�eri belirleniyor
   
   lcd_gotoxy(1,1); // �mle� 1.s�tun, 1. sat�rda
   printf(lcd_putc,"Sure=%03u.%02d",saniye,_10ms); // Saniye ve milisaniye LCD'ye yazd�r�l�yor
   lcd_gotoxy(1,2); // �mle� 1.s�tun, 2. sat�rda
   printf(lcd_putc,"Sonuc=%03u.%02d",read_eeprom(0),read_eeprom(1)); // EEPROM'da saklanan saniye ve milisaniye de�erleri LCD'ye yazd�r�l�yor

   while(1)
   {
      if(input(pin_a3))  // SIFIRLA butonuna bas�ld� ise
      {
         saniye=_10ms=0;
         write_eeprom(0,saniye);  // 0 (0x00) adresine saniye de�erini yaz
         write_eeprom(1,_10ms);   // 1 (0x01) adresine milisaniye de�erini yaz
         lcd_gotoxy(1,1); // �mle� 1.s�tun, 1. sat�rda
         printf(lcd_putc,"Sure=%03u.%02d",saniye,_10ms); // S�f�rlanan s�re LCD'ye yazd�r�l�yor
         lcd_gotoxy(1,2); // �mle� 1.s�tun, 2. sat�rda
         printf(lcd_putc,"Sonuc=%03u.%02d",saniye,_10ms);// S�f�rlanan kay�tl� s�re LCD'ye yazd�r�l�yor
         while(input(pin_a3)); // Butondan el �ekilene kadar bekle
      }
 
      if(input(pin_a0)) // BA�LA butonuna bas�ld� ise
      {
         while(!input(pin_a2)) // DUR butonuna bas�lana kadar d�ng� d�ns�n
         {
            enable_interrupts(INT_timer0); // int_timer0 kesmesini aktif yapar
            enable_interrupts(GLOBAL);     // Aktif edilen kesmelere izin ver

            lcd_gotoxy(1,1); // �mle� 1.s�tun, 1. sat�rda
            printf(lcd_putc,"Sure=%03u.%02d",saniye,_10ms); // S�re LCD'ye yazd�r�l�yor
            lcd_gotoxy(1,2); // �mle� 1.s�tun, 2. sat�rda
            printf(lcd_putc,"Sonuc=%03u.%02d",read_eeprom(0),read_eeprom(1)); // EEPROM'da saklanan saniye ve milisaniye de�erleri LCD'ye yazd�r�l�yor


            if (input(pin_a1))  // YAKALA butonuna bas�lm��sa
            {
             write_eeprom(0,saniye);  // 0 (0x00) adresine saniye de�erini yaz
             write_eeprom(1,_10ms);   // 1 (0x01) adresine milisaniye de�erini yaz
             lcd_gotoxy(7,2);         // �mle� 7.s�tun, 2. sat�rda
             printf(lcd_putc,"%03u.%02d",read_eeprom(0),read_eeprom(1));  // LCD'de yakalanan zaman� g�ster
             while(input(pin_a1));     // Butondan elimizi �ekene kadar bekle
            }
            
            lcd_gotoxy(6,1);                // �mle� 6.s�tun, 1. sat�rda
            printf(lcd_putc,"%03u.%02d",saniye,_10ms); // Ge�en zaman� LCD'de g�ster     
         }
         disable_interrupts(GLOBAL); // T�m kesmeleri pasif yap.
     }
  }
}

