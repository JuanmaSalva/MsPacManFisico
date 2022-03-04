#include "ServerManager.h"

ServerManager::ServerManager(){
}

/**
 * @brief Sincroniza el servidor arduino con el programa en Java donde corre
 * el simulador MsPacMan 
 */
void ServerManager::SyncToJava(){
    while(true){
		if(Serial.available()){
			JAVA_MESSAGE msg = ReadMsg();
            if(msg == JAVA_SYNC_ATTEMP){
				SendMsg(JAVA_SYNC);
				break;
			}
		}

		delay(5);
	}
}

/**
 * @brief Envia un mensaje al programa de Java
 * 
 * @param msg Mensaje a enviar
 */
void ServerManager::SendMsg(JAVA_MESSAGE msg){
    Serial.flush();
    Serial.write((int)msg);
    Serial.flush();
}

/**
 * @brief Lee un mensaje que viene desde el programa en java
 * 
 * @return Mensaje recibido
 */
JAVA_MESSAGE ServerManager::ReadMsg(){
    JAVA_MESSAGE msg = (JAVA_MESSAGE)Serial.read();
    return msg;
}