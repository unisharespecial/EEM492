int BUTON1 = 6;                  
int BUTON2 = 8;                 
int BUTON3 = 13;
int UP1 = A0;
int UP2 = 9;
int DOWN2 = 10;
int DOWN3 = A1;
int SENSOR1 = 7;
int SENSOR2 = 11;
int SENSOR3 = 2;
int MOT1 = 4;
int MOT2 = 5;
int MOTHIZ = 3;
int STBY = 12;

void setup(){                    
  pinMode(BUTON1,INPUT);        
  pinMode(BUTON2,INPUT);        
  pinMode(BUTON3,INPUT);        
  pinMode(UP1,INPUT);
  pinMode(UP2,INPUT);
  pinMode(DOWN2,INPUT);
  pinMode(DOWN3,INPUT);
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(SENSOR3,INPUT);
  pinMode(MOT1,OUTPUT);
  pinMode(MOT2,OUTPUT);
  pinMode(MOTHIZ,OUTPUT);
  pinMode(STBY,OUTPUT);
  
  if(digitalRead(SENSOR1) == LOW){                  
    while(digitalRead(SENSOR1) != HIGH){
      digitalWrite(STBY,HIGH);
      digitalWrite(MOT1,HIGH);
      digitalWrite(MOT2,LOW);
      digitalWrite(MOTHIZ,255);
    }
    digitalWrite(MOT1,LOW);
  }
}

int hesap(){
  int konum;
  int kat1 ;
  int kat2 ;
  int kat3 ;
  kat1 = digitalRead(SENSOR1);
  kat2 = digitalRead(SENSOR2);
  kat3 = digitalRead(SENSOR3);
  if(kat1 == HIGH){
    konum = 1;
  }
  if(kat2 == HIGH){
    konum = 2;
  }
  if(kat3 == HIGH){
    konum = 3;
  }
  return konum;
}

void loop(){
int m;
 m = hesap();
  switch(m){
    case 1 :
    
      if(digitalRead(BUTON2) == HIGH || digitalRead(DOWN2) == HIGH || digitalRead(UP2) == HIGH){
        while(digitalRead(SENSOR2) != HIGH){
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
        }
        digitalWrite(MOT2,LOW);
      }
    
      if(digitalRead(BUTON3) == HIGH || digitalRead(DOWN3) == HIGH){
        while(digitalRead(SENSOR3) != HIGH){
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);          
          if(digitalRead(UP2) == HIGH && digitalRead(SENSOR2) != HIGH){
            while(digitalRead(SENSOR2) != HIGH){
            digitalWrite(STBY,HIGH);
            digitalWrite(MOT1,LOW);
            digitalWrite(MOT2,HIGH);
            digitalWrite(MOTHIZ,255);
            }
          digitalWrite(MOT2,LOW);
          delay(3000);
          digitalWrite(MOT2,HIGH);
          }                                          
        }
        digitalWrite(MOT2,LOW);
      }
    
    break;
    
    case 2 :
    
      if(digitalRead(BUTON3) == HIGH || digitalRead(DOWN3) == HIGH){
        while(digitalRead(SENSOR3) != HIGH){
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
        }
        digitalWrite(MOT2,LOW);
      }
      
      if(digitalRead(BUTON1) == HIGH || digitalRead(UP1) == HIGH){
        while(digitalRead(SENSOR1) != HIGH){
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
        }
        digitalWrite(MOT1,LOW);
      }  

    break;
    
    case 3 :
    
      if(digitalRead(BUTON2) == HIGH || digitalRead(DOWN2) == HIGH || digitalRead(UP2) == HIGH){
        while(digitalRead(SENSOR2) != HIGH){
         digitalWrite(STBY,HIGH);
         digitalWrite(MOT1,HIGH);
         digitalWrite(MOT2,LOW);
         digitalWrite(MOTHIZ,255);
        }
        digitalWrite(MOT1,LOW);
      }
     
     if(digitalRead(BUTON1) == HIGH || digitalRead(UP1) == HIGH){
       while(digitalRead(SENSOR1) != HIGH){
         digitalWrite(STBY,HIGH);
         digitalWrite(MOT1,HIGH);
         digitalWrite(MOT2,LOW);
         digitalWrite(MOTHIZ,255);
         if(digitalRead(DOWN2) == HIGH && digitalRead(SENSOR2) != HIGH){
           while(digitalRead(SENSOR2) != HIGH){
             digitalWrite(STBY,HIGH);
             digitalWrite(MOT1,HIGH);
             digitalWrite(MOT2,LOW);
             digitalWrite(MOTHIZ,255);
           }
           digitalWrite(MOT1,LOW);
           delay(3000);
           digitalWrite(MOT1,HIGH);
         }
       }
       digitalWrite(MOT1,LOW);
     }
 
     break;
  }
}
 
      
    
  

  

