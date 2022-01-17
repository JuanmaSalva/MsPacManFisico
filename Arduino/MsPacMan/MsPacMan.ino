#include "LineTracker.h"
#include "MotorsController.h"
#include "GyroscopeController.h"

LineTracker* lineTracker;
MotorsController* motorsController;
GyroscopeController* gyroscopeController;

void setup() {
  lineTracker = new LineTracker();
  lineTracker->Init();

  gyroscopeController = new GyroscopeController();
  gyroscopeController->Init();

  motorsController = new MotorsController();
  motorsController->Init();
  motorsController->SetLineTracker(lineTracker);
  motorsController->SetGyroscopeController(gyroscopeController);


  Serial.begin(9600);
}


void loop() {
  lineTracker->Update();
  gyroscopeController->Update();
  motorsController->Update();
}
