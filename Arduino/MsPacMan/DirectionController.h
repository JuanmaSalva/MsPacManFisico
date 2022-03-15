#pragma once
#include "TurningDirecction.h"

class DirectionController{
private:
	TurningDirection turningDirections[16] = {TurningDirection::none, TurningDirection::none, 
												TurningDirection::none, TurningDirection::none,
												TurningDirection::left, TurningDirection::left,
												TurningDirection::none, TurningDirection::none,
												TurningDirection::none, TurningDirection::none,
												TurningDirection::left, TurningDirection::left,
												TurningDirection::none, TurningDirection::none,
												TurningDirection::none, TurningDirection::none};
	int currentInstruction;

public:
	DirectionController();

	TurningDirection GetNextDirection();
};