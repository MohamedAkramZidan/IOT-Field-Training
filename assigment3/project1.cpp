#include <Arduino.h>

const int IR = 15;
const int servo = 4;
const int PWM = 0;
const int PWM_F = 50;
const int PWM_R = 16;


void WriteServo(int angle){
  int duty = map(angle,0,180,1638,7864);
  ledcWrite(PWM,duty);
}

void setup(){
  Serial.begin(115200);
  pinMode(IR,INPUT);
  ledcSetup(PWM,PWM_F,PWM_R);
  ledcAttachPin(servo,PWM);
  WriteServo(0);
}

void loop(){
  int analog = analogRead(IR);
  if(analog < 4095){
    WriteServo(90);
    delay(200);
  }
  else{
    WriteServo(180);
    delay(200);
  }

}
