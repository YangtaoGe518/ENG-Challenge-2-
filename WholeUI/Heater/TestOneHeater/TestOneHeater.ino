int Mode = 3; //Mode 0 -> Heating, 1 -> pH, 2 -> Stiring
float Temp = 20;
float pH = 7;
float Stir = 1500;
char inString;
float inByte;
bool modeSetted = false;
int Heater = 5;
float TherVal;
float X;
float T;
int HeaterVal;



void setup() {
  Serial.begin (9600);

}

void loop() {
  setMode();
  valueInput();
  TherVal = analogRead(A0);
  HeaterControl(TherVal);
  delay(1000);
}

void setMode(){
  if (Serial.available() > 0){
    inString = Serial.read();
    if ( inString == 'A' ){
      Mode = 0;
    }
    if ( inString == 'B' ){
      Mode = 1;
    }
    if ( inString == 'C' ){
      Mode = 2;
    }
  }
}

void valueInput(){
  if (Serial.available() > 0){
    inByte = Serial.parseFloat();
    if (Mode == 0){
      Temp = inByte;
    }
    if (Mode == 1){
      pH = inByte;
    }
    if (Mode == 2){
      Stir = inByte;
    }
  }
}

void HeaterControl(float TherVal){
  X = (1023/(1023-TherVal))-1;
  T = 1/(1/298.15 + log(X)/4220) - 273.15;
  Serial.println( T );
  if ( T <= Temp - 4 ){
    HeaterVal = 180;
  }
  else if (T <= Temp - 3){
    HeaterVal = 145;
  }
  else if (T <= Temp - 2){
    HeaterVal = 110;
  }
  else if (T <= Temp - 1){
    HeaterVal = 75;
  }
  else if (T <= Temp){
    HeaterVal = 40;
  }
  else{
    HeaterVal = 0;
  }
  analogWrite(Heater, HeaterVal);
}
