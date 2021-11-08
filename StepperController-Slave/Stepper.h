class Stepper {
  public: 
    int DIR_PIN;        // LOW:counterclockwise, HIGH:clockwise
    int STEP_PIN;
    int ENABLE_PIN;

    int STEPS_PER_REVOLUTION;
    int MICROSTEPS;
  
    unsigned long curMicros;
    unsigned long prevMicros;
    long interval;

    long curSteps;
    long targetSteps;
    boolean isRunning;


    Stepper() {
      
    }
       
    Stepper(int dir, int step, int enable) {
      DIR_PIN = dir;
      STEP_PIN = step;
      ENABLE_PIN = enable;
    }

    void begin(int n, int m) {
      STEPS_PER_REVOLUTION = n;
      MICROSTEPS = m;
      
      pinMode(DIR_PIN, OUTPUT);
      pinMode(STEP_PIN, OUTPUT);
      pinMode(ENABLE_PIN, OUTPUT);
      digitalWrite(ENABLE_PIN, LOW);

      curMicros = 0;
      prevMicros = 0;

      curSteps = 0;
      targetSteps = 0;
      isRunning = false;
    }

    void home(int endstop) {
      interval = 100;
      while (digitalRead(endstop) == HIGH) {
        digitalWrite(STEP_PIN, HIGH);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(100);
      }
      curSteps = 0;
    }

    boolean rotate(long steps, int pulseInterval) {
//      targetSteps = angle * STEPS_PER_REVOLUTION * MICROSTEPS / 360;
//      float stepsPerSecond = angularVelocity * STEPS_PER_REVOLUTION * MICROSTEPS / 360;
//      interval = 1.0 / stepsPerSecond;
      
      long targetSteps = steps;
      int interval = pulseInterval;
      
      long delta = targetSteps - curSteps;

      if (delta == 0) {
        isRunning = false;
      }
      else {
        curMicros = micros();
        if (curMicros >= prevMicros + interval) {
          if (delta > 0) {
            digitalWrite(DIR_PIN, LOW);
            curSteps++;
          }
          else if (delta < 0) {
            digitalWrite(DIR_PIN, HIGH);
            curSteps--;
          }
          digitalWrite(STEP_PIN, HIGH);
          digitalWrite(STEP_PIN, LOW);
          prevMicros = curMicros;
        }
        isRunning = true;
      }

      return isRunning;
    }
    
};
