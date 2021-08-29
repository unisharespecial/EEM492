
; PICBASIC PRO(TM) Compiler 2.60, (c) 1998, 2009 microEngineering Labs, Inc. All Rights Reserved. 
_USED			EQU	1

	INCLUDE	"C:\PBP2.60\16F877A.INC"


; Define statements.
#define		CODE_SIZE		 8
#define		OSC		 20
#define		LCD_DREG		  PORTB          
#define		LCD_DBIT		  0              
#define		LCD_EREG		  PORTB          
#define		LCD_EBIT		  5              
#define		LCD_RSREG		 PORTB          
#define		LCD_RSBIT		 4              
#define		LCD_BITS		  4              
#define		LCD_LINES		 2              
#define		LCD_COMMANDUS		 2000       
#define		LCD_DATAUS		 50            
#define		WRITE_INT		 1
#define		INTHAND		  INT_ENTRY
#define		DS1820_DECIMALS		    1      
#define		DS1820_VERIFYCRC		   YES    
#define		HSER_BAUD		    115200        
#define		HSER_RCSTA		   90h           
#define		HSER_TXSTA		   24h           
#define		HSER_CLROERR		 1             

RAM_START       		EQU	00020h
RAM_END         		EQU	001EFh
RAM_BANKS       		EQU	00004h
BANK0_START     		EQU	00020h
BANK0_END       		EQU	0007Fh
BANK1_START     		EQU	000A0h
BANK1_END       		EQU	000EFh
BANK2_START     		EQU	00110h
BANK2_END       		EQU	0016Fh
BANK3_START     		EQU	00190h
BANK3_END       		EQU	001EFh
EEPROM_START    		EQU	02100h
EEPROM_END      		EQU	021FFh

wsave           		EQU	RAM_START + 000h
HeaterDrives    		EQU	RAM_START + 001h
R0              		EQU	RAM_START + 005h
R1              		EQU	RAM_START + 007h
R2              		EQU	RAM_START + 009h
R3              		EQU	RAM_START + 00Bh
R4              		EQU	RAM_START + 00Dh
R5              		EQU	RAM_START + 00Fh
R6              		EQU	RAM_START + 011h
R7              		EQU	RAM_START + 013h
R8              		EQU	RAM_START + 015h
_RetAddr         		EQU	RAM_START + 017h
FLAGS           		EQU	RAM_START + 019h
fsave           		EQU	RAM_START + 01Ah
GOP             		EQU	RAM_START + 01Bh
HeatCycle       		EQU	RAM_START + 01Ch
psave           		EQU	RAM_START + 01Dh
RM1             		EQU	RAM_START + 01Eh
RM2             		EQU	RAM_START + 01Fh
RR1             		EQU	RAM_START + 020h
RR2             		EQU	RAM_START + 021h
ssave           		EQU	RAM_START + 022h
_DS1820_Buffer   		EQU	RAM_START + 023h
_pid_Ei          		EQU	RAM_START + 02Ch
_pid_I           		EQU	RAM_START + 034h
_pid_I_Clamp     		EQU	RAM_START + 03Ch
_pid_Kd          		EQU	RAM_START + 044h
_pid_Ki          		EQU	RAM_START + 04Ch
_pid_Kp          		EQU	RAM_START + 054h
_pid_IntCount    		EQU	RAM_START + 05Ch
wsave1          		EQU	RAM_START + 080h
_pid_LastError   		EQU	RAM_START + 081h
_pid_Out_Clamp   		EQU	RAM_START + 089h
_SetPoints       		EQU	RAM_START + 091h
_Temperatures    		EQU	RAM_START + 099h
_TempStr         		EQU	RAM_START + 0A1h
_pid_Ti          		EQU	RAM_START + 0A9h
_spModes         		EQU	RAM_START + 0ADh
_DS1820_DeviceReg		EQU	RAM_START + 0B1h
_DS1820_HoldW    		EQU	RAM_START + 0B3h
_pid_D           		EQU	RAM_START + 0B5h
_pid_Error       		EQU	RAM_START + 0B7h
_pid_index       		EQU	RAM_START + 0B9h
_pid_Out         		EQU	RAM_START + 0BBh
_pid_P           		EQU	RAM_START + 0BDh
T1              		EQU	RAM_START + 0BFh
T2              		EQU	RAM_START + 0C1h
_TempC           		EQU	RAM_START + 0C3h
_TempWD          		EQU	RAM_START + 0C5h
_Bvar            		EQU	RAM_START + 0C7h
_Char            		EQU	RAM_START + 0C8h
_DS1820_DeviceBit		EQU	RAM_START + 0C9h
_DS1820_Error    		EQU	RAM_START + 0CAh
_DS1820_Family   		EQU	RAM_START + 0CBh
_DS1820_Flags    		EQU	RAM_START + 0CCh
_DS1820_HoldB    		EQU	RAM_START + 0CDh
_DS1820_HoldBU   		EQU	RAM_START + 0CEh
_DS1820_TimeoutCount		EQU	RAM_START + 0CFh
_DS_CRC          		EQU	RAM_START + 0F0h
_DS_CRCData      		EQU	RAM_START + 0F1h
_EditChannel     		EQU	RAM_START + 0F2h
PB01            		EQU	RAM_START + 0F3h
PB02            		EQU	RAM_START + 0F4h
_pid_Channel     		EQU	RAM_START + 0F5h
_X               		EQU	RAM_START + 0F6h
_Y               		EQU	RAM_START + 0F7h
wsave2          		EQU	RAM_START + 00100h
wsave3          		EQU	RAM_START + 00180h
_Temp1           		EQU	_Temperatures
_Temp2           		EQU	_Temperatures + 002h
_Temp3           		EQU	_Temperatures + 004h
_Temp4           		EQU	_Temperatures + 006h
_SetPoint1       		EQU	_SetPoints
_SetPoint2       		EQU	_SetPoints + 002h
_SetPoint3       		EQU	_SetPoints + 004h
_SetPoint4       		EQU	_SetPoints + 006h
_DS1820_AlarmH   		EQU	_DS1820_Buffer + 002h
_DS1820_AlarmL   		EQU	_DS1820_Buffer + 003h
_DS1820_Config   		EQU	_DS1820_Buffer + 004h
_DS1820_Cremain  		EQU	_DS1820_Buffer + 006h
_DS1820_CountPC  		EQU	_DS1820_Buffer + 007h
_DS1820_CRC      		EQU	_DS1820_Buffer + 008h
_spMode1         		EQU	_spModes
_spMode2         		EQU	_spModes + 001h
_spMode3         		EQU	_spModes + 002h
_spMode4         		EQU	_spModes + 003h
_HeatDrive1      		EQU	 HeaterDrives
_HeatDrive2      		EQU	 HeaterDrives + 001h
_HeatDrive3      		EQU	 HeaterDrives + 002h
_HeatDrive4      		EQU	 HeaterDrives + 003h
#define _SensorActive    	 PB01, 000h
_Temp            		EQU	_TempC
_PORTL           		EQU	 PORTB
_PORTH           		EQU	 PORTC
_TRISL           		EQU	 TRISB
_TRISH           		EQU	 TRISC
_DS_ByteCount    		EQU	_DS1820_HoldW + 001h
_DS_BitCount     		EQU	_DS1820_HoldW
_DS1820_HoldW??HIGHBYTE		EQU	_DS1820_HoldW + 001h
_DS1820_HoldW??LOWBYTE		EQU	_DS1820_HoldW
_R0??LOWBYTE     		EQU	 R0
#define _TempSensor1     	_PORTD??0
#define _TempSensor2     	_PORTD??1
#define _TempSensor3     	_PORTD??2
#define _TempSensor4     	_PORTD??3
#define _HeaterOut1      	_PORTD??4
#define _HeaterOut2      	_PORTD??5
#define _HeaterOut3      	_PORTD??6
#define _HeaterOut4      	_PORTD??7
#define _Eprom1          	_PORTB??6
#define _Eprom2          	_PORTB??7
#define _RTC1            	_PORTC??0
#define _RTC2            	_PORTC??1
#define _POT1            	_PORTA??0
#define _POT2            	_PORTA??1
#define _POT3            	_PORTA??2
#define _POT4            	_PORTA??3
#define _Switch1         	_PORTA??4
#define _Switch2         	_PORTA??5
#define _Switch3         	_PORTE??0
#define _Switch4         	_PORTE??1
#define _Switch5         	_PORTE??2
#define _Switch6         	_PORTC??2
#define _Switch7         	_PORTC??6
#define _Switch8         	_PORTC??7
#define _Serviced        	 PB02, 000h
#define _DS1820_Done     	_DS1820_Flags??0
#define _DS1820_Waiting  	_DS1820_Flags??1
#define _DS1820_Alarm    	_DS1820_Flags??2
#define _DS1820_HighAlarm	_DS1820_Flags??3
#define _DS1820_LowAlarm 	_DS1820_Flags??4
#define _DS1820_Sign     	_DS1820_Flags??5
#define _DS1820_Parasite 	_DS1820_Flags??6
#define _DS1820_FAM_Error	_DS1820_Error??0
#define _DS1820_TimedOut 	_DS1820_Error??1
#define _DS1820_NotValid 	_DS1820_Error??2
#define _DS1820_WriteFailed	_DS1820_Error??3
#define _DS1820_CRCfailed	_DS1820_Error??4
#define _DS_TestBit      	 PB01, 005h
#define _DS_CRCpassed    	 PB01, 004h
#define _pid_Sign        	 PB01, 007h
#define _RCIF            	_PIR1??5
#define _GIE             	_INTCON??7
#define _FlashStar       	 PB01, 006h
#define _PORTD??0        	 PORTD, 000h
#define _PORTD??1        	 PORTD, 001h
#define _PORTD??2        	 PORTD, 002h
#define _PORTD??3        	 PORTD, 003h
#define _PORTD??4        	 PORTD, 004h
#define _PORTD??5        	 PORTD, 005h
#define _PORTD??6        	 PORTD, 006h
#define _PORTD??7        	 PORTD, 007h
#define _PORTB??6        	 PORTB, 006h
#define _PORTB??7        	 PORTB, 007h
#define _PORTC??0        	 PORTC, 000h
#define _PORTC??1        	 PORTC, 001h
#define _PORTA??0        	 PORTA, 000h
#define _PORTA??1        	 PORTA, 001h
#define _PORTA??2        	 PORTA, 002h
#define _PORTA??3        	 PORTA, 003h
#define _PORTA??4        	 PORTA, 004h
#define _PORTA??5        	 PORTA, 005h
#define _PORTE??0        	 PORTE, 000h
#define _PORTE??1        	 PORTE, 001h
#define _PORTE??2        	 PORTE, 002h
#define _PORTC??2        	 PORTC, 002h
#define _PORTC??6        	 PORTC, 006h
#define _PORTC??7        	 PORTC, 007h
#define _DS1820_Flags??0 	_DS1820_Flags, 000h
#define _DS1820_Flags??1 	_DS1820_Flags, 001h
#define _DS1820_Flags??2 	_DS1820_Flags, 002h
#define _DS1820_Flags??3 	_DS1820_Flags, 003h
#define _DS1820_Flags??4 	_DS1820_Flags, 004h
#define _DS1820_Flags??5 	_DS1820_Flags, 005h
#define _DS1820_Flags??6 	_DS1820_Flags, 006h
#define _DS1820_Error??0 	_DS1820_Error, 000h
#define _DS1820_Error??1 	_DS1820_Error, 001h
#define _DS1820_Error??2 	_DS1820_Error, 002h
#define _DS1820_Error??3 	_DS1820_Error, 003h
#define _DS1820_Error??4 	_DS1820_Error, 004h
#define _DS1820_Raw??15  	 DS1820_Raw + 001h, 007h
#define _TempC??15       	_TempC + 001h, 007h
#define _DS_CRC??0       	_DS_CRC, 000h
#define _DS_CRCData??0   	_DS_CRCData, 000h
#define _DS_CRC??7       	_DS_CRC, 007h
#define _R0??BIT0        	 R0, 000h
#define _pid_Error??15   	_pid_Error + 001h, 007h
#define _pid_Ei??0       	_pid_Ei, 000h
#define _pid_I??0        	_pid_I, 000h
#define _pid_D??15       	_pid_D + 001h, 007h
#define _pid_Out??15     	_pid_Out + 001h, 007h
#define _PIR1??5         	 PIR1, 005h
#define _INTCON??7       	 INTCON, 007h
#define _TempWD??15      	_TempWD + 001h, 007h

