#include "MotorsController.h"
#include "LineTracker.h"

#define TURN_INTERSECCTION_MIN_TIME 250

MotorsController::MotorsController(){

}

void MotorsController::Init(){
	pinMode(rightSpeed, OUTPUT);
	pinMode(forwardRight, OUTPUT);
	pinMode(backwardRight, OUTPUT);
	pinMode(forwardLeft, OUTPUT);
	pinMode(backwardLeft, OUTPUT);
	pinMode(leftSpeed, OUTPUT);

	digitalWrite(forwardLeft, HIGH);
	digitalWrite(backwardLeft, LOW);
	digitalWrite(forwardRight, LOW);
	digitalWrite(backwardRight, HIGH);

	analogWrite(rightSpeed, NORMAL_SPEED);
	analogWrite(leftSpeed, NORMAL_SPEED);

	endIntersecctionTime = -TURN_INTERSECCTION_MIN_TIME;
	currentState = STRAIGHT;
}


void MotorsController::Update(){

	switch (currentState)
	{
	case STRAIGHT:
		Straight();
		break;
	case TURN:
		Turn();
		break;
	default:
		break;
	}
}



void MotorsController::Straight(){
	//aún podríamos estar en la zona de detección
	if(millis() - endIntersecctionTime < TURN_INTERSECCTION_MIN_TIME)
		return;

	if(lineTracker->IsBlackLine())
	{
		//TODO aquí deberemos sacar la dirección hacia la que queremos girar
		analogWrite(rightSpeed, INCREASED_SPEED);
		analogWrite(leftSpeed, REDUCED_SPEED);

		startIntersecctionTime = millis();
		currentState = TURN;
	}
}


void MotorsController::Turn(){
	//aún podríamos estar en la zona de detección
	if(millis() - startIntersecctionTime < TURN_INTERSECCTION_MIN_TIME)
		return;

	if(lineTracker->IsBlackLine())
	{
		//TODO aquí deberemos sacar la dirección hacia la que queremos girar
		analogWrite(rightSpeed, NORMAL_SPEED);
		analogWrite(leftSpeed, NORMAL_SPEED);

		endIntersecctionTime = millis();
		currentState = STRAIGHT;
	}
}

void MotorsController::SetLineTracker(LineTracker* _lineTracker){
	lineTracker = _lineTracker;
}