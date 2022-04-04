#pragma once
#include "TurningDirecction.h"

class DirectionController{
private:
	TurningDirection turningDirections[10] = { 
												TurningDirection::left, TurningDirection::none,
												TurningDirection::none, TurningDirection::none,
												TurningDirection::left, TurningDirection::left,
												TurningDirection::right, TurningDirection::left,
												TurningDirection::none, TurningDirection::left};
	int currentInstruction;

public:
	DirectionController();

	TurningDirection GetNextDirection();
};