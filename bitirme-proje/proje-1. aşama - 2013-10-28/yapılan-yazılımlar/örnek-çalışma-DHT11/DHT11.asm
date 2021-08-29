
_StartSignal:

;DHT11.c,31 :: 		void StartSignal(){
;DHT11.c,32 :: 		DataDir = 0;     // Data port is output
	BCF        TRISA0_bit+0, 0
;DHT11.c,33 :: 		Data    = 0;
	BCF        RA0_bit+0, 0
;DHT11.c,34 :: 		Delay_ms(25);
	MOVLW      33
	MOVWF      R12+0
	MOVLW      118
	MOVWF      R13+0
L_StartSignal0:
	DECFSZ     R13+0, 1
	GOTO       L_StartSignal0
	DECFSZ     R12+0, 1
	GOTO       L_StartSignal0
	NOP
;DHT11.c,35 :: 		Data    = 1;
	BSF        RA0_bit+0, 0
;DHT11.c,36 :: 		Delay_us(30);
	MOVLW      9
	MOVWF      R13+0
L_StartSignal1:
	DECFSZ     R13+0, 1
	GOTO       L_StartSignal1
	NOP
	NOP
;DHT11.c,37 :: 		DataDir = 1;     // Data port is input
	BSF        TRISA0_bit+0, 0
;DHT11.c,39 :: 		}
L_end_StartSignal:
	RETURN
; end of _StartSignal

_CheckResponse:

;DHT11.c,41 :: 		unsigned short CheckResponse(){
;DHT11.c,42 :: 		TOUT = 0;
	CLRF       _TOUT+0
;DHT11.c,43 :: 		TMR2 = 0;
	CLRF       TMR2+0
;DHT11.c,44 :: 		T2CON.TMR2ON = 1;      // start timer
	BSF        T2CON+0, 2
;DHT11.c,45 :: 		while(!Data && !TOUT);
L_CheckResponse2:
	BTFSC      RA0_bit+0, 0
	GOTO       L_CheckResponse3
	MOVF       _TOUT+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_CheckResponse3
L__CheckResponse32:
	GOTO       L_CheckResponse2
L_CheckResponse3:
;DHT11.c,46 :: 		if (TOUT) return 0;
	MOVF       _TOUT+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_CheckResponse6
	CLRF       R0+0
	GOTO       L_end_CheckResponse
L_CheckResponse6:
;DHT11.c,48 :: 		TMR2 = 0;
	CLRF       TMR2+0
;DHT11.c,49 :: 		while(Data && !TOUT);
L_CheckResponse8:
	BTFSS      RA0_bit+0, 0
	GOTO       L_CheckResponse9
	MOVF       _TOUT+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_CheckResponse9
L__CheckResponse31:
	GOTO       L_CheckResponse8
L_CheckResponse9:
;DHT11.c,50 :: 		if (TOUT) return 0;
	MOVF       _TOUT+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_CheckResponse12
	CLRF       R0+0
	GOTO       L_end_CheckResponse
L_CheckResponse12:
;DHT11.c,52 :: 		T2CON.TMR2ON = 0;
	BCF        T2CON+0, 2
;DHT11.c,53 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;DHT11.c,56 :: 		}
L_end_CheckResponse:
	RETURN
; end of _CheckResponse

_ReadByte:

