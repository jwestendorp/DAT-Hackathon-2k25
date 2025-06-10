
#include "HID-Project.h"


int sensor = 2;   // the pin that the sensor is atteched to
int state = LOW;  // by default, no motion detected
int val = 0;      // variable to store the sensor status (value)

void setup() {

  pinMode(sensor, INPUT);  // initialize sensor as an input
  Serial.begin(9600);      // initialize serial
}

void loop() {
  val = digitalRead(sensor);  // read sensor value
  if (val == HIGH) {          // check if the sensor is HIGH

    if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;  // update variable state to HIGH
    }
  } else {


    if (state == HIGH) {
      Serial.println("Motion stopped!");
      state = LOW;  // update variable state to LOW
    }
  }
}