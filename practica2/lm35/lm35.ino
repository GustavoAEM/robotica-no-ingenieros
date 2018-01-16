//Led de indicador ON/OF para saber que nuestro Arduino está prendido
#define status_led 13

//Se define el periodo para mostrar la temperatura
#define periodo 3

//Libreria para usar las interrupciones 
#include <TimerOne.h>


float sensor = 0;
float temperatura;
int contador = 0;
float promedio = 0;
float sumador = 0;

//Interrupcion salta cada segundo
void ISR_measureTemp(){
  //Esta interrupcion salta cada segundo, y se llama a la funcion medicion
  medicion();
  }

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
      Serial.print("La temperatura promedio es: "); 
      Serial.print(promedio,1);
      Serial.println(" °C");
      contador = sumador = promedio = 0;   
      
    }
  
    
  
}

