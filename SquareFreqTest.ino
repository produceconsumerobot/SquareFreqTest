   
float frequency = 1; //Hz
unsigned long samplingDelay;
unsigned long lastDelay;
unsigned long lastSampleTime;
boolean outState = LOW;

const int nOutPins = 4;
int outPins[nOutPins]  = {10, 11, 12, 13};
boolean outStates[nOutPins] = {HIGH, HIGH, HIGH, LOW};
boolean blinkPin[nOutPins] = {false, false, false, false};

const int nBlinkPins = 3;  
int blinkPins[nBlinkPins]  = {11, 12, 13};

void setup() {
  // Setup Pins
  for (int i=0; i<nOutPins; i++) {
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], outStates[i]);
  }
  
  samplingDelay = 1000000/frequency/2;
  //samplingDelay = 1/2/frequency*1000*1000;
  //samplingDelay = 1000000;
  
  lastSampleTime = micros();
}

void loop() {
  lastDelay = GetMicrosDelay(lastSampleTime); 
  
  if ( lastDelay > samplingDelay ) {
    lastSampleTime = micros();
    
    for (int i=0; i<nOutPins; i++) {
      if (blinkPin[i]) {
        outStates[i] = !outStates[i];
      }
    }

    // set the LED with the ledState of the variable:
    for (int i=0; i<nOutPins; i++) {
      pinMode(outPins[i], OUTPUT);
      digitalWrite(outPins[i], outStates[i]);
    }
  }
}
   
/* GetMicrosDelay 
** calculates time difference in microseconds between current time
** and passed time
** accounts for rollover of unsigned long
*/
unsigned long GetMicrosDelay(unsigned long t0) {
  unsigned long dt; // delay time (change)
  
  unsigned long t1 = micros();
  if ( (t1 - t0) < 0 ) { // account for unsigned long rollover
    dt = 4294967295 - t0 + t1; 
  } else {
    dt = t1 - t0;
  }
  return dt;
}
    
