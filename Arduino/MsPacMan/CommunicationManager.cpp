#include "CommunicationManager.h"

CommunicationManager::CommunicationManager():miBT(3,9)
{
}

void CommunicationManager::Init(){
	miBT.begin(38400);
	ET.begin(details(myData), &miBT);
	start = false;
}

void CommunicationManager::Update(){
    if(ET.receiveData()){
        //[...]
		start = true;
	}
}

bool CommunicationManager::Start(){
	return start;
}