; Constants.
_DS18B20_9bit    		EQU	0001Fh
_DS18B20_10bit   		EQU	0003Fh
_DS18B20_11bit   		EQU	0005Fh
_DS18B20_12bit   		EQU	0007Fh
_CMD_SearchROM   		EQU	000F0h
_CMD_ReadROM     		EQU	00033h
_CMD_MatchROM    		EQU	00055h
_CMD_SkipROM     		EQU	000CCh
_CMD_AlarmSearch 		EQU	000ECh
_CMD_Convert     		EQU	00044h
_CMD_WritePAD    		EQU	0004Eh
_CMD_ReadPAD     		EQU	000BEh
_CMD_CopyPAD     		EQU	00048h
_CMD_RecallEE    		EQU	000B8h
_CMD_ReadPower   		EQU	000B4h
_OW_NoReset      		EQU	00000h
_OW_PreReset     		EQU	00001h
_OW_PostReset    		EQU	00002h
_OW_BitData      		EQU	00004h
_Fam_DS1820      		EQU	00010h
_Fam_DS18S20     		EQU	00010h
_Fam_DS18B20     		EQU	00028h
_PID_Channels    		EQU	00004h
_ColumnWidth     		EQU	0000Ah
_TL              		EQU	000DAh
_HL              		EQU	000C4h
_TR              		EQU	000BFh
_VL              		EQU	000B3h
_BL              		EQU	000C0h
_BR              		EQU	000D9h

; EEPROM data.
	ORG EEPROM_START

_EE_spMode1	EQU	$
	DE	001h
_EE_SetPoint1	EQU	$
	DE LOW	00104h
	DE HIGH	00104h
_EE_pid_Kp1	EQU	$
	DE LOW	00700h
	DE HIGH	00700h
_EE_pid_Ki1	EQU	$
	DE LOW	080h
	DE HIGH	080h
_EE_pid_Kd1	EQU	$
	DE LOW	00200h
	DE HIGH	00200h
_EE_pid_Ti1	EQU	$
	DE	008h
_EE_pid_I_Clamp1	EQU	$
	DE	07Dh
_EE_pid_Out_Clamp1	EQU	$
	DE LOW	0FFh
	DE HIGH	0FFh
_EE_spMode2	EQU	$
	DE	001h
_EE_SetPoint2	EQU	$
	DE LOW	00104h
	DE HIGH	00104h
_EE_pid_Kp2	EQU	$
	DE LOW	00700h
	DE HIGH	00700h
_EE_pid_Ki2	EQU	$
	DE LOW	080h
	DE HIGH	080h
_EE_pid_Kd2	EQU	$
	DE LOW	00200h
	DE HIGH	00200h
_EE_pid_Ti2	EQU	$
	DE	008h
_EE_pid_I_Clamp2	EQU	$
	DE	07Dh
_EE_pid_Out_Clamp2	EQU	$
	DE LOW	0FFh
	DE HIGH	0FFh
_EE_spMode3	EQU	$
	DE	001h
_EE_SetPoint3	EQU	$
	DE LOW	00104h
	DE HIGH	00104h
_EE_pid_Kp3	EQU	$
	DE LOW	00700h
	DE HIGH	00700h
_EE_pid_Ki3	EQU	$
	DE LOW	080h
	DE HIGH	080h
_EE_pid_Kd3	EQU	$
	DE LOW	00200h
	DE HIGH	00200h
_EE_pid_Ti3	EQU	$
	DE	008h
_EE_pid_I_Clamp3	EQU	$
	DE	07Dh
_EE_pid_Out_Clamp3	EQU	$
	DE LOW	0FFh
	DE HIGH	0FFh
_EE_spMode4	EQU	$
	DE	001h
_EE_SetPoint4	EQU	$
	DE LOW	00104h
	DE HIGH	00104h
_EE_pid_Kp4	EQU	$
	DE LOW	00700h
	DE HIGH	00700h
_EE_pid_Ki4	EQU	$
	DE LOW	080h
	DE HIGH	080h
_EE_pid_Kd4	EQU	$
	DE LOW	00125h
	DE HIGH	00125h
_EE_pid_Ti4	EQU	$
	DE	008h
_EE_pid_I_Clamp4	EQU	$
	DE	0FAh
_EE_pid_Out_Clamp4	EQU	$
	DE LOW	0FFh
	DE HIGH	0FFh

	INCLUDE	"PID_4C~1.MAC"
	INCLUDE	"C:\PBP2.60\PBPPIC14.LIB"

	CLEAR?	

	ASM?
   __config _HS_OSC & _WDT_ON & _LVP_OFF & _CP_OFF

	ENDASM?

	CLEAR?	

	ASM?

asm = 0
ASM = 0
pbp = 1
PBP = 1
YES = 1
yes = 1
NO = 0
no = 0


	ENDASM?


	ASM?

  #define INT_INT   INTCON,INTF     ;-- INT External Interrupt
  #define RBC_INT   INTCON,RBIF     ;-- RB Port Change Interrupt
  #define TMR0_INT  INTCON,T0IF     ;-- TMR0 Overflow Interrupt 16F
  #define TMR1_INT  PIR1,TMR1IF     ;-- TMR1 Overflow Interrupt
  #define TMR2_INT  PIR1,TMR2IF     ;-- TMR2 to PR2 Match Interrupt
  #define TX_INT    PIR1,TXIF       ;-- USART Transmit Interrupt
  #define RX_INT    PIR1,RCIF       ;-- USART Receive Interrupt
  #define CMP_INT   PIR2,CMIF       ;-- Comparator Interrupt
  #define EE_INT    PIR2,EEIF       ;-- EEPROM/FLASH Write Operation Interrupt
  #define BUS_INT   PIR2,BCLIF      ;-- Bus Collision Interrupt
  #define PSP_INT   PIR1,PSPIF      ;-- Parallel Slave Port Read/Write Interrupt
  #define AD_INT    PIR1,ADIF       ;-- A/D Converter Interrupt
  #define SSP_INT   PIR1,SSPIF      ;-- Master Synchronous Serial Port Interrupt
  #define CCP1_INT  PIR1,CCP1IF     ;-- CCP1 Interrupt
  #define CCP2_INT  PIR2,CCP2IF     ;-- CCP2 Interrupt



	ENDASM?


	ASM?

INT_Source  macro  IFR, IFB, IER, IEB
    if ((IflagReg == IFR) && (IflagBit == IFB))
  list  
INT_Flag_Reg = IFR
INT_Flag_Bit = IFB
INT_Enable_Reg = IER
INT_Enable_Bit = IEB
Found = YES
    endif
;  nolist  
    endm 


	ENDASM?


	ASM?

;-------------------------------------------------------------------------------
GetIntInfo  macro  IflagReg, IflagBit

Found = NO
; nolist
  ifdef INTF    ;----{ INT External Interrupt }----------------[INTCON, INTF]---
      INT_Source  INTCON, INTF, INTCON, INTE
  endif
  ifdef RBIF    ;----{ RB Port Change Interrupt }--------------[INTCON, RBIF]---
      INT_Source  INTCON, RBIF, INTCON, RBIE
  endif
  ifdef T0IF    ;----{ TMR0 Overflow Interrupt }-------------[INTCON, TMR0IF]---
      INT_Source  INTCON, T0IF, INTCON, T0IE
  endif
  ifdef TMR1IF  ;----{ TMR1 Overflow Interrupt }---------------[PIR1, TMR1IF]---
      INT_Source  PIR1, TMR1IF, PIE1, TMR1IE
  endif
  ifdef TMR2IF  ;----{ TMR2 to PR2 Match Interrupt }-----------[PIR1, TMR2IF]---
      INT_Source  PIR1, TMR2IF, PIE1, TMR2IE
  endif
  ifdef TXIF    ;----{ USART Transmit Interrupt }----------------[PIR1, TXIF]---
      INT_Source  PIR1, TXIF, PIE1, TXIE
  endif
  ifdef RCIF    ;----{ USART Receive Interrupt }------------------[PIR1 RCIF]---
          INT_Source  PIR1, RCIF, PIE1, RCIE
  endif
  ifdef CMIF    ;----{ Comparator Interrupt }--------------------[PIR2, CMIF]---
      ifdef PIR2
          INT_Source  PIR2, CMIF, PIE2, CMIE
      else
          INT_Source  PIR1, CMIF, PIE1, CMIE
      endif
  endif
  ifdef EEIF    ;---{ EEPROM/FLASH Write Operation Interrupt }---[PIR2, EEIF]---
      ifdef PIR2
          INT_Source  PIR2, EEIF, PIE2, EEIE
      else
          INT_Source  PIR1, EEIF, PIE1, EEIE
      endif
  endif
  ifdef BCLIF   ;----{ Bus Collision Interrupt }----------------[PIR2, BCLIF]---
      INT_Source  PIR2, BCLIF, PIE2, BCLIE
  endif
  ifdef PSPIF   ;--{ Parallel Slave Port Read/Write Interrupt }--[PIR1, PSPIF]--
      INT_Source  PIR1, PSPIF, PIE1, PSPIE
  endif
  ifdef ADIF   ;----{ A/D Converter Interrupt }------------------[PIR1, ADIF]---
      INT_Source  PIR1, ADIF, PIE1, ADIE
  endif
  ifdef SSPIF  ;----{ Master Synchronous Serial Port Interrupt }--[PIR1, SSPIF]-
      INT_Source  PIR1, SSPIF, PIE1, SSPIE
  endif
  ifdef CCP1IF ;----{ CCP1 Interrupt }-------------------------[PIR1, CCP1IF]---
      INT_Source  PIR1, CCP1IF, PIE1, CCP1IE
  endif
  ifdef CCP2IF ;----{ CCP2 Interrupt Flag }--------------------[PIR2, CCP2IF]---
      INT_Source  PIR2, CCP2IF, PIE2, CCP2IE
  endif
    
  list
    endm
  list  


	ENDASM?


	ASM?

;---[Returns the Address of a Label as a Word]----------------------------------
GetAddress macro Label, Wout
    CHK?RP Wout
    movlw low Label          ; get low byte
    movwf Wout
    movlw High Label         ; get high byte
    movwf Wout + 1
    endm

;---[find correct bank for a BIT variable]--------------------------------------
CHKRP?T  macro reg, bit
        CHK?RP  reg
    endm
    
;---[This creates the main Interrupt Service Routine (ISR)]---------------------
INT_CREATE  macro
  local OverCREATE
    goto OverCREATE
INT_ENTRY  
    IF (CODE_SIZE <= 2)
        movwf   wsave       ; 1 copy W to wsave register
        swapf   STATUS,W    ; 2 swap status reg to be saved into W
        clrf    STATUS      ; 3 change to bank 0 regardless of current bank
        movwf   ssave       ; 4 save status reg to a bank 0 register
        movf    PCLATH,W    ; 5 move PCLATH reg to be saved into W reg
        movwf   psave       ; 6 save PCLATH reg to a bank 0 register
    EndIF
    movf      FSR,W         ; 7 move FSR reg to be saved into W reg
    movwf     fsave         ; 8 save FSR reg to a bank 0 register
;    clrf    STATUS          ; BANK 0
PREV_BANK = 0

List_Start
    RST?RP
    CHKRP?T  _Serviced
    bcf      _Serviced

    INT_LIST                ; Expand the users list of interrupt handlers
                            ; INT_LIST macro must be defined in main program
    
    CHKRP?T  _Serviced
    btfsc    _Serviced
    goto List_Start

    ifdef ReEnterUsed       ; if ReEnterPBP.bas was included in the main program
        CHKRP?T  _VarsSaved
        btfss    _VarsSaved   ; if PBP system vars have been saved 
        goto     INT_EXIT
        GetAddress  INT_EXIT, _RetAddr
        L?GOTO   _RestorePBP   ; Restore PBP system Vars
    endif
    
INT_EXIT
    clrf    STATUS          ; BANK 0
PREV_BANK = 0
    MOVF    fsave,W         ; Restore the FSR reg
    MOVWF   FSR
    Movf    psave,w         ; Restore the PCLATH reg
    Movwf   PCLATH
    swapf   ssave,w         ; Restore the STATUS reg
    movwf   STATUS
    swapf   wsave,f
    swapf   wsave,w         ; Restore W reg
    Retfie                  ; Exit the interrupt routine

OverCREATE
    bsf      INTCON, 6      ; Enable Peripheral interrupts
    bsf      INTCON, 7      ; Enable Global interrupts
    endm
    


	ENDASM?


	ASM?

