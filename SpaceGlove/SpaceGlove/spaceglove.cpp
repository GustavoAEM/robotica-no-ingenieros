#include "SpaceGlove.h"
#include "Arduino.h"



SpaceGlove::SpaceGlove() {

}

void SpaceGlove::attachTemp(int inTemPin) {
  SpaceGlove:temperaturePin = inTemPin;
  sTemp = new MedianFilter(20,0);


}

float SpaceGlove::readTemp() {
  tempValue = analogRead(temperaturePin);
  sTemp -> in(tempValue);
  return (sTemp -> out() * 5.0 * 100.0 / 1024.0);

}

void SpaceGlove::attachSharp(int inSharpPin){
  SpaceGlove:sharpPin = inSharpPin;
  sStep = new MedianFilter(20,0);
  
  
}

float SpaceGlove::readSharp(){
  sharpValue = analogRead(sharpPin);
  sStep -> in(sharpValue);
  return 10597.1 * pow(sStep -> out(), -1.13175);
}


void SpaceGlove::attachPulse(int inPulsePin){
  pulsePin = inPulsePin;
}

int SpaceGlove::readPulse(){
  return analogRead(pulsePin);
}

