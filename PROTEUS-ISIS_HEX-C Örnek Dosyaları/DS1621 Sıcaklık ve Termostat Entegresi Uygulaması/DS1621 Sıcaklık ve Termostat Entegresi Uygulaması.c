/******************************************************************
 PIC16F877 ile DS1621 S�cakl�k ve Termostat Entegresi Uygulamas�
*******************************************************************/
#include <16f877.h>     // Kullan�lacak denetleyicinin ba�l�k                 // dosyas� tan�t�l�yor.
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD // Denetleyici konfig�rasyon ayarlar�

#use delay (clock=4000000) // Gecikme fonksiyonu i�in kullan�lacak osilat�r frekans� belirtiliyor.


#define use_portb_lcd TRUE    // LCD B portuna ba�l�
#include <lcd.c>              // lcd.c dosyas� programa ekleniyor

#use i2c(master,sda=pin_c1, scl=pin_c0, slow=100000) // I2C Fonksiyonu,SDA ve SCL pinleri ve ileti�im h�z� belirleniyor

//***************** DS1621 SICAKLIK OKUMA FONKS�YONU **************************

float ds1621_oku (void)
{
   signed int8 th,tl;
   float sicaklik;

   i2c_start();        // i2c ileti�imini ba�lat
   i2c_write(0x90);    // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
                       // R/W biti yazma yap�laca�� i�in "0"
   i2c_write(0x22);    // s�cakl�k d�n���m�n� durdur komutu g�nderiliyor
   i2c_stop();         // i2c ileti�imini durdur

   i2c_start();        // i2c ileti�imini ba�lat
   i2c_write(0x90);    // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
                       // yazma yap�laca��ndan burada R/W biti "0"
   i2c_write(0xee);    // S�cakl�k d�n���m�ne ba�la komutu g�nderiliyor
   i2c_stop();         // i2c ileti�imini durdur

   i2c_start();        // i2c ileti�imini ba�lat
   i2c_write(0x90);    // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
   i2c_write(0xaa);    // S�cakl��� oku komutu g�nderiliyor
   i2c_start();        // i2c ileti�imini ba�lat
   i2c_write(0x91);    // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
                       // okuma yap�laca��ndan burada R/W biti "1"
   th=i2c_read(0);     // s�cakl�k de�erinin y�ksek 8 bitlik de�erini oku ve "th" de�i�kenine kaydet
   i2c_start();        // i2c ileti�imini ba�lat
   i2c_write(0x91);    // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
   tl=i2c_read(0);     // s�cakl�k de�erinin d���k 8 bitlik de�erini oku ve "tl" de�i�kenine kaydet
   i2c_stop();         // i2c ileti�imini durdur

   if (tl==0x80)      // E�er s�cakl�k de�eri bu�uklu ise s�cakl��a 0.5 ekle
      sicaklik=th+0.5;
   else
      sicaklik=th; // E�er s�cakl�k de�eri bu�uklu de�ilse aynen de�i�kene kaydet

   delay_ms(11);
   return(sicaklik);   // Fonksiyon "sicaklik" de�eri ile geri d�ner
}

//*************** DS1621 TH ve TL'ye VER� YAZMA FONKS�YONU ****************************

