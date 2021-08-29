/******************************************************
 Uygulama Adý      : Matris LED Display Uygulamas
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use fast_io(b) // Port yönlendirme komutlarý B portu için geçerli
#use fast_io(c) // Port yönlendirme komutlarý C portu için geçerli

//******** Matrise Gönderilecek Karakter Bilgileri *******
 int A[]={0x03,0x75,0x76,0x75,0X03};
 int B[]={0x00,0X36,0X36,0x36,0X49};
 int C[]={0x41,0x3E,0x3E,0x3E,0x5D};
 int D[]={0x00,0x3E,0x3E,0x3E,0x41};
 int E[]={0x00,0xB6,0xB6,0xB6,0xBE};
 int arti[]={0x77,0x77,0x41,0x77,0x77};
 int cift_ok[]={0x6B,0x5D,0x00,0x5D,0x6B};

//******* Sütun Seçme Fonksiyonu ************
int sutunsec (int s)
{
   switch (s)
   {
      case 0: return(0x10);break;  // 1. Sütun aktif, diðer sütunlar pasif
      case 1: return(0x08);break;  // 2. Sütun aktif, diðer sütunlar pasif
      case 2: return(0x04);break;  // 3. Sütun aktif, diðer sütunlar pasif
      case 3: return(0x02);break;  // 4. Sütun aktif, diðer sütunlar pasif
      case 4: return(0x01);break;  // 5. Sütun aktif, diðer sütunlar pasif
   }
}

//******* Matrise Veri Gönderme Fonksiyonu *******
void matris_karakter_gonder(char harf[], int tekrar)
{
   int i,j;  // Deðiþkenler tanýmlanýyor

   for (i=1;i<tekrar;i++)  // Karakterin Matris LED'de görünmesi için tekrar döngüsü
       {
         for(j=0;j<5;j++) // // Bu döngüde tarama iþlemi yapýlýyor
         {
            output_c(sutunsec(j)); // Sütun seç ve C portuna sütun deðerini gönder
            output_b(harf[j]);     // Gösterilecek harfin satýr bilgisini B portuna gönder
            delay_ms(10);          // Gecikme veriliyor
         }
      }
}

/********* ANA PROGRAM FONKSÝYONU********/

void main ()
{ 
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_b(0x00);  // B portu tümüyle çýkýþ olarak yönlendiriliyor
   set_tris_c(0x00);  // C portu tümüyle çýkýþ olarak yönlendiriliyor

   while(1)
   {
        matris_karakter_gonder(A,25);// A karakterini matriste göster
        matris_karakter_gonder(B,25);// B karakterini matriste göster
        matris_karakter_gonder(C,25);// C karakterini matriste göster
        matris_karakter_gonder(D,25);// D karakterini matriste göster
        matris_karakter_gonder(E,25);// E karakterini matriste göster
        matris_karakter_gonder(arti,25);//+ karakterini matriste göster
        matris_karakter_gonder(cift_ok,25);// Çift yönlü ok karakterini matriste göster

   }
}

