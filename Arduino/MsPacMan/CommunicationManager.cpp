#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(38400);
	et_in.begin(details(recivMsg), &miBT);
	et_out.begin(details(sendMsg), &miBT);
}

void CommunicationManager::Sync(){
	sendMsg.ent_state = SYNC_ATTEMP;

	//bucle hasta recibir mensaje del servidor
	while(true){
		if(et_in.receiveData()){
			//ambos modulos están conectados
			Serial.println("SINCRONIZADOS");
			id = recivMsg.id;
			break;
		}
		et_out.sendData();
		Serial.println("intentnado sincronizar");
		
	}
}

void CommunicationManager::Update(){
    // if(ET.receiveData()){
    //     //[...]
	// 	start = true;
	// }
}

void CommunicationManager::SendMsg(ENTITY_STATE msg){
	sendMsg.ent_state = msg;
	et_out.sendData();
}

void CommunicationManager::WaitApproval(){
	while(true){
		if(et_in.receiveData() && recivMsg.ent_state == OK){
			break;
		}
	}
}

bool CommunicationManager::Start(){
	return start;
}