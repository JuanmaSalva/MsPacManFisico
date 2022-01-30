#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(5,6)
{
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
}

void CommunicationManager::Init(){
	miBT.begin(9600);
	et_in.begin(details(recvMsg), &miBT);
	et_out.begin(details(sendMsg), &miBT);

	analogWrite(red, 255);
	analogWrite(green, 0);
	analogWrite(blue, 0);
}


void CommunicationManager::Sync(){
	while(true){
		Serial.println("Intentando sincronizar");
		sendMsg.ent_state = SYNC_ATTEMP;
		et_out.sendData();
		delay(100);	
	}
}

void CommunicationManager::WaitForRobotToInitialize(){
	// while (true)
	// {
	// 	Serial.println("Esperando sensores linea");
	// 	if(et_in.receiveData() && recvMsg.ent_state == LINE_TRACKER_INITIALIZED){
	// 		Serial.println("\nSensores de linea inicializados");
	// 		sendMsg.ent_state = OK;
	// 		et_out.sendData();
	// 		break;
	// 	}
	// }
	// while(true){
	// 	Serial.println("Esperando goroscopio");
	// 	if(et_in.receiveData() && recvMsg.ent_state == GYROSCOPE_INITIALIZED){
	// 		Serial.println("\nGiroscopio inicializados");
	// 		sendMsg.ent_state = OK;
	// 		et_out.sendData();
	// 		break;
	// 	}
	// }
	// while(true){
	// 	Serial.println("Esperando motores");
	// 	if(et_in.receiveData() && recvMsg.ent_state == MOTORS_INITIALIZES){
	// 		Serial.println("\nMotores inicializados");
	// 		sendMsg.ent_state = OK;
	// 		et_out.sendData();
	// 		break;
	// 	}
	// }
}