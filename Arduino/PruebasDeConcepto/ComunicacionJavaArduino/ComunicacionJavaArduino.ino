
int rojo = 9;
int verde = 10;
int azul = 11;


void setup() {
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);

  analogWrite(rojo, 255);
  analogWrite(verde, 0);
  analogWrite(azul, 0);

  Serial.begin(9600);
  while(!Serial)
    ;
}

void loop() {
  if(Serial.available() > 0){
    byte incomingByte = Serial.read();
    if(incomingByte != -1){
      analogWrite(rojo, 0);
      analogWrite(verde, 255);
      analogWrite(azul, 0);  
    }
  }
}
