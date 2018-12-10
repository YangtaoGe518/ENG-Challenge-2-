import meter.*;
import controlP5.*;
import processing.serial.*;

Serial myPort;
ControlP5 cp5;
Meter m1;
Meter m2;
Meter m3;
PFont font;
int newline = 10 ; // ASCII

float optTemp = 25;
float optPH = 5;
int optRPM = 1000;

String val;
String sendStr;
int sendMode = 3; //0 = temp, 1=stirring, 2=ph
boolean firstContact = false;

float nowTemp = 25;
float nowPH = 5;
float nowRPM = 1000;

int meterTemp;  //chsnge int to float
int meterPH;  //change int to float
int meterRPM;

int numReadings = 3;
float readings[];  //array to read the 3 values

void setup() {
  size(1440, 960);
  frameRate(50);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
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
  text(optRPM, width/2, 450);
  text(optPH, width/2, 725);
  

  //determine values to send
  if (sendMode == 0) {
    sendStr = "A" + str(optTemp);
  } else if (sendMode == 1) {
    sendStr = "B" + str(optRPM);
  } else if (sendMode == 2) {
    sendStr = "C" + str(optPH);
  }
  
  println(sendStr);
}

void serialEvent(Serial myPort) 
{
  val = myPort.readStringUntil(newline);
  if (val != null) 
  {
    val = trim(val);
    if (firstContact == false) 
    {
      if (val.equals("G")) 
      {
        myPort.clear();
        firstContact = true;
        myPort.write("G");
        println("contact");
      }
    } 
    else
    {
      readings = float(split(val, ','));
      nowTemp = int(readings[0]);
      nowRPM = int(readings[1]);
      nowPH = int(readings[2]);
    }
  }

  //println(nowTemp, nowRPM, nowPH);
  myPort.write(sendStr);
}
