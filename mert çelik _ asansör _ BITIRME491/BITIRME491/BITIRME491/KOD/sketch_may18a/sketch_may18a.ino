int AIN2 = 0;
int AIN1 = 1;
int PWMA = 3;
int STBY = 4;


void setup(){
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(STBY,OUTPUT);
}
void loop(){
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(PWMA,255);
  delay(1000);
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(PWMA,255);
  delay(1000);
}
