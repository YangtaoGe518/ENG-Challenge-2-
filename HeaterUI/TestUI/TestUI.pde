import processing.serial.*;
Serial myPort;
float inNum;
float NowTemp;
float SetTemp = 30;
String val;
boolean firstContact = false;

void setup(){
  size (400, 300);
  frameRate(60);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw(){
  background(0);
  textSize(46);
  fill(255);
  text(NowTemp,50,50);
  fill(255,0,0);
  rect(50,130,50,50);
  fill(0,255,0);
  rect(150,130,50,50);
  cursor(ARROW);
  if(mouseX >= 50 && mouseX <= 100 && mouseY >= 130 && mouseY <= 180){
    cursor(HAND);
  }
  if(mouseX >= 150 && mouseX <= 200 && mouseY >= 130 && mouseY <= 180){
    cursor(HAND);
  }
  fill(255);
  text(SetTemp,50,100);
}

void serialEvent( Serial myPort) {
val = myPort.readStringUntil('\n');
if (val != null) {
  val = trim(val);
  println(val);
  if (firstContact == false) {
    if (val.equals("A")) {
      myPort.clear();
      firstContact = true;
      myPort.write("A");
      println("contact");
    }
  }
  else { 
    if (float(val) >= 2000){
      NowTemp = float(val) - 2000;
    }
    myPort.write(byte(SetTemp));
    }
  }
}

public void mousePressed(){
  if(mouseX >= 50 && mouseX <= 100 && mouseY >= 130 && mouseY <= 180){
    SetTemp -= 0.5;
  }
  if(mouseX >= 150 && mouseX <= 200 && mouseY >= 130 && mouseY <= 180){
    SetTemp += 0.5;
  }
}
