/******************************************************
 Uygulama Ad�      : Matris LED Display Uygulamas
*******************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k dosyas� tan�t�l�yor.

//***********Denetleyici konfig�rasyon ayarlar�************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu i�in kullan�lan osilat�r frekans� belirtiliyor

#use fast_io(b) // Port y�nlendirme komutlar� B portu i�in ge�erli
#use fast_io(c) // Port y�nlendirme komutlar� C portu i�in ge�erli

//******** Matrise G�nderilecek Karakter Bilgileri *******
 int A[]={0x03,0x75,0x76,0x75,0X03};
 int B[]={0x00,0X36,0X36,0x36,0X49};
 int C[]={0x41,0x3E,0x3E,0x3E,0x5D};
 int D[]={0x00,0x3E,0x3E,0x3E,0x41};
 int E[]={0x00,0xB6,0xB6,0xB6,0xBE};
 int arti[]={0x77,0x77,0x41,0x77,0x77};
 int cift_ok[]={0x6B,0x5D,0x00,0x5D,0x6B};

//******* S�tun Se�me Fonksiyonu ************
int sutunsec (int s)
{
   switch (s)
   {
      case 0: return(0x10);break;  // 1. S�tun aktif, di�er s�tunlar pasif
      case 1: return(0x08);break;  // 2. S�tun aktif, di�er s�tunlar pasif
      case 2: return(0x04);break;  // 3. S�tun aktif, di�er s�tunlar pasif
      case 3: return(0x02);break;  // 4. S�tun aktif, di�er s�tunlar pasif
      case 4: return(0x01);break;  // 5. S�tun aktif, di�er s�tunlar pasif
   }
}

//******* Matrise Veri G�nderme Fonksiyonu *******
void matris_karakter_gonder(char harf[], int tekrar)
{
   int i,j;  // De�i�kenler tan�mlan�yor

   for (i=1;i<tekrar;i++)  // Karakterin Matris LED'de g�r�nmesi i�in tekrar d�ng�s�
       {
         for(j=0;j<5;j++) // // Bu d�ng�de tarama i�lemi yap�l�yor
         {
            output_c(sutunsec(j)); // S�tun se� ve C portuna s�tun de�erini g�nder
            output_b(harf[j]);     // G�sterilecek harfin sat�r bilgisini B portuna g�nder
            delay_ms(10);          // Gecikme veriliyor
         }
      }
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

   set_tris_b(0x00);  // B portu t�m�yle ��k�� olarak y�nlendiriliyor
   set_tris_c(0x00);  // C portu t�m�yle ��k�� olarak y�nlendiriliyor

   while(1)
   {
        matris_karakter_gonder(A,25);// A karakterini matriste g�ster
        matris_karakter_gonder(B,25);// B karakterini matriste g�ster
        matris_karakter_gonder(C,25);// C karakterini matriste g�ster
        matris_karakter_gonder(D,25);// D karakterini matriste g�ster
        matris_karakter_gonder(E,25);// E karakterini matriste g�ster
        matris_karakter_gonder(arti,25);//+ karakterini matriste g�ster
        matris_karakter_gonder(cift_ok,25);// �ift y�nl� ok karakterini matriste g�ster

   }
}

