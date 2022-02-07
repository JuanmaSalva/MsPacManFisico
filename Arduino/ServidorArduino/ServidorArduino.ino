#include "CommunicationManager.h"
#include "ServerManager.h"

CommunicationManager* communicationManager;
ServerManager* serverManager;

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


	serverManager = new ServerManager();
	serverManager->SyncToJava();

	analogWrite(red, 0);
	analogWrite(green, 0);
	analogWrite(blue, 255);

	// communicationManager = new CommunicationManager();
	// communicationManager->Init();
	// communicationManager->Sync();
	// communicationManager->WaitForRobotToInitialize();


	// analogWrite(red, 0);
	// analogWrite(green, 255);
	// analogWrite(blue, 0);
	
}

void loop() {
	if(Serial.available()){
		JAVA_MESSAGE msg = serverManager->ReadMsg();
		
		if(msg == PAC_MAN_NORTH){
			Serial.println("Norte");
		}
		else if(msg == PAC_MAN_EAST){
			Serial.println("East");	
		}
		else if(msg == PAC_MAN_SOUTH){
			Serial.println("South");	
		}
		else if(msg == PAC_MAN_WEST){
			Serial.println("West");	
		}
	}
}
