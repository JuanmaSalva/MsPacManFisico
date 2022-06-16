#pragma once
#include <Arduino.h>




#define BLACK 1
#define WHITE 0

class LineTracker{
private:
	int SENSOR = 9;
    bool blackLine = false;

public:

    LineTracker();

    void Init();
    void Update();

    bool IsBlackLine();
};