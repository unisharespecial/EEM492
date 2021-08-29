// RC Joystick 430mHz
// For use with Arduino Nano V3.0
// Ian Johnston 28/04/2010
//
// If you would like to help support future projects like these then please
// make a small PayPal donation via my website www.ianjohnston.com
// Thanks!
//
// Ver 1.6 - Now using Timer1 to set 22mS refresh for PPM output.
//           Dual rates are implemented but need custom setup.
//           Trimming is not working.
//           Battery monitor sub tweaked
//           Adjusted timing off various subs
//           Various tweaks to LCD & battery monitor
//
// LCD type = LCD0821 Matrix Orbital (serial TTL)

// Make sure LCD0821.pde is in the same dir as RCJoystick_IanJ_V2.pde

int DI_2 = 0;       // Dig In Ch.2 var
int DI_3 = 0;       // Dig In Ch.3 var
int DI_4 = 0;       // Dig In Ch.4 var
int DI_5 = 0;       // Dig In Ch.5 var
int DI_6 = 0;       // Dig In Ch.6 var
int DI_11 = 0;      // Dig In Ch.11 var

int AI_Pin_TIpot = 4;    // Ana In Pin - TI  potentiometer
int AI_Pin_Throt = 3;    // Ana In Pin - Throttle potentiometer
int AI_Pin_Rudde = 2;    // Ana In Pin - Rudder potentiometer
int AI_Pin_Eleva = 0;    // Ana In Pin - Elevator potentiometer
int AI_Pin_Aeler = 1;    // Ana In Pin - Aeleron potentiometer
int AI_Pin_Batte = 7;    // Ana In Pin - Battery Voltage
int AI_Raw_TIpot;        // Ana In Ch.2 raw var - 0->1023
int AI_Raw_Throt;        // Ana In Ch.3 raw var - 0->1023
int AI_Raw_Rudde;        // Ana In Ch.4 raw var - 0->1023
int AI_Raw_Eleva;        // Ana In Ch.4 raw var - 0->1023
int AI_Raw_Aeler;        // Ana In Ch.4 raw var - 0->1023
float AI_Raw_Batte;      // Ana In Ch.4 raw var - 0->1023 (requires DP for batt voltage)
int AI_TIpot;           // Ana In Ch.2 raw var - 0->1023 compensated
int AI_Throt;           // Ana In Ch.3 raw var - 0->1023 compensated
int AI_Rudde;           // Ana In Ch.4 raw var - 0->1023 compensated
int AI_Eleva;           // Ana In Ch.4 raw var - 0->1023 compensated
int AI_Aeler;           // Ana In Ch.4 raw var - 0->1023 compensated

float AI_Batte;         // Ana In Ch.4 raw var - 0->1023 compensated (requires DP for batt voltage)
int AI_Batte_percent = 0; // Battery %
int AI_Battefloat = 0;

int tick = 0; // Used for various timing of subs
int tick2 = 0; // Used for various timing
int slowflag;

int Aeleron_uS = 700;
int Elevator_uS = 700;
int Throttle_uS = 700;
int Rudder_uS = 700;
int TI_uS = 700;
int TIsw_uS = 700;

int RatesHIMIDLO = 2; // Default is MID rates
int TrimSetting = 0;

int Fixed_uS = 300;       // PPM frame fixed LOW phase
int pulseMin = 700;	      // pulse minimum width in uS
int pulseMax = 1700;	  // pulse maximum width in uS

float DualrateMultAel = 0.5; // Dual rate mult
float DualrateMultEle = 0.5; // Dual rate mult
float DualrateMultThr = 0.9; // Dual rate mult
float DualrateMultRud = 0.7; // Dual rate mult
float DualrateMultTI = 0.9;  // Dual rate mult
int DualrateAdjAel = 187;    // Dual rate mid adjustment
int DualrateAdjEle = 231;    // Dual rate mid adjustment
int DualrateAdjThr = 0;	     // Dual rate mid adjustment
int DualrateAdjRud = 112;	 // Dual rate mid adjustment
int DualrateAdjTI = 0;	     // Dual rate mid adjustment

