  int konum;
  int kat1 = digitalRead(SENSOR1);
  int kat2 = digitalRead(SENSOR2);
  int kat3 = digitalRead(SENSOR3);
  if(kat1 == HIGH){
    konum = 1;
  }
  if(kat2 == HIGH){
    konum = 2;
  }
  if(kat3 == HIGH){
    konum = 3;
  }

  switch(konum){
    case 1:
      if(digitalRead(BUTON2) == HIGH || digitalRead(2UP) == HIGH || digitalRead(2DOWN) == HIGH){
        do{
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
        }while(digitalRead(SENSOR2 != HIGH);
      }
      if(digitalRead(BUTON3) == HIGH || digitalRead(3DOWN) == HIGH){
        do{
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
          if(digitalRead(2UP) == HIGH || digitalRead(BUTON2) == HIGH){
            digitalWrite(STBY,LOW);
            delay(3000);
            digitalWrite(STBY,HIGH);
          }
        }while(digitalRead(SENSOR3 != HIGH);
      }
     break;
  
     case 2:
      if(digitalRead(BUTON3) == HIGH || digitalRead(3DOWN) == HIGH){
        do{
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
        }while(digitalRead(SENSOR3 != HIGH);
      }
      if(digitalRead(BUTON1) == HIGH || digitalRead(1UP) == HIGH){
        do{
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
        }while(digitalRead(SENSOR1 != HIGH);  
      }
     break;
    
      case 3:
        if(digitalRead(BUTON2) == HIGH || digitalRead(2UP) == HIGH || digitalRead(2DOWN) == HIGH){
          do{
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
        }while(digitalRead(SENSOR2 != HIGH); 
       }
       if(digitalRead(BUTON1) == HIGH || digitalRead(1UP) == HIGH){
        do{
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
          if(digitalRead(2DOWN) == HIGH || digitalRead(BUTON2) == HIGH){
            digitalWrite(STBY,LOW);
            delay(3000);
            digitalWrite(STBY,HIGH);
          }
        }while(digitalRead(SENSOR1 != HIGH);
      }
      break;
  }
