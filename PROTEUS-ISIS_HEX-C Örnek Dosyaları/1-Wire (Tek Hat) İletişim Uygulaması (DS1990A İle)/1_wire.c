#define ow_data_pin pin_c0

int16 A,B,C,D,E,F,G,H,I,J;

//***** �leti�im H�z� Se�me Fonksiyonu *****

void ow_hiz(int hiz)
{
   if (hiz==1) // hiz de�eri "1" ise standart h�z ge�erli
   {
      A = 6;
      B = 64;
      C = 60;
      D = 10;
      E = 9;
      F = 55;
      G = 0;
      H = 480;
      I = 70;
      J = 410;
   }

   if (hiz==0) // hiz de�eri "0" ise Y�ksek h�z ge�erli
               // Y�ksek h�zda ondal�kl� s�re de�erleri yuvarlat�lm��t�r
   {
      A = 1;
      B = 7;
      C = 7;
      D = 2;
      E = 1;
      F = 7;
      G = 2;
      H = 70;
      I = 8;
      J = 40;
   }
}


//***** 1-Wire �leti�im Reset Sinyali G�nderme Fonksiyonu *****

int1 ow_reset(void)
{
   int1 sonuc; // sonuc ad�nda 1 bitlik bir de�i�ken tan�mlan�yor

   delay_us(G); // G s�resi kadar gecikme veriliyor
   output_low(ow_data_pin); // 1-Wire data pini ��k��� lojik-0
   delay_us(H); // H s�resi kadar gecikme veriliyor
   output_float(ow_data_pin); // 1-Wire data pini bo�ta (giri� olarak y�nlendirildi)
   delay_us(I); // I s�resi kadar gecikme veriliyor
   sonuc=input(ow_data_pin); // 1-Wire data pini okunuyor
   delay_us(J); // J s�resi kadar gecikme veriliyor

   return sonuc; // sonuc de�i�keni de�eri ile fonksiyon geri d�ner
}



//***** 1-Wire �leti�imde Bir Bit Bilgi Yazma Fonksiyonu *****

void ow_yaz_bit(int bit)
{
   if (bit==1) // "1" Bilgisi Yaz�l�r
   {
      output_low(ow_data_pin);
      delay_us(A);
      output_float(ow_data_pin);
      delay_us(B);
   }
   else  // "0" Bilgisi Yaz�l�r
   {
      output_low(ow_data_pin);
      delay_us(C);
      output_float(ow_data_pin);
      delay_us(D);
   }
}

//***** 1-Wire �leti�imde Bir Bit Bilgi Okuma *****
int1 ow_oku_bit(void)
{
   int1 bit; // Bir bitlik de�i�ken tan�mlan�yor

   output_low(ow_data_pin);   // 1-Wire data pini ��k��� lojik-0
   delay_us(A);               // A s�resi kadar gecikme veriliyor
   output_float(ow_data_pin); // 1-Wire data pini bo�ta (giri� olarak y�nlendirildi)
   delay_us(E);               // E s�resi kadar gecikme veriliyor
   bit=input(ow_data_pin);
   delay_us(F);               // F s�resi kadar gecikme veriliyor

   return bit; // Fonksiyon bit de�i�keni de�eri ile geri d�ner
}


//***** 1-Wire �leti�imde Bir Byte Bilgi Yazma Fonksiyonu *****
void ow_yaz_byte(int data)
{
   int i; // Okunacak bilginin bit say�s�n� tutan de�i�ken

   for (i=0;i<8;i++) // Byte bilgisi bit bit yazd�r�l�yor. LSB biti ilk �nce g�nderiliyor.
   {
      ow_yaz_bit(bit_test(data,i)); // data de�i�keni de�erinin bitleri tek tek okunup g�nderiliyor
   }
}

//***** 1-Wire �leti�imde Bir Byte Bilgi Okuma Fonksiyonu *****
int ow_oku_byte(void)
{
   int i,sonuc=0; // Tam say� tipinde de�i�kenler tan�mlan�yor

   for (i=0;i<8;i++)
   {
      sonuc=sonuc>>1;    // sonuc de�i�kenini 1 bit sa�a kayd�r

      if (ow_oku_bit())        // E�er okunan bit "1" ise
         sonuc=(sonuc | 0x80); // Okunan biti sonuc de�erinde belirt
   }
   return sonuc;  // Okunan byte de�eri ile geri d�n
}





