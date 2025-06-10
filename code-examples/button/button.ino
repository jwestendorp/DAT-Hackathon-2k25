#include "HID-Project.h"

// Define a Button structure
struct Button {
  int pin;
  bool previouslyPressed;
  bool currentlyPressed;
  char* message;
};

// We will create a list of all our buttons using the Button structure
Button buttons[] = {
  {
    pin: 2,
    previouslyPressed: false,
    currentlyPressed: false,
    message: "I just pressed button 1"
  },
  {
    pin: 3,
    previouslyPressed: false,
    currentlyPressed: false,
    message: "I just pressed button 2"
  }
};

// Button buttons[] = {
//   {1, false, false,  "I just pressed button 1"},
//   {2, false, false,  "I just pressed button 2"}
// };

const int NUM_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  // Initialize all button pins
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    // Read the current state of the button
    buttons[i].currentlyPressed = digitalRead(buttons[i].pin) == LOW;

    // Handle the button press
    if (buttons[i].currentlyPressed && !buttons[i].previouslyPressed) {
      // Button was just pressed
      typeMessage(buttons[i].message);
    }

    // Update the previous state
    buttons[i].previouslyPressed = buttons[i].currentlyPressed;
  }
}


void typeMessage(char* str) {
  for (int i = 0; i < strlen(str); i++) {
    Keyboard.write(str[i]);
    delay(50);
  }

  Keyboard.write(KEY_RETURN);
}