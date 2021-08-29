//ERAY KULOÐLU/20895288	
//Keypad uygulamasý 2012
void init();
void bekle(unsigned long t);
void LcdInit();
void LcdYaz(char );
void LcdKomut(unsigned kom);
void MesajYaz(const char *msj,unsigned adr);

bit e @ PORTE.0, rs @ PORTE.1, rw @ PORTE.2;
unsigned disp @ PORTD;

void main(){
	init();
	LcdInit();
anadongu:
    
	PORTA.0=1;
    if(PORTB.0==1){

    MesajYaz("BASILAN BUTON 1",0x80);
	bekle(1500);
	}
    if(PORTB.1==1){

    MesajYaz("BASILAN BUTON 4",0x80);
	bekle(1500);
	}
    if(PORTB.2==1){

    MesajYaz("BASILAN BUTON 7",0x80);
	bekle(1500);
	}
    if(PORTB.3==1){

    MesajYaz("BASILAN YILDIZ",0x80);
	bekle(1500);
	}
    PORTA.0=0;
//----------------------------------------------------------------------
    PORTA.1=1;
    if(PORTB.0==1){

    MesajYaz("BASILAN BUTON 2",0x80);
	bekle(1500);
	}
    if(PORTB.1==1){

    MesajYaz("BASILAN BUTON 5",0x80);
	bekle(1500);
	}
    if(PORTB.2==1){

    MesajYaz("BASILAN BUTON 8",0x80);
	bekle(1500);
	}
    if(PORTB.3==1){

    MesajYaz("BASILAN BUTON 0",0x80);
	bekle(1500);
	}
    PORTA.1=0;
//---------------------------------------------------------------------------

   PORTA.2=1;
    if(PORTB.0==1){

    MesajYaz("BASILAN BUTON 3",0x80);
	bekle(1500);
	}
    if(PORTB.1==1){

    MesajYaz("BASILAN BUTON 6",0x80);
	bekle(1500);
	}
    if(PORTB.2==1){

    MesajYaz("BASILAN BUTON 9",0x80);
	bekle(1500);
	}
    if(PORTB.3==1){

    MesajYaz("BASILAN KARE",0x80);
	bekle(1500);
    
	}
    PORTA.2=0;


goto anadongu;
   	

}
   	
   void init()
{
    TRISA=0;	
	TRISB=0xFF;	
    TRISD=0X00;
	TRISE=0X00;
	
}
void bekle(unsigned long t)	//t milisaniye gecikme saðlar
{
	unsigned n;
	for(;t>0;t--)
		for(n=140;n>0;n--)
			nop();
}


void LcdKomut(unsigned kom)
{
	bekle(20);
	disp=kom;
	rs=0;
	e=0;
	e=1;
}

void LcdYaz(char c)
{
	bekle(100);
	disp=c;
	rs=1;
	e=0;
	e=1;
	bekle(1);	
}


void LcdInit()
{
	rw=0;
	e=1;
	rs=1;
	LcdKomut(0x38);
	LcdKomut(0x01);	//Clear display
	LcdKomut(0x0D); //Display,Cursor,Blink on
	LcdKomut(0x06); //Increment ddram adres, do not shift disp.
}

void MesajYaz(const char *msj,unsigned adr)
{
	unsigned i,j,k;
	i=0;
	while(msj[i]!=0)	i++;
	
	LcdKomut(adr);
	for(j=0;j<i;j++){
		LcdYaz(msj[j]);
		for(k=0;k<30;k++)nop();
	}
}