void yaz_ds1621_th_tl (signed int th_h, signed int th_l, signed int  tl_h, signed int tl_l)
{
   if (th_l==0x05)      // E�er th_l s�cakl�k  de�eri bu�uklu ise
      th_l=0x80;        // TH'�n d���k de�erlikli 8.bitinde bu belirtiliyor
      
   if (tl_l==0x05)      // E�er tl_l s�cakl�k de�eri bu�uklu ise
      tl_l=0x80;        // TL'n�n d���k de�erlikli 8.bitinde bu belirtiliyor
      
   i2c_start();       // i2c ileti�imi ba�lang�� ayarlar�
   i2c_write(0x90);   // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
                      // yazma yap�laca��ndan burada R/W biti "0"
   i2c_write(0xa1);   // TH'a eri�me komutu g�nderiliyor
   i2c_write(th_h);   // TH de�erinin y�ksek de�erlikli byte'� g�nderiliyor
   i2c_write(th_l);   // TH de�erinin d���k de�erlikli byte'� g�nderiliyor
   i2c_stop();        // i2c ileti�imi sonland�r�l�yor
   delay_ms(11);      // Belli bir s�re bekleniyor

   i2c_start();       // i2c ileti�imini ba�lat
   i2c_write(0x90);   // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
   i2c_write(0xa2);  // TL'ye eri�me komutu g�nderiliyor
   i2c_write(tl_h);  // TL de�erinin y�ksek de�erlikli byte'� g�nderiliyor
   i2c_write(tl_l);  // TL de�erinin d���k de�erlikli byte'� g�nderiliyor
   i2c_stop();       // i2c ileti�imini durdur
   delay_ms(11);
}

//******** DS1621 KONF�G�RASYON KAYDED�C�S�NE VER� YAZMA FONKS�YONU ************

void yaz_ds1621_ayar (byte deger)
{
   i2c_start();      // i2c ileti�imini ba�lat
   i2c_write(0x90);  // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
   i2c_write(0xac);  // Konfig�rasyon kaydedicisine eri�me komutu g�nderiliyor
   i2c_write(deger); // Konfig�rasyon ayar bilgisi g�nderiliyor
   i2c_stop();       // i2c ileti�imini durdur
   delay_ms(11);
}

//************ DS1621 KONF�G�RASYON KAYDED�C�S�N� OKUMA FONKS�YONU *************

byte oku_ds1621_ayar ()
{
   byte con;
   
   i2c_start();      // i2c ileti�imini ba�lat
   i2c_write(0x90);  // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
                     // yazma yap�laca��ndan burada R/W biti "0"
   i2c_write(0xac);  // Konfig�rasyon kaydedicisine eri�me komutu g�nderiliyor
   i2c_start();      // i2c ileti�imini ba�lat
   i2c_write(0x91);  // DS1621 entegresine adres ve R/W bit bilgisi g�nderiliyor
                     // okuma yap�laca��ndan burada R/W biti "1"
   con=i2c_read(0);  // Konfig�rasyon kaydedicisi i�eri�i okunuyor
   i2c_stop();       // i2c ileti�imini durdur
   return(con);      // Fonksiyon "con" de�i�keni de�eri ile geri d�ner
}

char sonuc[17];      // Karakter tipinde dizi tan�mlan�yor
byte ayar;           // byte olarak de�i�ken tan�mlan�yor

//******************* ANA PROGRAM FONKS�YONU *******************
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

   lcd_init();               // LCD ba�lang�� ayarlar� yap�l�yor
   delay_ms(5);

   ayar=oku_ds1621_ayar();  // DS1621 konfig�rasyon kaydedicisi i�eri�i okunuyor
   bit_set(ayar,1);         // Konfig�rasyon kaydedicisinde POL biti "1" yap�l�yor
                            // bu bit alarm an�nda ��k���n lojik-1 olmas� i�in
                            // "1" yap�l�yor
   bit_clear(ayar,0);       // Konfig�rasyon kaydedicisinde 1SHOT biti "0" yap�l�yor
                            // s�rekli s�cakl�k okumas� yap�ls�n diye
   yaz_ds1621_ayar(ayar);   // Yap�lan de�i�iklikler konfig�rasyon kaydedicisine aktar�l�yor

   yaz_ds1621_th_tl(24,5,21,0);  // TH ve TL de�erleri belirleniyor

   while(1)    // Sonsuz d�ng�
   {
      sprintf(sonuc,"\fSicaklik=%0.1fC",ds1621_oku());
      printf(lcd_putc,"%s",sonuc);
      delay_ms(500);
   }
}
