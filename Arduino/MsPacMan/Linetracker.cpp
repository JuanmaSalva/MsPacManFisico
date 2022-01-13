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

    if(izquierda == LINEA && centro == PASILLO && derecha == LINEA) //recto
        currentAction = stright;
    else if (izquierda == PASILLO && derecha == LINEA)  //desvio derecha
        currentAction = leftCorrection;
    else if(izquierda == LINEA && derecha == PASILLO) //desvio izquierda
        currentAction = rightCorrection;
    else
        currentAction = lost;
}

Action LineTracker::GetCurrentAction(){
    return currentAction;
}