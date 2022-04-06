#pragma once
#include "TurningDirecction.h"

class DirectionController{
private:
	TurningDirection turningDirections[10] = { 
												TurningDirection::right, TurningDirection::none,
												TurningDirection::right, TurningDirection::left,
												TurningDirection::right, TurningDirection::right,
												TurningDirection::none, TurningDirection::none,
												TurningDirection::none, TurningDirection::right};
	int currentInstruction;

public:
	DirectionController();

	TurningDirection GetNextDirection();
};


/*

TurningDirection::left, TurningDirection::none,
TurningDirection::none, TurningDirection::none,
TurningDirection::left, TurningDirection::left,
TurningDirection::right, TurningDirection::left,
TurningDirection::none, TurningDirection::left

*/