/******************************************************
      PIC16F877 ile 1-Wire (Tek Hat) �leti�im Uygulamas� (DS1990A �le)
PIC PROG/DEKA     : Port B jumper'� LCD konumunda olmal�
*******************************************************/

#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

// Denetleyici konfig�rasyon ayarlar�
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#include <1_wire.c>  // 1-Wire ileti�im fonksiyonlar�n�n kaydedildi�i dosya programa ekleniyor

#define use_portb_lcd TRUE   // LCD B portuna ba�l�

#include <lcd.c>   // lcd.c dosyas� tan�t�l�yor

int1 sonuc; // 1 bitlik de�i�ken tan�mlan�yor
int8 seri_no1=0,seri_no2=0,seri_no3=0,seri_no4=0,seri_no5=0,seri_no6=0,seri_no7=0,seri_no8=0; // 8 bitlik de�i�kenler tan�mlan�yor
int32 seri_no=0; // 32 bitlik de�i�ken tan�mlan�yor

//********** ANA PROGRAM FONKS�YONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre d���
   setup_timer_1(T1_DISABLED);     // T1 zamanlay�c�s� devre d���
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
   setup_adc_ports(NO_ANALOGS);    // ANALOG giri� yok
   setup_adc(ADC_OFF);             // ADC birimi devre d���
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre d���
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre d���

   lcd_init();   // LCD haz�rlan�yor

   ow_hiz(1);   // 1-Wire ileti�im h�z� standart se�ildi

   while(1) // Sonsuz d�ng�
   {
      sonuc=ow_reset();  // 1-Wire cihaz�na reset sinyalini g�nder

      if (sonuc==0)  // E�er data hatt�nda 1-wire cihaz� var ve sa�lam ise
      {
         printf(lcd_putc,"\fCihaz calisiyor"); // LCD'ye veri g�nderiliyor.
         delay_ms(1500); // 1.5 sn gecikme veriliyor

         ow_yaz_byte(0x33); //ROM numaras� okuma komutu cihaza g�nderiliyor

         seri_no1=ow_oku_byte(); // ROM numaras�n�n ilk byte de�eri aile (family) kodu'dur.
         seri_no2=ow_oku_byte(); // ROM numaras�n�n 2. byte ile 7.byte de�erleri
         seri_no3=ow_oku_byte();    // cihaz�n 48 bitlik seri nosunu olu�turur
         seri_no4=ow_oku_byte();
         seri_no5=ow_oku_byte();
         seri_no6=ow_oku_byte();
         seri_no7=ow_oku_byte();
         seri_no8=ow_oku_byte(); // ROM numaras�n�n 8. byte de�eri cihaz�n CRC de�eridir

         seri_no=make32(seri_no2,seri_no3,seri_no4,seri_no5); // 8 bitlik de�erleri birle�tirerek 32 bitlik de�er olu�turur

         printf(lcd_putc,"\fCihaz Aile Kodu"); // LCD'ye veri g�nderiliyor.
         printf(lcd_putc,"\n%X",seri_no1); // Cihaz aile kodu LCD'ye g�nderiliyor
         delay_ms(2000); // 2 sn gecikme veriliyor
         printf(lcd_putc,"\fCihaz Seri No"); // LCD'ye veri g�nderiliyor.
         printf(lcd_putc,"\n%X%X%X%X%X%X",seri_no2,seri_no3,seri_no4,seri_no5,seri_no6,seri_no7); // Cihaz seri no LCD'ye g�nderiliyor
         delay_ms(2000); // 2 sn gecikme veriliyor
         printf(lcd_putc,"\fCihaz CRC Degeri"); // LCD'ye veri g�nderiliyor.
         printf(lcd_putc,"\n%X",seri_no8); // Cihaz�n CRC de�eri LCD'ye g�nderiliyor
         delay_ms(2000); // 2 sn gecikme veriliyor

         if (seri_no==0x2CC5B800) // E�er do�ru cihaz sistemdeyse
            output_high(pin_c1);  // RC1 pinine ba�l� role �eker
      }
      else  // E�er data hatt�nda 1-wire cihaz� yok veya sa�lam de�ilse
         printf(lcd_putc,"\fCihaz calismiyor");
      delay_ms(1500);  // 1.5 sn gecikme veriliyor
   }
}