int outPinTEST = 8;       // digital pin 8
int outPinPPM = 10;       // digital pin 10
int outPinBuzz = 12;      // digital pin 12
int inPinD2 = 2;          // digital pin 2
int inPinD3 = 3;          // digital pin 3
int inPinD4 = 4;          // digital pin 4
int inPinD5 = 5;          // digital pin 5 - HI/LO rates set
int inPinD6 = 6;          // digital pin 6
int inPinD11 = 11;        // digital pin 11


ISR(TIMER1_COMPA_vect) {
    ppmoutput(); // Jump to ppmoutput subroutine
	tick = tick + 1;  // update timing tick for subs
	tick2 = tick2 + 1;  // update tick
}

void setup() {

 // setup I/O
  pinMode(outPinPPM, OUTPUT);   // sets the digital pin as output
  pinMode(outPinBuzz, OUTPUT);  // sets the digital pin as output

  pinMode(inPinD2, INPUT);      // sets the digital pin as input
  digitalWrite(inPinD2, HIGH);  // turn on pull-up resistor
  pinMode(inPinD3, INPUT);      // sets the digital pin as input
  digitalWrite(inPinD3, HIGH);  // turn on pull-up resistor
  pinMode(inPinD4, INPUT);      // sets the digital pin as input
  digitalWrite(inPinD4, HIGH);  // turn on pull-up resistor
  pinMode(inPinD5, INPUT);      // sets the digital pin as input
  digitalWrite(inPinD5, HIGH);  // turn on pull-up resistor  
  pinMode(inPinD11, INPUT);     // sets the digital pin as input
  digitalWrite(inPinD11, HIGH); // turn on pull-up resistor

 // Power up beep-beep
  digitalWrite(outPinBuzz, HIGH);  // Turn on buzzer
  delay (50);
  digitalWrite(outPinBuzz, LOW);  // Turn off buzzer

 // LCD setup
  Serial.begin(19200);     //start communications with LCD screen Matrix Orbital LCD0821
  Serial.print(12, BYTE);
  autoscrolloff();
  autolinewrapoff();
  blockcursoroff();
  underlinecursoroff();
  backlightOn(0);  // turn the backlight (minutes)
  setBrightness(100);
  clearLCD();

 // Setup timer
  TCCR1A = B00110001; // Compare register B used in mode '3'
  // TCCR1A = B00100001; // Invert output
  TCCR1B = B00010010; // WGM13 and CS11 set to 1
  TCCR1C = B00000000; // All set to 0
  TIMSK1 = B00000010; // Interrupt on compare B
  TIFR1  = B00000010; // Interrupt on compare B
  OCR1A = 22000; // 22mS PPM output refresh
  OCR1B = 1000;
}


void loop() { // Main loop
  readanainputsmap(); // Run sub - read ana inputs & map
  checklimits();      // Run sub - check individual channel PPM limits

  if (tick >= 11) {     // only run certain subs every 1/4 sec or so (22mS * 11 = 242mS)
	  tick = 0;
      switchesRates();    // Run sub - read panel switches
	  batterymonitor();   // Run sub - check battery
  }
  
  // generate slow changing flag, about 2sec on/off
  if (tick2 <= 50) {
	  slowflag = 0;
  }
  if (tick2 >= 50 && tick2 <=100) {
	  slowflag = 1;
  }
  if (tick2 >= 100) {
	  slowflag = 0;
	  tick2 = 0;
  } 
  
}


