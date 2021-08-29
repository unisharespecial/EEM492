// Matrix Orbital LCD0821
// By Ian Johnston 2/4/10

// clear the LCD
void clearLCD(){
  Serial.print(254, BYTE);
  //Serial.print(12, BYTE);
  Serial.print(88, BYTE);
}


// start a new line
void newLine() { 
  Serial.print(254, BYTE);
  Serial.print(10, BYTE); 
}


// move the cursor to the home position
void cursorHome(){
  Serial.print(254, BYTE);
  Serial.print(72, BYTE);
}


// move the cursor to a specific place
// e.g.: cursorSet(3,2) sets the cursor to x = 3 and y = 2
void cursorSet(int xpos, int ypos){  
  Serial.print(254, BYTE);
  Serial.print(71, BYTE);               
  Serial.print(xpos, BYTE); //Column position   
  Serial.print(ypos, BYTE); //Row position 
} 


// backspace and erase previous character
void backSpace() { 
  Serial.print(254, BYTE);
  Serial.print(8, BYTE); 
}


// move cursor left
void cursorLeft(){    
  Serial.print(254, BYTE); 
  Serial.print(76, BYTE);   
}


// move cursor right
void cursorRight(){
  Serial.print(254, BYTE); 
  Serial.print(77, BYTE);   
}


// set LCD remember, 0 (no) or 1 (yes)
void setRemember(int remember){
  Serial.print(254, BYTE); 
  Serial.print(147, BYTE);
  Serial.print(remember);   
}


// set LCD data lock, 0 = unlock
void setDatalock(int datalock){
  Serial.print(254, BYTE); 
  Serial.print(202, BYTE);   
  Serial.print(245, BYTE);
  Serial.print(160, BYTE);  
  Serial.print(datalock);   
}


// set LCD data lock set n save
void setDatalocksetnsave(int datalocksetnsave){
  Serial.print(254, BYTE); 
  Serial.print(203, BYTE);   
  Serial.print(245, BYTE);
  Serial.print(160, BYTE);  
  Serial.print(datalocksetnsave);   
}


// set LCD startup screen
void setStartupLCD(){
  Serial.print(254, BYTE); 
  Serial.print(64, BYTE);   
  Serial.print("HELLO...");   
}


// set LCD Init medium chars
void setInitMediumLCD(){
  Serial.print(254, BYTE); 
  Serial.print(109, BYTE);   
}


// set LCD read version number
void setReadVersionNoLCD(){
  Serial.print(254, BYTE); 
  Serial.print(54, BYTE);   
}


// set LCD read lcd type
void setReadModuleTypeLCD(){
  Serial.print(254, BYTE); 
  Serial.print(55, BYTE);   
}


// set LCD Init horizontal bars
void setHorizontalBarsLCD(){
  Serial.print(254, BYTE); 
  Serial.print(104, BYTE);   
}


// set LCD Place medium chars
void setPlaceMediumLCD(){
  Serial.print(254, BYTE); 
  Serial.print(111, BYTE);
  Serial.print(1, BYTE); 
  Serial.print(1, BYTE); 
  Serial.print("A"); // testing
}


// set LCD contrast 0-255
void setContrast(int contrast){
  Serial.print(254, BYTE); 
  Serial.print(80, BYTE);   
  Serial.print(contrast);   
}


// set LCD brightness 0-255
void setBrightness(int brightness){
  Serial.print(254, BYTE); 
  Serial.print(153, BYTE);   
  Serial.print(brightness);   
}


// turn on backlight 0-100mins
void backlightOn(int minutes){
  Serial.print(254, BYTE); 
  Serial.print(66, BYTE);
  minutes = 0;  
  Serial.print(minutes); // use 0 minutes to turn the backlight on indefinitely   
}


// turn off backlight
void backlightOff(){
  Serial.print(254, BYTE); 
  Serial.print(70, BYTE);   
}


// turn off auto scroll
void autoscrolloff(){
  Serial.print(254, BYTE); 
  Serial.print(82, BYTE);   
}


// turn off auto line wrap
void autolinewrapoff(){
  Serial.print(254, BYTE); 
  Serial.print(68, BYTE);   
}


// turn on auto line wrap
void autolinewrapon(){
  Serial.print(254, BYTE); 
  Serial.print(66, BYTE);   
}


// turn off block cursor
void blockcursoroff(){
  Serial.print(254, BYTE); 
  Serial.print(84, BYTE);   
}


// turn off underline cursor
void underlinecursoroff(){
  Serial.print(254, BYTE); 
  Serial.print(75, BYTE);   
}

