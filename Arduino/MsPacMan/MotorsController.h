#pragma once
#include <Arduino.h>
#include "LineTracker.h"


#define NORMAL_SPEED 200
#define REDUCED_SPEED 60

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

    void Stright(bool forwards);
    void Stop();
    void NinetyGegreeTurn(bool rightTurn);
    void OneEightyGegreeTurn();

public:
    MotorsController();
    void Init();
    void Update();

    void SetLineTracker(LineTracker* _lineTracker);
};