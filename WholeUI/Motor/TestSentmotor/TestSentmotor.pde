import processing.serial.*;
Serial myPort;
String val;
boolean firstContact = false;
int motor = 1500;
String sendStr;

void setup(){
  size (400, 300);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[4], 9600);
  myPort.bufferUntil('\n');
}

void draw (){
  if (motor <= 0){
    motor = 0;
  }
  motor += 100;
  sendStr = "B" + str(motor);
  delay(1000);
}

void serialEvent(Serial myPort) {
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
