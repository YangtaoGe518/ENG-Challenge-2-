import processing.serial.*;
Serial myPort; 
float val = 5.0;
String pH;
boolean firstContact = false;

void setup() 
{
  size(500,200); 
  myPort = new Serial(this,Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void keyPressed()
{
  if(key == 'q' || key == 'Q'){
    val += 1.0;
    myPort.write('q');
  }
  if(key == 'w' || key == 'W'){
    val -= 1.0;
    myPort.write('w');
  }
  if(key == 'e' || key == 'E'){
    val += 0.1;
    myPort.write('e');
  }
  if(key == 'r' || key == 'R'){
    val -= 0.1;
    myPort.write('r');
  }
}

void draw()
{
  background(0);
  textSize(32);
  String temp1= "pH Optimum=";
  String temp2= "pH actual=";
  String count = nf(val,0,1);
  temp1 += count;
  textAlign(CENTER,TOP);
  text(temp1, width/2,120);
  text(temp2, width/2,30);
}

void serialEvent(Serial myPort)
{
  pH = myPort.readStringUntil('\n');
  if (pH != null)
  {
    pH = trim(pH);
    println(pH);
    if (firstContact == false)
    {
      if(pH.equals("A"))
      {
        myPort.clear();
        firstContact = true;
        myPort.write("A");
        println("contact");
      }
    }
  }
}
