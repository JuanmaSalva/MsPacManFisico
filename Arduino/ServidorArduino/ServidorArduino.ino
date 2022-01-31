#include "CommunicationManager.h"

CommunicationManager* communicationManager;

int red = 9;
int green = 10;
int blue = 11;

void setup() {
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Inicializamos");
	
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	
	analogWrite(red, 255);
	analogWrite(green, 0);
	analogWrite(blue, 0);

	// communicationManager = new CommunicationManager();
	// communicationManager->Init();
	// communicationManager->Sync();
	// communicationManager->WaitForRobotToInitialize();

	while(true){
		if(Serial.available()){
			int aux = Serial.read();
			if(aux == 20){
				Serial.flush();
				int val = 10;
				Serial.write(val);
				Serial.flush();
				break;
			}
		}

		delay(5);
	}


	analogWrite(red, 0);
	analogWrite(green, 255);
	analogWrite(blue, 0);	
}

void loop() {


	// if(Serial.available()){
	// 	byte incomingByte = Serial.read();
	// 	Serial.println("ByteRecibido");
	// }
}
