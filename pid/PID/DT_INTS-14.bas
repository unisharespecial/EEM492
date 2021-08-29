'****************************************************************
'*  Name    : DT_INTS-14.bas                                    *
'*  Author  : Darrel Taylor                                     *
'*  Version : 0.93 BETA                                         *
'*  Date    : JAN 29, 2006                                      *
'****************************************************************
'* Rev 0.93  Fixed CMIF and EEIF problem with older PIC's       *
'*           that have the Flags in PIR1 instead of PIR2        *
'* Rev 0.92  solves a "Missed Interrupt" and                    *
'*           banking switching problem                          *
'****************************************************************
DEFINE  INTHAND  INT_ENTRY

wsave       var byte    $20     SYSTEM      ' location for W if in bank0
;wsave       var byte    $70     SYSTEM     ' alternate save location for W 
                                            ' if using $70, comment out wsave1-3

' --- IF any of these three lines cause an error ?? ---------------------------- 
'       Comment them out to fix the problem ----
' -- It depends on which Chip you are using, as to which variables are needed --
wsave1      var byte    $A0     SYSTEM      ' location for W if in bank1
wsave2      var byte    $120    SYSTEM      ' location for W if in bank2
wsave3      var byte    $1A0    SYSTEM      ' location for W if in bank3
' ------------------------------------------------------------------------------

ssave       var byte    BANK0   SYSTEM      ' location for STATUS register
psave       var byte    BANK0   SYSTEM      ' location for PCLATH register
fsave       var byte    BANK0   SYSTEM      ' location for FSR register
RetAddr     VAR WORD    BANK0   
Serviced    VAR BIT

Asm
asm = 0
ASM = 0
pbp = 1
PBP = 1
YES = 1
yes = 1
NO = 0
no = 0
ENDASM

ASM
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

ENDASM

asm
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
endasm


asm
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
ENDASM

ASM
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
    
EndAsm

ASM
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

ENDASM


