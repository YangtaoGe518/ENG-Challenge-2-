#include <stdio.h>
#include <math.h>

//const int tempPin = _;
const int voltPin =A0;
const int pumpOnePin = 3;  //pumpOne is acid
const int pumpTwoPin = 6;  //pumpTwo is alkali
//const int standard = 7;
//double temp;
double volt;
double pH;
float optimum = 5;
char val;

void setup()
{
  //pinMode(tempPin, INPUT);
  pinMode(voltPin, INPUT);  //500 offset
  pinMode(pumpOnePin, OUTPUT);
  pinMode(pumpTwoPin, OUTPUT);
  Serial.begin(9600);
  establishContact();
}

void loop()
{
  //temp = analogRead(tempPin);
  volt = (analogRead(voltPin)*0.001 - 0.5)/5;
  pH =  7 + (volt * 9.6485309* pow(10,4))/(8.314510 * 295.13 * 2.30258509299);

  if (pH > 5)
  {
    digitalWrite(pumpOnePin, HIGH);
    digitalWrite(pumpTwoPin, LOW);
  }
  if( pH == 5)
  {
    digitalWrite(pumpOnePin, LOW);
    digitalWrite(pumpTwoPin, LOW);
  }
  if( pH < 5)
  {
    digitalWrite(pumpOnePin, LOW);
    digitalWrite(pumpTwoPin, HIGH);
  }
  
  if (Serial.available())
  {
    val = Serial.read();
    if (val == 'a')
    {
      optimum = optimum + 1.0;
    }
    if (val == 's')
    {
      optimum = optimum - 1.0;
    }
    if (val == 'd')
    {
      optimum = optimum + 0.1;
    }
    if (val == 'f')
    {
      optimum = optimum - 0.1;
    }
    delay(100);
  }
  else
  {
    Serial.println(pH);
    delay(50);
  }
}

void establishContact()
{
  while (Serial.available() <= 0)
  {
    Serial.println("A");
    delay(300);
  }
}

void inputpH(int x)
{
  if (x >= 0 && x <= 13)
  pH = x;
}

//-V is ground, +V is 5V
