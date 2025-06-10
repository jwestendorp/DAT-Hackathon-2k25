#include "HID-Project.h"

#define VAPE_PIN 15
bool isPuffing = false;


void setup() {
  pinMode(VAPE_PIN, INPUT);
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  bool currentPuffValue = digitalRead(VAPE_PIN) == HIGH;

  handlePuff(currentPuffValue);
}


void handlePuff(bool currentPuff) {
  // Every arduino tick we read the value of VAPE_PIN to see if it is being inhaled.
  // However, to handle a long drag we don't just want to listen for the inhale value,
  // we want to listen for *state changes* in the inhale value. So we compare:
  // PREVIOUS PUFF     -->    CURRENT PUFF


  // not inhaling      -->    no puff     = do nothing
  if (!isPuffing && !currentPuff) return;

  // not pressed       -->    pressed         = we just inhaled
  if (!isPuffing && currentPuff) {
    inhale();
    isPuffing = true;
  }

  // pressed          -->    pressed         = we are still inhaling
  if (isPuffing && currentPuff) {
    Keyboard.write('*');
  };

  // pressed          -->    not pressed     = we just released
  if (isPuffing && !currentPuff) {
    exhale();
    isPuffing = false;
  }
}


void inhale() {
  const char* word = "inhale";

  for (int i = 0; word[i] != '\0'; i++) {
    Keyboard.write(word[i]);
    delay(50);
  }

  Keyboard.write(KEY_RETURN);
}

void exhale() {
  const char* word = "exhale";

  Keyboard.write(KEY_RETURN);

  for (int i = 0; word[i] != '\0'; i++) {
    Keyboard.write(word[i]);
    delay(100);
  }

  Keyboard.write(KEY_RETURN);
}
