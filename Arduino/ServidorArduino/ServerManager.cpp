#include "ServerManager.h"

ServerManager::ServerManager(){

}

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

void ServerManager::SendMsg(JAVA_MESSAGE msg){
    Serial.flush();
    Serial.write((int)msg);
    Serial.flush();
}

JAVA_MESSAGE ServerManager::ReadMsg(){
    JAVA_MESSAGE msg = (JAVA_MESSAGE)Serial.read();
    return msg;
}