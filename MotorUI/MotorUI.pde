import controlP5.*; // import controlP5 
import processing.serial.*; // import serial

ControlP5 cp5; // create an instance
Serial myPort;
int newline = 10; // ASCII code for '\n'
PFont font;

int trueSpeed;
int optSpeed = 0;

void setup()
{
  size (300, 400); 
  /* initialize the communication port */
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600); // locate the usb port
  myPort.bufferUntil(newline); //reading until newline
  
  cp5 = new ControlP5(this);
  font = createFont("calibri light", 20);

  /* make an add button */
  cp5.addButton("add")
    .setPosition(100, 50)
    .setSize(100, 80)
    .setFont(font);

  /* make an substract button */
  cp5.addButton("sub")
    .setPosition(100, 150)
    .setSize(100, 80)
    .setFont(font); 

  /* make an Automatic adjustment button */
  cp5.addButton("auto")
    .setPosition(100, 250)
    .setSize(100, 80)
    .setFont(font);
    
}

void draw()
{
  background (150, 0, 150);
  /* make a title */
  fill (0, 255, 0); 
  textFont(font);
  text ("MOTOR CONTROL", 75, 30);
  
  /* reading from Serial Port */
  fill (0, 255, 0);
  textFont(font);
  text (trueSpeed, 130 ,355);
  
  /* optimal Speed */
  fill (0, 100, 200);
  textFont(font);
  text(optSpeed, 130, 380);
}

void serialEvent(Serial myPort)
/* function for reading String from Serial Port*/
{
  String ArString;
  ArString = myPort.readStringUntil(newline);
  if (ArString != null)
  {
    ArString = trim(ArString);
    trueSpeed = int(ArString);
  }
  println(trueSpeed);
}

/* add function to different buttons */
void add()
{
  myPort.write('a');
  optSpeed += 10;
}

void sub()
{
  myPort.write('s');
  optSpeed -= 10;
}

void auto()
{
  myPort.write('i');
}
