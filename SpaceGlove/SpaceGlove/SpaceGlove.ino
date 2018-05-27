  #include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include "SpaceGlove.h"

//Tiempo de muestreo en milisegundos (resolucion)
#define T_MUESTREO 10
#define T_ISR 300

//Reset display
#define OLED_RESET 4

//Screen size
#define EJEX 127
#define EJEY 15
#define IN_BUTTON 3
//Functions
void intro();
void isr_push();


//Variables
int flag_0 = 0;
int flag_1 = 0;
int flag_2 = 0;
int x0 = 0;
int x1 = 0;
int y0 = 0;
int y1 = 0;
int counter = 0;
unsigned long auxmillis = 0;
unsigned long measureMillis = 0;
unsigned long pulsemillis = 0;
unsigned long mm = 0;
int pulso = 0;
int ppm;
int estado = '1';
bool flag;
int contador = 0;
SpaceGlove guante;
Adafruit_SSD1306 display(OLED_RESET);

void sharp_measure();
void vita_measure();
void tomarPulso();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  guante.attachTemp(1);
  guante.attachSharp(0);
  guante.attachPulse(2);
  pinMode(IN_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IN_BUTTON), isr_push, FALLING);

  //Initialize display
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  intro();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  switch(estado){
    case '1':
            //Serial.println(guante.readPulse());
            if((millis() - measureMillis) > T_MUESTREO ){
              measureMillis = millis();
              guante.takepulse();
              grafica();
              //Serial.println(String(guante.aux1())+ "," + String(guante.aux()));
              if((millis() - pulsemillis) > 1000){
                pulsemillis = millis();
                contador++;
              }
              if(contador == 20){
                contador = 0;
                Serial.println(guante.printpulse());
                ppm = guante.printpulse()*3;
                guante.reset(); 
                
              }
              
              }
              
            
          /************************************/
          if(estado == '1' && flag == HIGH) {
            flag = LOW;
            estado = '2';
            display.clearDisplay();
          }
          break;

    case '2':
          
          sharp_measure();
          /************************************/
          if(estado == '2' && flag == HIGH){
            flag = LOW;
            estado = '1';
            x1 = 0;
            y0 = y1;
            x0 = x1;
            guante.reset();
            pulsemillis = 0;
            display.clearDisplay();
          }
          break;
    
  }

  
  

 
    
 
  
  
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

void sharp_measure(){
  Serial.print(" Distance: ");
  Serial.println(guante.readSharp());
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12,0);
  display.println("Distancia");
  display.setCursor(12,18);
  display.print(guante.readSharp(), 1);
  display.println("  cm ");
  display.display();
  
}

void isr_push(){
  if((millis() - auxmillis) >= T_ISR ){
    flag = HIGH;
    auxmillis = millis();    
  } 
  
}

void grafica(){
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
        display.print("  PPM: ");
        display.print(ppm);
         
      
      
      
      }
      y0 = y1;
      x0 = x1;
}