void readanainputsmap() { // read ana inputs & map
 // Read all necessary analogue ports
   AI_Raw_TIpot = analogRead(AI_Pin_TIpot);
   AI_Raw_Throt = analogRead(AI_Pin_Throt);
   AI_Raw_Rudde = analogRead(AI_Pin_Rudde);
   AI_Raw_Eleva = analogRead(AI_Pin_Eleva);
   AI_Raw_Aeler = analogRead(AI_Pin_Aeler);
   AI_Raw_Batte = analogRead(AI_Pin_Batte);

 // Compensate for discrepancy in pot inputs including centering offset.
 // Also use this to invert inputs if necessary (swap x1 & y1)
 // y=mx+c, x to y scales to x1 to y1
   AI_TIpot = map(AI_Raw_TIpot, 0, 1023, 1023, 0) + 0; // TI pot
   AI_Throt = map(AI_Raw_Throt, 0, 1023, -25, 1150) - 0; // Throttle
   AI_Rudde = map(AI_Raw_Rudde, 0, 1023, 0, 1023) + 0; // Rudder
   AI_Eleva = map(AI_Raw_Eleva, 0, 1023, 0, 1023) + 0; // Elevator
   AI_Aeler = map(AI_Raw_Aeler, 0, 1023, 0, 1023) + 0; // Aeleron
   AI_Batte = AI_Raw_Batte / 36.2; // Battery

 // Map analogue inputs to PPM rates for each of the channels
   Aeleron_uS = (AI_Aeler * DualrateMultAel) + pulseMin + DualrateAdjAel;
   Elevator_uS = (AI_Eleva * DualrateMultEle) + pulseMin + DualrateAdjEle;
   Throttle_uS = (AI_Throt * DualrateMultThr) + pulseMin + DualrateAdjThr;
   Rudder_uS = (AI_Rudde * DualrateMultRud) + pulseMin + DualrateAdjRud;
   TI_uS = (AI_TIpot * DualrateMultTI) + pulseMin + DualrateAdjTI;
}


void checklimits() { // check limits sub
  if (Aeleron_uS < 700) Aeleron_uS = 700;     // Min
  if (Aeleron_uS > 1700) Aeleron_uS = 1700;   // Max   
  if (Elevator_uS < 700) Elevator_uS = 700;   // Min
  if (Elevator_uS > 1700) Elevator_uS = 1700; // Max 
  if (Throttle_uS < 700) Throttle_uS = 700;   // Min
  if (Throttle_uS > 1700) Throttle_uS = 1700; // Max 
  if (Rudder_uS < 700) Rudder_uS = 700;       // Min
  if (Rudder_uS > 1700) Rudder_uS = 1700;     // Max   
  if (TI_uS < 700) TI_uS = 700;               // Min
  if (TI_uS > 1700) TI_uS = 1700;             // Max 
}


void batterymonitor() { // check battery sub

	if (AI_Batte > 10.8) { // Minimum voltage for 3S lipo = 10.8v	
        digitalWrite(outPinBuzz, LOW);  // Turn off buzzer
    }
    if (AI_Batte < 10.8 && slowflag == 1) {
	    digitalWrite(outPinBuzz, HIGH);  // Turn on buzzer
    } else {
	    digitalWrite(outPinBuzz, LOW);  // Turn off buzzer
	}
	
	AI_Battefloat = AI_Batte * 100; // map doesn't work with float, only int so x100 gets around this
	AI_Batte_percent = map(AI_Battefloat, 1080, 1260, 0, 100) + 0; // map battery voltage to percentage 10.8v to 12.6v
	if (AI_Batte_percent < 0) {
	   AI_Batte_percent = 0;
	}
	if (AI_Batte_percent > 100) {
	   AI_Batte_percent = 100;
	}
}


void ppmoutput() { // PPM output sub
 // test pulse - used to trigger scope
 // digitalWrite(outPinTEST, LOW);
 // delayMicroseconds(100);    // Hold
 // digitalWrite(outPinTEST, HIGH);
  
 // Channel 1 - Aeleron
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);
  delayMicroseconds(Aeleron_uS);  // Hold for Aeleron_uS microseconds      

 // Channel 2 - Elevator 
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);
  delayMicroseconds(Elevator_uS); // Hold for Elevator_uS microseconds      

 // Channel 3 - Throttle
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);
  delayMicroseconds(Throttle_uS); // Hold for Throttle_uS microseconds      

 // Channel 4 - Rudder
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);
  delayMicroseconds(Rudder_uS);   // Hold for Rudder_uS microseconds

 // Channel 5 - TI Switch
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);
  delayMicroseconds(TIsw_uS);     // Hold for TIsw_uS microseconds        

 // Channel 6 - TI pot
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);
  delayMicroseconds(TI_uS);       // Hold for TI_uS microseconds  

 // Synchro pulse
  digitalWrite(outPinPPM, LOW);
  delayMicroseconds(Fixed_uS);    // Hold
  digitalWrite(outPinPPM, HIGH);  // Start Synchro pulse
}


