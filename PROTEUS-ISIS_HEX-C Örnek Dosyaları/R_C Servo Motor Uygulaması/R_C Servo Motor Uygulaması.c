/******************************************************
      PIC16F877 �le R/C Servo Motor Uygulamas�
******************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses HS,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=20000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

// R/C Servo motor d�nme a�� de�erleri
const int8 servo_derece_1[]={8,9,10,11,12,13,14,15,16,17,18};
const int8 servo_derece_2[]={18,17,16,15,14,13,12,11,10,9,8};
const int8 servo_derece_3[]={8,12,18,8,12,18,8,12,18,8,12};

int i=0,pwm=0,duty_0=0,duty_1=0,duty_2=0;
int16 zaman=0; // 16 bitlik de�i�ken tan�mlan�yor

#int_timer0  // Timer0 ta�ma kesmesi
void kesme ()
{
   set_timer0(113);  // TMR0 kaydedicisine 113 de�eri y�kleniyor
   if (pwm==0)       // E�er PWM de�i�keni 0 ise
   {
      output_high(pin_b0); // RB0 ��k��� lojik-1
      output_high(pin_b1); // RB1 ��k��� lojik-1
      output_high(pin_b2); // RB2 ��k��� lojik-1
   }

   if (pwm>=duty_0) output_low(pin_b0);
   if (pwm>=duty_1) output_low(pin_b1);
   if (pwm>=duty_2) output_low(pin_b2);

   zaman++; // zaman de�i�kenini 1 artt�r

   // Servo motor d�n�� ad�mlar� aras� bekleme s�resi i�in
   if (zaman>17350) // 17350x114,4�sn=1.984.840�sn, yakla��k 2msn
   {
      zaman=0;  // zaman de�i�kenini s�f�rla
      i++;      // i de�i�keni de�erini 1 artt�r
      if(i==11) // E�er i de�eri 11 ise-T�m ad�mlar bitti ise
         i=0;   // i de�i�kenini s�f�rla
   }

   pwm++;       // pwm de�i�kenini 1 artt�r
   if (pwm>=173) // pwm de�eri 173'den b�y�k ise
      pwm=0;    // pwm de�i�kenini s�f�rla
}

/********* ANA PROGRAM FONKS�YONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���


   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_4); // Timer0 ayarlar� belirtiliyor
   set_timer0(113);  // TMR0 kaydedicisine 113 de�eri y�kleniyor

   enable_interrupts(int_timer0); // Timer0 ta�ma kesmesi aktif
   enable_interrupts(global);     // Aktif edilen t�m kesmelere izin ver

   output_b(0x00);  // �lk anda B portu ��k��� s�f�rlan�yor

   while(1)  // Sonsuz d�ng�
   {
      duty_0=servo_derece_1[i]; // 1. R/C servo PWM g�rev sayk�l�
      duty_1=servo_derece_2[i]; // 2. R/C servo PWM g�rev sayk�l�
      duty_2=servo_derece_3[i]; // 3. R/C servo PWM g�rev sayk�l�
   }
}
