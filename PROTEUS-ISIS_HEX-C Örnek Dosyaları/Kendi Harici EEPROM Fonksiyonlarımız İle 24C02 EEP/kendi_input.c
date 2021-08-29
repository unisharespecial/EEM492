//******** HEX OLARAK 1 BASAMAKLI BÝLGÝYÝ OKUMA FONKSÝYONU ********
byte hex_oku1 ()  // Klavyeden girilen 1 basamaklý bir deðeri HEX formatýnda okur
{
   char karakter;  // Karakter tipinde deðiþken tanýmlanýyor

   karakter=getch();  // RS232 portundan gelen bilgi alýnýyor ve “karakter” deðiþkenine aktarýlýyor
   putc(karakter);  // Alýnan karakter ekranda görünmesi için gönderiliyor

   if (karakter<='9')   // alýnan karakter eðer 9’dan küçükse
      return(karakter-'0');
   else  // alýnan karakter eðer 9’dan büyükse
      return(toupper(karakter)-'A')+10;  // Dönüþtürülen deðer ile fonksiyon geri dönsün
}

//********* HEX OLARAK 2 BASAMAKLI BÝLGÝYÝ OKUMA FONKSÝYONU ***
byte hex_oku2()  // Klavyeden girilen 2 basamaklý bir deðeri HEX formatýnda okur
{
   int high,low;  // tam sayý tipinde deðiþkenler tanýmlanýyor 

   high=hex_oku1();  // Alýnan bilginin yüksek deðerlikli 4 bitini al ve “high” deðiþkenine kaydet
   low=hex_oku1();  // Alýnan bilginin düþük deðerlikli 4 bitini al ve “low” deðiþkenine
		        // kaydet
   return(high*16+low);  // Dönüþtürülen deðer ile fonksiyon geri dönsün
}
