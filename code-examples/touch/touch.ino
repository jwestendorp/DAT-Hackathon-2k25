#include "HID-Project.h"

#define LEFT_PIN 2
#define RIGHT_PIN 3

// Variable to store the current state of the sensor
int touchStateL = 0;
int touchStateR = 0;

// Variable to store the previous state to detect changes
int lastTouchStateL = 0;
int lastTouchStateR = 0;

void setup() {
  // Initialize serial communication for printing to the console
  Serial.begin(9600);
  Serial.println("TTP223 Touch Sensor Test");
  Serial.println("-------------------------");

  Mouse.begin();

  // Set the touch sensor pin as an INPUT
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
}

void loop() {
  // Read the current state of the touch sensor pin
  // When touched, it usually goes HIGH (or LOW depending on configuration)
  touchStateL = digitalRead(LEFT_PIN);
  touchStateR = digitalRead(RIGHT_PIN);

  // Check if the current state is different from the previous state
  // This helps detect a "press" or "release" event

    if (touchStateL == HIGH) {  // If the sensor output is HIGH when touched (common default)
      Serial.println("Sensor TOUCHED!");
      Mouse.move(10, 0);
    } 


    if (touchStateR == HIGH) {  // If the sensor output is HIGH when touched (common default)
      Serial.println("Sensor TOUCHED!");
      Mouse.move(-10, 0);
    } 

  delay(50);

  // Update the last state for the next loop iteration
  lastTouchStateL = touchStateL;
  lastTouchStateR = touchStateR;
}