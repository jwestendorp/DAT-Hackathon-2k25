#include "HID-Project.h"

int buttonPin = 5;
int joystickPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  Gamepad.begin();
}

void loop() {

  //  Analog example
  int joystickValue = analogRead(joystickPin);
  int mappedValue = map(joystickValue, 0, 1023, -32767, 32767); // We have to map the 10bit input of the analog pin to the 16bit input of the gamepad
  Gamepad.xAxis(mappedValue);
  Serial.print("Joystick value:");
  Serial.println(joystickValue);

  //Digital Example
  int buttonValue = digitalRead(buttonPin);
  if (buttonValue == LOW) {
    Gamepad.press(1);
  } else if (buttonValue == HIGH) {
    Gamepad.release(1);
  }
  Serial.print("Button value:");
  Serial.println(!buttonValue);

  Gamepad.write();
  delay(100);
}