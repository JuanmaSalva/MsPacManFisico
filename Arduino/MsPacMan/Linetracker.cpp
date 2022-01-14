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
    int izquierda = digitalRead(SENSOR_L);
    int centro = digitalRead(SENSOR_C);
    int derecha = digitalRead(SENSOR_R);

    if(izquierda == LINE && centro == CORRIDOR && derecha == LINE) //recto
        currentAction = stright;
    else if (izquierda == CORRIDOR && derecha == LINE)  //desvio derecha
        currentAction = leftCorrection;
    else if(izquierda == LINE && derecha == CORRIDOR) //desvio izquierda
        currentAction = rightCorrection;
    else
        currentAction = lost;
}

Action LineTracker::GetCurrentAction(){
    return currentAction;
}