#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600);
	et_in.begin(details(recivMsg), &miBT);
	et_out.begin(details(sendMsg), &miBT);
}

void CommunicationManager::Sync(){
	Serial.println("intentnado sincronizar");
	

	while(true){
		if(miBT.available()){
			Serial.println("Hay putos datos de mierda hostia ya");
		}
		// if(et_in.receiveData()){
		// 	Serial.println("Peticion");
		// 	break;
		//}		
	}
}

void CommunicationManager::Update(){
    // if(ET.receiveData()){
    //     //[...]
	// 	start = true;
	// }
}

// void CommunicationManager::SendMsg(ENTITY_STATE msg){
// 	// sendMsg.ent_state = msg;
// 	// et_out.sendData();
// }

void CommunicationManager::WaitApproval(){
	// while(true){
	// 	if(et_in.receiveData() && recivMsg.ent_state == OK){
	// 		break;
	// 	}
	// }
}

bool CommunicationManager::Start(){
	return start;
}