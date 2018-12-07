int Mode = 3; //Mode 0 -> Heating, 1 -> pH, 2 -> Stiring
float Temp = 20;
float pH = 7;
float Stir = 1500;
char inString;
float inByte;
bool modeSetted = false;


void setup() {
  Serial.begin (9600);

}

void loop() {
  setMode();
  valueInput();
  Serial.println(Temp);
  Serial.println(pH);
  Serial.println(Stir);
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
