int Mode = 3;
float Temp = 20;
char inString;
float inByte;

void setup() {
  Serial.begin(9600);
  establishContact();
}

void loop() {
  Mode = 3;
  readMode();
  readValue();
  if (Mode == 0){
    Serial.println("Received" + String(Temp));
  }
  delay(1000);
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   
  delay(300);
  }
}

void readMode(){
    if (Serial.available() > 0){
    inString = Serial.read();
      if ( inString == 'A' ){
        Mode = 0;
      }
    }
}

void readValue(){
  if (Serial.available() > 0){
    inByte = Serial.parseFloat();
    if (Mode == 0){
      Temp = inByte;
    }
  }
}
