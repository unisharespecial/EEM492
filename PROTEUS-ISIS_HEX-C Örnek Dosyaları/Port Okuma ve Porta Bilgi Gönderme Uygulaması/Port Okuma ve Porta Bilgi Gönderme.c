/******************************************************
 Uygulama Ad�      : Port Okuma ve Porta Bilgi G�nderme
 Program�n Amac�   : A portu RA0,RA1,RA2 ve RA3 pinlerine ba�l� butonlar�n durumunun
                     okunarak, okunan bu bilginin B portuna ba�l� LED'lerde g�sterilmesi
 PIC PROG/DEKA     : Port B jumper'� LED konumunda olmal�
 Yazan             : SERDAR ���EK
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use fast_io(a) // Port y�nlendirme komutlar� A portu i�in ge�erli
#use fast_io(b) // Port y�nlendirme komutlar� B portu i�in ge�erli

#byte portb=6  // Bu komutla portb kelimesi denetleyicinin B portu kaydedicisi adresiyle e�le�tirilmi�tir

int giris;     // 8 bitlik tamsay� tipinde de�i�ken tan�mlan�yor

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

   set_tris_a(0xFF);    // A portu t�m�yle giri� olarak y�nlendiriliyor
   set_tris_b(0x00);    // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   output_b(0x00);      // B portu ��k��lar� s�f�rlan�yor

   basla:

   giris=input_a();   // A port giri�i komple okunuyor ve okunan de�er giris de�i�kenine aktar�l�yor
   giris=giris&0b00111111;  // giris de�erinin y�ksek de�erlikli son 2 biti maskeleniyor
   portb=giris;       // giris de�i�keni de�eri B portuna ��k�� olarak g�nderiliyor

   goto basla;        // basla etiketine dallan�l�yor
}
