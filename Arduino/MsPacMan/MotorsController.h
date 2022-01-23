#pragma once
#include <Arduino.h>

#include "LineTracker.h"
#include "GyroscopeController.h"


#define NORMAL_SPEED 150
#define REDUCED_SPEED 95
#define INCREASED_SPEED 175

#define TURNING_DEGREES_BUFFER 2.0
#define MINIMUM_EXIT_TURN_TIME 200

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
	long initialTime;
	int perfectAngle; //el ángluo que deberia llevar el robot en relacion a la posicion de inicio


	void NinetyGegreeTurn();

	void FollowLine();
	void Turning();
	void TurnExit();
	
	void Turn();
	bool IsInLine();
	TurningDirection OverCorrectionDirection();

public:
	void Stright(bool forwards); //Provisional para probar el bletooh, volver a provado luego
	void Stop();

	MotorsController();
	void Init();
	void Update();

	void SetLineTracker(LineTracker* _lineTracker);
	void SetGyroscopeController(GyroscopeController* _gyroscopeController);
};