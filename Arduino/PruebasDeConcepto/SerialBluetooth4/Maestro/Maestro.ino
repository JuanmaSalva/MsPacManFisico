#include <SoftwareSerial.h>

SoftwareSerial miBT(5,6);

enum MESSAGE{
  SYNC_ATTEMP,
  SYNC,
  OK
};

MESSAGE msg;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializamos");
  miBT.begin(9600);


  while(true){
    if(miBT.available()){
      int val = miBT.read();
      Serial.println("Sincronizados" + val);
      break;
    }
    miBT.flush();
    msg = SYNC_ATTEMP;
    int i = 0;
    miBT.write(i);
    miBT.flush();
    delay(5);
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
