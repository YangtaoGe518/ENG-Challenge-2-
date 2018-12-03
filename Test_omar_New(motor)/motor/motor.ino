# define motorPin 5
# define rpmPin A0
// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
int rps = 0 ;

/* global variables */
int last = 0;
int rpm;

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(13, HIGH);
  analogWrite(motorPin, 255);
  // obtain the sensitive value
  while (millis() < 5000) 
  {
    sensorValue = analogRead(rpmPin);
    if (sensorValue > sensorMax) 
    {
      sensorMax = sensorValue;
    }
    if (sensorValue < sensorMin) 
    {
      sensorMin = sensorValue;
    }
  }
  analogWrite(motorPin, 0);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  
  // when serial is empty, requires input
  while (! Serial);
  Serial.println("Speed 0 to 255");
}

void loop()
{
  int speed;
  rpm = getRpm();
  Serial.println(rpm);
  speed = Serial.parseInt();
  inputSpeed(speed);

  delay (5); // delay in between read for stability
}

void inputSpeed(int speed)
/* the function is for writing in speed */
{
  if (Serial.available())
  {
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }
  }
}

void getRpm() {
  unsigned long start_time = millis();
  unsigned long end_time = start_time;
  int count = 0;
  int sensor = analogRead(rpmPin);
  int halfpoint = sensorMax / 2 ;
  int newstate = 0 ;
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
  
  rps = count ;
  rpm = rps * 60 ;
  return rpm
}
