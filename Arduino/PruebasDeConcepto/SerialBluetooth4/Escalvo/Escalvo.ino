//#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

SoftwareSerial miBT(3,9);



/*SoftEasyTransfer ET;

struct RECIEVE_DATA_STRUCTURE{
  int8_t id;
  int8_t number;
};


RECIEVE_DATA_STRUCTURE myData;
*/
void setup() {
  Serial.begin(9600);
  Serial.println("Iniciamos");
  miBT.begin(9600);
  //ET.begin(details(myData), &miBT);
  
}

void configuracion(){
  if(miBT.available())
    Serial.write(miBT.read());

  if(Serial.available())
    miBT.write(Serial.read());  
}

void loop(){
  if(miBT.available()){
    Serial.println(miBT.read());
    miBT.flush();
    miBT.print('b');
    miBT.flush();
  }
}
