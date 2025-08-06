#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

const char* ssid = "Martell";
const char* password = "MarwanMartell@04";

const int ir = 34;
const int SERVO = 4;

const int PWM = 0;
const int PWM_F = 50;
const int PWM_R = 16;

const char* mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;
const  char* topic_publish_ir = "esp32/ir_sensor";
const char* topic_subscribe_cmd = "esp32/servo_cmd";


WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

long previous_time = 0;

void WriteServo(int angle) {
    int duty = map(angle, 0, 180, 1683, 7864);
    ledcWrite(PWM, duty);
}


void reconnect(){
  Serial.println("Connecting to HiveMQT....");
  while(!mqttClient.connected()){
    Serial.println("Reconnecting to MQTT Broker...");
    String clientId = "ESP32Client-";
    clientId+= String(random(0xffff),HEX);

    if(mqttClient.connect(clientId.c_str())){
      Serial.println("Connected to MQTT Broker");
      mqttClient.subscribe(topic_subscribe_cmd);
    }
    else{
      Serial.print("Failed ,rc=");
      Serial.print(mqttClient.state());
      Serial.println("Trying Again in 5s ....");
      delay(5000);
    }
  }
}

void callback(char* topic , byte* message , unsigned int len){
  String  cmd = "";
  for(int x = 0 ; x < len ; x++){
    cmd +=(char)message[x];
  }

  Serial.println("Command received");
  Serial.println(cmd);

  cmd.toLowerCase();

  if(cmd == "open"){
    WriteServo(90);
  }
  else if(cmd == "close"){
    WriteServo(0);
  }
}


void setup_mqtt(){
  mqttClient.setServer(mqtt_broker,mqtt_port);
  mqttClient.setCallback(callback);
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


  ledcSetup(PWM, PWM_F, PWM_R);
  ledcAttachPin(SERVO, PWM);
  WriteServo(0); 

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
  int presence = irR > 500 ? 1 : 0;  
  mqttClient.publish(topic_publish_ir, String(presence).c_str());
  }
}
