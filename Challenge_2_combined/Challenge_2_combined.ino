#define RPMSensor 2
#define MOTOR 5
volatile byte half_revolution;
unsigned int rpm;
unsigned long timeold;
String readString;
int previousSetting = 0;


void setup() {
  Serial.begin(9600);
  attachInterrupt(0, rpmCount, FALLING);
  pinMode(MOTOR, OUTPUT);
  // Whenever the sensor detects a light decrease,
  // attachInterrupt() is called.

  half_revolution = 0;
  rpm = 0;
  timeold = 0;
  //Basic setup. Set all the variables to 0.
}

void loop() {
  // put your main code here, to run repeatedly:
  //rpmCalc();
  Serial.println(digitalRead(RPMSensor));
    while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }
  if (readString.length() > 0) {
    //Serial.println(readString);  //so you can see the captured string 
    int n = readString.toInt();  //convert readString into a number
   // analogWrite(ledPin, n);
   if (n <= 255 && n != previousSetting){
    if ( n > previousSetting) {
    for (int changeValue = previousSetting; changeValue <= n; changeValue += 5){
      analogWrite(MOTOR, changeValue);
        //rpmCalc();
      delay(30);
      }
    } else if (n < previousSetting) {
      for (int changeValue = previousSetting; changeValue >= n; changeValue -= 5){
      analogWrite(MOTOR, changeValue);
        //rpmCalc();
      delay(30);
      }
   }
      previousSetting = n;
   }
   }
    readString="";
}

void rpmCount(){
  half_revolution++;
  //This is ran twice per revolution.
  //When half_revolution == 2, we want to check
  //the RPM.
  }

void rpmCalc() {
    if (half_revolution == 2){
    // Check the RPM
    rpm = 60000/(millis() - timeold)*half_revolution;
    timeold = millis();
    // Set timeold as current time so to have a timestamp of last check.
    half_revolution = 0;
    Serial.println(rpm, DEC);
    }
  }
