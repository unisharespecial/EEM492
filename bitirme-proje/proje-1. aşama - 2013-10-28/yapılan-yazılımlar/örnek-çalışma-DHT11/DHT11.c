/*
 Project: Temperature and humidity measurements using DHT11
 MCU: PIC16F628A
 Clock: 4.0MHz external resonator
 MCLR is enabled
 Date: Jan 10, 2012
 Written by: Rajendra Bhatt (www.embedded-lab.com)
*/

// LCD module connections
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
  DataDir = 0;     // Data port is output
  Data    = 0;
  Delay_ms(25);
  Data    = 1;
  Delay_us(30);
  DataDir = 1;     // Data port is input

}

unsigned short CheckResponse(){
  TOUT = 0;
  TMR2 = 0;
  T2CON.TMR2ON = 1;      // start timer
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
   if(TMR2 > 40) num |= 1<<(7-i);  // If time > 40us, Data is 1
  }
  return num;
}

void interrupt(){
  if(PIR1.TMR2IF){
   TOUT = 1;
   T2CON.TMR2ON = 0; // stop timer
   PIR1.TMR2IF  = 0; // Clear TMR0 interrupt flag
  }
}

void main() {
  unsigned short check;
  TRISB = 0b00000000;
  PORTB = 0;
  TRISA = 0b00100001;
  CMCON = 7;
  INTCON.GIE = 1;    //Enable global interrupt
  INTCON.PEIE = 1;   //Enable peripheral interrupt
  // Configure Timer2 module
  PIE1.TMR2IE = 1;  // Enable Timer2 interrupt
  T2CON = 0;        // Prescaler 1:1, and Timer2 is off initially
  PIR1.TMR2IF =0;   // Clear TMR INT Flag bit
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
     // Check for error in Data reception
     if (CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))
     {
      message1[7]  = T_Byte1/10 + 48;
      message1[8]  = T_Byte1%10 + 48;
      message1[10] = T_Byte2/10 + 48;
      message2[7]  = RH_Byte1/10 + 48;
      message2[8]  = RH_Byte1%10 + 48;
      message2[10] = RH_Byte2/10 + 48;
      message1[11] = 223;     // Degree symbol
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