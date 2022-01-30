#include <SoftwareSerial.h>

SoftwareSerial miBT(3,9);

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciamos");
  miBT.begin(9600);

  while(true){
    if(miBT.available()){
      Serial.println("Sincronizados");
      miBT.flush();
      miBT.write('b');
      miBT.flush();
      break;
    }
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
