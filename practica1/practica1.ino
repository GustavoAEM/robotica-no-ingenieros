//Declaracion de variables
String nombre;
char juego;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Saludos humano soy HRN88, ¿cual es tu nombre?");
  while(Serial.available() == 0){
    
  }
  nombre = Serial.readString();
  Serial.print("Hola ");
  Serial.println(nombre);
  Serial.println("Soy el sistema dentro de tu Arduino");
  Serial.println("por el momento no se hacer muchas cosas");
  Serial.println("pero podras programarme para que realice nuevas tareas");
  Serial.println("descubriremos un mundo interesante y creativo...");
  Serial.println();
  Serial.print("Oye ");
  Serial.print(nombre);
  Serial.println(".....¿quieres jugar un juego? presiona 's' para si o 'n' para no");
  while(Serial.available() ==0 ){
    
  }
  juego = Serial.read();
  
  if(juego == 's'){
    Serial.println("Genial, vamos a divertirnos!");
    
    
    
  }
  
  
  
  

}
