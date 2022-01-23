#include "LineTracker.h"
#include "MotorsController.h"
#include "GyroscopeController.h"

#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

LineTracker* lineTracker;
MotorsController* motorsController;
GyroscopeController* gyroscopeController;

SoftwareSerial miBT(3,9);

SoftEasyTransfer ET;

struct RECIEVE_DATA_STRUCTURE{
	int8_t id;
	int8_t number;
};


RECIEVE_DATA_STRUCTURE myData;


void setup() {
	/*lineTracker = new LineTracker();
	lineTracker->Init();

	gyroscopeController = new GyroscopeController();
	gyroscopeController->Init();*/

	motorsController = new MotorsController();
	motorsController->Init();
	//motorsController->SetLineTracker(lineTracker);
	//motorsController->SetGyroscopeController(gyroscopeController);


	//Serial.begin(9600);

	miBT.begin(38400);
	ET.begin(details(myData), &miBT);
  

}


void loop() {
	/*lineTracker->Update();
	gyroscopeController->Update();
	motorsController->Update();*/

  	if(ET.receiveData() && myData.number == 2){
		  motorsController->Stop();
	}
}