;DHT11.c,58 :: 		unsigned short ReadByte(){
;DHT11.c,59 :: 		unsigned short num = 0, t;
	CLRF       ReadByte_num_L0+0
;DHT11.c,60 :: 		DataDir = 1;
	BSF        TRISA0_bit+0, 0
;DHT11.c,61 :: 		for (i=0; i<8; i++){
	CLRF       _i+0
L_ReadByte14:
	MOVLW      8
	SUBWF      _i+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_ReadByte15
;DHT11.c,62 :: 		while(!Data);
L_ReadByte17:
	BTFSC      RA0_bit+0, 0
	GOTO       L_ReadByte18
	GOTO       L_ReadByte17
L_ReadByte18:
;DHT11.c,63 :: 		TMR2 = 0;
	CLRF       TMR2+0
;DHT11.c,64 :: 		T2CON.TMR2ON = 1;
	BSF        T2CON+0, 2
;DHT11.c,65 :: 		while(Data);
L_ReadByte19:
	BTFSS      RA0_bit+0, 0
	GOTO       L_ReadByte20
	GOTO       L_ReadByte19
L_ReadByte20:
;DHT11.c,66 :: 		T2CON.TMR2ON = 0;
	BCF        T2CON+0, 2
;DHT11.c,67 :: 		if(TMR2 > 40) num |= 1<<(7-i);  // If time > 40us, Data is 1
	MOVF       TMR2+0, 0
	SUBLW      40
	BTFSC      STATUS+0, 0
	GOTO       L_ReadByte21
	MOVF       _i+0, 0
	SUBLW      7
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      R1+0
	MOVLW      1
	MOVWF      R0+0
	MOVF       R1+0, 0
L__ReadByte36:
	BTFSC      STATUS+0, 2
	GOTO       L__ReadByte37
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__ReadByte36
L__ReadByte37:
	MOVF       R0+0, 0
	IORWF      ReadByte_num_L0+0, 1
L_ReadByte21:
;DHT11.c,61 :: 		for (i=0; i<8; i++){
	INCF       _i+0, 1
;DHT11.c,68 :: 		}
	GOTO       L_ReadByte14
L_ReadByte15:
;DHT11.c,69 :: 		return num;
	MOVF       ReadByte_num_L0+0, 0
	MOVWF      R0+0
;DHT11.c,70 :: 		}
L_end_ReadByte:
	RETURN
; end of _ReadByte

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;DHT11.c,72 :: 		void interrupt(){
;DHT11.c,73 :: 		if(PIR1.TMR2IF){
	BTFSS      PIR1+0, 1
	GOTO       L_interrupt22
;DHT11.c,74 :: 		TOUT = 1;
	MOVLW      1
	MOVWF      _TOUT+0
;DHT11.c,75 :: 		T2CON.TMR2ON = 0; // stop timer
	BCF        T2CON+0, 2
;DHT11.c,76 :: 		PIR1.TMR2IF  = 0; // Clear TMR0 interrupt flag
	BCF        PIR1+0, 1
;DHT11.c,77 :: 		}
L_interrupt22:
;DHT11.c,78 :: 		}
L_end_interrupt:
L__interrupt39:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

;DHT11.c,80 :: 		void main() {
;DHT11.c,82 :: 		TRISB = 0b00000000;
	CLRF       TRISB+0
;DHT11.c,83 :: 		PORTB = 0;
	CLRF       PORTB+0
;DHT11.c,84 :: 		TRISA = 0b00100001;
	MOVLW      33
	MOVWF      TRISA+0
;DHT11.c,85 :: 		CMCON = 7;
	MOVLW      7
	MOVWF      CMCON+0
;DHT11.c,86 :: 		INTCON.GIE = 1;    //Enable global interrupt
	BSF        INTCON+0, 7
;DHT11.c,87 :: 		INTCON.PEIE = 1;   //Enable peripheral interrupt
	BSF        INTCON+0, 6
;DHT11.c,89 :: 		PIE1.TMR2IE = 1;  // Enable Timer2 interrupt
	BSF        PIE1+0, 1
;DHT11.c,90 :: 		T2CON = 0;        // Prescaler 1:1, and Timer2 is off initially
	CLRF       T2CON+0
;DHT11.c,91 :: 		PIR1.TMR2IF =0;   // Clear TMR INT Flag bit
	BCF        PIR1+0, 1
;DHT11.c,92 :: 		TMR2 = 0;
	CLRF       TMR2+0
;DHT11.c,93 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;DHT11.c,94 :: 		Lcd_Cmd(_Lcd_Clear);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DHT11.c,95 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DHT11.c,97 :: 		do {
L_main23:
;DHT11.c,98 :: 		Delay_ms(1000);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_main26:
	DECFSZ     R13+0, 1
	GOTO       L_main26
	DECFSZ     R12+0, 1
	GOTO       L_main26
	DECFSZ     R11+0, 1
	GOTO       L_main26
	NOP
	NOP
;DHT11.c,99 :: 		StartSignal();
	CALL       _StartSignal+0
;DHT11.c,100 :: 		check = CheckResponse();
	CALL       _CheckResponse+0
;DHT11.c,101 :: 		if (!check) {
	MOVF       R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main27
;DHT11.c,102 :: 		Lcd_Cmd(_Lcd_Clear);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DHT11.c,103 :: 		Lcd_Out(1, 1, "No response");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr1_DHT11+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DHT11.c,104 :: 		Lcd_Out(2, 1, "from the sensor");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr2_DHT11+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DHT11.c,105 :: 		}
	GOTO       L_main28
L_main27:
;DHT11.c,108 :: 		RH_Byte1 = ReadByte();
	CALL       _ReadByte+0
	MOVF       R0+0, 0
	MOVWF      _RH_Byte1+0
;DHT11.c,109 :: 		RH_Byte2 = ReadByte();
	CALL       _ReadByte+0
	MOVF       R0+0, 0
	MOVWF      _RH_Byte2+0
;DHT11.c,110 :: 		T_Byte1 = ReadByte();
	CALL       _ReadByte+0
	MOVF       R0+0, 0
	MOVWF      _T_Byte1+0
;DHT11.c,111 :: 		T_Byte2 = ReadByte();
	CALL       _ReadByte+0
	MOVF       R0+0, 0
	MOVWF      _T_Byte2+0
;DHT11.c,112 :: 		CheckSum = ReadByte();
	CALL       _ReadByte+0
	MOVF       R0+0, 0
	MOVWF      _CheckSum+0
;DHT11.c,114 :: 		if (CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF))
	MOVF       _RH_Byte2+0, 0
	ADDWF      _RH_Byte1+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVF       _T_Byte1+0, 0
	ADDWF      R1+0, 1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVF       _T_Byte2+0, 0
	ADDWF      R1+0, 1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      255
	ANDWF      R1+0, 0
	MOVWF      R3+0
	MOVF       R1+1, 0
	MOVWF      R3+1
	MOVLW      0
	ANDWF      R3+1, 1
	MOVLW      0
	XORWF      R3+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main41
	MOVF       R3+0, 0
	XORWF      R0+0, 0
L__main41:
	BTFSS      STATUS+0, 2
	GOTO       L_main29
;DHT11.c,116 :: 		message1[7]  = T_Byte1/10 + 48;
	MOVLW      10
	MOVWF      R4+0
	MOVF       _T_Byte1+0, 0
	MOVWF      R0+0
	CALL       _Div_8x8_U+0
	MOVLW      48
	ADDWF      R0+0, 0
	MOVWF      _message1+7
;DHT11.c,117 :: 		message1[8]  = T_Byte1%10 + 48;
	MOVLW      10
	MOVWF      R4+0
	MOVF       _T_Byte1+0, 0
	MOVWF      R0+0
	CALL       _Div_8x8_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVLW      48
	ADDWF      R0+0, 0
	MOVWF      _message1+8
;DHT11.c,118 :: 		message1[10] = T_Byte2/10 + 48;
	MOVLW      10
	MOVWF      R4+0
	MOVF       _T_Byte2+0, 0
	MOVWF      R0+0
	CALL       _Div_8x8_U+0
	MOVLW      48
	ADDWF      R0+0, 0
	MOVWF      _message1+10
;DHT11.c,119 :: 		message2[7]  = RH_Byte1/10 + 48;
	MOVLW      10
	MOVWF      R4+0
	MOVF       _RH_Byte1+0, 0
	MOVWF      R0+0
	CALL       _Div_8x8_U+0
	MOVLW      48
	ADDWF      R0+0, 0
	MOVWF      _message2+7
;DHT11.c,120 :: 		message2[8]  = RH_Byte1%10 + 48;
	MOVLW      10
	MOVWF      R4+0
	MOVF       _RH_Byte1+0, 0
	MOVWF      R0+0
	CALL       _Div_8x8_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVLW      48
	ADDWF      R0+0, 0
	MOVWF      _message2+8
;DHT11.c,121 :: 		message2[10] = RH_Byte2/10 + 48;
	MOVLW      10
	MOVWF      R4+0
	MOVF       _RH_Byte2+0, 0
	MOVWF      R0+0
	CALL       _Div_8x8_U+0
	MOVLW      48
	ADDWF      R0+0, 0
	MOVWF      _message2+10
;DHT11.c,122 :: 		message1[11] = 223;     // Degree symbol
	MOVLW      223
	MOVWF      _message1+11
;DHT11.c,123 :: 		Lcd_Cmd(_Lcd_Clear);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DHT11.c,124 :: 		Lcd_Out(1, 1, message1);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message1+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DHT11.c,125 :: 		Lcd_Out(2, 1, message2);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message2+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DHT11.c,126 :: 		}
	GOTO       L_main30
L_main29:
;DHT11.c,129 :: 		Lcd_Cmd(_Lcd_Clear);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;DHT11.c,130 :: 		Lcd_Out(1, 1, "Checksum Error!");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr3_DHT11+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DHT11.c,131 :: 		Lcd_Out(2, 1, "Trying Again ...");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr4_DHT11+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;DHT11.c,132 :: 		}
L_main30:
;DHT11.c,133 :: 		}
L_main28:
;DHT11.c,135 :: 		}while(1);
	GOTO       L_main23
;DHT11.c,136 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
