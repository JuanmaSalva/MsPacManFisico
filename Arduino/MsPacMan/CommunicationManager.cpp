#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(): miBT(3,9)
{
}

void CommunicationManager::Init(){

	miBT.begin(38400);
	ET.begin(details(myData), &miBT);
	

	myData.ent_state = SYNC_ATTEMP;

	//bucle hasta recibir mensaje del servidor
	while(true){
		ET.sendData();
		Serial.println("intentnado sincronizar");
		if(ET.receiveData() && myData.ent_state == SYNC){
			//ambos modulos están conectados
			Serial.println("SINCRONIZADOS");
			
			break;
		}
	}


	// miBT.begin(38400);
	// ET.begin(details(myData), &miBT);
	// start = false;
}

void CommunicationManager::Update(){
    // if(ET.receiveData()){
    //     //[...]
	// 	start = true;
	// }
}

bool CommunicationManager::Start(){
	return start;
}