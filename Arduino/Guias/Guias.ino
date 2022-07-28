#include "MotorsController.h"
#include "LineTracker.h"
#include "DirectionController.h"
#include "CommunicationManager.h"

LineTracker* lineTracker;
MotorsController* motorsController;
DirectionController* directionController;
CommunicationManager* communicationManager;

void setup() {
    Serial.begin(9600);

	//Communication Manager
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();

    lineTracker = new LineTracker();
    lineTracker->Init();
	communicationManager->SendMsg(LINE_TRACKER_INITIALIZED);
	communicationManager->WaitApproval();

    directionController = new DirectionController();

    motorsController = new MotorsController();
    motorsController->Init();
    motorsController->SetLineTracker(lineTracker);
    motorsController->SetDirectionController(directionController);
	communicationManager->SendMsg(MOTORS_INITIALIZED);
	communicationManager->WaitApproval();

	communicationManager->SendMsg(DIRECCTION_INITIALIZED);
	communicationManager->WaitApproval();

	communicationManager->SendMsg(MESSAGE::GREEN_LED);
}



void loop() {
    lineTracker->Update();
    motorsController->Update();
}