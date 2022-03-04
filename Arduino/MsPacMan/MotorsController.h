#pragma once
#include <Arduino.h>
#include "TurningDirecction.h"

class LineTracker;
class GyroscopeController;
class CommunicationManager;

#define NORMAL_SPEED 150
#define REDUCED_SPEED 95
#define INCREASED_SPEED 180

#define TURNING_DEGREES_BUFFER 2.0
#define MINIMUM_EXIT_TURN_TIME 250

enum State{
	followingLine,
	turning,
	turnExit
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
	CommunicationManager* communicationManager = nullptr;

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
	void SetCommunicationManager(CommunicationManager* _communicationManager);
};