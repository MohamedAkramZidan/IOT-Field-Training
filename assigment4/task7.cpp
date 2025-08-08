#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include "cert.h"

// Wifi settings
const char* ssid = "Martell";
const char* password = "MarwanMartell@04";

// HiveMQ settings
const char* mqtt_broker = "5965aa9309824cb48daa5da0a2083f47.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_usernmae="Maro123";
const char* mqtt_password="Marwan@012";
const  char* topic_publish_ir = "esp32/ir";
WiFiClientSecure Wifi;
PubSubClient mqttClient(Wifi);

// pins
const int ir = 34;

//lcd
LiquidCrystal_I2C lcd(0x27,16,2);

//other
int lasttime = 0;



// helper functions

void LCDInit(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void ConnectMqtt(){
  Serial.println("Connecting.....");
  while(!mqttClient.connected()){
    Serial.println("Reconnecting....");
    String Client = "ESP32CLIENT-";
    Client+= String(random(0xfffff),HEX);

    if(mqttClient.connect(Client.c_str(),mqtt_usernmae,mqtt_password)){
      Serial.println("Connected To Mqtt Server (Broker)");
      mqttClient.subscribe(topic_publish_ir);
    }
    else{
      Serial.print("Failed rc=");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload , unsigned int len){
  payload[len]='\0';
  String message = String((char*)payload);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MQTT:");
  lcd.setCursor(0, 1);
  lcd.print(message);
}


void setUpMqtt(){
  mqttClient.setServer(mqtt_broker,mqtt_port);
  mqttClient.setCallback(callback);
}

const int BufferSizer = 1e2;
char jsonBuffer[BufferSizer];
const char* toJson(const int data){
  snprintf(jsonBuffer,sizeof jsonBuffer,"{\"data\":%d}",data);
  return jsonBuffer;
}



void setup(){
  Serial.begin(115200);
  pinMode(ir,INPUT);

  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.print("Connected!");

  Wifi.setCACert(root_ca);
  setUpMqtt();
  ConnectMqtt();

  LCDInit();

}



void loop(){
  mqttClient.loop();
  int now = millis();
  if(now - lasttime > 1000){
    lasttime = now;
    int read = analogRead(ir);
    const char* jsonData = toJson(read);
    mqttClient.publish(topic_publish_ir,jsonData);
    Serial.println(jsonData);
  }
}
