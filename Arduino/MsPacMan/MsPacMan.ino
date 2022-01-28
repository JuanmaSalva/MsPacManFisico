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

	
	// lineTracker = new LineTracker();
	// lineTracker->Init();

	// gyroscopeController = new GyroscopeController();
	// gyroscopeController->Init();

	// motorsController = new MotorsController();
	// motorsController->Init();
	//motorsController->SetLineTracker(lineTracker);
	//motorsController->SetGyroscopeController(gyroscopeController);




	// motorsController->SetLineTracker(lineTracker);
	// motorsController->SetGyroscopeController(gyroscopeController);


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
