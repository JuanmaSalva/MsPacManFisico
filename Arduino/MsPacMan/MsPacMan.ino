#include "LineTracker.h"
#include "MotorsController.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"
#include "DirectionController.h"

LineTracker* lineTracker;
MotorsController* motorsController;
GyroscopeController* gyroscopeController;
CommunicationManager* communicationManager;
DirectionController* directionController;

bool DEBUG = false;

void setup() {
	Serial.begin(9600);
	Serial.println("Inicializamos");

	if(!DEBUG){
		communicationManager = new CommunicationManager();
		communicationManager->Init();
		communicationManager->Sync();
	}

	lineTracker = new LineTracker();
	lineTracker->Init();
	if(!DEBUG){
		communicationManager->SendMsg(LINE_TRACKER_INITIALIZED);
		communicationManager->WaitApproval();
		}

	gyroscopeController = new GyroscopeController();
	gyroscopeController->Init();
	if(!DEBUG){
		communicationManager->SendMsg(GYROSCOPE_INITIALIZED);
		communicationManager->WaitApproval();
	}

	motorsController = new MotorsController();
	motorsController->Init();
	motorsController->SetLineTracker(lineTracker);
	motorsController->SetGyroscopeController(gyroscopeController);
	if(!DEBUG){
		communicationManager->SendMsg(MOTORS_INITIALIZED);
		communicationManager->WaitApproval();
		motorsController->SetCommunicationManager(communicationManager);
	}


	directionController = new DirectionController();
	directionController->SetMotorsController(motorsController);
	if(!DEBUG){
		communicationManager->SetDirectionController(directionController);
		communicationManager->SendMsg(DIRECCTION_INITIALIZED);
		communicationManager->WaitApproval();
		communicationManager->SendMsg(MESSAGE::GREEN_LED);
	}

	//Serial.println("\n\nEl server sabe que hemos terminado");
}


void loop() {
	lineTracker->Update();
	gyroscopeController->Update();
	motorsController->Update();

	communicationManager->Update();	
}
