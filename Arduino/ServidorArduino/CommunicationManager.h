#pragma once
#include <SoftwareSerial.h>
#include <Arduino.h>

enum MESSAGE{
	SYNC_ATTEMP,
	SYNC,
	LINE_TRACKER_INITIALIZED,
	GYROSCOPE_INITIALIZED,
	MOTORS_INITIALIZES,

	OK
};

class CommunicationManager{
private:
	SoftwareSerial miBT;


    int red = 9;
    int green = 10;
    int blue = 11;

	void SendMsg(MESSAGE msg);
	MESSAGE ReadMsg();

public:
    CommunicationManager();

    void Init();
    void Sync();
    void WaitForRobotToInitialize();
	void WaitForMsg(MESSAGE msg);


};