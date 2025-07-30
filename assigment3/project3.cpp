#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <math.h>

const int lcdCols = 16;
const int lcdRows = 2;
const int IR = 15;

LiquidCrystal_I2C lcd(0x27, lcdCols, lcdRows);

void setup() {
    pinMode(IR, INPUT);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void loop() {
    int rawValue = analogRead(IR);
    float voltage = rawValue * (3.3 / 4095.0); 
    float distance_cm = 27.86 * pow(voltage, -1.15);

    lcd.clear();
    lcd.setCursor(0, 0);

    if (distance_cm >= 10 && distance_cm <= 80) {
        lcd.print("Distance:");
        lcd.setCursor(0, 1);
        lcd.print(distance_cm, 1);  // One decimal place
        lcd.print(" cm");
    } else {
        lcd.print("Out of range");
    }

    delay(200);
}
