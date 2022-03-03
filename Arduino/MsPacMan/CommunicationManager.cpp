#include "CommunicationManager.h"
#include "DirectionController.h"

CommunicationManager::CommunicationManager(): miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600);
}

void CommunicationManager::Sync(){
	Serial.println("intentnado sincronizar");
	

	while(true){
		if(miBT.available()){
			MESSAGE msg = ReadMsg();
			if(msg == SYNC_ATTEMP){
				SendMsg(SYNC);
				Serial.println("Sincronizados");
				break;
			}
		}
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

void CommunicationManager::WaitApproval(){
	while(true){
		if(miBT.available()){
			MESSAGE msg = ReadMsg();
			if(msg == OK){
				return;
			}
		}
		delay(5);
	}
}


void CommunicationManager::Update(){
	/*if(miBT.available()){
		MESSAGE msg = ReadMsg();
		if(msg == OK){
			return;
		}
	}*/
}

void CommunicationManager::SetDirectionController(DirectionController* d){
	directionController = d;
}