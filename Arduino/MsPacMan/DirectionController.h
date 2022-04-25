#pragma once
#include "TurningDirecction.h"

#define INSTRUCTIONS_COUNT 4

class DirectionController{
private:
	TurningDirection turningDirections[INSTRUCTIONS_COUNT] = {
		TurningDirection::left,TurningDirection::left,TurningDirection::left,TurningDirection::left
	 };
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



TurningDirection::right, TurningDirection::none,
TurningDirection::right, TurningDirection::left,
TurningDirection::right, TurningDirection::right,
TurningDirection::none, TurningDirection::none,
TurningDirection::none, TurningDirection::right


	TurningDirection::left, TurningDirection::none,
	TurningDirection::right, TurningDirection::none,
	TurningDirection::right, TurningDirection::right,
	TurningDirection::none, TurningDirection::none,
	TurningDirection::none, TurningDirection::left,
	TurningDirection::left
*/