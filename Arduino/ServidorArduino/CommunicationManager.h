#pragma once
#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

enum ENTITY_STATE{
	SYNC_ATTEMP,
	SYNC,
	LINE_TRACKER_INITIALIZED,
	GYROSCOPE_INITIALIZED,
	MOTORS_INITIALIZES,
    OK
};

struct MESSAGE{
	int8_t id; //robot id
	ENTITY_STATE ent_state;
};



class CommunicationManager{
private:
	MESSAGE recvMsg;
	MESSAGE sendMsg;

	SoftwareSerial miBT;

	SoftEasyTransfer et_in;
	SoftEasyTransfer et_out;

    int red = 9;
    int green = 10;
    int blue = 11;

public:
    CommunicationManager();

    void Init();
    void Sync();
    void WaitForRobotToInitialize();



};