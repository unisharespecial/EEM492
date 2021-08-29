#include <htc.h>
#include "yeni_lcd.h" // lcd.h dosyasý tanýmlanýp, deðerler alýnýyor
#include "delay.h" // Gecikme fonksiyonu tanýmlanýyor

void lcd_delay(void)
{
DelayUs(250);
DelayUs(250);
}

void lcd_byte(unsigned char b){
	d7=(b&0B10000000)>>7;
	d6=(b&0B01000000)>>6;
	d5=(b&0B00100000)>>5;
	d4=(b&0B00010000)>>4;
	
	
}

void lcd_komut(unsigned char c) // Komut gönderme fonksiyonu
{
	rw=0; // LCD'ye yazma yapýlacak
	rs=0; // LCD'ye komut gönderilecek
	e=1; // Düsen kenar tetikleme olduðu için E önce 1
	lcd_byte ( c & 0xF0 ); // Yüksek deðerlikli bitler gönderiliyor
	e=0; // E, 0 yapýlýyor
	lcd_delay(); //Belirli süre bekleniyor
	e=1; // E, 1 yapýlýyor
	lcd_byte( (c & 0x0F)<<4 ); // Düsük deðerlikli bitler gönderiliyor
	e=0; // E, 0 yapýlýyor
	lcd_delay(); // Belirli bir süre bekleniyor
}
void veri_yolla(unsigned char c)
{
	rw=0;
	rs=1; // Komut yolladan tek farký, RS'nin 1 olmasý
	e=1;
	lcd_byte ( c & 0xF0 );
	e=0;
	lcd_delay();
	e=1;
	lcd_byte ( (c & 0x0F)<<4 );
	e=0;
	lcd_delay();
}
void lcd_clear(void) // LCD siliniyor
{
	lcd_komut(0x1);
	lcd_delay();
}
void lcd_yaz(const char * s) // LCD'ye string ifade gönderiliyor
{
	lcd_delay();
	while(*s)
		veri_yolla(*s++);
}
void lcd_gotoxy(unsigned char x,unsigned char y) //LCD'nin belli
	//bölgesine gidiliyor
{
	if(x==1)
		lcd_komut(0x80+((y-1)%16));
	else
		lcd_komut(0xC0+((y-1)%16));
}
void lcd_init() // LCD ilk yükleme ayarlarý yapýlýyor
{
	rs = 0;
	e = 0;
	rw = 0;
	lcd_delay();
	e=1;
	lcd_komut(0x02);
	lcd_delay();
	lcd_komut(CiftSatir4Bit);
	lcd_komut(SagaYaz);
	lcd_komut(ImlecGizle);
	lcd_clear();
	lcd_komut(BirinciSatir);
}

void lcd_sayi(unsigned long sayi)
{
	if(sayi==0){
		veri_yolla(48);	
	}
	else{
		unsigned char dizi[10];
		unsigned char i;
		unsigned char durum=0;
		dizi[0]=sayi/1000000000;
			sayi-=dizi[0]*1000000000;
	   	dizi[1]=sayi/100000000;
			sayi-=dizi[1]*100000000;
		dizi[2]=sayi/10000000;
			sayi-=dizi[2]*10000000;
		dizi[3]=sayi/1000000;
			sayi-=dizi[3]*1000000;
		dizi[4]=sayi/100000;
			sayi-=dizi[4]*100000;
		dizi[5]=sayi/10000;
			sayi-=dizi[5]*10000;
		dizi[6]=sayi/1000;
			sayi-=dizi[6]*1000;
		dizi[7]=sayi/100;
			sayi-=dizi[7]*100;
		dizi[8]=sayi/10;
			sayi-=dizi[8]*10;
		dizi[9]=sayi%10;
		for(i=0;i<=9;i++)
		{
			switch (dizi[i]){
				case 0:
					dizi[i]=48;
					break;
				case 1:
					dizi[i]=49;
					break;
				case 2:
					dizi[i]=50;
					break;
				case 3:
					dizi[i]=51;
					break;
				case 4:
					dizi[i]=52;
					break;
				case 5:
					dizi[i]=53;
					break;
				case 6:
					dizi[i]=54;
					break;
				case 7:
					dizi[i]=55;
					break;
				case 8:
					dizi[i]=56;
					break;
				case 9:
					dizi[i]=57;
					break;
				default:
					break;
	
	
	
			}
		}
		for( i=0;i<=9;i++){
			if(dizi[i]!=0x30&&durum==0)
			{
					durum=1;
			}
			
			if(durum==1)
			{
				veri_yolla(dizi[i]);
			}
		}
	}

}


