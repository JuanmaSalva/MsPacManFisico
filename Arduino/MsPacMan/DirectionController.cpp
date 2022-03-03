#include "DirectionController.h"
#include "MotorsController.h"

DirectionController::DirectionController(){

}


void DirectionController::SetMotorsController(MotorsController* m){
	motorsController = m;
}