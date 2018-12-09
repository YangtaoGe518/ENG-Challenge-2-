void setButtons(){
  noStroke();
  cp5 = new ControlP5(this);
  font = createFont("calibri light", 26);
  
  cp5.addButton("tM")
     .setValue(0)
     .setPosition(1100,100)
     .setSize(75,75)
     .setFont(font)
     ;
     
  cp5.addButton("tP")
     .setValue(0)
     .setPosition(1200,100)
     .setSize(75,75)
     .setFont(font)
     ;

  cp5.addButton("pHM")
     .setValue(0)
     .setPosition(1100,400)
     .setSize(75,75)
     .setFont(font)
     ;
     
  cp5.addButton("pHP")
     .setValue(0)
     .setPosition(1200,400)
     .setSize(75,75)
     .setFont(font)
     ;
   
  cp5.addButton("rpmM")
     .setValue(0)
     .setPosition(1100,675)
     .setSize(75,75)
     .setFont(font)
     ;
     
  cp5.addButton("rpmP")
     .setValue(0)
     .setPosition(1200,675)
     .setSize(75,75)
     .setFont(font)
     ;
}

public void tM(){
  optTemp -= 0.5;
  sendMode = 0;
}

public void tP(){
  optTemp += 0.5;
  sendMode = 0;
}

public void pHM(){
  optPH -= 0.1;
  sendMode = 1;
}

public void pHP(){
  optPH += 0.1;
  sendMode = 1;
}

public void rpmM(){
  optRPM -= 50;
  sendMode = 2;
}

public void rpmP(){
  optRPM += 50;
  sendMode = 2;
}
