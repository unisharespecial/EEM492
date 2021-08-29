/******************************************************
      PIC16F877 �le Bilgisayar �le Step Motor Uygulamas�
******************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 protokol� ayarlar� belirtiliyor

int i,hiz=500; // Tam say� tipinde de�i�kenler tan�mlan�yor
char islem=0;  // Karakter tipinde de�i�ken tan�mlan�yor

const int yarim_adim[]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09}; // Step motor yar�m ad�m d�n�� ad�mlar�

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

   output_b(0x00); // B portu ��k��� ba�lang��ta s�f�rlan�yor

/****************MEN�**********************************/

   printf("\n\r************************************************");
   printf("\n\r           ADIM MOTOR KONTROL�                  ");
   printf("\n\r************************************************");
   printf("\n\n");
   printf("\n\rIslem Seciniz:\n");
   printf("\n\r------------------------------------------------");
   printf("\n\r   Saga Dondur   (R)");
   printf("\n\r   Sola Dondur   (L)");
   printf("\n\r   Motoru Durdur (R ve L disindaki herhangi bir tus)");
   printf("\n\r------------------------------------------------");
   printf("\n\rYapmak istediginiz islemi seciniz>");

   while(1)
   {
      islem="null";    // islem de�i�keninin i�eri�ini bo� olarak ayarla
      islem=getchar(); // Seri port �zerinden gelen karakter islem de�i�kenine aktar�l�yor
      putc(islem);     // RS232 �zerinden klavye'den girilen karakteri ekrana g�nder.

      while (islem=='R'||islem=='r')   //Sa�a d�nd�rme i�lemi se�ildi ise
      {
         printf("\n\rMotor Saga Donuyor...");
         for (;i<8;i++)   // S�ra ile sa�a d�nme de�erlerini g�nder
         {
            output_b(yarim_adim[i]); // Step motor 1 ad�m ileri
            delay_ms(hiz);           // Ad�mlar aras�ndaki s�re

            if (i==7)   // E�er i de�eri 7 olursa s�f�rla
               i=0;

           if (kbhit()) break;   //Seri portan bir veri al�nd� ise d�ng�den ��k
         }
         if (kbhit()) break;     //Seri portan bir veri al�nd� ise d�ng�den ��k
      }

      while (islem=='L'||islem=='l')   //Sola d�nd�rme i�lemi se�ildi ise
      {
         printf("\n\rMotor Sola Donuyor...");

         for (;i>=0;i--)   // S�ra ile sola d�nme de�erlerini g�nder
         {
            if (i==0)   // E�er i de�eri 0 ise i de�eri 7 olsun
               i=7;
            output_b(yarim_adim[i]);   // Step motor 1 ad�m geri
            delay_ms(hiz);             // Ad�mlar aras�ndaki s�re

            if (kbhit()) break;        // Seri portan bir veri al�nd� ise d�ng�den ��k
         }
         if (kbhit()) break;           // Seri portan bir veri al�nd� ise d�ng�den ��k
      }
   }
}
