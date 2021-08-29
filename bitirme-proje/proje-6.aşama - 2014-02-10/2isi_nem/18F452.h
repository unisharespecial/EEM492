//////// Standard Header file for the PIC18F452 device ////////////////
#device PIC18F452
#nolist
//////// Program memory: 16384x16  Data RAM: 1536  Stack: 31
//////// I/O: 34   Analog Pins: 8
//////// Data EEPROM: 256
//////// C Scratch area: 00   ID Location: 200000
//////// Fuses: LP,XT,HS,RC,EC,EC_IO,H4,RC_IO,PROTECT,NOPROTECT,OSCSEN
//////// Fuses: NOOSCSEN,NOBROWNOUT,BROWNOUT,WDT1,WDT2,WDT4,WDT8,WDT16,WDT32
//////// Fuses: WDT64,WDT128,WDT,NOWDT,BORV20,BORV27,BORV42,BORV45,PUT,NOPUT
//////// Fuses: CCP2C1,CCP2B3,NOSTVREN,STVREN,NODEBUG,DEBUG,NOLVP,LVP,WRT
//////// Fuses: NOWRT,NOWRTD,WRTD,NOWRTB,WRTB,WRTC,NOWRTC,CPD,NOCPD,CPB
//////// Fuses: NOCPB,EBTR,NOEBTR,EBTRB,NOEBTRB
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_x_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A0  31744
#define PIN_A1  31745
#define PIN_A2  31746
#define PIN_A3  31747
#define PIN_A4  31748
#define PIN_A5  31749
#define PIN_A6  31750

#define PIN_B0  31752
#define PIN_B1  31753
#define PIN_B2  31754
#define PIN_B3  31755
#define PIN_B4  31756
#define PIN_B5  31757
#define PIN_B6  31758
#define PIN_B7  31759

#define PIN_C0  31760
#define PIN_C1  31761
#define PIN_C2  31762
#define PIN_C3  31763
#define PIN_C4  31764
#define PIN_C5  31765
#define PIN_C6  31766
#define PIN_C7  31767

#define PIN_D0  31768
#define PIN_D1  31769
#define PIN_D2  31770
#define PIN_D3  31771
#define PIN_D4  31772
#define PIN_D5  31773
#define PIN_D6  31774
#define PIN_D7  31775

#define PIN_E0  31776
#define PIN_E1  31777
#define PIN_E2  31778

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int8
#define BOOLEAN int1

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants returned from RESTART_CAUSE() are:

#define WDT_TIMEOUT       7    
#define MCLR_FROM_SLEEP  11    
#define MCLR_FROM_RUN    15    
#define NORMAL_POWER_UP  12    
#define BROWNOUT_RESTART 14    
#define WDT_FROM_SLEEP   3     
#define RESET_INSTRUCTION 0    
////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Constants used for SETUP_TIMER_0() are:
#define T0_INTERNAL   0
#define T0_EXT_L_TO_H 32
#define T0_EXT_H_TO_L 48

#define T0_DIV_1      8
#define T0_DIV_2      0
#define T0_DIV_4      1
#define T0_DIV_8      2
#define T0_DIV_16     3
#define T0_DIV_32     4
#define T0_DIV_64     5
#define T0_DIV_128    6
#define T0_DIV_256    7

#define T0_OFF        0x80  

#define T0_8_BIT      0x40  

#define RTCC_INTERNAL   0      // The following are provided for compatibility
#define RTCC_EXT_L_TO_H 32     // with older compiler versions
#define RTCC_EXT_H_TO_L 48
#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7
#define RTCC_OFF        0x80  
#define RTCC_8_BIT      0x40  

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
// WDT base is 18ms
//
#define WDT_ON      0x100   
#define WDT_OFF     0       


////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_INTERNAL         0x85
#define T1_EXTERNAL         0x87
#define T1_EXTERNAL_SYNC    0x83

#define T1_CLK_OUT          8

#define T1_DIV_BY_1         0
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6

