#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include "SpaceGlove.h"

//Tiempo de muestreo en milisegundos (resolucion)
#define T_MUESTREO 10

//Reset display
#define OLED_RESET 4

//Screen size
#define EJEX 127
#define EJEY 15

//Functions
void intro();


//Variables
int x0 = 0;
int x1 = 0;
int y0 = 0;
int y1 = 0;
int counter = 0;
unsigned long auxMillis = 0;
SpaceGlove guante;
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  guante.attachTemp(1);
  guante.attachSharp(0);
  guante.attachPulse(2);

  //Initialize display
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  intro();
  

}

void loop() {
  // put your main code here, to run repeatedly:

  if((millis()-auxMillis) > T_MUESTREO){
    Serial.print("Temperature: ");
    Serial.print(guante.readTemp());
    Serial.print(" Distance: ");
    Serial.print(guante.readSharp());
    Serial.print(" Pulse: ");
    Serial.println(guante.readPulse());
    
  }
  //display.clearDisplay();
  
  //Resolucion en X
    x1 += 1;
    
    //Resolucion en Y
    y1 = EJEY - map(guante.readPulse(), 0, 1023, 0, EJEY);
    
    //Dibuja la grafica
    display.drawLine(x0, y0, x1, y1, 1);
    
    display.display();
    counter++;

    if(x1 >= EJEX){
      x1 = 0;
      display.clearDisplay(); 
      counter = 0;
      display.setTextSize(1);
      display.setCursor(0, 25);
      display.print("T: ");
      display.print(guante.readTemp());
      display.print(" C ");
      
      
      
    }
    y0 = y1;
    x0 = x1;
  
  
}
  

    
  


  
  
  

void intro(){
  //AEM INTRO
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45,0);
  display.println("AEM");
  display.setTextSize(1);
  display.setCursor(16,15);
  display.println("Agencia Espacial");
  display.setCursor(38,24);
  display.println("Mexicana");
  display.display();
  delay(2000);
  
  //SPACE GLOVE INTRO
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("SPACE");
  display.println("GLOVE");
  display.display();
  delay(2000);
  display.clearDisplay();
}

