/******************************************************
 Uygulama Ad�      : 74138 �le Port �o�ullama Uygulamas�
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use fast_io(b) // Port y�nlendirme komutlar� b portu i�in ge�erli

int i; // Tamsay� tipinde de�i�ken tan�mlan�yor

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
   
   set_tris_b(0x00); // B portu t�m�yle ��k�� olarak y�nlendiriliyor

   while(1) // Sonsuz d�ng�
   {
      for(i=0;i<8;i++) // 1. 74138 entegresi ��k�� kontrol�
      {
         output_b(i|0b00000000); // �lk 74138 se�iliyor ve s�rayla ��k��lar aktif yap�l�yor
         delay_ms(250);          // Gecikme veriliyor
      }
      for (i=0;i<8;i++) // 2. 74138 entegresi ��k�� kontrol�
      {
         output_b(i|0b00010000); // �kinci 74138 se�iliyor ve s�rayla ��k��lar aktif yap�l�yor
         delay_ms(250);          // Gecikme veriliyor
      }
      for(i=0;i<8;i++) // 3. 74138 entegresi ��k�� kontrol�
      {
         output_b(i|0b00100000); // ���nc� 74138 se�iliyor ve s�rayla ��k��lar aktif yap�l�yor
         delay_ms(250);          // Gecikme veriliyor
      }
      for (i=0;i<8;i++) //  4. 74138 entegresi ��k�� kontrol�
      {
         output_b(i|0b00110000); // D�rd�nc� 74138 se�iliyor ve s�rayla ��k��lar aktif yap�l�yor
         delay_ms(250);          // Gecikme veriliyor
      }
   }
}

