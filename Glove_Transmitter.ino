#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>

// SoftwareSerial setup: RX = Pin 2, TX = Pin 3
SoftwareSerial BT(2, 3); 

// Hardware ID initialization
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("Initializing Gesture Remote...");

  if(!accel.begin()) {
    Serial.println("Error: ADXL345 not detected! Check I2C wiring (A4/A5).");
    while(1);
  }

  // 2G mode provides maximum resolution for hand tilts
  accel.setRange(ADXL345_RANGE_2_G);
  Serial.println("Remote Online and Broadcasting...");
}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);

  float x = event.acceleration.x;
  float y = event.acceleration.y;

  /* TILT LOGIC:
     Forward / Backward -> Evaluated on X-axis
     Left / Right       -> Evaluated on Y-axis
  */

  if (x > 3.5) {
    BT.print('F'); 
    Serial.println("Command: Forward");
  } 
  else if (x < -3.5) {
    BT.print('B'); 
    Serial.println("Command: Backward");
  } 
  else if (y > 3.5) {
    BT.print('L'); 
    Serial.println("Command: Left");
  } 
  else if (y < -3.5) {
    BT.print('R'); 
    Serial.println("Command: Right");
  } 
  else {
    BT.print('S'); 
    Serial.println("Command: Stop");
  }

  delay(100); // 100ms sample rate for smooth real-time response
}