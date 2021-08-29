#define ow_data_pin pin_c0

int16 A,B,C,D,E,F,G,H,I,J;

//***** Ýletiþim Hýzý Seçme Fonksiyonu *****

void ow_hiz(int hiz)
{
   if (hiz==1) // hiz deðeri "1" ise standart hýz geçerli
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

   if (hiz==0) // hiz deðeri "0" ise Yüksek hýz geçerli
               // Yüksek hýzda ondalýklý süre deðerleri yuvarlatýlmýþtýr
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


//***** 1-Wire Ýletiþim Reset Sinyali Gönderme Fonksiyonu *****

int1 ow_reset(void)
{
   int1 sonuc; // sonuc adýnda 1 bitlik bir deðiþken tanýmlanýyor

   delay_us(G); // G süresi kadar gecikme veriliyor
   output_low(ow_data_pin); // 1-Wire data pini çýkýþý lojik-0
   delay_us(H); // H süresi kadar gecikme veriliyor
   output_float(ow_data_pin); // 1-Wire data pini boþta (giriþ olarak yönlendirildi)
   delay_us(I); // I süresi kadar gecikme veriliyor
   sonuc=input(ow_data_pin); // 1-Wire data pini okunuyor
   delay_us(J); // J süresi kadar gecikme veriliyor

   return sonuc; // sonuc deðiþkeni deðeri ile fonksiyon geri döner
}



//***** 1-Wire Ýletiþimde Bir Bit Bilgi Yazma Fonksiyonu *****

void ow_yaz_bit(int bit)
{
   if (bit==1) // "1" Bilgisi Yazýlýr
   {
      output_low(ow_data_pin);
      delay_us(A);
      output_float(ow_data_pin);
      delay_us(B);
   }
   else  // "0" Bilgisi Yazýlýr
   {
      output_low(ow_data_pin);
      delay_us(C);
      output_float(ow_data_pin);
      delay_us(D);
   }
}

//***** 1-Wire Ýletiþimde Bir Bit Bilgi Okuma *****
int1 ow_oku_bit(void)
{
   int1 bit; // Bir bitlik deðiþken tanýmlanýyor

   output_low(ow_data_pin);   // 1-Wire data pini çýkýþý lojik-0
   delay_us(A);               // A süresi kadar gecikme veriliyor
   output_float(ow_data_pin); // 1-Wire data pini boþta (giriþ olarak yönlendirildi)
   delay_us(E);               // E süresi kadar gecikme veriliyor
   bit=input(ow_data_pin);
   delay_us(F);               // F süresi kadar gecikme veriliyor

   return bit; // Fonksiyon bit deðiþkeni deðeri ile geri döner
}


//***** 1-Wire Ýletiþimde Bir Byte Bilgi Yazma Fonksiyonu *****
void ow_yaz_byte(int data)
{
   int i; // Okunacak bilginin bit sayýsýný tutan deðiþken

   for (i=0;i<8;i++) // Byte bilgisi bit bit yazdýrýlýyor. LSB biti ilk önce gönderiliyor.
   {
      ow_yaz_bit(bit_test(data,i)); // data deðiþkeni deðerinin bitleri tek tek okunup gönderiliyor
   }
}

//***** 1-Wire Ýletiþimde Bir Byte Bilgi Okuma Fonksiyonu *****
int ow_oku_byte(void)
{
   int i,sonuc=0; // Tam sayý tipinde deðiþkenler tanýmlanýyor

   for (i=0;i<8;i++)
   {
      sonuc=sonuc>>1;    // sonuc deðiþkenini 1 bit saða kaydýr

      if (ow_oku_bit())        // Eðer okunan bit "1" ise
         sonuc=(sonuc | 0x80); // Okunan biti sonuc deðerinde belirt
   }
   return sonuc;  // Okunan byte deðeri ile geri dön
}





