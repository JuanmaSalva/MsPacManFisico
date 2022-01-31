#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(5,6)
{
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
}

void CommunicationManager::Init(){
	miBT.begin(9600);

	analogWrite(red, 255);
	analogWrite(green, 0);
	analogWrite(blue, 0);
}


void CommunicationManager::Sync(){
	while(true){
		if(miBT.available()){
			MESSAGE msg = ReadMsg();
			if(msg == SYNC){
				analogWrite(red, 0);
				analogWrite(green, 255);
				analogWrite(blue, 0);		
				break;		
			}
		}

		SendMsg(SYNC_ATTEMP);

		delay(50);
	}
}

void CommunicationManager::SendMsg(MESSAGE msg){
	miBT.flush();
	int val = (int)msg;
	miBT.write(val);
	miBT.flush();
}

MESSAGE CommunicationManager::ReadMsg(){
	int val = miBT.read();
	MESSAGE msg = (MESSAGE)val;
	return msg;
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