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
	
	WaitForMsg(MOTORS_INITIALIZES);
	Serial.println("Motores Inicializados");
}

void CommunicationManager::WaitForMsg(MESSAGE msg){
	while (true)
	{
		if(miBT.available()){
			MESSAGE msg = ReadMsg();
			if(msg == msg){
				SendMsg(OK);
				break;
			}
		}
		delay(5);
	}
}