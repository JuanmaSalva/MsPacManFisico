#include "CommunicationManager.h"

CommunicationManager::CommunicationManager():miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(38400);
	ET.begin(details(myData), &miBT);
}

void CommunicationManager::Update(){
    if(ET.receiveData() && myData.number == 2){
        //[...]
	}
}