#include "CommunicationManager.h"
#include "DirectionController.h"

CommunicationManager::CommunicationManager(): miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(9600);
}

/**
 * @brief Sincroniza el robot con el servidor arduino 
 */
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

/**
 * @brief Envía un mensaje al servidor arduino
 * 
 * @param msg Mensaje a enviar
 */
void CommunicationManager::SendMsg(MESSAGE msg){
	miBT.flush();
	miBT.write((int)msg);
	miBT.flush();
}

/**
 * @brief Lee un mensaje del servidor arduino
 * 
 * @return Mensaje leido
 */
MESSAGE CommunicationManager::ReadMsg(){
	MESSAGE msg = (MESSAGE)miBT.read();
	return msg;
}

/**
 * @brief Espera a un mensaje de confirmación indicando que el servidor arduino
 * ha recibido correctamente un mensaje 
 */
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