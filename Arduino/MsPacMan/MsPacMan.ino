#include "LineTracker.h"
#include "MotorsController.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"

LineTracker* lineTracker;
MotorsController* motorsController;
GyroscopeController* gyroscopeController;
CommunicationManager* communicationManager;

void setup() {
	Serial.begin(9600);
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();

	// lineTracker = new LineTracker();
	// lineTracker->Init();
	// communicationManager->SendMsg(LINE_TRACKER_INITIALIZED);
	// communicationManager->WaitApproval();

	// gyroscopeController = new GyroscopeController();
	// gyroscopeController->Init();
	// communicationManager->SendMsg(GYROSCOPE_INITIALIZED);
	// communicationManager->WaitApproval();

	// motorsController = new MotorsController();
	// motorsController->Init();
	// motorsController->SetLineTracker(lineTracker);
	// motorsController->SetGyroscopeController(gyroscopeController);
	// communicationManager->SendMsg(MOTORS_INITIALIZES);
	// communicationManager->WaitApproval();
}


void loop() {
	// if(communicationManager->Start()){
	// 	lineTracker->Update();
	// 	gyroscopeController->Update();
	// 	motorsController->Update();
	// 	//motorsController->Stright(true);

	// }
	// Serial.println("Loop");
	// communicationManager->Update();
	
}
