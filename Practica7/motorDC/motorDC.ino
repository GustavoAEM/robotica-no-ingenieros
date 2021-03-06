#define M0 6
#define M1 7
#define EN 3
#define LED 13

int velocity = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(LED, HIGH);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    char ctrl = Serial.read();
    switch(ctrl){
      case '1':
        Serial.println("Velocidad baja " + String(velocity));
        velocity = 85;
      break;

      case '2':
        velocity = 170;
        Serial.println("Velocidad media " + String(velocity));
      break;

      case '3':
        velocity = 255;
        Serial.println("Velocidad alta " + String(velocity));
      break;

      case 'a':
        analogWrite(EN, velocity);
        digitalWrite(M0, HIGH);
        digitalWrite(M1, LOW); 
        Serial.println("Giro en sentido horario");
      break;

      case 's':
        analogWrite(EN, velocity);
        digitalWrite(M0, LOW);
        digitalWrite(M1, HIGH);
        Serial.println("Giro en sentido antihorario");
      break;

      case 'd':
        analogWrite(EN, velocity);
        digitalWrite(M0, LOW);
        digitalWrite(M1, LOW);
        Serial.println("Detener");
      break;
        
    }
  }

}
