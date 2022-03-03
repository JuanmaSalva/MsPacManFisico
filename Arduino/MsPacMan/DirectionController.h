#pragma once
#include "MotorsController.h"

class DirectionController{
private:
    MotorsController* motorsController;
    TurningDirection turningDirections[];

public:
    DirectionController();
    void SetMotorsController(MotorsController* m);

};