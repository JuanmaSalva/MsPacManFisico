#include <SoftwareSerial.h>

SoftwareSerial miBT(5,6);

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializamos");
  miBT.begin(9600);


  while(true){
    if(miBT.available()){
      Serial.println("Sincronizados");
      break;
    }
    miBT.flush();
    miBT.write('a');
    miBT.flush();
    delay(100);

  }
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());  
}

void loop(){
}