////////////////////////////////////////////////////////////////// Timer 3
// Timer 3 Functions: SETUP_TIMER_3, GET_TIMER3, SET_TIMER3
// Constants used for SETUP_TIMER_3() are:
//      (or (via |) together constants from each group)
#define T3_DISABLED         0
#define T3_INTERNAL         0x85
#define T3_EXTERNAL         0x87
#define T3_EXTERNAL_SYNC    0x83

#define T3_DIV_BY_1         0
#define T3_DIV_BY_2         0x10
#define T3_DIV_BY_4         0x20
#define T3_DIV_BY_8         0x30

// OR in one of the following to use timer 3 with a CCP unit
#define  T3_CCP1_TO_2  0x48
#define  T3_CCP2       0x8

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_INT_AND_TOGGLE      0x2       
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
//#define CCP_USE_TIMER3                0x100  OBSOLETE, SEE TIMER-3     
#word   CCP_1    =                      getenv("SFR:CCPR1L")
#byte   CCP_1_LOW=                      getenv("SFR:CCPR1L")
#byte   CCP_1_HIGH=                     getenv("SFR:CCPR1H")
#word   CCP_2    =                      getenv("SFR:CCPR2L")
#byte   CCP_2_LOW=                      getenv("SFR:CCPR2L")
#byte   CCP_2_HIGH=                     getenv("SFR:CCPR2H")
////////////////////////////////////////////////////////////////// PSP
// PSP Functions: SETUP_PSP, PSP_INPUT_FULL(), PSP_OUTPUT_FULL(),
//                PSP_OVERFLOW(), INPUT_D(), OUTPUT_D()
// PSP Variables: PSP_DATA
// Constants used in SETUP_PSP() are:
#define PSP_ENABLED                     0x10
#define PSP_DISABLED                    0

#byte  PSP_DATA=    0xF83               

////////////////////////////////////////////////////////////////// SPI
// SPI Functions: SETUP_SPI, SPI_WRITE, SPI_READ, SPI_DATA_IN
// Constants used in SETUP_SPI() are:
#define SPI_MASTER       0x20
#define SPI_SLAVE        0x24
#define SPI_L_TO_H       0
#define SPI_H_TO_L       0x10
#define SPI_CLK_DIV_4    0
#define SPI_CLK_DIV_16   1
#define SPI_CLK_DIV_64   2
#define SPI_CLK_T2       3
#define SPI_SS_DISABLED  1

#define SPI_SAMPLE_AT_END 0x8000
#define SPI_XMIT_L_TO_H  0x4000

////////////////////////////////////////////////////////////////// UART
// Constants used in setup_uart() are:
// FALSE - Turn UART off
// TRUE  - Turn UART on
#define UART_ADDRESS           2
#define UART_DATA              4
////////////////////////////////////////////////////////////////// VREF
// Constants used in setup_low_volt_detect() are:
//
#define LVD_LVDIN   0x1F
#define LVD_46 0x1E
#define LVD_43 0x1D
#define LVD_41 0x1C
#define LVD_40 0x1B
#define LVD_37 0x1A
#define LVD_36 0x19
#define LVD_34 0x18
#define LVD_31 0x17
#define LVD_29 0x16
#define LVD_28 0x15
#define LVD_26 0x14
#define LVD_25 0x13
#define LVD_23 0x12
#define LVD_21 0x11



////////////////////////////////////////////////////////////////// INTERNAL RC
// Constants used in setup_oscillator() are:
#define OSC_TIMER1  1
#define OSC_NORMAL  0


////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// Constants used for SETUP_ADC() are:
#define ADC_OFF                 0              // ADC Off
#define ADC_CLOCK_DIV_2   0x10000
#define ADC_CLOCK_DIV_4    0x4000
#define ADC_CLOCK_DIV_8    0x0040
#define ADC_CLOCK_DIV_16   0x4040
#define ADC_CLOCK_DIV_32   0x0080
#define ADC_CLOCK_DIV_64   0x4080
#define ADC_CLOCK_INTERNAL 0x00c0              // Internal 2-6us

