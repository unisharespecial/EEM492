int k;
k = digitalRead(SENSOR1);
if(k == LOW){
  do{
    digitalWrite(STBY,HIGH);
    digitalWrite(MOT1,HIGH);
    digitalWrite(MOT2,LOW);
    digitalWrite(MOTHIZ,255);
  }while(k != HIGH);
