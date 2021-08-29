#include <18F452.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES XT                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOOSCSEN                 //Oscillator switching is disabled, main oscillator is source
#FUSES NOBROWNOUT               //No brownout reset
#FUSES BORV20                   //Brownout reset at 2.0V
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOSTVREN                 //Stack full/underflow will not cause reset
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOWRTD                   //Data EEPROM not write protected
#FUSES NOWRTB                   //Boot block not write protected
#FUSES NOWRTC                   //configuration not registers write protected
#FUSES NOCPD                    //No EE protection
#FUSES NOCPB                    //No Boot Block code protection
#FUSES NOEBTR                   //Memory not protected from table reads
#FUSES NOEBTRB                  //Boot block not protected from table reads

#use delay(clock=4000000)

#include "SHT11.c"
#include "new_lcd.c"


//3x4 tuş takımı
#define sut1   pin_A0 
#define sut2   pin_A1 
#define sut3   pin_A2

#define sat1   pin_B0 
#define sat2   pin_B1
#define sat3   pin_B2 
#define sat4   pin_B3 

// ısıtıcı ve soğutucu
#define isitici   pin_C0 
#define sogutucu  pin_C1

//sht11 algılayıcı            
#define sht_data_pin   PIN_B7//(Data pin veya input)
#define sht_clk_pin    PIN_B6


float temp=0,humid=0,sicaklik=0,nem=0;
char tus=0; // karakter tipinde değişken tanımlanıyor
int katsayi=1,flag=0,a=0,b=0,derece=25;

char keypad_oku() // Fonksiyon ismi
{
   output_d(0x00); // D portu çıkışı sıfırlanıyor

   output_high(sat1); // 1. satır lojik-1 yapılıyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=1; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=2; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=3; }
   output_low(sat1); // 1. satır lojik-0 yapılıyor

   output_high(sat2); // 2. satır lojik-1 yapılıyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=4; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=5; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=6; }
   output_low(sat2); // 2. satır lojik-0 yapılıyor

   output_high(sat3); // 3. satır lojik-1 yapılıyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=7; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=8; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=9; }
   output_low(sat3); // 3. satır lojik-0 yapılıyor

   output_high(sat4); // 3. satır lojik-1 yapılıyor
   if (input(sut1))   // 1. sütun okunuyor
      { delay_ms(20); tus=0xE; }
   if (input(sut2))   // 2. sütun okunuyor
      { delay_ms(20); tus=0; }
   if (input(sut3))   // 3. sütun okunuyor
      { delay_ms(20); tus=0xF; }
   output_low(sat4); // 3. satır lojik-0 yapılıyor

   return tus; // Fonksiyon "tus" değeri ile geri döner
}

//********** ANA PROGRAM FONKSİYONU*******

int ChartoInt(char asd)
{
  switch(asd)
  {
  case '0' : return 0;break;
  case '1' : return 1;break;
  case '2' : return 2;break;
  case '3' : return 3;break;
  case '4' : return 4;break;
  case '5' : return 5;break;
  case '6' : return 6;break;
  case '7' : return 7;break;
  case '8' : return 8;break;
  case '9' : return 9;break;
  }
}

void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   

   lcd_init();
   delay_ms(100);
   sht_init();
   delay_ms(100);
 
 
   set_tris_a(0x00);   // A portu komple çıkış
   set_tris_b(0x00);  
   set_tris_c(0x0F);   
   set_tris_d(0x0F);   

   lcd_init();   // LCD hazırlanıyor
 
 
   while(1)
   {
      
      if(flag == 1)
      {
        lcd_gotoxy(1,1);
        printf(lcd_putc,"\fSicaklik Giriniz");
        delay(2000);
        lcd_gotoxy(2,2);
        if(keypad_oku() != 0xF && keypad_oku() != 0xE)   
        {
          a = ChartoInt(keypad_oku());
          printf(lcd_putc,"%d",a);
          lcd_gotoxy(3,2);
          delay(2000);
          if(keypad_oku() != 0xF || keypad_oku() != 0xE)
          {
            b = ChartoInt(keypad_oku());            
            printf(lcd_putc,"%d",b);
            delay(1000);
            derece = (a*10 + b) * katsayi;
            lcd_clear();
            lcd_gotoxy(3,1);
            printf(lcd_putc,"%d derece",derece);
            lcd_gotoxy(3,2);          
            printf(lcd_putc,"ayarlandı.");
            flag=0;
          }
          else
          { 
            derece = a * katsayi;
            delay(1000);           
            lcd_clear();
            lcd_gotoxy(3,1);
            printf(lcd_putc,"%d derece",derece);
            lcd_gotoxy(3,2);          
            printf(lcd_putc,"ayarlandı.");
            flag=0;
          }
             
        }
        else
        {
          lcd_clear();
          lcd_gotoxy(3,1);
          printf(lcd_putc,"%d derece",derece);
          lcd_gotoxy(3,2);          
          printf(lcd_putc,"ayarlandı.");
          flag=0;
        }    
      }
      else
      {
        sht_rd (temp, humid);
        sicaklik=(unsigned int)temp;
        nem=(unsigned int)humid;
        lcd_gotoxy(1,1);
        printf(lcd_putc,"SICAKLIK %1.3f ",sicaklik);
        lcd_gotoxy(1,2);
        printf(lcd_putc,"NEM %1.3f ",nem);
        delay_ms(200);
        if(keypadoku() == 0xE)
          flag = 1;
      }
      
      if(derece == sicaklik-2 || derece == sicaklik+2)
      {
        isitici=0;
        sogutucu=0;
      }  
      else if(derece > sicaklik)
      {
        isitici=1;
        sogutucu=0;     
      }
      else
      {
        isitici=0;
        sogutucu=1;      
      }

   }

}

