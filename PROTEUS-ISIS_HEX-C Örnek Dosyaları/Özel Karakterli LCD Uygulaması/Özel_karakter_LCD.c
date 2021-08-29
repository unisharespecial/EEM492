/////////////////////////////////////////////////////////////////
//                  özel_karakter_LCD.c                    //////
// Bu LCD sürücü dosyasý 2x16 HD44780 uyumlu LCD'ler        /////
// için yazýlmýþtýr. LCD'ye sadece yazma yapýlacaðý için    /////
// R/W ucu þaseye baðlanmalýdýr. LCD baðlantýsý aþaðýdadýr. /////
// Bu LCD dosyasýyla özel karakterler de LCD’de gösterilebilir///
/////////////////////////////////////////////////////////////////
// RB0 -> LCD’nin D4 ucuna
// RB1 -> LCD’nin D5 ucuna
// RB2 -> LCD’nin D6 ucuna
// RB3 -> LCD’nin D7 ucuna
// RB4 -> LCD’nin RS ucuna
// RB5 -> LCD’nin E  ucuna
// R/W ucu direkt þaseye baðlanacak

#define e   pin_b5 // LCD'nin E ucu RB5 pinine baðlý
#define rs  pin_b4 // LCD'nin RS ucu RB4 pinine baðlý

//****** LCD'ye Komut Gönderme Fonksiyonu **********
void lcd_komut(byte komut)
{
   output_b(komut>>4);  // Komutun yüksek deðerli 4 bitini gönder
   output_low(rs);      // LCD komut almak için ayarlandý
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_high(e);      // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(2);         // 2 msn gecikme veriliyor

   output_b(komut&0x0F); // Komutun düþük deðerli 4 bitini gönder
   output_low(rs);       // LCD komut almak için ayarlandý
   delay_cycles(1);      // 1 komut saykýlý bekle
   output_high(e);       // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);      // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(2);        // 2 msn gecikme veriliyor
}

