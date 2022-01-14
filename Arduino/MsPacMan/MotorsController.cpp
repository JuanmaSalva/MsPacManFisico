#include "MotorsController.h"

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
}


void MotorsController::Update(){
    Action currentAction = lineTracker->GetCurrentAction();

    if(currentAction == stright){ //recto
        Stright(true);
        analogWrite(leftSpeed, NORMAL_SPEED);
        analogWrite(rightSpeed, NORMAL_SPEED);
    }
    // else if(izquierda == LINEA && centro == LINEA && derecha == LINEA){ //Giro 90 grados
    //   recta(false);
    //   delay(100);
    //   noventagrados(false);
    //   parada();
    //   delay(100);
    //   recta(true);
    //   delay(300);
    // }
    else if (currentAction == leftCorrection) { //desvio derecha
        Stright(true);
        analogWrite(rightSpeed, REDUCED_SPEED);
    }
    else if(currentAction == rightCorrection){ //desvio izquierda
        Stright(true);
        analogWrite(leftSpeed, REDUCED_SPEED);
    }
    else if (currentAction == lost){ //parada
        Stop();
    }
}

void MotorsController::SetLineTracker(LineTracker* _lineTracker){
    lineTracker = _lineTracker;
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
    delay(ROTATION_TIME);
}

void MotorsController::OneEightyGegreeTurn(){
    digitalWrite(forwardLeft, LOW);
    digitalWrite(backwardLeft, HIGH);
    digitalWrite(forwardRight, LOW);
    digitalWrite(backwardRight, HIGH);
    delay(460);
}