/******************************************************************
 PIC16F877 ile DS1621 Sýcaklýk ve Termostat Entegresi Uygulamasý
*******************************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk                 // dosyasý tanýtýlýyor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfigürasyon ayarlarý

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.


#define use_portb_lcd TRUE    // LCD B portuna baðlý
#include <lcd.c>              // lcd.c dosyasý programa ekleniyor

#use i2c(master,sda=pin_c1, scl=pin_c0, slow=100000) // I2C Fonksiyonu,SDA ve SCL pinleri ve iletiþim hýzý belirleniyor

//***************** DS1621 SICAKLIK OKUMA FONKSÝYONU **************************

float ds1621_oku (void)
{
   signed int8 th,tl;
   float sicaklik;

   i2c_start();        // i2c iletiþimini baþlat
   i2c_write(0x90);    // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
                       // R/W biti yazma yapýlacaðý için "0"
   i2c_write(0x22);    // sýcaklýk dönüþümünü durdur komutu gönderiliyor
   i2c_stop();         // i2c iletiþimini durdur

   i2c_start();        // i2c iletiþimini baþlat
   i2c_write(0x90);    // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
                       // yazma yapýlacaðýndan burada R/W biti "0"
   i2c_write(0xee);    // Sýcaklýk dönüþümüne baþla komutu gönderiliyor
   i2c_stop();         // i2c iletiþimini durdur

   i2c_start();        // i2c iletiþimini baþlat
   i2c_write(0x90);    // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
   i2c_write(0xaa);    // Sýcaklýðý oku komutu gönderiliyor
   i2c_start();        // i2c iletiþimini baþlat
   i2c_write(0x91);    // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
                       // okuma yapýlacaðýndan burada R/W biti "1"
   th=i2c_read(0);     // sýcaklýk deðerinin yüksek 8 bitlik deðerini oku ve "th" deðiþkenine kaydet
   i2c_start();        // i2c iletiþimini baþlat
   i2c_write(0x91);    // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
   tl=i2c_read(0);     // sýcaklýk deðerinin düþük 8 bitlik deðerini oku ve "tl" deðiþkenine kaydet
   i2c_stop();         // i2c iletiþimini durdur

   if (tl==0x80)      // Eðer sýcaklýk deðeri buçuklu ise sýcaklýða 0.5 ekle
      sicaklik=th+0.5;
   else
      sicaklik=th; // Eðer sýcaklýk deðeri buçuklu deðilse aynen deðiþkene kaydet

   delay_ms(11);
   return(sicaklik);   // Fonksiyon "sicaklik" deðeri ile geri döner
}

//*************** DS1621 TH ve TL'ye VERÝ YAZMA FONKSÝYONU ****************************

void yaz_ds1621_th_tl (signed int th_h, signed int th_l, signed int  tl_h, signed int tl_l)
{
   if (th_l==0x05)      // Eðer th_l sýcaklýk  deðeri buçuklu ise
      th_l=0x80;        // TH'ýn düþük deðerlikli 8.bitinde bu belirtiliyor
      
   if (tl_l==0x05)      // Eðer tl_l sýcaklýk deðeri buçuklu ise
      tl_l=0x80;        // TL'nýn düþük deðerlikli 8.bitinde bu belirtiliyor
      
   i2c_start();       // i2c iletiþimi baþlangýç ayarlarý
   i2c_write(0x90);   // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
                      // yazma yapýlacaðýndan burada R/W biti "0"
   i2c_write(0xa1);   // TH'a eriþme komutu gönderiliyor
   i2c_write(th_h);   // TH deðerinin yüksek deðerlikli byte'ý gönderiliyor
   i2c_write(th_l);   // TH deðerinin düþük deðerlikli byte'ý gönderiliyor
   i2c_stop();        // i2c iletiþimi sonlandýrýlýyor
   delay_ms(11);      // Belli bir süre bekleniyor

   i2c_start();       // i2c iletiþimini baþlat
   i2c_write(0x90);   // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
   i2c_write(0xa2);  // TL'ye eriþme komutu gönderiliyor
   i2c_write(tl_h);  // TL deðerinin yüksek deðerlikli byte'ý gönderiliyor
   i2c_write(tl_l);  // TL deðerinin düþük deðerlikli byte'ý gönderiliyor
   i2c_stop();       // i2c iletiþimini durdur
   delay_ms(11);
}

//******** DS1621 KONFÝGÜRASYON KAYDEDÝCÝSÝNE VERÝ YAZMA FONKSÝYONU ************

void yaz_ds1621_ayar (byte deger)
{
   i2c_start();      // i2c iletiþimini baþlat
   i2c_write(0x90);  // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
   i2c_write(0xac);  // Konfigürasyon kaydedicisine eriþme komutu gönderiliyor
   i2c_write(deger); // Konfigürasyon ayar bilgisi gönderiliyor
   i2c_stop();       // i2c iletiþimini durdur
   delay_ms(11);
}

//************ DS1621 KONFÝGÜRASYON KAYDEDÝCÝSÝNÝ OKUMA FONKSÝYONU *************

byte oku_ds1621_ayar ()
{
   byte con;
   
   i2c_start();      // i2c iletiþimini baþlat
   i2c_write(0x90);  // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
                     // yazma yapýlacaðýndan burada R/W biti "0"
   i2c_write(0xac);  // Konfigürasyon kaydedicisine eriþme komutu gönderiliyor
   i2c_start();      // i2c iletiþimini baþlat
   i2c_write(0x91);  // DS1621 entegresine adres ve R/W bit bilgisi gönderiliyor
                     // okuma yapýlacaðýndan burada R/W biti "1"
   con=i2c_read(0);  // Konfigürasyon kaydedicisi içeriði okunuyor
   i2c_stop();       // i2c iletiþimini durdur
   return(con);      // Fonksiyon "con" deðiþkeni deðeri ile geri döner
}

char sonuc[17];      // Karakter tipinde dizi tanýmlanýyor
byte ayar;           // byte olarak deðiþken tanýmlanýyor

//******************* ANA PROGRAM FONKSÝYONU *******************
void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);     // SPI birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   lcd_init();               // LCD baþlangýç ayarlarý yapýlýyor
   delay_ms(5);

   ayar=oku_ds1621_ayar();  // DS1621 konfigürasyon kaydedicisi içeriði okunuyor
   bit_set(ayar,1);         // Konfigürasyon kaydedicisinde POL biti "1" yapýlýyor
                            // bu bit alarm anýnda çýkýþýn lojik-1 olmasý için
                            // "1" yapýlýyor
   bit_clear(ayar,0);       // Konfigürasyon kaydedicisinde 1SHOT biti "0" yapýlýyor
                            // sürekli sýcaklýk okumasý yapýlsýn diye
   yaz_ds1621_ayar(ayar);   // Yapýlan deðiþiklikler konfigürasyon kaydedicisine aktarýlýyor

   yaz_ds1621_th_tl(24,5,21,0);  // TH ve TL deðerleri belirleniyor

   while(1)    // Sonsuz döngü
   {
      sprintf(sonuc,"\fSicaklik=%0.1fC",ds1621_oku());
      printf(lcd_putc,"%s",sonuc);
      delay_ms(500);
   }
}