// Constants used in SETUP_ADC_PORTS() are:
#define NO_ANALOGS                           7    // None
#define ALL_ANALOG                           0    // A0 A1 A2 A3 A5 E0 E1 E2 
#define AN0_AN1_AN2_AN4_AN5_AN6_AN7_VSS_VREF 1    // A0 A1 A2 A5 E0 E1 E2 VRefh=A3     
#define AN0_AN1_AN2_AN3_AN4                  2    // A0 A1 A2 A3 A5          
#define AN0_AN1_AN2_AN4_VSS_VREF             3    // A0 A1 A2 A4 VRefh=A3              
#define AN0_AN1_AN3                          4    // A0 A1 A3
#define AN0_AN1_VSS_VREF                     5    // A0 A1 VRefh=A3
#define AN0_AN1_AN4_AN5_AN6_AN7_VREF_VREF 0x08    // A0 A1 A5 E0 E1 E2 VRefh=A3 VRefl=A2     
#define AN0_AN1_AN2_AN3_AN4_AN5           0x09    // A0 A1 A2 A3 A5 E0        
#define AN0_AN1_AN2_AN4_AN5_VSS_VREF      0x0A    // A0 A1 A2 A5 E0 VRefh=A3           
#define AN0_AN1_AN4_AN5_VREF_VREF         0x0B    // A0 A1 A5 E0 VRefh=A3 VRefl=A2           
#define AN0_AN1_AN4_VREF_VREF             0x0C    // A0 A1 A4 VRefh=A3 VRefl=A2              
#define AN0_AN1_VREF_VREF                 0x0D    // A0 A1 VRefh=A3 VRefl=A2
#define AN0                               0x0E    // A0
#define AN0_VREF_VREF                     0x0F    // A0 VRefh=A3 VRefl=A2
#define ANALOG_RA3_REF         0x1         //!old only provided for compatibility
#define A_ANALOG               0x2         //!old only provided for compatibility  
#define A_ANALOG_RA3_REF       0x3         //!old only provided for compatibility  
#define RA0_RA1_RA3_ANALOG     0x4         //!old only provided for compatibility
#define RA0_RA1_ANALOG_RA3_REF 0x5         //!old only provided for compatibility
#define ANALOG_RA3_RA2_REF              0x8   //!old only provided for compatibility
#define ANALOG_NOT_RE1_RE2              0x9   //!old only provided for compatibility  
#define ANALOG_NOT_RE1_RE2_REF_RA3      0xA   //!old only provided for compatibility  
#define ANALOG_NOT_RE1_RE2_REF_RA3_RA2  0xB   //!old only provided for compatibility  
#define A_ANALOG_RA3_RA2_REF            0xC   //!old only provided for compatibility  
#define RA0_RA1_ANALOG_RA3_RA2_REF      0xD   //!old only provided for compatibility
#define RA0_ANALOG                      0xE   //!old only provided for compatibility
#define RA0_ANALOG_RA3_RA2_REF          0xF   //!old only provided for compatibility


// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6





////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      CLEAR_INTERRUPT(), INTERRUPT_ACTIVE(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0xF2C0
#define INT_RTCC                  0x00F220
#define INT_TIMER0                0x00F220
#define INT_TIMER1                0x009D01
#define INT_TIMER2                0x009D02
#define INT_TIMER3                0x00A002
#define INT_EXT_L2H               0x5000F210
#define INT_EXT_H2L               0x6000F210
#define INT_EXT                   0x00F210
#define INT_EXT1_L2H              0x5001F008
#define INT_EXT1_H2L              0x6001F008
#define INT_EXT1                  0x00F008
#define INT_EXT2_L2H              0x5002F010
#define INT_EXT2_H2L              0x6002F010
#define INT_EXT2                  0x00F010
#define INT_RB                    0x00FFF208
#define INT_PSP                   0x009D80
#define INT_AD                    0x009D40
#define INT_RDA                   0x009D20
#define INT_TBE                   0x009D10
#define INT_SSP                   0x009D08
#define INT_CCP1                  0x009D04
#define INT_CCP2                  0x00A001
#define INT_BUSCOL                0x00A008
#define INT_LOWVOLT               0x00A004
#define INT_EEPROM                0x00A010

#list
