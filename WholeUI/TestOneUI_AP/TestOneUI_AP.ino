#include <math.h>
/* Pins definition*/
/* Heater */
#define heaterPin 5
#define tempReadPin A0
/* Motor */
#define motorPin 4
#define rpmPin A1
/* PH */
#define phPin A2
#define pumpOnePin 3  //pumpOne is acid
#define pumpTwoPin 6  //pumpTwo is alkali

/* global variables */
int Mode = 3; //Mode 0 -> Heating, 1 -> pH, 2 -> Stiring
char inString;
float inByte;
bool modeSetted = false;

/*Real hardware reading*/
float READTEMP;
int READRPM;
float READPH;

/* circuit variables */
// heater
float TherVal;
int Temp = 20;
float optTemp = 20;   // here i change the original 'Temp' to 'TempOpt'
// motor
int sensorMax = 0;
int optRpm;
// pH
float voltRead;
double volt;
double pH;  // real pH
float optPh = 5; // optimal pH

void setup() {
  Serial.begin (9600);
  //establishContact();
  /* set heater pin mode */
  pinMode(heaterPin, OUTPUT);
  pinMode(tempReadPin, INPUT);
  /* set motor pin mode*/
  pinMode(motorPin, OUTPUT);
  pinMode(rpmPin, INPUT);
  /* set heater pin mode */
  pinMode(phPin, INPUT);
  pinMode(pumpOnePin, OUTPUT);
  pinMode(pumpTwoPin, OUTPUT);

  // initialization for motor sensorMaximum
  sensorMax = getSensorMax();
  analogWrite(motorPin, 0);
}

void loop() {
  Mode = 3;  //reset Mode
  setMode();
  valueInput();
  /* heater */
  TherVal = analogRead(A0);
  READTEMP = HeaterControl(TherVal);
  /* motor */
  READRPM = getRpm(sensorMax);
  inputOptRpm(optRpm);
  /* pH */
  voltRead = analogRead(A2);
  READPH = pumpControl(voltRead);
  /* Arduino -> Processing */
  Serial.print(READTEMP, DEC);
  Serial.print(',');
  Serial.print(READRPM, DEC);
  Serial.print(',');
  Serial.println(READPH, DEC);
  delay(1000);
}

/* communication functions */
void establishContact()
{
  while (Serial.available() <= 0)
  {
    Serial.println("G");
    delay(300);
  }
}

void setMode() {
  if (Serial.available() > 0) {
    inString = Serial.read();
    if ( inString == 'A' ) {
      Mode = 0;
    }
    if ( inString == 'B' ) {
      Mode = 1;
    }
    if ( inString == 'C' ) {
      Mode = 2;
    }
  }
}

void valueInput() {
  if (Serial.available() > 0) {
    inByte = Serial.parseFloat();
    if (Mode == 0) {
      optTemp = inByte;
    }
    if (Mode == 1) {
      optRpm = inByte;
    }
    if (Mode == 2) {
      optPh = inByte;
    }
  }
}

/* Heater functions */
float HeaterControl(float TherVal) {
  float X;
  float T;
  int HeaterVal;
  // calculate temp
  X = (1023 / (1023 - TherVal)) - 1;
  T = 1 / (1 / 298.15 + log(X) / 4220) - 273.15;
  // control the heater
  if ( T <= Temp - 4 ) {
    HeaterVal = 180;
  }
  else if (T <= Temp - 3) {
    HeaterVal = 145;
  }
  else if (T <= Temp - 2) {
    HeaterVal = 110;
  }
  else if (T <= Temp - 1) {
    HeaterVal = 75;
  }
  else if (T <= Temp) {
    HeaterVal = 40;
  }
  else {
    HeaterVal = 0;
  }
  analogWrite(heaterPin, HeaterVal);

  return T;
}


/* motor functions */
int getSensorMax()
{
  int _sensorValue = 0;         // the sensor value
  int _sensorMin = 1023;        // minimum sensor value
  int _sensorMax = 0;           // maximum sensor value
  digitalWrite(13, HIGH);
  analogWrite(motorPin, 255);
  while (millis() < 5000)
  {
    _sensorValue = analogRead(rpmPin);
    if (_sensorValue > _sensorMax)
    {
      _sensorMax = _sensorValue;
    }
    if (_sensorValue < _sensorMin)
    {
      _sensorMin = _sensorValue;
    }
  }
  return _sensorMax;
}

void inputOptRpm(int optRpm)
{
  /* the function is for writing in speed */
  if (Serial.available())
  {
    if (optRpm >= 0 && optRpm <= 255)
    {
      analogWrite(motorPin, optRpm);
    }
  }
}

double getRpm(int sensorMax)
{
  double start_time = millis();
  double end_time = start_time;
  int rps = 0;
  int rpm = 0;
  int count = 0;
  int sensor = analogRead(rpmPin);
  int newstate = 0 ;  // newstate is either 0 or 1

  int halfpoint = sensorMax / 2 ;  // get the halfpoint

  while (end_time - start_time < 1000)
  {
    if (sensor < halfpoint && newstate != 1)
    {
      count++ ;
      newstate = 1;
    }
    else if (sensor > halfpoint)
    {
      newstate = 0 ;
    }
    sensor = analogRead(rpmPin);
    end_time = millis();
  }

  rps = count;
  rpm = rps * 60 ;
  return rpm;
}

/* pH functions */
float pumpControl(float voltRead) {
  // calculate ph
  volt = (voltRead * 0.001 - 0.5) / 5 - 0.177;
  pH =  7 + (volt * 9.6485309 * pow(10, 4)) / (8.314510 * (TherVal + 273.15) * 2.30258509299) - 0.29;
  // control the pumps
  if (pH > 5)
  {
    digitalWrite(pumpOnePin, HIGH);
    digitalWrite(pumpTwoPin, LOW);
  }
  if ( pH == 5)
  {
    digitalWrite(pumpOnePin, LOW);
    digitalWrite(pumpTwoPin, LOW);
  }
  if ( pH < 5)
  {
    digitalWrite(pumpOnePin, LOW);
    digitalWrite(pumpTwoPin, HIGH);
  }

  return pH;
}
