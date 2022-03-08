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

	//Communication Manager
	if(!DEBUG){
		communicationManager = new CommunicationManager();
		communicationManager->Init();
		communicationManager->Sync();
	}

	//Line tracker
	lineTracker = new LineTracker();
	lineTracker->Init();
	if(!DEBUG){
		communicationManager->SendMsg(LINE_TRACKER_INITIALIZED);
		communicationManager->WaitApproval();
	}

	//Gyroscope Controller
	gyroscopeController = new GyroscopeController();
	gyroscopeController->Init();
	if(!DEBUG){
		communicationManager->SendMsg(GYROSCOPE_INITIALIZED);
		communicationManager->WaitApproval();
	}

	//Direccion Controller
	directionController = new DirectionController();
	
	//Motors Controller
	motorsController = new MotorsController();
	motorsController->SetLineTracker(lineTracker);
	motorsController->SetGyroscopeController(gyroscopeController);
	motorsController->SetDirectionController(directionController);
	motorsController->Init();
	if(!DEBUG){
		communicationManager->SendMsg(MOTORS_INITIALIZED);
		communicationManager->WaitApproval();
		motorsController->SetCommunicationManager(communicationManager);
	}


	if(!DEBUG){
		communicationManager->SetDirectionController(directionController);
		communicationManager->SendMsg(DIRECCTION_INITIALIZED);
		communicationManager->WaitApproval();
		communicationManager->SendMsg(MESSAGE::GREEN_LED);
	}
}


void loop() {
	lineTracker->Update();
	gyroscopeController->Update();
	motorsController->Update();

	communicationManager->Update();	
}
