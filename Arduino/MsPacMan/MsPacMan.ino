#include "LineTracker.h"
#include "MotorsController.h"
//#include "GyroscopeController.h"

LineTracker* lineTracker;
MotorsController* motorsController;
//GyroscopeController* gyroscopeController;

void setup() {
  lineTracker = new LineTracker();
  lineTracker->Init();

  motorsController = new MotorsController();
  motorsController->Init();
  motorsController->SetLineTracker(lineTracker);

  //gyroscopeController = new GyroscopeController();
  //gyroscopeController->Init();

  Serial.begin(9600);
}


void loop() {
  lineTracker->Update();
  motorsController->Update();
  //gyroscopeController->Update();
}
