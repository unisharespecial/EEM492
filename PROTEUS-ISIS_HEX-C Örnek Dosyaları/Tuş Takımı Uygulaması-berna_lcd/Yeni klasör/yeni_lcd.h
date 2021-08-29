#define rs RD2 //Pin tanýmlamalarý
#define rw RD4
#define e RD3

#define d7 RD7
#define d6 RD6
#define d5 RD5
#define d4 RD4
/* LCD'de kullanilan komutlarin tanimlamasi*/
#define Sil 1 // Ekrani temizler
#define BasaDon 2 // Imleci sol üst köseye getirir
#define SolaYaz 4 // Imlecin belirttigi adres azalarak gider
#define SagaYaz 6 // Imlecin belirttigi adres artarak gider
#define ImlecGizle 12 // Göstergeyi ac, kursor görünmesin
#define ImlecAltta 14 // Yanip sönen blok kursor
#define ImlecYanSon 15 // Yanip sönen blok kursor
#define ImlecGeri 16 // Kursoru bir karakter geri kaydýr
#define KaydirSaga 24 // Göstergeyi bir karakter saða kaydýr
#define KaydirSola 28 // Göstergeyi bir karakter sola kaydýr
#define EkraniKapat 8 // Göstergeyi kapat (veriler silinmez)
#define BirinciSatir 128 // LCD'nin ilk satir baslangýç adresi
// (DDRAM adres)
#define IkinciSatir 192 // ikinci satirin baslangýç adresi
#define KarakUretAdres 64 // Karakter üreteci adresini belirle
// (CGRAM adres)
/* LCD'de Kullanilan Fonksiyon Seçimi */

#define CiftSatir4Bit 40 // 4 bit ara birim, 2 satir, 5*7 piksel
#define TekSatir4Bit 32 // 4 bit ara birim, 1 satir, 5*7 piksel
extern void veri_yolla(unsigned char );
extern void lcd_clear(void);
extern void lcd_yaz(const char *s);
extern void lcd_gotoxy(unsigned char x, unsigned char y);
extern void lcd_init(void);
extern void lcd_komut(unsigned char c);
extern void lcd_byte(unsigned char);
extern void lcd_sayi(unsigned long sayi);