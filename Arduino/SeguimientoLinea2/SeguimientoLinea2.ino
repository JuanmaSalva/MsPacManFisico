#define LINEA 1
#define PASILLO 0

#define TIEMPO_DE_GIRO 35
#define TIEMPO_RECTO 70


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

  if(izquierda == LINEA && centro == PASILLO && derecha == LINEA){
    //Serial.println("Recta");
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);
  }
  // else if(izquierda == PASILLO && centro == PASILLO && derecha == LINEA){
  //   digitalWrite(IN1I, HIGH);
  //   digitalWrite(IN2I, LOW);
  //   digitalWrite(IN1D, LOW);
  //   digitalWrite(IN2D, HIGH);
  //   delay(1000);
  // }
  else if (izquierda == PASILLO && derecha == LINEA) {
    //Serial.println("Desvio derecha");
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, HIGH);
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, LOW);
    delay(TIEMPO_DE_GIRO);
    recta(TIEMPO_RECTO);
  }
  else if(izquierda == LINEA && derecha == PASILLO){
    //Serial.println("Desvio izquierda");
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, LOW);
    digitalWrite(IN1D, HIGH);
    digitalWrite(IN2D, LOW);
    delay(TIEMPO_DE_GIRO);
    recta(TIEMPO_RECTO);
  }
  else{
    //Serial.println("Parada");
    digitalWrite(IN1I, LOW);
    digitalWrite(IN2I, LOW);
    digitalWrite(IN1D, LOW);
    digitalWrite(IN2D, LOW);
  }
}



void loop() {
  seguimientoLinea();
}
