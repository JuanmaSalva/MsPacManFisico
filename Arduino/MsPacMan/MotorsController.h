#pragma once
#include <Arduino.h>

#include "LineTracker.h"
#include "GyroscopeController.h"


#define NORMAL_SPEED 150
#define REDUCED_SPEED 125
#define INCREASED_SPEED 175

#define ROTATION_TIME 350

class MotorsController{
private:
    int rightSpeed = 11;
    int forwardRight = A0;
    int backwardRight = A1;
    int forwardLeft = A2;
    int backwardLeft = A3;
    int leftSpeed = 10;

    LineTracker* lineTracker;
    GyroscopeController* gyroscopeController;

    bool turning = false;
    float initialTurningYaw;

    void Stright(bool forwards);
    void Stop();
    void NinetyGegreeTurn(bool rightTurn);
    void OneEightyGegreeTurn();
    void Turn();

public:
    MotorsController();
    void Init();
    void Update();

    void SetLineTracker(LineTracker* _lineTracker);
    void SetGyroscopeController(GyroscopeController* _gyroscopeController);
};