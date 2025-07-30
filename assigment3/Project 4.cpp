#define BUTTON_PIN 14
#define LED_PIN 27
#define BUZZER_PIN 26
#define LDR_PIN 34
#define SERVO_PIN 25
#define THRESHOLD 1000

#include <ESP32Servo.h>

Servo myServo;

bool overrideMode = false;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(0);  
}

void loop() {
  int lightLevel = analogRead(LDR_PIN);
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Button press detected (LOW when pressed)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    overrideMode = !overrideMode;  
    if (overrideMode) {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      myServo.write(0);  // Unlock
      Serial.println("Manual Override: Unlocked");
    } else {
      Serial.println("Manual Override: Off (Resumed Auto)");
    }
    delay(300);  // Debounce
  }

  lastButtonState = currentButtonState;

  if (!overrideMode) {
    if (lightLevel < THRESHOLD) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      myServo.write(180);  // Lock
      Serial.println("Too Dark! Door Locked.");
    } else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      myServo.write(0);  // Unlock
      Serial.println("Bright Enough. Door Unlocked.");
    }
    delay(300);
  }
}
