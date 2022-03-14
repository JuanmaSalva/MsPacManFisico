#include "DirectionController.h"
#include "MotorsController.h"

DirectionController::DirectionController(){
    currentInstruction = 0;
}

TurningDirection DirectionController::GetNextDirection(){
    TurningDirection aux = turningDirections[currentInstruction];
    currentInstruction = (currentInstruction + 1) % 13;
    return aux;
}