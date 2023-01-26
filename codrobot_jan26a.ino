const int SpateTrigPin = 13;
const int SpateEchoPin = 12;

const int DreaptaSpateTrigPin = 7;
const int DreaptaSpateEchoPin = 8;

const int DreaptaFataTrigPin = 3;
const int DreaptaFataEchoPin = 2;

int DistanceSpate, DistanceDreaptaSpate, DistanceDreaptaFata;


  void setup() 
  {
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(10,OUTPUT);     //en A
    pinMode(11,OUTPUT);     //en B
    
    pinMode(SpateTrigPin, OUTPUT);
    pinMode(SpateEchoPin, INPUT);

    pinMode(DreaptaSpateTrigPin, OUTPUT);
    pinMode(DreaptaSpateEchoPin, INPUT);

    pinMode(DreaptaFataTrigPin, OUTPUT);
    pinMode(DreaptaFataEchoPin, INPUT);

    Serial.begin(9600);
  }
  int masurare_distanta(int TrigPin, int EchoPin)
  {
    int distance;
    long duration;
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(4);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);

    return distance;
  }

  boolean cautare_parcare(int DistanceDreaptSpate, int DistanceDreaptFata)
  {
    if((DistanceDreaptSpate > 30)&&(DistanceDreaptFata > 30))
    {
      return true;
    }
    return false;
  }

  void mers_cu_spatele()
  {
    analogWrite (10,100);
    analogWrite(11,100);
    digitalWrite(5,HIGH); //stanga
    digitalWrite(6,LOW); //stanga
    digitalWrite(9,HIGH);
    digitalWrite(4,LOW);
    
  }

  void oprire()
  {
    analogWrite (10,0);
    analogWrite(11,0);
    digitalWrite(5,LOW); //stanga
    digitalWrite(6,LOW); //stanga
    digitalWrite(9,LOW);
    digitalWrite(4,LOW);
    delay(500);
  }

  void parcare_cu_spatele()
  {
     //stanga merge cu spatele si dreapta sta
  analogWrite (10,100);
  analogWrite(11,255);
  digitalWrite(5,HIGH); //stanga
  digitalWrite(6,LOW); //stanga
  digitalWrite(9,LOW);
  digitalWrite(4,HIGH);
  delay(500);

  DistanceSpate = 30;
  while(DistanceSpate > 10)
  {
    DistanceSpate = masurare_distanta( SpateTrigPin, SpateEchoPin);
    Serial.print("DistanceSPATE: ");
    Serial.println(DistanceSpate);
    mers_cu_spatele();
  }
  analogWrite (10,0);
  analogWrite(11,0);
  digitalWrite(5,LOW); //stanga
  digitalWrite(6,LOW); //stanga
  digitalWrite(9,LOW);
  digitalWrite(4,LOW);
  
  delay(1000);
  }

  void mers_inainte()
  {
     analogWrite (10,100);
     analogWrite(11,100);
     digitalWrite(5,LOW);
     digitalWrite(6,HIGH);
     digitalWrite(9,LOW);
     digitalWrite(4,HIGH);
  
  }
bool iesire_din_parcare_efectuata = false;
  void iesire_parcare(int DistanceDreaptaSpate)
  {
    mers_inainte();
        if(DistanceDreaptaSpate > 30)
    {
           //stanga merge cu fata si dreapta sta
      analogWrite (10,100);
      analogWrite(11,255);
      digitalWrite(5,LOW); //stanga
      digitalWrite(6,HIGH); //stanga
      digitalWrite(9,HIGH);
      digitalWrite(4,LOW);
      delay(500);
      mers_inainte();
      delay(500);
      iesire_din_parcare_efectuata = true;
    } 
  }

  boolean cautare_parcare_laterala(int DistanceDreaptFata)
  {
    if(DistanceDreaptFata > 30)
    {
      return true;
    }
    return false;
  }

  void parcare_laterala()
  {
    oprire();
  }

  bool ajustare_distanta(int DistanceDreaptaFata, int DistanceDreaptaSpate)
  {
    if(DistanceDreaptaFata-DistanceDreaptaSpate > 4)
    {
      analogWrite (10,100);
      analogWrite(11,255);
      digitalWrite(5,LOW); //stanga
      digitalWrite(6,HIGH); //stanga
      digitalWrite(9,HIGH);
      digitalWrite(4,LOW);
      delay(120);
      return false;
    }
    else if(DistanceDreaptaSpate - DistanceDreaptaFata > 4)
    {
      analogWrite (10,100);
      analogWrite(11,255);
      digitalWrite(5,HIGH); //stanga
      digitalWrite(6,LOW); //stanga
      digitalWrite(9,LOW);
      digitalWrite(4,HIGH);
      delay(120);

      return false;
    }
    else if (abs(DistanceDreaptaFata-DistanceDreaptaSpate) < 1)
    {
      return true;
    }
  }
  
  bool parcare_cu_spatele_efectuata = false;
  void loop() 
  {
  
  DistanceDreaptaSpate = 0; 
  DistanceDreaptaFata = 0;
  
    DistanceDreaptaSpate = masurare_distanta(DreaptaSpateTrigPin ,DreaptaSpateEchoPin );
    DistanceDreaptaFata = masurare_distanta(DreaptaFataTrigPin ,DreaptaFataEchoPin );
    
  if(!parcare_cu_spatele_efectuata)
  {
    mers_inainte();
    if(cautare_parcare(DistanceDreaptaSpate, DistanceDreaptaFata) )
    {
       oprire();
       parcare_cu_spatele();
       parcare_cu_spatele_efectuata = true;
    }
  }
  else
  {
    if(!iesire_din_parcare_efectuata)
    {
      iesire_parcare(DistanceDreaptaSpate);
    }   
    else
    {
      mers_inainte();
      delay(200);
      ajustare_distanta(DistanceDreaptaFata, DistanceDreaptaSpate); 

      if(DistanceDreaptaFata > 50)
      {
        oprire();
        delay(50000);
      }
    }
  }  
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
