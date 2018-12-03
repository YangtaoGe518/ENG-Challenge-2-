import processing.serial.*;

Serial myPort;  // Create object from Serial class

void setup() 
{
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  if (keyPressed)
  {
    if (key == 'b' || key == 'B')
    {
      fill(0);
      myPort.write(10);
      delay (100);
    }
  }
  else
  {
    fill(255);
    myPort.write('M');
  }
  rect(25, 25, 50, 50);
}

boolean mouseOverRect() { // Test if mouse is over square
  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
}
