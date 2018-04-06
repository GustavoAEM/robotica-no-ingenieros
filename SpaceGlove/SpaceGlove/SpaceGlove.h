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
    int readPulse();

   
  
};



#endif
