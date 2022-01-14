#include "LineTracker.h"
#include "MotorsController.h"

LineTracker* lineTracker;
MotorsController* motorsController;

void setup() {
  lineTracker = new LineTracker();
  lineTracker->Init();

  motorsController = new MotorsController();
  motorsController->Init();
  motorsController->SetLineTracker(lineTracker);

  Serial.begin(9600);
}


void loop() {
  lineTracker->Update();
  motorsController->Update();
}
