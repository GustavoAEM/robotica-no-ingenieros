#include<Servo.h>
#define CTRL 9
#define LED 13

Servo sg90;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  sg90.attach(CTRL);
  sg90.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    char val = Serial.read();
    if(val == '1') sg90.write(0);
    if(val == '2') sg90.write(20);
    if(val == '3') sg90.write(45);
    if(val == '4') sg90.write(100);
    if(val == '5') sg90.write(180);
    
    
    
  }

}
