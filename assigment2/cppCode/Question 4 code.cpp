#define LED1_PIN 32    // PWM-controlled by potentiometer (done)
#define LED2_PIN 33    // LED controlled by LDR (done)
#define LED3_PIN 25    // LED toggled by button (done)
#define LDR_PIN 34     // LDR input (done)
#define POT_PIN 35     // Potentiometer input (done)
#define BUTTON_PIN 26  // Push button input

// Button state variables
bool led3State = false;
bool lastButtonState = HIGH;
bool buttonState;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  
  // Set all LED pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button to ground with pullup
}

void loop() {
  // Read sensor values (0-4095)
  int ldrValue = analogRead(LDR_PIN);
  int potValue = analogRead(POT_PIN);
  
  // --- LED1 (POT-controlled) ---
  // ESP32 requires special analogWrite implementation
  int led1Brightness = map(potValue, 0, 4095, 0, 255);
  analogWriteESP32(LED1_PIN, led1Brightness);
  
  // --- LED2 (LDR-controlled) ---
  int ldrMapped = map(ldrValue, 0, 4095, 255, 0); // Dark=HIGH, Bright=LOW
  int ldrThreshold = 150; // Adjust this threshold as needed
  
  digitalWrite(LED2_PIN, (ldrMapped < ldrThreshold) ? HIGH : LOW);
  
  // --- LED3 (Button-controlled) ---
  // Read button with debounce
  bool reading = digitalRead(BUTTON_PIN);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) { // Button pressed (pulled up)
        led3State = !led3State;
        digitalWrite(LED3_PIN, led3State);
      }
    }
  }
  lastButtonState = reading;
  
  // Print debug information
  Serial.print("POT: ");
  Serial.print(potValue);
  Serial.print(" (");
  Serial.print(led1Brightness);
  Serial.print(") | LDR: ");
  Serial.print(ldrValue);
  Serial.print(" (");
  Serial.print(ldrMapped);
  Serial.print(") | LED2: ");
  Serial.print(digitalRead(LED2_PIN));
  Serial.print(" | LED3: ");
  Serial.println(led3State);
  
  delay(10);
}

// ESP32-compatible analogWrite implementation
void analogWriteESP32(uint8_t pin, uint32_t value) {
  if (value == 0) {
    digitalWrite(pin, LOW);
  } else if (value == 255) {
    digitalWrite(pin, HIGH);
  } else {
    // Crude PWM implementation (not as precise as ledc)
    digitalWrite(pin, HIGH);
    delayMicroseconds(value * 8);  // Adjust timing as needed
    digitalWrite(pin, LOW);
    delayMicroseconds((255 - value) * 8);
  }
}