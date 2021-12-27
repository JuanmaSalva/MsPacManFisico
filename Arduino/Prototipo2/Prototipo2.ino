int ENA = A0;
int IN1D = A1;
int IN2D = A2;
int IN1I = A3;
int IN2I = A4;
int ENB = A5;

int SENSOR_I = 7;
int SENSOR_C = 6;
int SENSOR_D = 5;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1D, OUTPUT);
  pinMode(IN2D, OUTPUT);
  pinMode(IN1I, OUTPUT);
  pinMode(IN2I, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);  

  pinMode(SENSOR_I, INPUT);
  pinMode(SENSOR_C, INPUT);
  pinMode(SENSOR_D, INPUT);

  Serial.begin(9600);
}


void recta(int tiempo){  
  digitalWrite(IN1I, LOW);
  digitalWrite(IN2I, HIGH);   
  digitalWrite(IN1D, HIGH);
  digitalWrite(IN2D, LOW);  
  delay(tiempo);
} 
    
void noventagrados(bool derecha){
  if(derecha){  
    digitalWrite(IN1I, HIGH);
    digitalWrite(IN2I, LOW);   
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);  
  }
  else {      
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);   
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, HIGH);   
  }
  delay(230);  
}

void cientoochentagrados(){
  digitalWrite(IN1I, LOW);
  digitalWrite(IN2I, HIGH);   
  digitalWrite(IN1D, LOW);
  digitalWrite(IN2D, HIGH);  
  delay(460);  
}

void parada(int tiempo){
  digitalWrite(IN1D, LOW);
  digitalWrite(IN2D, LOW);  
  digitalWrite(IN1I, LOW);
  digitalWrite(IN2I, LOW);
  delay(tiempo);  
}

void seguimientoLinea(){
  int izquierda = digitalRead(SENSOR_I);
  int centro = digitalRead(SENSOR_C);
  int derecha = digitalRead(SENSOR_D);
  //Serial.print(izquierda);
  //Serial.print(centro);
  //Serial.println(derecha);


  //recto
  if(izquierda == 1 && centro == 0 && derecha == 1){  
    Serial.println("Recta");
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);   
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);  
  }
  //nos hemos desviado hacia la derecha
  else if (izquierda == 0 && centro == 1) {     
    Serial.println("Desvio derecha");  
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);   
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, LOW); 
    delay(30); 
    recta(75);
  }
  //nos hemos desviado hacia la izquierda
  else if(centro == 1 && derecha == 0){
    Serial.println("Desvio izquierda");  
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, LOW);   
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);    
    delay(30); 
    recta(75);  
  }
  //nos paramos
  else{
    Serial.println("Parada");  
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, LOW);   
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, LOW);  
  }
}



void loop() {
  int izquierda = digitalRead(SENSOR_I);
  int centro = digitalRead(SENSOR_C);
  int derecha = digitalRead(SENSOR_D);
  //Serial.print(izquierda);
  //Serial.print(centro);
  //Serial.println(derecha);


  //recto
  if(izquierda == 1 && centro == 0 && derecha == 1){  
    Serial.println("Recta");
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);   
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);  
  }
  else{
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, LOW);   
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, LOW);      
  }
}
