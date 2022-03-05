#include "MotorsController.h"
#include "LineTracker.h"
#include "GyroscopeController.h"
#include "CommunicationManager.h"
#include "DirectionController.h"

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
	nextDirection = directionController->GetNextDirection();
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


/**
 * @brief Método encargado de dirigir el robot cuando se va en linea recta.
 * Se encarga de leer la acción que tiene que realizar dada por el lineTracker.
 * Encargado de detectar cuando se tiene que empezar a girar.
 */
void MotorsController::FollowLine(){
	Action currentAction = lineTracker->GetCurrentAction();
 
	if(currentAction == Action::straight){ //recto
		Stright(true);
		analogWrite(leftSpeed, NORMAL_SPEED);
		analogWrite(rightSpeed, NORMAL_SPEED);
	}
	else if(currentAction == turn){ //Giro 90 grados
		if(nextDirection == TurningDirection::left){
			turningDirection = left;
			NinetyGegreeTurn();
		}
		else if (nextDirection == TurningDirection::right){
			turningDirection = right;
			NinetyGegreeTurn();
		}
		else{
			nextDirection = directionController->GetNextDirection();
			Stright(true);	
			analogWrite(leftSpeed, NORMAL_SPEED);
			analogWrite(rightSpeed, NORMAL_SPEED);
			delay(MINIMUM_EXIT_TURN_TIME);
			//TODO mientras estamos en este estado, tenemos que seguir la trayectoria perfecta
		}
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

/**
 * @brief Controla el giro, encargado de pararlo cuando es necesario 
 */
void MotorsController::Turning(){
	if(abs((perfectAngle % 360) - gyroscopeController->GetCurrentYaw()) < TURNING_DEGREES_BUFFER){
		turningDirection = (turningDirection == right) ? left: right;
		Turn();
		delay(100);
		turningDirection = none;

		Stop();
		delay(100);
		Stright(true);	
		digitalWrite(rightSpeed, NORMAL_SPEED);
		digitalWrite(leftSpeed, NORMAL_SPEED);
		state = turnExit;
		initialTime = millis();
		gyroscopeController->ResetYaw();
	}
}

/**
 * @brief Encargado de dirigir el robot los instantes posteriores a un giro
 * Encargado tambien de sobrecorregirlo para salir en la dirección correcta
 */
void MotorsController::TurnExit(){
	Stright(true);
	
	if(IsInLine()){
		if(millis() - initialTime > MINIMUM_EXIT_TURN_TIME)
		{
			communicationManager->SendMsg(MESSAGE::GREEN_LED);
			state = followingLine;
			analogWrite(leftSpeed, NORMAL_SPEED);
			analogWrite(rightSpeed, NORMAL_SPEED); 
			nextDirection = directionController->GetNextDirection(); 
		}
		else {
			//Si esta en linea pero aun no ha pasado suficiente tiempo mínimo, se
			//acelera más rápido para recuperar la velocidad de cricero 
			analogWrite(leftSpeed, INCREASED_SPEED);
			analogWrite(rightSpeed, INCREASED_SPEED);  
		}
	}
	else{
		TurningDirection overCorrectionDir = OverCorrectionDirection();

		if(overCorrectionDir == right){ //corregimos a la derecha  
			analogWrite(leftSpeed, INCREASED_SPEED);
			analogWrite(rightSpeed, REDUCED_SPEED/2);    
		}
		else if(overCorrectionDir == left){ //corregimos a la izquierda   
			analogWrite(leftSpeed, REDUCED_SPEED/2);
			analogWrite(rightSpeed, INCREASED_SPEED);  
		}
	}
}



/**
 * @brief Establece los motores para ir en linea recta
 * 
 * @param forwards true si se quiere de frente, false en caso de querer ir marcha atrás
 */
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
}



/**
 * @brief Para los motores 
 */
void MotorsController::Stop(){
	digitalWrite(forwardRight, LOW);
	digitalWrite(backwardRight, LOW);
	digitalWrite(forwardLeft, LOW);
	digitalWrite(backwardLeft, LOW);
}


/**
 * @brief Empieza a realizar un giro de 90 grados
 */
void MotorsController::NinetyGegreeTurn(){
	communicationManager->SendMsg(MESSAGE::RED_LED);
	Stright(false);	
	digitalWrite(rightSpeed, NORMAL_SPEED);
	digitalWrite(leftSpeed, NORMAL_SPEED);
	delay(75);
	Stop();
	delay(100);

	state = turning;
	communicationManager->SendMsg(MESSAGE::BLUE_LED);
	initialTurningYaw = gyroscopeController->GetAdverageYaw();
	
	if(turningDirection == TurningDirection::left)
		perfectAngle += 270;
	else if(turningDirection == TurningDirection::right)
		perfectAngle += 90;

	gyroscopeController->SetTargetYaw(perfectAngle);
	Turn();
}

/**
 * @brief Establece los motores en direcciones inversas para realizar un giro
 */
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






/**
 * @brief Revisa si el robor está orientado en la dirección correcta
 * 
 * @return true si está bien orientado
 * @return false si no está bien orientado
 */
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


/**
 * @brief Devuelve la dirección hacia la que el robot tiene que sobre-corregir tras realizar un giro de 90 grados * 
 * @return Dirección hacia la que se tiene que corregir 
 */
TurningDirection MotorsController::OverCorrectionDirection(){
	float aux = gyroscopeController->GetCurrentYaw(); 
	if(aux < (perfectAngle % 360))
		return right;
	else 
		return left;
}




void MotorsController::SetLineTracker(LineTracker* _lineTracker){
	lineTracker = _lineTracker;
}

void MotorsController::SetGyroscopeController(GyroscopeController* _gyroscopeController){
	gyroscopeController = _gyroscopeController;
}

void MotorsController::SetCommunicationManager(CommunicationManager* _communicationManager){
	communicationManager = _communicationManager;
}

void MotorsController::SetDirectionController(DirectionController* _directionController){
	directionController = _directionController;
}
