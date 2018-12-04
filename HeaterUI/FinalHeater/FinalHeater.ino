int Heater = 5;
float TherVal;
float X;
float T;
int HeaterVal;
float input;
int Temp;
char val;



void setup() {
  pinMode(Heater, OUTPUT);
  Serial.begin(9600);
  establishContact();
}

void loop() {
  TherVal = analogRead(A0);
  X = (1023/(1023-TherVal))-1;
  T = 1/(1/298.15 + log(X)/4220) - 273.15;
  if (Serial.available() > 0) { 
    val = Serial.read(); 
    if(val != 0){
       inputTemp(float(val));
    }
  } 
    else {
    Serial.println(T + 2000);
  }
  if ( T <= Temp ){
     HeaterVal = 145;
  }
  else{
     HeaterVal = 0;
  }
  analogWrite(Heater, HeaterVal);
  delay(1000);
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}

void inputTemp(int x){
  if ( x>=20 && x <= 30){
    Temp = x;
  }
}
