 #include <Arduino.h>



#define timeSeconds 10

// Set GPIOs for LED and PIR Motion Sensor
const int led = 35;
const int motionSensor = 36;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
void IRAM_ATTR detectsMovement() {
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(9600);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  // Set LED to LOW
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // Current time
  now = millis();
  if((digitalRead(led) == HIGH) && (motion == false)) {
    Serial.println("MOTION DETECTED!!!");
    digitalWrite(led,LOW);
    motion = true;
  }
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*100))) 
  {
    Serial.println("Motion stopped...");
    digitalWrite(led, HIGH);
    startTimer = false;
    motion=false;
    
  }
} 