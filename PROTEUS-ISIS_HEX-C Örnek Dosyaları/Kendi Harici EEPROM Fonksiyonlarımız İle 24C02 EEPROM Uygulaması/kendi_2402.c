//***************** EEPROM Ýletiþime Hazýr mý? Fonksiyonu **********
int1 eeprom_hazirmi()
{
   int1 ack;

   i2c_start();            // i2c iletiþimi baþlatýlýyor
   ack=i2c_write(0xa0);    // EEPROM hazýrsa ack=0 olur.
   i2c_stop();             // i2c iletiþimi sonlandýrýlýyor
   
   return !ack;            // Fonksiyon ack bitinin deðerinin tersi ile geri döner
}

//************************** EEPROM YAZMA FONKSÝYONU *****************
void eeprom_yaz(byte adres, byte veri)
{
   while(!eeprom_hazirmi());  // EEPROM hazýr olana kadar bekle
   i2c_start();               // i2c iletiþimi baþlatýlýyor
   i2c_write(0xa0);           // EEPROM entegresine kontrol bilgisi gönderiliyor
   i2c_write(adres);          // adres bilgisi EEPROM'a gönderiliyor
   i2c_write(veri);           // veri bilgisi EEPROM'a gönderiliyor
   i2c_stop();                // i2c iletiþimi sonlandýrýlýyor
   delay_ms(11);              // Belli bir süre bekleniyor
}

//************************* EEPROM OKUMA FONKSÝYONU *****************
byte eeprom_oku(byte adres)
{
   byte veri;

   while(!eeprom_hazirmi());  // EEPROM hazýr olana kadar bekle
   i2c_start();               // i2c iletiþimi baþlatýlýyor
   i2c_write(0xa0);           // EEPROM entegresine kontrol bilgisi gönderiliyor
   i2c_write(adres);          // adres bilgisi EEPROM'a gönderiliyor
   i2c_start();               // i2c iletiþimi baþlangýç ayarlarý
   i2c_write(0xa1);           // EEPROM entegresine kontrol bilgisi gönderiliyor
   veri=i2c_read(0);          // Slave konumunda olan EEPROM'dan okuma yap
   i2c_stop();                // i2c iletiþimi sonlandýrýlýyor
   
   return(veri);              // Fonksiyon "veri" deðeri ile geri döner
}
