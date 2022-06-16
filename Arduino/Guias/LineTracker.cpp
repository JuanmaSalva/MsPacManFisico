#include "LineTracker.h"

LineTracker::LineTracker(){
}

void LineTracker::Init(){
	pinMode(SENSOR, INPUT);
}


void LineTracker::Update(){
	if(digitalRead(SENSOR) == BLACK)
		blackLine = true;
	else
		blackLine = false;
}

/**
 * @brief Devuelve si la linea de abajo del robot es negra o no
 * 
 * @return Color 
 */
bool LineTracker::IsBlackLine(){
	return blackLine;
}