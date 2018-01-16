//Declaracion de variables
String nombre;
char juego;
char resp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Saludos humano, ¿cuál es tu nombre?");
  while(Serial.available() == 0){
    
  }
  nombre = Serial.readString();
  Serial.print("Hola ");
  Serial.println(nombre);
  Serial.println("Soy HRN88 el sistema dentro de tu Arduino");
  Serial.println("por el momento no se realizar muchas cosas,");
  Serial.println("pero pronto podras programarme para realizar nuevas tareas:");
  Serial.println("controlar motores, leer sensores, desplegar informacion");
  Serial.println("incluso, puedo ser el sistema de control de tus robots.");
  Serial.println("Descubriremos un mundo lleno de posibilidades y creatividad");
  Serial.println();
  Serial.println("Te gustaria ver un video sobre todo lo que podras ser capaz de hacer");
  Serial.println("                Ingresa s para si o n para no");
  Serial.println();
  while(Serial.available() == 0){
 
  }
  resp = Serial.read();
  if(resp == 's'){
    Serial.println("      Genial, ingresa a esta direccion en tu navegador: ");
    Serial.println("         https://www.youtube.com/watch?v=eJg3yuAAawA");    
  }
  else if(resp == 'n'){
    Serial.println("Qué lastima te hubiera encantado");
  }
  Serial.println();
  Serial.println();
  delay(10000);
  Serial.print("Por el momento me despido, espero que el video te haya motivado "); 
  Serial.print(nombre);
  Serial.println("pronto nos veremos nuevamente, y recuerda estar al pendiente de las proximas publicaciones :)");
  Serial.println("Cerrando sesion");
  Serial.println("..........");
  while(1){}
  

   
  
  
  
  

}
