#include <stdio.h>
#include <math.h>

const int voltPin =A0;
double volt;
double pH;
float optimum = 5;
int Mode = 3;
float inByte;
char val;

void setup()
{
  pinMode(voltPin, INPUT);  //500 offset
  Serial.begin(9600);
  establishContact();
}

void loop()
{
  Mode = 3;
  volt = (analogRead(voltPin)*0.001 - 0.5)/5;
  pH =  7 + (volt * 9.6485309* pow(10,4))/(8.314510 * 295.13 * 2.30258509299);
  Serial.println(pH);
  readMode();
  readValue();
  if (Mode == 2)
  {
    Serial.println("Received" + String(optimum));
    delay(50);
  }
  delay(1000);
}

void establishContact()
{
  while (Serial.available() <= 0)
  {
    Serial.println("A");
    delay(300);
  }
}

void readMode()
{
  if (Serial.available() > 0)
  {
    val = Serial.read();
    if (val == 'C')
    {
      Mode = 2;
    }
  }
}

void readValue()
{
  if (Serial.available () > 0)
  {
    inByte = Serial.parseFloat();
    if (Mode == 2)
    {
      optimum = inByte;
    }
  }
}
//-V is ground, +V is 5V
