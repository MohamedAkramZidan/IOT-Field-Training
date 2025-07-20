#include <Arduino.h>

#define LED_PIN 23
#define BUTTON_PIN 4

bool ledState = false;
bool buttonState = HIGH;            // current stable state
bool lastReading = HIGH;            // last raw reading
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  bool currentReading = digitalRead(BUTTON_PIN);

  if (currentReading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentReading != buttonState) {
      buttonState = currentReading;
      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      }
    }
  }

  lastReading = currentReading;
}
