int BUTON1 = 6;                 //platform üzerindeki pinlere, kodda 
int BUTON2 = 8;                 //kullanılan değişkenlerin atanması
int BUTON3 = 13;
int UP1 = 6;
int UP2 = 9;
int DOWN2 = 10;
int DOWN3 = 13;
int SENSOR1 = 7;
int SENSOR2 = 1;
int SENSOR3 = 2;
int MOT1 = 4;
int MOT2 = 5;
int MOTHIZ = 3;
int STBY = 12;

void setup(){                    //Bu fonksiyon platforma reset atıldığında 
  pinMode(BUTON1,INPUT);        //başlangıçta sadece 1 kere çalışıyor
  pinMode(BUTON2,INPUT);        //Burada kullanacağımız değişkenlerden 
  pinMode(BUTON3,INPUT);        //giriş ya da çıkış olarak kullanacaklarımızı tanımlıyoruz
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

  if(digitalRead(SENSOR1) == LOW){                  //asansör 1.katta değil ise 1.kata gelmesi için yazılan fonksiyon
    while(digitalRead(SENSOR1) != HIGH){
      digitalWrite(STBY,HIGH);
      digitalWrite(MOT1,HIGH);
      digitalWrite(MOT2,LOW);
      digitalWrite(MOTHIZ,255);
    }
    digitalWrite(MOT1,LOW);
  }

}
void loop(){                    //Bu fonksiyon asansör açık olduğu sürece sürekli çalışacak 
  int konum;
  int kat1 = digitalRead(SENSOR1);  //Asansörün bulunduğu katın tespit edilip konum değişkenine
  int kat2 = digitalRead(SENSOR2);  //atılması
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

  switch(konum){                  //Asansörün bulunduğu konuma göre maruz kalabileceği fonksiyonlar
    case 1:                       //Asansörün 1.katta bulunduğu takdirde maruz kalabileceği fonksiyonlar
      if(digitalRead(BUTON2) == HIGH || digitalRead(UP2) == HIGH || digitalRead(DOWN2) == HIGH){
        while(digitalRead(SENSOR2) != HIGH){                       //2.kattan çağırılma durumu
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
        }
        digitalWrite(MOT2,LOW);
      }
      if(digitalRead(BUTON3) == HIGH || digitalRead(DOWN3) == HIGH){
        while(digitalRead(SENSOR3) != HIGH){                      //3.kattan çağırılma durumu
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
          if(digitalRead(SENSOR2) == HIGH){
  if(digitalRead(UP2) == HIGH){
    digitalWrite(MOT2,LOW);
    delay(3000);
    digitalWrite(MOT2,HIGH);
  }
}
        }
        digitalWrite(MOT2,LOW);
      }
      digitalWrite(SENSOR1,LOW);
     break;
  
     case 2:                      //Asansörün 2.katta bulunduğu takdirde maruz kalabileceği fonksiyonlar
      if(digitalRead(BUTON3) == HIGH || digitalRead(DOWN3) == HIGH){
        while(digitalRead(SENSOR3) != HIGH){                       //3.kattan çağırılma durumu
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,LOW);
          digitalWrite(MOT2,HIGH);
          digitalWrite(MOTHIZ,255);
        }
        digitalWrite(MOT2,LOW);
      }
      if(digitalRead(BUTON1) == HIGH || digitalRead(UP1) == HIGH){
        while(digitalRead(SENSOR1) != HIGH){                      //1.kattan çağırılma durumu
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
        }  
        digitalWrite(MOT1,LOW);
      }
      digitalWrite(SENSOR2,LOW);
     break;
    
      case 3:                  //Asansörün 3.katta bulunduğu takdirde maruz kalabileceği fonksiyonlar
        if(digitalRead(BUTON2) == HIGH || digitalRead(UP2) == HIGH || digitalRead(DOWN2) == HIGH){
          while(digitalRead(SENSOR2) != HIGH){                  //2.kattan çağırılma durumu
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
        } 
        digitalWrite(MOT1,LOW);
       }
       if(digitalRead(BUTON1) == HIGH || digitalRead(UP1) == HIGH){
        while(digitalRead(SENSOR1) != HIGH){                    //1.kattan çağırılma durumu
          digitalWrite(STBY,HIGH);
          digitalWrite(MOT1,HIGH);
          digitalWrite(MOT2,LOW);
          digitalWrite(MOTHIZ,255);
          while(digitalRead(SENSOR2) == HIGH){
            if(digitalRead(DOWN2) == HIGH){ 
            digitalWrite(MOT1,LOW);    //2.katta düğmeye basılma ihtimali
            delay(3000);
            digitalWrite(MOT1,HIGH);
            }
          }
        }
        digitalWrite(MOT1,LOW);
      }
      break;
      digitalWrite(SENSOR3,LOW);
  }
}
