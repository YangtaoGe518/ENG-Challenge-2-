void setMeters(){
  m1 = new Meter(this, 100, 25); // Instantiate a meter class.
  setMeterOne();
  m2 = new Meter(this, 100, 300);
  setMeterTwo();
  m3 = new Meter(this, 100, 575);
  setMeterThree();
}

void setMeterOne(){
  m1.setFrameColor(color(5,60,252));
  m1.setPivotPointColor(color(255,0,0));
  m1.setMinScaleValue(25.0);
  m1.setMaxScaleValue(35.0);
  String[] scaleLabels = {"25","26","27","28","29","30","31","32","33","34","35"};
  m1.setScaleLabels(scaleLabels);
  m1.setTitle("Temperature");
  m1.setDisplayDigitalMeterValue(true);
  m1.setLowSensorWarningActive(true);
  m1.setLowSensorWarningValue((float)27.0);
  m1.setHighSensorWarningActive(true);
  m1.setHighSensorWarningValue((float)33.0);
}

void setMeterTwo(){
  m2.setFrameColor(color(5,60,252));
  m2.setPivotPointColor(color(255,0,0));
  m2.setMinScaleValue(3.0);
  m2.setMaxScaleValue(7.0);
  String[] scaleLabels = {"3","3.5","4","4.5","5","5.5","6","6.5","7"};
  m2.setScaleLabels(scaleLabels);
  m2.setTitle("pH");
  m2.setDisplayDigitalMeterValue(true);
  m2.setLowSensorWarningActive(true);
  m2.setLowSensorWarningValue((float)3.5);
  m2.setHighSensorWarningActive(true);
  m2.setHighSensorWarningValue((float)6.5);
}

void setMeterThree(){
  m3.setFrameColor(color(5,60,252));
  m3.setPivotPointColor(color(255,0,0));
  m3.setMinScaleValue(500);
  m3.setMaxScaleValue(1500);
  String[] scaleLabels = {"500","600","700","800","900","1000","1100","1200","1300","1400","1500"};
  m3.setScaleLabels(scaleLabels);
  m3.setTitle("Motor RPM");
  m3.setDisplayDigitalMeterValue(false);
  m3.setLowSensorWarningActive(true);
  m3.setLowSensorWarningValue((float)650);
  m3.setHighSensorWarningActive(true);
  m3.setHighSensorWarningValue((float)1350);
}
