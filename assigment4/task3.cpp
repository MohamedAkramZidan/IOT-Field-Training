#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "Martell";
const char* password = "MarwanMartell@04";

const int ir = 34;

const char* mqtt_broker = "5965aa9309824cb48daa5da0a2083f47.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_usernmae="Maro123";
const char* mqtt_password="Marwan@012";
const  char* topic_publish_ir = "esp32/ir_sensor";

WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

long previous_time = 0;

void setup_mqtt(){
  mqttClient.setServer(mqtt_broker,mqtt_port);
}

void reconnect(){
  Serial.println("Connecting to HiveMQT....");
  while(!mqttClient.connected()){
    Serial.println("Reconnecting to MQTT Broker...");
    String clientId = "ESP32Client-";
    clientId+= String(random(0xffff),HEX);

    if(mqttClient.connect(clientId.c_str(),mqtt_usernmae,mqtt_password)){
      Serial.println("Connected to MQTT Broker");
    }
    else{
      Serial.print("Failed ,rc=");
      Serial.print(mqttClient.state());
      Serial.println("Trying Again in 5s ....");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ir,INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  wifiClient.setInsecure();
  setup_mqtt();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if(now - previous_time > 1000){
    previous_time = now;

    int irR = analogRead(ir);

    String IrRS = String(irR);
    Serial.println(IrRS);
    mqttClient.publish(topic_publish_ir,IrRS.c_str());
  }
}
