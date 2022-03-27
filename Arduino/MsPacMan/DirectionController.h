#pragma once
#include "TurningDirecction.h"

class DirectionController{
private:
	TurningDirection turningDirections[5] = {TurningDirection::left, TurningDirection::left, 
												TurningDirection::left, TurningDirection::none,
												TurningDirection::left};
	int currentInstruction;

public:
	DirectionController();

	TurningDirection GetNextDirection();
};