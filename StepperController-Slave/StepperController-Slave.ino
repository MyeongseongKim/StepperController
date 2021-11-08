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
    String str = Serial.readStringUntil('\n');
//    Serial.println(str);

    char buf[str.length()+1];
    str.toCharArray(buf, str.length()+1);
    
    Serial.println(buf);

    float posString;
    float velString;
    
    sscanf(buf, "S%d I%d", 
           &steps, &interval);

    Serial.print("Target Steps : ");
    Serial.println(steps);
    Serial.print("Pulse Interval : ");
    Serial.println(interval);
  }  

  X.rotate(steps, interval);
  
}
