/******************************************************
 Uygulama Adý      : Display Uygulamasý-3(7448 Entegresi ve Buton Ýle 0-99 Yukarý/Aþaðý Sayýcý)
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

//***********Denetleyici konfigürasyon ayarlarý************
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor

#use fast_io(a) // Port yönlendirme komutlarý a portu için geçerli
#use fast_io(b) // Port yönlendirme komutlarý b portu için geçerli

#define   arttir      pin_a0   // arttir butonu pin_a0 ile eþleniyor
#define   azalt       pin_a1   // azalt butonu pin_a1 ile eþleniyor

char birler=0, onlar=0, sayi=0; // int tipinde deðiþkenler tanýmlanýyor

// Ortak katot display için veri deðerleri
const int digit[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};

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

   set_tris_a(0x03); // RA0 ve RA1 giriþ olarak yönlendiriliyor
   set_tris_b(0x00); // B portu tümüyle çýkýþ olarak yönlendiriliyor

   while(1)     // Sonsuz döngü
   {
       output_b(digit[birler]|(0b00010000)); // 1.display aktif, 2.display pasif yapýlýyor ve birler basamaðý bilgisi B portuna gönderiliyor
       delay_ms(5);                          // Gecikme veriliyor
       output_b(digit[onlar]|(0b00100000));  // 2.display aktif, 1.display pasif yapýlýyor ve onlar basamaðý bilgisi B portuna gönderiliyor
       delay_ms(5);                          // Gecikme veriliyor

       if (input(arttir))   // arttýr butonuna basýldýðýnda
       {
          sayi++;    // sayi deðerini 1 arttýr

          birler=sayi%10;;         // birler hanesi hesaplanýyor
          onlar=sayi/10;           // onlar hanesi hesaplanýyor

          while(input(arttir))     // arttýr butonundan el çekilene kadar bekle
          {
             output_b(digit[birler]|(0b00010000)); // 1.display aktif, 2.display pasif yapýlýyor ve birler basamaðý bilgisi B portuna gönderiliyor
             delay_ms(5);                          // Gecikme veriliyor
             output_b(digit[onlar]|(0b00100000));  // 2.display aktif, 1.display pasif yapýlýyor ve onlar basamaðý bilgisi B portuna gönderiliyor
             delay_ms(5);                          // Gecikme veriliyor
          }
        }

      if (input(azalt)&&(sayi!=0))   // azalt butonuna basýldýðýnda
       {
          sayi--;     // sayi deðerini 1 azalt

         birler=sayi%10;;         // birler hanesi hesaplanýyor
         onlar=sayi/10;           // onlar hanesi hesaplanýyor

          while(input(azalt))      // azalt butonundan el çekilene kadar bekle
          {
             output_b(digit[birler]|(0b00010000)); // 1.display aktif, 2.display pasif yapýlýyor ve birler basamaðý bilgisi B portuna gönderiliyor
             delay_ms(5);                          // Gecikme veriliyor
             output_b(digit[onlar]|(0b00100000));  // 2.display aktif, 1.display pasif yapýlýyor ve onlar basamaðý bilgisi B portuna gönderiliyor
             delay_ms(5);                          // Gecikme veriliyor

          }
       }
       if (sayi==100)   // sayi deðeri 100 ise deðeri sýfýrla
          sayi=0;
    }
}
