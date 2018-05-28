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
  lectura_sensor = analogRead(pulsePin);
  return lectura_sensor;
}

void SpaceGlove::takepulse(){
  muestras ++;
  lectura_sensor_acumulador += readPulse();
  media_lectura_sensor = (lectura_sensor_acumulador/muestras) + 300;
  
  if(lectura_sensor > media_lectura_sensor){
    flag = 1;
  }
  else{
    flag = 0;
  }

  if(flag_ante == 0 && flag == 1){
      inpulse = 1;
      }
  if(inpulse ==  1){
    if(flag == 0 && flag_ante == 1){
      inpulse = 0;
      pulso++;
      }
    }
    
    flag_ante = flag;
    
  
}


int SpaceGlove::aux(){
  return media_lectura_sensor;
}

int SpaceGlove::aux1(){
  return lectura_sensor;
}
int SpaceGlove::printpulse(){
  return pulso;
  
}
void SpaceGlove::reset(){
  pulso = 0;
}

