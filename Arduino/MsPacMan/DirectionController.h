#pragma once
#include "TurningDirecction.h"

class MotorsController;

class DirectionController{
private:
	MotorsController* motorsController;
	TurningDirection turningDirections[];

public:
	DirectionController();
	void SetMotorsController(MotorsController* m);

};