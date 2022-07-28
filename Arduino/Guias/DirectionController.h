#pragma once
#include "TurningDirecction.h"

#define INSTRUCTIONS_COUNT 5

class DirectionController{
private:
	//recorrido provisional
	TurningDirection turningDirections[INSTRUCTIONS_COUNT] = {
		TurningDirection::left, TurningDirection::left,
		TurningDirection::left, TurningDirection::left,
		TurningDirection::right	};

	int currentInstruction = 0;

public:
	DirectionController();

	TurningDirection GetNextDirection();
};