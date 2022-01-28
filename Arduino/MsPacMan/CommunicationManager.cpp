#include "CommunicationManager.h"


SoftwareSerial miBT(3,9);

CommunicationManager::CommunicationManager()
{
}

void CommunicationManager::Init(){

	miBT.begin(38400);
	ET.begin(details(myData), &miBT);
	

	myData.number = 100;
	//bucle hasta recibir mensaje del servidor
	while(true){
		ET.sendData();
		Serial.println("intentnado sincronizar");
		if(ET.receiveData()){
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