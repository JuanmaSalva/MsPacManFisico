#include "LineTracker.h"

LineTracker::LineTracker(){
    currentAction = lost;
}

void LineTracker::Init(){
    pinMode(SENSOR_L, INPUT);
    pinMode(SENSOR_C, INPUT);
    pinMode(SENSOR_R, INPUT);
}

void LineTracker::Update(){
    int _left = digitalRead(SENSOR_L);
    int _center = digitalRead(SENSOR_C);
    int _right = digitalRead(SENSOR_R);

    // Serial.print(left);
    // Serial.print(" ");
    // Serial.print(center);
    // Serial.print(" ");
    // Serial.println(right);
    if(_left == LINE && _center == CORRIDOR && _right == LINE) //recto
        currentAction = straight;
    else if (_left == CORRIDOR && _right == LINE)  //desvio derecha
        currentAction = leftCorrection;
    else if(_left == LINE && _right == CORRIDOR) //desvio izquierda
        currentAction = rightCorrection;      
    else if(_left == LINE && _center == LINE && _right == LINE) //TODO de momento provisional
    {
        currentAction = leftTurn;
    }   
    else
        currentAction = lost;
}

Action LineTracker::GetCurrentAction(){
    return currentAction;
}