#include "HID-Project.h"

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_PRESS 10

bool isPressed = false;

void setup() {
  Serial.begin(9600);
  AbsoluteMouse.begin();

  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_PRESS, INPUT_PULLUP);
}


void loop() {
  int joystickX = analogRead(JOYSTICK_X);
  int joystickY = analogRead(JOYSTICK_Y);
  bool joystickPressed = digitalRead(JOYSTICK_PRESS) == 0;

  int cursorX = map(joystickX, 0, 1023, -32768, 32767);
  int cursorY = map(joystickY, 0, 1023, -32768, 32767);

  Serial.print("X: ");
  Serial.print(joystickX);
  Serial.print(", Y: ");
  Serial.print(joystickY);
  Serial.print(", Pressed: ");
  Serial.println(joystickPressed);

  AbsoluteMouse.moveTo(cursorX, cursorY);  // Move to coordinate (16bit signed, -32768 - 32767)
  handleClick(joystickPressed);
}


void handleClick(bool newPressValue) {
  // Every arduino tick we read the value of JOYSTICK_PRESS to see if it is being pressed.
  // However, to handle a "click" we don't just want to listen for the pressed value,
  // we want to listen for *state changes* in the pressed value. So we compare:
  // PREVIOUS PRESS   -->    CURRENT PRESS


  // not pressed      -->    not pressed     = do nothing
  if (!isPressed && !newPressValue) return;

  // not pressed      -->    pressed         = we just clicked
  if (!isPressed && newPressValue) {
    AbsoluteMouse.press(MOUSE_LEFT);
    isPressed = true;
  }

  // pressed          -->    pressed         = we are still pressing the button
  if (isPressed && newPressValue) return;

  // pressed          -->    not pressed     = we just released
  if (isPressed && !newPressValue) {
    AbsoluteMouse.release(MOUSE_LEFT);
    isPressed = false;
  }
}