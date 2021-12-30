#define LINEA 1
#define PASILLO 0

#define VELOCIDAD_NORMAL 175
#define VELOCIDAD_REDUCIDA 80


int velocidadDerecha = 11; //derecha
int delanteDerecha = A1;
int atrasDerecha = A2;
int delanteIzquierda = A3;
int atrasIzquierda = A4;
int velocidadIzquierda = 10; //izquierda

int SENSOR_I = 7;
int SENSOR_C = 6;
int SENSOR_D = 5;


void setup() {
  pinMode(velocidadDerecha, OUTPUT);
  pinMode(delanteDerecha, OUTPUT);
  pinMode(atrasDerecha, OUTPUT);
  pinMode(delanteIzquierda, OUTPUT);
  pinMode(atrasIzquierda, OUTPUT);
  pinMode(velocidadIzquierda, OUTPUT);

  digitalWrite(velocidadDerecha, 100);
  digitalWrite(velocidadIzquierda, 100);

  pinMode(SENSOR_I, INPUT);
  pinMode(SENSOR_C, INPUT);
  pinMode(SENSOR_D, INPUT);

  Serial.begin(9600);
}


void recta(bool marchaAlante){
  if(marchaAlante){
    digitalWrite(delanteIzquierda, LOW);
    digitalWrite(atrasIzquierda, HIGH);
    digitalWrite(delanteDerecha, HIGH);
    digitalWrite(atrasDerecha, LOW);
  }
  else {
    digitalWrite(delanteIzquierda, HIGH);
    digitalWrite(atrasIzquierda, LOW);
    digitalWrite(delanteDerecha, LOW);
    digitalWrite(atrasDerecha, HIGH);
  }
}

void noventagrados(bool derecha){
  analogWrite(velocidadIzquierda, VELOCIDAD_NORMAL);
  analogWrite(velocidadDerecha, VELOCIDAD_NORMAL);

  if(derecha){
    digitalWrite(delanteIzquierda, LOW);
    digitalWrite(atrasIzquierda, HIGH);
    digitalWrite(delanteDerecha, LOW);
    digitalWrite(atrasDerecha, HIGH);
  }
  else {
    digitalWrite(delanteIzquierda, HIGH);
    digitalWrite(atrasIzquierda, LOW);
    digitalWrite(delanteDerecha, HIGH);
    digitalWrite(atrasDerecha, LOW);
  }
  delay(545);
}

void cientoochentagrados(){
  digitalWrite(delanteIzquierda, LOW);
  digitalWrite(atrasIzquierda, HIGH);
  digitalWrite(delanteDerecha, LOW);
  digitalWrite(atrasDerecha, HIGH);
  delay(460);
}

void parada(){
  digitalWrite(delanteDerecha, LOW);
  digitalWrite(atrasDerecha, LOW);
  digitalWrite(delanteIzquierda, LOW);
  digitalWrite(atrasIzquierda, LOW);
}



void seguimientoLinea(){
  int izquierda = digitalRead(SENSOR_I);
  int centro = digitalRead(SENSOR_C);
  int derecha = digitalRead(SENSOR_D);

  if(izquierda == LINEA && centro == PASILLO && derecha == LINEA){ //recto
    recta(true);
    analogWrite(velocidadIzquierda, VELOCIDAD_NORMAL);
    analogWrite(velocidadDerecha, VELOCIDAD_NORMAL);
  }
  else if(izquierda == LINEA && centro == LINEA && derecha == LINEA){ //Giro 90 grados
    recta(false);
    delay(100);
    noventagrados(false);
    parada();
    delay(500);
    recta(true);
    delay(300);
  }
  else if (izquierda == PASILLO && derecha == LINEA) { //desvio derecha
    recta(true);

    analogWrite(velocidadDerecha, VELOCIDAD_REDUCIDA);
  }
  else if(izquierda == LINEA && derecha == PASILLO){ //desvio izquierda
    recta(true);

    analogWrite(velocidadIzquierda, VELOCIDAD_REDUCIDA);
  }
  else{ //parada
    parada();
  }
}



void loop() {
  seguimientoLinea();
}
