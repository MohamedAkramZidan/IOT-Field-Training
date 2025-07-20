#include <Arduino.h>

#define POT_PIN 12
#define LED_PIN 14


void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(POT_PIN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(POT_PIN);

  int brightness = map(potValue,0,4095,0,255);

  analogWrite(LED_PIN,brightness);

  delay(50); // this speeds up the simulation
}

