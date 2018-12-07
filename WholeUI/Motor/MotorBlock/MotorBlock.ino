#define motorPin 5
#define rpmPin A0

int sensorMax = 0;
int realRpm;
int optRpm;

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(13, OUTPUT);

  sensorMax = getSensorMax(); // get the maximum sensorVal

  analogWrite(motorPin, 0);
  digitalWrite(13, LOW);

  Serial.begin(9600);
}

void loop()
{
  /* print realRpm and send to processing */
  realRpm = getRpm(sensorMax);
  Serial.println(realRpm);
  /* get optRpm from processing and applied to the hardware  */
  optRpm = Serial.parseInt(); // get the optRpm from processing and convert to Int
  inputOptRpm(optRpm);
}



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
  unsigned long start_time = millis();
  unsigned long end_time = start_time;
  int rps = 0;
  int rpm = 0;
  int count = 0;
  int sensor = analogRead(rpmPin);
  int newstate = 0 ;  // newstate is either 0 or 1

  int halfpoint = sensorMax / 2 ;  // get the halfpoint

  while (end_time - start_time < 2000)
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
  rpm = rps * 30 ;
  return rpm;
}
