#include <Arduino.h>

const int LDR = 15;
const int SERVO = 4;
const int btn = 23;

const int PWM = 0;
const int PWM_F = 50;
const int PWM_R = 16;

void WriteServo(int angle) {
    int duty = map(angle, 0, 180, 1683, 7864);
    ledcWrite(PWM, duty);
}

bool reset = false;
void setup() {
    pinMode(LDR, INPUT);
    Serial.begin(115200);
    ledcSetup(PWM, PWM_F, PWM_R);
    ledcAttachPin(SERVO, PWM);
    WriteServo(0); 
}

void loop() {
    int btnClicked = digitalRead(btn) == HIGH;
    int lightVal = analogRead(LDR);
    Serial.print("LDR: ");
    Serial.println(lightVal);
    Serial.println(digitalRead(btn));

    if(btnClicked){
        WriteServo(0);
        reset = true;
    }
    if(!reset){
        if (lightVal > 3000) {
            WriteServo(120);
        } else if (lightVal > 2000) {
            WriteServo(90);
        } else if (lightVal > 1500) {
            WriteServo(60);
        } else if (lightVal > 600) {
            WriteServo(45);
        } else {
            WriteServo(30);
        }

    }
    delay(300); 
}
