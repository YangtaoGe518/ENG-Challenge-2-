#include <stdio.h>
#include <math.h>

//int tempPin =25;
const int voltPin =A0;
const int pumpOnePin = 3;  //pumpOne is acid
const int pumpTwoPin = 6;  //pumpTwo is alkali
const int standard = 7;
//int optimum = 5;
double temp;
double volt;
double pH;
//int pumpOnestate = 0;
//int pumpTwostate = 0;

//manual scanf() vs Serial.read(): setpoint adjustment

void setup()
{
  //pinMode(tempPin, INPUT);
  pinMode(voltPin, INPUT);
  pinMode(pumpOnePin, OUTPUT);
  pinMode(pumpTwoPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //temp = analogRead(tempPin);
  volt = analogRead(voltPin)*0.001;
  pH =  (volt * 9.6485309* pow(10,4))/(8.314510 * 300 * 2.30258509299);
  //Serial.println(pH);
  //digitalWrite(pumpOnePin, LOW);
  //digitalWrite(pumpTwoPin, LOW);
  if (pH > 5.5)
  {
    digitalWrite(pumpOnePin, HIGH);
    digitalWrite(pumpTwoPin, LOW);
  }
  if( 4.5 <= pH <= 5.5)
  {
    digitalWrite(pumpOnePin, LOW);
    digitalWrite(pumpTwoPin, LOW);
  }
  if( pH < 4.5)
  {
    digitalWrite(pumpOnePin, LOW);
    digitalWrite(pumpTwoPin, HIGH);
  }
  /* pumpOnestate = digitalRead(pumpOnePin);
  pumpTwostate = digitalRead(pumpTwoPin);
  if (pumpOnestate == HIGH)
  {
    Serial.println("1");
  }
  if (pumpTwostate == HIGH)
  {
    Serial.println("2");
  }*/
}
