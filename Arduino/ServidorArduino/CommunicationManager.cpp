#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(5,6)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600);
}


void CommunicationManager::Sync(){
	while(true){
		if(miBT.available()){
			MESSAGE msg = ReadMsg();
			if(msg == SYNC){	
				break;		
			}
		}

		SendMsg(SYNC_ATTEMP);

		delay(50);
	}
}

void CommunicationManager::SendMsg(MESSAGE msg){
	miBT.flush();
	miBT.write((int)msg);
	miBT.flush();
}

MESSAGE CommunicationManager::ReadMsg(){
	MESSAGE msg = (MESSAGE)miBT.read();
	return msg;
}

void CommunicationManager::WaitForRobotToInitialize(){
	WaitForMsg(LINE_TRACKER_INITIALIZED);
	Serial.println("Sensores Linea Inicializados");
	
	WaitForMsg(GYROSCOPE_INITIALIZED);
	Serial.println("Giroscopio Inicializados");
	
	WaitForMsg(MOTORS_INITIALIZED);
	Serial.println("Motores Inicializados");

	WaitForMsg(DIRECCTION_INITIALIZED);
	Serial.println("Motores Inicializados");
}

void CommunicationManager::WaitForMsg(MESSAGE msg){
	while (true)
	{
		if(miBT.available()){
			MESSAGE msgAux = ReadMsg();
			if(msgAux == msg){
				SendMsg(OK);
				break;
			}
		}
		delay(5);
	}
}

bool CommunicationManager::MsgAvailable(){
	return miBT.available();
}