;---[Add an Interrupt Source to the user's list of INT Handlers]----------------
INT_Handler  macro  IntFlagReg, IntFlagBit, Label, Type, Reset
  list
    local AfterSave, AfterRestore, NoInt
        GetIntInfo   IntFlagReg, IntFlagBit
        if (Found == YES)
            CLRWDT
            CHK?RP   INT_Enable_Reg
            btfss    INT_Enable_Reg, INT_Enable_Bit  ; if the INT is enabled
            goto   NoInt
            CHK?RP   INT_Flag_Reg                    
            btfss    INT_Flag_Reg, INT_Flag_Bit      ; and the Flag set?
            goto     NoInt
    CHKRP?T  _Serviced
    bsf      _Serviced
            
            if (Type == PBP)                         ; If INT handler is PBP
                ifdef ReEnterUsed
                    GetAddress  AfterSave, _RetAddr  
                    L?GOTO  _SavePBP                 ; Save PBP system Vars
AfterSave                    
                    clrf    STATUS
PREV_BANK = 0
                else
                    error ReEnterPBP must be INCLUDEd to use PBP interrupts
                endif
            endif
            GetAddress  AfterRestore, _RetAddr       ; save return address
            L?GOTO   Label                           ; goto the users INT handler
AfterRestore
            clrf   STATUS
PREV_BANK = 0            
            if (Reset == YES)
                CHK?RP   INT_Flag_Reg
                bcf      INT_Flag_Reg, INT_Flag_Bit ; reset flag (if specified)
            endif
        else
            error Interrupt Source (IntFlagReg,IntFlagBit) not found
        endif
NoInt
        clrf   STATUS
PREV_BANK = 0        
    endm

;---[Returns from a "goto" subroutine]------------(RetAddr must be set first)---
INT_RETURN  macro
      CHK?RP  _RetAddr
      movf    _RetAddr + 1, W  ; Set PCLATH with top byte of return address
      movwf   PCLATH
      movf    _RetAddr, W      ; Go back to where we were
      movwf   PCL
    endm    
    
;---[Enable an interrupt source]------------------------------------------------
INT_ENABLE  macro  IntFlagReg, IntFlagBit
      GetIntInfo   IntFlagReg, IntFlagBit
      if (Found == YES)
          CHK?RP  INT_Flag_Reg
          bcf     INT_Flag_Reg, INT_Flag_Bit        ; clear the flag first 
          CHK?RP  INT_Enable_Reg
          bsf     INT_Enable_Reg, INT_Enable_Bit    ; enable the INT source  
      else
          error Cannot Enable (IntFlagReg,IntFlagBit)
      endif
    endm    

;---[Disable an interrupt source]-----------------------------------------------
INT_DISABLE  macro  IntFlagReg, IntFlagBit
      GetIntInfo   IntFlagReg, IntFlagBit
      if (Found == YES)
          CHK?RP  INT_Enable_Reg
          bcf     INT_Enable_Reg, INT_Enable_Bit    ; disable the INT source  
      else
          error Cannot Disable (IntFlagReg,IntFlagBit)
      endif
    endm    

;---[Clear an interrupt Flag]---------------------------------------------------
INT_CLEAR  macro  IntFlagReg, IntFlagBit
      GetIntInfo   IntFlagReg, IntFlagBit
      if (Found == YES)
          CHK?RP  INT_Flag_Reg
          bcf     INT_Flag_Reg, INT_Flag_Bit       ; clear the INT flag
      else
          error Cannot CLEAR (IntFlagReg,IntFlagBit)
      endif
    endm



	ENDASM?


	ASM?

INT_LIST  macro                     ; IntSource,        Label,  Type, ResetFlag?
        INT_Handler   TMR1_INT,  HeaterDrive,   ASM,  yes
    endm
    INT_CREATE                      ; Creates the interrupt processor


	ENDASM?

	MOVE?CB	001h, T1CON

	ASM?
   INT_ENABLE   TMR1_INT           ; enable Timer1 interrupts

	ENDASM?


	ASM?
 #define DT_18x20_Present 1

	ENDASM?

	DDISABLE?	

	ASM?
DS1820_Raw = _DS1820_Buffer

	ENDASM?

	GOTO?L	_Init_DS1820

	ASM?

  ifdef PM_USED
    "For DT_18x20, you must use MPASM for the assembler"
  endif


	ENDASM?


	ASM?

YES = 1                           ; YES ON or 1 can be used interchangably
ON  = 1
NO  = 0                           ; NO OFF or 0  "     "         "
OFF = 0

  ifndef  DS1820_DECIMALS
DS1820_DECIMALS = 1               ; 1 decimal place
  endif 
  ifndef DS1820_VERIFYCRC         
DS1820_VERIFYCRC = NO             ; does NOT Verify CRC
  endif 
  ifndef  DS1820_ONLY             
DS1820_ONLY = NO                  ; NOT DS1820 Only
  endif 
  ifndef  DS18B20_ONLY            
DS18B20_ONLY = NO                 ; NOT DS18B20 Only
  endif 
  ifndef  DS1820_USEALARMS
DS1820_USEALARMS = NO             ; No alarms
  endif
  if (DS1820_ONLY == 1) && (DS18B20_ONLY == 1) ; Both can't be ONLY
      error "DS1820_ONLY and DS18B20_ONLY Can Not be enabled at the same time"
  endif 
  ifndef  DS1820_ERRORCHECK
DS1820_ERRORCHECK = NO            ; No Error checking
  endif
  ifndef  DS1820_SIMULATION
DS1820_SIMULATION = NO            ; Simulation is disabled
  endif

  ifndef  DS1820_TIMEOUT
DS1820_TIMEOUT = 800              ; Timeout after ~800ms
  else
      if (DS1820_TIMEOUT > 800)
        warning "DS1820_TIMEOUT" [DS1820_TIMEOUT] above recommended max of 800 
      endif 
  endif

  ifdef  DS1820_ALLOWPARASITE     ; force timeouts if allowing parasite PWR
    if (DS1820_ALLOWPARASITE == 1)
      ifdef DS1820_USETIMEOUT
          #undefine  DS1820_USETIMEOUT
      endif
      #define  DS1820_USETIMEOUT YES
    endif
  endif
  ifndef DS1820_USETIMEOUT  ; should force it with errorcheck
DS1820_USETIMEOUT = 1
  endif             
  
  if (DS1820_DECIMALS >= 0) && (DS1820_DECIMALS <= 2)                         ; so far this line doesn't help much, doesn't hurt 
    if (DS1820_DECIMALS == 0)
DS1820_DIG = 1
    endif
    if (DS1820_DECIMALS == 1)
DS1820_DIG = 10
    endif
    if (DS1820_DECIMALS == 2)
DS1820_DIG = 100
    endif
  else
DS1820_DIG = 1
      error "Invalid DS1820_DECIMALS Specified" [DS1820_DECIMALS]
  endif

;DS1820_BUSSCOUNT = 0


;____[Add a PIN to the Array of Busses]___________Not used yet________________
;OW_BUSS  macro Name, PinReg, PinBit
;    #DEFINE Name DS1820_BUSSCOUNT
;DS1820_BUSSCOUNT = DS1820_BUSSCOUNT + 1

;DS1820_BUSS#v(DS1820_BUSSCOUNT)_REG = PinReg
;DS1820_BUSS#v(DS1820_BUSSCOUNT)_BIT = PinBit

;  endm

;____[Select PIN from Array of Busses]________________________________________
;DS1820_CreateArray  macro  BussList

;  endm
  
;DS1820_SelectBuss  macro  IDX

;  endm

;____[ Select PIN to use for next access ]____________________________________
DS1820_Select  macro  Regin, Bitin
    MOVE?CW  Regin, _DS1820_DeviceReg
    BIT?W    Bitin
    MOVE?AB  _DS1820_DeviceBit
    if ((DS1820_ERRORCHECK == 1) || ((DS1820_ONLY == 0)&&(DS18B20_ONLY == 0)))
        L?CALL   _DS1820_GetFamily
    endif
    MOVE?CT  1, _DS1820_NotValid
  endm

;____[ Tell OW commands which pin to use ]____________________________________
DS1820_SetPin  macro                     ; 
    ifdef BSR                                 ; if PIC is 18F  
        MOVE?BB  _DS1820_DeviceReg + 1, RS1   ;   HighByte (BSR) of PORT Addr
    endif
    MOVE?BB  _DS1820_DeviceReg, RR1           ; LowByte of PORT Addr
    MOVE?BB  _DS1820_DeviceBit, RM1
  endm


	ENDASM?


	ASM?

DS1820_Save2EE  macro
    DS1820_SetPin
  	OWMODE?C     _OW_PreReset
  	OWOUT?C      _CMD_SkipROM
  	OWOUT?C      _CMD_CopyPAD
    OWEND?	
    ; **** drive parasite if needed =====================================================
;    MOVE?BB    RR1, FSR    ; put port in FSR               ; 16F only *************
;    MOVE?BA    RM1         ; W = bit mask
;   	L?CALL	   HIGHT       ; Drive pin HIGH during EEPROM write
    

	ENDASM?

	PAUSE?C	00Ah

	ASM?

    L?CALL	   INPUTT      ; Set output low

  endm  


	ENDASM?


	ASM?
                                               ; optimize out if not used
Expand_DS1820_Write  macro
    ifndef DS1820_Write_Expanded
DS1820_Write_Expanded = 1
        L?GOTO  Over_DS1820_Write
DS1820_Write3
    if (DS1820_ONLY == 0) && (DS18B20_ONLY == 0)
        

	ENDASM?

	CMPNE?BCL	_DS1820_Family, _Fam_DS18B20, L00011
	MOVE?CB	003h, _DS1820_HoldBU
	GOTO?L	L00012
	LABEL?L	L00011	
	MOVE?CB	002h, _DS1820_HoldBU
	LABEL?L	L00012	

	ASM?

    endif
;   OWOUT DQ, OW_PreReset, [CMD_SkipROM, CMD_WritePAD, STR DS1820_AlarmH\3]
        DS1820_SetPin
    	OWMODE?C     _OW_PreReset
    	OWOUT?C      _CMD_SkipROM
    	OWOUT?C      _CMD_WritePAD
        if (DS1820_ONLY == 0) && (DS18B20_ONLY == 0)
        	OWCOUNT?B    _DS1820_HoldBU
       	else
       	    if (DS1820_ONLY == 1)
            	OWCOUNT?C    2
       	    else
       	        if (DS18B20_ONLY == 1)
                	OWCOUNT?C    3
       	        endif
       	    endif
        endif
    	OWOUTSTRN?B  _DS1820_AlarmH
    	OWEND?	
     RETURN?
 LABEL?L  Over_DS1820_Write
    endif
  endm

DS1820_Write  macro
    Expand_DS1820_Write
    L?CALL  DS1820_Write3
  endm  

;____[Set Resolution of DS18B20 9-12 bit]_____________________________________
Expand_DS1820_SetResolution  macro                ; optimize out if not used
    ifndef DS1820_SetResolution_Expanded
DS1820_SetResolution_Expanded = 1
        L?GOTO  Over_DS1820_SetResolution
        

	ENDASM?


	LABEL?L	_DS1820_SetResolution	
	GOSUB?L	_DS1820_Wait
	CMPT?TL	_DS1820_TimedOut, L00013

	ASM?

          if (DS18B20_ONLY == 1)
            MOVE?CB  _Fam_DS18B20, _DS1820_Family
          else
            L?CALL _DS1820_GetFamily
          endif
        

	ENDASM?

	CMPNE?BCL	_DS1820_Family, _Fam_DS18B20, L00015
	GOSUB?L	_DS1820_Read
	CMPNE?BCL	_DS1820_Error, 000h, L00017
	MOVE?BB	_DS1820_HoldB, _DS1820_Config

	ASM?
  DS1820_Write

	ENDASM?

	GOSUB?L	_DS1820_Read
	CMPEQ?BBL	_DS1820_HoldB, _DS1820_Config, L00019
	MOVE?CT	001h, _DS1820_WriteFailed
	LABEL?L	L00019	
	LABEL?L	L00017	
	GOTO?L	L00016
	LABEL?L	L00015	
	MOVE?CT	001h, _DS1820_FAM_Error
	LABEL?L	L00016	
	LABEL?L	L00013	
	RETURN?	

	ASM?
        
Over_DS1820_SetResolution
    endif
  endm
    
DS1820_Resolution  macro Res
    if (DS1820_ONLY == 0)
        if (Res >= 9) && (Res <= 12)
            if (Res == 9)
                MOVE?CB  _DS18B20_9bit, _DS1820_HoldB
            endif
            if (Res == 10)
                MOVE?CB  _DS18B20_10bit, _DS1820_HoldB
            endif
            if (Res == 11)
                MOVE?CB  _DS18B20_11bit, _DS1820_HoldB
            endif
            if (Res == 12)
                MOVE?CB  _DS18B20_12bit, _DS1820_HoldB
            endif
            Expand_DS1820_SetResolution
            L?CALL  _DS1820_SetResolution
        else
            error "DS1820_Resolution - Invalid Resolution Specified."
        endif
    else
        error "DS1820_Resolution cannot be used with DS1820_ONLY"
    endif
  endm

;_____________________________________________________________________________
Expand_RuntimeResolution  macro
  ifndef  RuntimeResolution_Expanded
RuntimeResolution_Expanded = 1  
    L?GOTO  OverRuntimeResolution
    

	ENDASM?


	LABEL?L	_RuntimeResolution	
	SUB?BCW	_DS1820_HoldB, 009h, T1
	LOOKUP?WCLB	T1, 004h, L00001, _DS1820_HoldB
	LURET?C	01Fh
	LURET?C	03Fh
	LURET?C	05Fh
	LURET?C	07Fh

	LABEL?L	L00001	
	RETURN?	

	ASM?
  
 LABEL?L  OverRuntimeResolution  
  endm
  
DS1820_Resolution?B  macro Res
    if (DS1820_ONLY == 0)
        MOVE?BB  Res, _DS1820_HoldB
        Expand_RuntimeResolution
        L?CALL   _RuntimeResolution
        Expand_DS1820_SetResolution
        L?CALL  _DS1820_SetResolution
    else
        error "DS1820_Resolution?B cannot be used with DS1820_ONLY"
    endif
  endm
  


	ENDASM?


	ASM?

CanUseAlarms?  macro  S                ; Make sure Alarms are Enabled first
    if (DS1820_USEALARMS == 0)
        error S - Alarms are disabled
    endif
  endm

ReadAndCheck macro L
    L?CALL   _DS1820_Read
    if (DS1820_ERRORCHECK == 1)       ; if Error checking is enabled
        CHK?RP   _DS1820_Error
        movf     _DS1820_Error, W
        btfss    STATUS, Z            ; is DS1820_Error = 0
        L?GOTO   L                    ; NO, goto Label
    endif
  endm

Expand_VerifyAlarms  macro                                                     ; not implemented yet
    ifndef VerifyAlarms_Expanded
VerifyAlarms_Expanded = 1
    L?GOTO  Over_VerifyAlarms    
    

	ENDASM?


	LABEL?L	_VerifyAlarms_Code	
	RETURN?	

	ASM?

Over_VerifyAlarms
    endif
  endm

VerifyAlarms  macro TH, TL                                                     ; not implemented yet
  local  BadWrite                                                              
    if (DS1820_ERRORCHECK == 1)       ; if Error checking is enabled
      if (TH < 255) || (TL < 255)     ; 255 = don't check
        
    
      endif
    endif
  endm
  
DS1820_SetAlarms  macro  TH, TL
  local  BadRead, BadWrite, ReadDone
    CanUseAlarms?  DS1820_SetAlarms
    if (DS1820_ONLY == 0)
        ReadAndCheck  BadRead         ; Read 18B20 first to get config
    endif
    MOVE?CB  TH, _DS1820_AlarmH       ; change alarm data
    MOVE?CB  TL, _DS1820_AlarmL
    DS1820_Write                      ; write it back to the device
    if (DS1820_ERRORCHECK == 1)       ; if Error checking is enabled
        ReadAndCheck  BadRead
        movlw    TH                   ;   verify High alarm
        CHK?RP   _DS1820_AlarmH
        subwf    _DS1820_AlarmH, W
        btfss    STATUS, Z
        L?GOTO   BadWrite
        movlw    TL                   ;   verify Low alarm
        CHK?RP   _DS1820_AlarmL
        subwf    _DS1820_AlarmL, W
        btfsc    STATUS, Z
        L?GOTO   ReadDone                
 LABEL?L BadWrite                 ; ******** Check for Banking issues ******
                                  ; **     Jumping here is a problem      **
                                  ; ** Use L?GOTO and LABEL?L, RETURN?    **
                                  ; **   Here, and everywhere else too    **
                                  ; ****************************************
        MOVE?CT  1, _DS1820_WriteFailed
    endif
 LABEL?L BadRead
        
 LABEL?L ReadDone
  endm

DS1820_SetAlarms?B  macro  TH, TL
  local  BadRead, BadWrite, ReadDone
    CanUseAlarms? DS1820_SetAlarms 
    if (DS1820_ONLY == 0)
        ReadAndCheck  BadRead         ; Read 18B20 first to get config
    endif
    MOVE?BB  TH, _DS1820_AlarmH       ; change alarm data
    MOVE?BB  TL, _DS1820_AlarmL
    DS1820_Write                      ; write it back to the device
    if (DS1820_ERRORCHECK == 1)       ; if Error checking is enabled
        ReadAndCheck  BadRead
        MOVE?BA  TH                   ;   verify High alarm
        CHK?RP   _DS1820_AlarmH
        subwf    _DS1820_AlarmH, W
        btfss    STATUS, Z
        L?GOTO   BadWrite
        MOVE?BA  TL                   ;   verify Low alarm
        CHK?RP   _DS1820_AlarmL
        subwf    _DS1820_AlarmL, W
        btfsc    STATUS, Z
        L?GOTO   ReadDone
 LABEL?L BadWrite
        MOVE?CT  1, _DS1820_WriteFailed
    endif
 LABEL?L BadRead
    ; -- Error is already flagged -- BadRead is for Whatever, Later ---
 LABEL?L ReadDone
  endm
  
DS1820_SetHighAlarm  macro TH
  local  BadRead, BadWrite, ReadDone
    CanUseAlarms? DS1820_SetHighAlarm
    if (DS1820_ONLY == 0)
        ReadAndCheck  BadRead         ; Read 18B20 first to get config
    endif
    MOVE?CB  TH, _DS1820_AlarmH       ; change High alarm data
    DS1820_Write                      ; write it back to the device
    if (DS1820_ERRORCHECK == 1)       ; if Error checking is enabled
        ReadAndCheck  BadRead
        MOVE?BA  TH                   ;   verify High alarm
        CHK?RP   _DS1820_AlarmH
        subwf    _DS1820_AlarmH, W
        btfsc    STATUS, Z
        L?GOTO   ReadDone
 LABEL?L BadWrite
        MOVE?CT  1, _DS1820_WriteFailed
    endif
 LABEL?L BadRead
 LABEL?L ReadDone
  endm
  
DS1820_SetLowAlarm  macro TL
  local  BadRead, BadWrite, ReadDone
    CanUseAlarms? DS1820_SetLowAlarm
    ReadAndCheck  BadRead
    MOVE?CB  TL, _DS1820_AlarmL
    DS1820_Write
    if (DS1820_ERRORCHECK == 1)       ; if Error checking is enabled
        ReadAndCheck  BadRead
        MOVE?BA  TL                   ;   verify Low alarm
        CHK?RP   _DS1820_AlarmH
        subwf    _DS1820_AlarmH, W
        btfsc    STATUS, Z
        L?GOTO   ReadDone
 LABEL?L BadWrite
        MOVE?CT  1, _DS1820_WriteFailed
    endif
 LABEL?L BadRead
 LABEL?L ReadDone
  endm


	ENDASM?


	LABEL?L	_DS1820_ReadPWR	

	ASM?

        DS1820_SetPin
    	OWMODE?C  _OW_PreReset
    	OWOUT?C   _CMD_SkipROM
    	OWOUT?C   _CMD_ReadPower
    	OWEND?
      
     	OWMODE?C  _OW_BitData
    	OWIN?T    _DS1820_Parasite
    	OWEND?	
	
    

	ENDASM?

	RETURN?	

	ASM?

DS1820_ReadPWR  macro
    L?CALL _DS1820_ReadPWR
  endm


	ENDASM?


	LABEL?L	_DS1820_Convert	

	ASM?

      ifdef DS1820_ALLOWPARASITE
        if (DS1820_ALLOWPARASITE == 1)
          DS1820_ReadPWR
          BIT?GOTO   1, _DS1820_Parasite, DontNeed2Read
            ReadAndCheck  _CantConvert  ; get config from the device


	ENDASM?


	ASM?

          LABEL?L DontNeed2Read
        endif
      endif  
        DS1820_SetPin
    	OWMODE?C  _OW_PreReset
    	OWOUT?C   _CMD_SkipROM
    	OWOUT?C   _CMD_Convert
    	OWEND?	
      ifdef DS1820_ALLOWPARASITE
        if (DS1820_ALLOWPARASITE == 1)
          BIT?GOTO   1, _DS1820_Parasite, NoParasitePause
          MOVE?BB    RR1, FSR    ; put port in FSR               ; 16F only *************
          MOVE?BA    RM1         ; W = bit mask
;          movf	RR1, W    
;        	movwf	FSR
;        	movf	RM1, W    
        	L?CALL	HIGHT                 ; Drive pin HIGH during conversion
          

	ENDASM?

	CMPNE?BCL	_DS1820_Config, 07Fh, L00023
	PAUSE?C	002EEh
	GOTO?L	L00022
	LABEL?L	L00023	
	CMPNE?BCL	_DS1820_Config, 05Fh, L00024
	PAUSE?C	00177h
	GOTO?L	L00022
	LABEL?L	L00024	
	CMPNE?BCL	_DS1820_Config, 03Fh, L00025
	PAUSE?C	0BCh
	GOTO?L	L00022
	LABEL?L	L00025	
	CMPNE?BCL	_DS1820_Config, 01Fh, L00026
	PAUSE?C	05Eh
	LABEL?L	L00026	
	LABEL?L	L00022	

	ASM?

        	call	INPUTT    ; Set output low
          LABEL?L NoParasitePause        	
        endif
      endif  

    

	ENDASM?

	MOVE?CT	000h, _DS1820_Done
	RETURN?	

	LABEL?L	_CantConvert	
	RETURN?	

	ASM?

DS1820_Convert  macro
    L?CALL  _DS1820_Convert
  endm


	ENDASM?


	LABEL?L	_DS1820_Wait	
	MOVE?CT	001h, _DS1820_Waiting

	ASM?
DSTIMEOUTloops = DS1820_TIMEOUT / 10 ; Number of 10ms loops for timeout

	ENDASM?


	LABEL?L	_DS1820_Stat	
	CMPF?TL	_DS1820_Done, L00027
	RETURN?	
	LABEL?L	L00027	

	ASM?
   if (DS1820_USETIMEOUT == 1) 

	ENDASM?

	MOVE?CB	DSTIMEOUTloops, _DS1820_TimeoutCount
	MOVE?CT	000h, _DS1820_TimedOut

	ASM?
   endif

	ENDASM?


	LABEL?L	_TryStatAgain	

	ASM?

        DS1820_SetPin
    	OWMODE?C  _OW_BitData
    	OWIN?T    _DS1820_Done
    	OWEND?	
    

	ENDASM?

	CMPF?TL	_DS1820_Done, L00029
	MOVE?CT	000h, _DS1820_Waiting

	ASM?
       if (DS1820_USEALARMS == 1) 

	ENDASM?

	GOTO?L	_DS1820_GetAlarm

	ASM?
       else

	ENDASM?

	RETURN?	

	ASM?
       endif

	ENDASM?

	GOTO?L	L00030
	LABEL?L	L00029	
	CMPF?TL	_DS1820_Waiting, L00031
	PAUSE?C	00Ah

	ASM?
           if (DS1820_USETIMEOUT == 1) 

	ENDASM?

	SUB?BCB	_DS1820_TimeoutCount, 001h, _DS1820_TimeoutCount
	CMPGT?BCL	_DS1820_TimeoutCount, 000h, _TryStatAgain
	MOVE?CT	001h, _DS1820_TimedOut
	MOVE?CT	001h, _DS1820_NotValid

	ASM?
           else

	ENDASM?

	GOTO?L	_TryStatAgain

	ASM?
           endif

	ENDASM?

	LABEL?L	L00031	
	LABEL?L	L00030	
	RETURN?	

	ASM?

DS1820_Stat  macro                  ; Get DS18x20 status
    L?CALL  _DS1820_Stat
  endm



	ENDASM?


	ASM?
  if (DS1820_USEALARMS == 1) 

	ENDASM?


	LABEL?L	_DS1820_GetAlarm	
	CMPEQ?TCL	_DS1820_Done, 000h, _DS1820_Wait

	ASM?
 ;   OWOUT   DS1820_DQ, OW_PreReset, [CMD_AlarmSearch]
        DS1820_SetPin
    	OWMODE?C  _OW_PreReset
    	OWOUT?C   _CMD_AlarmSearch
    	OWEND?	
        ;   OWIN    DS1820_DQ, OW_BitData, [DS1820_Alarm]
        DS1820_SetPin
    	OWMODE?C  _OW_BitData
    	OWIN?T    _DS1820_Alarm
    	OWEND?	
    

	ENDASM?

	XOR?TCT	_DS1820_Alarm, 001h, _DS1820_Alarm
	RETURN?	

	ASM?
  endif

	ENDASM?


	LABEL?L	_DS1820_Read	
	GOSUB?L	_DS1820_Wait

	ASM?

        DS1820_SetPin
    	OWMODE?C   _OW_PreReset
    	OWOUT?C    _CMD_SkipROM
    	OWOUT?C    _CMD_ReadPAD
    	OWEND?	
    

	ENDASM?


	ASM?

        DS1820_SetPin
    	OWMODE?C   _OW_PostReset
    	OWCOUNT?C  009h
    	OWINSTR?B  _DS1820_Buffer
    	OWEND?	
    

	ENDASM?

	MOVE?TT	_DS1820_Raw??15, _DS1820_Sign
	ABS?WW	DS1820_Raw, DS1820_Raw

	ASM?
  if ((DS1820_ONLY == 0) && (DS18B20_ONLY == 0)) 

	ENDASM?

	CMPNE?BCL	_DS1820_Family, _Fam_DS18B20, L00035

	ASM?
  endif

	ENDASM?


	ASM?
  if ((DS18B20_ONLY == 1) || ((DS1820_ONLY == 0) && (DS18B20_ONLY == 0)))

	ENDASM?

	SHIFTR?WCW	DS1820_Raw, 004h, T1
	MUL?WCW	T1, 064h, T1
	AND?WCW	DS1820_Raw, 00Fh, T2
	MUL?WCW	T2, 064h, T2
	DIV?WCW	T2, 010h, T2
	ADD?WWW	T1, T2, _TempC
	CMPF?TL	_DS1820_Sign, L00036
	UMINUS?WW	_TempC, _TempC
	LABEL?L	L00036	

	ASM?
  endif

	ENDASM?


	ASM?
  if ((DS1820_ONLY == 0) && (DS18B20_ONLY == 0)) 

	ENDASM?

	GOTO?L	L00034
	LABEL?L	L00035	
	CMPNE?BCL	_DS1820_Family, _Fam_DS18S20, L00038

	ASM?
  endif

	ENDASM?


	ASM?
  if ((DS1820_ONLY == 1) || ((DS1820_ONLY == 0) && (DS18B20_ONLY == 0)))

	ENDASM?

	SHIFTR?WCW	DS1820_Raw, 001h, T1
	MUL?WCW	T1, 064h, _TempC
	CMPF?TL	_DS1820_Sign, L00039
	UMINUS?WW	_TempC, _TempC
	LABEL?L	L00039	
	SUB?WCW	_TempC, 019h, T1
	SUB?BBW	_DS1820_CountPC, _DS1820_Cremain, T2
	MUL?WCW	T2, 064h, T2
	DIV?WBW	T2, _DS1820_CountPC, T2
	ADD?WWW	T1, T2, _TempC

	ASM?
  endif

	ENDASM?


	ASM?
  if ((DS1820_ONLY == 0) && (DS18B20_ONLY == 0)) 

	ENDASM?

	LABEL?L	L00038	
	LABEL?L	L00034	

	ASM?
  endif

	ENDASM?


	ASM?
  if (DS1820_DECIMALS == 0)

	ENDASM?

	DIV?WCW	_TempC, 064h, _TempC

	ASM?
  endif

	ENDASM?


	ASM?
  if (DS1820_DECIMALS == 1)

	ENDASM?

	DIV?WCW	_TempC, 00Ah, _TempC

	ASM?
  endif

	ENDASM?


	ASM?

        if (DS1820_VERIFYCRC == 1)
            L?CALL  _CheckCRC
        else
            MOVE?CT  0, _DS1820_NotValid
        endif
    

	ENDASM?

	RETURN?	

	ASM?

DS1820_Read  macro
    L?CALL  _DS1820_Read
  endm


	ENDASM?


	ASM?

DS1820_GetTemp  macro
    DS1820_Convert
    DS1820_Read
  endm


	ENDASM?


	ASM?

Expand_Convert2Fahrenheit  macro
    ifndef Convert2Fahrenheit_Expanded
Convert2Fahrenheit_Expanded = 1
        L?GOTO OverDS1820_Convert2F
    

	ENDASM?


	LABEL?L	_Convert2Fahrenheit	
	MOVE?TT	_TempC??15, _DS1820_Sign
	ABS?WW	_TempC, T1
	MULMID?WCW	T1, 001CDh, _DS1820_HoldW
	CMPF?TL	_DS1820_Sign, L00041
	UMINUS?WW	_DS1820_HoldW, _DS1820_HoldW
	LABEL?L	L00041	

	ASM?
    if (DS1820_DECIMALS == 0)

	ENDASM?

	ADD?WCW	_DS1820_HoldW, 020h, _DS1820_HoldW

	ASM?
    endif

	ENDASM?


	ASM?
    if (DS1820_DECIMALS == 1)

	ENDASM?

	ADD?WCW	_DS1820_HoldW, 00140h, _DS1820_HoldW

	ASM?
    endif

	ENDASM?


	ASM?
    if (DS1820_DECIMALS == 2)

	ENDASM?

	ADD?WCW	_DS1820_HoldW, 00C80h, _DS1820_HoldW

	ASM?
    endif

	ENDASM?

	RETURN?	

	ASM?

OverDS1820_Convert2F            
    endif
  endm

DS1820_Convert2F  macro Wout
    Expand_Convert2Fahrenheit
    L?CALL  _Convert2Fahrenheit
    MOVE?WW  _DS1820_HoldW, Wout
  endm 

;___________________________________________________________________________
DS1820_Convert2K  macro Wout         ; convert to Kelvin
    

	ENDASM?


	ASM?
    if (DS1820_DECIMALS == 0)

	ENDASM?

	ADD?WCW	_TempC, 00111h, _DS1820_HoldW

	ASM?
    endif

	ENDASM?


	ASM?
    if (DS1820_DECIMALS == 1)

	ENDASM?

	ADD?WCW	_TempC, 00AAAh, _DS1820_HoldW

	ASM?
    endif

	ENDASM?


	ASM?
    if (DS1820_DECIMALS == 2)

	ENDASM?

	ADD?WCW	_TempC, 06AA4h, _DS1820_HoldW

	ASM?
    endif

	ENDASM?


	ASM?
    MOVE?WW  _DS1820_HoldW, Wout

	ENDASM?


	ASM?
  endm

	ENDASM?


	ASM?
  if (((DS1820_ONLY == 0)&&(DS18B20_ONLY == 0)) || (DS1820_ERRORCHECK == 1))

	ENDASM?


	LABEL?L	_DS1820_GetFamily	
	GOSUB?L	_DS1820_Wait

	ASM?

        ;    OWOUT DS1820_DQ, OW_PreReset, [CMD_ReadROM]
        DS1820_SetPin
    	OWMODE?C   _OW_PreReset
    	OWOUT?C    _CMD_ReadROM
    	OWEND?	
        ;    OWIN  DS1820_DQ, OW_PostReset,[DS1820_Family]
        DS1820_SetPin
    	OWMODE?C   _OW_PostReset
    	OWIN?B     _DS1820_Family
    	OWEND?	
        if (DS1820_ONLY == 1)
          if (DS1820_ERRORCHECK == 1)
            movlw   _Fam_DS1820
            subwf   _DS1820_Family, W
            btfsc   STATUS, Z
            L?GOTO  _GetFamilyDone
            MOVE?CT  1, _DS1820_FAM_Error
         endif   
       endif   
    
       if (DS18B20_ONLY == 1)
         if (DS1820_ERRORCHECK == 1)
            movlw   _Fam_DS18B20
            subwf   _DS1820_Family, W
            btfsc   STATUS, Z
            L?GOTO  _GetFamilyDone
            MOVE?CT  1, _DS1820_FAM_Error
         endif   
       endif   
    

	ENDASM?


	LABEL?L	_GetFamilyDone	
	RETURN?	

	ASM?
  endif

	ENDASM?


	ASM?
    if (DS1820_VERIFYCRC == 1)

	ENDASM?


	LABEL?L	_CheckCRC	
	MOVE?CB	000h, _DS_CRC
	MOVE?CT	000h, _DS_CRCpassed
	MOVE?CB	000h, _DS_ByteCount
	LABEL?L	L00043	
	CMPGT?BCL	_DS_ByteCount, 007h, L00044
	AOUT?BBB	_DS1820_Buffer, _DS_ByteCount, _DS_CRCData

	LABEL?L	_CRC8	
	MOVE?CB	000h, _DS_BitCount
	LABEL?L	L00045	
	CMPGT?BCL	_DS_BitCount, 007h, L00046
	XOR?TTT	_DS_CRC??0, _DS_CRCData??0, _DS_TestBit
	SHIFTR?BCB	_DS_CRCData, 001h, _DS_CRCData
	CMPEQ?TCL	_DS_TestBit, 000h, _Shift
	XOR?BCB	_DS_CRC, 018h, _DS_CRC

	LABEL?L	_Shift	
	SHIFTR?BCB	_DS_CRC, 001h, _DS_CRC
	MOVE?TT	_DS_TestBit, _DS_CRC??7
	NEXT?BCL	_DS_BitCount, 001h, L00045
	LABEL?L	L00046	
	NEXT?BCL	_DS_ByteCount, 001h, L00043
	LABEL?L	L00044	
	CMPNE?BBL	_DS_CRC, _DS1820_CRC, L00047
	MOVE?CT	001h, _DS_CRCpassed
	MOVE?CT	000h, _DS1820_NotValid
	MOVE?CT	000h, _DS1820_CRCfailed
	GOTO?L	L00048
	LABEL?L	L00047	
	MOVE?CT	001h, _DS1820_NotValid
	MOVE?CT	001h, _DS1820_CRCfailed
	LABEL?L	L00048	
	RETURN?	

	ASM?
    endif

	ENDASM?


	ASM?
   ifdef NoCompile

	ENDASM?

	OWPIN?T	_PORTA??0
	OWMODE?C	000h
	OWOUT?C	001h
	OWOUT?B	_R0??LOWBYTE
	OWCOUNT?C	003h
	OWOUTSTRN?B	_DS1820_Buffer
	OWEND?	
	OWPIN?T	_PORTA??0
	OWMODE?C	000h
	OWIN?T	_R0??BIT0
	OWIN?B	_R0??LOWBYTE
	OWCOUNT?B	_R0??LOWBYTE
	OWINSTR?B	_DS1820_Buffer
	OWEND?	
	HIGH?W	R0
	INPUT?W	R0

	ASM?
   endif

	ENDASM?


	LABEL?L	_Init_DS1820	
	MOVE?CT	001h, _DS1820_NotValid
	MOVE?CT	001h, _DS1820_Done
	DENABLE?	
	GOTO?L	_SkipPID

	LABEL?L	_PID	
	ADD?BCW	_pid_Channel, 001h, T1
	MUL?WCW	T1, 010h, T1
	SUB?WCW	T1, 001h, _pid_index
	ABS?WW	_pid_Error, T1
	AOUT?WBW	_pid_Kp, _pid_Channel, T2
	MULMID?WWW	T1, T2, _pid_P
	CMPF?TL	_pid_Error??15, L00049
	UMINUS?WW	_pid_P, _pid_P
	LABEL?L	L00049	
	AOUT?WBW	_pid_Ei, _pid_Channel, T1
	ADD?WWW	T1, _pid_Error, T1
	AIN?WWB	T1, _pid_Ei, _pid_Channel
	AOUT?BBB	_pid_IntCount, _pid_Channel, T1
	ADD?BCW	T1, 001h, T1
	AIN?WBB	T1, _pid_IntCount, _pid_Channel
	AOUT?BBB	_pid_IntCount, _pid_Channel, T1
	AOUT?BBB	_pid_Ti, _pid_Channel, T2
	CMPLT?BBL	T1, T2, L00051
	AOUT?TWT	_pid_Ei??0, _pid_index, _pid_Sign
	AOUT?WBW	_pid_Ei, _pid_Channel, T1
	ABS?WW	T1, T1
	AIN?WWB	T1, _pid_Ei, _pid_Channel
	AOUT?WBW	_pid_Ei, _pid_Channel, T1
	AOUT?WBW	_pid_Ki, _pid_Channel, T2
	MULMID?WWW	T1, T2, T2
	AIN?WWB	T2, _pid_Ei, _pid_Channel
	AOUT?WBW	_pid_Ei, _pid_Channel, T1
	AOUT?BBB	_pid_Ti, _pid_Channel, T2
	DIV?WBW	T1, T2, T2
	AIN?WWB	T2, _pid_Ei, _pid_Channel
	CMPF?TL	_pid_Sign, L00053
	AOUT?WBW	_pid_Ei, _pid_Channel, T1
	UMINUS?WW	T1, T1
	AIN?WWB	T1, _pid_Ei, _pid_Channel
	LABEL?L	L00053	
	AOUT?WBW	_pid_I, _pid_Channel, T1
	AOUT?WBW	_pid_Ei, _pid_Channel, T2
	ADD?WWW	T1, T2, T2
	AIN?WWB	T2, _pid_I, _pid_Channel
	AOUT?TWT	_pid_I??0, _pid_index, _pid_Sign
	AOUT?WBW	_pid_I, _pid_Channel, T1
	ABS?WW	T1, T1
	AIN?WWB	T1, _pid_I, _pid_Channel
	AOUT?WBW	_pid_I, _pid_Channel, T1
	AOUT?WBW	_pid_I_Clamp, _pid_Channel, T2
	CMPLT?WWL	T1, T2, L00055
	AOUT?WBW	_pid_I_Clamp, _pid_Channel, T1
	AIN?WWB	T1, _pid_I, _pid_Channel
	LABEL?L	L00055	
	CMPF?TL	_pid_Sign, L00057
	AOUT?WBW	_pid_I, _pid_Channel, T1
	UMINUS?WW	T1, T1
	AIN?WWB	T1, _pid_I, _pid_Channel
	LABEL?L	L00057	
	AIN?CBB	000h, _pid_IntCount, _pid_Channel
	AIN?CWB	000h, _pid_Ei, _pid_Channel
	LABEL?L	L00051	
	AOUT?WBW	_pid_LastError, _pid_Channel, T1
	SUB?WWW	_pid_Error, T1, _pid_D
	MOVE?TT	_pid_D??15, _pid_Sign
	ABS?WW	_pid_D, T1
	AOUT?WBW	_pid_Kd, _pid_Channel, T2
	MULMID?WWW	T1, T2, _pid_D
	CMPF?TL	_pid_Sign, L00059
	UMINUS?WW	_pid_D, _pid_D
	LABEL?L	L00059	

	LABEL?L	_DerivDone	
	AIN?WWB	_pid_Error, _pid_LastError, _pid_Channel
	AOUT?WBW	_pid_I, _pid_Channel, T1
	ADD?WWW	_pid_P, T1, T1
	ADD?WWW	T1, _pid_D, _pid_Out
	MOVE?TT	_pid_Out??15, _pid_Sign
	ABS?WW	_pid_Out, _pid_Out
	AOUT?WBW	_pid_Out_Clamp, _pid_Channel, T1
	CMPLT?WWL	_pid_Out, T1, L00061
	AOUT?WBW	_pid_Out_Clamp, _pid_Channel, _pid_Out
	LABEL?L	L00061	
	CMPF?TL	_pid_Sign, L00063
	UMINUS?WW	_pid_Out, _pid_Out
	LABEL?L	L00063	
	RETURN?	

	LABEL?L	_SkipPID	
	READADDRESS?C	_EE_spMode1
	READ?B	_spMode1
	READADDRESS?C	_EE_SetPoint1
	READW?W	_SetPoint1
	READADDRESS?C	_EE_pid_Kp1
	READW?W	_pid_Kp
	READADDRESS?C	_EE_pid_Ki1
	READW?W	_pid_Ki
	READADDRESS?C	_EE_pid_Kd1
	READW?W	_pid_Kd
	READADDRESS?C	_EE_pid_Ti1
	READ?B	_pid_Ti
	READADDRESS?C	_EE_pid_I_Clamp1
	READ?W	_pid_I_Clamp
	READADDRESS?C	_EE_pid_Out_Clamp1
	READW?W	_pid_Out_Clamp
	READADDRESS?C	_EE_spMode2
	READ?B	_spMode2
	READADDRESS?C	_EE_SetPoint2
	READW?W	_SetPoint2
	READADDRESS?C	_EE_pid_Kp2
	READW?W	_pid_Kp + 00002h
	READADDRESS?C	_EE_pid_Ki2
	READW?W	_pid_Ki + 00002h
	READADDRESS?C	_EE_pid_Kd2
	READW?W	_pid_Kd + 00002h
	READADDRESS?C	_EE_pid_Ti2
	READ?B	_pid_Ti + 00001h
	READADDRESS?C	_EE_pid_I_Clamp2
	READ?W	_pid_I_Clamp + 00002h
	READADDRESS?C	_EE_pid_Out_Clamp2
	READW?W	_pid_Out_Clamp + 00002h
	READADDRESS?C	_EE_spMode3
	READ?B	_spMode3
	READADDRESS?C	_EE_SetPoint3
	READW?W	_SetPoint3
	READADDRESS?C	_EE_pid_Kp3
	READW?W	_pid_Kp + 00004h
	READADDRESS?C	_EE_pid_Ki3
	READW?W	_pid_Ki + 00004h
	READADDRESS?C	_EE_pid_Kd3
	READW?W	_pid_Kd + 00004h
	READADDRESS?C	_EE_pid_Ti3
	READ?B	_pid_Ti + 00002h
	READADDRESS?C	_EE_pid_I_Clamp3
	READ?W	_pid_I_Clamp + 00004h
	READADDRESS?C	_EE_pid_Out_Clamp3
	READW?W	_pid_Out_Clamp + 00004h
	READADDRESS?C	_EE_spMode4
	READ?B	_spMode4
	READADDRESS?C	_EE_SetPoint4
	READW?W	_SetPoint4
	READADDRESS?C	_EE_pid_Kp4
	READW?W	_pid_Kp + 00006h
	READADDRESS?C	_EE_pid_Ki4
	READW?W	_pid_Ki + 00006h
	READADDRESS?C	_EE_pid_Kd4
	READW?W	_pid_Kd + 00006h
	READADDRESS?C	_EE_pid_Ti4
	READ?B	_pid_Ti + 00003h
	READADDRESS?C	_EE_pid_I_Clamp4
	READ?W	_pid_I_Clamp + 00006h
	READADDRESS?C	_EE_pid_Out_Clamp4
	READW?W	_pid_Out_Clamp + 00006h
	LCDOUT?C	0FEh
	LCDOUT?C	001h
	MOVE?CB	000h, FLAGS
	PAUSE?C	0FAh
	LCDOUT?C	0FEh
	LCDOUT?C	001h
	PAUSE?C	0FAh
	GOSUB?L	_TerminalMenu
	MOVE?CB	000h, _Bvar
	LABEL?L	L00065	
	CMPGT?BCL	_Bvar, 003h, L00066
	MOVE?CT	001h, _SensorActive
	NEXT?BCL	_Bvar, 001h, L00065
	LABEL?L	L00066	
	MOVE?CB	000h, _pid_Channel
	LABEL?L	L00067	
	CMPGT?BCL	_pid_Channel, 003h, L00068
	GOSUB?L	_SelectSensor
	MOVE?CT	000h, _GIE

	ASM?
 DS1820_Resolution 12            

	ENDASM?

	MOVE?CT	001h, _GIE
	NEXT?BCL	_pid_Channel, 001h, L00067
	LABEL?L	L00068	
	LOW?T	_HeaterOut1
	LOW?T	_HeaterOut2
	LOW?T	_HeaterOut3
	LOW?T	_HeaterOut4

	LABEL?L	_Main	
	MOVE?CB	000h, _pid_Channel
	LABEL?L	L00069	
	CMPGT?BCL	_pid_Channel, 003h, L00070
	GOSUB?L	_SelectSensor
	MOVE?CT	000h, _GIE

	ASM?
  DS1820_Convert                 ;   start a temperature conversion

	ENDASM?

	MOVE?CT	001h, _GIE
	NEXT?BCL	_pid_Channel, 001h, L00069
	LABEL?L	L00070	
	MOVE?CW	000h, _TempWD
	LABEL?L	L00071	
	CMPGT?WCL	_TempWD, 003E8h, L00072
	CMPF?TL	_RCIF, L00073
	GOSUB?L	_Term_RX
	LABEL?L	L00073	
	PAUSE?C	001h
	NEXT?WCL	_TempWD, 001h, L00071
	LABEL?L	L00072	
	MOVE?CB	000h, _pid_Channel
	LABEL?L	L00075	
	CMPGT?BCL	_pid_Channel, 003h, L00076
	GOSUB?L	_SelectSensor
	MOVE?CB	000h, _DS1820_Error
	MOVE?CB	000h, _DS1820_Flags
	MOVE?CT	000h, _GIE

	ASM?
 DS1820_Stat                   ; check the sensors status

	ENDASM?

	MOVE?CT	001h, _GIE
	CMPF?TL	_DS1820_Done, _SensorError
	MOVE?CT	000h, _GIE

	ASM?
 DS1820_Read                   ;   get the temperature result

	ENDASM?

	MOVE?CT	001h, _GIE
	MOVE?CB	000h, _DS1820_Flags

	ASM?
 DS1820_Stat

	ENDASM?

	CMPEQ?BCB	_DS1820_Error, 000h, T1
	LAND?BTW	T1, _DS1820_Done, T1
	CMPF?WL	T1, L00077
	AIN?WWB	_TempC, _Temperatures, _pid_Channel
	AOUT?WBW	_SetPoints, _pid_Channel, T1
	SUB?WWW	T1, _TempC, _pid_Error
	GOSUB?L	_PID
	CMPF?TL	_pid_Out??15, L00079
	MOVE?CW	000h, _pid_Out
	LABEL?L	L00079	
	AIN?WBB	_pid_Out, HeaterDrives, _pid_Channel
	GOSUB?L	_DisplayPID
	GOSUB?L	_ShowLCD
	GOTO?L	L00078
	LABEL?L	L00077	

	LABEL?L	_SensorError	
	AIN?CBB	000h, HeaterDrives, _pid_Channel
	AIN?CTB	000h, _SensorActive, _pid_Channel
	GOSUB?L	_ShowError
	LABEL?L	L00078	
	NEXT?BCL	_pid_Channel, 001h, L00075
	LABEL?L	L00076	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	LCDOUT?C	0FEh
	LCDOUT?C	08Fh
	MUL?TCW	_FlashStar, 0FFh, T1
	AND?CWW	02Ah, T1, T1
	MUL?TCW	_FlashStar, 0FFh, T2
	NOT?WW	T2, T2
	AND?CWW	020h, T2, T2
	OR?WWW	T1, T2, T2
	LCDOUT?W	T2
	LNOT?TT	_FlashStar, _FlashStar
	GOTO?L	_Main

	LABEL?L	_ShowLCD	
	LOOKUP?BCLB	_pid_Channel, 004h, L00002, _Bvar
	LURET?C	080h
	LURET?C	0C0h
	LURET?C	088h
	LURET?C	0C8h

	LABEL?L	L00002	
	LCDOUT?C	0FEh
	LCDOUT?B	_Bvar
	LCDOUTCOUNT?C	001h
	ADD?BCW	_pid_Channel, 001h, T1
	LCDOUTNUM?W	T1
	LCDOUTDEC?	
	LCDOUT?C	03Dh
	MOVE?WW	_TempC, _TempWD
	GOSUB?L	_TempToLCD
	LCDOUT?C	0DFh
	RETURN?	

	LABEL?L	_SelectSensor	
	CMPNE?BCL	_pid_Channel, 000h, L00083

	ASM?
 DS1820_Select  _TempSensor1   ; Select the DS18x20 pin

	ENDASM?

	GOTO?L	L00082
	LABEL?L	L00083	
	CMPNE?BCL	_pid_Channel, 001h, L00084

	ASM?
 DS1820_Select  _TempSensor2

	ENDASM?

	GOTO?L	L00082
	LABEL?L	L00084	
	CMPNE?BCL	_pid_Channel, 002h, L00085

	ASM?
 DS1820_Select  _TempSensor3

	ENDASM?

	GOTO?L	L00082
	LABEL?L	L00085	
	CMPNE?BCL	_pid_Channel, 003h, L00086

	ASM?
 DS1820_Select  _TempSensor4

	ENDASM?

	LABEL?L	L00086	
	LABEL?L	L00082	
	RETURN?	

	ASM?

HeaterDrive
      incf    HeatCycle,F       ; HeatCycle

      movf    _HeatDrive1,W      ; HeatDrive1
      subwf   HeatCycle,w
      btfsc   STATUS,C
      bcf     _HeaterOut1
      btfss   STATUS,C
      bsf     _HeaterOut1
      
      movf    _HeatDrive2,W      ; HeatDrive2
      subwf   HeatCycle,w
      btfsc   STATUS,C
      bcf     _HeaterOut2
      btfss   STATUS,C
      bsf     _HeaterOut2

      movf    _HeatDrive3,W      ; HeatDrive3
      subwf   HeatCycle,w
      btfsc   STATUS,C
      bcf     _HeaterOut3
      btfss   STATUS,C
      bsf     _HeaterOut3

      movf    _HeatDrive4,W      ; HeatDrive4
      subwf   HeatCycle,w
      btfsc   STATUS,C
      bcf     _HeaterOut4
      btfss   STATUS,C
      bsf     _HeaterOut4

  INT_RETURN


	ENDASM?


	LABEL?L	_TempToLCD	
	CMPF?TL	_TempWD??15, L00087
	LCDOUT?C	02Dh
	LABEL?L	L00087	
	ABS?WW	_TempWD, _TempWD
	LCDOUTCOUNT?C	000h
	DIV?WCW	_TempWD, DS1820_DIG, T1
	LCDOUTNUM?W	T1
	LCDOUTDEC?	

	ASM?
   if (DS1820_DECIMALS > 0)              ; if using decimals

	ENDASM?

	LCDOUT?C	02Eh
	MOD?WCW	_TempWD, DS1820_DIG, _TempWD

	ASM?
       if (DS1820_DECIMALS > 1)          ; with DECIMALS=2, next DIG is 1

	ENDASM?

	LCDOUTCOUNT?C	001h
	DIG?WCW	_TempWD, 001h, T1
	LCDOUTNUM?W	T1
	LCDOUTDEC?	

	ASM?
       endif

	ENDASM?


	ASM?
       if (DS1820_DECIMALS >= 1)         ; with DECIMALS=1, next DIG is 0

	ENDASM?

	LCDOUTCOUNT?C	001h
	DIG?WCW	_TempWD, 000h, T1
	LCDOUTNUM?W	T1
	LCDOUTDEC?	

	ASM?
       endif

	ENDASM?


	ASM?
   endif

	ENDASM?

	RETURN?	

	LABEL?L	_Term_RX	
	HSERIN?B	_Char
	CMPEQ?BCL	_Char, 072h, L00091
	CMPNE?BCL	_Char, 052h, L00092

	LABEL?L	L00091	
	GOSUB?L	_TerminalMenu
	GOTO?L	L00090
	LABEL?L	L00092	
	CMPEQ?BCL	_Char, 073h, L00093
	CMPNE?BCL	_Char, 053h, L00094

	LABEL?L	L00093	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	053h
	HSEROUT?C	065h
	HSEROUT?C	074h
	HSEROUT?C	050h
	HSEROUT?C	06Fh
	HSEROUT?C	069h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	028h
	HSEROUT?C	033h
	HSEROUT?C	034h
	HSEROUT?C	030h
	HSEROUT?C	03Dh
	HSEROUT?C	033h
	HSEROUT?C	034h
	HSEROUT?C	02Eh
	HSEROUT?C	030h
	HSEROUT?C	0F8h
	HSEROUT?C	029h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	000h
	HSERINDEC?W	T1
	AIN?WWB	T1, _SetPoints, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00003, _Bvar
	LU2RET?C	_EE_SetPoint1
	LU2RET?C	_EE_SetPoint2
	LU2RET?C	_EE_SetPoint3
	LU2RET?C	_EE_SetPoint4

	LABEL?L	L00003	
	WRITEADDRESS?B	_Bvar
	AOUT?WBW	_SetPoints, _EditChannel, T1
	WRITEW?W	T1
	GOTO?L	L00090
	LABEL?L	L00094	
	CMPEQ?BCL	_Char, 070h, L00095
	CMPNE?BCL	_Char, 050h, L00096

	LABEL?L	L00095	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	050h
	HSEROUT?C	020h
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	06Dh
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	073h
	HSEROUT?C	020h
	HSEROUT?C	048h
	HSEROUT?C	045h
	HSEROUT?C	058h
	HSEROUT?C	034h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	004h
	HSERINHEX?W	T1
	AIN?WWB	T1, _pid_Kp, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00004, _Bvar
	LU2RET?C	_EE_pid_Kp1
	LU2RET?C	_EE_pid_Kp2
	LU2RET?C	_EE_pid_Kp3
	LU2RET?C	_EE_pid_Kp4

	LABEL?L	L00004	
	WRITEADDRESS?B	_Bvar
	AOUT?WBW	_pid_Kp, _EditChannel, T1
	WRITEW?W	T1
	GOTO?L	L00090
	LABEL?L	L00096	
	CMPEQ?BCL	_Char, 069h, L00097
	CMPNE?BCL	_Char, 049h, L00098

	LABEL?L	L00097	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	049h
	HSEROUT?C	020h
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	06Dh
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	073h
	HSEROUT?C	020h
	HSEROUT?C	048h
	HSEROUT?C	045h
	HSEROUT?C	058h
	HSEROUT?C	034h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	004h
	HSERINHEX?W	T1
	AIN?WWB	T1, _pid_Ki, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00005, _Bvar
	LU2RET?C	_EE_pid_Ki1
	LU2RET?C	_EE_pid_Ki2
	LU2RET?C	_EE_pid_Ki3
	LU2RET?C	_EE_pid_Ki4

	LABEL?L	L00005	
	WRITEADDRESS?B	_Bvar
	AOUT?WBW	_pid_Ki, _EditChannel, T1
	WRITEW?W	T1
	GOTO?L	L00090
	LABEL?L	L00098	
	CMPEQ?BCL	_Char, 064h, L00099
	CMPNE?BCL	_Char, 044h, L00100

	LABEL?L	L00099	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	044h
	HSEROUT?C	020h
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	06Dh
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	073h
	HSEROUT?C	020h
	HSEROUT?C	048h
	HSEROUT?C	045h
	HSEROUT?C	058h
	HSEROUT?C	034h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	004h
	HSERINHEX?W	T1
	AIN?WWB	T1, _pid_Kd, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00006, _Bvar
	LU2RET?C	_EE_pid_Kd1
	LU2RET?C	_EE_pid_Kd2
	LU2RET?C	_EE_pid_Kd3
	LU2RET?C	_EE_pid_Kd4

	LABEL?L	L00006	
	WRITEADDRESS?B	_Bvar
	AOUT?WBW	_pid_Kd, _EditChannel, T1
	WRITEW?W	T1
	GOTO?L	L00090
	LABEL?L	L00100	
	CMPEQ?BCL	_Char, 074h, L00101
	CMPNE?BCL	_Char, 054h, L00102

	LABEL?L	L00101	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	054h
	HSEROUT?C	069h
	HSEROUT?C	020h
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	06Dh
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	073h
	HSEROUT?C	020h
	HSEROUT?C	044h
	HSEROUT?C	045h
	HSEROUT?C	043h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	000h
	HSERINDEC?W	T1
	AIN?BBB	T1, _pid_Ti, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00007, _Bvar
	LU2RET?C	_EE_pid_Ti1
	LU2RET?C	_EE_pid_Ti2
	LU2RET?C	_EE_pid_Ti3
	LU2RET?C	_EE_pid_Ti4

	LABEL?L	L00007	
	WRITEADDRESS?B	_Bvar
	AOUT?BBB	_pid_Ti, _EditChannel, T1
	WRITE?B	T1
	GOTO?L	L00090
	LABEL?L	L00102	
	CMPEQ?BCL	_Char, 063h, L00103
	CMPNE?BCL	_Char, 043h, L00104

	LABEL?L	L00103	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	049h
	HSEROUT?C	020h
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	06Dh
	HSEROUT?C	020h
	HSEROUT?C	043h
	HSEROUT?C	06Ch
	HSEROUT?C	061h
	HSEROUT?C	06Dh
	HSEROUT?C	070h
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	073h
	HSEROUT?C	020h
	HSEROUT?C	044h
	HSEROUT?C	045h
	HSEROUT?C	043h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	000h
	HSERINDEC?W	T1
	AIN?WWB	T1, _pid_I_Clamp, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00008, _Bvar
	LU2RET?C	_EE_pid_I_Clamp1
	LU2RET?C	_EE_pid_I_Clamp2
	LU2RET?C	_EE_pid_I_Clamp3
	LU2RET?C	_EE_pid_I_Clamp4

	LABEL?L	L00008	
	WRITEADDRESS?B	_Bvar
	AOUT?WBW	_pid_I_Clamp, _EditChannel, T1
	WRITEW?W	T1
	GOTO?L	L00090
	LABEL?L	L00104	
	CMPEQ?BCL	_Char, 06Fh, L00105
	CMPNE?BCL	_Char, 04Fh, L00106

	LABEL?L	L00105	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	04Fh
	HSEROUT?C	075h
	HSEROUT?C	074h
	HSEROUT?C	070h
	HSEROUT?C	075h
	HSEROUT?C	074h
	HSEROUT?C	020h
	HSEROUT?C	043h
	HSEROUT?C	06Ch
	HSEROUT?C	061h
	HSEROUT?C	06Dh
	HSEROUT?C	070h
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	073h
	HSEROUT?C	020h
	HSEROUT?C	044h
	HSEROUT?C	045h
	HSEROUT?C	043h
	HSEROUT?C	020h
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSERINCOUNT?C	000h
	HSERINDEC?W	T1
	AIN?WWB	T1, _pid_Out_Clamp, _EditChannel
	GOSUB?L	_TerminalMenu
	LOOKUP2?BCLB	_EditChannel, 004h, L00009, _Bvar
	LU2RET?C	_EE_pid_Out_Clamp1
	LU2RET?C	_EE_pid_Out_Clamp2
	LU2RET?C	_EE_pid_Out_Clamp3
	LU2RET?C	_EE_pid_Out_Clamp4

	LABEL?L	L00009	
	WRITEADDRESS?B	_Bvar
	AOUT?WBW	_pid_Out_Clamp, _EditChannel, T1
	WRITEW?W	T1
	GOTO?L	L00090
	LABEL?L	L00106	
	CMPEQ?BCL	_Char, 06Dh, L00107
	CMPNE?BCL	_Char, 04Dh, L00108

	LABEL?L	L00107	
	MOVE?CB	001h, _X
	MOVE?CB	016h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	04Dh
	HSEROUT?C	061h
	HSEROUT?C	06Eh
	HSEROUT?C	075h
	HSEROUT?C	061h
	HSEROUT?C	06Ch
	HSEROUT?C	020h
	HSEROUT?C	04Dh
	HSEROUT?C	06Fh
	HSEROUT?C	064h
	HSEROUT?C	065h
	HSEROUT?C	020h
	HSEROUT?C	06Eh
	HSEROUT?C	06Fh
	HSEROUT?C	074h
	HSEROUT?C	020h
	HSEROUT?C	061h
	HSEROUT?C	076h
	HSEROUT?C	061h
	HSEROUT?C	069h
	HSEROUT?C	06Ch
	HSEROUT?C	061h
	HSEROUT?C	062h
	HSEROUT?C	06Ch
	HSEROUT?C	065h
	HSEROUT?C	02Eh
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	GOTO?L	L00090
	LABEL?L	L00108	
	CMPEQ?BCL	_Char, 034h, L00109
	CMPEQ?BCL	_Char, 033h, L00110
	CMPEQ?BCL	_Char, 032h, L00111
	CMPNE?BCL	_Char, 031h, L00112

	LABEL?L	L00109	

	LABEL?L	L00110	

	LABEL?L	L00111	
	SUB?BCW	_Char, 031h, T1
	CMPEQ?BWL	_EditChannel, T1, L00113
	GOSUB?L	_ClearBox
	SUB?BCB	_Char, 031h, _EditChannel
	GOSUB?L	_DrawBox
	LABEL?L	L00113	
	GOTO?L	L00090
	LABEL?L	L00112	
	HSEROUT?C	007h
	LABEL?L	L00090	
	RETURN?	

	LABEL?L	_TerminalMenu	
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	032h
	HSEROUT?C	04Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	032h
	HSEROUT?C	06Dh
	HSEROUT?C	048h
	HSEROUT?C	065h
	HSEROUT?C	061h
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	043h
	HSEROUT?C	06Fh
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	072h
	HSEROUT?C	06Fh
	HSEROUT?C	06Ch
	HSEROUT?C	06Ch
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	054h
	HSEROUT?C	075h
	HSEROUT?C	06Eh
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	030h
	HSEROUT?C	06Dh
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	054h
	HSEROUT?C	065h
	HSEROUT?C	06Dh
	HSEROUT?C	070h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	061h
	HSEROUT?C	074h
	HSEROUT?C	075h
	HSEROUT?C	072h
	HSEROUT?C	065h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	053h
	HSEROUT?C	065h
	HSEROUT?C	074h
	HSEROUT?C	050h
	HSEROUT?C	06Fh
	HSEROUT?C	069h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	045h
	HSEROUT?C	072h
	HSEROUT?C	072h
	HSEROUT?C	06Fh
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	04Fh
	HSEROUT?C	075h
	HSEROUT?C	074h
	HSEROUT?C	070h
	HSEROUT?C	075h
	HSEROUT?C	074h
	HSEROUT?C	020h
	HSEROUT?C	044h
	HSEROUT?C	072h
	HSEROUT?C	069h
	HSEROUT?C	076h
	HSEROUT?C	065h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	050h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	049h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	044h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	000h, _Bvar
	LABEL?L	L00115	
	CMPGT?BCL	_Bvar, 003h, L00116
	MUL?BCW	_Bvar, _ColumnWidth, T1
	ADD?CWB	011h, T1, _X
	MOVE?CB	004h, _Y
	GOSUB?L	_MoveCursor
	AOUT?WBW	_SetPoints, _Bvar, _TempWD
	GOSUB?L	_TempToTerminal
	NEXT?BCL	_Bvar, 001h, L00115
	LABEL?L	L00116	

	LABEL?L	_TerminalPIDvars	
	MOVE?CB	001h, _X
	MOVE?CB	00Dh, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	04Dh
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	073h
	HSEROUT?C	070h
	HSEROUT?C	04Dh
	HSEROUT?C	06Fh
	HSEROUT?C	064h
	HSEROUT?C	065h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	050h
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	070h
	HSEROUT?C	069h
	HSEROUT?C	064h
	HSEROUT?C	05Fh
	HSEROUT?C	04Bh
	HSEROUT?C	070h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	049h
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	070h
	HSEROUT?C	069h
	HSEROUT?C	064h
	HSEROUT?C	05Fh
	HSEROUT?C	04Bh
	HSEROUT?C	069h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	044h
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	070h
	HSEROUT?C	069h
	HSEROUT?C	064h
	HSEROUT?C	05Fh
	HSEROUT?C	04Bh
	HSEROUT?C	064h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	054h
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	070h
	HSEROUT?C	069h
	HSEROUT?C	064h
	HSEROUT?C	05Fh
	HSEROUT?C	054h
	HSEROUT?C	069h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	043h
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	049h
	HSEROUT?C	05Fh
	HSEROUT?C	043h
	HSEROUT?C	06Ch
	HSEROUT?C	061h
	HSEROUT?C	06Dh
	HSEROUT?C	070h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	04Bh
	HSEROUT?C	04Fh
	HSEROUT?C	029h
	HSEROUT?C	020h
	HSEROUT?C	04Fh
	HSEROUT?C	075h
	HSEROUT?C	074h
	HSEROUT?C	05Fh
	HSEROUT?C	043h
	HSEROUT?C	06Ch
	HSEROUT?C	061h
	HSEROUT?C	06Dh
	HSEROUT?C	070h
	HSEROUT?C	020h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	000h, _Bvar
	LABEL?L	L00117	
	CMPGT?BCL	_Bvar, 003h, L00118
	MUL?BCW	_Bvar, _ColumnWidth, T1
	ADD?CWB	011h, T1, _X
	MOVE?CB	00Dh, _Y
	GOSUB?L	_MoveCursor
	CMPF?BL	_spMode1, L00119
	HSEROUT?C	050h
	HSEROUT?C	043h
	HSEROUT?C	020h
	GOTO?L	L00120
	LABEL?L	L00119	
	HSEROUT?C	050h
	HSEROUT?C	04Fh
	HSEROUT?C	054h
	LABEL?L	L00120	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	00Eh, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	004h
	AOUT?WBW	_pid_Kp, _Bvar, T1
	HSEROUTNUM?W	T1
	HSEROUTIHEX?	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	00Fh, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	004h
	AOUT?WBW	_pid_Ki, _Bvar, T1
	HSEROUTNUM?W	T1
	HSEROUTIHEX?	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	010h, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	004h
	AOUT?WBW	_pid_Kd, _Bvar, T1
	HSEROUTNUM?W	T1
	HSEROUTIHEX?	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	011h, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	000h
	AOUT?BBB	_pid_Ti, _Bvar, T1
	HSEROUTNUM?B	T1
	HSEROUTDEC?	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	012h, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	000h
	AOUT?WBW	_pid_I_Clamp, _Bvar, T1
	HSEROUTNUM?W	T1
	HSEROUTDEC?	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	MOVE?CB	013h, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	000h
	AOUT?WBW	_pid_Out_Clamp, _Bvar, T1
	HSEROUTNUM?W	T1
	HSEROUTDEC?	
	HSEROUT?C	00Dh
	HSEROUT?C	00Ah
	NEXT?BCL	_Bvar, 001h, L00117
	LABEL?L	L00118	
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	032h
	HSEROUT?C	031h
	HSEROUT?C	03Bh
	HSEROUT?C	031h
	HSEROUT?C	048h
	HSEROUT?C	04Dh
	HSEROUT?C	065h
	HSEROUT?C	06Eh
	HSEROUT?C	075h
	HSEROUT?C	03Ah
	HSEROUT?C	020h
	HSEROUT?C	043h
	HSEROUT?C	068h
	HSEROUT?C	061h
	HSEROUT?C	06Eh
	HSEROUT?C	06Eh
	HSEROUT?C	065h
	HSEROUT?C	06Ch
	HSEROUT?C	028h
	HSEROUT?C	031h
	HSEROUT?C	02Dh
	HSEROUT?C	034h
	HSEROUT?C	029h
	HSEROUT?C	02Ch
	HSEROUT?C	020h
	HSEROUT?C	045h
	HSEROUT?C	064h
	HSEROUT?C	069h
	HSEROUT?C	074h
	HSEROUT?C	028h
	HSEROUT?C	04Dh
	HSEROUT?C	050h
	HSEROUT?C	049h
	HSEROUT?C	044h
	HSEROUT?C	054h
	HSEROUT?C	043h
	HSEROUT?C	04Fh
	HSEROUT?C	029h
	HSEROUT?C	02Ch
	HSEROUT?C	020h
	HSEROUT?C	053h
	HSEROUT?C	03Dh
	HSEROUT?C	065h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	065h
	HSEROUT?C	072h
	HSEROUT?C	020h
	HSEROUT?C	053h
	HSEROUT?C	065h
	HSEROUT?C	074h
	HSEROUT?C	050h
	HSEROUT?C	06Fh
	HSEROUT?C	069h
	HSEROUT?C	06Eh
	HSEROUT?C	074h
	HSEROUT?C	02Ch
	HSEROUT?C	020h
	HSEROUT?C	052h
	HSEROUT?C	03Dh
	HSEROUT?C	052h
	HSEROUT?C	065h
	HSEROUT?C	066h
	HSEROUT?C	072h
	HSEROUT?C	065h
	HSEROUT?C	073h
	HSEROUT?C	068h
	GOSUB?L	_DrawBox
	RETURN?	

	LABEL?L	_TempToTerminal	
	CMPF?TL	_TempWD??15, L00121
	HSEROUT?C	02Dh
	LABEL?L	L00121	
	ABS?WW	_TempWD, _TempWD
	HSEROUTCOUNT?C	000h
	DIV?WCW	_TempWD, DS1820_DIG, T1
	HSEROUTNUM?W	T1
	HSEROUTDEC?	

	ASM?
   if (DS1820_DECIMALS > 0)              ; if using decimals

	ENDASM?

	HSEROUT?C	02Eh
	MOD?WCW	_TempWD, DS1820_DIG, _TempWD

	ASM?
       if (DS1820_DECIMALS > 1)          ; with DECIMALS=2, next DIG is 1

	ENDASM?

	HSEROUTCOUNT?C	001h
	DIG?WCW	_TempWD, 001h, T1
	HSEROUTNUM?W	T1
	HSEROUTDEC?	

	ASM?
       endif

	ENDASM?


	ASM?
       if (DS1820_DECIMALS >= 1)         ; with DECIMALS=1, next DIG is 0

	ENDASM?

	HSEROUTCOUNT?C	001h
	DIG?WCW	_TempWD, 000h, T1
	HSEROUTNUM?W	T1
	HSEROUTDEC?	

	ASM?
       endif

	ENDASM?


	ASM?
   endif

	ENDASM?

	RETURN?	

	LABEL?L	_DisplayPID	
	MOVE?CB	005h, _Y
	GOSUB?L	_ColumnData
	MOVE?WW	_pid_Error, _TempWD
	GOSUB?L	_TempToTerminal
	HSEROUT?C	020h
	HSEROUT?C	020h
	MOVE?CB	003h, _Y
	GOSUB?L	_ColumnData
	MOVE?WW	_TempC, _TempWD
	GOSUB?L	_TempToTerminal
	HSEROUT?C	020h
	HSEROUT?C	020h
	MOVE?CB	006h, _Y
	GOSUB?L	_ColumnData
	HSEROUTCOUNT?C	000h
	AOUT?BBB	HeaterDrives, _pid_Channel, T1
	HSEROUTNUM?B	T1
	HSEROUTDEC?	
	HSEROUT?C	020h
	HSEROUT?C	020h
	AOUT?BBB	HeaterDrives, _pid_Channel, T1
	AOUT?WBW	_pid_Out_Clamp, _pid_Channel, T2
	CMPNE?BWL	T1, T2, L00123
	GOSUB?L	_ColumnData
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	034h
	HSEROUT?C	043h
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	031h
	HSEROUT?C	06Dh
	HSEROUT?C	043h
	HSEROUT?C	04Ch
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	030h
	HSEROUT?C	06Dh
	GOTO?L	L00124
	LABEL?L	L00123	
	GOSUB?L	_ColumnData
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	034h
	HSEROUT?C	043h
	HSEROUT?C	020h
	HSEROUT?C	020h
	LABEL?L	L00124	
	MOVE?CB	008h, _Y
	GOSUB?L	_ColumnData
	HSEROUTCOUNT?C	000h
	HSEROUTSNUM?W	_pid_P
	HSEROUTSDEC?	
	HSEROUT?C	020h
	HSEROUT?C	020h
	MOVE?CB	009h, _Y
	GOSUB?L	_ColumnData
	HSEROUTCOUNT?C	000h
	AOUT?WBW	_pid_I, _pid_Channel, T1
	HSEROUTSNUM?W	T1
	HSEROUTSDEC?	
	HSEROUT?C	020h
	HSEROUT?C	020h
	AOUT?WBW	_pid_I, _pid_Channel, T1
	AOUT?WBW	_pid_I_Clamp, _pid_Channel, T2
	CMPNE?WWL	T1, T2, L00125
	GOSUB?L	_ColumnData
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	034h
	HSEROUT?C	043h
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	031h
	HSEROUT?C	06Dh
	HSEROUT?C	043h
	HSEROUT?C	04Ch
	HSEROUT?C	020h
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	030h
	HSEROUT?C	06Dh
	GOTO?L	L00126
	LABEL?L	L00125	
	GOSUB?L	_ColumnData
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	034h
	HSEROUT?C	043h
	HSEROUT?C	020h
	HSEROUT?C	020h
	HSEROUT?C	020h
	LABEL?L	L00126	
	MOVE?CB	00Ah, _Y
	GOSUB?L	_ColumnData
	HSEROUTCOUNT?C	000h
	HSEROUTSNUM?W	_pid_D
	HSEROUTSDEC?	
	HSEROUT?C	020h
	HSEROUT?C	020h
	RETURN?	

	LABEL?L	_ShowError	
	LOOKUP?BCLB	_pid_Channel, 004h, L00010, _Bvar
	LURET?C	083h
	LURET?C	0C3h
	LURET?C	08Bh
	LURET?C	0CBh

	LABEL?L	L00010	
	LCDOUT?C	0FEh
	LCDOUT?B	_Bvar
	LCDOUT?C	045h
	LCDOUT?C	052h
	LCDOUT?C	052h
	MUL?BCW	_pid_Channel, _ColumnWidth, T1
	ADD?CWB	011h, T1, _X
	MOVE?CB	003h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	045h
	HSEROUT?C	072h
	HSEROUT?C	072h
	HSEROUT?C	06Fh
	HSEROUT?C	072h
	RETURN?	

	LABEL?L	_ColumnData	
	MUL?BCW	_pid_Channel, _ColumnWidth, T1
	ADD?CWB	011h, T1, _X

	LABEL?L	_MoveCursor	
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUTCOUNT?C	000h
	HSEROUTNUM?B	_Y
	HSEROUTDEC?	
	HSEROUT?C	03Bh
	HSEROUTCOUNT?C	000h
	HSEROUTNUM?B	_X
	HSEROUTDEC?	
	HSEROUT?C	048h
	RETURN?	

	LABEL?L	_DrawBox	
	MUL?BCW	_EditChannel, _ColumnWidth, T1
	ADD?CWB	00Fh, T1, _X
	MOVE?CB	002h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	035h
	HSEROUT?C	06Dh
	HSEROUT?C	_TL
	HSEROUTCOUNT?C	008h
	HSEROUTREP?C	_HL
	HSEROUT?C	_TR
	MOVE?CB	003h, _Y
	LABEL?L	L00127	
	CMPGT?BCL	_Y, 013h, L00128
	GOSUB?L	_MoveCursor
	HSEROUT?C	_VL
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUTCOUNT?C	000h
	HSEROUTNUM?C	008h
	HSEROUTDEC?	
	HSEROUT?C	043h
	HSEROUT?C	_VL
	NEXT?BCL	_Y, 001h, L00127
	LABEL?L	L00128	
	MOVE?CB	014h, _Y
	GOSUB?L	_MoveCursor
	HSEROUT?C	_BL
	HSEROUTCOUNT?C	008h
	HSEROUTREP?C	_HL
	HSEROUT?C	_BR
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUT?C	033h
	HSEROUT?C	030h
	HSEROUT?C	06Dh
	RETURN?	

	LABEL?L	_ClearBox	
	MUL?BCW	_EditChannel, _ColumnWidth, T1
	ADD?CWB	00Fh, T1, _X
	MOVE?CB	002h, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	_ColumnWidth
	HSEROUTREP?C	020h
	MOVE?CB	003h, _Y
	LABEL?L	L00129	
	CMPGT?BCL	_Y, 013h, L00130
	GOSUB?L	_MoveCursor
	HSEROUT?C	020h
	HSEROUT?C	01Bh
	HSEROUT?C	05Bh
	HSEROUTCOUNT?C	000h
	HSEROUTNUM?C	008h
	HSEROUTDEC?	
	HSEROUT?C	043h
	HSEROUT?C	020h
	NEXT?BCL	_Y, 001h, L00129
	LABEL?L	L00130	
	MOVE?CB	014h, _Y
	GOSUB?L	_MoveCursor
	HSEROUTCOUNT?C	_ColumnWidth
	HSEROUTREP?C	020h
	RETURN?	

	END
