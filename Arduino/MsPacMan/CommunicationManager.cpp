#include "CommunicationManager.h"

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
	int val = (int)msg;
	miBT.write(val);
	miBT.flush();
}

MESSAGE CommunicationManager::ReadMsg(){
	int val = miBT.read();
	MESSAGE msg = (MESSAGE)val;
	return msg;
}


void CommunicationManager::Update(){
}
