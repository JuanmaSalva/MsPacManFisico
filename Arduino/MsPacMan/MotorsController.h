#pragma once
#include <Arduino.h>
#include "TurningDirecction.h"

class LineTracker;
class GyroscopeController;
class CommunicationManager;
class DirectionController;

#define REDUCED_SPEED 70.0
#define NORMAL_SPEED 100.0
#define INCREASED_SPEED 130.0


#define TURNING_DEGREES_BUFFER 1.5
#define STRIGHT_DEGREES_BUFFER 12.5
#define MINIMUM_EXIT_TURN_TIME 300.0

#define FULL_BRAKE_TIME 70.0
#define MIN_TIME_FOR_FULL_BRAKE 750.0

enum State{
	followingLine,
	turning,
	turnExit,
	followGyroscope,
	braking
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
	DirectionController* directionController;

	State state;
	float initialTurningYaw;
	TurningDirection turningDirection;
	TurningDirection nextDirection = TurningDirection::none;
	long initialTime;
	int perfectAngle; //el ángluo que deberia llevar el robot en relacion a la posicion de inicio


	void NinetyGegreeTurn();

	void FollowLine();
	void Turning();
	void TurnExit();
	void FollowGyroscope();
	void Braking();
	
	void Turn();
	TurningDirection OverCorrectionDirection();
	void AplyOverCorrection(TurningDirection dir);
	float CurrentDirectionOffset();
	int GetBrakingTime();

public:
	void Stright(bool forwards); //Provisional para probar el bletooh, volver a provado luego
	void Stop();

	MotorsController();
	void Init();
	void Start();
	void Update();

	void SetLineTracker(LineTracker* _lineTracker);
	void SetGyroscopeController(GyroscopeController* _gyroscopeController);
	void SetCommunicationManager(CommunicationManager* _communicationManager);
	void SetDirectionController(DirectionController* _directionController);
};