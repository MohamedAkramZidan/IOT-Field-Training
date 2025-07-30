#include <Arduino.h>

const int LDR_PIN = 34;
const int LED_PIN = 23;
const int BUZZER_PIN = 25;
const int SERVO_PIN = 4;
const int BUTTON_PIN = 27;

const int THRESHOLD = 1500; 
bool overrideActive = false;
const int PWM = 0;
const int PWM_F = 50;
const int PWM_R = 16;

void WriteServo(int angle){
  int duty = map(angle,0,180,1638,7864);
  ledcWrite(PWM,duty);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  ledcSetup(PWM,PWM_F,PWM_R);
  ledcAttachPin(SERVO_PIN,PWM);
  WriteServo(0);
  Serial.begin(115200);
}

void loop() {
  int lightValue = analogRead(LDR_PIN);
  bool buttonPressed = digitalRead(BUTTON_PIN) == HIGH;

  Serial.print("LDR: ");
  Serial.print(lightValue);
  Serial.print(" | Override: ");
  Serial.println(overrideActive);
  Serial.println(digitalRead(BUTTON_PIN));

  if (buttonPressed) {
    overrideActive = true;
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    WriteServo(0);
  }
  if(!overrideActive){
    if (lightValue < THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
        WriteServo(180);  
    } else {
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        WriteServo(0);
    }
  }

  delay(200);
}
