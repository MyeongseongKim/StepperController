#include "Stepper.h"
#include "PinOut.h"


// NEMA17 with TMC2208 with 16 microsteps
Stepper X;

float angle;



void setup() {
  Serial.begin(250000);

  X = Stepper(X_DIR, X_STEP, X_ENABLE);
  X.begin(200, 16);

  pinMode(X_STOP_MIN, INPUT_PULLUP);
  pinMode(X_STOP_MAX, INPUT_PULLUP);

//  X.home(X_STOP_MIN);
//  delay(1000);
//  Serial.println("Ready!");

  angle = 0;
}


void loop() {  
  if (Serial.available()) {
    angle = Serial.parseInt(SKIP_ALL, '\n');
    
    Serial.print("Rotate to ");
    Serial.println(angle);
//    Serial.println(Serial.read());
  }  

  X.rotateTo(angle);
  
}
