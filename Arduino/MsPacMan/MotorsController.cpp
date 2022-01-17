#include "MotorsController.h"
#include "GyroscopeController.h"

MotorsController::MotorsController(){

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
    if(turning){
        Turn();
        return;
    }

    Action currentAction = lineTracker->GetCurrentAction();
 
    if(currentAction == stright){ //recto
        Stright(true);
        analogWrite(leftSpeed, NORMAL_SPEED);
        analogWrite(rightSpeed, NORMAL_SPEED);
    }
    else if(currentAction == leftTurn){ //Giro 90 grados
        NinetyGegreeTurn(false);
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

void MotorsController::NinetyGegreeTurn(bool rightTurn){
    Stright(false);
    delay(100);
    Stop();
    delay(100);
    turning = true;
    initialTurningYaw = gyroscopeController->GetAdverageYaw();

    if(rightTurn){
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

void MotorsController::OneEightyGegreeTurn(){
    digitalWrite(forwardLeft, LOW);
    digitalWrite(backwardLeft, HIGH);
    digitalWrite(forwardRight, LOW);
    digitalWrite(backwardRight, HIGH);
    delay(460);
}


void MotorsController::Turn(){
    if(abs(initialTurningYaw - gyroscopeController->GetCurrentYaw()) > 90.0f){
        turning = false;

        //provisional
        analogWrite(leftSpeed, NORMAL_SPEED);
        analogWrite(rightSpeed, NORMAL_SPEED);

        digitalWrite(forwardLeft, LOW);
        digitalWrite(backwardLeft, HIGH);
        digitalWrite(forwardRight, LOW);
        digitalWrite(backwardRight, HIGH);
        delay(100);

        Stop();
        delay(100);
        Stright(true);
        delay(300);
        gyroscopeController->ResetYaw();
    }
}