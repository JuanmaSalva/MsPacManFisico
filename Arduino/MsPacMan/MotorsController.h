#pragma once
#include <Arduino.h>

#include "LineTracker.h"
#include "GyroscopeController.h"


#define NORMAL_SPEED 150
#define REDUCED_SPEED 125
#define INCREASED_SPEED 175

#define TURN_EXIT_TIME 500

enum State{
    followingLine,
    turning,
    turnExit
};

enum TurningDirection{
    left,
    right,
    none
};

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

    State state;
    float initialTurningYaw;
    TurningDirection turningDirection;
    unsigned long initialTime;

    void Stright(bool forwards);
    void Stop();

    void NinetyGegreeTurn();

    void FollowLine();
    void Turning();
    void TurnExit();
    
    void Turn();

public:
    MotorsController();
    void Init();
    void Update();

    void SetLineTracker(LineTracker* _lineTracker);
    void SetGyroscopeController(GyroscopeController* _gyroscopeController);
};