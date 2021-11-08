#include "Stepper.h"
#include "PinOut.h"


// NEMA17 with TMC2208 with 16 microsteps
Stepper X;

long steps;
int interval;

float pos;
float vel;



void setup() {
  Serial.begin(250000);

  X = Stepper(X_DIR, X_STEP, X_ENABLE);
  X.begin(200, 16);

  pinMode(X_STOP_MIN, INPUT_PULLUP);
  pinMode(X_STOP_MAX, INPUT_PULLUP);

//  X.home(X_STOP_MIN);
//  delay(1000);
  Serial.println("Ready!");

  steps = 0;
  interval = 100;

  pos = 0.0;
  vel = 0.0;
}


void loop() {  
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
//    Serial.println(data);

    getValues(data);
  }  

  X.rotate(steps, interval);
  
  if (X.getState()) Serial.write(1);
  else  Serial.write(0);
}


void getValues(String str) {
  int indexOfSeperator = str.indexOf(' ');
  if (indexOfSeperator == -1) return;

  if (str.charAt(0) != 'S') return;
  if (str.charAt(indexOfSeperator+1) != 'I')  return;

  steps = str.substring(1, indexOfSeperator).toInt();
  interval = str.substring(indexOfSeperator+2).toInt();
}
