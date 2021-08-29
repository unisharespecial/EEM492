
; CC8E Version 1.3E, Copyright (c) B Knudsen Data
; C compiler for the PIC18 microcontrollers
; ************  27. Dec 2012  16:07  *************

	processor  PIC18F452
	radix  DEC

TBLPTR      EQU   0xFF6
TABLAT      EQU   0xFF5
Zero_       EQU   2
TRISE       EQU   0xF96
TRISD       EQU   0xF95
TRISB       EQU   0xF93
TRISA       EQU   0xF92
PORTB       EQU   0xF81
PORTA       EQU   0xF80
e           EQU   0
rs          EQU   1
rw          EQU   2
disp        EQU   0xF83
t           EQU   0x06
n           EQU   0x08
kom         EQU   0x05
c           EQU   0x05
msj         EQU   0x00
adr         EQU   0x01
i           EQU   0x02
j           EQU   0x03
k           EQU   0x04
ci          EQU   0x05

	GOTO main

  ; FILE eray.c
			;//ERAY KULOÐLU/20895288	
			;//Keypad uygulamasý 2012
			;void init();
			;void bekle(unsigned long t);
			;void LcdInit();
			;void LcdYaz(char );
			;void LcdKomut(unsigned kom);
			;void MesajYaz(const char *msj,unsigned adr);
			;
			;bit e @ PORTE.0, rs @ PORTE.1, rw @ PORTE.2;
			;unsigned disp @ PORTD;
			;
			;void main(){
main
			;	init();
	RCALL init
			;	LcdInit();
	RCALL LcdInit
			;anadongu:
			;    
			;	PORTA.0=1;
m001	BSF   PORTA,0,0
			;    if(PORTB.0==1){
	BTFSS PORTB,0,0
	BRA   m002
			;
			;    MesajYaz("BASILAN BUTON 1",0x80);
	CLRF  msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.1==1){
m002	BTFSS PORTB,1,0
	BRA   m003
			;
			;    MesajYaz("BASILAN BUTON 4",0x80);
	MOVLW 16
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.2==1){
m003	BTFSS PORTB,2,0
	BRA   m004
			;
			;    MesajYaz("BASILAN BUTON 7",0x80);
	MOVLW 32
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.3==1){
m004	BTFSS PORTB,3,0
	BRA   m005
			;
			;    MesajYaz("BASILAN YILDIZ",0x80);
	MOVLW 48
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    PORTA.0=0;
m005	BCF   PORTA,0,0
			;//----------------------------------------------------------------------
			;    PORTA.1=1;
	BSF   PORTA,1,0
			;    if(PORTB.0==1){
	BTFSS PORTB,0,0
	BRA   m006
			;
			;    MesajYaz("BASILAN BUTON 2",0x80);
	MOVLW 63
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.1==1){
m006	BTFSS PORTB,1,0
	BRA   m007
			;
			;    MesajYaz("BASILAN BUTON 5",0x80);
	MOVLW 79
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.2==1){
m007	BTFSS PORTB,2,0
	BRA   m008
			;
			;    MesajYaz("BASILAN BUTON 8",0x80);
	MOVLW 95
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.3==1){
m008	BTFSS PORTB,3,0
	BRA   m009
			;
			;    MesajYaz("BASILAN BUTON 0",0x80);
	MOVLW 111
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    PORTA.1=0;
m009	BCF   PORTA,1,0
			;//---------------------------------------------------------------------------
			;
			;   PORTA.2=1;
	BSF   PORTA,2,0
			;    if(PORTB.0==1){
	BTFSS PORTB,0,0
	BRA   m010
			;
			;    MesajYaz("BASILAN BUTON 3",0x80);
	MOVLW 127
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.1==1){
m010	BTFSS PORTB,1,0
	BRA   m011
			;
			;    MesajYaz("BASILAN BUTON 6",0x80);
	MOVLW 143
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.2==1){
m011	BTFSS PORTB,2,0
	BRA   m012
			;
			;    MesajYaz("BASILAN BUTON 9",0x80);
	MOVLW 159
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;	}
			;    if(PORTB.3==1){
m012	BTFSS PORTB,3,0
	BRA   m013
			;
			;    MesajYaz("BASILAN KARE",0x80);
	MOVLW 175
	MOVWF msj,0
	MOVLW 128
	RCALL MesajYaz
			;	bekle(1500);
	MOVLW 220
	MOVWF t,0
	MOVLW 5
	MOVWF t+1,0
	RCALL bekle
			;    
			;	}
			;    PORTA.2=0;
m013	BCF   PORTA,2,0
			;
			;
			;goto anadongu;
	BRA   m001
			;   	
			;
			;}
			;   	
			;   void init()
			;{
init
			;    TRISA=0;	
	CLRF  TRISA,0
			;	TRISB=0xFF;	
	SETF  TRISB,0
			;    TRISD=0X00;
	CLRF  TRISD,0
			;	TRISE=0X00;
	CLRF  TRISE,0
			;	
			;}
	RETURN
			;void bekle(unsigned long t)	//t milisaniye gecikme saðlar
			;{
bekle
			;	unsigned n;
			;	for(;t>0;t--)
m014	MOVF  t,W,0
	IORWF t+1,W,0
	BTFSC 0xFD8,Zero_,0
	BRA   m017
			;		for(n=140;n>0;n--)
	MOVLW 140
	MOVWF n,0
m015	MOVF  n,1,0
	BTFSC 0xFD8,Zero_,0
	BRA   m016
			;			nop();
	NOP  
	DECF  n,1,0
	BRA   m015
m016	DECF  t,1,0
	MOVLW 0
	SUBWFB t+1,1,0
	BRA   m014
			;}
m017	RETURN
			;
			;
			;void LcdKomut(unsigned kom)
			;{
LcdKomut
	MOVWF kom,0
			;	bekle(20);
	MOVLW 20
	MOVWF t,0
	CLRF  t+1,0
	RCALL bekle
			;	disp=kom;
	MOVFF kom,disp
			;	rs=0;
	BCF   0xF84,rs,0
			;	e=0;
	BCF   0xF84,e,0
			;	e=1;
	BSF   0xF84,e,0
			;}
	RETURN
			;
			;void LcdYaz(char c)
			;{
LcdYaz
	MOVWF c,0
			;	bekle(100);
	MOVLW 100
	MOVWF t,0
	CLRF  t+1,0
	RCALL bekle
			;	disp=c;
	MOVFF c,disp
			;	rs=1;
	BSF   0xF84,rs,0
			;	e=0;
	BCF   0xF84,e,0
			;	e=1;
	BSF   0xF84,e,0
			;	bekle(1);	
	MOVLW 1
	MOVWF t,0
	CLRF  t+1,0
	BRA   bekle
			;}
			;
			;
			;void LcdInit()
			;{
LcdInit
			;	rw=0;
	BCF   0xF84,rw,0
			;	e=1;
	BSF   0xF84,e,0
			;	rs=1;
	BSF   0xF84,rs,0
			;	LcdKomut(0x38);
	MOVLW 56
	RCALL LcdKomut
			;	LcdKomut(0x01);	//Clear display
	MOVLW 1
	RCALL LcdKomut
			;	LcdKomut(0x0D); //Display,Cursor,Blink on
	MOVLW 13
	RCALL LcdKomut
			;	LcdKomut(0x06); //Increment ddram adres, do not shift disp.
	MOVLW 6
	BRA   LcdKomut
			;}
			;
			;void MesajYaz(const char *msj,unsigned adr)
			;{
MesajYaz
	MOVWF adr,0
			;	unsigned i,j,k;
			;	i=0;
	CLRF  i,0
			;	while(msj[i]!=0)	i++;
m018	MOVF  i,W,0
	ADDWF msj,W,0
	RCALL _const1
	XORLW 0
	BTFSC 0xFD8,Zero_,0
	BRA   m019
	INCF  i,1,0
	BRA   m018
			;	
			;	LcdKomut(adr);
m019	MOVF  adr,W,0
	RCALL LcdKomut
			;	for(j=0;j<i;j++){
	CLRF  j,0
m020	MOVF  i,W,0
	CPFSLT j,0
	BRA   m023
			;		LcdYaz(msj[j]);
	MOVF  j,W,0
	ADDWF msj,W,0
	RCALL _const1
	RCALL LcdYaz
			;		for(k=0;k<30;k++)nop();
	CLRF  k,0
m021	MOVLW 30
	CPFSLT k,0
	BRA   m022
	NOP  
	INCF  k,1,0
	BRA   m021
			;	}
m022	INCF  j,1,0
	BRA   m020
			;}
m023	RETURN
_const1
	MOVWF ci,0
	MOVF  ci,W,0
	ADDLW 226
	MOVWF TBLPTR,0
	MOVLW 1
	CLRF  TBLPTR+1,0
	ADDWFC TBLPTR+1,1,0
	CLRF  TBLPTR+2,0
	TBLRD *
	MOVF  TABLAT,W,0
	RETURN
	DW    0x4142
	DW    0x4953
	DW    0x414C
	DW    0x204E
	DW    0x5542
	DW    0x4F54
	DW    0x204E
	DW    0x31
	DW    0x4142
	DW    0x4953
	DW    0x414C
	DW    0x204E
	DW    0x5542
	DW    0x4F54
	DW    0x204E
	DW    0x34
	DW    0x4142
	DW    0x4953
	DW    0x414C
	DW    0x204E
	DW    0x5542
	DW    0x4F54
	DW    0x204E
	DW    0x37
	DW    0x4142
	DW    0x4953
	DW    0x414C
	DW    0x204E
	DW    0x4959
	DW    0x444C
	DW    0x5A49
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3220
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3520
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3820
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3020
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3320
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3620
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4220
	DW    0x5455
	DW    0x4E4F
	DW    0x3920
	DW    0x4200
	DW    0x5341
	DW    0x4C49
	DW    0x4E41
	DW    0x4B20
	DW    0x5241
	DW    0x45

	END


; *** KEY INFO ***

; 0x00011C    5 word(s)  0 % : init
; 0x000126   17 word(s)  0 % : bekle
; 0x00017A   11 word(s)  0 % : LcdInit
; 0x00015E   14 word(s)  0 % : LcdYaz
; 0x000148   11 word(s)  0 % : LcdKomut
; 0x000190   30 word(s)  0 % : MesajYaz
; 0x000004  140 word(s)  0 % : main
; 0x0001CC  105 word(s)  0 % : _const1

; RAM usage: 9 bytes (9 local), 1527 bytes free
; Maximum call level: 3
; Total of 335 code words (2 %)
