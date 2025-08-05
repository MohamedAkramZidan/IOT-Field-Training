#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

const char* ssid = "Martell";
const char* pass = "MarwanMartell@04";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 2 * 3600;      // Egypt Standard Time (UTC+2)
const int daylightOffset_sec = 3600;      // Add 1 hour for DST (UTC+3 in summer)

const int lcdColumns = 16;
const int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void LCDWrite(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void ConnectWifiAndTime() {
  LCDWrite("Connecting WiFi");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    lcd.print(".");
    delay(500);
  }

  LCDWrite("WiFi Connected!");
  delay(1000);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    LCDWrite("Waiting NTP...");
    delay(1000);
  }

  LCDWrite("Time Synced!");
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  ConnectWifiAndTime();
}

void loop() {
  struct tm timeinfo;
  lcd.clear();
  if (getLocalTime(&timeinfo)) {
    char timeStr[9];  // HH:MM:SS
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);

    char dateStr[17]; // DD-MM-YYYY
    strftime(dateStr, sizeof(dateStr), "%d-%m-%Y", &timeinfo);

    lcd.setCursor(0, 0);
    lcd.print(timeStr);
    lcd.setCursor(0, 1);
    lcd.print(dateStr);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Time Error");
  }

  delay(1000);
}
