/******************************************************
 Uygulama Ad�     : Buton ile Led Kontrol Uygulamas�
 Program�n Amac�  : Bu program ile B0 portuna ba�l� LED, RA0 giri�ine ba�l� buton ile kontrol edilmektedir.
 PIC PROG/DEKA    : Port B jumper'� LED konumunda olmal�
 Yazan            : SERDAR ���EK
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use fast_io(a) // Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(b) // Port y�nlendirme komutlar� B portu i�in ge�erli

int1 x; // 1 bitlik x ad�nda tamsay� tipinde bir de�i�ken tan�mlan�yor.

/********* ANA PROGRAM FONKS�YONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   set_tris_a(0b00000001);    // RA0 ucu giri� olarak ayarland�.
   set_tris_b(0x00);    // RB0 portu t�m�yle ��k�� olarak ayarland�.
   
   output_b(0x00);

   basla:
   x=input(pin_a0);      // RA0 giri�i okunuyor, tersleniyor ve x de�i�kenine aktar�l�yor.
   output_bit(pin_b0,x);  // x de�i�keni de�eri RB0 pini ��k���na aktar�l�yor.
   goto basla;            // basla etiketinin oldu�u yere gidilir.
}

