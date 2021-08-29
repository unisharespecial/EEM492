//////////////////////////////////////////////////////////////
//                    benim_LCD.c                           // 
// Bu LCD s�r�c� dosyas� 2x16 HD44780 uyumlu LCD�ler        //
// i�in yaz�lm��t�r. LCD�ye sadece yazma yap�laca�� i�in    //
// R/W ucu �aseye ba�lanmal�d�r. LCD ba�lant�s� a�a��dad�r. //
//////////////////////////////////////////////////////////////
// RB0 -> LCD�nin D4 ucuna
// RB1 -> LCD�nin D5 ucuna
// RB2 -> LCD�nin D6 ucuna
// RB3 -> LCD�nin D7 ucuna
// RB4 -> LCD�nin RS ucuna
// RB5 -> LCD�nin E  ucuna
// R/W ucu direkt �aseye ba�lanacak

#define e   pin_b5 // LCD'nin E ucu RB5 pinine ba�l�
#define rs  pin_b4 // LCD'nin RS ucu RB4 pinine ba�l�

//****** LCD'ye Komut G�nderme Fonksiyonu **********
void lcd_komut(byte komut)
{   
   output_b(komut>>4);   // Komutun y�ksek de�erli 4 bitini g�nder
   output_low(rs);       // LCD komut almak i�in ayarland�
   delay_cycles(1);      // 1 komut sayk�l� bekle   
   output_high(e);       // E ucu lojik-1'den lojik-0'a �ekiliyor
   delay_cycles(1);      // 1 komut sayk�l� bekle
   output_low(e);
   delay_ms(2);          // 2 msn gecikme veriliyor

   output_b(komut&0x0F); // Komutun d���k de�erli 4 bitini g�nder
   output_low(rs);      // LCD veri almak i�in ayarland�  
   delay_cycles(1);      // 1 komut sayk�l� bekle      
   output_high(e);       // E ucu lojik-1'den lojik-0'a �ekiliyor
   delay_cycles(1);      // 1 komut sayk�l� bekle
   output_low(e);
   delay_ms(2);          // 2 msn gecikme veriliyor
}

//******* LCD'ye Veri G�nderme Fonksiyonu **********
void lcd_veri(byte veri)
{ 
   output_b(veri>>4);    // Verinin y�ksek de�erli 4 bitini g�nder
   output_high(rs);      // LCD veri almak i�in ayarland�
   delay_cycles(1);      // 1 komut sayk�l� bekle    
   output_high(e);       // E ucu lojik-1'den lojik-0'a �ekiliyor
   delay_cycles(1);      // 1 komut sayk�l� bekle
   output_low(e);
   delay_ms(2);          // 2 msn gecikme veriliyor

   output_b(veri&0x0F); // Verinin d���k de�erli 4 bitini g�nder
   output_high(rs);      // LCD veri almak i�in ayarland�
   delay_cycles(1);      // 1 komut sayk�l� bekle    
   output_high(e);      // E ucu lojik-1'den lojik-0'a �ekiliyor
   delay_cycles(1);     // 1 komut sayk�l� bekle
   output_low(e);
   delay_ms(2);         // 2 msn gecikme veriliyor
}

//******* LCD'de �mlec Konumland�rma Fonksiyonu ********
void imlec(byte satir, byte sutun)
{
   if (satir==1)      // E�er sat�r de�i�keni "1" ise
      lcd_komut(0x80|(sutun-1));

   if (satir==2)      // E�er sat�r de�i�keni "2" ise
      lcd_komut(0x80|(0x40+(sutun-1)));
}

//********* LCD Ba�lang�� Ayarlar� Fonksiyonu ******
void lcd_hazirla()
{
   int i=0;
   output_low(rs); // RS ucu lojik-0
   output_low(e);  // E ucu lojik-0
   delay_ms(30);   // LCD enerjlendi�inde LCD'nin haz�r olmas� i�in beklenen s�re
   
   for(i=0;i<=3;i++)    // LCD'ye 3 kez 0x03 komutu g�nderiliyor
   {
      lcd_komut(0x03);
      delay_ms(5);      // 5msn gecikme veriliyor
   }
   lcd_komut(0x02); // LCD'ye 4 bit ileti�im komutu g�nderiliyor
   lcd_komut(0x28); // 4 bit ileti�im, 2 sat�r, 5x8 dot matris se�ildi
   lcd_komut(0x08); // Display Kapal�
   lcd_komut(0x0C); // Display a��k,imle� alt �izgi ve yan�p s�nme yok
   lcd_komut(0x06); // Her veri yaz�ld���nda imle� bir sa�a gitsin
   lcd_komut(0x01); // Display sil. �mle� 1.sat�r 1.s�tunda
}

