//***************** EEPROM �leti�ime Haz�r m�? Fonksiyonu **********
int1 eeprom_hazirmi()
{
   int1 ack;

   i2c_start();            // i2c ileti�imi ba�lat�l�yor
   ack=i2c_write(0xa0);    // EEPROM haz�rsa ack=0 olur.
   i2c_stop();             // i2c ileti�imi sonland�r�l�yor
   
   return !ack;            // Fonksiyon ack bitinin de�erinin tersi ile geri d�ner
}

//************************** EEPROM YAZMA FONKS�YONU *****************
void eeprom_yaz(byte adres, byte veri)
{
   while(!eeprom_hazirmi());  // EEPROM haz�r olana kadar bekle
   i2c_start();               // i2c ileti�imi ba�lat�l�yor
   i2c_write(0xa0);           // EEPROM entegresine kontrol bilgisi g�nderiliyor
   i2c_write(adres);          // adres bilgisi EEPROM'a g�nderiliyor
   i2c_write(veri);           // veri bilgisi EEPROM'a g�nderiliyor
   i2c_stop();                // i2c ileti�imi sonland�r�l�yor
   delay_ms(11);              // Belli bir s�re bekleniyor
}

//************************* EEPROM OKUMA FONKS�YONU *****************
byte eeprom_oku(byte adres)
{
   byte veri;

   while(!eeprom_hazirmi());  // EEPROM haz�r olana kadar bekle
   i2c_start();               // i2c ileti�imi ba�lat�l�yor
   i2c_write(0xa0);           // EEPROM entegresine kontrol bilgisi g�nderiliyor
   i2c_write(adres);          // adres bilgisi EEPROM'a g�nderiliyor
   i2c_start();               // i2c ileti�imi ba�lang�� ayarlar�
   i2c_write(0xa1);           // EEPROM entegresine kontrol bilgisi g�nderiliyor
   veri=i2c_read(0);          // Slave konumunda olan EEPROM'dan okuma yap
   i2c_stop();                // i2c ileti�imi sonland�r�l�yor
   
   return(veri);              // Fonksiyon "veri" de�eri ile geri d�ner
}
