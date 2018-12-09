import meter.*;
import controlP5.*;
import processing.serial.*;

Serial myPort;
ControlP5 cp5;
Meter m1;
Meter m2;
Meter m3;
PFont font;

float optTemp = 20;
float optPH = 5;
int optRPM = 1000;

String val;
float num;
String sendStr;
int sendMode = 0; //0 = temp, 1=ph, 2=stirring
boolean firstContact = false;

float nowTemp;
float nowPH;
float nowRPM;

int meterTemp;
int meterPH;
int meterRPM;

void setup() {
  size(1440,960);
  frameRate(50);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[3], 9600);
  myPort.bufferUntil('\n');
  setMeters();
  setButtons();
}

void draw() {
  background(0);
  //map data to meter
  meterTemp = int(map(nowTemp, 25, 35, 0, 255));
  meterPH = int(map(nowPH, 3, 7, 0, 255));
  meterRPM = int(map(nowRPM, 500, 1500, 0, 255));
  
  //update meter
  m1.updateMeter(meterTemp);
  m2.updateMeter(meterPH);
  m3.updateMeter(meterRPM);
  
  //display optimum numbers
  fill(255);
  textSize(48);
  text(optTemp, width/2, 150);
  text(optPH, width/2, 450);
  text(optRPM, width/2, 725);
  
  //determine values to send
  if (sendMode == 0){
    sendStr = "A" + str(optTemp);
  }
  else if (sendMode == 1){
    sendStr = "B" + str(optPH);
  }
  else if (sendMode == 2){
    sendStr = "C" + str(optRPM);
  }
}

void serialEvent( Serial myPort) {
val = myPort.readStringUntil('\n');
if (val != null) {
  val = trim(val);
  num = float(val);
  if (firstContact == false) {
    if (val.equals("G")) {
      myPort.clear();
      firstContact = true;
      myPort.write("G");
      println("contact");
    }
  }
  else { 
    if (num <= 13){
      nowPH = num;
    }
    else if (num >13 && num <= 50){
      nowTemp = num;
    }
    else {
      nowRPM = num;
    }
    myPort.write(sendStr);
    }
  }
}
