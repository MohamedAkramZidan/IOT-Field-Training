#include <Arduino.h>

#define LDR_PIN 15
#define LED_PIN 4

const int threshold = 1000;

void setup() {
  Serial.begin(9600);          // Start Serial communication
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN,INPUT);
}

void loop() {
  int lightLevel = analogRead(LDR_PIN);
  Serial.println(lightLevel);  // Print to PlatformIO Serial Monitor

  if(lightLevel < 4000 ){
    digitalWrite(LED_PIN,LOW);
  }
  else{
    digitalWrite(LED_PIN,HIGH);
  }

  delay(500);
}
