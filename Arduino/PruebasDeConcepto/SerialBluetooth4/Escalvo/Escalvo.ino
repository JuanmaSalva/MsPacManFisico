#include <SoftwareSerial.h>

SoftwareSerial miBT(3,9);

enum MESSAGE{
  SYNC_ATTEMP,
  SYNC,
  OK
};

MESSAGE msg;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciamos");
  miBT.begin(9600);

  while(true){
    if(miBT.available()){
      int val = miBT.read();
      msg = (MESSAGE)val;
      if(msg == SYNC_ATTEMP){
        Serial.println("SYNC_ATTEMP");        
      }
      
      miBT.flush();
      msg = SYNC;
      int i = 1;
      miBT.write(i);
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
