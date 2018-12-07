import processing.serial.*;
Serial myPort;
String val;
boolean firstContact = false;
int Temp = 20;
String sendStr;

void setup(){
  size (400, 300);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[4], 9600);
  myPort.bufferUntil('\n');
}

void draw (){
  if (Temp >= 30){
    Temp = 20;
  }
  Temp += 1;
  sendStr = "A" + str(Temp);
  delay(1000);
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
      println(val);
      myPort.write(sendStr);
    }
  }
}
