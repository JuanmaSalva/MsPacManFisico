#include "LineTracker.h"
#include "MotorsController.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"

LineTracker* lineTracker;
MotorsController* motorsController;
GyroscopeController* gyroscopeController;
CommunicationManager* communicationManager;

void setup() {
	lineTracker = new LineTracker();
	lineTracker->Init();

	gyroscopeController = new GyroscopeController();
	gyroscopeController->Init();

	motorsController = new MotorsController();
	motorsController->Init();
	//motorsController->SetLineTracker(lineTracker);
	//motorsController->SetGyroscopeController(gyroscopeController);


	// Serial.begin(9600);

	// miBT.begin(38400);
	// ET.begin(details(myData), &miBT);
	

	// myData.number = 100;
	// //bucle hasta recibir mensaje del servidor
	// while(true){
	// 	ET.sendData();
	// 	Serial.println("intentnado sincronizar");
	// 	if(ET.receiveData()){
	// 		//ambos modulos están conectados
	// 		motorsController->Stright(true);
	// 		Serial.println("SINCRONIZADOS");
			
	// 		break;
	// 	}
	// }
	motorsController->SetLineTracker(lineTracker);
	motorsController->SetGyroscopeController(gyroscopeController);

	communicationManager = new CommunicationManager();
	communicationManager->Init();

	Serial.begin(9600);
}


void loop() {
	if(communicationManager->Start()){
		lineTracker->Update();
		gyroscopeController->Update();
		motorsController->Update();
		//motorsController->Stright(true);

	}
	Serial.println("Loop");
	communicationManager->Update();
	
}
