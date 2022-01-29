#include "CommunicationManager.h"

CommunicationManager* communicationManager;

void setup() {
	Serial.begin(9600);
	while(!Serial);

	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();
	//communicationManager->WaitForRobotToInitialize();
}

void loop() {


	// if(Serial.available() > 0){
	// 	byte incomingByte = Serial.read();

	// 	if(incomingByte != -1){
	// 		analogWrite(rojo, 0);
	// 		analogWrite(verde, 255);
	// 		analogWrite(azul, 0);  
			
			// myData.number = 2;
			// ET.sendData();
	// 	}
	// }
}
