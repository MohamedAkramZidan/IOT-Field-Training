#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const int LDR = 15;
const int servo = 4;
const int led = 23;
const int IR = 34;
const int buzzer = 19;
const int btn = 35;

const int PWM = 0;
const int PWM_F = 50;
const int PWM_R = 16;
const int lcdCols = 16;
const int lcdRows = 2;

const int threshold = 1600;
int CurrentMood = 1; // light;
LiquidCrystal_I2C lcd(0x27,lcdCols,lcdRows);

bool lastButtonState = LOW;

void WriteServo(int angle){
    int duty = map(angle,0,180,1638,7864);
    ledcWrite(PWM,duty);
}

void setup(){
    Serial.begin(115200);
    pinMode(LDR,INPUT);
    pinMode(led,OUTPUT);
    pinMode(IR,INPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(btn,INPUT);

    ledcSetup(PWM,PWM_F,PWM_R);
    ledcAttachPin(servo,PWM);
    WriteServo(0);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);

}
bool manualOverride = false;

void loop() {
    int analog = analogRead(LDR);
    int digital = digitalRead(IR);
    bool buttonState = digitalRead(btn);
    Serial.println(analog);

    if (buttonState == HIGH && lastButtonState == LOW) {
        manualOverride = true;
        lcd.clear();
        lcd.print("Manual Override");
        lcd.setCursor(0, 1);
        lcd.print("Activated");

        WriteServo(0);
        digitalWrite(buzzer, LOW);
        digitalWrite(led, LOW);
    }

    lastButtonState = buttonState;

    if (!manualOverride) {
        lcd.clear();
        if (analog < threshold) {
            WriteServo(180);
            digitalWrite(led, HIGH);
            lcd.print("Night Mode:");
            lcd.setCursor(0, 1);
            lcd.print("Door Locked");
            CurrentMood = 0;

            if (digital == LOW) {
                digitalWrite(buzzer, HIGH);
                lcd.clear();
                lcd.print("Alert:");
                lcd.setCursor(0, 1);
                lcd.print("Motion Detected !");
                // delay(5000);
                digitalWrite(buzzer, LOW);
            }
        } else {
            WriteServo(0);
            digitalWrite(led, LOW);
            lcd.print("Light Mode:");
            lcd.setCursor(0, 1);
            lcd.print("Door Unlocked");
            CurrentMood = 1;
        }
    }

    delay(100);
}
