#include "C:\Users\AKIN\Desktop\bitirme-proje\Sadik_carsamba\dden7.h"
#use delay(clock=20M)
#fuses HS,NOWDT,NOPROTECT
#define dht11 PIN_B0
#include "flex_lcd.c"

char dht_dat[10]; // Output data will be here

void dht_init()

{
    delay_ms (1);
    output_high(dht11);
}
int leer_dht_dat()

{
    int i = 0;
    int result = 0;

    for (i = 0; i < 8; i++)
    {
        while (input (dht11) == 0);

        delay_us(30);

        if (input (dht11) == 1)
        {
            result |= (1 << (7 - i) );
        }

        while (input (dht11) == 1);
    }

    return result;
}

void read_dht()
{
    int GlobalErr = 0;
    int dht_in;
    int i;
    int dht_check_sum;
    dht_init();
    output_low(dht11);
    delay_ms(18);
    output_high(dht11);
    delay_us(30);
    dht_in = input(dht11);

    if (dht_in)
    {
        GlobalErr = 1;
        return;
    }

    delay_us(80);
    dht_in = input(dht11);

    if (!dht_in)
    {
        GlobalErr = 2;
        return;
    }

    delay_us(80);

    for (i = 0; i < 4; i++)
    {
        dht_dat[i] = leer_dht_dat();
    }

    output_high(dht11);
}




void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init();
   delay_ms(100);
   dht_init();
   int dht11_check_sum;
   while(1)
   {
      read_dht(); // Check dht_dat variable after this funciton
      dht11_check_sum = (dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3]) & 0xFF;// check check_sum
      if(dht_dat[4]!= dht11_check_sum)
      {
         printf(lcd_putc, "DHT11 checksum error");
      }
      else
      {
         printf(lcd_putc,"\fHUMI RH :%d.%d %%  ",dht_dat[0],dht_dat[1]);
         printf(lcd_putc,"\nTEMP :%d.%d %cC  ",dht_dat[2],dht_dat[3],223);
      }
      delay_ms(2000);
   }

}