void switchesRates() {
    if (digitalRead(inPinD5) == 0) {      // HI/MID/LO setting
	    backlightOn(0);
		digitalWrite(outPinBuzz, HIGH);   // Turn on buzzer	
	    delay(25);
		RatesHIMIDLO = RatesHIMIDLO + 1;
		if (RatesHIMIDLO == 4) { RatesHIMIDLO = 1; }
		digitalWrite(outPinBuzz, LOW);   // Turn off buzzer
    }

    if (RatesHIMIDLO == 3) {  // High rate
		TrimSetting = 0;
		DualrateMultAel = 1.0;
        DualrateMultEle = 1.0;
		DualrateMultThr = 1.0;
		DualrateMultRud = 1.0;
		DualrateMultTI = 1.0;
        DualrateAdjAel = 0;
        DualrateAdjEle = 0;
		DualrateAdjThr = 0;
		DualrateAdjRud = 0;
		DualrateAdjTI = 0;
		cursorSet(1,2);
        Serial.println("Rates=HI");
	}
    if (RatesHIMIDLO == 2) {  // Mid rate
		TrimSetting = 0;
		DualrateMultAel = 0.7;
		DualrateMultEle = 0.7;
		DualrateMultThr = 1.0;
		DualrateMultRud = 0.7;
		DualrateMultTI = 1.0;
		DualrateAdjAel = 187;
	    DualrateAdjEle = 120;
		DualrateAdjThr = 0;
		DualrateAdjRud = 120;
		DualrateAdjTI = 0;
	    cursorSet(1,2);
        Serial.println("Rates=MI");
    }
	
    if (RatesHIMIDLO == 1) {  // LO rate
		TrimSetting = 0;
		DualrateMultAel = 0.5;
		DualrateMultEle = 0.5;
		DualrateMultThr = 1.0;
		DualrateMultRud = 0.5;
		DualrateMultTI = 1.0;
		DualrateAdjAel = 270;
	    DualrateAdjEle = 220;
		DualrateAdjThr = 0;
		DualrateAdjRud = 215;
		DualrateAdjTI = 0;
	    cursorSet(1,2);
        Serial.println("Rates=LO");
    }	

/*
    if (digitalRead(inPinD2) == 0) {      // Trim setting
		digitalWrite(outPinBuzz, HIGH);   // Turn on buzzer	
		if (TrimSetting == 3) {
	        cursorSet(1,2);
            Serial.println("-READY- ");
		}
		TrimSetting = TrimSetting + 1;
		if (TrimSetting == 4) { TrimSetting = 0; }
	    delay(25);
		digitalWrite(outPinBuzz, LOW);   // Turn off buzzer
    }

    if (TrimSetting == 1) {              // AEL Trim setting
		RatesHIMIDLO = 0;
		cursorSet(1,2);
        Serial.println("AEL Trim");
		// code to adjust trim will go here
    }	

    if (TrimSetting == 2) {              // ELE Trim setting
		RatesHIMIDLO = 0;
		cursorSet(1,2);
        Serial.println("ELE Trim");
		// code to adjust trim will go here
    }	
	
    if (TrimSetting == 3) {              // RUD Trim setting
		RatesHIMIDLO = 0;
		cursorSet(1,2);
        Serial.println("RUD Trim");
		// code to adjust trim will go here
    }		
*/
	
    if (digitalRead(inPinD11) == 1) {    // TI Switch	
        TIsw_uS = 1700;
    } else {
	    TIsw_uS = 750;
    }	
	
    if (AI_Batte_percent < 10) {
	cursorSet(1,1); Serial.println(AI_Batte_percent);
	cursorSet(2,1); Serial.println("%");
    cursorSet(3,1); Serial.println("  ");
	cursorSet(5,1); Serial.println(AI_Batte);
    }
	
	if (AI_Batte_percent >= 10 && AI_Batte_percent < 100) {
	cursorSet(1,1); Serial.println(AI_Batte_percent);
	cursorSet(3,1); Serial.println("%");
    cursorSet(4,1); Serial.println(" ");
	cursorSet(5,1); Serial.println(AI_Batte);
    }
	
    if (AI_Batte_percent >= 100) {
	cursorSet(1,1); Serial.println(AI_Batte_percent);
	cursorSet(4,1); Serial.println("%");
	cursorSet(5,1); Serial.println(AI_Batte);
    }
	
}

