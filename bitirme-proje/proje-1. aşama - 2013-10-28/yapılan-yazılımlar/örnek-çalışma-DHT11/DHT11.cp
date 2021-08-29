#line 1 "C:/Users/raj/Desktop/EmbeddedLab_Code/MikroC_PIC/PIC16F628A/DHT11/DHT11.c"
#line 11 "C:/Users/raj/Desktop/EmbeddedLab_Code/MikroC_PIC/PIC16F628A/DHT11/DHT11.c"
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;
sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

sbit Data at RA0_bit;
sbit DataDir at TRISA0_bit;
char message1[] = "Temp = 00.0 C";
char message2[] = "RH   = 00.0 %";
unsigned short TOUT = 0, CheckSum, i;
unsigned short T_Byte1, T_Byte2, RH_Byte1, RH_Byte2;

void StartSignal(){
 DataDir = 0;
 Data = 0;
 Delay_ms(25);
 Data = 1;
 Delay_us(30);
 DataDir = 1;

}

unsigned short CheckResponse(){
 TOUT = 0;
 TMR2 = 0;
 T2CON.TMR2ON = 1;
 while(!Data && !TOUT);
 if (TOUT) return 0;
 else {
 TMR2 = 0;
 while(Data && !TOUT);
 if (TOUT) return 0;
 else {
 T2CON.TMR2ON = 0;
 return 1;
 }
 }
}

unsigned short ReadByte(){
 unsigned short num = 0, t;
 DataDir = 1;
 for (i=0; i<8; i++){
 while(!Data);
 TMR2 = 0;
 T2CON.TMR2ON = 1;
 while(Data);
 T2CON.TMR2ON = 0;
 if(TMR2 > 40) num |= 1<<(7-i);
 }
 return num;
}

void interrupt(){
 if(PIR1.TMR2IF){
 TOUT = 1;
 T2CON.TMR2ON = 0;
 PIR1.TMR2IF = 0;
 }
}

void main() {
 unsigned short check;
 TRISB = 0b00000000;
 PORTB = 0;
 TRISA = 0b00100001;
 CMCON = 7;
 INTCON.GIE = 1;
 INTCON.PEIE = 1;

 PIE1.TMR2IE = 1;
 T2CON = 0;
 PIR1.TMR2IF =0;
 TMR2 = 0;
 Lcd_Init();
 Lcd_Cmd(_Lcd_Clear);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 do {
 Delay_ms(1000);
 StartSignal();
 check = CheckResponse();
 if (!check) {
 Lcd_Cmd(_Lcd_Clear);
 Lcd_Out(1, 1, "No response");
 Lcd_Out(2, 1, "from the sensor");
 }
 else{

 RH_Byte1 = ReadByte();
 RH_Byte2 = ReadByte();
 T_Byte1 = ReadByte();
 T_Byte2 = ReadByte();
 CheckSum = ReadByte();

 if (CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))
 {
 message1[7] = T_Byte1/10 + 48;
 message1[8] = T_Byte1%10 + 48;
 message1[10] = T_Byte2/10 + 48;
 message2[7] = RH_Byte1/10 + 48;
 message2[8] = RH_Byte1%10 + 48;
 message2[10] = RH_Byte2/10 + 48;
 message1[11] = 223;
 Lcd_Cmd(_Lcd_Clear);
 Lcd_Out(1, 1, message1);
 Lcd_Out(2, 1, message2);
 }

 else{
 Lcd_Cmd(_Lcd_Clear);
 Lcd_Out(1, 1, "Checksum Error!");
 Lcd_Out(2, 1, "Trying Again ...");
 }
 }

 }while(1);
}