//******* LCD'ye Veri Gönderme Fonksiyonu **********
void lcd_veri(byte veri)
{
   if (veri=='Ç') veri=0; // Karakter Ç ise CGRAM 0.adresteki bilgiyi gönder
   if (veri=='Ð') veri=1; // Karakter Ð ise CGRAM 1.adresteki bilgiyi gönder
   if (veri=='Ý') veri=2; // Karakter Ý ise CGRAM 2.adresteki bilgiyi gönder
   if (veri=='Ö') veri=3; // Karakter Ö ise CGRAM 3.adresteki bilgiyi gönder
   if (veri=='Þ') veri=4; // Karakter Þ ise CGRAM 4.adresteki bilgiyi gönder
   if (veri=='Ü') veri=5; // Karakter Ü ise CGRAM 5.adresteki bilgiyi gönder
   if (veri=='I') veri=6; // Karakter I ise CGRAM 6.adresteki bilgiyi gönder
   if (veri==''') veri=7; // Karakter ' ise CGRAM 7.adresteki bilgiyi gönder

   output_b(veri>>4);   // Komutun yüksek deðerli 4 bitini gönder
   output_high(rs);     // LCD veri almak için ayarlandý
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_high(e);      // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(1);         // 1 msn gecikme veriliyor

   output_b(veri&0x0F); // Komutun düþük deðerli 4 bitini gönder
   output_high(rs);     // LCD veri almak için ayarlandý
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_high(e);      // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(1);         // 1 msn gecikme veriliyor
}

//******* LCD'de Ýmlec Konumlandýrma Fonksiyonu ********
void imlec(byte satir, byte sutun)
{
   if (satir==1)      // Eðer satýr deðiþkeni "1" ise
      lcd_komut(0x80|(sutun-1));

   if (satir==2)      // Eðer satýr deðiþkeni "2" ise
      lcd_komut(0x80|(0x40+(sutun-1)));
}

//********* LCD Baþlangýç Ayarlarý Fonksiyonu ******
void lcd_hazirla()
{
   int i=0;
   output_low(rs); // RS ucu lojik-0
   output_low(e);  // E ucu lojik-0
   delay_ms(30);   // LCD enerjlendiðinde LCD'nin hazýr olmasý için beklenen süre
   
   for(i=0;i<=3;i++)    // LCD'ye 3 kez 0x03 komutu gönderiliyor
   {
      lcd_komut(0x03);
      delay_ms(5);      // 5msn gecikme veriliyor
   }
   lcd_komut(0x02); // LCD'ye 4 bit iletiþim komutu gönderiliyor
   lcd_komut(0x28); // 4 bit iletiþim, 2 satýr, 5x8 dot matris seçildi
   lcd_komut(0x08); // Display Kapalý
   lcd_komut(0x0C); // Display açýk,imleç alt çizgi ve yanýp sönme yok
   lcd_komut(0x06); // Her veri yazýldýðýnda imleç bir saða gitsin
   lcd_komut(0x01); // Display sil. Ýmleç 1.satýr 1.sütunda
}

//*** Özel Karakterleri CGRAM'e Yükleyen Fonksiyon ****
void ozel_karakterler()
{
   // CGRAM'de 1. Adrese "Ç" Karakteri Kaydediliyor
   lcd_komut(0x40);lcd_veri(14);
   lcd_komut(0x41);lcd_veri(17);
   lcd_komut(0x42);lcd_veri(16);
   lcd_komut(0x43);lcd_veri(16);
   lcd_komut(0x44);lcd_veri(16);
   lcd_komut(0x45);lcd_veri(21);
   lcd_komut(0x46);lcd_veri(14);
   lcd_komut(0x47);lcd_veri(0);

   // CGRAM'de 1. Adrese "Ð" Karakteri Kaydediliyor
   lcd_komut(0x48);lcd_veri(14);
   lcd_komut(0x49);lcd_veri(0);
   lcd_komut(0x4A);lcd_veri(15);
   lcd_komut(0x4B);lcd_veri(16);
   lcd_komut(0x4C);lcd_veri(19);
   lcd_komut(0x4D);lcd_veri(17);
   lcd_komut(0x4E);lcd_veri(15);
   lcd_komut(0x4F);lcd_veri(0);

   // CGRAM'de 2. Adrese "Ý" Karakteri Kaydediliyor
   lcd_komut(0x50);lcd_veri(4);
   lcd_komut(0x51);lcd_veri(0);
   lcd_komut(0x52);lcd_veri(4);
   lcd_komut(0x53);lcd_veri(4);
   lcd_komut(0x54);lcd_veri(4);
   lcd_komut(0x55);lcd_veri(4);
   lcd_komut(0x56);lcd_veri(4);
   lcd_komut(0x57);lcd_veri(0);

   // CGRAM'de 3. Adrese "Ö" Karakteri Kaydediliyor
   lcd_komut(0x58);lcd_veri(10);
   lcd_komut(0x59);lcd_veri(0);
   lcd_komut(0x5A);lcd_veri(14);
   lcd_komut(0x5B);lcd_veri(17);
   lcd_komut(0x5C);lcd_veri(17);
   lcd_komut(0x5D);lcd_veri(17);
   lcd_komut(0x5E);lcd_veri(14);
   lcd_komut(0x5F);lcd_veri(0);

   // CGRAM'de 4. Adrese "Þ" Karakteri Kaydediliyor
   lcd_komut(0x60);lcd_veri(14);
   lcd_komut(0x61);lcd_veri(17);
   lcd_komut(0x62);lcd_veri(16);
   lcd_komut(0x63);lcd_veri(14);
   lcd_komut(0x64);lcd_veri(1);
   lcd_komut(0x65);lcd_veri(21);
   lcd_komut(0x66);lcd_veri(14);
   lcd_komut(0x67);lcd_veri(0);

   // CGRAM'de 5. Adrese "Ü" Karakteri Kaydediliyor
   lcd_komut(0x68);lcd_veri(10);
   lcd_komut(0x69);lcd_veri(0);
   lcd_komut(0x6A);lcd_veri(17);
   lcd_komut(0x6B);lcd_veri(17);
   lcd_komut(0x6C);lcd_veri(17);
   lcd_komut(0x6D);lcd_veri(17);
   lcd_komut(0x6E);lcd_veri(14);
   lcd_komut(0x6F);lcd_veri(0);

   // CGRAM'de 6. Adrese "I" Karakteri Kaydediliyor
   lcd_komut(0x70);lcd_veri(4);
   lcd_komut(0x71);lcd_veri(4);
   lcd_komut(0x72);lcd_veri(4);
   lcd_komut(0x73);lcd_veri(4);
   lcd_komut(0x74);lcd_veri(4);
   lcd_komut(0x75);lcd_veri(4);
   lcd_komut(0x76);lcd_veri(4);
   lcd_komut(0x77);lcd_veri(0);

   // CGRAM'de 7. Adrese "'" Karakteri Kaydediliyor
   lcd_komut(0x78);lcd_veri(12);
   lcd_komut(0x79);lcd_veri(18);
   lcd_komut(0x7A);lcd_veri(18);
   lcd_komut(0x7B);lcd_veri(12);
   lcd_komut(0x7C);lcd_veri(0);
   lcd_komut(0x7D);lcd_veri(0);
   lcd_komut(0x7E);lcd_veri(0);
   lcd_komut(0x7F);lcd_veri(0);
}
