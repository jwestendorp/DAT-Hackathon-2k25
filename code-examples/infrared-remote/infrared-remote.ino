#include <IRremote.hpp>  // Use .hpp for the new version
#include "HID-Project.h"

// Define the IR receiver pin. It's good practice to use #define for pins.
#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
  Serial.println("IR Receiver ready. Point a remote at it!");
  Keyboard.begin();
  // Start the IR receiver.
  // IrReceiver object is now globally available, no need to declare it.
  // Use IrReceiver.begin() instead of irrecv.enableIRIn().
  // You can choose ENABLE_LED_FEEDBACK or DISABLE_LED_FEEDBACK.
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
}

void loop() {
  // Check if an IR signal has been received and decoded.
  // Use IrReceiver.decode() directly, no need for &results.
  if (IrReceiver.decode()) {
    // Print the decoded value in hexadecimal format.
    // The decoded value is now in IrReceiver.decodedIRData.decodedRawData.
    Serial.print("Received IR signal: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    char str[32];
    sprintf(str, "%lX", IrReceiver.decodedIRData.decodedRawData);

    for (int i = 0; i < strlen(str); i++) {
      Keyboard.write(str[i]);
      delay(50);
    }
    Keyboard.write(KEY_RETURN);
    // Optional: Print complete received data in one line
    // IrReceiver.printIRResultShort(&Serial);

    // Optional: Print the statement required to send this data
    // IrReceiver.printIRSendUsage(&Serial);

    // Resume receiving the next IR signal.
    // Use IrReceiver.resume() instead of irrecv.resume().
    IrReceiver.resume();
  }
}