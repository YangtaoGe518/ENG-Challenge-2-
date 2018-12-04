# define motorPin 5
# define rpmPin A0

/* global variables */
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
int rps = 0;
int rpm = 0;

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(13, HIGH);  // the LED on the Arduino Board
  analogWrite(motorPin, 255);

  // obtain the sensitive value * We have to decrease the voltage !!!
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

  analogWrite(motorPin, 0);  // After caculating the SensorVal = set motor to zero;
  digitalWrite(13, LOW);
  Serial.begin(9600);

  // when serial is empty, requires input (only used in Ardunio Serial Port)
  //while (! Serial);
  //Serial.println("Speed 0 to 255");
}

void loop()
{
  int speed;
  rpm = getRpm();
  Serial.println(rpm);
  /* input speed by Arduino Serial Port */
  //speed = Serial.parseInt();
  //inputSpeed(speed);

  /* input speed by Processing code */
  speed = getOptSpeed();
  inputSpeed(speed);

  delay (5); // delay in between read for stability
}

void inputSpeed(int speed)
/* the function is for writing in speed by Arduino Serial Port */
{
  if (Serial.available())
  {
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }
  }
}

int getOptSpeed ()
/* the function is for writing in speed by Processing optimal speed */
{
  char val;
  int optSpeed = 0;
  if (Serial.available())
  {
    val = Serial.read();
    if (val == 'a') // add
    {
      optSpeed += 10;
    }
    if (val == 's') // substract
    {
      optSpeed -= 10;
    }
    if (val == 'i') // auto mode
    {
      /* here using fade funtion (not finished yet) */
      optSpeed = 63; // probrely 1500rpm ?
    }
  }
  return optSpeed;
}

double getRpm() {
  /* the function is for getting the real Revolution per minutes */
  unsigned long start_time = millis();
  unsigned long end_time = start_time;
  int count = 0;
  int sensor = analogRead(rpmPin);
  int halfpoint = sensorMax / 2 ;
  int newstate = 0 ;

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

  rps = count ;
  rpm = rps * 30 ;
  return rpm;
}
