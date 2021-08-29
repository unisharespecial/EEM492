//////////////////////////////////////////////////////////////
//                    benim_LCD.c                           // 
// Bu LCD sürücü dosyasý 2x16 HD44780 uyumlu LCD’ler        //
// için yazýlmýþtýr. LCD’ye sadece yazma yapýlacaðý için    //
// R/W ucu þaseye baðlanmalýdýr. LCD baðlantýsý aþaðýdadýr. //
//////////////////////////////////////////////////////////////
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
   output_b(komut>>4);   // Komutun yüksek deðerli 4 bitini gönder
   output_low(rs);       // LCD komut almak için ayarlandý
   delay_cycles(1);      // 1 komut saykýlý bekle   
   output_high(e);       // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);      // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(2);          // 2 msn gecikme veriliyor

   output_b(komut&0x0F); // Komutun düþük deðerli 4 bitini gönder
   output_low(rs);      // LCD veri almak için ayarlandý  
   delay_cycles(1);      // 1 komut saykýlý bekle      
   output_high(e);       // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);      // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(2);          // 2 msn gecikme veriliyor
}

//******* LCD'ye Veri Gönderme Fonksiyonu **********
void lcd_veri(byte veri)
{ 
   output_b(veri>>4);    // Verinin yüksek deðerli 4 bitini gönder
   output_high(rs);      // LCD veri almak için ayarlandý
   delay_cycles(1);      // 1 komut saykýlý bekle    
   output_high(e);       // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);      // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(2);          // 2 msn gecikme veriliyor

   output_b(veri&0x0F); // Verinin düþük deðerli 4 bitini gönder
   output_high(rs);      // LCD veri almak için ayarlandý
   delay_cycles(1);      // 1 komut saykýlý bekle    
   output_high(e);      // E ucu lojik-1'den lojik-0'a çekiliyor
   delay_cycles(1);     // 1 komut saykýlý bekle
   output_low(e);
   delay_ms(2);         // 2 msn gecikme veriliyor
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

