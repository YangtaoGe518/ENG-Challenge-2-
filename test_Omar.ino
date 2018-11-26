/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 3;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  
  // print out the state of the button:
  rpm_measure();
  delay(20);        // delay in between reads for stability
}


void rpm_measure(){
int rps = 0;
int starttime = millis();
int endtime = starttime;
int prevstate ;
int counter= 0 ;
  while((endtime-starttime)<1000){
    int buttonState=digitalRead(pushButton);
    if(buttonState== HIGH && buttonState!=prevstate){
    rps = rps+1;
    }
    prevstate = buttonState;
    counter++;
   endtime = millis();
  }
//Serial.println(counter,DEC); 
Serial.println(rps*60);  
}
