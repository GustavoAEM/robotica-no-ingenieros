//Definicion de los pins de control para el LCD
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3 
#define D7 2

#define COLS 16
#define ROWS 2

//Led ON/OF para saber que nuestro Arduino está prendido
#define status_led 13

//Se define el periodo para mostrar la temperatura
#define periodo 3

//Libreria para usar las interrupciones 
#include <TimerOne.h>
#include <LiquidCrystal.h>


float sensor = 0;
float temperatura;
int contador = 0;
float promedio = 0;
float sumador = 0;
byte caracter[8] = {
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

//Interrupcion salta cada segundo
void ISR_measureTemp(){
  //Esta interrupcion salta cada segundo, y se llama a la funcion medicion
  medicion();
  }

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  // put your setup code here, to run once:
  
  //Se define el led indicador como salida y se activa
  pinMode(status_led, OUTPUT);
  digitalWrite(status_led, HIGH);
  
  //Se inicializa el puerto de comunicacion serie
  Serial.begin(9600);

  //Indicamos el uso de referencia interna de 1.1 V
  analogReference(INTERNAL);

  //Se define cada cuantos us salta la interrupcion
  Timer1.initialize(1000000);

  //Se define la interrupcion
  Timer1.attachInterrupt(ISR_measureTemp);

  //Se inicializa el LCD
  lcd.begin(COLS, ROWS);

  //Creando el simbolo para grados
  lcd.createChar(0, caracter);
  delay(100);

  lcd.print("   Sensor LM35");
  
  

}


void loop() {
  // put your main code here, to run repeatedly:
  }

void medicion(){
  if(contador <= periodo){
    temperatura = (analogRead(A0)*1.1/1023)/0.010;
    sumador = temperatura + sumador;
    promedio = sumador/periodo; 
    contador += 1;
    
    
  }
   if(contador >= periodo){  
      lcd.setCursor(3, 0);
      lcd.print("Sensor LM35");   
      lcd.setCursor(5, 1);
      lcd.print(promedio, 1);
      lcd.write(byte(0));
      lcd.print("C");
      contador = sumador = promedio = 0;   
      
    }
  
}

