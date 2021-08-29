/******************************************************
      PIC16F877 ile Dahili ADC Uygulamasý-2
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

#device ADC=10  // 10 bitlik ADC kullanýlacaðý belirtiliyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli
#use fast_io(e) //Port yönlendirme komutlarý E portu için geçerli

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

#INT_AD               // ADC çevrimi bitti kesmesi
void ADC_Kesmesi ( )
{
   output_high(pin_c5);  // RC5 çýkýþý 1
   delay_ms(200);
   output_low(pin_c5);   // RC5 çýkýþý 0
}

unsigned long int bilgi; // Ýþaretsiz 16 bitlik tam sayý tipinde deðiþken tanýmlanýyor
float voltaj;            // ondalýklý tipte voltaj isminde deðiþken tanýtýlýyor

//********** ANA PROGRAM FONKSÝYONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_c(0x00);  // C portu komple çýkýþ
   set_tris_e(0x0F);  // E portu komple giriþ

   output_c(0x00);    // C portu çýkýþýný sýfýrla

   setup_adc(adc_clock_div_32);   // ADC clock frekansý fosc/32
   setup_adc_ports(AN0_AN1_AN4_AN5_AN6_AN7_VREF_VREF);   //ADC giriþleri ayarlanýyor
   enable_interrupts(INT_AD);     // AD çevrimi bitti kesmesi tanýtýlýyor
   enable_interrupts(GLOBAL);     // Tüm kesmeler aktif

   lcd_init();                            // LCD hazýr hale getiriliyor

   printf(lcd_putc,"\f ADC UYGULAMASI "); // LCD'ye yazý yazdýrýlýyor
   delay_ms(1500);

   while(1)   // sonsuz döngü
   {

      set_adc_channel(5);   // RE0/AN5 ucundaki sinyal A/D iþlemine tabi tutulacak
      delay_us(20);         // Kanal seçiminde sonra bu bekleme süresi verilmelidir
      bilgi=read_adc();     // ADC sonucu okunuyor ve bilgi deðiþkenine aktarýlýyor

      voltaj=1+(0.001953125*bilgi);   // Dijitale çevirme iþlemine uðrayan sinyalin gerilimi hesaplanýyor

      printf(lcd_putc,"\fAN5 Kanali");
      delay_ms(1500);
      printf(lcd_putc,"\fDijital=%lu",bilgi); // AN5 ucundaki sinyalin dijital karþýlýðý LCD'ye aktarýlýyor
      printf(lcd_putc,"\nVoltaj=%fV",voltaj); // AN5 ucundaki sinyalin gerilim deðeri LCD'ye aktarýlýyor
      delay_ms(2500);

      set_adc_channel(6);   // RE1/AN6 ucundaki sinyal A/D iþlemine tabi tutulacak
      delay_us(20);         // Kanal seçiminde sonra bu bekleme süresi verilmelidir
      bilgi=read_adc();     // ADC sonucu okunuyor ve bilgi deðiþkenine aktarýlýyor

      voltaj=1+(0.001953125*bilgi);  // Dijitale çevirme iþlemine uðrayan sinyalin gerilimi hesaplanýyor

      printf(lcd_putc,"\fAN6 Kanali");
      delay_ms(1500);
      printf(lcd_putc,"\fDijital=%lu",bilgi);  // AN6 ucundaki sinyalin dijital karþýlýðý LCD'ye aktarýlýyor
      printf(lcd_putc,"\nVoltaj=%fV",voltaj);  // AN6 ucundaki sinyalin gerilim deðeri LCD'ye aktarýlýyor
      delay_ms(2500);

      set_adc_channel(7);   // RE2/AN7 ucundaki sinyal A/D iþlemine tabi tutulacak
      delay_us(20);         // Kanal seçiminde sonra bu bekleme süresi verilmelidir
      bilgi=read_adc();     // ADC sonucu okunuyor ve bilgi deðiþkenine aktarýlýyor

      voltaj=1+(0.001953125*bilgi);  // Dijitale çevirme iþlemine uðrayan sinyalin gerilimi hesaplanýyor

      printf(lcd_putc,"\fAN7 Kanali");
      delay_ms(1500);
      printf(lcd_putc,"\fDijital=%lu",bilgi);  // AN7 ucundaki sinyalin dijital karþýlýðý LCD'ye aktarýlýyor
      printf(lcd_putc,"\nVoltaj=%fV",voltaj);  // AN7 ucundaki sinyalin gerilim deðeri LCD'ye aktarýlýyor
      delay_ms(2500);
   }
}

