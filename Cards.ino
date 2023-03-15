#include <Stepper.h>

const int stepsPerRevolution = 200;
int ena=5, in1=6, in2=7; //dc motor declarations
bool dealingDone=false;

int NrJucatori=0, NrCarti=0;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); //stepper motor declarations
int enaStepper1=12, enaStepper2=13;

void setup() {
  myStepper.setSpeed(50);
  pinMode(enaStepper1, OUTPUT);
  pinMode(enaStepper2, OUTPUT);
  
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void dealCard()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(ena, 180);
    delay(200);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(ena, 2000);
    delay(400);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(ena, 0);
}


void loop() {

  while (Serial.available() > 0)
  {   
      if(NrJucatori==0)
      {
      NrJucatori=Serial.parseInt();
      Serial.print("nr jucatori: ");
      Serial.println(NrJucatori);
      }
      
      Serial.flush();

      if(NrCarti==0)
      {
      NrCarti=Serial.parseInt();
      Serial.print("nr carti: ");
      Serial.println(NrCarti);
      dealingDone=false;
      }
   }

  if(NrJucatori>=2 && NrJucatori<=6 && NrCarti!=0 && dealingDone==false)
  {
    for(int i=0;i<NrJucatori;i++)
    {
      int nrRotatii=0;
      for(int j=0;j<NrCarti;j++)
      {
        dealCard();
        
        if(nrRotatii<NrJucatori-1)
        {
          digitalWrite(enaStepper1, HIGH);
          digitalWrite(enaStepper2, HIGH);
          
          int playerToPlayer=stepsPerRevolution/NrJucatori;
          myStepper.step(playerToPlayer);
          delay(300);
          
          digitalWrite(enaStepper1, LOW);
          digitalWrite(enaStepper2, LOW);
  
          delay(700);
          nrRotatii++;
        }
        else
        {
          digitalWrite(enaStepper1, HIGH);
          digitalWrite(enaStepper2, HIGH);
          
          myStepper.step(-(NrJucatori-1)*stepsPerRevolution/NrJucatori);
          delay(500);
          
          digitalWrite(enaStepper1, LOW);
          digitalWrite(enaStepper2, LOW);
          delay(700);
        }
      }
      dealingDone=true;
    }
  }
}
