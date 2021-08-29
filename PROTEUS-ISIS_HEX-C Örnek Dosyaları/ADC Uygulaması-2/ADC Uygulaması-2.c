/******************************************************
      PIC16F877 ile Dahili ADC Uygulamas�-2
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#device ADC=10  // 10 bitlik ADC kullan�laca�� belirtiliyor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use fast_io(c) //Port y�nlendirme komutlar� C portu i�in ge�erli
#use fast_io(e) //Port y�nlendirme komutlar� E portu i�in ge�erli

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

#INT_AD               // ADC �evrimi bitti kesmesi
void ADC_Kesmesi ( )
{
   output_high(pin_c5);  // RC5 ��k��� 1
   delay_ms(200);
   output_low(pin_c5);   // RC5 ��k��� 0
}

unsigned long int bilgi; // ��aretsiz 16 bitlik tam say� tipinde de�i�ken tan�mlan�yor
float voltaj;            // ondal�kl� tipte voltaj isminde de�i�ken tan�t�l�yor

//********** ANA PROGRAM FONKS�YONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_c(0x00);  // C portu komple ��k��
   set_tris_e(0x0F);  // E portu komple giri�

   output_c(0x00);    // C portu ��k���n� s�f�rla

   setup_adc(adc_clock_div_32);   // ADC clock frekans� fosc/32
   setup_adc_ports(AN0_AN1_AN4_AN5_AN6_AN7_VREF_VREF);   //ADC giri�leri ayarlan�yor
   enable_interrupts(INT_AD);     // AD �evrimi bitti kesmesi tan�t�l�yor
   enable_interrupts(GLOBAL);     // T�m kesmeler aktif

   lcd_init();                            // LCD haz�r hale getiriliyor

   printf(lcd_putc,"\f ADC UYGULAMASI "); // LCD'ye yaz� yazd�r�l�yor
   delay_ms(1500);

   while(1)   // sonsuz d�ng�
   {

      set_adc_channel(5);   // RE0/AN5 ucundaki sinyal A/D i�lemine tabi tutulacak
      delay_us(20);         // Kanal se�iminde sonra bu bekleme s�resi verilmelidir
      bilgi=read_adc();     // ADC sonucu okunuyor ve bilgi de�i�kenine aktar�l�yor

      voltaj=1+(0.001953125*bilgi);   // Dijitale �evirme i�lemine u�rayan sinyalin gerilimi hesaplan�yor

      printf(lcd_putc,"\fAN5 Kanali");
      delay_ms(1500);
      printf(lcd_putc,"\fDijital=%lu",bilgi); // AN5 ucundaki sinyalin dijital kar��l��� LCD'ye aktar�l�yor
      printf(lcd_putc,"\nVoltaj=%fV",voltaj); // AN5 ucundaki sinyalin gerilim de�eri LCD'ye aktar�l�yor
      delay_ms(2500);

      set_adc_channel(6);   // RE1/AN6 ucundaki sinyal A/D i�lemine tabi tutulacak
      delay_us(20);         // Kanal se�iminde sonra bu bekleme s�resi verilmelidir
      bilgi=read_adc();     // ADC sonucu okunuyor ve bilgi de�i�kenine aktar�l�yor

      voltaj=1+(0.001953125*bilgi);  // Dijitale �evirme i�lemine u�rayan sinyalin gerilimi hesaplan�yor

      printf(lcd_putc,"\fAN6 Kanali");
      delay_ms(1500);
      printf(lcd_putc,"\fDijital=%lu",bilgi);  // AN6 ucundaki sinyalin dijital kar��l��� LCD'ye aktar�l�yor
      printf(lcd_putc,"\nVoltaj=%fV",voltaj);  // AN6 ucundaki sinyalin gerilim de�eri LCD'ye aktar�l�yor
      delay_ms(2500);

      set_adc_channel(7);   // RE2/AN7 ucundaki sinyal A/D i�lemine tabi tutulacak
      delay_us(20);         // Kanal se�iminde sonra bu bekleme s�resi verilmelidir
      bilgi=read_adc();     // ADC sonucu okunuyor ve bilgi de�i�kenine aktar�l�yor

      voltaj=1+(0.001953125*bilgi);  // Dijitale �evirme i�lemine u�rayan sinyalin gerilimi hesaplan�yor

      printf(lcd_putc,"\fAN7 Kanali");
      delay_ms(1500);
      printf(lcd_putc,"\fDijital=%lu",bilgi);  // AN7 ucundaki sinyalin dijital kar��l��� LCD'ye aktar�l�yor
      printf(lcd_putc,"\nVoltaj=%fV",voltaj);  // AN7 ucundaki sinyalin gerilim de�eri LCD'ye aktar�l�yor
      delay_ms(2500);
   }
}

