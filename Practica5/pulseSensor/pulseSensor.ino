#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

//Pin Reset para el display
#define OLED_RESET 4

//Tiempo de muestreo en milisegundos (resolucion)
#define T_MUESTREO 10

//Pin del sensor se usa A0
#define PIN_SENSOR 0   

//Umbral de deteccion por encima del nivel medio de la seÃ±al
#define UMBRAL1 200
#define UMBRAL2 300
 

//TamaÃ±o de la pantalla donde se mostrara la grafica
#define EJEX 127
#define EJEY 15

//Frecuencia de refresco para mostrar ppm
#define SYNCPPM 9000

//Pin de entrada para el push button
#define push 2

//Variable auxiliar para almacenar el valor de millis()
unsigned long auxMillis = 0;
unsigned long mMillis = 0;
unsigned long mm = 0;
int muestras;
int pulso = 0;
int flag = 0;
int x0 = 0;
int x1 = 0;
int y0 = 0;
int y1 = 0;
int ppm;
int lectura_sensor;
int media_lectura_sensor;
long lectura_sensor_acumulador = 0;
int counter;
int flag_ante = 0;
int flagpush = 0;
int flagmenu = 1;
int inpulse = 0;
//Instancia del display
Adafruit_SSD1306 display(OLED_RESET);

void setup(){
  pinMode(push, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  //Inicializa display y muestra bienvenida
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Medidor de");
  display.println("Pulso");
  display.display();
  delay(500);
  display.clearDisplay();
  
  
} 


void loop(){
  if(digitalRead(push) == LOW){
    delay(20);
    flagpush = 1; 
    display.clearDisplay();   
    digitalWrite(13, HIGH);
    flagmenu = 0;
    mMillis = millis();
    
  }
  else{
    digitalWrite(13, LOW);    
  }

  if(flagpush == 1){
    grafica_senal();
    tomarPulso();       
   }  
}


void grafica_senal(){  

//Realiza una muestra cada T_MUESTREO
  if((millis() - auxMillis) > T_MUESTREO){
    auxMillis = millis();
    lectura_sensor = analogRead(PIN_SENSOR);
  }
    //------------RUTINA PARA GRAFICAR----------------
    //*************************************************
    //Configuracion del display
    display.setTextSize(2);
    display.setCursor(6, 18);
    display.println("PPM");
    display.display();
    display.setTextSize(1);
    display.setCursor(0, 31);
    
    //Resolucion en X
    x1 += 1;
    
    //Resolucion en Y
    y1 = EJEY - map(lectura_sensor, 0, 1023, 0, EJEY);
    
    //Dibuja la grafica
    display.drawLine(x0, y0, x1, y1, 1);
    display.display();
    counter++;

    //Refresca la pantalla cada EJEX tiempo, tambien se reestablecen
    //las variables de control
    if(x1 >= EJEX){
      int pp;
      mm = millis()- mMillis;
      Serial.println(mm);
      pp = pulso*60000/mm ;
      x1 = 0;
      display.clearDisplay(); 
      display.setTextSize(1);
      display.setCursor(20,0);
      display.println("Tu pulso es de: ");
      display.setTextSize(2);
      display.setCursor(6, 18);
      display.println("PPM");
      display.setCursor(65, 18);
      display.println(pp);
      Serial.println(pulso);
      display.display();
      counter = 0;
      flagpush = 0;
      pulso = 0;
      
      
    }
    y0 = y1;
    x0 = x1;
}

void tomarPulso(){
  //Deteccion de pulos si la lectura esta por encima del nivel medio

  //Calcula una señal que tiende a la parte media de la grafica
    muestras++;
    lectura_sensor_acumulador += lectura_sensor;
    media_lectura_sensor = lectura_sensor_acumulador/muestras;

    if(lectura_sensor > media_lectura_sensor){
      flag = 1;
      
    }

    else{
      flag = 0;
    }
    if(flag_ante == 0 && flag == 1){
      inpulse = 1;
    }
    if(inpulse = 1){
      if(flag==0 && flag_ante == 1){
        inpulse = 0;
        pulso++;
      }
    }
    
    flag_ante = flag;
}



