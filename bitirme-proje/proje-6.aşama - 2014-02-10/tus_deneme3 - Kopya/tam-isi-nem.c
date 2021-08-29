#include <18F452.h> 
#device adc=8

#use delay(clock=4000000)

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


#include "SHT11.c"
#include "new_lcd.c"

//3x4 tu� tak�m�
#define sat1   pin_c0 
#define sat2   pin_c1 
#define sat3   pin_c2

#define sat4   pin_c3 
#define sut1   pin_c4
#define sut2   pin_c5 
#define sut3   pin_c6 

// �s�t�c� ve so�utucu
#define isitici   pin_b0 
#define sogutucu  pin_b1

//sht11 alg�lay�c�            
#define sht_data_pin   PIN_b7//(Data pin veya input)
#define sht_clk_pin    PIN_b6

float temp=0,humid=0,sicaklik=0,nem=0;
int i=1, negatif=0, flag=0, derece=25, tus=99, pres = 99;
                    
//fonksiyonlar
int keypad_oku() // Fonksiyon ismi
{   
output_c(0x00); // D portu ��k��� s�f�rlan�yor

   output_high(sat1); 
      if (input(sut1))  
         { delay_ms(20); tus=1;output_low(sat1);}
      else if (input(sut2))   
         { delay_ms(20); tus=2;output_low(sat1);}
      else if (input(sut3))
         { delay_ms(20); tus=3;output_low(sat1);}
      else
        output_low(sat1);
   
   output_high(sat2);
      if (input(sut1))  
         { delay_ms(20); tus=4;output_low(sat2);}
      else if (input(sut2)) 
         { delay_ms(20); tus=5;output_low(sat2);}
      else if (input(sut3))  
         { delay_ms(20); tus=6;output_low(sat2);}
      else
        output_low(sat2); 

    output_high(sat3); 
      if (input(sut1))   
         { delay_ms(20); tus=7;output_low(sat3);}
      else if (input(sut2)) 
         { delay_ms(20); tus=8;output_low(sat3);}
      else if (input(sut3))  
         { delay_ms(20); tus=9;output_low(sat3);}
      else
        output_low(sat3); 
   
  output_high(sat4);
      if (input(sut1))  
         { delay_ms(20); tus=10;output_low(sat4);}
      else if (input(sut2))   
         { delay_ms(20); tus=0;output_low(sat4);}
      else if (input(sut3)) 
         { delay_ms(20); tus=19;output_low(sat4);}
      else
        output_low(sat4);

   return tus; 
}

void allkeypadlow()
{
   output_low(sat1);
   output_low(sat2);
   output_low(sat3);
   output_low(sat4);
   output_low(sut1);
   output_low(sut2);
   output_low(sut3);
   tus=99;
}


// ana program
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
 
 
   set_tris_a(0x00);   // A portu komple ��k��
   set_tris_b(0x00);
   set_tris_c(0x0f);   
   set_tris_d(0x00);   

   lcd_init();   // LCD haz�rlan�yor

   while(1)
   {                        
      allkeypadlow();
      keypad_oku();
      pres = tus;
      allkeypadlow();
      
      if(pres == 10)
      {
          flag = 1;             
        output_high(sogutucu);   
          printf(lcd_putc,"yildiz");
          delay_ms(2000);
      }
      else if(pres == 19)
      {
          flag = 1;             
       output_high(sogutucu);   
          printf(lcd_putc,"kare");  
          delay_ms(2000);
      }    
      
      else if(pres == 1)
      {
          flag = 1;         
       output_high(sogutucu);       
          printf(lcd_putc,"basilan 1");  
          delay_ms(2000);
      }    
      else if(pres == 2)
      {
          flag = 1;    
       output_high(sogutucu);            
          printf(lcd_putc,"basilan 2");    
          delay_ms(2000);
      }    
      else if(pres == 3)
      {
          flag = 1;     
       output_high(sogutucu);           
          printf(lcd_putc,"basilan 3");    
          delay_ms(2000);
      }    
      else if(pres == 4)
      {
          flag = 1;          
       output_high(sogutucu);      
          printf(lcd_putc,"basilan 4");   
          delay_ms(2000);
      }    
      else if(pres == 5)
      {
          flag = 1;          
       output_high(sogutucu);      
          printf(lcd_putc,"basilan 5"); 
          delay_ms(2000);
      }    
      else if(pres == 6)
      {
          flag = 1;             
       output_high(sogutucu);   
          printf(lcd_putc,"basilan 6");  
          delay_ms(2000);
      }    
      else if(pres == 7)
      {
          flag = 1;            
       output_high(sogutucu);    
          printf(lcd_putc,"basilan 7");  
          delay_ms(2000);
      }
      else if(pres == 8)
      {
          flag = 1;         
       output_high(sogutucu);       
          printf(lcd_putc,"basilan 8");  
          delay_ms(2000);
      }    
      else if(pres == 9)
      {
          flag = 1;             
       output_high(sogutucu);   
          printf(lcd_putc,"basilan 9");
          delay_ms(2000);
      }    
      else if(pres == 0)
      {
          flag = 1;      
       output_high(sogutucu);          
          printf(lcd_putc,"basilan 0");   
          delay_ms(2000);
      }    
      else
      {
      
          printf(lcd_putc,"\f");
          printf(lcd_putc,"deneme tus");    
          delay_ms(1000);       
      }            
          printf(lcd_putc,"\f");  
      
   }

}


