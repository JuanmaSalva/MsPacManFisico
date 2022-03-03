#include "MotorsController.h"
#include "LineTracker.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"

MotorsController::MotorsController(){
	state = followingLine;
	turningDirection = none;
	perfectAngle = 0;
}

void MotorsController::Init(){
	pinMode(rightSpeed, OUTPUT);
	pinMode(forwardRight, OUTPUT);
	pinMode(backwardRight, OUTPUT);
	pinMode(forwardLeft, OUTPUT);
	pinMode(backwardLeft, OUTPUT);
	pinMode(leftSpeed, OUTPUT);

	Stop();
	//Stright(true);
	//delay(50); //para empezar con velocidad

}


void MotorsController::Update(){
	switch (state)
	{
	case followingLine:
		FollowLine();
		break;
	case turning:
		Turning();
		break;
	case turnExit:
		TurnExit();
		break;
	default:
		break;
	}
}

void MotorsController::SetLineTracker(LineTracker* _lineTracker){
	lineTracker = _lineTracker;
}

void MotorsController::SetGyroscopeController(GyroscopeController* _gyroscopeController){
	gyroscopeController = _gyroscopeController;
}

void MotorsController::SetCommunicationManager(CommunicationManager* _communicationManager){
	communicationManager = _communicationManager;
	communicationManager->SendMsg(MESSAGE::RED_LED);
}

void MotorsController::Stright(bool forwards){
	if(forwards){
		digitalWrite(forwardLeft, LOW);
		digitalWrite(backwardLeft, HIGH);
		digitalWrite(forwardRight, HIGH);
		digitalWrite(backwardRight, LOW);
	}
	else {
		digitalWrite(forwardLeft, HIGH);
		digitalWrite(backwardLeft, LOW);
		digitalWrite(forwardRight, LOW);
		digitalWrite(backwardRight, HIGH);
	}
	
	digitalWrite(rightSpeed, REDUCED_SPEED);
	digitalWrite(leftSpeed, REDUCED_SPEED);
}

void MotorsController::Stop(){
	digitalWrite(forwardRight, LOW);
	digitalWrite(backwardRight, LOW);
	digitalWrite(forwardLeft, LOW);
	digitalWrite(backwardLeft, LOW);
}

void MotorsController::NinetyGegreeTurn(){
	Stright(false);
	delay(75);
	Stop();
	delay(100);
	state = turning;
	initialTurningYaw = gyroscopeController->GetAdverageYaw();
	perfectAngle += 270;
	gyroscopeController->SetTargetYaw(perfectAngle);
	Turn();
}

void MotorsController::Turn(){
	if(turningDirection == right){
		analogWrite(leftSpeed, NORMAL_SPEED);
		analogWrite(rightSpeed, NORMAL_SPEED);

		digitalWrite(forwardLeft, LOW);
		digitalWrite(backwardLeft, HIGH);
		digitalWrite(forwardRight, LOW);
		digitalWrite(backwardRight, HIGH);
	}
	else {
		analogWrite(leftSpeed, NORMAL_SPEED);
		analogWrite(rightSpeed, NORMAL_SPEED);   

		digitalWrite(forwardLeft, HIGH);
		digitalWrite(backwardLeft, LOW);
		digitalWrite(forwardRight, HIGH);
		digitalWrite(backwardRight, LOW);
	}
}






void MotorsController::FollowLine(){
	Action currentAction = lineTracker->GetCurrentAction();
 
	if(currentAction == straight){ //recto
		Stright(true);
		analogWrite(leftSpeed, NORMAL_SPEED);
		analogWrite(rightSpeed, NORMAL_SPEED);
	}
	else if(currentAction == leftTurn){ //Giro 90 grados
		turningDirection = left;
		NinetyGegreeTurn();
	}
	else if (currentAction == leftCorrection) { //desvio derecha
		Stright(true);
		analogWrite(leftSpeed, REDUCED_SPEED);
		analogWrite(rightSpeed, INCREASED_SPEED);
	}
	else if(currentAction == rightCorrection){ //desvio izquierda
		Stright(true);
		analogWrite(leftSpeed, INCREASED_SPEED);
		analogWrite(rightSpeed, REDUCED_SPEED);
	}
	else if (currentAction == lost){ //parada
		Stop();
	}
}

void MotorsController::Turning(){
	if(abs((perfectAngle % 360) - gyroscopeController->GetCurrentYaw()) < TURNING_DEGREES_BUFFER){
		turningDirection = (turningDirection == right) ? left: right;
		Turn();
		delay(100);
		turningDirection = none;

		Stop();
		delay(100);
		Stright(true);
		state = turnExit;
		initialTime = millis();
		gyroscopeController->ResetYaw();
	}
}

bool MotorsController::IsInLine(){
	int angleModule = perfectAngle % 360;

	if(angleModule == 0){
		if(gyroscopeController->GetCurrentYaw() < TURNING_DEGREES_BUFFER ||
		gyroscopeController->GetCurrentYaw() > 360 - TURNING_DEGREES_BUFFER)
			return true;
		else 
			return false;
	}
	else
		return (abs(angleModule - gyroscopeController->GetCurrentYaw()) < TURNING_DEGREES_BUFFER);	
}

TurningDirection MotorsController::OverCorrectionDirection(){
	float aux = gyroscopeController->GetCurrentYaw(); 
	if(aux < (perfectAngle % 360))
		return right;
	else 
		return left;
}

void MotorsController::TurnExit(){
	Stright(true);
	
	if(IsInLine()){
		if(millis() - initialTime > MINIMUM_EXIT_TURN_TIME)
		{
			state = followingLine;
			analogWrite(leftSpeed, NORMAL_SPEED);
			analogWrite(rightSpeed, NORMAL_SPEED);  
		}
		else {
			analogWrite(leftSpeed, INCREASED_SPEED);
			analogWrite(rightSpeed, INCREASED_SPEED);  
		}
	}
	else{
		TurningDirection overCorrectionDir = OverCorrectionDirection();

		if(overCorrectionDir == right){ //corregimos a la derecha  
			analogWrite(leftSpeed, INCREASED_SPEED);
			analogWrite(rightSpeed, NORMAL_SPEED);    
		}
		else if(overCorrectionDir == left){ //corregimos a la izquierda   
			analogWrite(leftSpeed, NORMAL_SPEED);
			analogWrite(rightSpeed, INCREASED_SPEED);  
		}
	}
}
