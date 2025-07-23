#include <Arduino.h>
#define LED_PIN 32     // Use GPIO 32 for LED (PWM)
#define LDR_PIN 34     // Use GPIO 34 for LDR (Analog Input)
#define POT_PIN 35     // Use GPIO 35 for Potentiometer (Analog Input)

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
}

void loop() {
  // Read sensor values (0-4095)
  int ldrValue = analogRead(LDR_PIN);       // LDR: Dark = Low, Bright = High
  int potValue = analogRead(POT_PIN);       // Potentiometer sets threshold
  
  // Map LDR to inverted brightness (Dark = 255, Bright = 0)
  int brightness = map(ldrValue, 0, 4095, 255, 0);
  
  // Map Potentiometer to threshold (0-255)
  int threshold = map(potValue, 0, 4095, 0, 255);

  // Adaptive lighting logic
  if (brightness < threshold) {
    // If ambient light is DARKER than threshold, turn LED ON
    analogWrite(LED_PIN, threshold - brightness);  // Brighter when darker
  } else {
    // If ambient light is BRIGHTER than threshold, turn LED OFF
    analogWrite(LED_PIN, 0);
  }

  // Print values to Serial Monitor (for debugging)
  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(" | Brightness: ");
  Serial.print(brightness);
  Serial.print(" | Threshold: ");
  Serial.println(threshold);

  delay(100);  // Small delay for stability
}