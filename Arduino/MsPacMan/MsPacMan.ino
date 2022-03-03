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

bool DEBUG = true;

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
		communicationManager->SendMsg(MOTORS_INITIALIZES);
		communicationManager->WaitApproval();
		Serial.println("\n\nEl server sabe que hemos terminado");
	}


	directionController = new DirectionController();
	directionController->SetMotorsController(motorsController);
	communicationManager->SetDirectionController(directionController);
}


void loop() {
	lineTracker->Update();
	gyroscopeController->Update();
	motorsController->Update();

	communicationManager->Update();	
}
