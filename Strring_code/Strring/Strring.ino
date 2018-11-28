# define motorPin 13
# define rpmPin A1

# define milisecs 500   // we can change it

/* global variables */
int state = LOW;
int slots = 2;  //we have two slots on the detector
int last = 0;

void setup()
{
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  // provide an input instruction
  while (! Serial);
  Serial.println("Speed 0 to 255");
}

void loop()
{
  int speed;
  int val;
  val = rpmSensor(); // here is the variable to read the rpm
  speed = Serial.parseInt();  // here is the variable to receive speed input
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

int getCount()
{
  /* the function is for getting how many times the shield covers the light*/
  int count;
  int newstate;
  newstate = digitalRead(rpmPin); // return HIGH or LOW (1 or 0)
  if (newstate != state)
  {
    count ++;
    newstate = state;
  }
  return count;
}

double rpmSensor()
{
  /* the function is for getting the value of rpm */
  int count = getCount();
  double rps;
  double rpm;
  if (millis() - last >= milisecs)
  {
    rps = ((double)count/slots) / 2.0 * 1000.0 / milisecs;
    rpm = rps * 60;  //here we get the rpm 
  }
  count = 0;
  last = millis();
  return rpm
}
