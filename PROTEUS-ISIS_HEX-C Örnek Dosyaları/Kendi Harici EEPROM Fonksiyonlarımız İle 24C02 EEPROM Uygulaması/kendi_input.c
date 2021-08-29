//******** HEX OLARAK 1 BASAMAKLI B�LG�Y� OKUMA FONKS�YONU ********
byte hex_oku1 ()  // Klavyeden girilen 1 basamakl� bir de�eri HEX format�nda okur
{
   char karakter;  // Karakter tipinde de�i�ken tan�mlan�yor

   karakter=getch();  // RS232 portundan gelen bilgi al�n�yor ve �karakter� de�i�kenine aktar�l�yor
   putc(karakter);  // Al�nan karakter ekranda g�r�nmesi i�in g�nderiliyor

   if (karakter<='9')   // al�nan karakter e�er 9�dan k���kse
      return(karakter-'0');
   else  // al�nan karakter e�er 9�dan b�y�kse
      return(toupper(karakter)-'A')+10;  // D�n��t�r�len de�er ile fonksiyon geri d�ns�n
}

//********* HEX OLARAK 2 BASAMAKLI B�LG�Y� OKUMA FONKS�YONU ***
byte hex_oku2()  // Klavyeden girilen 2 basamakl� bir de�eri HEX format�nda okur
{
   int high,low;  // tam say� tipinde de�i�kenler tan�mlan�yor 

   high=hex_oku1();  // Al�nan bilginin y�ksek de�erlikli 4 bitini al ve �high� de�i�kenine kaydet
   low=hex_oku1();  // Al�nan bilginin d���k de�erlikli 4 bitini al ve �low� de�i�kenine
		        // kaydet
   return(high*16+low);  // D�n��t�r�len de�er ile fonksiyon geri d�ns�n
}
