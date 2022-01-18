#include "MotorsController.h"
#include "GyroscopeController.h"

MotorsController::MotorsController(){
    state = followingLine;
    turningDirection = none;
}

void MotorsController::Init(){
    pinMode(rightSpeed, OUTPUT);
    pinMode(forwardRight, OUTPUT);
    pinMode(backwardRight, OUTPUT);
    pinMode(forwardLeft, OUTPUT);
    pinMode(backwardLeft, OUTPUT);
    pinMode(leftSpeed, OUTPUT);

    digitalWrite(rightSpeed, NORMAL_SPEED);
    digitalWrite(leftSpeed, NORMAL_SPEED);
    delay(50); //para empezar con velocidad
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

void MotorsController::Stop(){
    digitalWrite(forwardRight, LOW);
    digitalWrite(backwardRight, LOW);
    digitalWrite(forwardLeft, LOW);
    digitalWrite(backwardLeft, LOW);
}

void MotorsController::NinetyGegreeTurn(){
    Stright(false);
    delay(100);
    Stop();
    delay(100);
    state = turning;
    initialTurningYaw = gyroscopeController->GetAdverageYaw();
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
    if(abs(initialTurningYaw - gyroscopeController->GetCurrentYaw()) > 90.0f){

        turningDirection = (turningDirection == right) ? left: right;
        Turn();
        delay(100);
        turningDirection = none;

        Stop();
        delay(100);
        Stright(true);
        state = turnExit;
        delay(300);
        gyroscopeController->ResetYaw();
    }
}

void MotorsController::TurnExit(){

}