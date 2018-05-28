#ifndef SpaceGlove_h
#define SpaceGlove_h
#include <MedianFilter.h>

class SpaceGlove{
  private:
  //Temperature sensor attributes
  int temperaturePin;
  float tempValue;
  MedianFilter* sTemp;
  

  //Sharp attributes
  int sharpPin;
  float sharpValue;
  MedianFilter* sStep;

  //Pulse sensor attributes
  int pulsePin;
  int pulseValue;
  //Median level
  int muestras;
  int lectura_sensor;
  int media_lectura_sensor;
  long lectura_sensor_acumulador = 0;
  int contador;
  int flag;
  int inpulse = 0;
  int pulso;
  int flag_ante = 0;
  int pp;
  unsigned long auxMillis = 0;
  
  public:
    //Constructor
    SpaceGlove();
    
    //LM35 methods
    void attachTemp(int inTempPin);
    float readTemp();
    
    //Sharp methods
    void attachSharp(int inSharpPin);
    float readSharp();

    //Pulse methods
    void attachPulse(int inPulsePin);
    
    //Funcion auxiliar
    int readPulse();
    void takepulse();

    int aux();
    int aux1();
    int printpulse();
    void reset();
   
  
};



#endif
