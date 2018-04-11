//**********Librerias**********
#include <MedianFilter.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define reset 4

//Declaracion de objetos
Adafruit_SSD1306 display(reset);
MedianFilter prueba(20,0);

int value;
int filtered;

void setup()
{
  //Se inicializa el display OLED
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Sharp");
  display.println("GP2Y0A21F");
  display.display();
  delay(2000);
  display.clearDisplay();

}

void loop()
{
  //Conversion ADC
  value = analogRead(A0);
  //Filtro de datos para reducir el ruido
  prueba.in(value);
  filtered = prueba.out();
  Serial.println(filtered);
  //Se obtiene la distancia en relacion con los datos de entrada
  float distancia_cm = 10597.1 * pow(filtered, -1.13175);
  //Se imprime el valor de la distancia en el display OLED
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("Sharp GP2Y0A21F");
  display.setTextSize(2);
  display.setCursor(23, 15);
  display.print(distancia_cm,1);
  display.print(" cm");
  display.display();
  delay(50);  
  display.clearDisplay();                                   

}
